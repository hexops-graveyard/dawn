
#include "mock_webgpu.h"

using namespace testing;

namespace {
    WGPUDevice ForwardAdapterCreateDevice(WGPUAdapter self, WGPUDeviceDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterCreateDevice(self, descriptor);
    }
    size_t ForwardAdapterEnumerateFeatures(WGPUAdapter self, WGPUFeatureName * features) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterEnumerateFeatures(self, features);
    }
    WGPUInstance ForwardAdapterGetInstance(WGPUAdapter self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterGetInstance(self);
    }
    bool ForwardAdapterGetLimits(WGPUAdapter self, WGPUSupportedLimits * limits) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterGetLimits(self, limits);
    }
    void ForwardAdapterGetProperties(WGPUAdapter self, WGPUAdapterProperties * properties) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterGetProperties(self, properties);
    }
    bool ForwardAdapterHasFeature(WGPUAdapter self, WGPUFeatureName feature) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterHasFeature(self, feature);
    }
    void ForwardAdapterRequestDevice(WGPUAdapter self, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterRequestDevice(self, descriptor, callback, userdata);
    }
    void ForwardAdapterReference(WGPUAdapter self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterReference(self);
    }
    void ForwardAdapterRelease(WGPUAdapter self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->AdapterRelease(self);
    }

    void ForwardBindGroupSetLabel(WGPUBindGroup self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupSetLabel(self, label);
    }
    void ForwardBindGroupReference(WGPUBindGroup self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupReference(self);
    }
    void ForwardBindGroupRelease(WGPUBindGroup self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupRelease(self);
    }

    void ForwardBindGroupLayoutSetLabel(WGPUBindGroupLayout self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupLayoutSetLabel(self, label);
    }
    void ForwardBindGroupLayoutReference(WGPUBindGroupLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupLayoutReference(self);
    }
    void ForwardBindGroupLayoutRelease(WGPUBindGroupLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BindGroupLayoutRelease(self);
    }

    void ForwardBufferDestroy(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferDestroy(self);
    }
    void const * ForwardBufferGetConstMappedRange(WGPUBuffer self, size_t offset, size_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferGetConstMappedRange(self, offset, size);
    }
    WGPUBufferMapState ForwardBufferGetMapState(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferGetMapState(self);
    }
    void * ForwardBufferGetMappedRange(WGPUBuffer self, size_t offset, size_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferGetMappedRange(self, offset, size);
    }
    uint64_t ForwardBufferGetSize(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferGetSize(self);
    }
    WGPUBufferUsage ForwardBufferGetUsage(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferGetUsage(self);
    }
    void ForwardBufferMapAsync(WGPUBuffer self, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferMapAsync(self, mode, offset, size, callback, userdata);
    }
    void ForwardBufferSetLabel(WGPUBuffer self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferSetLabel(self, label);
    }
    void ForwardBufferUnmap(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferUnmap(self);
    }
    void ForwardBufferReference(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferReference(self);
    }
    void ForwardBufferRelease(WGPUBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->BufferRelease(self);
    }

    void ForwardCommandBufferSetLabel(WGPUCommandBuffer self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandBufferSetLabel(self, label);
    }
    void ForwardCommandBufferReference(WGPUCommandBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandBufferReference(self);
    }
    void ForwardCommandBufferRelease(WGPUCommandBuffer self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandBufferRelease(self);
    }

    WGPUComputePassEncoder ForwardCommandEncoderBeginComputePass(WGPUCommandEncoder self, WGPUComputePassDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderBeginComputePass(self, descriptor);
    }
    WGPURenderPassEncoder ForwardCommandEncoderBeginRenderPass(WGPUCommandEncoder self, WGPURenderPassDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderBeginRenderPass(self, descriptor);
    }
    void ForwardCommandEncoderClearBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderClearBuffer(self, buffer, offset, size);
    }
    void ForwardCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder self, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyBufferToBuffer(self, source, sourceOffset, destination, destinationOffset, size);
    }
    void ForwardCommandEncoderCopyBufferToTexture(WGPUCommandEncoder self, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyBufferToTexture(self, source, destination, copySize);
    }
    void ForwardCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyTextureToBuffer(self, source, destination, copySize);
    }
    void ForwardCommandEncoderCopyTextureToTexture(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyTextureToTexture(self, source, destination, copySize);
    }
    void ForwardCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderCopyTextureToTextureInternal(self, source, destination, copySize);
    }
    WGPUCommandBuffer ForwardCommandEncoderFinish(WGPUCommandEncoder self, WGPUCommandBufferDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderFinish(self, descriptor);
    }
    void ForwardCommandEncoderInjectValidationError(WGPUCommandEncoder self, char const * message) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderInjectValidationError(self, message);
    }
    void ForwardCommandEncoderInsertDebugMarker(WGPUCommandEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardCommandEncoderPopDebugGroup(WGPUCommandEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderPopDebugGroup(self);
    }
    void ForwardCommandEncoderPushDebugGroup(WGPUCommandEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardCommandEncoderResolveQuerySet(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderResolveQuerySet(self, querySet, firstQuery, queryCount, destination, destinationOffset);
    }
    void ForwardCommandEncoderSetLabel(WGPUCommandEncoder self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderSetLabel(self, label);
    }
    void ForwardCommandEncoderWriteBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderWriteBuffer(self, buffer, bufferOffset, data, size);
    }
    void ForwardCommandEncoderWriteTimestamp(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderWriteTimestamp(self, querySet, queryIndex);
    }
    void ForwardCommandEncoderReference(WGPUCommandEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderReference(self);
    }
    void ForwardCommandEncoderRelease(WGPUCommandEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->CommandEncoderRelease(self);
    }

    void ForwardComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder self, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderDispatchWorkgroups(self, workgroupCountX, workgroupCountY, workgroupCountZ);
    }
    void ForwardComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderDispatchWorkgroupsIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardComputePassEncoderEnd(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderEnd(self);
    }
    void ForwardComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardComputePassEncoderPopDebugGroup(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderPopDebugGroup(self);
    }
    void ForwardComputePassEncoderPushDebugGroup(WGPUComputePassEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardComputePassEncoderSetBindGroup(WGPUComputePassEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void ForwardComputePassEncoderSetLabel(WGPUComputePassEncoder self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderSetLabel(self, label);
    }
    void ForwardComputePassEncoderSetPipeline(WGPUComputePassEncoder self, WGPUComputePipeline pipeline) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderSetPipeline(self, pipeline);
    }
    void ForwardComputePassEncoderWriteTimestamp(WGPUComputePassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderWriteTimestamp(self, querySet, queryIndex);
    }
    void ForwardComputePassEncoderReference(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderReference(self);
    }
    void ForwardComputePassEncoderRelease(WGPUComputePassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePassEncoderRelease(self);
    }

    WGPUBindGroupLayout ForwardComputePipelineGetBindGroupLayout(WGPUComputePipeline self, uint32_t groupIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePipelineGetBindGroupLayout(self, groupIndex);
    }
    void ForwardComputePipelineSetLabel(WGPUComputePipeline self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePipelineSetLabel(self, label);
    }
    void ForwardComputePipelineReference(WGPUComputePipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePipelineReference(self);
    }
    void ForwardComputePipelineRelease(WGPUComputePipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ComputePipelineRelease(self);
    }

    WGPUBindGroup ForwardDeviceCreateBindGroup(WGPUDevice self, WGPUBindGroupDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateBindGroup(self, descriptor);
    }
    WGPUBindGroupLayout ForwardDeviceCreateBindGroupLayout(WGPUDevice self, WGPUBindGroupLayoutDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateBindGroupLayout(self, descriptor);
    }
    WGPUBuffer ForwardDeviceCreateBuffer(WGPUDevice self, WGPUBufferDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateBuffer(self, descriptor);
    }
    WGPUCommandEncoder ForwardDeviceCreateCommandEncoder(WGPUDevice self, WGPUCommandEncoderDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateCommandEncoder(self, descriptor);
    }
    WGPUComputePipeline ForwardDeviceCreateComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateComputePipeline(self, descriptor);
    }
    void ForwardDeviceCreateComputePipelineAsync(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateComputePipelineAsync(self, descriptor, callback, userdata);
    }
    WGPUBuffer ForwardDeviceCreateErrorBuffer(WGPUDevice self, WGPUBufferDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateErrorBuffer(self, descriptor);
    }
    WGPUExternalTexture ForwardDeviceCreateErrorExternalTexture(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateErrorExternalTexture(self);
    }
    WGPUShaderModule ForwardDeviceCreateErrorShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateErrorShaderModule(self, descriptor, errorMessage);
    }
    WGPUTexture ForwardDeviceCreateErrorTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateErrorTexture(self, descriptor);
    }
    WGPUExternalTexture ForwardDeviceCreateExternalTexture(WGPUDevice self, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateExternalTexture(self, externalTextureDescriptor);
    }
    WGPUPipelineLayout ForwardDeviceCreatePipelineLayout(WGPUDevice self, WGPUPipelineLayoutDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreatePipelineLayout(self, descriptor);
    }
    WGPUQuerySet ForwardDeviceCreateQuerySet(WGPUDevice self, WGPUQuerySetDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateQuerySet(self, descriptor);
    }
    WGPURenderBundleEncoder ForwardDeviceCreateRenderBundleEncoder(WGPUDevice self, WGPURenderBundleEncoderDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateRenderBundleEncoder(self, descriptor);
    }
    WGPURenderPipeline ForwardDeviceCreateRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateRenderPipeline(self, descriptor);
    }
    void ForwardDeviceCreateRenderPipelineAsync(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateRenderPipelineAsync(self, descriptor, callback, userdata);
    }
    WGPUSampler ForwardDeviceCreateSampler(WGPUDevice self, WGPUSamplerDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateSampler(self, descriptor);
    }
    WGPUShaderModule ForwardDeviceCreateShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateShaderModule(self, descriptor);
    }
    WGPUSwapChain ForwardDeviceCreateSwapChain(WGPUDevice self, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateSwapChain(self, surface, descriptor);
    }
    WGPUTexture ForwardDeviceCreateTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceCreateTexture(self, descriptor);
    }
    void ForwardDeviceDestroy(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceDestroy(self);
    }
    size_t ForwardDeviceEnumerateFeatures(WGPUDevice self, WGPUFeatureName * features) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceEnumerateFeatures(self, features);
    }
    void ForwardDeviceForceLoss(WGPUDevice self, WGPUDeviceLostReason type, char const * message) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceForceLoss(self, type, message);
    }
    WGPUAdapter ForwardDeviceGetAdapter(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceGetAdapter(self);
    }
    bool ForwardDeviceGetLimits(WGPUDevice self, WGPUSupportedLimits * limits) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceGetLimits(self, limits);
    }
    WGPUQueue ForwardDeviceGetQueue(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceGetQueue(self);
    }
    WGPUTextureUsage ForwardDeviceGetSupportedSurfaceUsage(WGPUDevice self, WGPUSurface surface) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceGetSupportedSurfaceUsage(self, surface);
    }
    bool ForwardDeviceHasFeature(WGPUDevice self, WGPUFeatureName feature) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceHasFeature(self, feature);
    }
    void ForwardDeviceInjectError(WGPUDevice self, WGPUErrorType type, char const * message) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceInjectError(self, type, message);
    }
    void ForwardDevicePopErrorScope(WGPUDevice self, WGPUErrorCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DevicePopErrorScope(self, callback, userdata);
    }
    void ForwardDevicePushErrorScope(WGPUDevice self, WGPUErrorFilter filter) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DevicePushErrorScope(self, filter);
    }
    void ForwardDeviceSetDeviceLostCallback(WGPUDevice self, WGPUDeviceLostCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceSetDeviceLostCallback(self, callback, userdata);
    }
    void ForwardDeviceSetLabel(WGPUDevice self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceSetLabel(self, label);
    }
    void ForwardDeviceSetLoggingCallback(WGPUDevice self, WGPULoggingCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceSetLoggingCallback(self, callback, userdata);
    }
    void ForwardDeviceSetUncapturedErrorCallback(WGPUDevice self, WGPUErrorCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceSetUncapturedErrorCallback(self, callback, userdata);
    }
    void ForwardDeviceTick(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceTick(self);
    }
    void ForwardDeviceValidateTextureDescriptor(WGPUDevice self, WGPUTextureDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceValidateTextureDescriptor(self, descriptor);
    }
    void ForwardDeviceReference(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceReference(self);
    }
    void ForwardDeviceRelease(WGPUDevice self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->DeviceRelease(self);
    }

    void ForwardExternalTextureDestroy(WGPUExternalTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ExternalTextureDestroy(self);
    }
    void ForwardExternalTextureExpire(WGPUExternalTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ExternalTextureExpire(self);
    }
    void ForwardExternalTextureRefresh(WGPUExternalTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ExternalTextureRefresh(self);
    }
    void ForwardExternalTextureSetLabel(WGPUExternalTexture self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ExternalTextureSetLabel(self, label);
    }
    void ForwardExternalTextureReference(WGPUExternalTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ExternalTextureReference(self);
    }
    void ForwardExternalTextureRelease(WGPUExternalTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ExternalTextureRelease(self);
    }

    WGPUSurface ForwardInstanceCreateSurface(WGPUInstance self, WGPUSurfaceDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceCreateSurface(self, descriptor);
    }
    void ForwardInstanceProcessEvents(WGPUInstance self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceProcessEvents(self);
    }
    void ForwardInstanceRequestAdapter(WGPUInstance self, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceRequestAdapter(self, options, callback, userdata);
    }
    void ForwardInstanceReference(WGPUInstance self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceReference(self);
    }
    void ForwardInstanceRelease(WGPUInstance self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->InstanceRelease(self);
    }

    void ForwardPipelineLayoutSetLabel(WGPUPipelineLayout self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->PipelineLayoutSetLabel(self, label);
    }
    void ForwardPipelineLayoutReference(WGPUPipelineLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->PipelineLayoutReference(self);
    }
    void ForwardPipelineLayoutRelease(WGPUPipelineLayout self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->PipelineLayoutRelease(self);
    }

    void ForwardQuerySetDestroy(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetDestroy(self);
    }
    uint32_t ForwardQuerySetGetCount(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetGetCount(self);
    }
    WGPUQueryType ForwardQuerySetGetType(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetGetType(self);
    }
    void ForwardQuerySetSetLabel(WGPUQuerySet self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetSetLabel(self, label);
    }
    void ForwardQuerySetReference(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetReference(self);
    }
    void ForwardQuerySetRelease(WGPUQuerySet self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QuerySetRelease(self);
    }

    void ForwardQueueCopyExternalTextureForBrowser(WGPUQueue self, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueCopyExternalTextureForBrowser(self, source, destination, copySize, options);
    }
    void ForwardQueueCopyTextureForBrowser(WGPUQueue self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueCopyTextureForBrowser(self, source, destination, copySize, options);
    }
    void ForwardQueueOnSubmittedWorkDone(WGPUQueue self, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueOnSubmittedWorkDone(self, signalValue, callback, userdata);
    }
    void ForwardQueueSetLabel(WGPUQueue self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueSetLabel(self, label);
    }
    void ForwardQueueSubmit(WGPUQueue self, size_t commandCount, WGPUCommandBuffer const * commands) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueSubmit(self, commandCount, commands);
    }
    void ForwardQueueWriteBuffer(WGPUQueue self, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueWriteBuffer(self, buffer, bufferOffset, data, size);
    }
    void ForwardQueueWriteTexture(WGPUQueue self, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueWriteTexture(self, destination, data, dataSize, dataLayout, writeSize);
    }
    void ForwardQueueReference(WGPUQueue self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueReference(self);
    }
    void ForwardQueueRelease(WGPUQueue self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->QueueRelease(self);
    }

    void ForwardRenderBundleSetLabel(WGPURenderBundle self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleSetLabel(self, label);
    }
    void ForwardRenderBundleReference(WGPURenderBundle self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleReference(self);
    }
    void ForwardRenderBundleRelease(WGPURenderBundle self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleRelease(self);
    }

    void ForwardRenderBundleEncoderDraw(WGPURenderBundleEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void ForwardRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void ForwardRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
    }
    WGPURenderBundle ForwardRenderBundleEncoderFinish(WGPURenderBundleEncoder self, WGPURenderBundleDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderFinish(self, descriptor);
    }
    void ForwardRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderPopDebugGroup(self);
    }
    void ForwardRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void ForwardRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetIndexBuffer(self, buffer, format, offset, size);
    }
    void ForwardRenderBundleEncoderSetLabel(WGPURenderBundleEncoder self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetLabel(self, label);
    }
    void ForwardRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder self, WGPURenderPipeline pipeline) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetPipeline(self, pipeline);
    }
    void ForwardRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderSetVertexBuffer(self, slot, buffer, offset, size);
    }
    void ForwardRenderBundleEncoderReference(WGPURenderBundleEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderReference(self);
    }
    void ForwardRenderBundleEncoderRelease(WGPURenderBundleEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderBundleEncoderRelease(self);
    }

    void ForwardRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder self, uint32_t queryIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderBeginOcclusionQuery(self, queryIndex);
    }
    void ForwardRenderPassEncoderDraw(WGPURenderPassEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void ForwardRenderPassEncoderDrawIndexed(WGPURenderPassEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void ForwardRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardRenderPassEncoderDrawIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
    }
    void ForwardRenderPassEncoderEnd(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderEnd(self);
    }
    void ForwardRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderEndOcclusionQuery(self);
    }
    void ForwardRenderPassEncoderExecuteBundles(WGPURenderPassEncoder self, size_t bundleCount, WGPURenderBundle const * bundles) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderExecuteBundles(self, bundleCount, bundles);
    }
    void ForwardRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder self, char const * markerLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderInsertDebugMarker(self, markerLabel);
    }
    void ForwardRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderPopDebugGroup(self);
    }
    void ForwardRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder self, char const * groupLabel) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderPushDebugGroup(self, groupLabel);
    }
    void ForwardRenderPassEncoderSetBindGroup(WGPURenderPassEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void ForwardRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder self, WGPUColor const * color) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetBlendConstant(self, color);
    }
    void ForwardRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetIndexBuffer(self, buffer, format, offset, size);
    }
    void ForwardRenderPassEncoderSetLabel(WGPURenderPassEncoder self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetLabel(self, label);
    }
    void ForwardRenderPassEncoderSetPipeline(WGPURenderPassEncoder self, WGPURenderPipeline pipeline) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetPipeline(self, pipeline);
    }
    void ForwardRenderPassEncoderSetScissorRect(WGPURenderPassEncoder self, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetScissorRect(self, x, y, width, height);
    }
    void ForwardRenderPassEncoderSetStencilReference(WGPURenderPassEncoder self, uint32_t reference) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetStencilReference(self, reference);
    }
    void ForwardRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetVertexBuffer(self, slot, buffer, offset, size);
    }
    void ForwardRenderPassEncoderSetViewport(WGPURenderPassEncoder self, float x, float y, float width, float height, float minDepth, float maxDepth) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderSetViewport(self, x, y, width, height, minDepth, maxDepth);
    }
    void ForwardRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderWriteTimestamp(self, querySet, queryIndex);
    }
    void ForwardRenderPassEncoderReference(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderReference(self);
    }
    void ForwardRenderPassEncoderRelease(WGPURenderPassEncoder self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPassEncoderRelease(self);
    }

    WGPUBindGroupLayout ForwardRenderPipelineGetBindGroupLayout(WGPURenderPipeline self, uint32_t groupIndex) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPipelineGetBindGroupLayout(self, groupIndex);
    }
    void ForwardRenderPipelineSetLabel(WGPURenderPipeline self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPipelineSetLabel(self, label);
    }
    void ForwardRenderPipelineReference(WGPURenderPipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPipelineReference(self);
    }
    void ForwardRenderPipelineRelease(WGPURenderPipeline self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->RenderPipelineRelease(self);
    }

    void ForwardSamplerSetLabel(WGPUSampler self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SamplerSetLabel(self, label);
    }
    void ForwardSamplerReference(WGPUSampler self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SamplerReference(self);
    }
    void ForwardSamplerRelease(WGPUSampler self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SamplerRelease(self);
    }

    void ForwardShaderModuleGetCompilationInfo(WGPUShaderModule self, WGPUCompilationInfoCallback callback, void * userdata) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ShaderModuleGetCompilationInfo(self, callback, userdata);
    }
    void ForwardShaderModuleSetLabel(WGPUShaderModule self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ShaderModuleSetLabel(self, label);
    }
    void ForwardShaderModuleReference(WGPUShaderModule self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ShaderModuleReference(self);
    }
    void ForwardShaderModuleRelease(WGPUShaderModule self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->ShaderModuleRelease(self);
    }

    void ForwardSurfaceReference(WGPUSurface self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SurfaceReference(self);
    }
    void ForwardSurfaceRelease(WGPUSurface self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SurfaceRelease(self);
    }

    WGPUTexture ForwardSwapChainGetCurrentTexture(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainGetCurrentTexture(self);
    }
    WGPUTextureView ForwardSwapChainGetCurrentTextureView(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainGetCurrentTextureView(self);
    }
    void ForwardSwapChainPresent(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainPresent(self);
    }
    void ForwardSwapChainReference(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainReference(self);
    }
    void ForwardSwapChainRelease(WGPUSwapChain self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->SwapChainRelease(self);
    }

    WGPUTextureView ForwardTextureCreateView(WGPUTexture self, WGPUTextureViewDescriptor const * descriptor) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureCreateView(self, descriptor);
    }
    void ForwardTextureDestroy(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureDestroy(self);
    }
    uint32_t ForwardTextureGetDepthOrArrayLayers(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetDepthOrArrayLayers(self);
    }
    WGPUTextureDimension ForwardTextureGetDimension(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetDimension(self);
    }
    WGPUTextureFormat ForwardTextureGetFormat(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetFormat(self);
    }
    uint32_t ForwardTextureGetHeight(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetHeight(self);
    }
    uint32_t ForwardTextureGetMipLevelCount(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetMipLevelCount(self);
    }
    uint32_t ForwardTextureGetSampleCount(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetSampleCount(self);
    }
    WGPUTextureUsage ForwardTextureGetUsage(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetUsage(self);
    }
    uint32_t ForwardTextureGetWidth(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureGetWidth(self);
    }
    void ForwardTextureSetLabel(WGPUTexture self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureSetLabel(self, label);
    }
    void ForwardTextureReference(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureReference(self);
    }
    void ForwardTextureRelease(WGPUTexture self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureRelease(self);
    }

    void ForwardTextureViewSetLabel(WGPUTextureView self, char const * label) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureViewSetLabel(self, label);
    }
    void ForwardTextureViewReference(WGPUTextureView self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureViewReference(self);
    }
    void ForwardTextureViewRelease(WGPUTextureView self) {
        auto object = reinterpret_cast<ProcTableAsClass::Object*>(self);
        return object->procs->TextureViewRelease(self);
    }

}

