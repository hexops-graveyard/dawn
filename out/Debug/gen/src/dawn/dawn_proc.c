
#include "dawn/dawn_proc.h"

static DawnProcTable procs;

static DawnProcTable nullProcs;

void dawnProcSetProcs(const DawnProcTable* procs_) {
    if (procs_) {
        procs = *procs_;
    } else {
        procs = nullProcs;
    }
}

WGPUInstance wgpuCreateInstance(WGPUInstanceDescriptor const * descriptor) {
    return procs.createInstance(descriptor);
}

WGPUProc wgpuGetProcAddress(WGPUDevice device, const char* procName) {
    return procs.getProcAddress(device, procName);
}

void wgpuBindGroupReference(WGPUBindGroup bindGroup) {
    procs.bindGroupReference(bindGroup);
}
void wgpuBindGroupRelease(WGPUBindGroup bindGroup) {
    procs.bindGroupRelease(bindGroup);
}

void wgpuBindGroupLayoutReference(WGPUBindGroupLayout bindGroupLayout) {
    procs.bindGroupLayoutReference(bindGroupLayout);
}
void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) {
    procs.bindGroupLayoutRelease(bindGroupLayout);
}

void wgpuBufferDestroy(WGPUBuffer buffer) {
    procs.bufferDestroy(buffer);
}
void const * wgpuBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
return     procs.bufferGetConstMappedRange(buffer, offset, size);
}
void * wgpuBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
return     procs.bufferGetMappedRange(buffer, offset, size);
}
void wgpuBufferMapAsync(WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
    procs.bufferMapAsync(buffer, mode, offset, size, callback, userdata);
}
void wgpuBufferSetLabel(WGPUBuffer buffer, char const * label) {
    procs.bufferSetLabel(buffer, label);
}
void wgpuBufferUnmap(WGPUBuffer buffer) {
    procs.bufferUnmap(buffer);
}
void wgpuBufferReference(WGPUBuffer buffer) {
    procs.bufferReference(buffer);
}
void wgpuBufferRelease(WGPUBuffer buffer) {
    procs.bufferRelease(buffer);
}

void wgpuCommandBufferReference(WGPUCommandBuffer commandBuffer) {
    procs.commandBufferReference(commandBuffer);
}
void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer) {
    procs.commandBufferRelease(commandBuffer);
}

WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor) {
return     procs.commandEncoderBeginComputePass(commandEncoder, descriptor);
}
WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) {
return     procs.commandEncoderBeginRenderPass(commandEncoder, descriptor);
}
void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
    procs.commandEncoderCopyBufferToBuffer(commandEncoder, source, sourceOffset, destination, destinationOffset, size);
}
void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    procs.commandEncoderCopyBufferToTexture(commandEncoder, source, destination, copySize);
}
void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
    procs.commandEncoderCopyTextureToBuffer(commandEncoder, source, destination, copySize);
}
void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    procs.commandEncoderCopyTextureToTexture(commandEncoder, source, destination, copySize);
}
void wgpuCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    procs.commandEncoderCopyTextureToTextureInternal(commandEncoder, source, destination, copySize);
}
WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor) {
return     procs.commandEncoderFinish(commandEncoder, descriptor);
}
void wgpuCommandEncoderInjectValidationError(WGPUCommandEncoder commandEncoder, char const * message) {
    procs.commandEncoderInjectValidationError(commandEncoder, message);
}
void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const * markerLabel) {
    procs.commandEncoderInsertDebugMarker(commandEncoder, markerLabel);
}
void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) {
    procs.commandEncoderPopDebugGroup(commandEncoder);
}
void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const * groupLabel) {
    procs.commandEncoderPushDebugGroup(commandEncoder, groupLabel);
}
void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
    procs.commandEncoderResolveQuerySet(commandEncoder, querySet, firstQuery, queryCount, destination, destinationOffset);
}
void wgpuCommandEncoderWriteBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
    procs.commandEncoderWriteBuffer(commandEncoder, buffer, bufferOffset, data, size);
}
void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    procs.commandEncoderWriteTimestamp(commandEncoder, querySet, queryIndex);
}
void wgpuCommandEncoderReference(WGPUCommandEncoder commandEncoder) {
    procs.commandEncoderReference(commandEncoder);
}
void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder) {
    procs.commandEncoderRelease(commandEncoder);
}

