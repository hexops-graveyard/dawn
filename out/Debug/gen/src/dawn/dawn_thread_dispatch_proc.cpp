#include "dawn/dawn_thread_dispatch_proc.h"

#include <thread>

static DawnProcTable nullProcs;
thread_local DawnProcTable perThreadProcs;

void dawnProcSetPerThreadProcs(const DawnProcTable* procs) {
    if (procs) {
        perThreadProcs = *procs;
    } else {
        perThreadProcs = nullProcs;
    }
}

static WGPUInstance ThreadDispatchCreateInstance(WGPUInstanceDescriptor const * descriptor) {
return     perThreadProcs.createInstance(descriptor);
}
static WGPUProc ThreadDispatchGetProcAddress(WGPUDevice device, char const * procName) {
return     perThreadProcs.getProcAddress(device, procName);
}

static WGPUDevice ThreadDispatchAdapterCreateDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor) {
return     perThreadProcs.adapterCreateDevice(adapter, descriptor);
}
static size_t ThreadDispatchAdapterEnumerateFeatures(WGPUAdapter adapter, WGPUFeatureName * features) {
return     perThreadProcs.adapterEnumerateFeatures(adapter, features);
}
static WGPUInstance ThreadDispatchAdapterGetInstance(WGPUAdapter adapter) {
return     perThreadProcs.adapterGetInstance(adapter);
}
static bool ThreadDispatchAdapterGetLimits(WGPUAdapter adapter, WGPUSupportedLimits * limits) {
return     perThreadProcs.adapterGetLimits(adapter, limits);
}
static void ThreadDispatchAdapterGetProperties(WGPUAdapter adapter, WGPUAdapterProperties * properties) {
    perThreadProcs.adapterGetProperties(adapter, properties);
}
static bool ThreadDispatchAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature) {
return     perThreadProcs.adapterHasFeature(adapter, feature);
}
static void ThreadDispatchAdapterRequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata) {
    perThreadProcs.adapterRequestDevice(adapter, descriptor, callback, userdata);
}
static void ThreadDispatchAdapterReference(WGPUAdapter adapter) {
    perThreadProcs.adapterReference(adapter);
}
static void ThreadDispatchAdapterRelease(WGPUAdapter adapter) {
    perThreadProcs.adapterRelease(adapter);
}
static void ThreadDispatchBindGroupSetLabel(WGPUBindGroup bindGroup, char const * label) {
    perThreadProcs.bindGroupSetLabel(bindGroup, label);
}
static void ThreadDispatchBindGroupReference(WGPUBindGroup bindGroup) {
    perThreadProcs.bindGroupReference(bindGroup);
}
static void ThreadDispatchBindGroupRelease(WGPUBindGroup bindGroup) {
    perThreadProcs.bindGroupRelease(bindGroup);
}
static void ThreadDispatchBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, char const * label) {
    perThreadProcs.bindGroupLayoutSetLabel(bindGroupLayout, label);
}
static void ThreadDispatchBindGroupLayoutReference(WGPUBindGroupLayout bindGroupLayout) {
    perThreadProcs.bindGroupLayoutReference(bindGroupLayout);
}
static void ThreadDispatchBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) {
    perThreadProcs.bindGroupLayoutRelease(bindGroupLayout);
}
static void ThreadDispatchBufferDestroy(WGPUBuffer buffer) {
    perThreadProcs.bufferDestroy(buffer);
}
static void const * ThreadDispatchBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
return     perThreadProcs.bufferGetConstMappedRange(buffer, offset, size);
}
static WGPUBufferMapState ThreadDispatchBufferGetMapState(WGPUBuffer buffer) {
return     perThreadProcs.bufferGetMapState(buffer);
}
static void * ThreadDispatchBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
return     perThreadProcs.bufferGetMappedRange(buffer, offset, size);
}
static uint64_t ThreadDispatchBufferGetSize(WGPUBuffer buffer) {
return     perThreadProcs.bufferGetSize(buffer);
}
static WGPUBufferUsageFlags ThreadDispatchBufferGetUsage(WGPUBuffer buffer) {
return     perThreadProcs.bufferGetUsage(buffer);
}
static void ThreadDispatchBufferMapAsync(WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
    perThreadProcs.bufferMapAsync(buffer, mode, offset, size, callback, userdata);
}
static void ThreadDispatchBufferSetLabel(WGPUBuffer buffer, char const * label) {
    perThreadProcs.bufferSetLabel(buffer, label);
}
static void ThreadDispatchBufferUnmap(WGPUBuffer buffer) {
    perThreadProcs.bufferUnmap(buffer);
}
static void ThreadDispatchBufferReference(WGPUBuffer buffer) {
    perThreadProcs.bufferReference(buffer);
}
static void ThreadDispatchBufferRelease(WGPUBuffer buffer) {
    perThreadProcs.bufferRelease(buffer);
}
static void ThreadDispatchCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, char const * label) {
    perThreadProcs.commandBufferSetLabel(commandBuffer, label);
}
static void ThreadDispatchCommandBufferReference(WGPUCommandBuffer commandBuffer) {
    perThreadProcs.commandBufferReference(commandBuffer);
}
static void ThreadDispatchCommandBufferRelease(WGPUCommandBuffer commandBuffer) {
    perThreadProcs.commandBufferRelease(commandBuffer);
}
static WGPUComputePassEncoder ThreadDispatchCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor) {
return     perThreadProcs.commandEncoderBeginComputePass(commandEncoder, descriptor);
}
static WGPURenderPassEncoder ThreadDispatchCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) {
return     perThreadProcs.commandEncoderBeginRenderPass(commandEncoder, descriptor);
}
static void ThreadDispatchCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    perThreadProcs.commandEncoderClearBuffer(commandEncoder, buffer, offset, size);
}
static void ThreadDispatchCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
    perThreadProcs.commandEncoderCopyBufferToBuffer(commandEncoder, source, sourceOffset, destination, destinationOffset, size);
}
static void ThreadDispatchCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    perThreadProcs.commandEncoderCopyBufferToTexture(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
    perThreadProcs.commandEncoderCopyTextureToBuffer(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    perThreadProcs.commandEncoderCopyTextureToTexture(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    perThreadProcs.commandEncoderCopyTextureToTextureInternal(commandEncoder, source, destination, copySize);
}
static WGPUCommandBuffer ThreadDispatchCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor) {
return     perThreadProcs.commandEncoderFinish(commandEncoder, descriptor);
}
static void ThreadDispatchCommandEncoderInjectValidationError(WGPUCommandEncoder commandEncoder, char const * message) {
    perThreadProcs.commandEncoderInjectValidationError(commandEncoder, message);
}
static void ThreadDispatchCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const * markerLabel) {
    perThreadProcs.commandEncoderInsertDebugMarker(commandEncoder, markerLabel);
}
static void ThreadDispatchCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) {
    perThreadProcs.commandEncoderPopDebugGroup(commandEncoder);
}
static void ThreadDispatchCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const * groupLabel) {
    perThreadProcs.commandEncoderPushDebugGroup(commandEncoder, groupLabel);
}
static void ThreadDispatchCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
    perThreadProcs.commandEncoderResolveQuerySet(commandEncoder, querySet, firstQuery, queryCount, destination, destinationOffset);
}
static void ThreadDispatchCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, char const * label) {
    perThreadProcs.commandEncoderSetLabel(commandEncoder, label);
}
static void ThreadDispatchCommandEncoderWriteBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
    perThreadProcs.commandEncoderWriteBuffer(commandEncoder, buffer, bufferOffset, data, size);
}
static void ThreadDispatchCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    perThreadProcs.commandEncoderWriteTimestamp(commandEncoder, querySet, queryIndex);
}
static void ThreadDispatchCommandEncoderReference(WGPUCommandEncoder commandEncoder) {
    perThreadProcs.commandEncoderReference(commandEncoder);
}
static void ThreadDispatchCommandEncoderRelease(WGPUCommandEncoder commandEncoder) {
    perThreadProcs.commandEncoderRelease(commandEncoder);
}
static void ThreadDispatchComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
    perThreadProcs.computePassEncoderDispatchWorkgroups(computePassEncoder, workgroupCountX, workgroupCountY, workgroupCountZ);
}
static void ThreadDispatchComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.computePassEncoderDispatchWorkgroupsIndirect(computePassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderEnd(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * markerLabel) {
    perThreadProcs.computePassEncoderInsertDebugMarker(computePassEncoder, markerLabel);
}
static void ThreadDispatchComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderPopDebugGroup(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel) {
    perThreadProcs.computePassEncoderPushDebugGroup(computePassEncoder, groupLabel);
}
static void ThreadDispatchComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    perThreadProcs.computePassEncoderSetBindGroup(computePassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, char const * label) {
    perThreadProcs.computePassEncoderSetLabel(computePassEncoder, label);
}
static void ThreadDispatchComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) {
    perThreadProcs.computePassEncoderSetPipeline(computePassEncoder, pipeline);
}
static void ThreadDispatchComputePassEncoderWriteTimestamp(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    perThreadProcs.computePassEncoderWriteTimestamp(computePassEncoder, querySet, queryIndex);
}
static void ThreadDispatchComputePassEncoderReference(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderReference(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) {
    perThreadProcs.computePassEncoderRelease(computePassEncoder);
}
static WGPUBindGroupLayout ThreadDispatchComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) {
return     perThreadProcs.computePipelineGetBindGroupLayout(computePipeline, groupIndex);
}
static void ThreadDispatchComputePipelineSetLabel(WGPUComputePipeline computePipeline, char const * label) {
    perThreadProcs.computePipelineSetLabel(computePipeline, label);
}
static void ThreadDispatchComputePipelineReference(WGPUComputePipeline computePipeline) {
    perThreadProcs.computePipelineReference(computePipeline);
}
static void ThreadDispatchComputePipelineRelease(WGPUComputePipeline computePipeline) {
    perThreadProcs.computePipelineRelease(computePipeline);
}
static WGPUBindGroup ThreadDispatchDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateBindGroup(device, descriptor);
}
static WGPUBindGroupLayout ThreadDispatchDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateBindGroupLayout(device, descriptor);
}
static WGPUBuffer ThreadDispatchDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateBuffer(device, descriptor);
}
static WGPUCommandEncoder ThreadDispatchDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateCommandEncoder(device, descriptor);
}
static WGPUComputePipeline ThreadDispatchDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateComputePipeline(device, descriptor);
}
static void ThreadDispatchDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
    perThreadProcs.deviceCreateComputePipelineAsync(device, descriptor, callback, userdata);
}
static WGPUBuffer ThreadDispatchDeviceCreateErrorBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateErrorBuffer(device, descriptor);
}
static WGPUExternalTexture ThreadDispatchDeviceCreateErrorExternalTexture(WGPUDevice device) {
return     perThreadProcs.deviceCreateErrorExternalTexture(device);
}
static WGPUShaderModule ThreadDispatchDeviceCreateErrorShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage) {
return     perThreadProcs.deviceCreateErrorShaderModule(device, descriptor, errorMessage);
}
static WGPUTexture ThreadDispatchDeviceCreateErrorTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateErrorTexture(device, descriptor);
}
static WGPUExternalTexture ThreadDispatchDeviceCreateExternalTexture(WGPUDevice device, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
return     perThreadProcs.deviceCreateExternalTexture(device, externalTextureDescriptor);
}
static WGPUPipelineLayout ThreadDispatchDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) {
return     perThreadProcs.deviceCreatePipelineLayout(device, descriptor);
}
static WGPUQuerySet ThreadDispatchDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateQuerySet(device, descriptor);
}
static WGPURenderBundleEncoder ThreadDispatchDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateRenderBundleEncoder(device, descriptor);
}
static WGPURenderPipeline ThreadDispatchDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateRenderPipeline(device, descriptor);
}
static void ThreadDispatchDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
    perThreadProcs.deviceCreateRenderPipelineAsync(device, descriptor, callback, userdata);
}
static WGPUSampler ThreadDispatchDeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateSampler(device, descriptor);
}
static WGPUShaderModule ThreadDispatchDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateShaderModule(device, descriptor);
}
static WGPUSwapChain ThreadDispatchDeviceCreateSwapChain(WGPUDevice device, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateSwapChain(device, surface, descriptor);
}
static WGPUTexture ThreadDispatchDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
return     perThreadProcs.deviceCreateTexture(device, descriptor);
}
static void ThreadDispatchDeviceDestroy(WGPUDevice device) {
    perThreadProcs.deviceDestroy(device);
}
static size_t ThreadDispatchDeviceEnumerateFeatures(WGPUDevice device, WGPUFeatureName * features) {
return     perThreadProcs.deviceEnumerateFeatures(device, features);
}
static void ThreadDispatchDeviceForceLoss(WGPUDevice device, WGPUDeviceLostReason type, char const * message) {
    perThreadProcs.deviceForceLoss(device, type, message);
}
static WGPUAdapter ThreadDispatchDeviceGetAdapter(WGPUDevice device) {
return     perThreadProcs.deviceGetAdapter(device);
}
static bool ThreadDispatchDeviceGetLimits(WGPUDevice device, WGPUSupportedLimits * limits) {
return     perThreadProcs.deviceGetLimits(device, limits);
}
static WGPUQueue ThreadDispatchDeviceGetQueue(WGPUDevice device) {
return     perThreadProcs.deviceGetQueue(device);
}
static WGPUTextureUsageFlags ThreadDispatchDeviceGetSupportedSurfaceUsage(WGPUDevice device, WGPUSurface surface) {
return     perThreadProcs.deviceGetSupportedSurfaceUsage(device, surface);
}
static bool ThreadDispatchDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature) {
return     perThreadProcs.deviceHasFeature(device, feature);
}
static void ThreadDispatchDeviceInjectError(WGPUDevice device, WGPUErrorType type, char const * message) {
    perThreadProcs.deviceInjectError(device, type, message);
}
static void ThreadDispatchDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    perThreadProcs.devicePopErrorScope(device, callback, userdata);
}
static void ThreadDispatchDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) {
    perThreadProcs.devicePushErrorScope(device, filter);
}
static void ThreadDispatchDeviceSetDeviceLostCallback(WGPUDevice device, WGPUDeviceLostCallback callback, void * userdata) {
    perThreadProcs.deviceSetDeviceLostCallback(device, callback, userdata);
}
static void ThreadDispatchDeviceSetLabel(WGPUDevice device, char const * label) {
    perThreadProcs.deviceSetLabel(device, label);
}
static void ThreadDispatchDeviceSetLoggingCallback(WGPUDevice device, WGPULoggingCallback callback, void * userdata) {
    perThreadProcs.deviceSetLoggingCallback(device, callback, userdata);
}
static void ThreadDispatchDeviceSetUncapturedErrorCallback(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    perThreadProcs.deviceSetUncapturedErrorCallback(device, callback, userdata);
}
static void ThreadDispatchDeviceTick(WGPUDevice device) {
    perThreadProcs.deviceTick(device);
}
static void ThreadDispatchDeviceValidateTextureDescriptor(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
    perThreadProcs.deviceValidateTextureDescriptor(device, descriptor);
}
static void ThreadDispatchDeviceReference(WGPUDevice device) {
    perThreadProcs.deviceReference(device);
}
static void ThreadDispatchDeviceRelease(WGPUDevice device) {
    perThreadProcs.deviceRelease(device);
}
static void ThreadDispatchExternalTextureDestroy(WGPUExternalTexture externalTexture) {
    perThreadProcs.externalTextureDestroy(externalTexture);
}
static void ThreadDispatchExternalTextureExpire(WGPUExternalTexture externalTexture) {
    perThreadProcs.externalTextureExpire(externalTexture);
}
static void ThreadDispatchExternalTextureRefresh(WGPUExternalTexture externalTexture) {
    perThreadProcs.externalTextureRefresh(externalTexture);
}
static void ThreadDispatchExternalTextureSetLabel(WGPUExternalTexture externalTexture, char const * label) {
    perThreadProcs.externalTextureSetLabel(externalTexture, label);
}
static void ThreadDispatchExternalTextureReference(WGPUExternalTexture externalTexture) {
    perThreadProcs.externalTextureReference(externalTexture);
}
static void ThreadDispatchExternalTextureRelease(WGPUExternalTexture externalTexture) {
    perThreadProcs.externalTextureRelease(externalTexture);
}
static WGPUSurface ThreadDispatchInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) {
return     perThreadProcs.instanceCreateSurface(instance, descriptor);
}
static void ThreadDispatchInstanceProcessEvents(WGPUInstance instance) {
    perThreadProcs.instanceProcessEvents(instance);
}
static void ThreadDispatchInstanceRequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
    perThreadProcs.instanceRequestAdapter(instance, options, callback, userdata);
}
static void ThreadDispatchInstanceReference(WGPUInstance instance) {
    perThreadProcs.instanceReference(instance);
}
static void ThreadDispatchInstanceRelease(WGPUInstance instance) {
    perThreadProcs.instanceRelease(instance);
}
static void ThreadDispatchPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, char const * label) {
    perThreadProcs.pipelineLayoutSetLabel(pipelineLayout, label);
}
static void ThreadDispatchPipelineLayoutReference(WGPUPipelineLayout pipelineLayout) {
    perThreadProcs.pipelineLayoutReference(pipelineLayout);
}
static void ThreadDispatchPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) {
    perThreadProcs.pipelineLayoutRelease(pipelineLayout);
}
static void ThreadDispatchQuerySetDestroy(WGPUQuerySet querySet) {
    perThreadProcs.querySetDestroy(querySet);
}
static uint32_t ThreadDispatchQuerySetGetCount(WGPUQuerySet querySet) {
return     perThreadProcs.querySetGetCount(querySet);
}
static WGPUQueryType ThreadDispatchQuerySetGetType(WGPUQuerySet querySet) {
return     perThreadProcs.querySetGetType(querySet);
}
static void ThreadDispatchQuerySetSetLabel(WGPUQuerySet querySet, char const * label) {
    perThreadProcs.querySetSetLabel(querySet, label);
}
static void ThreadDispatchQuerySetReference(WGPUQuerySet querySet) {
    perThreadProcs.querySetReference(querySet);
}
static void ThreadDispatchQuerySetRelease(WGPUQuerySet querySet) {
    perThreadProcs.querySetRelease(querySet);
}
static void ThreadDispatchQueueCopyExternalTextureForBrowser(WGPUQueue queue, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
    perThreadProcs.queueCopyExternalTextureForBrowser(queue, source, destination, copySize, options);
}
static void ThreadDispatchQueueCopyTextureForBrowser(WGPUQueue queue, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
    perThreadProcs.queueCopyTextureForBrowser(queue, source, destination, copySize, options);
}
static void ThreadDispatchQueueOnSubmittedWorkDone(WGPUQueue queue, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
    perThreadProcs.queueOnSubmittedWorkDone(queue, signalValue, callback, userdata);
}
static void ThreadDispatchQueueSetLabel(WGPUQueue queue, char const * label) {
    perThreadProcs.queueSetLabel(queue, label);
}
static void ThreadDispatchQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) {
    perThreadProcs.queueSubmit(queue, commandCount, commands);
}
static void ThreadDispatchQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
    perThreadProcs.queueWriteBuffer(queue, buffer, bufferOffset, data, size);
}
static void ThreadDispatchQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
    perThreadProcs.queueWriteTexture(queue, destination, data, dataSize, dataLayout, writeSize);
}
static void ThreadDispatchQueueReference(WGPUQueue queue) {
    perThreadProcs.queueReference(queue);
}
static void ThreadDispatchQueueRelease(WGPUQueue queue) {
    perThreadProcs.queueRelease(queue);
}
static void ThreadDispatchRenderBundleSetLabel(WGPURenderBundle renderBundle, char const * label) {
    perThreadProcs.renderBundleSetLabel(renderBundle, label);
}
static void ThreadDispatchRenderBundleReference(WGPURenderBundle renderBundle) {
    perThreadProcs.renderBundleReference(renderBundle);
}
static void ThreadDispatchRenderBundleRelease(WGPURenderBundle renderBundle) {
    perThreadProcs.renderBundleRelease(renderBundle);
}
static void ThreadDispatchRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    perThreadProcs.renderBundleEncoderDraw(renderBundleEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void ThreadDispatchRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    perThreadProcs.renderBundleEncoderDrawIndexed(renderBundleEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void ThreadDispatchRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderBundleEncoderDrawIndexedIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderBundleEncoderDrawIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static WGPURenderBundle ThreadDispatchRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderBundleDescriptor const * descriptor) {
return     perThreadProcs.renderBundleEncoderFinish(renderBundleEncoder, descriptor);
}
static void ThreadDispatchRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel) {
    perThreadProcs.renderBundleEncoderInsertDebugMarker(renderBundleEncoder, markerLabel);
}
static void ThreadDispatchRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) {
    perThreadProcs.renderBundleEncoderPopDebugGroup(renderBundleEncoder);
}
static void ThreadDispatchRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel) {
    perThreadProcs.renderBundleEncoderPushDebugGroup(renderBundleEncoder, groupLabel);
}
static void ThreadDispatchRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    perThreadProcs.renderBundleEncoderSetBindGroup(renderBundleEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    perThreadProcs.renderBundleEncoderSetIndexBuffer(renderBundleEncoder, buffer, format, offset, size);
}
static void ThreadDispatchRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, char const * label) {
    perThreadProcs.renderBundleEncoderSetLabel(renderBundleEncoder, label);
}
static void ThreadDispatchRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) {
    perThreadProcs.renderBundleEncoderSetPipeline(renderBundleEncoder, pipeline);
}
static void ThreadDispatchRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    perThreadProcs.renderBundleEncoderSetVertexBuffer(renderBundleEncoder, slot, buffer, offset, size);
}
static void ThreadDispatchRenderBundleEncoderReference(WGPURenderBundleEncoder renderBundleEncoder) {
    perThreadProcs.renderBundleEncoderReference(renderBundleEncoder);
}
static void ThreadDispatchRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) {
    perThreadProcs.renderBundleEncoderRelease(renderBundleEncoder);
}
static void ThreadDispatchRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) {
    perThreadProcs.renderPassEncoderBeginOcclusionQuery(renderPassEncoder, queryIndex);
}
static void ThreadDispatchRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    perThreadProcs.renderPassEncoderDraw(renderPassEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void ThreadDispatchRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    perThreadProcs.renderPassEncoderDrawIndexed(renderPassEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void ThreadDispatchRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderPassEncoderDrawIndexedIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    perThreadProcs.renderPassEncoderDrawIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderPassEncoderEnd(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderEnd(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderEndOcclusionQuery(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) {
    perThreadProcs.renderPassEncoderExecuteBundles(renderPassEncoder, bundleCount, bundles);
}
static void ThreadDispatchRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const * markerLabel) {
    perThreadProcs.renderPassEncoderInsertDebugMarker(renderPassEncoder, markerLabel);
}
static void ThreadDispatchRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderPopDebugGroup(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel) {
    perThreadProcs.renderPassEncoderPushDebugGroup(renderPassEncoder, groupLabel);
}
static void ThreadDispatchRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    perThreadProcs.renderPassEncoderSetBindGroup(renderPassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) {
    perThreadProcs.renderPassEncoderSetBlendConstant(renderPassEncoder, color);
}
static void ThreadDispatchRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    perThreadProcs.renderPassEncoderSetIndexBuffer(renderPassEncoder, buffer, format, offset, size);
}
static void ThreadDispatchRenderPassEncoderSetLabel(WGPURenderPassEncoder renderPassEncoder, char const * label) {
    perThreadProcs.renderPassEncoderSetLabel(renderPassEncoder, label);
}
static void ThreadDispatchRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) {
    perThreadProcs.renderPassEncoderSetPipeline(renderPassEncoder, pipeline);
}
static void ThreadDispatchRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    perThreadProcs.renderPassEncoderSetScissorRect(renderPassEncoder, x, y, width, height);
}
static void ThreadDispatchRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) {
    perThreadProcs.renderPassEncoderSetStencilReference(renderPassEncoder, reference);
}
static void ThreadDispatchRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    perThreadProcs.renderPassEncoderSetVertexBuffer(renderPassEncoder, slot, buffer, offset, size);
}
static void ThreadDispatchRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) {
    perThreadProcs.renderPassEncoderSetViewport(renderPassEncoder, x, y, width, height, minDepth, maxDepth);
}
static void ThreadDispatchRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    perThreadProcs.renderPassEncoderWriteTimestamp(renderPassEncoder, querySet, queryIndex);
}
static void ThreadDispatchRenderPassEncoderReference(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderReference(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) {
    perThreadProcs.renderPassEncoderRelease(renderPassEncoder);
}
static WGPUBindGroupLayout ThreadDispatchRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) {
return     perThreadProcs.renderPipelineGetBindGroupLayout(renderPipeline, groupIndex);
}
static void ThreadDispatchRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, char const * label) {
    perThreadProcs.renderPipelineSetLabel(renderPipeline, label);
}
static void ThreadDispatchRenderPipelineReference(WGPURenderPipeline renderPipeline) {
    perThreadProcs.renderPipelineReference(renderPipeline);
}
static void ThreadDispatchRenderPipelineRelease(WGPURenderPipeline renderPipeline) {
    perThreadProcs.renderPipelineRelease(renderPipeline);
}
static void ThreadDispatchSamplerSetLabel(WGPUSampler sampler, char const * label) {
    perThreadProcs.samplerSetLabel(sampler, label);
}
static void ThreadDispatchSamplerReference(WGPUSampler sampler) {
    perThreadProcs.samplerReference(sampler);
}
static void ThreadDispatchSamplerRelease(WGPUSampler sampler) {
    perThreadProcs.samplerRelease(sampler);
}
static void ThreadDispatchShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule, WGPUCompilationInfoCallback callback, void * userdata) {
    perThreadProcs.shaderModuleGetCompilationInfo(shaderModule, callback, userdata);
}
static void ThreadDispatchShaderModuleSetLabel(WGPUShaderModule shaderModule, char const * label) {
    perThreadProcs.shaderModuleSetLabel(shaderModule, label);
}
static void ThreadDispatchShaderModuleReference(WGPUShaderModule shaderModule) {
    perThreadProcs.shaderModuleReference(shaderModule);
}
static void ThreadDispatchShaderModuleRelease(WGPUShaderModule shaderModule) {
    perThreadProcs.shaderModuleRelease(shaderModule);
}
static void ThreadDispatchSurfaceReference(WGPUSurface surface) {
    perThreadProcs.surfaceReference(surface);
}
static void ThreadDispatchSurfaceRelease(WGPUSurface surface) {
    perThreadProcs.surfaceRelease(surface);
}
static WGPUTexture ThreadDispatchSwapChainGetCurrentTexture(WGPUSwapChain swapChain) {
return     perThreadProcs.swapChainGetCurrentTexture(swapChain);
}
static WGPUTextureView ThreadDispatchSwapChainGetCurrentTextureView(WGPUSwapChain swapChain) {
return     perThreadProcs.swapChainGetCurrentTextureView(swapChain);
}
static void ThreadDispatchSwapChainPresent(WGPUSwapChain swapChain) {
    perThreadProcs.swapChainPresent(swapChain);
}
static void ThreadDispatchSwapChainReference(WGPUSwapChain swapChain) {
    perThreadProcs.swapChainReference(swapChain);
}
static void ThreadDispatchSwapChainRelease(WGPUSwapChain swapChain) {
    perThreadProcs.swapChainRelease(swapChain);
}
static WGPUTextureView ThreadDispatchTextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor) {
return     perThreadProcs.textureCreateView(texture, descriptor);
}
static void ThreadDispatchTextureDestroy(WGPUTexture texture) {
    perThreadProcs.textureDestroy(texture);
}
static uint32_t ThreadDispatchTextureGetDepthOrArrayLayers(WGPUTexture texture) {
return     perThreadProcs.textureGetDepthOrArrayLayers(texture);
}
static WGPUTextureDimension ThreadDispatchTextureGetDimension(WGPUTexture texture) {
return     perThreadProcs.textureGetDimension(texture);
}
static WGPUTextureFormat ThreadDispatchTextureGetFormat(WGPUTexture texture) {
return     perThreadProcs.textureGetFormat(texture);
}
static uint32_t ThreadDispatchTextureGetHeight(WGPUTexture texture) {
return     perThreadProcs.textureGetHeight(texture);
}
static uint32_t ThreadDispatchTextureGetMipLevelCount(WGPUTexture texture) {
return     perThreadProcs.textureGetMipLevelCount(texture);
}
static uint32_t ThreadDispatchTextureGetSampleCount(WGPUTexture texture) {
return     perThreadProcs.textureGetSampleCount(texture);
}
static WGPUTextureUsageFlags ThreadDispatchTextureGetUsage(WGPUTexture texture) {
return     perThreadProcs.textureGetUsage(texture);
}
static uint32_t ThreadDispatchTextureGetWidth(WGPUTexture texture) {
return     perThreadProcs.textureGetWidth(texture);
}
static void ThreadDispatchTextureSetLabel(WGPUTexture texture, char const * label) {
    perThreadProcs.textureSetLabel(texture, label);
}
static void ThreadDispatchTextureReference(WGPUTexture texture) {
    perThreadProcs.textureReference(texture);
}
static void ThreadDispatchTextureRelease(WGPUTexture texture) {
    perThreadProcs.textureRelease(texture);
}
static void ThreadDispatchTextureViewSetLabel(WGPUTextureView textureView, char const * label) {
    perThreadProcs.textureViewSetLabel(textureView, label);
}
static void ThreadDispatchTextureViewReference(WGPUTextureView textureView) {
    perThreadProcs.textureViewReference(textureView);
}
static void ThreadDispatchTextureViewRelease(WGPUTextureView textureView) {
    perThreadProcs.textureViewRelease(textureView);
}

