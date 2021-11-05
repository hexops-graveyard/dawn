
#include "dawn_native/dawn_platform.h"
#include "dawn_native/DawnNative.h"

#include <algorithm>
#include <vector>

#include "dawn_native/BindGroup.h"
#include "dawn_native/BindGroupLayout.h"
#include "dawn_native/Buffer.h"
#include "dawn_native/CommandBuffer.h"
#include "dawn_native/CommandEncoder.h"
#include "dawn_native/ComputePassEncoder.h"
#include "dawn_native/ComputePipeline.h"
#include "dawn_native/Device.h"
#include "dawn_native/ExternalTexture.h"
#include "dawn_native/Instance.h"
#include "dawn_native/PipelineLayout.h"
#include "dawn_native/QuerySet.h"
#include "dawn_native/Queue.h"
#include "dawn_native/RenderBundle.h"
#include "dawn_native/RenderBundleEncoder.h"
#include "dawn_native/RenderPassEncoder.h"
#include "dawn_native/RenderPipeline.h"
#include "dawn_native/Sampler.h"
#include "dawn_native/ShaderModule.h"
#include "dawn_native/Surface.h"
#include "dawn_native/SwapChain.h"
#include "dawn_native/Texture.h"

namespace dawn_native {

    namespace {


        void NativeBindGroupReference(WGPUBindGroup cSelf) {
            auto self = reinterpret_cast<BindGroupBase*>(cSelf);

            self->APIReference();
        }

        void NativeBindGroupRelease(WGPUBindGroup cSelf) {
            auto self = reinterpret_cast<BindGroupBase*>(cSelf);

            self->APIRelease();
        }

        void NativeBindGroupLayoutReference(WGPUBindGroupLayout cSelf) {
            auto self = reinterpret_cast<BindGroupLayoutBase*>(cSelf);

            self->APIReference();
        }

        void NativeBindGroupLayoutRelease(WGPUBindGroupLayout cSelf) {
            auto self = reinterpret_cast<BindGroupLayoutBase*>(cSelf);

            self->APIRelease();
        }

        void NativeBufferDestroy(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->APIDestroy();
        }

        void const * NativeBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            auto offset_ = offset;
            auto size_ = size;
            auto result =            self->APIGetConstMappedRange(offset_, size_);
            return result;
        }