void wgpuComputePassEncoderDispatch(WGPUComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z) {
    procs.computePassEncoderDispatch(computePassEncoder, x, y, z);
}
void wgpuComputePassEncoderDispatchIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    procs.computePassEncoderDispatchIndirect(computePassEncoder, indirectBuffer, indirectOffset);
}
void wgpuComputePassEncoderEndPass(WGPUComputePassEncoder computePassEncoder) {
    procs.computePassEncoderEndPass(computePassEncoder);
}
void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * markerLabel) {
    procs.computePassEncoderInsertDebugMarker(computePassEncoder, markerLabel);
}
void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) {
    procs.computePassEncoderPopDebugGroup(computePassEncoder);
}
void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel) {
    procs.computePassEncoderPushDebugGroup(computePassEncoder, groupLabel);
}
void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    procs.computePassEncoderSetBindGroup(computePassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) {
    procs.computePassEncoderSetPipeline(computePassEncoder, pipeline);
}
void wgpuComputePassEncoderWriteTimestamp(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    procs.computePassEncoderWriteTimestamp(computePassEncoder, querySet, queryIndex);
}
void wgpuComputePassEncoderReference(WGPUComputePassEncoder computePassEncoder) {
    procs.computePassEncoderReference(computePassEncoder);
}
void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) {
    procs.computePassEncoderRelease(computePassEncoder);
}

WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) {
return     procs.computePipelineGetBindGroupLayout(computePipeline, groupIndex);
}
void wgpuComputePipelineSetLabel(WGPUComputePipeline computePipeline, char const * label) {
    procs.computePipelineSetLabel(computePipeline, label);
}
void wgpuComputePipelineReference(WGPUComputePipeline computePipeline) {
    procs.computePipelineReference(computePipeline);
}
void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline) {
    procs.computePipelineRelease(computePipeline);
}

WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) {
return     procs.deviceCreateBindGroup(device, descriptor);
}
WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) {
return     procs.deviceCreateBindGroupLayout(device, descriptor);
}
WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
return     procs.deviceCreateBuffer(device, descriptor);
}
WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor) {
return     procs.deviceCreateCommandEncoder(device, descriptor);
}
WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) {
return     procs.deviceCreateComputePipeline(device, descriptor);
}
void wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
    procs.deviceCreateComputePipelineAsync(device, descriptor, callback, userdata);
}
WGPUBuffer wgpuDeviceCreateErrorBuffer(WGPUDevice device) {
return     procs.deviceCreateErrorBuffer(device);
}
WGPUExternalTexture wgpuDeviceCreateExternalTexture(WGPUDevice device, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
return     procs.deviceCreateExternalTexture(device, externalTextureDescriptor);
}
WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) {
return     procs.deviceCreatePipelineLayout(device, descriptor);
}
WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) {
return     procs.deviceCreateQuerySet(device, descriptor);
}
WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) {
return     procs.deviceCreateRenderBundleEncoder(device, descriptor);
}
WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) {
return     procs.deviceCreateRenderPipeline(device, descriptor);
}
void wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
    procs.deviceCreateRenderPipelineAsync(device, descriptor, callback, userdata);
}
WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const * descriptor) {
return     procs.deviceCreateSampler(device, descriptor);
}
WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) {
return     procs.deviceCreateShaderModule(device, descriptor);
}
WGPUSwapChain wgpuDeviceCreateSwapChain(WGPUDevice device, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
return     procs.deviceCreateSwapChain(device, surface, descriptor);
}
WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
return     procs.deviceCreateTexture(device, descriptor);
}
bool wgpuDeviceGetLimits(WGPUDevice device, WGPUSupportedLimits * limits) {
return     procs.deviceGetLimits(device, limits);
}
WGPUQueue wgpuDeviceGetQueue(WGPUDevice device) {
return     procs.deviceGetQueue(device);
}
void wgpuDeviceInjectError(WGPUDevice device, WGPUErrorType type, char const * message) {
    procs.deviceInjectError(device, type, message);
}
void wgpuDeviceLoseForTesting(WGPUDevice device) {
    procs.deviceLoseForTesting(device);
}
bool wgpuDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
return     procs.devicePopErrorScope(device, callback, userdata);
}
void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) {
    procs.devicePushErrorScope(device, filter);
}
void wgpuDeviceSetDeviceLostCallback(WGPUDevice device, WGPUDeviceLostCallback callback, void * userdata) {
    procs.deviceSetDeviceLostCallback(device, callback, userdata);
}
void wgpuDeviceSetLoggingCallback(WGPUDevice device, WGPULoggingCallback callback, void * userdata) {
    procs.deviceSetLoggingCallback(device, callback, userdata);
}
void wgpuDeviceSetUncapturedErrorCallback(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    procs.deviceSetUncapturedErrorCallback(device, callback, userdata);
}
void wgpuDeviceTick(WGPUDevice device) {
    procs.deviceTick(device);
}
void wgpuDeviceReference(WGPUDevice device) {
    procs.deviceReference(device);
}
void wgpuDeviceRelease(WGPUDevice device) {
    procs.deviceRelease(device);
}