ProcTableAsClass::~ProcTableAsClass() {
}

void ProcTableAsClass::GetProcTable(DawnProcTable* table) {
    table->adapterCreateDevice = reinterpret_cast<WGPUProcAdapterCreateDevice>(ForwardAdapterCreateDevice);
    table->adapterEnumerateFeatures = reinterpret_cast<WGPUProcAdapterEnumerateFeatures>(ForwardAdapterEnumerateFeatures);
    table->adapterGetInstance = reinterpret_cast<WGPUProcAdapterGetInstance>(ForwardAdapterGetInstance);
    table->adapterGetLimits = reinterpret_cast<WGPUProcAdapterGetLimits>(ForwardAdapterGetLimits);
    table->adapterGetProperties = reinterpret_cast<WGPUProcAdapterGetProperties>(ForwardAdapterGetProperties);
    table->adapterHasFeature = reinterpret_cast<WGPUProcAdapterHasFeature>(ForwardAdapterHasFeature);
    table->adapterRequestDevice = reinterpret_cast<WGPUProcAdapterRequestDevice>(ForwardAdapterRequestDevice);
    table->adapterReference = reinterpret_cast<WGPUProcAdapterReference>(ForwardAdapterReference);
    table->adapterRelease = reinterpret_cast<WGPUProcAdapterRelease>(ForwardAdapterRelease);
    table->bindGroupSetLabel = reinterpret_cast<WGPUProcBindGroupSetLabel>(ForwardBindGroupSetLabel);
    table->bindGroupReference = reinterpret_cast<WGPUProcBindGroupReference>(ForwardBindGroupReference);
    table->bindGroupRelease = reinterpret_cast<WGPUProcBindGroupRelease>(ForwardBindGroupRelease);
    table->bindGroupLayoutSetLabel = reinterpret_cast<WGPUProcBindGroupLayoutSetLabel>(ForwardBindGroupLayoutSetLabel);
    table->bindGroupLayoutReference = reinterpret_cast<WGPUProcBindGroupLayoutReference>(ForwardBindGroupLayoutReference);
    table->bindGroupLayoutRelease = reinterpret_cast<WGPUProcBindGroupLayoutRelease>(ForwardBindGroupLayoutRelease);
    table->bufferDestroy = reinterpret_cast<WGPUProcBufferDestroy>(ForwardBufferDestroy);
    table->bufferGetConstMappedRange = reinterpret_cast<WGPUProcBufferGetConstMappedRange>(ForwardBufferGetConstMappedRange);
    table->bufferGetMapState = reinterpret_cast<WGPUProcBufferGetMapState>(ForwardBufferGetMapState);
    table->bufferGetMappedRange = reinterpret_cast<WGPUProcBufferGetMappedRange>(ForwardBufferGetMappedRange);
    table->bufferGetSize = reinterpret_cast<WGPUProcBufferGetSize>(ForwardBufferGetSize);
    table->bufferGetUsage = reinterpret_cast<WGPUProcBufferGetUsage>(ForwardBufferGetUsage);
    table->bufferMapAsync = reinterpret_cast<WGPUProcBufferMapAsync>(ForwardBufferMapAsync);
    table->bufferSetLabel = reinterpret_cast<WGPUProcBufferSetLabel>(ForwardBufferSetLabel);
    table->bufferUnmap = reinterpret_cast<WGPUProcBufferUnmap>(ForwardBufferUnmap);
    table->bufferReference = reinterpret_cast<WGPUProcBufferReference>(ForwardBufferReference);
    table->bufferRelease = reinterpret_cast<WGPUProcBufferRelease>(ForwardBufferRelease);
    table->commandBufferSetLabel = reinterpret_cast<WGPUProcCommandBufferSetLabel>(ForwardCommandBufferSetLabel);
    table->commandBufferReference = reinterpret_cast<WGPUProcCommandBufferReference>(ForwardCommandBufferReference);
    table->commandBufferRelease = reinterpret_cast<WGPUProcCommandBufferRelease>(ForwardCommandBufferRelease);
    table->commandEncoderBeginComputePass = reinterpret_cast<WGPUProcCommandEncoderBeginComputePass>(ForwardCommandEncoderBeginComputePass);
    table->commandEncoderBeginRenderPass = reinterpret_cast<WGPUProcCommandEncoderBeginRenderPass>(ForwardCommandEncoderBeginRenderPass);
    table->commandEncoderClearBuffer = reinterpret_cast<WGPUProcCommandEncoderClearBuffer>(ForwardCommandEncoderClearBuffer);
    table->commandEncoderCopyBufferToBuffer = reinterpret_cast<WGPUProcCommandEncoderCopyBufferToBuffer>(ForwardCommandEncoderCopyBufferToBuffer);
    table->commandEncoderCopyBufferToTexture = reinterpret_cast<WGPUProcCommandEncoderCopyBufferToTexture>(ForwardCommandEncoderCopyBufferToTexture);
    table->commandEncoderCopyTextureToBuffer = reinterpret_cast<WGPUProcCommandEncoderCopyTextureToBuffer>(ForwardCommandEncoderCopyTextureToBuffer);
    table->commandEncoderCopyTextureToTexture = reinterpret_cast<WGPUProcCommandEncoderCopyTextureToTexture>(ForwardCommandEncoderCopyTextureToTexture);
    table->commandEncoderCopyTextureToTextureInternal = reinterpret_cast<WGPUProcCommandEncoderCopyTextureToTextureInternal>(ForwardCommandEncoderCopyTextureToTextureInternal);
    table->commandEncoderFinish = reinterpret_cast<WGPUProcCommandEncoderFinish>(ForwardCommandEncoderFinish);
    table->commandEncoderInjectValidationError = reinterpret_cast<WGPUProcCommandEncoderInjectValidationError>(ForwardCommandEncoderInjectValidationError);
    table->commandEncoderInsertDebugMarker = reinterpret_cast<WGPUProcCommandEncoderInsertDebugMarker>(ForwardCommandEncoderInsertDebugMarker);
    table->commandEncoderPopDebugGroup = reinterpret_cast<WGPUProcCommandEncoderPopDebugGroup>(ForwardCommandEncoderPopDebugGroup);
    table->commandEncoderPushDebugGroup = reinterpret_cast<WGPUProcCommandEncoderPushDebugGroup>(ForwardCommandEncoderPushDebugGroup);
    table->commandEncoderResolveQuerySet = reinterpret_cast<WGPUProcCommandEncoderResolveQuerySet>(ForwardCommandEncoderResolveQuerySet);
    table->commandEncoderSetLabel = reinterpret_cast<WGPUProcCommandEncoderSetLabel>(ForwardCommandEncoderSetLabel);
    table->commandEncoderWriteBuffer = reinterpret_cast<WGPUProcCommandEncoderWriteBuffer>(ForwardCommandEncoderWriteBuffer);
    table->commandEncoderWriteTimestamp = reinterpret_cast<WGPUProcCommandEncoderWriteTimestamp>(ForwardCommandEncoderWriteTimestamp);
    table->commandEncoderReference = reinterpret_cast<WGPUProcCommandEncoderReference>(ForwardCommandEncoderReference);
    table->commandEncoderRelease = reinterpret_cast<WGPUProcCommandEncoderRelease>(ForwardCommandEncoderRelease);
    table->computePassEncoderDispatchWorkgroups = reinterpret_cast<WGPUProcComputePassEncoderDispatchWorkgroups>(ForwardComputePassEncoderDispatchWorkgroups);
    table->computePassEncoderDispatchWorkgroupsIndirect = reinterpret_cast<WGPUProcComputePassEncoderDispatchWorkgroupsIndirect>(ForwardComputePassEncoderDispatchWorkgroupsIndirect);
    table->computePassEncoderEnd = reinterpret_cast<WGPUProcComputePassEncoderEnd>(ForwardComputePassEncoderEnd);
    table->computePassEncoderInsertDebugMarker = reinterpret_cast<WGPUProcComputePassEncoderInsertDebugMarker>(ForwardComputePassEncoderInsertDebugMarker);
    table->computePassEncoderPopDebugGroup = reinterpret_cast<WGPUProcComputePassEncoderPopDebugGroup>(ForwardComputePassEncoderPopDebugGroup);
    table->computePassEncoderPushDebugGroup = reinterpret_cast<WGPUProcComputePassEncoderPushDebugGroup>(ForwardComputePassEncoderPushDebugGroup);
    table->computePassEncoderSetBindGroup = reinterpret_cast<WGPUProcComputePassEncoderSetBindGroup>(ForwardComputePassEncoderSetBindGroup);
    table->computePassEncoderSetLabel = reinterpret_cast<WGPUProcComputePassEncoderSetLabel>(ForwardComputePassEncoderSetLabel);
    table->computePassEncoderSetPipeline = reinterpret_cast<WGPUProcComputePassEncoderSetPipeline>(ForwardComputePassEncoderSetPipeline);
    table->computePassEncoderWriteTimestamp = reinterpret_cast<WGPUProcComputePassEncoderWriteTimestamp>(ForwardComputePassEncoderWriteTimestamp);
    table->computePassEncoderReference = reinterpret_cast<WGPUProcComputePassEncoderReference>(ForwardComputePassEncoderReference);
    table->computePassEncoderRelease = reinterpret_cast<WGPUProcComputePassEncoderRelease>(ForwardComputePassEncoderRelease);
    table->computePipelineGetBindGroupLayout = reinterpret_cast<WGPUProcComputePipelineGetBindGroupLayout>(ForwardComputePipelineGetBindGroupLayout);
    table->computePipelineSetLabel = reinterpret_cast<WGPUProcComputePipelineSetLabel>(ForwardComputePipelineSetLabel);
    table->computePipelineReference = reinterpret_cast<WGPUProcComputePipelineReference>(ForwardComputePipelineReference);
    table->computePipelineRelease = reinterpret_cast<WGPUProcComputePipelineRelease>(ForwardComputePipelineRelease);
    table->deviceCreateBindGroup = reinterpret_cast<WGPUProcDeviceCreateBindGroup>(ForwardDeviceCreateBindGroup);
    table->deviceCreateBindGroupLayout = reinterpret_cast<WGPUProcDeviceCreateBindGroupLayout>(ForwardDeviceCreateBindGroupLayout);
    table->deviceCreateBuffer = reinterpret_cast<WGPUProcDeviceCreateBuffer>(ForwardDeviceCreateBuffer);
    table->deviceCreateCommandEncoder = reinterpret_cast<WGPUProcDeviceCreateCommandEncoder>(ForwardDeviceCreateCommandEncoder);
    table->deviceCreateComputePipeline = reinterpret_cast<WGPUProcDeviceCreateComputePipeline>(ForwardDeviceCreateComputePipeline);
    table->deviceCreateComputePipelineAsync = reinterpret_cast<WGPUProcDeviceCreateComputePipelineAsync>(ForwardDeviceCreateComputePipelineAsync);
    table->deviceCreateErrorBuffer = reinterpret_cast<WGPUProcDeviceCreateErrorBuffer>(ForwardDeviceCreateErrorBuffer);
    table->deviceCreateErrorExternalTexture = reinterpret_cast<WGPUProcDeviceCreateErrorExternalTexture>(ForwardDeviceCreateErrorExternalTexture);
    table->deviceCreateErrorShaderModule = reinterpret_cast<WGPUProcDeviceCreateErrorShaderModule>(ForwardDeviceCreateErrorShaderModule);
    table->deviceCreateErrorTexture = reinterpret_cast<WGPUProcDeviceCreateErrorTexture>(ForwardDeviceCreateErrorTexture);
    table->deviceCreateExternalTexture = reinterpret_cast<WGPUProcDeviceCreateExternalTexture>(ForwardDeviceCreateExternalTexture);
    table->deviceCreatePipelineLayout = reinterpret_cast<WGPUProcDeviceCreatePipelineLayout>(ForwardDeviceCreatePipelineLayout);
    table->deviceCreateQuerySet = reinterpret_cast<WGPUProcDeviceCreateQuerySet>(ForwardDeviceCreateQuerySet);
    table->deviceCreateRenderBundleEncoder = reinterpret_cast<WGPUProcDeviceCreateRenderBundleEncoder>(ForwardDeviceCreateRenderBundleEncoder);
    table->deviceCreateRenderPipeline = reinterpret_cast<WGPUProcDeviceCreateRenderPipeline>(ForwardDeviceCreateRenderPipeline);
    table->deviceCreateRenderPipelineAsync = reinterpret_cast<WGPUProcDeviceCreateRenderPipelineAsync>(ForwardDeviceCreateRenderPipelineAsync);
    table->deviceCreateSampler = reinterpret_cast<WGPUProcDeviceCreateSampler>(ForwardDeviceCreateSampler);
    table->deviceCreateShaderModule = reinterpret_cast<WGPUProcDeviceCreateShaderModule>(ForwardDeviceCreateShaderModule);
    table->deviceCreateSwapChain = reinterpret_cast<WGPUProcDeviceCreateSwapChain>(ForwardDeviceCreateSwapChain);
    table->deviceCreateTexture = reinterpret_cast<WGPUProcDeviceCreateTexture>(ForwardDeviceCreateTexture);
    table->deviceDestroy = reinterpret_cast<WGPUProcDeviceDestroy>(ForwardDeviceDestroy);
    table->deviceEnumerateFeatures = reinterpret_cast<WGPUProcDeviceEnumerateFeatures>(ForwardDeviceEnumerateFeatures);
    table->deviceForceLoss = reinterpret_cast<WGPUProcDeviceForceLoss>(ForwardDeviceForceLoss);
    table->deviceGetAdapter = reinterpret_cast<WGPUProcDeviceGetAdapter>(ForwardDeviceGetAdapter);
    table->deviceGetLimits = reinterpret_cast<WGPUProcDeviceGetLimits>(ForwardDeviceGetLimits);
    table->deviceGetQueue = reinterpret_cast<WGPUProcDeviceGetQueue>(ForwardDeviceGetQueue);
    table->deviceGetSupportedSurfaceUsage = reinterpret_cast<WGPUProcDeviceGetSupportedSurfaceUsage>(ForwardDeviceGetSupportedSurfaceUsage);
    table->deviceHasFeature = reinterpret_cast<WGPUProcDeviceHasFeature>(ForwardDeviceHasFeature);
    table->deviceInjectError = reinterpret_cast<WGPUProcDeviceInjectError>(ForwardDeviceInjectError);
    table->devicePopErrorScope = reinterpret_cast<WGPUProcDevicePopErrorScope>(ForwardDevicePopErrorScope);
    table->devicePushErrorScope = reinterpret_cast<WGPUProcDevicePushErrorScope>(ForwardDevicePushErrorScope);
    table->deviceSetDeviceLostCallback = reinterpret_cast<WGPUProcDeviceSetDeviceLostCallback>(ForwardDeviceSetDeviceLostCallback);
    table->deviceSetLabel = reinterpret_cast<WGPUProcDeviceSetLabel>(ForwardDeviceSetLabel);
    table->deviceSetLoggingCallback = reinterpret_cast<WGPUProcDeviceSetLoggingCallback>(ForwardDeviceSetLoggingCallback);
    table->deviceSetUncapturedErrorCallback = reinterpret_cast<WGPUProcDeviceSetUncapturedErrorCallback>(ForwardDeviceSetUncapturedErrorCallback);
    table->deviceTick = reinterpret_cast<WGPUProcDeviceTick>(ForwardDeviceTick);
    table->deviceValidateTextureDescriptor = reinterpret_cast<WGPUProcDeviceValidateTextureDescriptor>(ForwardDeviceValidateTextureDescriptor);
    table->deviceReference = reinterpret_cast<WGPUProcDeviceReference>(ForwardDeviceReference);
    table->deviceRelease = reinterpret_cast<WGPUProcDeviceRelease>(ForwardDeviceRelease);
    table->externalTextureDestroy = reinterpret_cast<WGPUProcExternalTextureDestroy>(ForwardExternalTextureDestroy);
    table->externalTextureExpire = reinterpret_cast<WGPUProcExternalTextureExpire>(ForwardExternalTextureExpire);
    table->externalTextureRefresh = reinterpret_cast<WGPUProcExternalTextureRefresh>(ForwardExternalTextureRefresh);
    table->externalTextureSetLabel = reinterpret_cast<WGPUProcExternalTextureSetLabel>(ForwardExternalTextureSetLabel);
    table->externalTextureReference = reinterpret_cast<WGPUProcExternalTextureReference>(ForwardExternalTextureReference);
    table->externalTextureRelease = reinterpret_cast<WGPUProcExternalTextureRelease>(ForwardExternalTextureRelease);
    table->instanceCreateSurface = reinterpret_cast<WGPUProcInstanceCreateSurface>(ForwardInstanceCreateSurface);
    table->instanceProcessEvents = reinterpret_cast<WGPUProcInstanceProcessEvents>(ForwardInstanceProcessEvents);
    table->instanceRequestAdapter = reinterpret_cast<WGPUProcInstanceRequestAdapter>(ForwardInstanceRequestAdapter);
    table->instanceReference = reinterpret_cast<WGPUProcInstanceReference>(ForwardInstanceReference);
    table->instanceRelease = reinterpret_cast<WGPUProcInstanceRelease>(ForwardInstanceRelease);
    table->pipelineLayoutSetLabel = reinterpret_cast<WGPUProcPipelineLayoutSetLabel>(ForwardPipelineLayoutSetLabel);
    table->pipelineLayoutReference = reinterpret_cast<WGPUProcPipelineLayoutReference>(ForwardPipelineLayoutReference);
    table->pipelineLayoutRelease = reinterpret_cast<WGPUProcPipelineLayoutRelease>(ForwardPipelineLayoutRelease);
    table->querySetDestroy = reinterpret_cast<WGPUProcQuerySetDestroy>(ForwardQuerySetDestroy);
    table->querySetGetCount = reinterpret_cast<WGPUProcQuerySetGetCount>(ForwardQuerySetGetCount);
    table->querySetGetType = reinterpret_cast<WGPUProcQuerySetGetType>(ForwardQuerySetGetType);
    table->querySetSetLabel = reinterpret_cast<WGPUProcQuerySetSetLabel>(ForwardQuerySetSetLabel);
    table->querySetReference = reinterpret_cast<WGPUProcQuerySetReference>(ForwardQuerySetReference);
    table->querySetRelease = reinterpret_cast<WGPUProcQuerySetRelease>(ForwardQuerySetRelease);
    table->queueCopyExternalTextureForBrowser = reinterpret_cast<WGPUProcQueueCopyExternalTextureForBrowser>(ForwardQueueCopyExternalTextureForBrowser);
    table->queueCopyTextureForBrowser = reinterpret_cast<WGPUProcQueueCopyTextureForBrowser>(ForwardQueueCopyTextureForBrowser);
    table->queueOnSubmittedWorkDone = reinterpret_cast<WGPUProcQueueOnSubmittedWorkDone>(ForwardQueueOnSubmittedWorkDone);
    table->queueSetLabel = reinterpret_cast<WGPUProcQueueSetLabel>(ForwardQueueSetLabel);
    table->queueSubmit = reinterpret_cast<WGPUProcQueueSubmit>(ForwardQueueSubmit);
    table->queueWriteBuffer = reinterpret_cast<WGPUProcQueueWriteBuffer>(ForwardQueueWriteBuffer);
    table->queueWriteTexture = reinterpret_cast<WGPUProcQueueWriteTexture>(ForwardQueueWriteTexture);
    table->queueReference = reinterpret_cast<WGPUProcQueueReference>(ForwardQueueReference);
    table->queueRelease = reinterpret_cast<WGPUProcQueueRelease>(ForwardQueueRelease);
    table->renderBundleSetLabel = reinterpret_cast<WGPUProcRenderBundleSetLabel>(ForwardRenderBundleSetLabel);
    table->renderBundleReference = reinterpret_cast<WGPUProcRenderBundleReference>(ForwardRenderBundleReference);
    table->renderBundleRelease = reinterpret_cast<WGPUProcRenderBundleRelease>(ForwardRenderBundleRelease);
    table->renderBundleEncoderDraw = reinterpret_cast<WGPUProcRenderBundleEncoderDraw>(ForwardRenderBundleEncoderDraw);
    table->renderBundleEncoderDrawIndexed = reinterpret_cast<WGPUProcRenderBundleEncoderDrawIndexed>(ForwardRenderBundleEncoderDrawIndexed);
    table->renderBundleEncoderDrawIndexedIndirect = reinterpret_cast<WGPUProcRenderBundleEncoderDrawIndexedIndirect>(ForwardRenderBundleEncoderDrawIndexedIndirect);
    table->renderBundleEncoderDrawIndirect = reinterpret_cast<WGPUProcRenderBundleEncoderDrawIndirect>(ForwardRenderBundleEncoderDrawIndirect);
    table->renderBundleEncoderFinish = reinterpret_cast<WGPUProcRenderBundleEncoderFinish>(ForwardRenderBundleEncoderFinish);
    table->renderBundleEncoderInsertDebugMarker = reinterpret_cast<WGPUProcRenderBundleEncoderInsertDebugMarker>(ForwardRenderBundleEncoderInsertDebugMarker);
    table->renderBundleEncoderPopDebugGroup = reinterpret_cast<WGPUProcRenderBundleEncoderPopDebugGroup>(ForwardRenderBundleEncoderPopDebugGroup);
    table->renderBundleEncoderPushDebugGroup = reinterpret_cast<WGPUProcRenderBundleEncoderPushDebugGroup>(ForwardRenderBundleEncoderPushDebugGroup);
    table->renderBundleEncoderSetBindGroup = reinterpret_cast<WGPUProcRenderBundleEncoderSetBindGroup>(ForwardRenderBundleEncoderSetBindGroup);
    table->renderBundleEncoderSetIndexBuffer = reinterpret_cast<WGPUProcRenderBundleEncoderSetIndexBuffer>(ForwardRenderBundleEncoderSetIndexBuffer);
    table->renderBundleEncoderSetLabel = reinterpret_cast<WGPUProcRenderBundleEncoderSetLabel>(ForwardRenderBundleEncoderSetLabel);
    table->renderBundleEncoderSetPipeline = reinterpret_cast<WGPUProcRenderBundleEncoderSetPipeline>(ForwardRenderBundleEncoderSetPipeline);
    table->renderBundleEncoderSetVertexBuffer = reinterpret_cast<WGPUProcRenderBundleEncoderSetVertexBuffer>(ForwardRenderBundleEncoderSetVertexBuffer);
    table->renderBundleEncoderReference = reinterpret_cast<WGPUProcRenderBundleEncoderReference>(ForwardRenderBundleEncoderReference);
    table->renderBundleEncoderRelease = reinterpret_cast<WGPUProcRenderBundleEncoderRelease>(ForwardRenderBundleEncoderRelease);
    table->renderPassEncoderBeginOcclusionQuery = reinterpret_cast<WGPUProcRenderPassEncoderBeginOcclusionQuery>(ForwardRenderPassEncoderBeginOcclusionQuery);
    table->renderPassEncoderDraw = reinterpret_cast<WGPUProcRenderPassEncoderDraw>(ForwardRenderPassEncoderDraw);
    table->renderPassEncoderDrawIndexed = reinterpret_cast<WGPUProcRenderPassEncoderDrawIndexed>(ForwardRenderPassEncoderDrawIndexed);
    table->renderPassEncoderDrawIndexedIndirect = reinterpret_cast<WGPUProcRenderPassEncoderDrawIndexedIndirect>(ForwardRenderPassEncoderDrawIndexedIndirect);
    table->renderPassEncoderDrawIndirect = reinterpret_cast<WGPUProcRenderPassEncoderDrawIndirect>(ForwardRenderPassEncoderDrawIndirect);
    table->renderPassEncoderEnd = reinterpret_cast<WGPUProcRenderPassEncoderEnd>(ForwardRenderPassEncoderEnd);
    table->renderPassEncoderEndOcclusionQuery = reinterpret_cast<WGPUProcRenderPassEncoderEndOcclusionQuery>(ForwardRenderPassEncoderEndOcclusionQuery);
    table->renderPassEncoderExecuteBundles = reinterpret_cast<WGPUProcRenderPassEncoderExecuteBundles>(ForwardRenderPassEncoderExecuteBundles);
    table->renderPassEncoderInsertDebugMarker = reinterpret_cast<WGPUProcRenderPassEncoderInsertDebugMarker>(ForwardRenderPassEncoderInsertDebugMarker);
    table->renderPassEncoderPopDebugGroup = reinterpret_cast<WGPUProcRenderPassEncoderPopDebugGroup>(ForwardRenderPassEncoderPopDebugGroup);
    table->renderPassEncoderPushDebugGroup = reinterpret_cast<WGPUProcRenderPassEncoderPushDebugGroup>(ForwardRenderPassEncoderPushDebugGroup);
    table->renderPassEncoderSetBindGroup = reinterpret_cast<WGPUProcRenderPassEncoderSetBindGroup>(ForwardRenderPassEncoderSetBindGroup);
    table->renderPassEncoderSetBlendConstant = reinterpret_cast<WGPUProcRenderPassEncoderSetBlendConstant>(ForwardRenderPassEncoderSetBlendConstant);
    table->renderPassEncoderSetIndexBuffer = reinterpret_cast<WGPUProcRenderPassEncoderSetIndexBuffer>(ForwardRenderPassEncoderSetIndexBuffer);
    table->renderPassEncoderSetLabel = reinterpret_cast<WGPUProcRenderPassEncoderSetLabel>(ForwardRenderPassEncoderSetLabel);
    table->renderPassEncoderSetPipeline = reinterpret_cast<WGPUProcRenderPassEncoderSetPipeline>(ForwardRenderPassEncoderSetPipeline);
    table->renderPassEncoderSetScissorRect = reinterpret_cast<WGPUProcRenderPassEncoderSetScissorRect>(ForwardRenderPassEncoderSetScissorRect);
    table->renderPassEncoderSetStencilReference = reinterpret_cast<WGPUProcRenderPassEncoderSetStencilReference>(ForwardRenderPassEncoderSetStencilReference);
    table->renderPassEncoderSetVertexBuffer = reinterpret_cast<WGPUProcRenderPassEncoderSetVertexBuffer>(ForwardRenderPassEncoderSetVertexBuffer);
    table->renderPassEncoderSetViewport = reinterpret_cast<WGPUProcRenderPassEncoderSetViewport>(ForwardRenderPassEncoderSetViewport);
    table->renderPassEncoderWriteTimestamp = reinterpret_cast<WGPUProcRenderPassEncoderWriteTimestamp>(ForwardRenderPassEncoderWriteTimestamp);
    table->renderPassEncoderReference = reinterpret_cast<WGPUProcRenderPassEncoderReference>(ForwardRenderPassEncoderReference);
    table->renderPassEncoderRelease = reinterpret_cast<WGPUProcRenderPassEncoderRelease>(ForwardRenderPassEncoderRelease);
    table->renderPipelineGetBindGroupLayout = reinterpret_cast<WGPUProcRenderPipelineGetBindGroupLayout>(ForwardRenderPipelineGetBindGroupLayout);
    table->renderPipelineSetLabel = reinterpret_cast<WGPUProcRenderPipelineSetLabel>(ForwardRenderPipelineSetLabel);
    table->renderPipelineReference = reinterpret_cast<WGPUProcRenderPipelineReference>(ForwardRenderPipelineReference);
    table->renderPipelineRelease = reinterpret_cast<WGPUProcRenderPipelineRelease>(ForwardRenderPipelineRelease);
    table->samplerSetLabel = reinterpret_cast<WGPUProcSamplerSetLabel>(ForwardSamplerSetLabel);
    table->samplerReference = reinterpret_cast<WGPUProcSamplerReference>(ForwardSamplerReference);
    table->samplerRelease = reinterpret_cast<WGPUProcSamplerRelease>(ForwardSamplerRelease);
    table->shaderModuleGetCompilationInfo = reinterpret_cast<WGPUProcShaderModuleGetCompilationInfo>(ForwardShaderModuleGetCompilationInfo);
    table->shaderModuleSetLabel = reinterpret_cast<WGPUProcShaderModuleSetLabel>(ForwardShaderModuleSetLabel);
    table->shaderModuleReference = reinterpret_cast<WGPUProcShaderModuleReference>(ForwardShaderModuleReference);
    table->shaderModuleRelease = reinterpret_cast<WGPUProcShaderModuleRelease>(ForwardShaderModuleRelease);
    table->surfaceReference = reinterpret_cast<WGPUProcSurfaceReference>(ForwardSurfaceReference);
    table->surfaceRelease = reinterpret_cast<WGPUProcSurfaceRelease>(ForwardSurfaceRelease);
    table->swapChainGetCurrentTexture = reinterpret_cast<WGPUProcSwapChainGetCurrentTexture>(ForwardSwapChainGetCurrentTexture);
    table->swapChainGetCurrentTextureView = reinterpret_cast<WGPUProcSwapChainGetCurrentTextureView>(ForwardSwapChainGetCurrentTextureView);
    table->swapChainPresent = reinterpret_cast<WGPUProcSwapChainPresent>(ForwardSwapChainPresent);
    table->swapChainReference = reinterpret_cast<WGPUProcSwapChainReference>(ForwardSwapChainReference);
    table->swapChainRelease = reinterpret_cast<WGPUProcSwapChainRelease>(ForwardSwapChainRelease);
    table->textureCreateView = reinterpret_cast<WGPUProcTextureCreateView>(ForwardTextureCreateView);
    table->textureDestroy = reinterpret_cast<WGPUProcTextureDestroy>(ForwardTextureDestroy);
    table->textureGetDepthOrArrayLayers = reinterpret_cast<WGPUProcTextureGetDepthOrArrayLayers>(ForwardTextureGetDepthOrArrayLayers);
    table->textureGetDimension = reinterpret_cast<WGPUProcTextureGetDimension>(ForwardTextureGetDimension);
    table->textureGetFormat = reinterpret_cast<WGPUProcTextureGetFormat>(ForwardTextureGetFormat);
    table->textureGetHeight = reinterpret_cast<WGPUProcTextureGetHeight>(ForwardTextureGetHeight);
    table->textureGetMipLevelCount = reinterpret_cast<WGPUProcTextureGetMipLevelCount>(ForwardTextureGetMipLevelCount);
    table->textureGetSampleCount = reinterpret_cast<WGPUProcTextureGetSampleCount>(ForwardTextureGetSampleCount);
    table->textureGetUsage = reinterpret_cast<WGPUProcTextureGetUsage>(ForwardTextureGetUsage);
    table->textureGetWidth = reinterpret_cast<WGPUProcTextureGetWidth>(ForwardTextureGetWidth);
    table->textureSetLabel = reinterpret_cast<WGPUProcTextureSetLabel>(ForwardTextureSetLabel);
    table->textureReference = reinterpret_cast<WGPUProcTextureReference>(ForwardTextureReference);
    table->textureRelease = reinterpret_cast<WGPUProcTextureRelease>(ForwardTextureRelease);
    table->textureViewSetLabel = reinterpret_cast<WGPUProcTextureViewSetLabel>(ForwardTextureViewSetLabel);
    table->textureViewReference = reinterpret_cast<WGPUProcTextureViewReference>(ForwardTextureViewReference);
    table->textureViewRelease = reinterpret_cast<WGPUProcTextureViewRelease>(ForwardTextureViewRelease);
}