        void * NativeBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            auto offset_ = offset;
            auto size_ = size;
            auto result =            self->APIGetMappedRange(offset_, size_);
            return result;
        }

        void NativeBufferMapAsync(WGPUBuffer cSelf, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            auto mode_ = static_cast<wgpu::MapMode>(mode);
            auto offset_ = offset;
            auto size_ = size;
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APIMapAsync(mode_, offset_, size_, callback_, userdata_);
        }

        void NativeBufferSetLabel(WGPUBuffer cSelf, char const * label) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            auto label_ = reinterpret_cast<char const * >(label);
            self->APISetLabel(label_);
        }

        void NativeBufferUnmap(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->APIUnmap();
        }

        void NativeBufferReference(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->APIReference();
        }

        void NativeBufferRelease(WGPUBuffer cSelf) {
            auto self = reinterpret_cast<BufferBase*>(cSelf);

            self->APIRelease();
        }

        void NativeCommandBufferReference(WGPUCommandBuffer cSelf) {
            auto self = reinterpret_cast<CommandBufferBase*>(cSelf);

            self->APIReference();
        }

        void NativeCommandBufferRelease(WGPUCommandBuffer cSelf) {
            auto self = reinterpret_cast<CommandBufferBase*>(cSelf);

            self->APIRelease();
        }

        WGPUComputePassEncoder NativeCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ComputePassDescriptor const * >(descriptor);
            auto result =            self->APIBeginComputePass(descriptor_);
            return reinterpret_cast<WGPUComputePassEncoder>(result);
        }

        WGPURenderPassEncoder NativeCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderPassDescriptor const * >(descriptor);
            auto result =            self->APIBeginRenderPass(descriptor_);
            return reinterpret_cast<WGPURenderPassEncoder>(result);
        }

        void NativeCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<BufferBase* >(source);
            auto sourceOffset_ = sourceOffset;
            auto destination_ = reinterpret_cast<BufferBase* >(destination);
            auto destinationOffset_ = destinationOffset;
            auto size_ = size;
            self->APICopyBufferToBuffer(source_, sourceOffset_, destination_, destinationOffset_, size_);
        }

        void NativeCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<ImageCopyBuffer const * >(source);
            auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            self->APICopyBufferToTexture(source_, destination_, copySize_);
        }

        void NativeCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
            auto destination_ = reinterpret_cast<ImageCopyBuffer const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            self->APICopyTextureToBuffer(source_, destination_, copySize_);
        }

        void NativeCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
            auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            self->APICopyTextureToTexture(source_, destination_, copySize_);
        }

        void NativeCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
            auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            self->APICopyTextureToTextureInternal(source_, destination_, copySize_);
        }

        WGPUCommandBuffer NativeCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<CommandBufferDescriptor const * >(descriptor);
            auto result =            self->APIFinish(descriptor_);
            return reinterpret_cast<WGPUCommandBuffer>(result);
        }

        void NativeCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, char const * message) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto message_ = reinterpret_cast<char const * >(message);
            self->APIInjectValidationError(message_);
        }

        void NativeCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->APIInsertDebugMarker(markerLabel_);
        }

        void NativeCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            self->APIPopDebugGroup();
        }

        void NativeCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->APIPushDebugGroup(groupLabel_);
        }

        void NativeCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto firstQuery_ = firstQuery;
            auto queryCount_ = queryCount;
            auto destination_ = reinterpret_cast<BufferBase* >(destination);
            auto destinationOffset_ = destinationOffset;
            self->APIResolveQuerySet(querySet_, firstQuery_, queryCount_, destination_, destinationOffset_);
        }

        void NativeCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto bufferOffset_ = bufferOffset;
            auto data_ = reinterpret_cast<uint8_t const * >(data);
            auto size_ = size;
            self->APIWriteBuffer(buffer_, bufferOffset_, data_, size_);
        }

        void NativeCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto queryIndex_ = queryIndex;
            self->APIWriteTimestamp(querySet_, queryIndex_);
        }

        void NativeCommandEncoderReference(WGPUCommandEncoder cSelf) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            self->APIReference();
        }

        void NativeCommandEncoderRelease(WGPUCommandEncoder cSelf) {
            auto self = reinterpret_cast<CommandEncoderBase*>(cSelf);

            self->APIRelease();
        }

        void NativeComputePassEncoderDispatch(WGPUComputePassEncoder cSelf, uint32_t x, uint32_t y, uint32_t z) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto x_ = x;
            auto y_ = y;
            auto z_ = z;
            self->APIDispatch(x_, y_, z_);
        }

        void NativeComputePassEncoderDispatchIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->APIDispatchIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeComputePassEncoderEndPass(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->APIEndPass();
        }

        void NativeComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->APIInsertDebugMarker(markerLabel_);
        }

        void NativeComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->APIPopDebugGroup();
        }

        void NativeComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->APIPushDebugGroup(groupLabel_);
        }

        void NativeComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto group_ = reinterpret_cast<BindGroupBase* >(group);
            auto dynamicOffsetCount_ = dynamicOffsetCount;
            auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
            self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
        }

        void NativeComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto pipeline_ = reinterpret_cast<ComputePipelineBase* >(pipeline);
            self->APISetPipeline(pipeline_);
        }

        void NativeComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto queryIndex_ = queryIndex;
            self->APIWriteTimestamp(querySet_, queryIndex_);
        }

        void NativeComputePassEncoderReference(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->APIReference();
        }

        void NativeComputePassEncoderRelease(WGPUComputePassEncoder cSelf) {
            auto self = reinterpret_cast<ComputePassEncoderBase*>(cSelf);

            self->APIRelease();
        }

        WGPUBindGroupLayout NativeComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
            auto self = reinterpret_cast<ComputePipelineBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto result =            self->APIGetBindGroupLayout(groupIndex_);
            return reinterpret_cast<WGPUBindGroupLayout>(result);
        }

        void NativeComputePipelineSetLabel(WGPUComputePipeline cSelf, char const * label) {
            auto self = reinterpret_cast<ComputePipelineBase*>(cSelf);

            auto label_ = reinterpret_cast<char const * >(label);
            self->APISetLabel(label_);
        }

        void NativeComputePipelineReference(WGPUComputePipeline cSelf) {
            auto self = reinterpret_cast<ComputePipelineBase*>(cSelf);

            self->APIReference();
        }

        void NativeComputePipelineRelease(WGPUComputePipeline cSelf) {
            auto self = reinterpret_cast<ComputePipelineBase*>(cSelf);

            self->APIRelease();
        }

        WGPUBindGroup NativeDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<BindGroupDescriptor const * >(descriptor);
            auto result =            self->APICreateBindGroup(descriptor_);
            return reinterpret_cast<WGPUBindGroup>(result);
        }

        WGPUBindGroupLayout NativeDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<BindGroupLayoutDescriptor const * >(descriptor);
            auto result =            self->APICreateBindGroupLayout(descriptor_);
            return reinterpret_cast<WGPUBindGroupLayout>(result);
        }

        WGPUBuffer NativeDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<BufferDescriptor const * >(descriptor);
            auto result =            self->APICreateBuffer(descriptor_);
            return reinterpret_cast<WGPUBuffer>(result);
        }

        WGPUCommandEncoder NativeDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<CommandEncoderDescriptor const * >(descriptor);
            auto result =            self->APICreateCommandEncoder(descriptor_);
            return reinterpret_cast<WGPUCommandEncoder>(result);
        }

        WGPUComputePipeline NativeDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const * >(descriptor);
            auto result =            self->APICreateComputePipeline(descriptor_);
            return reinterpret_cast<WGPUComputePipeline>(result);
        }

        void NativeDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const * >(descriptor);
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APICreateComputePipelineAsync(descriptor_, callback_, userdata_);
        }

        WGPUBuffer NativeDeviceCreateErrorBuffer(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto result =            self->APICreateErrorBuffer();
            return reinterpret_cast<WGPUBuffer>(result);
        }

        WGPUExternalTexture NativeDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto externalTextureDescriptor_ = reinterpret_cast<ExternalTextureDescriptor const * >(externalTextureDescriptor);
            auto result =            self->APICreateExternalTexture(externalTextureDescriptor_);
            return reinterpret_cast<WGPUExternalTexture>(result);
        }

        WGPUPipelineLayout NativeDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<PipelineLayoutDescriptor const * >(descriptor);
            auto result =            self->APICreatePipelineLayout(descriptor_);
            return reinterpret_cast<WGPUPipelineLayout>(result);
        }

        WGPUQuerySet NativeDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<QuerySetDescriptor const * >(descriptor);
            auto result =            self->APICreateQuerySet(descriptor_);
            return reinterpret_cast<WGPUQuerySet>(result);
        }

        WGPURenderBundleEncoder NativeDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderBundleEncoderDescriptor const * >(descriptor);
            auto result =            self->APICreateRenderBundleEncoder(descriptor_);
            return reinterpret_cast<WGPURenderBundleEncoder>(result);
        }

        WGPURenderPipeline NativeDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const * >(descriptor);
            auto result =            self->APICreateRenderPipeline(descriptor_);
            return reinterpret_cast<WGPURenderPipeline>(result);
        }

        void NativeDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const * >(descriptor);
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APICreateRenderPipelineAsync(descriptor_, callback_, userdata_);
        }

        WGPUSampler NativeDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<SamplerDescriptor const * >(descriptor);
            auto result =            self->APICreateSampler(descriptor_);
            return reinterpret_cast<WGPUSampler>(result);
        }

        WGPUShaderModule NativeDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<ShaderModuleDescriptor const * >(descriptor);
            auto result =            self->APICreateShaderModule(descriptor_);
            return reinterpret_cast<WGPUShaderModule>(result);
        }

        WGPUSwapChain NativeDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto surface_ = reinterpret_cast<SurfaceBase* >(surface);
            auto descriptor_ = reinterpret_cast<SwapChainDescriptor const * >(descriptor);
            auto result =            self->APICreateSwapChain(surface_, descriptor_);
            return reinterpret_cast<WGPUSwapChain>(result);
        }

        WGPUTexture NativeDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<TextureDescriptor const * >(descriptor);
            auto result =            self->APICreateTexture(descriptor_);
            return reinterpret_cast<WGPUTexture>(result);
        }

        bool NativeDeviceGetLimits(WGPUDevice cSelf, WGPUSupportedLimits * limits) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto limits_ = reinterpret_cast<SupportedLimits * >(limits);
            auto result =            self->APIGetLimits(limits_);
            return result;
        }

        WGPUQueue NativeDeviceGetQueue(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto result =            self->APIGetQueue();
            return reinterpret_cast<WGPUQueue>(result);
        }

        void NativeDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto type_ = static_cast<wgpu::ErrorType>(type);
            auto message_ = reinterpret_cast<char const * >(message);
            self->APIInjectError(type_, message_);
        }

        void NativeDeviceLoseForTesting(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->APILoseForTesting();
        }

        bool NativeDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            auto result =            self->APIPopErrorScope(callback_, userdata_);
            return result;
        }

        void NativeDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto filter_ = static_cast<wgpu::ErrorFilter>(filter);
            self->APIPushErrorScope(filter_);
        }

        void NativeDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APISetDeviceLostCallback(callback_, userdata_);
        }

        void NativeDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APISetLoggingCallback(callback_, userdata_);
        }

        void NativeDeviceSetUncapturedErrorCallback(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APISetUncapturedErrorCallback(callback_, userdata_);
        }

        void NativeDeviceTick(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->APITick();
        }

        void NativeDeviceReference(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->APIReference();
        }

        void NativeDeviceRelease(WGPUDevice cSelf) {
            auto self = reinterpret_cast<DeviceBase*>(cSelf);

            self->APIRelease();
        }

        void NativeExternalTextureDestroy(WGPUExternalTexture cSelf) {
            auto self = reinterpret_cast<ExternalTextureBase*>(cSelf);

            self->APIDestroy();
        }

        void NativeExternalTextureReference(WGPUExternalTexture cSelf) {
            auto self = reinterpret_cast<ExternalTextureBase*>(cSelf);

            self->APIReference();
        }

        void NativeExternalTextureRelease(WGPUExternalTexture cSelf) {
            auto self = reinterpret_cast<ExternalTextureBase*>(cSelf);

            self->APIRelease();
        }

        WGPUSurface NativeInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
            auto self = reinterpret_cast<InstanceBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<SurfaceDescriptor const * >(descriptor);
            auto result =            self->APICreateSurface(descriptor_);
            return reinterpret_cast<WGPUSurface>(result);
        }

        void NativeInstanceReference(WGPUInstance cSelf) {
            auto self = reinterpret_cast<InstanceBase*>(cSelf);

            self->APIReference();
        }

        void NativeInstanceRelease(WGPUInstance cSelf) {
            auto self = reinterpret_cast<InstanceBase*>(cSelf);

            self->APIRelease();
        }

        void NativePipelineLayoutReference(WGPUPipelineLayout cSelf) {
            auto self = reinterpret_cast<PipelineLayoutBase*>(cSelf);

            self->APIReference();
        }

        void NativePipelineLayoutRelease(WGPUPipelineLayout cSelf) {
            auto self = reinterpret_cast<PipelineLayoutBase*>(cSelf);

            self->APIRelease();
        }

        void NativeQuerySetDestroy(WGPUQuerySet cSelf) {
            auto self = reinterpret_cast<QuerySetBase*>(cSelf);

            self->APIDestroy();
        }

        void NativeQuerySetReference(WGPUQuerySet cSelf) {
            auto self = reinterpret_cast<QuerySetBase*>(cSelf);

            self->APIReference();
        }

        void NativeQuerySetRelease(WGPUQuerySet cSelf) {
            auto self = reinterpret_cast<QuerySetBase*>(cSelf);

            self->APIRelease();
        }

        void NativeQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
            auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
            auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
            auto options_ = reinterpret_cast<CopyTextureForBrowserOptions const * >(options);
            self->APICopyTextureForBrowser(source_, destination_, copySize_, options_);
        }

        void NativeQueueOnSubmittedWorkDone(WGPUQueue cSelf, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto signalValue_ = signalValue;
            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APIOnSubmittedWorkDone(signalValue_, callback_, userdata_);
        }

        void NativeQueueSubmit(WGPUQueue cSelf, uint32_t commandCount, WGPUCommandBuffer const * commands) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto commandCount_ = commandCount;
            auto commands_ = reinterpret_cast<CommandBufferBase* const * >(commands);
            self->APISubmit(commandCount_, commands_);
        }

        void NativeQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto bufferOffset_ = bufferOffset;
            auto data_ = reinterpret_cast<void const * >(data);
            auto size_ = size;
            self->APIWriteBuffer(buffer_, bufferOffset_, data_, size_);
        }

        void NativeQueueWriteTexture(WGPUQueue cSelf, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
            auto data_ = reinterpret_cast<void const * >(data);
            auto dataSize_ = dataSize;
            auto dataLayout_ = reinterpret_cast<TextureDataLayout const * >(dataLayout);
            auto writeSize_ = reinterpret_cast<Extent3D const * >(writeSize);
            self->APIWriteTexture(destination_, data_, dataSize_, dataLayout_, writeSize_);
        }

        void NativeQueueReference(WGPUQueue cSelf) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            self->APIReference();
        }

        void NativeQueueRelease(WGPUQueue cSelf) {
            auto self = reinterpret_cast<QueueBase*>(cSelf);

            self->APIRelease();
        }

        void NativeRenderBundleReference(WGPURenderBundle cSelf) {
            auto self = reinterpret_cast<RenderBundleBase*>(cSelf);

            self->APIReference();
        }

        void NativeRenderBundleRelease(WGPURenderBundle cSelf) {
            auto self = reinterpret_cast<RenderBundleBase*>(cSelf);

            self->APIRelease();
        }

        void NativeRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto vertexCount_ = vertexCount;
            auto instanceCount_ = instanceCount;
            auto firstVertex_ = firstVertex;
            auto firstInstance_ = firstInstance;
            self->APIDraw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
        }

        void NativeRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto indexCount_ = indexCount;
            auto instanceCount_ = instanceCount;
            auto firstIndex_ = firstIndex;
            auto baseVertex_ = baseVertex;
            auto firstInstance_ = firstInstance;
            self->APIDrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
        }

        void NativeRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->APIDrawIndexedIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->APIDrawIndirect(indirectBuffer_, indirectOffset_);
        }

        WGPURenderBundle NativeRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<RenderBundleDescriptor const * >(descriptor);
            auto result =            self->APIFinish(descriptor_);
            return reinterpret_cast<WGPURenderBundle>(result);
        }

        void NativeRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->APIInsertDebugMarker(markerLabel_);
        }

        void NativeRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            self->APIPopDebugGroup();
        }

        void NativeRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->APIPushDebugGroup(groupLabel_);
        }

        void NativeRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto group_ = reinterpret_cast<BindGroupBase* >(group);
            auto dynamicOffsetCount_ = dynamicOffsetCount;
            auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
            self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
        }

        void NativeRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto format_ = static_cast<wgpu::IndexFormat>(format);
            auto offset_ = offset;
            auto size_ = size;
            self->APISetIndexBuffer(buffer_, format_, offset_, size_);
        }

        void NativeRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto pipeline_ = reinterpret_cast<RenderPipelineBase* >(pipeline);
            self->APISetPipeline(pipeline_);
        }

        void NativeRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            auto slot_ = slot;
            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto offset_ = offset;
            auto size_ = size;
            self->APISetVertexBuffer(slot_, buffer_, offset_, size_);
        }

        void NativeRenderBundleEncoderReference(WGPURenderBundleEncoder cSelf) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            self->APIReference();
        }

        void NativeRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf) {
            auto self = reinterpret_cast<RenderBundleEncoderBase*>(cSelf);

            self->APIRelease();
        }

        void NativeRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto queryIndex_ = queryIndex;
            self->APIBeginOcclusionQuery(queryIndex_);
        }

        void NativeRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto vertexCount_ = vertexCount;
            auto instanceCount_ = instanceCount;
            auto firstVertex_ = firstVertex;
            auto firstInstance_ = firstInstance;
            self->APIDraw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
        }

        void NativeRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto indexCount_ = indexCount;
            auto instanceCount_ = instanceCount;
            auto firstIndex_ = firstIndex;
            auto baseVertex_ = baseVertex;
            auto firstInstance_ = firstInstance;
            self->APIDrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
        }

        void NativeRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->APIDrawIndexedIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
            auto indirectOffset_ = indirectOffset;
            self->APIDrawIndirect(indirectBuffer_, indirectOffset_);
        }

        void NativeRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->APIEndOcclusionQuery();
        }

        void NativeRenderPassEncoderEndPass(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->APIEndPass();
        }

        void NativeRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto bundlesCount_ = bundlesCount;
            auto bundles_ = reinterpret_cast<RenderBundleBase* const * >(bundles);
            self->APIExecuteBundles(bundlesCount_, bundles_);
        }

        void NativeRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
            self->APIInsertDebugMarker(markerLabel_);
        }

        void NativeRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->APIPopDebugGroup();
        }

        void NativeRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
            self->APIPushDebugGroup(groupLabel_);
        }

        void NativeRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto group_ = reinterpret_cast<BindGroupBase* >(group);
            auto dynamicOffsetCount_ = dynamicOffsetCount;
            auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
            self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
        }

        void NativeRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto color_ = reinterpret_cast<Color const * >(color);
            self->APISetBlendConstant(color_);
        }

        void NativeRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto format_ = static_cast<wgpu::IndexFormat>(format);
            auto offset_ = offset;
            auto size_ = size;
            self->APISetIndexBuffer(buffer_, format_, offset_, size_);
        }

        void NativeRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto pipeline_ = reinterpret_cast<RenderPipelineBase* >(pipeline);
            self->APISetPipeline(pipeline_);
        }

        void NativeRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto x_ = x;
            auto y_ = y;
            auto width_ = width;
            auto height_ = height;
            self->APISetScissorRect(x_, y_, width_, height_);
        }

        void NativeRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto reference_ = reference;
            self->APISetStencilReference(reference_);
        }

        void NativeRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto slot_ = slot;
            auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
            auto offset_ = offset;
            auto size_ = size;
            self->APISetVertexBuffer(slot_, buffer_, offset_, size_);
        }

        void NativeRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto x_ = x;
            auto y_ = y;
            auto width_ = width;
            auto height_ = height;
            auto minDepth_ = minDepth;
            auto maxDepth_ = maxDepth;
            self->APISetViewport(x_, y_, width_, height_, minDepth_, maxDepth_);
        }

        void NativeRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
            auto queryIndex_ = queryIndex;
            self->APIWriteTimestamp(querySet_, queryIndex_);
        }

        void NativeRenderPassEncoderReference(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->APIReference();
        }

        void NativeRenderPassEncoderRelease(WGPURenderPassEncoder cSelf) {
            auto self = reinterpret_cast<RenderPassEncoderBase*>(cSelf);

            self->APIRelease();
        }

        WGPUBindGroupLayout NativeRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
            auto self = reinterpret_cast<RenderPipelineBase*>(cSelf);

            auto groupIndex_ = groupIndex;
            auto result =            self->APIGetBindGroupLayout(groupIndex_);
            return reinterpret_cast<WGPUBindGroupLayout>(result);
        }

        void NativeRenderPipelineSetLabel(WGPURenderPipeline cSelf, char const * label) {
            auto self = reinterpret_cast<RenderPipelineBase*>(cSelf);

            auto label_ = reinterpret_cast<char const * >(label);
            self->APISetLabel(label_);
        }

        void NativeRenderPipelineReference(WGPURenderPipeline cSelf) {
            auto self = reinterpret_cast<RenderPipelineBase*>(cSelf);

            self->APIReference();
        }

        void NativeRenderPipelineRelease(WGPURenderPipeline cSelf) {
            auto self = reinterpret_cast<RenderPipelineBase*>(cSelf);

            self->APIRelease();
        }

        void NativeSamplerReference(WGPUSampler cSelf) {
            auto self = reinterpret_cast<SamplerBase*>(cSelf);

            self->APIReference();
        }

        void NativeSamplerRelease(WGPUSampler cSelf) {
            auto self = reinterpret_cast<SamplerBase*>(cSelf);

            self->APIRelease();
        }

        void NativeShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallback callback, void * userdata) {
            auto self = reinterpret_cast<ShaderModuleBase*>(cSelf);

            auto callback_ = callback;
            auto userdata_ = reinterpret_cast<void * >(userdata);
            self->APIGetCompilationInfo(callback_, userdata_);
        }

        void NativeShaderModuleSetLabel(WGPUShaderModule cSelf, char const * label) {
            auto self = reinterpret_cast<ShaderModuleBase*>(cSelf);

            auto label_ = reinterpret_cast<char const * >(label);
            self->APISetLabel(label_);
        }

        void NativeShaderModuleReference(WGPUShaderModule cSelf) {
            auto self = reinterpret_cast<ShaderModuleBase*>(cSelf);

            self->APIReference();
        }

        void NativeShaderModuleRelease(WGPUShaderModule cSelf) {
            auto self = reinterpret_cast<ShaderModuleBase*>(cSelf);

            self->APIRelease();
        }

        void NativeSurfaceReference(WGPUSurface cSelf) {
            auto self = reinterpret_cast<SurfaceBase*>(cSelf);

            self->APIReference();
        }

        void NativeSurfaceRelease(WGPUSurface cSelf) {
            auto self = reinterpret_cast<SurfaceBase*>(cSelf);

            self->APIRelease();
        }

        void NativeSwapChainConfigure(WGPUSwapChain cSelf, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            auto format_ = static_cast<wgpu::TextureFormat>(format);
            auto allowedUsage_ = static_cast<wgpu::TextureUsage>(allowedUsage);
            auto width_ = width;
            auto height_ = height;
            self->APIConfigure(format_, allowedUsage_, width_, height_);
        }

        WGPUTextureView NativeSwapChainGetCurrentTextureView(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            auto result =            self->APIGetCurrentTextureView();
            return reinterpret_cast<WGPUTextureView>(result);
        }

        void NativeSwapChainPresent(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            self->APIPresent();
        }

        void NativeSwapChainReference(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            self->APIReference();
        }

        void NativeSwapChainRelease(WGPUSwapChain cSelf) {
            auto self = reinterpret_cast<SwapChainBase*>(cSelf);

            self->APIRelease();
        }

        WGPUTextureView NativeTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            auto descriptor_ = reinterpret_cast<TextureViewDescriptor const * >(descriptor);
            auto result =            self->APICreateView(descriptor_);
            return reinterpret_cast<WGPUTextureView>(result);
        }

        void NativeTextureDestroy(WGPUTexture cSelf) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            self->APIDestroy();
        }

        void NativeTextureSetLabel(WGPUTexture cSelf, char const * label) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            auto label_ = reinterpret_cast<char const * >(label);
            self->APISetLabel(label_);
        }

        void NativeTextureReference(WGPUTexture cSelf) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            self->APIReference();
        }

        void NativeTextureRelease(WGPUTexture cSelf) {
            auto self = reinterpret_cast<TextureBase*>(cSelf);

            self->APIRelease();
        }

        void NativeTextureViewReference(WGPUTextureView cSelf) {
            auto self = reinterpret_cast<TextureViewBase*>(cSelf);

            self->APIReference();
        }

        void NativeTextureViewRelease(WGPUTextureView cSelf) {
            auto self = reinterpret_cast<TextureViewBase*>(cSelf);

            self->APIRelease();
        }

        struct ProcEntry {
            WGPUProc proc;
            const char* name;
        };
        static const ProcEntry sProcMap[] = {
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutReference), "wgpuBindGroupLayoutReference" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutRelease), "wgpuBindGroupLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupReference), "wgpuBindGroupReference" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupRelease), "wgpuBindGroupRelease" },
            { reinterpret_cast<WGPUProc>(NativeBufferDestroy), "wgpuBufferDestroy" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetConstMappedRange), "wgpuBufferGetConstMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetMappedRange), "wgpuBufferGetMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferMapAsync), "wgpuBufferMapAsync" },
            { reinterpret_cast<WGPUProc>(NativeBufferReference), "wgpuBufferReference" },
            { reinterpret_cast<WGPUProc>(NativeBufferRelease), "wgpuBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeBufferSetLabel), "wgpuBufferSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeBufferUnmap), "wgpuBufferUnmap" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferReference), "wgpuCommandBufferReference" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferRelease), "wgpuCommandBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginComputePass), "wgpuCommandEncoderBeginComputePass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginRenderPass), "wgpuCommandEncoderBeginRenderPass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyBufferToBuffer), "wgpuCommandEncoderCopyBufferToBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyBufferToTexture), "wgpuCommandEncoderCopyBufferToTexture" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyTextureToBuffer), "wgpuCommandEncoderCopyTextureToBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyTextureToTexture), "wgpuCommandEncoderCopyTextureToTexture" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyTextureToTextureInternal), "wgpuCommandEncoderCopyTextureToTextureInternal" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderFinish), "wgpuCommandEncoderFinish" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderInjectValidationError), "wgpuCommandEncoderInjectValidationError" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderInsertDebugMarker), "wgpuCommandEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderPopDebugGroup), "wgpuCommandEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderPushDebugGroup), "wgpuCommandEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderReference), "wgpuCommandEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderRelease), "wgpuCommandEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderResolveQuerySet), "wgpuCommandEncoderResolveQuerySet" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderWriteBuffer), "wgpuCommandEncoderWriteBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderWriteTimestamp), "wgpuCommandEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatch), "wgpuComputePassEncoderDispatch" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatchIndirect), "wgpuComputePassEncoderDispatchIndirect" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderEndPass), "wgpuComputePassEncoderEndPass" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderInsertDebugMarker), "wgpuComputePassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPopDebugGroup), "wgpuComputePassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPushDebugGroup), "wgpuComputePassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderReference), "wgpuComputePassEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderRelease), "wgpuComputePassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetBindGroup), "wgpuComputePassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetPipeline), "wgpuComputePassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderWriteTimestamp), "wgpuComputePassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineGetBindGroupLayout), "wgpuComputePipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineReference), "wgpuComputePipelineReference" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineRelease), "wgpuComputePipelineRelease" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineSetLabel), "wgpuComputePipelineSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBindGroup), "wgpuDeviceCreateBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBindGroupLayout), "wgpuDeviceCreateBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBuffer), "wgpuDeviceCreateBuffer" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateCommandEncoder), "wgpuDeviceCreateCommandEncoder" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateComputePipeline), "wgpuDeviceCreateComputePipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateComputePipelineAsync), "wgpuDeviceCreateComputePipelineAsync" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorBuffer), "wgpuDeviceCreateErrorBuffer" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateExternalTexture), "wgpuDeviceCreateExternalTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreatePipelineLayout), "wgpuDeviceCreatePipelineLayout" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateQuerySet), "wgpuDeviceCreateQuerySet" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderBundleEncoder), "wgpuDeviceCreateRenderBundleEncoder" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderPipeline), "wgpuDeviceCreateRenderPipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderPipelineAsync), "wgpuDeviceCreateRenderPipelineAsync" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateSampler), "wgpuDeviceCreateSampler" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateShaderModule), "wgpuDeviceCreateShaderModule" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateSwapChain), "wgpuDeviceCreateSwapChain" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateTexture), "wgpuDeviceCreateTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetLimits), "wgpuDeviceGetLimits" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetQueue), "wgpuDeviceGetQueue" },
            { reinterpret_cast<WGPUProc>(NativeDeviceInjectError), "wgpuDeviceInjectError" },
            { reinterpret_cast<WGPUProc>(NativeDeviceLoseForTesting), "wgpuDeviceLoseForTesting" },
            { reinterpret_cast<WGPUProc>(NativeDevicePopErrorScope), "wgpuDevicePopErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDevicePushErrorScope), "wgpuDevicePushErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDeviceReference), "wgpuDeviceReference" },
            { reinterpret_cast<WGPUProc>(NativeDeviceRelease), "wgpuDeviceRelease" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetDeviceLostCallback), "wgpuDeviceSetDeviceLostCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetLoggingCallback), "wgpuDeviceSetLoggingCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetUncapturedErrorCallback), "wgpuDeviceSetUncapturedErrorCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceTick), "wgpuDeviceTick" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureDestroy), "wgpuExternalTextureDestroy" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureReference), "wgpuExternalTextureReference" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureRelease), "wgpuExternalTextureRelease" },
            { reinterpret_cast<WGPUProc>(NativeInstanceCreateSurface), "wgpuInstanceCreateSurface" },
            { reinterpret_cast<WGPUProc>(NativeInstanceReference), "wgpuInstanceReference" },
            { reinterpret_cast<WGPUProc>(NativeInstanceRelease), "wgpuInstanceRelease" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutReference), "wgpuPipelineLayoutReference" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutRelease), "wgpuPipelineLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetDestroy), "wgpuQuerySetDestroy" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetReference), "wgpuQuerySetReference" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetRelease), "wgpuQuerySetRelease" },
            { reinterpret_cast<WGPUProc>(NativeQueueCopyTextureForBrowser), "wgpuQueueCopyTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(NativeQueueOnSubmittedWorkDone), "wgpuQueueOnSubmittedWorkDone" },
            { reinterpret_cast<WGPUProc>(NativeQueueReference), "wgpuQueueReference" },
            { reinterpret_cast<WGPUProc>(NativeQueueRelease), "wgpuQueueRelease" },
            { reinterpret_cast<WGPUProc>(NativeQueueSubmit), "wgpuQueueSubmit" },
            { reinterpret_cast<WGPUProc>(NativeQueueWriteBuffer), "wgpuQueueWriteBuffer" },
            { reinterpret_cast<WGPUProc>(NativeQueueWriteTexture), "wgpuQueueWriteTexture" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDraw), "wgpuRenderBundleEncoderDraw" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndexed), "wgpuRenderBundleEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndexedIndirect), "wgpuRenderBundleEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndirect), "wgpuRenderBundleEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderFinish), "wgpuRenderBundleEncoderFinish" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderInsertDebugMarker), "wgpuRenderBundleEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderPopDebugGroup), "wgpuRenderBundleEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderPushDebugGroup), "wgpuRenderBundleEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderReference), "wgpuRenderBundleEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderRelease), "wgpuRenderBundleEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetBindGroup), "wgpuRenderBundleEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetIndexBuffer), "wgpuRenderBundleEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetPipeline), "wgpuRenderBundleEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetVertexBuffer), "wgpuRenderBundleEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleReference), "wgpuRenderBundleReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleRelease), "wgpuRenderBundleRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderBeginOcclusionQuery), "wgpuRenderPassEncoderBeginOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDraw), "wgpuRenderPassEncoderDraw" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexed), "wgpuRenderPassEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexedIndirect), "wgpuRenderPassEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndirect), "wgpuRenderPassEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderEndOcclusionQuery), "wgpuRenderPassEncoderEndOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderEndPass), "wgpuRenderPassEncoderEndPass" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderExecuteBundles), "wgpuRenderPassEncoderExecuteBundles" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderInsertDebugMarker), "wgpuRenderPassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPopDebugGroup), "wgpuRenderPassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPushDebugGroup), "wgpuRenderPassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderReference), "wgpuRenderPassEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderRelease), "wgpuRenderPassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBindGroup), "wgpuRenderPassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBlendConstant), "wgpuRenderPassEncoderSetBlendConstant" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetIndexBuffer), "wgpuRenderPassEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetPipeline), "wgpuRenderPassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetScissorRect), "wgpuRenderPassEncoderSetScissorRect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetStencilReference), "wgpuRenderPassEncoderSetStencilReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetVertexBuffer), "wgpuRenderPassEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetViewport), "wgpuRenderPassEncoderSetViewport" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderWriteTimestamp), "wgpuRenderPassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineGetBindGroupLayout), "wgpuRenderPipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineReference), "wgpuRenderPipelineReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineRelease), "wgpuRenderPipelineRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineSetLabel), "wgpuRenderPipelineSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeSamplerReference), "wgpuSamplerReference" },
            { reinterpret_cast<WGPUProc>(NativeSamplerRelease), "wgpuSamplerRelease" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleGetCompilationInfo), "wgpuShaderModuleGetCompilationInfo" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleReference), "wgpuShaderModuleReference" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleRelease), "wgpuShaderModuleRelease" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleSetLabel), "wgpuShaderModuleSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceReference), "wgpuSurfaceReference" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceRelease), "wgpuSurfaceRelease" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainConfigure), "wgpuSwapChainConfigure" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainGetCurrentTextureView), "wgpuSwapChainGetCurrentTextureView" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainPresent), "wgpuSwapChainPresent" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainReference), "wgpuSwapChainReference" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainRelease), "wgpuSwapChainRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureCreateView), "wgpuTextureCreateView" },
            { reinterpret_cast<WGPUProc>(NativeTextureDestroy), "wgpuTextureDestroy" },
            { reinterpret_cast<WGPUProc>(NativeTextureReference), "wgpuTextureReference" },
            { reinterpret_cast<WGPUProc>(NativeTextureRelease), "wgpuTextureRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureSetLabel), "wgpuTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewReference), "wgpuTextureViewReference" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewRelease), "wgpuTextureViewRelease" },
        };
        static constexpr size_t sProcMapSize = sizeof(sProcMap) / sizeof(sProcMap[0]);
    }

    WGPUInstance NativeCreateInstance(WGPUInstanceDescriptor const* cDescriptor) {
        const dawn_native::InstanceDescriptor* descriptor =
            reinterpret_cast<const dawn_native::InstanceDescriptor*>(cDescriptor);
        return reinterpret_cast<WGPUInstance>(InstanceBase::Create(descriptor));
    }

    WGPUProc NativeGetProcAddress(WGPUDevice, const char* procName) {
        if (procName == nullptr) {
            return nullptr;
        }

        const ProcEntry* entry = std::lower_bound(&sProcMap[0], &sProcMap[sProcMapSize], procName,
            [](const ProcEntry &a, const char *b) -> bool {
                return strcmp(a.name, b) < 0;
            }
        );

        if (entry != &sProcMap[sProcMapSize] && strcmp(entry->name, procName) == 0) {
            return entry->proc;
        }

        // Special case the two free-standing functions of the API.
        if (strcmp(procName, "wgpuGetProcAddress") == 0) {
            return reinterpret_cast<WGPUProc>(NativeGetProcAddress);
        }

        if (strcmp(procName, "wgpuCreateInstance") == 0) {
            return reinterpret_cast<WGPUProc>(NativeCreateInstance);
        }

        return nullptr;
    }

    std::vector<const char*> GetProcMapNamesForTestingInternal() {
        std::vector<const char*> result;
        result.reserve(sProcMapSize);
        for (const ProcEntry& entry : sProcMap) {
            result.push_back(entry.name);
        }
        return result;
    }

    static DawnProcTable gProcTable = {
        NativeGetProcAddress,
        NativeCreateInstance,
        NativeBindGroupReference,
        NativeBindGroupRelease,
        NativeBindGroupLayoutReference,
        NativeBindGroupLayoutRelease,
        NativeBufferDestroy,
        NativeBufferGetConstMappedRange,
        NativeBufferGetMappedRange,
        NativeBufferMapAsync,
        NativeBufferSetLabel,
        NativeBufferUnmap,
        NativeBufferReference,
        NativeBufferRelease,
        NativeCommandBufferReference,
        NativeCommandBufferRelease,
        NativeCommandEncoderBeginComputePass,
        NativeCommandEncoderBeginRenderPass,
        NativeCommandEncoderCopyBufferToBuffer,
        NativeCommandEncoderCopyBufferToTexture,
        NativeCommandEncoderCopyTextureToBuffer,
        NativeCommandEncoderCopyTextureToTexture,
        NativeCommandEncoderCopyTextureToTextureInternal,
        NativeCommandEncoderFinish,
        NativeCommandEncoderInjectValidationError,
        NativeCommandEncoderInsertDebugMarker,
        NativeCommandEncoderPopDebugGroup,
        NativeCommandEncoderPushDebugGroup,
        NativeCommandEncoderResolveQuerySet,
        NativeCommandEncoderWriteBuffer,
        NativeCommandEncoderWriteTimestamp,
        NativeCommandEncoderReference,
        NativeCommandEncoderRelease,
        NativeComputePassEncoderDispatch,
        NativeComputePassEncoderDispatchIndirect,
        NativeComputePassEncoderEndPass,
        NativeComputePassEncoderInsertDebugMarker,
        NativeComputePassEncoderPopDebugGroup,
        NativeComputePassEncoderPushDebugGroup,
        NativeComputePassEncoderSetBindGroup,
        NativeComputePassEncoderSetPipeline,
        NativeComputePassEncoderWriteTimestamp,
        NativeComputePassEncoderReference,
        NativeComputePassEncoderRelease,
        NativeComputePipelineGetBindGroupLayout,
        NativeComputePipelineSetLabel,
        NativeComputePipelineReference,
        NativeComputePipelineRelease,
        NativeDeviceCreateBindGroup,
        NativeDeviceCreateBindGroupLayout,
        NativeDeviceCreateBuffer,
        NativeDeviceCreateCommandEncoder,
        NativeDeviceCreateComputePipeline,
        NativeDeviceCreateComputePipelineAsync,
        NativeDeviceCreateErrorBuffer,
        NativeDeviceCreateExternalTexture,
        NativeDeviceCreatePipelineLayout,
        NativeDeviceCreateQuerySet,
        NativeDeviceCreateRenderBundleEncoder,
        NativeDeviceCreateRenderPipeline,
        NativeDeviceCreateRenderPipelineAsync,
        NativeDeviceCreateSampler,
        NativeDeviceCreateShaderModule,
        NativeDeviceCreateSwapChain,
        NativeDeviceCreateTexture,
        NativeDeviceGetLimits,
        NativeDeviceGetQueue,
        NativeDeviceInjectError,
        NativeDeviceLoseForTesting,
        NativeDevicePopErrorScope,
        NativeDevicePushErrorScope,
        NativeDeviceSetDeviceLostCallback,
        NativeDeviceSetLoggingCallback,
        NativeDeviceSetUncapturedErrorCallback,
        NativeDeviceTick,
        NativeDeviceReference,
        NativeDeviceRelease,
        NativeExternalTextureDestroy,
        NativeExternalTextureReference,
        NativeExternalTextureRelease,
        NativeInstanceCreateSurface,
        NativeInstanceReference,
        NativeInstanceRelease,
        NativePipelineLayoutReference,
        NativePipelineLayoutRelease,
        NativeQuerySetDestroy,
        NativeQuerySetReference,
        NativeQuerySetRelease,
        NativeQueueCopyTextureForBrowser,
        NativeQueueOnSubmittedWorkDone,
        NativeQueueSubmit,
        NativeQueueWriteBuffer,
        NativeQueueWriteTexture,
        NativeQueueReference,
        NativeQueueRelease,
        NativeRenderBundleReference,
        NativeRenderBundleRelease,
        NativeRenderBundleEncoderDraw,
        NativeRenderBundleEncoderDrawIndexed,
        NativeRenderBundleEncoderDrawIndexedIndirect,
        NativeRenderBundleEncoderDrawIndirect,
        NativeRenderBundleEncoderFinish,
        NativeRenderBundleEncoderInsertDebugMarker,
        NativeRenderBundleEncoderPopDebugGroup,
        NativeRenderBundleEncoderPushDebugGroup,
        NativeRenderBundleEncoderSetBindGroup,
        NativeRenderBundleEncoderSetIndexBuffer,
        NativeRenderBundleEncoderSetPipeline,
        NativeRenderBundleEncoderSetVertexBuffer,
        NativeRenderBundleEncoderReference,
        NativeRenderBundleEncoderRelease,
        NativeRenderPassEncoderBeginOcclusionQuery,
        NativeRenderPassEncoderDraw,
        NativeRenderPassEncoderDrawIndexed,
        NativeRenderPassEncoderDrawIndexedIndirect,
        NativeRenderPassEncoderDrawIndirect,
        NativeRenderPassEncoderEndOcclusionQuery,
        NativeRenderPassEncoderEndPass,
        NativeRenderPassEncoderExecuteBundles,
        NativeRenderPassEncoderInsertDebugMarker,
        NativeRenderPassEncoderPopDebugGroup,
        NativeRenderPassEncoderPushDebugGroup,
        NativeRenderPassEncoderSetBindGroup,
        NativeRenderPassEncoderSetBlendConstant,
        NativeRenderPassEncoderSetIndexBuffer,
        NativeRenderPassEncoderSetPipeline,
        NativeRenderPassEncoderSetScissorRect,
        NativeRenderPassEncoderSetStencilReference,
        NativeRenderPassEncoderSetVertexBuffer,
        NativeRenderPassEncoderSetViewport,
        NativeRenderPassEncoderWriteTimestamp,
        NativeRenderPassEncoderReference,
        NativeRenderPassEncoderRelease,
        NativeRenderPipelineGetBindGroupLayout,
        NativeRenderPipelineSetLabel,
        NativeRenderPipelineReference,
        NativeRenderPipelineRelease,
        NativeSamplerReference,
        NativeSamplerRelease,
        NativeShaderModuleGetCompilationInfo,
        NativeShaderModuleSetLabel,
        NativeShaderModuleReference,
        NativeShaderModuleRelease,
        NativeSurfaceReference,
        NativeSurfaceRelease,
        NativeSwapChainConfigure,
        NativeSwapChainGetCurrentTextureView,
        NativeSwapChainPresent,
        NativeSwapChainReference,
        NativeSwapChainRelease,
        NativeTextureCreateView,
        NativeTextureDestroy,
        NativeTextureSetLabel,
        NativeTextureReference,
        NativeTextureRelease,
        NativeTextureViewReference,
        NativeTextureViewRelease,
    };

    const DawnProcTable& GetProcsAutogen() {
        return gProcTable;
    }
}
