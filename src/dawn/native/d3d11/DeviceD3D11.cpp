// Copyright 2023 The Dawn Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "dawn/native/d3d11/DeviceD3D11.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <utility>

#include "dawn/common/GPUInfo.h"
#include "dawn/native/Buffer.h"
#include "dawn/native/ComputePipeline.h"
#include "dawn/native/D3D11Backend.h"
#include "dawn/native/DynamicUploader.h"
#include "dawn/native/Instance.h"
#include "dawn/native/RenderPipeline.h"
#include "dawn/native/Texture.h"
#include "dawn/native/d3d/D3DError.h"
#include "dawn/native/d3d11/AdapterD3D11.h"
#include "dawn/native/d3d11/BackendD3D11.h"
#include "dawn/native/d3d11/BindGroupD3D11.h"
#include "dawn/native/d3d11/BindGroupLayoutD3D11.h"
#include "dawn/native/d3d11/PipelineLayoutD3D11.h"
#include "dawn/native/d3d11/PlatformFunctionsD3D11.h"
#include "dawn/native/d3d11/QueueD3D11.h"
#include "dawn/native/d3d11/SamplerD3D11.h"
#include "dawn/native/d3d11/ShaderModuleD3D11.h"
#include "dawn/platform/DawnPlatform.h"
#include "dawn/platform/tracing/TraceEvent.h"