void ProcTableAsClass::AdapterRequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(adapter);
    object->mAdapterRequestDeviceCallback = callback;
    object->userdata = userdata;
    return OnAdapterRequestDevice(adapter, descriptor, callback, userdata);
}

void ProcTableAsClass::CallAdapterRequestDeviceCallback(WGPUAdapter adapter, WGPURequestDeviceStatus status, WGPUDevice device, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(adapter);
    object->mAdapterRequestDeviceCallback(status, device, message, object->userdata);
}

void ProcTableAsClass::BufferMapAsync(WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(buffer);
    object->mBufferMapAsyncCallback = callback;
    object->userdata = userdata;
    return OnBufferMapAsync(buffer, mode, offset, size, callback, userdata);
}

void ProcTableAsClass::CallBufferMapAsyncCallback(WGPUBuffer buffer, WGPUBufferMapAsyncStatus status) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(buffer);
    object->mBufferMapAsyncCallback(status, object->userdata);
}

void ProcTableAsClass::DeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceCreateComputePipelineAsyncCallback = callback;
    object->userdata = userdata;
    return OnDeviceCreateComputePipelineAsync(device, descriptor, callback, userdata);
}

void ProcTableAsClass::CallDeviceCreateComputePipelineAsyncCallback(WGPUDevice device, WGPUCreatePipelineAsyncStatus status, WGPUComputePipeline pipeline, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceCreateComputePipelineAsyncCallback(status, pipeline, message, object->userdata);
}