extern "C" {
    DawnProcTable dawnThreadDispatchProcTable = {
        ThreadDispatchCreateInstance,
        ThreadDispatchGetProcAddress,
        ThreadDispatchAdapterCreateDevice,
        ThreadDispatchAdapterEnumerateFeatures,
        ThreadDispatchAdapterGetInstance,
        ThreadDispatchAdapterGetLimits,
        ThreadDispatchAdapterGetProperties,
        ThreadDispatchAdapterHasFeature,
        ThreadDispatchAdapterRequestDevice,
        ThreadDispatchAdapterReference,
        ThreadDispatchAdapterRelease,
        ThreadDispatchBindGroupSetLabel,
        ThreadDispatchBindGroupReference,
        ThreadDispatchBindGroupRelease,
        ThreadDispatchBindGroupLayoutSetLabel,
        ThreadDispatchBindGroupLayoutReference,
        ThreadDispatchBindGroupLayoutRelease,
        ThreadDispatchBufferDestroy,
        ThreadDispatchBufferGetConstMappedRange,
        ThreadDispatchBufferGetMapState,
        ThreadDispatchBufferGetMappedRange,
        ThreadDispatchBufferGetSize,
        ThreadDispatchBufferGetUsage,
        ThreadDispatchBufferMapAsync,
        ThreadDispatchBufferSetLabel,
        ThreadDispatchBufferUnmap,
        ThreadDispatchBufferReference,
        ThreadDispatchBufferRelease,
        ThreadDispatchCommandBufferSetLabel,
        ThreadDispatchCommandBufferReference,
        ThreadDispatchCommandBufferRelease,
        ThreadDispatchCommandEncoderBeginComputePass,
        ThreadDispatchCommandEncoderBeginRenderPass,
        ThreadDispatchCommandEncoderClearBuffer,
        ThreadDispatchCommandEncoderCopyBufferToBuffer,
        ThreadDispatchCommandEncoderCopyBufferToTexture,
        ThreadDispatchCommandEncoderCopyTextureToBuffer,
        ThreadDispatchCommandEncoderCopyTextureToTexture,
        ThreadDispatchCommandEncoderCopyTextureToTextureInternal,
        ThreadDispatchCommandEncoderFinish,
        ThreadDispatchCommandEncoderInjectValidationError,
        ThreadDispatchCommandEncoderInsertDebugMarker,
        ThreadDispatchCommandEncoderPopDebugGroup,
        ThreadDispatchCommandEncoderPushDebugGroup,
        ThreadDispatchCommandEncoderResolveQuerySet,
        ThreadDispatchCommandEncoderSetLabel,
        ThreadDispatchCommandEncoderWriteBuffer,
        ThreadDispatchCommandEncoderWriteTimestamp,
        ThreadDispatchCommandEncoderReference,
        ThreadDispatchCommandEncoderRelease,
        ThreadDispatchComputePassEncoderDispatchWorkgroups,
        ThreadDispatchComputePassEncoderDispatchWorkgroupsIndirect,
        ThreadDispatchComputePassEncoderEnd,
        ThreadDispatchComputePassEncoderInsertDebugMarker,
        ThreadDispatchComputePassEncoderPopDebugGroup,
        ThreadDispatchComputePassEncoderPushDebugGroup,
        ThreadDispatchComputePassEncoderSetBindGroup,
        ThreadDispatchComputePassEncoderSetLabel,
        ThreadDispatchComputePassEncoderSetPipeline,
        ThreadDispatchComputePassEncoderWriteTimestamp,
        ThreadDispatchComputePassEncoderReference,
        ThreadDispatchComputePassEncoderRelease,
        ThreadDispatchComputePipelineGetBindGroupLayout,
        ThreadDispatchComputePipelineSetLabel,
        ThreadDispatchComputePipelineReference,
        ThreadDispatchComputePipelineRelease,
        ThreadDispatchDeviceCreateBindGroup,
        ThreadDispatchDeviceCreateBindGroupLayout,
        ThreadDispatchDeviceCreateBuffer,
        ThreadDispatchDeviceCreateCommandEncoder,
        ThreadDispatchDeviceCreateComputePipeline,
        ThreadDispatchDeviceCreateComputePipelineAsync,
        ThreadDispatchDeviceCreateErrorBuffer,
        ThreadDispatchDeviceCreateErrorExternalTexture,
        ThreadDispatchDeviceCreateErrorShaderModule,
        ThreadDispatchDeviceCreateErrorTexture,
        ThreadDispatchDeviceCreateExternalTexture,
        ThreadDispatchDeviceCreatePipelineLayout,
        ThreadDispatchDeviceCreateQuerySet,
        ThreadDispatchDeviceCreateRenderBundleEncoder,
        ThreadDispatchDeviceCreateRenderPipeline,
        ThreadDispatchDeviceCreateRenderPipelineAsync,
        ThreadDispatchDeviceCreateSampler,
        ThreadDispatchDeviceCreateShaderModule,
        ThreadDispatchDeviceCreateSwapChain,
        ThreadDispatchDeviceCreateTexture,
        ThreadDispatchDeviceDestroy,
        ThreadDispatchDeviceEnumerateFeatures,
        ThreadDispatchDeviceForceLoss,
        ThreadDispatchDeviceGetAdapter,
        ThreadDispatchDeviceGetLimits,
        ThreadDispatchDeviceGetQueue,
        ThreadDispatchDeviceGetSupportedSurfaceUsage,
        ThreadDispatchDeviceHasFeature,
        ThreadDispatchDeviceInjectError,
        ThreadDispatchDevicePopErrorScope,
        ThreadDispatchDevicePushErrorScope,
        ThreadDispatchDeviceSetDeviceLostCallback,
        ThreadDispatchDeviceSetLabel,
        ThreadDispatchDeviceSetLoggingCallback,
        ThreadDispatchDeviceSetUncapturedErrorCallback,
        ThreadDispatchDeviceTick,
        ThreadDispatchDeviceValidateTextureDescriptor,
        ThreadDispatchDeviceReference,
        ThreadDispatchDeviceRelease,
        ThreadDispatchExternalTextureDestroy,
        ThreadDispatchExternalTextureExpire,
        ThreadDispatchExternalTextureRefresh,
        ThreadDispatchExternalTextureSetLabel,
        ThreadDispatchExternalTextureReference,
        ThreadDispatchExternalTextureRelease,
        ThreadDispatchInstanceCreateSurface,
        ThreadDispatchInstanceProcessEvents,
        ThreadDispatchInstanceRequestAdapter,
        ThreadDispatchInstanceReference,
        ThreadDispatchInstanceRelease,
        ThreadDispatchPipelineLayoutSetLabel,
        ThreadDispatchPipelineLayoutReference,
        ThreadDispatchPipelineLayoutRelease,
        ThreadDispatchQuerySetDestroy,
        ThreadDispatchQuerySetGetCount,
        ThreadDispatchQuerySetGetType,
        ThreadDispatchQuerySetSetLabel,
        ThreadDispatchQuerySetReference,
        ThreadDispatchQuerySetRelease,
        ThreadDispatchQueueCopyExternalTextureForBrowser,
        ThreadDispatchQueueCopyTextureForBrowser,
        ThreadDispatchQueueOnSubmittedWorkDone,
        ThreadDispatchQueueSetLabel,
        ThreadDispatchQueueSubmit,
        ThreadDispatchQueueWriteBuffer,
        ThreadDispatchQueueWriteTexture,
        ThreadDispatchQueueReference,
        ThreadDispatchQueueRelease,
        ThreadDispatchRenderBundleSetLabel,
        ThreadDispatchRenderBundleReference,
        ThreadDispatchRenderBundleRelease,
        ThreadDispatchRenderBundleEncoderDraw,
        ThreadDispatchRenderBundleEncoderDrawIndexed,
        ThreadDispatchRenderBundleEncoderDrawIndexedIndirect,
        ThreadDispatchRenderBundleEncoderDrawIndirect,
        ThreadDispatchRenderBundleEncoderFinish,
        ThreadDispatchRenderBundleEncoderInsertDebugMarker,
        ThreadDispatchRenderBundleEncoderPopDebugGroup,
        ThreadDispatchRenderBundleEncoderPushDebugGroup,
        ThreadDispatchRenderBundleEncoderSetBindGroup,
        ThreadDispatchRenderBundleEncoderSetIndexBuffer,
        ThreadDispatchRenderBundleEncoderSetLabel,
        ThreadDispatchRenderBundleEncoderSetPipeline,
        ThreadDispatchRenderBundleEncoderSetVertexBuffer,
        ThreadDispatchRenderBundleEncoderReference,
        ThreadDispatchRenderBundleEncoderRelease,
        ThreadDispatchRenderPassEncoderBeginOcclusionQuery,
        ThreadDispatchRenderPassEncoderDraw,
        ThreadDispatchRenderPassEncoderDrawIndexed,
        ThreadDispatchRenderPassEncoderDrawIndexedIndirect,
        ThreadDispatchRenderPassEncoderDrawIndirect,
        ThreadDispatchRenderPassEncoderEnd,
        ThreadDispatchRenderPassEncoderEndOcclusionQuery,
        ThreadDispatchRenderPassEncoderExecuteBundles,
        ThreadDispatchRenderPassEncoderInsertDebugMarker,
        ThreadDispatchRenderPassEncoderPopDebugGroup,
        ThreadDispatchRenderPassEncoderPushDebugGroup,
        ThreadDispatchRenderPassEncoderSetBindGroup,
        ThreadDispatchRenderPassEncoderSetBlendConstant,
        ThreadDispatchRenderPassEncoderSetIndexBuffer,
        ThreadDispatchRenderPassEncoderSetLabel,
        ThreadDispatchRenderPassEncoderSetPipeline,
        ThreadDispatchRenderPassEncoderSetScissorRect,
        ThreadDispatchRenderPassEncoderSetStencilReference,
        ThreadDispatchRenderPassEncoderSetVertexBuffer,
        ThreadDispatchRenderPassEncoderSetViewport,
        ThreadDispatchRenderPassEncoderWriteTimestamp,
        ThreadDispatchRenderPassEncoderReference,
        ThreadDispatchRenderPassEncoderRelease,
        ThreadDispatchRenderPipelineGetBindGroupLayout,
        ThreadDispatchRenderPipelineSetLabel,
        ThreadDispatchRenderPipelineReference,
        ThreadDispatchRenderPipelineRelease,
        ThreadDispatchSamplerSetLabel,
        ThreadDispatchSamplerReference,
        ThreadDispatchSamplerRelease,
        ThreadDispatchShaderModuleGetCompilationInfo,
        ThreadDispatchShaderModuleSetLabel,
        ThreadDispatchShaderModuleReference,
        ThreadDispatchShaderModuleRelease,
        ThreadDispatchSurfaceReference,
        ThreadDispatchSurfaceRelease,
        ThreadDispatchSwapChainGetCurrentTexture,
        ThreadDispatchSwapChainGetCurrentTextureView,
        ThreadDispatchSwapChainPresent,
        ThreadDispatchSwapChainReference,
        ThreadDispatchSwapChainRelease,
        ThreadDispatchTextureCreateView,
        ThreadDispatchTextureDestroy,
        ThreadDispatchTextureGetDepthOrArrayLayers,
        ThreadDispatchTextureGetDimension,
        ThreadDispatchTextureGetFormat,
        ThreadDispatchTextureGetHeight,
        ThreadDispatchTextureGetMipLevelCount,
        ThreadDispatchTextureGetSampleCount,
        ThreadDispatchTextureGetUsage,
        ThreadDispatchTextureGetWidth,
        ThreadDispatchTextureSetLabel,
        ThreadDispatchTextureReference,
        ThreadDispatchTextureRelease,
        ThreadDispatchTextureViewSetLabel,
        ThreadDispatchTextureViewReference,
        ThreadDispatchTextureViewRelease,
    };
}