namespace dawn::native::d3d11 {
namespace {

static constexpr uint64_t kMaxDebugMessagesToPrint = 5;

void AppendDebugLayerMessagesToError(ID3D11InfoQueue* infoQueue,
                                     uint64_t totalErrors,
                                     ErrorData* error) {
    ASSERT(totalErrors > 0);
    ASSERT(error != nullptr);

    uint64_t errorsToPrint = std::min(kMaxDebugMessagesToPrint, totalErrors);
    for (uint64_t i = 0; i < errorsToPrint; ++i) {
        std::ostringstream messageStream;
        SIZE_T messageLength = 0;
        HRESULT hr = infoQueue->GetMessage(i, nullptr, &messageLength);
        if (FAILED(hr)) {
            messageStream << " ID3D11InfoQueue::GetMessage failed with " << hr;
            error->AppendBackendMessage(messageStream.str());
            continue;
        }

        std::unique_ptr<uint8_t[]> messageData(new uint8_t[messageLength]);
        D3D11_MESSAGE* message = reinterpret_cast<D3D11_MESSAGE*>(messageData.get());
        hr = infoQueue->GetMessage(i, message, &messageLength);
        if (FAILED(hr)) {
            messageStream << " ID3D11InfoQueue::GetMessage failed with " << hr;
            error->AppendBackendMessage(messageStream.str());
            continue;
        }

        messageStream << message->pDescription << " (" << message->ID << ")";
        error->AppendBackendMessage(messageStream.str());
    }
    if (errorsToPrint < totalErrors) {
        std::ostringstream messages;
        messages << (totalErrors - errorsToPrint) << " messages silenced";
        error->AppendBackendMessage(messages.str());
    }

    // We only print up to the first kMaxDebugMessagesToPrint errors
    infoQueue->ClearStoredMessages();
}

}  // namespace

// static
ResultOrError<Ref<Device>> Device::Create(Adapter* adapter,
                                          const DeviceDescriptor* descriptor,
                                          const TogglesState& deviceToggles) {
    Ref<Device> device = AcquireRef(new Device(adapter, descriptor, deviceToggles));
    DAWN_TRY(device->Initialize(descriptor));
    return device;
}

MaybeError Device::Initialize(const DeviceDescriptor* descriptor) {
    DAWN_TRY_ASSIGN(mD3d11Device, ToBackend(GetAdapter())->CreateD3D11Device());
    ASSERT(mD3d11Device != nullptr);

    DAWN_TRY(DeviceBase::Initialize(Queue::Create(this, &descriptor->defaultQueue)));

    // Get the ID3D11Device5 interface which is need for creating fences.
    // TODO(dawn:1741): Handle the case where ID3D11Device5 is not available.
    DAWN_TRY(CheckHRESULT(mD3d11Device.As(&mD3d11Device5), "D3D11: getting ID3D11Device5"));

    // Create the fence.
    DAWN_TRY(
        CheckHRESULT(mD3d11Device5->CreateFence(0, D3D11_FENCE_FLAG_SHARED, IID_PPV_ARGS(&mFence)),
                     "D3D11: creating fence"));

    DAWN_TRY(CheckHRESULT(mFence->CreateSharedHandle(nullptr, GENERIC_ALL, nullptr, &mFenceHandle),
                          "D3D11: creating fence shared handle"));

    // Create the fence event.
    mFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    SetLabelImpl();

    return {};
}

Device::~Device() {
    Destroy();

    // Close the handle here instead of in DestroyImpl. The handle is returned from
    // ExternalImageDXGI, so it needs to live as long as the Device ref does, even if the device
    // state is destroyed.
    if (mFenceHandle != nullptr) {
        ::CloseHandle(mFenceHandle);
        mFenceHandle = nullptr;
    }
}

ID3D11Device* Device::GetD3D11Device() const {
    return mD3d11Device.Get();
}

ID3D11Device5* Device::GetD3D11Device5() const {
    return mD3d11Device5.Get();
}

ResultOrError<CommandRecordingContext*> Device::GetPendingCommandContext(
    Device::SubmitMode submitMode) {
    // Callers of GetPendingCommandList do so to record commands. Only reserve a command
    // allocator when it is needed so we don't submit empty command lists
    if (!mPendingCommands.IsOpen()) {
        DAWN_TRY(mPendingCommands.Open(this));
    }
    if (submitMode == Device::SubmitMode::Normal) {
        mPendingCommands.SetNeedsSubmit();
    }
    return &mPendingCommands;
}

MaybeError Device::TickImpl() {
    // Perform cleanup operations to free unused objects
    [[maybe_unused]] ExecutionSerial completedSerial = GetCompletedCommandSerial();

    if (mPendingCommands.IsOpen() && mPendingCommands.NeedsSubmit()) {
        DAWN_TRY(ExecutePendingCommandContext());
        DAWN_TRY(NextSerial());
    }

    DAWN_TRY(CheckDebugLayerAndGenerateErrors());

    return {};
}

MaybeError Device::NextSerial() {
    IncrementLastSubmittedCommandSerial();

    TRACE_EVENT1(GetPlatform(), General, "D3D11Device::SignalFence", "serial",
                 uint64_t(GetLastSubmittedCommandSerial()));

    CommandRecordingContext* commandContext;
    DAWN_TRY_ASSIGN(commandContext, GetPendingCommandContext());

    DAWN_TRY(CheckHRESULT(commandContext->GetD3D11DeviceContext4()->Signal(
                              mFence.Get(), uint64_t(GetLastSubmittedCommandSerial())),
                          "D3D11 command queue signal fence"));

    return {};
}

MaybeError Device::WaitForSerial(ExecutionSerial serial) {
    DAWN_TRY(CheckPassedSerials());
    if (GetCompletedCommandSerial() < serial) {
        DAWN_TRY(CheckHRESULT(mFence->SetEventOnCompletion(uint64_t(serial), mFenceEvent),
                              "D3D11 set event on completion"));
        WaitForSingleObject(mFenceEvent, INFINITE);
        DAWN_TRY(CheckPassedSerials());
    }
    return {};
}

ResultOrError<ExecutionSerial> Device::CheckAndUpdateCompletedSerials() {
    ExecutionSerial completedSerial = ExecutionSerial(mFence->GetCompletedValue());
    if (DAWN_UNLIKELY(completedSerial == ExecutionSerial(UINT64_MAX))) {
        // GetCompletedValue returns UINT64_MAX if the device was removed.
        // Try to query the failure reason.
        DAWN_TRY(CheckHRESULT(mD3d11Device->GetDeviceRemovedReason(),
                              "ID3D11Device::GetDeviceRemovedReason"));
        // Otherwise, return a generic device lost error.
        return DAWN_DEVICE_LOST_ERROR("Device lost");
    }

    if (completedSerial <= GetCompletedCommandSerial()) {
        return ExecutionSerial(0);
    }

    return completedSerial;
}

void Device::ReferenceUntilUnused(ComPtr<IUnknown> object) {
    mUsedComObjectRefs.Enqueue(object, GetPendingCommandSerial());
}

bool Device::HasPendingCommands() const {
    return mPendingCommands.NeedsSubmit();
}

void Device::ForceEventualFlushOfCommands() {
    if (mPendingCommands.IsOpen()) {
        mPendingCommands.SetNeedsSubmit();
    }
}

MaybeError Device::ExecutePendingCommandContext() {
    return {};
}

ResultOrError<Ref<BindGroupBase>> Device::CreateBindGroupImpl(
    const BindGroupDescriptor* descriptor) {
    return BindGroup::Create(this, descriptor);
}

ResultOrError<Ref<BindGroupLayoutBase>> Device::CreateBindGroupLayoutImpl(
    const BindGroupLayoutDescriptor* descriptor,
    PipelineCompatibilityToken pipelineCompatibilityToken) {
    return BindGroupLayout::Create(this, descriptor, pipelineCompatibilityToken);
}

ResultOrError<Ref<BufferBase>> Device::CreateBufferImpl(const BufferDescriptor* descriptor) {
    return DAWN_UNIMPLEMENTED_ERROR("CreateBufferImpl");
}

ResultOrError<Ref<CommandBufferBase>> Device::CreateCommandBuffer(
    CommandEncoder* encoder,
    const CommandBufferDescriptor* descriptor) {
    return DAWN_UNIMPLEMENTED_ERROR("CreateCommandBuffer");
}

Ref<ComputePipelineBase> Device::CreateUninitializedComputePipelineImpl(
    const ComputePipelineDescriptor* descriptor) {
    return nullptr;
}

ResultOrError<Ref<PipelineLayoutBase>> Device::CreatePipelineLayoutImpl(
    const PipelineLayoutDescriptor* descriptor) {
    return PipelineLayout::Create(this, descriptor);
}

ResultOrError<Ref<QuerySetBase>> Device::CreateQuerySetImpl(const QuerySetDescriptor* descriptor) {
    return DAWN_UNIMPLEMENTED_ERROR("CreateQuerySetImpl");
}

Ref<RenderPipelineBase> Device::CreateUninitializedRenderPipelineImpl(
    const RenderPipelineDescriptor* descriptor) {
    return nullptr;
}

ResultOrError<Ref<SamplerBase>> Device::CreateSamplerImpl(const SamplerDescriptor* descriptor) {
    return Sampler::Create(this, descriptor);
}

ResultOrError<Ref<ShaderModuleBase>> Device::CreateShaderModuleImpl(
    const ShaderModuleDescriptor* descriptor,
    ShaderModuleParseResult* parseResult,
    OwnedCompilationMessages* compilationMessages) {
    return ShaderModule::Create(this, descriptor, parseResult, compilationMessages);
}

ResultOrError<Ref<SwapChainBase>> Device::CreateSwapChainImpl(
    const SwapChainDescriptor* descriptor) {
    return DAWN_UNIMPLEMENTED_ERROR("CreateSwapChainImpl");
}

ResultOrError<Ref<NewSwapChainBase>> Device::CreateSwapChainImpl(
    Surface* surface,
    NewSwapChainBase* previousSwapChain,
    const SwapChainDescriptor* descriptor) {
    return DAWN_UNIMPLEMENTED_ERROR("CreateSwapChainImpl");
}

ResultOrError<Ref<TextureBase>> Device::CreateTextureImpl(const TextureDescriptor* descriptor) {
    return DAWN_UNIMPLEMENTED_ERROR("CreateTextureImpl");
}

ResultOrError<Ref<TextureViewBase>> Device::CreateTextureViewImpl(
    TextureBase* texture,
    const TextureViewDescriptor* descriptor) {
    return DAWN_UNIMPLEMENTED_ERROR("CreateTextureViewImpl");
}

void Device::InitializeComputePipelineAsyncImpl(Ref<ComputePipelineBase> computePipeline,
                                                WGPUCreateComputePipelineAsyncCallback callback,
                                                void* userdata) {}

void Device::InitializeRenderPipelineAsyncImpl(Ref<RenderPipelineBase> renderPipeline,
                                               WGPUCreateRenderPipelineAsyncCallback callback,
                                               void* userdata) {}

MaybeError Device::CopyFromStagingToBufferImpl(BufferBase* source,
                                               uint64_t sourceOffset,
                                               BufferBase* destination,
                                               uint64_t destinationOffset,
                                               uint64_t size) {
    return DAWN_UNIMPLEMENTED_ERROR("CopyFromStagingToBufferImpl");
}

MaybeError Device::CopyFromStagingToTextureImpl(const BufferBase* source,
                                                const TextureDataLayout& src,
                                                const TextureCopy& dst,
                                                const Extent3D& copySizePixels) {
    return DAWN_UNIMPLEMENTED_ERROR("CopyFromStagingToTextureImpl");
}

const DeviceInfo& Device::GetDeviceInfo() const {
    return ToBackend(GetAdapter())->GetDeviceInfo();
}

MaybeError Device::WaitForIdleForDestruction() {
    // Immediately forget about all pending commands
    mPendingCommands.Release();

    DAWN_TRY(NextSerial());
    // Wait for all in-flight commands to finish executing
    DAWN_TRY(WaitForSerial(GetLastSubmittedCommandSerial()));

    return {};
}

MaybeError Device::CheckDebugLayerAndGenerateErrors() {
    if (!GetAdapter()->GetInstance()->IsBackendValidationEnabled()) {
        return {};
    }

    ComPtr<ID3D11InfoQueue> infoQueue;
    DAWN_TRY(CheckHRESULT(mD3d11Device.As(&infoQueue),
                          "D3D11 QueryInterface ID3D11Device to ID3D11InfoQueue"));
    uint64_t totalErrors = infoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();

    // Check if any errors have occurred otherwise we would be creating an empty error. Note
    // that we use GetNumStoredMessagesAllowedByRetrievalFilter instead of GetNumStoredMessages
    // because we only convert WARNINGS or higher messages to dawn errors.
    if (totalErrors == 0) {
        return {};
    }

    auto error = DAWN_INTERNAL_ERROR("The D3D11 debug layer reported uncaught errors.");

    AppendDebugLayerMessagesToError(infoQueue.Get(), totalErrors, error.get());

    return error;
}

void Device::AppendDebugLayerMessages(ErrorData* error) {
    if (!GetAdapter()->GetInstance()->IsBackendValidationEnabled()) {
        return;
    }

    ComPtr<ID3D11InfoQueue> infoQueue;
    if (FAILED(mD3d11Device.As(&infoQueue))) {
        return;
    }
    uint64_t totalErrors = infoQueue->GetNumStoredMessagesAllowedByRetrievalFilter();

    if (totalErrors == 0) {
        return;
    }

    AppendDebugLayerMessagesToError(infoQueue.Get(), totalErrors, error);
}

void Device::DestroyImpl() {
    ASSERT(GetState() == State::Disconnected);

    if (mFenceEvent != nullptr) {
        ::CloseHandle(mFenceEvent);
        mFenceEvent = nullptr;
    }
}

uint32_t Device::GetOptimalBytesPerRowAlignment() const {
    return 256;
}

uint64_t Device::GetOptimalBufferToTextureCopyOffsetAlignment() const {
    return 1;
}

float Device::GetTimestampPeriodInNS() const {
    return 1.0f;
}

bool Device::ShouldDuplicateNumWorkgroupsForDispatchIndirect(
    ComputePipelineBase* computePipeline) const {
    return false;
}

void Device::SetLabelImpl() {}

bool Device::MayRequireDuplicationOfIndirectParameters() const {
    return true;
}

bool Device::ShouldDuplicateParametersForDrawIndirect(
    const RenderPipelineBase* renderPipelineBase) const {
    // return ToBackend(renderPipelineBase)->UsesVertexOrInstanceIndex();
    return false;
}

uint64_t Device::GetBufferCopyOffsetAlignmentForDepthStencil() const {
    return DeviceBase::GetBufferCopyOffsetAlignmentForDepthStencil();
}

HANDLE Device::GetFenceHandle() const {
    return mFenceHandle;
}

}  // namespace dawn::native::d3d11