void ProcTableAsClass::DeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceCreateRenderPipelineAsyncCallback = callback;
    object->userdata = userdata;
    return OnDeviceCreateRenderPipelineAsync(device, descriptor, callback, userdata);
}

void ProcTableAsClass::CallDeviceCreateRenderPipelineAsyncCallback(WGPUDevice device, WGPUCreatePipelineAsyncStatus status, WGPURenderPipeline pipeline, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceCreateRenderPipelineAsyncCallback(status, pipeline, message, object->userdata);
}

void ProcTableAsClass::DevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDevicePopErrorScopeCallback = callback;
    object->userdata = userdata;
    return OnDevicePopErrorScope(device, callback, userdata);
}

void ProcTableAsClass::CallDevicePopErrorScopeCallback(WGPUDevice device, WGPUErrorType type, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDevicePopErrorScopeCallback(type, message, object->userdata);
}

void ProcTableAsClass::DeviceSetDeviceLostCallback(WGPUDevice device, WGPUDeviceLostCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceSetDeviceLostCallbackCallback = callback;
    object->userdata = userdata;
    return OnDeviceSetDeviceLostCallback(device, callback, userdata);
}

void ProcTableAsClass::CallDeviceSetDeviceLostCallbackCallback(WGPUDevice device, WGPUDeviceLostReason reason, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceSetDeviceLostCallbackCallback(reason, message, object->userdata);
}

