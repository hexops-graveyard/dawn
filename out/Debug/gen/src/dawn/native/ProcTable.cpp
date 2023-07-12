
#include "dawn/native/dawn_platform.h"
#include "dawn/native/DawnNative.h"

#include <algorithm>
#include <vector>

#include "dawn/native/Adapter.h"
#include "dawn/native/BindGroup.h"
#include "dawn/native/BindGroupLayout.h"
#include "dawn/native/Buffer.h"
#include "dawn/native/CommandBuffer.h"
#include "dawn/native/CommandEncoder.h"
#include "dawn/native/ComputePassEncoder.h"
#include "dawn/native/ComputePipeline.h"
#include "dawn/native/Device.h"
#include "dawn/native/ExternalTexture.h"
#include "dawn/native/Instance.h"
#include "dawn/native/PipelineLayout.h"
#include "dawn/native/QuerySet.h"
#include "dawn/native/Queue.h"
#include "dawn/native/RenderBundle.h"
#include "dawn/native/RenderBundleEncoder.h"
#include "dawn/native/RenderPassEncoder.h"
#include "dawn/native/RenderPipeline.h"
#include "dawn/native/Sampler.h"
#include "dawn/native/ShaderModule.h"
#include "dawn/native/Surface.h"
#include "dawn/native/SwapChain.h"
#include "dawn/native/Texture.h"

namespace dawn::native {