void wgpuExternalTextureDestroy(WGPUExternalTexture externalTexture) {
    procs.externalTextureDestroy(externalTexture);
}
void wgpuExternalTextureReference(WGPUExternalTexture externalTexture) {
    procs.externalTextureReference(externalTexture);
}
void wgpuExternalTextureRelease(WGPUExternalTexture externalTexture) {
    procs.externalTextureRelease(externalTexture);
}

WGPUSurface wgpuInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) {
return     procs.instanceCreateSurface(instance, descriptor);
}
void wgpuInstanceReference(WGPUInstance instance) {
    procs.instanceReference(instance);
}
void wgpuInstanceRelease(WGPUInstance instance) {
    procs.instanceRelease(instance);
}

void wgpuPipelineLayoutReference(WGPUPipelineLayout pipelineLayout) {
    procs.pipelineLayoutReference(pipelineLayout);
}
void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) {
    procs.pipelineLayoutRelease(pipelineLayout);
}

void wgpuQuerySetDestroy(WGPUQuerySet querySet) {
    procs.querySetDestroy(querySet);
}
void wgpuQuerySetReference(WGPUQuerySet querySet) {
    procs.querySetReference(querySet);
}
void wgpuQuerySetRelease(WGPUQuerySet querySet) {
    procs.querySetRelease(querySet);
}

void wgpuQueueCopyTextureForBrowser(WGPUQueue queue, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
    procs.queueCopyTextureForBrowser(queue, source, destination, copySize, options);
}
void wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
    procs.queueOnSubmittedWorkDone(queue, signalValue, callback, userdata);
}
void wgpuQueueSubmit(WGPUQueue queue, uint32_t commandCount, WGPUCommandBuffer const * commands) {
    procs.queueSubmit(queue, commandCount, commands);
}
void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
    procs.queueWriteBuffer(queue, buffer, bufferOffset, data, size);
}
void wgpuQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
    procs.queueWriteTexture(queue, destination, data, dataSize, dataLayout, writeSize);
}
void wgpuQueueReference(WGPUQueue queue) {
    procs.queueReference(queue);
}
void wgpuQueueRelease(WGPUQueue queue) {
    procs.queueRelease(queue);
}

void wgpuRenderBundleReference(WGPURenderBundle renderBundle) {
    procs.renderBundleReference(renderBundle);
}
void wgpuRenderBundleRelease(WGPURenderBundle renderBundle) {
    procs.renderBundleRelease(renderBundle);
}

void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    procs.renderBundleEncoderDraw(renderBundleEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    procs.renderBundleEncoderDrawIndexed(renderBundleEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    procs.renderBundleEncoderDrawIndexedIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    procs.renderBundleEncoderDrawIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderBundleDescriptor const * descriptor) {
return     procs.renderBundleEncoderFinish(renderBundleEncoder, descriptor);
}
void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel) {
    procs.renderBundleEncoderInsertDebugMarker(renderBundleEncoder, markerLabel);
}
void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) {
    procs.renderBundleEncoderPopDebugGroup(renderBundleEncoder);
}
void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel) {
    procs.renderBundleEncoderPushDebugGroup(renderBundleEncoder, groupLabel);
}
void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    procs.renderBundleEncoderSetBindGroup(renderBundleEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    procs.renderBundleEncoderSetIndexBuffer(renderBundleEncoder, buffer, format, offset, size);
}
void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) {
    procs.renderBundleEncoderSetPipeline(renderBundleEncoder, pipeline);
}
void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    procs.renderBundleEncoderSetVertexBuffer(renderBundleEncoder, slot, buffer, offset, size);
}
void wgpuRenderBundleEncoderReference(WGPURenderBundleEncoder renderBundleEncoder) {
    procs.renderBundleEncoderReference(renderBundleEncoder);
}
void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) {
    procs.renderBundleEncoderRelease(renderBundleEncoder);
}

void wgpuRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) {
    procs.renderPassEncoderBeginOcclusionQuery(renderPassEncoder, queryIndex);
}
void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    procs.renderPassEncoderDraw(renderPassEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    procs.renderPassEncoderDrawIndexed(renderPassEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    procs.renderPassEncoderDrawIndexedIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    procs.renderPassEncoderDrawIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
void wgpuRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder renderPassEncoder) {
    procs.renderPassEncoderEndOcclusionQuery(renderPassEncoder);
}
void wgpuRenderPassEncoderEndPass(WGPURenderPassEncoder renderPassEncoder) {
    procs.renderPassEncoderEndPass(renderPassEncoder);
}
void wgpuRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
    procs.renderPassEncoderExecuteBundles(renderPassEncoder, bundlesCount, bundles);
}
void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const * markerLabel) {
    procs.renderPassEncoderInsertDebugMarker(renderPassEncoder, markerLabel);
}
void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) {
    procs.renderPassEncoderPopDebugGroup(renderPassEncoder);
}
void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel) {
    procs.renderPassEncoderPushDebugGroup(renderPassEncoder, groupLabel);
}
void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    procs.renderPassEncoderSetBindGroup(renderPassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) {
    procs.renderPassEncoderSetBlendConstant(renderPassEncoder, color);
}
void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    procs.renderPassEncoderSetIndexBuffer(renderPassEncoder, buffer, format, offset, size);
}
void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) {
    procs.renderPassEncoderSetPipeline(renderPassEncoder, pipeline);
}
void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    procs.renderPassEncoderSetScissorRect(renderPassEncoder, x, y, width, height);
}
void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) {
    procs.renderPassEncoderSetStencilReference(renderPassEncoder, reference);
}
void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    procs.renderPassEncoderSetVertexBuffer(renderPassEncoder, slot, buffer, offset, size);
}
void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) {
    procs.renderPassEncoderSetViewport(renderPassEncoder, x, y, width, height, minDepth, maxDepth);
}
void wgpuRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    procs.renderPassEncoderWriteTimestamp(renderPassEncoder, querySet, queryIndex);
}
void wgpuRenderPassEncoderReference(WGPURenderPassEncoder renderPassEncoder) {
    procs.renderPassEncoderReference(renderPassEncoder);
}
void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) {
    procs.renderPassEncoderRelease(renderPassEncoder);
}

WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) {
return     procs.renderPipelineGetBindGroupLayout(renderPipeline, groupIndex);
}
void wgpuRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, char const * label) {
    procs.renderPipelineSetLabel(renderPipeline, label);
}
void wgpuRenderPipelineReference(WGPURenderPipeline renderPipeline) {
    procs.renderPipelineReference(renderPipeline);
}
void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline) {
    procs.renderPipelineRelease(renderPipeline);
}

void wgpuSamplerReference(WGPUSampler sampler) {
    procs.samplerReference(sampler);
}
void wgpuSamplerRelease(WGPUSampler sampler) {
    procs.samplerRelease(sampler);
}

void wgpuShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule, WGPUCompilationInfoCallback callback, void * userdata) {
    procs.shaderModuleGetCompilationInfo(shaderModule, callback, userdata);
}
void wgpuShaderModuleSetLabel(WGPUShaderModule shaderModule, char const * label) {
    procs.shaderModuleSetLabel(shaderModule, label);
}
void wgpuShaderModuleReference(WGPUShaderModule shaderModule) {
    procs.shaderModuleReference(shaderModule);
}
void wgpuShaderModuleRelease(WGPUShaderModule shaderModule) {
    procs.shaderModuleRelease(shaderModule);
}

void wgpuSurfaceReference(WGPUSurface surface) {
    procs.surfaceReference(surface);
}
void wgpuSurfaceRelease(WGPUSurface surface) {
    procs.surfaceRelease(surface);
}

void wgpuSwapChainConfigure(WGPUSwapChain swapChain, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
    procs.swapChainConfigure(swapChain, format, allowedUsage, width, height);
}
WGPUTextureView wgpuSwapChainGetCurrentTextureView(WGPUSwapChain swapChain) {
return     procs.swapChainGetCurrentTextureView(swapChain);
}
void wgpuSwapChainPresent(WGPUSwapChain swapChain) {
    procs.swapChainPresent(swapChain);
}
void wgpuSwapChainReference(WGPUSwapChain swapChain) {
    procs.swapChainReference(swapChain);
}
void wgpuSwapChainRelease(WGPUSwapChain swapChain) {
    procs.swapChainRelease(swapChain);
}

WGPUTextureView wgpuTextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor) {
return     procs.textureCreateView(texture, descriptor);
}
void wgpuTextureDestroy(WGPUTexture texture) {
    procs.textureDestroy(texture);
}
void wgpuTextureSetLabel(WGPUTexture texture, char const * label) {
    procs.textureSetLabel(texture, label);
}
void wgpuTextureReference(WGPUTexture texture) {
    procs.textureReference(texture);
}
void wgpuTextureRelease(WGPUTexture texture) {
    procs.textureRelease(texture);
}

void wgpuTextureViewReference(WGPUTextureView textureView) {
    procs.textureViewReference(textureView);
}
void wgpuTextureViewRelease(WGPUTextureView textureView) {
    procs.textureViewRelease(textureView);
}