void ProcTableAsClass::DeviceSetLoggingCallback(WGPUDevice device, WGPULoggingCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceSetLoggingCallbackCallback = callback;
    object->userdata = userdata;
    return OnDeviceSetLoggingCallback(device, callback, userdata);
}

void ProcTableAsClass::CallDeviceSetLoggingCallbackCallback(WGPUDevice device, WGPULoggingType type, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceSetLoggingCallbackCallback(type, message, object->userdata);
}

void ProcTableAsClass::DeviceSetUncapturedErrorCallback(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceSetUncapturedErrorCallbackCallback = callback;
    object->userdata = userdata;
    return OnDeviceSetUncapturedErrorCallback(device, callback, userdata);
}

void ProcTableAsClass::CallDeviceSetUncapturedErrorCallbackCallback(WGPUDevice device, WGPUErrorType type, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(device);
    object->mDeviceSetUncapturedErrorCallbackCallback(type, message, object->userdata);
}

void ProcTableAsClass::InstanceRequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(instance);
    object->mInstanceRequestAdapterCallback = callback;
    object->userdata = userdata;
    return OnInstanceRequestAdapter(instance, options, callback, userdata);
}

void ProcTableAsClass::CallInstanceRequestAdapterCallback(WGPUInstance instance, WGPURequestAdapterStatus status, WGPUAdapter adapter, char const * message) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(instance);
    object->mInstanceRequestAdapterCallback(status, adapter, message, object->userdata);
}