    WGPUDevice NativeAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<DeviceDescriptor const * >(descriptor);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APICreateDevice(descriptor_);
        return ToAPI(result);
    }

    size_t NativeAdapterEnumerateFeatures(WGPUAdapter cSelf, WGPUFeatureName * features) {
        auto self = FromAPI(cSelf);

        auto features_ = reinterpret_cast<wgpu::FeatureName * >(features);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIEnumerateFeatures(features_);
        return result;
    }

    WGPUInstance NativeAdapterGetInstance(WGPUAdapter cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIGetInstance();
        return ToAPI(result);
    }

    bool NativeAdapterGetLimits(WGPUAdapter cSelf, WGPUSupportedLimits * limits) {
        auto self = FromAPI(cSelf);

        auto limits_ = reinterpret_cast<SupportedLimits * >(limits);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIGetLimits(limits_);
        return result;
    }

    void NativeAdapterGetProperties(WGPUAdapter cSelf, WGPUAdapterProperties * properties) {
        auto self = FromAPI(cSelf);

        auto properties_ = reinterpret_cast<AdapterProperties * >(properties);
        // This method is specified to not use AutoLock in json script.

        self->APIGetProperties(properties_);
    }

    bool NativeAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature) {
        auto self = FromAPI(cSelf);

        auto feature_ = static_cast<wgpu::FeatureName>(feature);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIHasFeature(feature_);
        return result;
    }

    void NativeAdapterRequestDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<DeviceDescriptor const * >(descriptor);
        auto callback_ = callback;
        auto userdata_ = userdata;
        // This method is specified to not use AutoLock in json script.

        self->APIRequestDevice(descriptor_, callback_, userdata_);
    }

    void NativeAdapterReference(WGPUAdapter cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeAdapterRelease(WGPUAdapter cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeBindGroupSetLabel(WGPUBindGroup cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeBindGroupReference(WGPUBindGroup cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeBindGroupRelease(WGPUBindGroup cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeBindGroupLayoutReference(WGPUBindGroupLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeBindGroupLayoutRelease(WGPUBindGroupLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeBufferDestroy(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIDestroy();
    }

    void const * NativeBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto size_ = size;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetConstMappedRange(offset_, size_);
        return result;
    }

    WGPUBufferMapState NativeBufferGetMapState(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetMapState();
        return ToAPI(result);
    }

    void * NativeBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto size_ = size;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetMappedRange(offset_, size_);
        return result;
    }

    uint64_t NativeBufferGetSize(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetSize();
        return result;
    }

    WGPUBufferUsageFlags NativeBufferGetUsage(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetUsage();
        return ToAPI(result);
    }

    void NativeBufferMapAsync(WGPUBuffer cSelf, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto mode_ = static_cast<wgpu::MapMode>(mode);
        auto offset_ = offset;
        auto size_ = size;
        auto callback_ = callback;
        auto userdata_ = userdata;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIMapAsync(mode_, offset_, size_, callback_, userdata_);
    }

    void NativeBufferSetLabel(WGPUBuffer cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeBufferUnmap(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIUnmap();
    }

    void NativeBufferReference(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeBufferRelease(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeCommandBufferSetLabel(WGPUCommandBuffer cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeCommandBufferReference(WGPUCommandBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeCommandBufferRelease(WGPUCommandBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUComputePassEncoder NativeCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ComputePassDescriptor const * >(descriptor);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIBeginComputePass(descriptor_);
        return ToAPI(result);
    }

    WGPURenderPassEncoder NativeCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderPassDescriptor const * >(descriptor);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIBeginRenderPass(descriptor_);
        return ToAPI(result);
    }

    void NativeCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script.

        self->APIClearBuffer(buffer_, offset_, size_);
    }

    void NativeCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<BufferBase* >(source);
        auto sourceOffset_ = sourceOffset;
        auto destination_ = reinterpret_cast<BufferBase* >(destination);
        auto destinationOffset_ = destinationOffset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script.

        self->APICopyBufferToBuffer(source_, sourceOffset_, destination_, destinationOffset_, size_);
    }

    void NativeCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<ImageCopyBuffer const * >(source);
        auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
        auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
        // This method is specified to not use AutoLock in json script.

        self->APICopyBufferToTexture(source_, destination_, copySize_);
    }

    void NativeCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
        auto destination_ = reinterpret_cast<ImageCopyBuffer const * >(destination);
        auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
        // This method is specified to not use AutoLock in json script.

        self->APICopyTextureToBuffer(source_, destination_, copySize_);
    }

    void NativeCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
        auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
        auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
        // This method is specified to not use AutoLock in json script.

        self->APICopyTextureToTexture(source_, destination_, copySize_);
    }

    void NativeCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
        auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
        auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
        // This method is specified to not use AutoLock in json script.

        self->APICopyTextureToTextureInternal(source_, destination_, copySize_);
    }

    WGPUCommandBuffer NativeCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<CommandBufferDescriptor const * >(descriptor);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIFinish(descriptor_);
        return ToAPI(result);
    }

    void NativeCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, char const * message) {
        auto self = FromAPI(cSelf);

        auto message_ = reinterpret_cast<char const * >(message);
        // This method is specified to not use AutoLock in json script.

        self->APIInjectValidationError(message_);
    }

    void NativeCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIPopDebugGroup();
    }

    void NativeCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
        auto firstQuery_ = firstQuery;
        auto queryCount_ = queryCount;
        auto destination_ = reinterpret_cast<BufferBase* >(destination);
        auto destinationOffset_ = destinationOffset;
        // This method is specified to not use AutoLock in json script.

        self->APIResolveQuerySet(querySet_, firstQuery_, queryCount_, destination_, destinationOffset_);
    }

    void NativeCommandEncoderSetLabel(WGPUCommandEncoder cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        // This method is specified to not use AutoLock in json script.

        self->APISetLabel(label_);
    }

    void NativeCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
        auto bufferOffset_ = bufferOffset;
        auto data_ = reinterpret_cast<uint8_t const * >(data);
        auto size_ = size;
        // This method is specified to not use AutoLock in json script.

        self->APIWriteBuffer(buffer_, bufferOffset_, data_, size_);
    }

    void NativeCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script.

        self->APIWriteTimestamp(querySet_, queryIndex_);
    }

    void NativeCommandEncoderReference(WGPUCommandEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeCommandEncoderRelease(WGPUCommandEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder cSelf, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        auto self = FromAPI(cSelf);

        auto workgroupCountX_ = workgroupCountX;
        auto workgroupCountY_ = workgroupCountY;
        auto workgroupCountZ_ = workgroupCountZ;
        // This method is specified to not use AutoLock in json script.

        self->APIDispatchWorkgroups(workgroupCountX_, workgroupCountY_, workgroupCountZ_);
    }

    void NativeComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script.

        self->APIDispatchWorkgroupsIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeComputePassEncoderEnd(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIEnd();
    }

    void NativeComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIPopDebugGroup();
    }

    void NativeComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto group_ = reinterpret_cast<BindGroupBase* >(group);
        auto dynamicOffsetCount_ = dynamicOffsetCount;
        auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
        // This method is specified to not use AutoLock in json script.

        self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
    }

    void NativeComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        // This method is specified to not use AutoLock in json script.

        self->APISetLabel(label_);
    }

    void NativeComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
        auto self = FromAPI(cSelf);

        auto pipeline_ = reinterpret_cast<ComputePipelineBase* >(pipeline);
        // This method is specified to not use AutoLock in json script.

        self->APISetPipeline(pipeline_);
    }

    void NativeComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script.

        self->APIWriteTimestamp(querySet_, queryIndex_);
    }

    void NativeComputePassEncoderReference(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeComputePassEncoderRelease(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUBindGroupLayout NativeComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetBindGroupLayout(groupIndex_);
        return ToAPI(result);
    }

    void NativeComputePipelineSetLabel(WGPUComputePipeline cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeComputePipelineReference(WGPUComputePipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeComputePipelineRelease(WGPUComputePipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUBindGroup NativeDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BindGroupDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateBindGroup(descriptor_);
        return ToAPI(result);
    }

    WGPUBindGroupLayout NativeDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BindGroupLayoutDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateBindGroupLayout(descriptor_);
        return ToAPI(result);
    }

    WGPUBuffer NativeDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BufferDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateBuffer(descriptor_);
        return ToAPI(result);
    }

    WGPUCommandEncoder NativeDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<CommandEncoderDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateCommandEncoder(descriptor_);
        return ToAPI(result);
    }

    WGPUComputePipeline NativeDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateComputePipeline(descriptor_);
        return ToAPI(result);
    }

    void NativeDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const * >(descriptor);
        auto callback_ = callback;
        auto userdata_ = userdata;
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APICreateComputePipelineAsync(descriptor_, callback_, userdata_);
    }

    WGPUBuffer NativeDeviceCreateErrorBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BufferDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateErrorBuffer(descriptor_);
        return ToAPI(result);
    }

    WGPUExternalTexture NativeDeviceCreateErrorExternalTexture(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateErrorExternalTexture();
        return ToAPI(result);
    }

    WGPUShaderModule NativeDeviceCreateErrorShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ShaderModuleDescriptor const * >(descriptor);
        auto errorMessage_ = reinterpret_cast<char const * >(errorMessage);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateErrorShaderModule(descriptor_, errorMessage_);
        return ToAPI(result);
    }

    WGPUTexture NativeDeviceCreateErrorTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateErrorTexture(descriptor_);
        return ToAPI(result);
    }

    WGPUExternalTexture NativeDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
        auto self = FromAPI(cSelf);

        auto externalTextureDescriptor_ = reinterpret_cast<ExternalTextureDescriptor const * >(externalTextureDescriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateExternalTexture(externalTextureDescriptor_);
        return ToAPI(result);
    }

    WGPUPipelineLayout NativeDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<PipelineLayoutDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreatePipelineLayout(descriptor_);
        return ToAPI(result);
    }

    WGPUQuerySet NativeDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<QuerySetDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateQuerySet(descriptor_);
        return ToAPI(result);
    }

    WGPURenderBundleEncoder NativeDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderBundleEncoderDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateRenderBundleEncoder(descriptor_);
        return ToAPI(result);
    }

    WGPURenderPipeline NativeDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateRenderPipeline(descriptor_);
        return ToAPI(result);
    }

    void NativeDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const * >(descriptor);
        auto callback_ = callback;
        auto userdata_ = userdata;
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APICreateRenderPipelineAsync(descriptor_, callback_, userdata_);
    }

    WGPUSampler NativeDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<SamplerDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateSampler(descriptor_);
        return ToAPI(result);
    }

    WGPUShaderModule NativeDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ShaderModuleDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateShaderModule(descriptor_);
        return ToAPI(result);
    }

    WGPUSwapChain NativeDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto surface_ = reinterpret_cast<SurfaceBase* >(surface);
        auto descriptor_ = reinterpret_cast<SwapChainDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateSwapChain(surface_, descriptor_);
        return ToAPI(result);
    }

    WGPUTexture NativeDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateTexture(descriptor_);
        return ToAPI(result);
    }

    void NativeDeviceDestroy(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APIDestroy();
    }

    size_t NativeDeviceEnumerateFeatures(WGPUDevice cSelf, WGPUFeatureName * features) {
        auto self = FromAPI(cSelf);

        auto features_ = reinterpret_cast<wgpu::FeatureName * >(features);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIEnumerateFeatures(features_);
        return result;
    }

    void NativeDeviceForceLoss(WGPUDevice cSelf, WGPUDeviceLostReason type, char const * message) {
        auto self = FromAPI(cSelf);

        auto type_ = static_cast<wgpu::DeviceLostReason>(type);
        auto message_ = reinterpret_cast<char const * >(message);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APIForceLoss(type_, message_);
    }

    WGPUAdapter NativeDeviceGetAdapter(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetAdapter();
        return ToAPI(result);
    }

    bool NativeDeviceGetLimits(WGPUDevice cSelf, WGPUSupportedLimits * limits) {
        auto self = FromAPI(cSelf);

        auto limits_ = reinterpret_cast<SupportedLimits * >(limits);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetLimits(limits_);
        return result;
    }

    WGPUQueue NativeDeviceGetQueue(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetQueue();
        return ToAPI(result);
    }

    WGPUTextureUsageFlags NativeDeviceGetSupportedSurfaceUsage(WGPUDevice cSelf, WGPUSurface surface) {
        auto self = FromAPI(cSelf);

        auto surface_ = reinterpret_cast<SurfaceBase* >(surface);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetSupportedSurfaceUsage(surface_);
        return ToAPI(result);
    }

    bool NativeDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature) {
        auto self = FromAPI(cSelf);

        auto feature_ = static_cast<wgpu::FeatureName>(feature);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIHasFeature(feature_);
        return result;
    }

    void NativeDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message) {
        auto self = FromAPI(cSelf);

        auto type_ = static_cast<wgpu::ErrorType>(type);
        auto message_ = reinterpret_cast<char const * >(message);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APIInjectError(type_, message_);
    }

    void NativeDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto callback_ = callback;
        auto userdata_ = userdata;
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APIPopErrorScope(callback_, userdata_);
    }

    void NativeDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
        auto self = FromAPI(cSelf);

        auto filter_ = static_cast<wgpu::ErrorFilter>(filter);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APIPushErrorScope(filter_);
    }

    void NativeDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto callback_ = callback;
        auto userdata_ = userdata;
        // This method is specified to not use AutoLock in json script.

        self->APISetDeviceLostCallback(callback_, userdata_);
    }

    void NativeDeviceSetLabel(WGPUDevice cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto callback_ = callback;
        auto userdata_ = userdata;
        // This method is specified to not use AutoLock in json script.

        self->APISetLoggingCallback(callback_, userdata_);
    }

    void NativeDeviceSetUncapturedErrorCallback(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto callback_ = callback;
        auto userdata_ = userdata;
        // This method is specified to not use AutoLock in json script.

        self->APISetUncapturedErrorCallback(callback_, userdata_);
    }

    void NativeDeviceTick(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APITick();
    }

    void NativeDeviceValidateTextureDescriptor(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureDescriptor const * >(descriptor);
        auto device = self;
        auto deviceLock(device->GetScopedLock());

        self->APIValidateTextureDescriptor(descriptor_);
    }

    void NativeDeviceReference(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeDeviceRelease(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeExternalTextureDestroy(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIDestroy();
    }

    void NativeExternalTextureExpire(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIExpire();
    }

    void NativeExternalTextureRefresh(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIRefresh();
    }

    void NativeExternalTextureSetLabel(WGPUExternalTexture cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeExternalTextureReference(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeExternalTextureRelease(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUSurface NativeInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<SurfaceDescriptor const * >(descriptor);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APICreateSurface(descriptor_);
        return ToAPI(result);
    }

    void NativeInstanceProcessEvents(WGPUInstance cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIProcessEvents();
    }

    void NativeInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto options_ = reinterpret_cast<RequestAdapterOptions const * >(options);
        auto callback_ = callback;
        auto userdata_ = userdata;
        // This method is specified to not use AutoLock in json script.

        self->APIRequestAdapter(options_, callback_, userdata_);
    }

    void NativeInstanceReference(WGPUInstance cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeInstanceRelease(WGPUInstance cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativePipelineLayoutSetLabel(WGPUPipelineLayout cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativePipelineLayoutReference(WGPUPipelineLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativePipelineLayoutRelease(WGPUPipelineLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeQuerySetDestroy(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIDestroy();
    }

    uint32_t NativeQuerySetGetCount(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetCount();
        return result;
    }

    WGPUQueryType NativeQuerySetGetType(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetType();
        return ToAPI(result);
    }

    void NativeQuerySetSetLabel(WGPUQuerySet cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeQuerySetReference(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeQuerySetRelease(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeQueueCopyExternalTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<ImageCopyExternalTexture const * >(source);
        auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
        auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
        auto options_ = reinterpret_cast<CopyTextureForBrowserOptions const * >(options);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APICopyExternalTextureForBrowser(source_, destination_, copySize_, options_);
    }

    void NativeQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<ImageCopyTexture const * >(source);
        auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
        auto copySize_ = reinterpret_cast<Extent3D const * >(copySize);
        auto options_ = reinterpret_cast<CopyTextureForBrowserOptions const * >(options);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APICopyTextureForBrowser(source_, destination_, copySize_, options_);
    }

    void NativeQueueOnSubmittedWorkDone(WGPUQueue cSelf, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto signalValue_ = signalValue;
        auto callback_ = callback;
        auto userdata_ = userdata;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIOnSubmittedWorkDone(signalValue_, callback_, userdata_);
    }

    void NativeQueueSetLabel(WGPUQueue cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeQueueSubmit(WGPUQueue cSelf, size_t commandCount, WGPUCommandBuffer const * commands) {
        auto self = FromAPI(cSelf);

        auto commandCount_ = commandCount;
        auto commands_ = reinterpret_cast<CommandBufferBase* const * >(commands);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISubmit(commandCount_, commands_);
    }

    void NativeQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
        auto bufferOffset_ = bufferOffset;
        auto data_ = reinterpret_cast<void const * >(data);
        auto size_ = size;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIWriteBuffer(buffer_, bufferOffset_, data_, size_);
    }

    void NativeQueueWriteTexture(WGPUQueue cSelf, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        auto self = FromAPI(cSelf);

        auto destination_ = reinterpret_cast<ImageCopyTexture const * >(destination);
        auto data_ = reinterpret_cast<void const * >(data);
        auto dataSize_ = dataSize;
        auto dataLayout_ = reinterpret_cast<TextureDataLayout const * >(dataLayout);
        auto writeSize_ = reinterpret_cast<Extent3D const * >(writeSize);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIWriteTexture(destination_, data_, dataSize_, dataLayout_, writeSize_);
    }

    void NativeQueueReference(WGPUQueue cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeQueueRelease(WGPUQueue cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeRenderBundleSetLabel(WGPURenderBundle cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeRenderBundleReference(WGPURenderBundle cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeRenderBundleRelease(WGPURenderBundle cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto vertexCount_ = vertexCount;
        auto instanceCount_ = instanceCount;
        auto firstVertex_ = firstVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script.

        self->APIDraw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
    }

    void NativeRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto indexCount_ = indexCount;
        auto instanceCount_ = instanceCount;
        auto firstIndex_ = firstIndex;
        auto baseVertex_ = baseVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script.

        self->APIDrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
    }

    void NativeRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script.

        self->APIDrawIndexedIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script.

        self->APIDrawIndirect(indirectBuffer_, indirectOffset_);
    }

    WGPURenderBundle NativeRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderBundleDescriptor const * >(descriptor);
        // This method is specified to not use AutoLock in json script.

        auto result =        self->APIFinish(descriptor_);
        return ToAPI(result);
    }

    void NativeRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIPopDebugGroup();
    }

    void NativeRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto group_ = reinterpret_cast<BindGroupBase* >(group);
        auto dynamicOffsetCount_ = dynamicOffsetCount;
        auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
        // This method is specified to not use AutoLock in json script.

        self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
    }

    void NativeRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
        auto format_ = static_cast<wgpu::IndexFormat>(format);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script.

        self->APISetIndexBuffer(buffer_, format_, offset_, size_);
    }

    void NativeRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        // This method is specified to not use AutoLock in json script.

        self->APISetLabel(label_);
    }

    void NativeRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = FromAPI(cSelf);

        auto pipeline_ = reinterpret_cast<RenderPipelineBase* >(pipeline);
        // This method is specified to not use AutoLock in json script.

        self->APISetPipeline(pipeline_);
    }

    void NativeRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto slot_ = slot;
        auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script.

        self->APISetVertexBuffer(slot_, buffer_, offset_, size_);
    }

    void NativeRenderBundleEncoderReference(WGPURenderBundleEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script.

        self->APIBeginOcclusionQuery(queryIndex_);
    }

    void NativeRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto vertexCount_ = vertexCount;
        auto instanceCount_ = instanceCount;
        auto firstVertex_ = firstVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script.

        self->APIDraw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
    }

    void NativeRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto indexCount_ = indexCount;
        auto instanceCount_ = instanceCount;
        auto firstIndex_ = firstIndex;
        auto baseVertex_ = baseVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script.

        self->APIDrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
    }

    void NativeRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script.

        self->APIDrawIndexedIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase* >(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script.

        self->APIDrawIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeRenderPassEncoderEnd(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIEnd();
    }

    void NativeRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIEndOcclusionQuery();
    }

    void NativeRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, size_t bundleCount, WGPURenderBundle const * bundles) {
        auto self = FromAPI(cSelf);

        auto bundleCount_ = bundleCount;
        auto bundles_ = reinterpret_cast<RenderBundleBase* const * >(bundles);
        // This method is specified to not use AutoLock in json script.

        self->APIExecuteBundles(bundleCount_, bundles_);
    }

    void NativeRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = reinterpret_cast<char const * >(markerLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIPopDebugGroup();
    }

    void NativeRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = reinterpret_cast<char const * >(groupLabel);
        // This method is specified to not use AutoLock in json script.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto group_ = reinterpret_cast<BindGroupBase* >(group);
        auto dynamicOffsetCount_ = dynamicOffsetCount;
        auto dynamicOffsets_ = reinterpret_cast<uint32_t const * >(dynamicOffsets);
        // This method is specified to not use AutoLock in json script.

        self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
    }

    void NativeRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
        auto self = FromAPI(cSelf);

        auto color_ = reinterpret_cast<Color const * >(color);
        // This method is specified to not use AutoLock in json script.

        self->APISetBlendConstant(color_);
    }

    void NativeRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
        auto format_ = static_cast<wgpu::IndexFormat>(format);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script.

        self->APISetIndexBuffer(buffer_, format_, offset_, size_);
    }

    void NativeRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        // This method is specified to not use AutoLock in json script.

        self->APISetLabel(label_);
    }

    void NativeRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = FromAPI(cSelf);

        auto pipeline_ = reinterpret_cast<RenderPipelineBase* >(pipeline);
        // This method is specified to not use AutoLock in json script.

        self->APISetPipeline(pipeline_);
    }

    void NativeRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        auto self = FromAPI(cSelf);

        auto x_ = x;
        auto y_ = y;
        auto width_ = width;
        auto height_ = height;
        // This method is specified to not use AutoLock in json script.

        self->APISetScissorRect(x_, y_, width_, height_);
    }

    void NativeRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
        auto self = FromAPI(cSelf);

        auto reference_ = reference;
        // This method is specified to not use AutoLock in json script.

        self->APISetStencilReference(reference_);
    }

    void NativeRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto slot_ = slot;
        auto buffer_ = reinterpret_cast<BufferBase* >(buffer);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script.

        self->APISetVertexBuffer(slot_, buffer_, offset_, size_);
    }

    void NativeRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
        auto self = FromAPI(cSelf);

        auto x_ = x;
        auto y_ = y;
        auto width_ = width;
        auto height_ = height;
        auto minDepth_ = minDepth;
        auto maxDepth_ = maxDepth;
        // This method is specified to not use AutoLock in json script.

        self->APISetViewport(x_, y_, width_, height_, minDepth_, maxDepth_);
    }

    void NativeRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase* >(querySet);
        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script.

        self->APIWriteTimestamp(querySet_, queryIndex_);
    }

    void NativeRenderPassEncoderReference(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeRenderPassEncoderRelease(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUBindGroupLayout NativeRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetBindGroupLayout(groupIndex_);
        return ToAPI(result);
    }

    void NativeRenderPipelineSetLabel(WGPURenderPipeline cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeRenderPipelineReference(WGPURenderPipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeRenderPipelineRelease(WGPURenderPipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeSamplerSetLabel(WGPUSampler cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeSamplerReference(WGPUSampler cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeSamplerRelease(WGPUSampler cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallback callback, void * userdata) {
        auto self = FromAPI(cSelf);

        auto callback_ = callback;
        auto userdata_ = userdata;
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIGetCompilationInfo(callback_, userdata_);
    }

    void NativeShaderModuleSetLabel(WGPUShaderModule cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeShaderModuleReference(WGPUShaderModule cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeShaderModuleRelease(WGPUShaderModule cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeSurfaceReference(WGPUSurface cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeSurfaceRelease(WGPUSurface cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUTexture NativeSwapChainGetCurrentTexture(WGPUSwapChain cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetCurrentTexture();
        return ToAPI(result);
    }

    WGPUTextureView NativeSwapChainGetCurrentTextureView(WGPUSwapChain cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetCurrentTextureView();
        return ToAPI(result);
    }

    void NativeSwapChainPresent(WGPUSwapChain cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIPresent();
    }

    void NativeSwapChainReference(WGPUSwapChain cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeSwapChainRelease(WGPUSwapChain cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUTextureView NativeTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureViewDescriptor const * >(descriptor);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APICreateView(descriptor_);
        return ToAPI(result);
    }

    void NativeTextureDestroy(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APIDestroy();
    }

    uint32_t NativeTextureGetDepthOrArrayLayers(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetDepthOrArrayLayers();
        return result;
    }

    WGPUTextureDimension NativeTextureGetDimension(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetDimension();
        return ToAPI(result);
    }

    WGPUTextureFormat NativeTextureGetFormat(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetFormat();
        return ToAPI(result);
    }

    uint32_t NativeTextureGetHeight(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetHeight();
        return result;
    }

    uint32_t NativeTextureGetMipLevelCount(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetMipLevelCount();
        return result;
    }

    uint32_t NativeTextureGetSampleCount(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetSampleCount();
        return result;
    }

    WGPUTextureUsageFlags NativeTextureGetUsage(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetUsage();
        return ToAPI(result);
    }

    uint32_t NativeTextureGetWidth(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        auto result =        self->APIGetWidth();
        return result;
    }

    void NativeTextureSetLabel(WGPUTexture cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeTextureReference(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeTextureRelease(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    void NativeTextureViewSetLabel(WGPUTextureView cSelf, char const * label) {
        auto self = FromAPI(cSelf);

        auto label_ = reinterpret_cast<char const * >(label);
        auto device = self->GetDevice();
        auto deviceLock(device->GetScopedLock());

        self->APISetLabel(label_);
    }

    void NativeTextureViewReference(WGPUTextureView cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIReference();
    }

    void NativeTextureViewRelease(WGPUTextureView cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script.

        self->APIRelease();
    }

    WGPUInstance NativeCreateInstance(WGPUInstanceDescriptor const * descriptor) {
        auto descriptor_ = reinterpret_cast<InstanceDescriptor const * >(descriptor);
        auto result =        APICreateInstance(descriptor_);
        return ToAPI(result);
    }

    namespace {

        struct ProcEntry {
            WGPUProc proc;
            const char* name;
        };
        static const ProcEntry sProcMap[] = {
            { reinterpret_cast<WGPUProc>(NativeAdapterCreateDevice), "wgpuAdapterCreateDevice" },
            { reinterpret_cast<WGPUProc>(NativeAdapterEnumerateFeatures), "wgpuAdapterEnumerateFeatures" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetInstance), "wgpuAdapterGetInstance" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetLimits), "wgpuAdapterGetLimits" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetProperties), "wgpuAdapterGetProperties" },
            { reinterpret_cast<WGPUProc>(NativeAdapterHasFeature), "wgpuAdapterHasFeature" },
            { reinterpret_cast<WGPUProc>(NativeAdapterReference), "wgpuAdapterReference" },
            { reinterpret_cast<WGPUProc>(NativeAdapterRelease), "wgpuAdapterRelease" },
            { reinterpret_cast<WGPUProc>(NativeAdapterRequestDevice), "wgpuAdapterRequestDevice" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutReference), "wgpuBindGroupLayoutReference" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutRelease), "wgpuBindGroupLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutSetLabel), "wgpuBindGroupLayoutSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupReference), "wgpuBindGroupReference" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupRelease), "wgpuBindGroupRelease" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupSetLabel), "wgpuBindGroupSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeBufferDestroy), "wgpuBufferDestroy" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetConstMappedRange), "wgpuBufferGetConstMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetMapState), "wgpuBufferGetMapState" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetMappedRange), "wgpuBufferGetMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetSize), "wgpuBufferGetSize" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetUsage), "wgpuBufferGetUsage" },
            { reinterpret_cast<WGPUProc>(NativeBufferMapAsync), "wgpuBufferMapAsync" },
            { reinterpret_cast<WGPUProc>(NativeBufferReference), "wgpuBufferReference" },
            { reinterpret_cast<WGPUProc>(NativeBufferRelease), "wgpuBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeBufferSetLabel), "wgpuBufferSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeBufferUnmap), "wgpuBufferUnmap" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferReference), "wgpuCommandBufferReference" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferRelease), "wgpuCommandBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferSetLabel), "wgpuCommandBufferSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginComputePass), "wgpuCommandEncoderBeginComputePass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginRenderPass), "wgpuCommandEncoderBeginRenderPass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderClearBuffer), "wgpuCommandEncoderClearBuffer" },
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
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderSetLabel), "wgpuCommandEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderWriteBuffer), "wgpuCommandEncoderWriteBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderWriteTimestamp), "wgpuCommandEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatchWorkgroups), "wgpuComputePassEncoderDispatchWorkgroups" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatchWorkgroupsIndirect), "wgpuComputePassEncoderDispatchWorkgroupsIndirect" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderEnd), "wgpuComputePassEncoderEnd" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderInsertDebugMarker), "wgpuComputePassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPopDebugGroup), "wgpuComputePassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPushDebugGroup), "wgpuComputePassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderReference), "wgpuComputePassEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderRelease), "wgpuComputePassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetBindGroup), "wgpuComputePassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetLabel), "wgpuComputePassEncoderSetLabel" },
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
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorExternalTexture), "wgpuDeviceCreateErrorExternalTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorShaderModule), "wgpuDeviceCreateErrorShaderModule" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorTexture), "wgpuDeviceCreateErrorTexture" },
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
            { reinterpret_cast<WGPUProc>(NativeDeviceDestroy), "wgpuDeviceDestroy" },
            { reinterpret_cast<WGPUProc>(NativeDeviceEnumerateFeatures), "wgpuDeviceEnumerateFeatures" },
            { reinterpret_cast<WGPUProc>(NativeDeviceForceLoss), "wgpuDeviceForceLoss" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetAdapter), "wgpuDeviceGetAdapter" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetLimits), "wgpuDeviceGetLimits" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetQueue), "wgpuDeviceGetQueue" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetSupportedSurfaceUsage), "wgpuDeviceGetSupportedSurfaceUsage" },
            { reinterpret_cast<WGPUProc>(NativeDeviceHasFeature), "wgpuDeviceHasFeature" },
            { reinterpret_cast<WGPUProc>(NativeDeviceInjectError), "wgpuDeviceInjectError" },
            { reinterpret_cast<WGPUProc>(NativeDevicePopErrorScope), "wgpuDevicePopErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDevicePushErrorScope), "wgpuDevicePushErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDeviceReference), "wgpuDeviceReference" },
            { reinterpret_cast<WGPUProc>(NativeDeviceRelease), "wgpuDeviceRelease" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetDeviceLostCallback), "wgpuDeviceSetDeviceLostCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetLabel), "wgpuDeviceSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetLoggingCallback), "wgpuDeviceSetLoggingCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetUncapturedErrorCallback), "wgpuDeviceSetUncapturedErrorCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceTick), "wgpuDeviceTick" },
            { reinterpret_cast<WGPUProc>(NativeDeviceValidateTextureDescriptor), "wgpuDeviceValidateTextureDescriptor" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureDestroy), "wgpuExternalTextureDestroy" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureExpire), "wgpuExternalTextureExpire" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureReference), "wgpuExternalTextureReference" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureRefresh), "wgpuExternalTextureRefresh" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureRelease), "wgpuExternalTextureRelease" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureSetLabel), "wgpuExternalTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeInstanceCreateSurface), "wgpuInstanceCreateSurface" },
            { reinterpret_cast<WGPUProc>(NativeInstanceProcessEvents), "wgpuInstanceProcessEvents" },
            { reinterpret_cast<WGPUProc>(NativeInstanceReference), "wgpuInstanceReference" },
            { reinterpret_cast<WGPUProc>(NativeInstanceRelease), "wgpuInstanceRelease" },
            { reinterpret_cast<WGPUProc>(NativeInstanceRequestAdapter), "wgpuInstanceRequestAdapter" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutReference), "wgpuPipelineLayoutReference" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutRelease), "wgpuPipelineLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutSetLabel), "wgpuPipelineLayoutSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetDestroy), "wgpuQuerySetDestroy" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetGetCount), "wgpuQuerySetGetCount" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetGetType), "wgpuQuerySetGetType" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetReference), "wgpuQuerySetReference" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetRelease), "wgpuQuerySetRelease" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetSetLabel), "wgpuQuerySetSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeQueueCopyExternalTextureForBrowser), "wgpuQueueCopyExternalTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(NativeQueueCopyTextureForBrowser), "wgpuQueueCopyTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(NativeQueueOnSubmittedWorkDone), "wgpuQueueOnSubmittedWorkDone" },
            { reinterpret_cast<WGPUProc>(NativeQueueReference), "wgpuQueueReference" },
            { reinterpret_cast<WGPUProc>(NativeQueueRelease), "wgpuQueueRelease" },
            { reinterpret_cast<WGPUProc>(NativeQueueSetLabel), "wgpuQueueSetLabel" },
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
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetLabel), "wgpuRenderBundleEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetPipeline), "wgpuRenderBundleEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetVertexBuffer), "wgpuRenderBundleEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleReference), "wgpuRenderBundleReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleRelease), "wgpuRenderBundleRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleSetLabel), "wgpuRenderBundleSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderBeginOcclusionQuery), "wgpuRenderPassEncoderBeginOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDraw), "wgpuRenderPassEncoderDraw" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexed), "wgpuRenderPassEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexedIndirect), "wgpuRenderPassEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndirect), "wgpuRenderPassEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderEnd), "wgpuRenderPassEncoderEnd" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderEndOcclusionQuery), "wgpuRenderPassEncoderEndOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderExecuteBundles), "wgpuRenderPassEncoderExecuteBundles" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderInsertDebugMarker), "wgpuRenderPassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPopDebugGroup), "wgpuRenderPassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPushDebugGroup), "wgpuRenderPassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderReference), "wgpuRenderPassEncoderReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderRelease), "wgpuRenderPassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBindGroup), "wgpuRenderPassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBlendConstant), "wgpuRenderPassEncoderSetBlendConstant" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetIndexBuffer), "wgpuRenderPassEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetLabel), "wgpuRenderPassEncoderSetLabel" },
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
            { reinterpret_cast<WGPUProc>(NativeSamplerSetLabel), "wgpuSamplerSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleGetCompilationInfo), "wgpuShaderModuleGetCompilationInfo" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleReference), "wgpuShaderModuleReference" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleRelease), "wgpuShaderModuleRelease" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleSetLabel), "wgpuShaderModuleSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceReference), "wgpuSurfaceReference" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceRelease), "wgpuSurfaceRelease" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainGetCurrentTexture), "wgpuSwapChainGetCurrentTexture" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainGetCurrentTextureView), "wgpuSwapChainGetCurrentTextureView" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainPresent), "wgpuSwapChainPresent" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainReference), "wgpuSwapChainReference" },
            { reinterpret_cast<WGPUProc>(NativeSwapChainRelease), "wgpuSwapChainRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureCreateView), "wgpuTextureCreateView" },
            { reinterpret_cast<WGPUProc>(NativeTextureDestroy), "wgpuTextureDestroy" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetDepthOrArrayLayers), "wgpuTextureGetDepthOrArrayLayers" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetDimension), "wgpuTextureGetDimension" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetFormat), "wgpuTextureGetFormat" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetHeight), "wgpuTextureGetHeight" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetMipLevelCount), "wgpuTextureGetMipLevelCount" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetSampleCount), "wgpuTextureGetSampleCount" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetUsage), "wgpuTextureGetUsage" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetWidth), "wgpuTextureGetWidth" },
            { reinterpret_cast<WGPUProc>(NativeTextureReference), "wgpuTextureReference" },
            { reinterpret_cast<WGPUProc>(NativeTextureRelease), "wgpuTextureRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureSetLabel), "wgpuTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewReference), "wgpuTextureViewReference" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewRelease), "wgpuTextureViewRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewSetLabel), "wgpuTextureViewSetLabel" },
        };
        static constexpr size_t sProcMapSize = sizeof(sProcMap) / sizeof(sProcMap[0]);

    }  // anonymous namespace

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

        // Special case the free-standing functions of the API.
        // TODO(dawn:1238) Checking string one by one is slow, it needs to be optimized.
        if (strcmp(procName, "wgpuCreateInstance") == 0) {
            return reinterpret_cast<WGPUProc>(NativeCreateInstance);
        }

        if (strcmp(procName, "wgpuGetProcAddress") == 0) {
            return reinterpret_cast<WGPUProc>(NativeGetProcAddress);
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
        NativeCreateInstance,
        NativeGetProcAddress,
        NativeAdapterCreateDevice,
        NativeAdapterEnumerateFeatures,
        NativeAdapterGetInstance,
        NativeAdapterGetLimits,
        NativeAdapterGetProperties,
        NativeAdapterHasFeature,
        NativeAdapterRequestDevice,
        NativeAdapterReference,
        NativeAdapterRelease,
        NativeBindGroupSetLabel,
        NativeBindGroupReference,
        NativeBindGroupRelease,
        NativeBindGroupLayoutSetLabel,
        NativeBindGroupLayoutReference,
        NativeBindGroupLayoutRelease,
        NativeBufferDestroy,
        NativeBufferGetConstMappedRange,
        NativeBufferGetMapState,
        NativeBufferGetMappedRange,
        NativeBufferGetSize,
        NativeBufferGetUsage,
        NativeBufferMapAsync,
        NativeBufferSetLabel,
        NativeBufferUnmap,
        NativeBufferReference,
        NativeBufferRelease,
        NativeCommandBufferSetLabel,
        NativeCommandBufferReference,
        NativeCommandBufferRelease,
        NativeCommandEncoderBeginComputePass,
        NativeCommandEncoderBeginRenderPass,
        NativeCommandEncoderClearBuffer,
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
        NativeCommandEncoderSetLabel,
        NativeCommandEncoderWriteBuffer,
        NativeCommandEncoderWriteTimestamp,
        NativeCommandEncoderReference,
        NativeCommandEncoderRelease,
        NativeComputePassEncoderDispatchWorkgroups,
        NativeComputePassEncoderDispatchWorkgroupsIndirect,
        NativeComputePassEncoderEnd,
        NativeComputePassEncoderInsertDebugMarker,
        NativeComputePassEncoderPopDebugGroup,
        NativeComputePassEncoderPushDebugGroup,
        NativeComputePassEncoderSetBindGroup,
        NativeComputePassEncoderSetLabel,
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
        NativeDeviceCreateErrorExternalTexture,
        NativeDeviceCreateErrorShaderModule,
        NativeDeviceCreateErrorTexture,
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
        NativeDeviceDestroy,
        NativeDeviceEnumerateFeatures,
        NativeDeviceForceLoss,
        NativeDeviceGetAdapter,
        NativeDeviceGetLimits,
        NativeDeviceGetQueue,
        NativeDeviceGetSupportedSurfaceUsage,
        NativeDeviceHasFeature,
        NativeDeviceInjectError,
        NativeDevicePopErrorScope,
        NativeDevicePushErrorScope,
        NativeDeviceSetDeviceLostCallback,
        NativeDeviceSetLabel,
        NativeDeviceSetLoggingCallback,
        NativeDeviceSetUncapturedErrorCallback,
        NativeDeviceTick,
        NativeDeviceValidateTextureDescriptor,
        NativeDeviceReference,
        NativeDeviceRelease,
        NativeExternalTextureDestroy,
        NativeExternalTextureExpire,
        NativeExternalTextureRefresh,
        NativeExternalTextureSetLabel,
        NativeExternalTextureReference,
        NativeExternalTextureRelease,
        NativeInstanceCreateSurface,
        NativeInstanceProcessEvents,
        NativeInstanceRequestAdapter,
        NativeInstanceReference,
        NativeInstanceRelease,
        NativePipelineLayoutSetLabel,
        NativePipelineLayoutReference,
        NativePipelineLayoutRelease,
        NativeQuerySetDestroy,
        NativeQuerySetGetCount,
        NativeQuerySetGetType,
        NativeQuerySetSetLabel,
        NativeQuerySetReference,
        NativeQuerySetRelease,
        NativeQueueCopyExternalTextureForBrowser,
        NativeQueueCopyTextureForBrowser,
        NativeQueueOnSubmittedWorkDone,
        NativeQueueSetLabel,
        NativeQueueSubmit,
        NativeQueueWriteBuffer,
        NativeQueueWriteTexture,
        NativeQueueReference,
        NativeQueueRelease,
        NativeRenderBundleSetLabel,
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
        NativeRenderBundleEncoderSetLabel,
        NativeRenderBundleEncoderSetPipeline,
        NativeRenderBundleEncoderSetVertexBuffer,
        NativeRenderBundleEncoderReference,
        NativeRenderBundleEncoderRelease,
        NativeRenderPassEncoderBeginOcclusionQuery,
        NativeRenderPassEncoderDraw,
        NativeRenderPassEncoderDrawIndexed,
        NativeRenderPassEncoderDrawIndexedIndirect,
        NativeRenderPassEncoderDrawIndirect,
        NativeRenderPassEncoderEnd,
        NativeRenderPassEncoderEndOcclusionQuery,
        NativeRenderPassEncoderExecuteBundles,
        NativeRenderPassEncoderInsertDebugMarker,
        NativeRenderPassEncoderPopDebugGroup,
        NativeRenderPassEncoderPushDebugGroup,
        NativeRenderPassEncoderSetBindGroup,
        NativeRenderPassEncoderSetBlendConstant,
        NativeRenderPassEncoderSetIndexBuffer,
        NativeRenderPassEncoderSetLabel,
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
        NativeSamplerSetLabel,
        NativeSamplerReference,
        NativeSamplerRelease,
        NativeShaderModuleGetCompilationInfo,
        NativeShaderModuleSetLabel,
        NativeShaderModuleReference,
        NativeShaderModuleRelease,
        NativeSurfaceReference,
        NativeSurfaceRelease,
        NativeSwapChainGetCurrentTexture,
        NativeSwapChainGetCurrentTextureView,
        NativeSwapChainPresent,
        NativeSwapChainReference,
        NativeSwapChainRelease,
        NativeTextureCreateView,
        NativeTextureDestroy,
        NativeTextureGetDepthOrArrayLayers,
        NativeTextureGetDimension,
        NativeTextureGetFormat,
        NativeTextureGetHeight,
        NativeTextureGetMipLevelCount,
        NativeTextureGetSampleCount,
        NativeTextureGetUsage,
        NativeTextureGetWidth,
        NativeTextureSetLabel,
        NativeTextureReference,
        NativeTextureRelease,
        NativeTextureViewSetLabel,
        NativeTextureViewReference,
        NativeTextureViewRelease,
    };

    const DawnProcTable& GetProcsAutogen() {
        return gProcTable;
    }
}