void ProcTableAsClass::QueueOnSubmittedWorkDone(WGPUQueue queue, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(queue);
    object->mQueueOnSubmittedWorkDoneCallback = callback;
    object->userdata = userdata;
    return OnQueueOnSubmittedWorkDone(queue, signalValue, callback, userdata);
}

void ProcTableAsClass::CallQueueOnSubmittedWorkDoneCallback(WGPUQueue queue, WGPUQueueWorkDoneStatus status) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(queue);
    object->mQueueOnSubmittedWorkDoneCallback(status, object->userdata);
}

void ProcTableAsClass::ShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule, WGPUCompilationInfoCallback callback, void * userdata) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(shaderModule);
    object->mShaderModuleGetCompilationInfoCallback = callback;
    object->userdata = userdata;
    return OnShaderModuleGetCompilationInfo(shaderModule, callback, userdata);
}

void ProcTableAsClass::CallShaderModuleGetCompilationInfoCallback(WGPUShaderModule shaderModule, WGPUCompilationInfoRequestStatus status, WGPUCompilationInfo const * compilationInfo) {
    ProcTableAsClass::Object* object = reinterpret_cast<ProcTableAsClass::Object*>(shaderModule);
    object->mShaderModuleGetCompilationInfoCallback(status, compilationInfo, object->userdata);
}

WGPUAdapter ProcTableAsClass::GetNewAdapter() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUAdapter>(mObjects.back().get());
}
WGPUBindGroup ProcTableAsClass::GetNewBindGroup() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUBindGroup>(mObjects.back().get());
}
WGPUBindGroupLayout ProcTableAsClass::GetNewBindGroupLayout() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUBindGroupLayout>(mObjects.back().get());
}
WGPUBuffer ProcTableAsClass::GetNewBuffer() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUBuffer>(mObjects.back().get());
}
WGPUCommandBuffer ProcTableAsClass::GetNewCommandBuffer() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUCommandBuffer>(mObjects.back().get());
}
WGPUCommandEncoder ProcTableAsClass::GetNewCommandEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUCommandEncoder>(mObjects.back().get());
}
WGPUComputePassEncoder ProcTableAsClass::GetNewComputePassEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUComputePassEncoder>(mObjects.back().get());
}
WGPUComputePipeline ProcTableAsClass::GetNewComputePipeline() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUComputePipeline>(mObjects.back().get());
}
WGPUDevice ProcTableAsClass::GetNewDevice() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUDevice>(mObjects.back().get());
}
WGPUExternalTexture ProcTableAsClass::GetNewExternalTexture() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUExternalTexture>(mObjects.back().get());
}
WGPUInstance ProcTableAsClass::GetNewInstance() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUInstance>(mObjects.back().get());
}
WGPUPipelineLayout ProcTableAsClass::GetNewPipelineLayout() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUPipelineLayout>(mObjects.back().get());
}
WGPUQuerySet ProcTableAsClass::GetNewQuerySet() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUQuerySet>(mObjects.back().get());
}
WGPUQueue ProcTableAsClass::GetNewQueue() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUQueue>(mObjects.back().get());
}
WGPURenderBundle ProcTableAsClass::GetNewRenderBundle() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderBundle>(mObjects.back().get());
}
WGPURenderBundleEncoder ProcTableAsClass::GetNewRenderBundleEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderBundleEncoder>(mObjects.back().get());
}
WGPURenderPassEncoder ProcTableAsClass::GetNewRenderPassEncoder() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderPassEncoder>(mObjects.back().get());
}
WGPURenderPipeline ProcTableAsClass::GetNewRenderPipeline() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPURenderPipeline>(mObjects.back().get());
}
WGPUSampler ProcTableAsClass::GetNewSampler() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUSampler>(mObjects.back().get());
}
WGPUShaderModule ProcTableAsClass::GetNewShaderModule() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUShaderModule>(mObjects.back().get());
}
WGPUSurface ProcTableAsClass::GetNewSurface() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUSurface>(mObjects.back().get());
}
WGPUSwapChain ProcTableAsClass::GetNewSwapChain() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUSwapChain>(mObjects.back().get());
}
WGPUTexture ProcTableAsClass::GetNewTexture() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUTexture>(mObjects.back().get());
}
WGPUTextureView ProcTableAsClass::GetNewTextureView() {
    mObjects.emplace_back(new Object);
    mObjects.back()->procs = this;
    return reinterpret_cast<WGPUTextureView>(mObjects.back().get());
}

MockProcTable::MockProcTable() = default;

MockProcTable::~MockProcTable() = default;

void MockProcTable::IgnoreAllReleaseCalls() {
    EXPECT_CALL(*this, AdapterRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, BindGroupRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, BindGroupLayoutRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, BufferRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, CommandBufferRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, CommandEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, ComputePassEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, ComputePipelineRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, DeviceRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, ExternalTextureRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, InstanceRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, PipelineLayoutRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, QuerySetRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, QueueRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderBundleRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderBundleEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderPassEncoderRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, RenderPipelineRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, SamplerRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, ShaderModuleRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, SurfaceRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, SwapChainRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, TextureRelease(_)).Times(AnyNumber());
    EXPECT_CALL(*this, TextureViewRelease(_)).Times(AnyNumber());
}
