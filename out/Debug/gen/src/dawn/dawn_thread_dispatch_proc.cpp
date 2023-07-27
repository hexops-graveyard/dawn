#include "dawn/dawn_thread_dispatch_proc.h"

#include <thread>

static DawnProcTable nullProcs;
static DawnProcTable defaultProc;
thread_local DawnProcTable perThreadProcs;

void dawnProcSetDefaultThreadProcs(const DawnProcTable* procs) {
    if (procs) {
        defaultProc = *procs;
    } else {
        defaultProc = nullProcs;
    }
}

void dawnProcSetPerThreadProcs(const DawnProcTable* procs) {
    if (procs) {
        perThreadProcs = *procs;
    } else {
        perThreadProcs = nullProcs;
    }
}

static WGPUInstance ThreadDispatchCreateInstance(WGPUInstanceDescriptor const * descriptor) {
    auto* proc = perThreadProcs.createInstance;
    if (!proc) {
        proc = defaultProc.createInstance;
    }
return     proc(descriptor);
}
static WGPUProc ThreadDispatchGetProcAddress(WGPUDevice device, char const * procName) {
    auto* proc = perThreadProcs.getProcAddress;
    if (!proc) {
        proc = defaultProc.getProcAddress;
    }
return     proc(device, procName);
}

static WGPUDevice ThreadDispatchAdapterCreateDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor) {
    auto* proc = perThreadProcs.adapterCreateDevice;
    if (!proc) {
        proc = defaultProc.adapterCreateDevice;
    }
return     proc(adapter, descriptor);
}
static size_t ThreadDispatchAdapterEnumerateFeatures(WGPUAdapter adapter, WGPUFeatureName * features) {
    auto* proc = perThreadProcs.adapterEnumerateFeatures;
    if (!proc) {
        proc = defaultProc.adapterEnumerateFeatures;
    }
return     proc(adapter, features);
}
static WGPUInstance ThreadDispatchAdapterGetInstance(WGPUAdapter adapter) {
    auto* proc = perThreadProcs.adapterGetInstance;
    if (!proc) {
        proc = defaultProc.adapterGetInstance;
    }
return     proc(adapter);
}
static bool ThreadDispatchAdapterGetLimits(WGPUAdapter adapter, WGPUSupportedLimits * limits) {
    auto* proc = perThreadProcs.adapterGetLimits;
    if (!proc) {
        proc = defaultProc.adapterGetLimits;
    }
return     proc(adapter, limits);
}
static void ThreadDispatchAdapterGetProperties(WGPUAdapter adapter, WGPUAdapterProperties * properties) {
    auto* proc = perThreadProcs.adapterGetProperties;
    if (!proc) {
        proc = defaultProc.adapterGetProperties;
    }
    proc(adapter, properties);
}
static bool ThreadDispatchAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature) {
    auto* proc = perThreadProcs.adapterHasFeature;
    if (!proc) {
        proc = defaultProc.adapterHasFeature;
    }
return     proc(adapter, feature);
}
static void ThreadDispatchAdapterRequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata) {
    auto* proc = perThreadProcs.adapterRequestDevice;
    if (!proc) {
        proc = defaultProc.adapterRequestDevice;
    }
    proc(adapter, descriptor, callback, userdata);
}
static void ThreadDispatchAdapterReference(WGPUAdapter adapter) {
    auto* proc = perThreadProcs.adapterReference;
    if (!proc) {
        proc = defaultProc.adapterReference;
    }
    proc(adapter);
}
static void ThreadDispatchAdapterRelease(WGPUAdapter adapter) {
    auto* proc = perThreadProcs.adapterRelease;
    if (!proc) {
        proc = defaultProc.adapterRelease;
    }
    proc(adapter);
}
static void ThreadDispatchBindGroupSetLabel(WGPUBindGroup bindGroup, char const * label) {
    auto* proc = perThreadProcs.bindGroupSetLabel;
    if (!proc) {
        proc = defaultProc.bindGroupSetLabel;
    }
    proc(bindGroup, label);
}
static void ThreadDispatchBindGroupReference(WGPUBindGroup bindGroup) {
    auto* proc = perThreadProcs.bindGroupReference;
    if (!proc) {
        proc = defaultProc.bindGroupReference;
    }
    proc(bindGroup);
}
static void ThreadDispatchBindGroupRelease(WGPUBindGroup bindGroup) {
    auto* proc = perThreadProcs.bindGroupRelease;
    if (!proc) {
        proc = defaultProc.bindGroupRelease;
    }
    proc(bindGroup);
}
static void ThreadDispatchBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, char const * label) {
    auto* proc = perThreadProcs.bindGroupLayoutSetLabel;
    if (!proc) {
        proc = defaultProc.bindGroupLayoutSetLabel;
    }
    proc(bindGroupLayout, label);
}
static void ThreadDispatchBindGroupLayoutReference(WGPUBindGroupLayout bindGroupLayout) {
    auto* proc = perThreadProcs.bindGroupLayoutReference;
    if (!proc) {
        proc = defaultProc.bindGroupLayoutReference;
    }
    proc(bindGroupLayout);
}
static void ThreadDispatchBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) {
    auto* proc = perThreadProcs.bindGroupLayoutRelease;
    if (!proc) {
        proc = defaultProc.bindGroupLayoutRelease;
    }
    proc(bindGroupLayout);
}
static void ThreadDispatchBufferDestroy(WGPUBuffer buffer) {
    auto* proc = perThreadProcs.bufferDestroy;
    if (!proc) {
        proc = defaultProc.bufferDestroy;
    }
    proc(buffer);
}
static void const * ThreadDispatchBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
    auto* proc = perThreadProcs.bufferGetConstMappedRange;
    if (!proc) {
        proc = defaultProc.bufferGetConstMappedRange;
    }
return     proc(buffer, offset, size);
}
static WGPUBufferMapState ThreadDispatchBufferGetMapState(WGPUBuffer buffer) {
    auto* proc = perThreadProcs.bufferGetMapState;
    if (!proc) {
        proc = defaultProc.bufferGetMapState;
    }
return     proc(buffer);
}
static void * ThreadDispatchBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) {
    auto* proc = perThreadProcs.bufferGetMappedRange;
    if (!proc) {
        proc = defaultProc.bufferGetMappedRange;
    }
return     proc(buffer, offset, size);
}
static uint64_t ThreadDispatchBufferGetSize(WGPUBuffer buffer) {
    auto* proc = perThreadProcs.bufferGetSize;
    if (!proc) {
        proc = defaultProc.bufferGetSize;
    }
return     proc(buffer);
}
static WGPUBufferUsageFlags ThreadDispatchBufferGetUsage(WGPUBuffer buffer) {
    auto* proc = perThreadProcs.bufferGetUsage;
    if (!proc) {
        proc = defaultProc.bufferGetUsage;
    }
return     proc(buffer);
}
static void ThreadDispatchBufferMapAsync(WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
    auto* proc = perThreadProcs.bufferMapAsync;
    if (!proc) {
        proc = defaultProc.bufferMapAsync;
    }
    proc(buffer, mode, offset, size, callback, userdata);
}
static void ThreadDispatchBufferSetLabel(WGPUBuffer buffer, char const * label) {
    auto* proc = perThreadProcs.bufferSetLabel;
    if (!proc) {
        proc = defaultProc.bufferSetLabel;
    }
    proc(buffer, label);
}
static void ThreadDispatchBufferUnmap(WGPUBuffer buffer) {
    auto* proc = perThreadProcs.bufferUnmap;
    if (!proc) {
        proc = defaultProc.bufferUnmap;
    }
    proc(buffer);
}
static void ThreadDispatchBufferReference(WGPUBuffer buffer) {
    auto* proc = perThreadProcs.bufferReference;
    if (!proc) {
        proc = defaultProc.bufferReference;
    }
    proc(buffer);
}
static void ThreadDispatchBufferRelease(WGPUBuffer buffer) {
    auto* proc = perThreadProcs.bufferRelease;
    if (!proc) {
        proc = defaultProc.bufferRelease;
    }
    proc(buffer);
}
static void ThreadDispatchCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, char const * label) {
    auto* proc = perThreadProcs.commandBufferSetLabel;
    if (!proc) {
        proc = defaultProc.commandBufferSetLabel;
    }
    proc(commandBuffer, label);
}
static void ThreadDispatchCommandBufferReference(WGPUCommandBuffer commandBuffer) {
    auto* proc = perThreadProcs.commandBufferReference;
    if (!proc) {
        proc = defaultProc.commandBufferReference;
    }
    proc(commandBuffer);
}
static void ThreadDispatchCommandBufferRelease(WGPUCommandBuffer commandBuffer) {
    auto* proc = perThreadProcs.commandBufferRelease;
    if (!proc) {
        proc = defaultProc.commandBufferRelease;
    }
    proc(commandBuffer);
}
static WGPUComputePassEncoder ThreadDispatchCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor) {
    auto* proc = perThreadProcs.commandEncoderBeginComputePass;
    if (!proc) {
        proc = defaultProc.commandEncoderBeginComputePass;
    }
return     proc(commandEncoder, descriptor);
}
static WGPURenderPassEncoder ThreadDispatchCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) {
    auto* proc = perThreadProcs.commandEncoderBeginRenderPass;
    if (!proc) {
        proc = defaultProc.commandEncoderBeginRenderPass;
    }
return     proc(commandEncoder, descriptor);
}
static void ThreadDispatchCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    auto* proc = perThreadProcs.commandEncoderClearBuffer;
    if (!proc) {
        proc = defaultProc.commandEncoderClearBuffer;
    }
    proc(commandEncoder, buffer, offset, size);
}
static void ThreadDispatchCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
    auto* proc = perThreadProcs.commandEncoderCopyBufferToBuffer;
    if (!proc) {
        proc = defaultProc.commandEncoderCopyBufferToBuffer;
    }
    proc(commandEncoder, source, sourceOffset, destination, destinationOffset, size);
}
static void ThreadDispatchCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    auto* proc = perThreadProcs.commandEncoderCopyBufferToTexture;
    if (!proc) {
        proc = defaultProc.commandEncoderCopyBufferToTexture;
    }
    proc(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
    auto* proc = perThreadProcs.commandEncoderCopyTextureToBuffer;
    if (!proc) {
        proc = defaultProc.commandEncoderCopyTextureToBuffer;
    }
    proc(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    auto* proc = perThreadProcs.commandEncoderCopyTextureToTexture;
    if (!proc) {
        proc = defaultProc.commandEncoderCopyTextureToTexture;
    }
    proc(commandEncoder, source, destination, copySize);
}
static void ThreadDispatchCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
    auto* proc = perThreadProcs.commandEncoderCopyTextureToTextureInternal;
    if (!proc) {
        proc = defaultProc.commandEncoderCopyTextureToTextureInternal;
    }
    proc(commandEncoder, source, destination, copySize);
}
static WGPUCommandBuffer ThreadDispatchCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor) {
    auto* proc = perThreadProcs.commandEncoderFinish;
    if (!proc) {
        proc = defaultProc.commandEncoderFinish;
    }
return     proc(commandEncoder, descriptor);
}
static void ThreadDispatchCommandEncoderInjectValidationError(WGPUCommandEncoder commandEncoder, char const * message) {
    auto* proc = perThreadProcs.commandEncoderInjectValidationError;
    if (!proc) {
        proc = defaultProc.commandEncoderInjectValidationError;
    }
    proc(commandEncoder, message);
}
static void ThreadDispatchCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const * markerLabel) {
    auto* proc = perThreadProcs.commandEncoderInsertDebugMarker;
    if (!proc) {
        proc = defaultProc.commandEncoderInsertDebugMarker;
    }
    proc(commandEncoder, markerLabel);
}
static void ThreadDispatchCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) {
    auto* proc = perThreadProcs.commandEncoderPopDebugGroup;
    if (!proc) {
        proc = defaultProc.commandEncoderPopDebugGroup;
    }
    proc(commandEncoder);
}
static void ThreadDispatchCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const * groupLabel) {
    auto* proc = perThreadProcs.commandEncoderPushDebugGroup;
    if (!proc) {
        proc = defaultProc.commandEncoderPushDebugGroup;
    }
    proc(commandEncoder, groupLabel);
}
static void ThreadDispatchCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
    auto* proc = perThreadProcs.commandEncoderResolveQuerySet;
    if (!proc) {
        proc = defaultProc.commandEncoderResolveQuerySet;
    }
    proc(commandEncoder, querySet, firstQuery, queryCount, destination, destinationOffset);
}
static void ThreadDispatchCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, char const * label) {
    auto* proc = perThreadProcs.commandEncoderSetLabel;
    if (!proc) {
        proc = defaultProc.commandEncoderSetLabel;
    }
    proc(commandEncoder, label);
}
static void ThreadDispatchCommandEncoderWriteBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
    auto* proc = perThreadProcs.commandEncoderWriteBuffer;
    if (!proc) {
        proc = defaultProc.commandEncoderWriteBuffer;
    }
    proc(commandEncoder, buffer, bufferOffset, data, size);
}
static void ThreadDispatchCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    auto* proc = perThreadProcs.commandEncoderWriteTimestamp;
    if (!proc) {
        proc = defaultProc.commandEncoderWriteTimestamp;
    }
    proc(commandEncoder, querySet, queryIndex);
}
static void ThreadDispatchCommandEncoderReference(WGPUCommandEncoder commandEncoder) {
    auto* proc = perThreadProcs.commandEncoderReference;
    if (!proc) {
        proc = defaultProc.commandEncoderReference;
    }
    proc(commandEncoder);
}
static void ThreadDispatchCommandEncoderRelease(WGPUCommandEncoder commandEncoder) {
    auto* proc = perThreadProcs.commandEncoderRelease;
    if (!proc) {
        proc = defaultProc.commandEncoderRelease;
    }
    proc(commandEncoder);
}
static void ThreadDispatchComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
    auto* proc = perThreadProcs.computePassEncoderDispatchWorkgroups;
    if (!proc) {
        proc = defaultProc.computePassEncoderDispatchWorkgroups;
    }
    proc(computePassEncoder, workgroupCountX, workgroupCountY, workgroupCountZ);
}
static void ThreadDispatchComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    auto* proc = perThreadProcs.computePassEncoderDispatchWorkgroupsIndirect;
    if (!proc) {
        proc = defaultProc.computePassEncoderDispatchWorkgroupsIndirect;
    }
    proc(computePassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder) {
    auto* proc = perThreadProcs.computePassEncoderEnd;
    if (!proc) {
        proc = defaultProc.computePassEncoderEnd;
    }
    proc(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * markerLabel) {
    auto* proc = perThreadProcs.computePassEncoderInsertDebugMarker;
    if (!proc) {
        proc = defaultProc.computePassEncoderInsertDebugMarker;
    }
    proc(computePassEncoder, markerLabel);
}
static void ThreadDispatchComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) {
    auto* proc = perThreadProcs.computePassEncoderPopDebugGroup;
    if (!proc) {
        proc = defaultProc.computePassEncoderPopDebugGroup;
    }
    proc(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel) {
    auto* proc = perThreadProcs.computePassEncoderPushDebugGroup;
    if (!proc) {
        proc = defaultProc.computePassEncoderPushDebugGroup;
    }
    proc(computePassEncoder, groupLabel);
}
static void ThreadDispatchComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    auto* proc = perThreadProcs.computePassEncoderSetBindGroup;
    if (!proc) {
        proc = defaultProc.computePassEncoderSetBindGroup;
    }
    proc(computePassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, char const * label) {
    auto* proc = perThreadProcs.computePassEncoderSetLabel;
    if (!proc) {
        proc = defaultProc.computePassEncoderSetLabel;
    }
    proc(computePassEncoder, label);
}
static void ThreadDispatchComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) {
    auto* proc = perThreadProcs.computePassEncoderSetPipeline;
    if (!proc) {
        proc = defaultProc.computePassEncoderSetPipeline;
    }
    proc(computePassEncoder, pipeline);
}
static void ThreadDispatchComputePassEncoderWriteTimestamp(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    auto* proc = perThreadProcs.computePassEncoderWriteTimestamp;
    if (!proc) {
        proc = defaultProc.computePassEncoderWriteTimestamp;
    }
    proc(computePassEncoder, querySet, queryIndex);
}
static void ThreadDispatchComputePassEncoderReference(WGPUComputePassEncoder computePassEncoder) {
    auto* proc = perThreadProcs.computePassEncoderReference;
    if (!proc) {
        proc = defaultProc.computePassEncoderReference;
    }
    proc(computePassEncoder);
}
static void ThreadDispatchComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) {
    auto* proc = perThreadProcs.computePassEncoderRelease;
    if (!proc) {
        proc = defaultProc.computePassEncoderRelease;
    }
    proc(computePassEncoder);
}
static WGPUBindGroupLayout ThreadDispatchComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) {
    auto* proc = perThreadProcs.computePipelineGetBindGroupLayout;
    if (!proc) {
        proc = defaultProc.computePipelineGetBindGroupLayout;
    }
return     proc(computePipeline, groupIndex);
}
static void ThreadDispatchComputePipelineSetLabel(WGPUComputePipeline computePipeline, char const * label) {
    auto* proc = perThreadProcs.computePipelineSetLabel;
    if (!proc) {
        proc = defaultProc.computePipelineSetLabel;
    }
    proc(computePipeline, label);
}
static void ThreadDispatchComputePipelineReference(WGPUComputePipeline computePipeline) {
    auto* proc = perThreadProcs.computePipelineReference;
    if (!proc) {
        proc = defaultProc.computePipelineReference;
    }
    proc(computePipeline);
}
static void ThreadDispatchComputePipelineRelease(WGPUComputePipeline computePipeline) {
    auto* proc = perThreadProcs.computePipelineRelease;
    if (!proc) {
        proc = defaultProc.computePipelineRelease;
    }
    proc(computePipeline);
}
static WGPUBindGroup ThreadDispatchDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateBindGroup;
    if (!proc) {
        proc = defaultProc.deviceCreateBindGroup;
    }
return     proc(device, descriptor);
}
static WGPUBindGroupLayout ThreadDispatchDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateBindGroupLayout;
    if (!proc) {
        proc = defaultProc.deviceCreateBindGroupLayout;
    }
return     proc(device, descriptor);
}
static WGPUBuffer ThreadDispatchDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateBuffer;
    if (!proc) {
        proc = defaultProc.deviceCreateBuffer;
    }
return     proc(device, descriptor);
}
static WGPUCommandEncoder ThreadDispatchDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateCommandEncoder;
    if (!proc) {
        proc = defaultProc.deviceCreateCommandEncoder;
    }
return     proc(device, descriptor);
}
static WGPUComputePipeline ThreadDispatchDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateComputePipeline;
    if (!proc) {
        proc = defaultProc.deviceCreateComputePipeline;
    }
return     proc(device, descriptor);
}
static void ThreadDispatchDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
    auto* proc = perThreadProcs.deviceCreateComputePipelineAsync;
    if (!proc) {
        proc = defaultProc.deviceCreateComputePipelineAsync;
    }
    proc(device, descriptor, callback, userdata);
}
static WGPUBuffer ThreadDispatchDeviceCreateErrorBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateErrorBuffer;
    if (!proc) {
        proc = defaultProc.deviceCreateErrorBuffer;
    }
return     proc(device, descriptor);
}
static WGPUExternalTexture ThreadDispatchDeviceCreateErrorExternalTexture(WGPUDevice device) {
    auto* proc = perThreadProcs.deviceCreateErrorExternalTexture;
    if (!proc) {
        proc = defaultProc.deviceCreateErrorExternalTexture;
    }
return     proc(device);
}
static WGPUShaderModule ThreadDispatchDeviceCreateErrorShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage) {
    auto* proc = perThreadProcs.deviceCreateErrorShaderModule;
    if (!proc) {
        proc = defaultProc.deviceCreateErrorShaderModule;
    }
return     proc(device, descriptor, errorMessage);
}
static WGPUTexture ThreadDispatchDeviceCreateErrorTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateErrorTexture;
    if (!proc) {
        proc = defaultProc.deviceCreateErrorTexture;
    }
return     proc(device, descriptor);
}
static WGPUExternalTexture ThreadDispatchDeviceCreateExternalTexture(WGPUDevice device, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
    auto* proc = perThreadProcs.deviceCreateExternalTexture;
    if (!proc) {
        proc = defaultProc.deviceCreateExternalTexture;
    }
return     proc(device, externalTextureDescriptor);
}
static WGPUPipelineLayout ThreadDispatchDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreatePipelineLayout;
    if (!proc) {
        proc = defaultProc.deviceCreatePipelineLayout;
    }
return     proc(device, descriptor);
}
static WGPUQuerySet ThreadDispatchDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateQuerySet;
    if (!proc) {
        proc = defaultProc.deviceCreateQuerySet;
    }
return     proc(device, descriptor);
}
static WGPURenderBundleEncoder ThreadDispatchDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateRenderBundleEncoder;
    if (!proc) {
        proc = defaultProc.deviceCreateRenderBundleEncoder;
    }
return     proc(device, descriptor);
}
static WGPURenderPipeline ThreadDispatchDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateRenderPipeline;
    if (!proc) {
        proc = defaultProc.deviceCreateRenderPipeline;
    }
return     proc(device, descriptor);
}
static void ThreadDispatchDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
    auto* proc = perThreadProcs.deviceCreateRenderPipelineAsync;
    if (!proc) {
        proc = defaultProc.deviceCreateRenderPipelineAsync;
    }
    proc(device, descriptor, callback, userdata);
}
static WGPUSampler ThreadDispatchDeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateSampler;
    if (!proc) {
        proc = defaultProc.deviceCreateSampler;
    }
return     proc(device, descriptor);
}
static WGPUShaderModule ThreadDispatchDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateShaderModule;
    if (!proc) {
        proc = defaultProc.deviceCreateShaderModule;
    }
return     proc(device, descriptor);
}
static WGPUSwapChain ThreadDispatchDeviceCreateSwapChain(WGPUDevice device, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateSwapChain;
    if (!proc) {
        proc = defaultProc.deviceCreateSwapChain;
    }
return     proc(device, surface, descriptor);
}
static WGPUTexture ThreadDispatchDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceCreateTexture;
    if (!proc) {
        proc = defaultProc.deviceCreateTexture;
    }
return     proc(device, descriptor);
}
static void ThreadDispatchDeviceDestroy(WGPUDevice device) {
    auto* proc = perThreadProcs.deviceDestroy;
    if (!proc) {
        proc = defaultProc.deviceDestroy;
    }
    proc(device);
}
static size_t ThreadDispatchDeviceEnumerateFeatures(WGPUDevice device, WGPUFeatureName * features) {
    auto* proc = perThreadProcs.deviceEnumerateFeatures;
    if (!proc) {
        proc = defaultProc.deviceEnumerateFeatures;
    }
return     proc(device, features);
}
static void ThreadDispatchDeviceForceLoss(WGPUDevice device, WGPUDeviceLostReason type, char const * message) {
    auto* proc = perThreadProcs.deviceForceLoss;
    if (!proc) {
        proc = defaultProc.deviceForceLoss;
    }
    proc(device, type, message);
}
static WGPUAdapter ThreadDispatchDeviceGetAdapter(WGPUDevice device) {
    auto* proc = perThreadProcs.deviceGetAdapter;
    if (!proc) {
        proc = defaultProc.deviceGetAdapter;
    }
return     proc(device);
}
static bool ThreadDispatchDeviceGetLimits(WGPUDevice device, WGPUSupportedLimits * limits) {
    auto* proc = perThreadProcs.deviceGetLimits;
    if (!proc) {
        proc = defaultProc.deviceGetLimits;
    }
return     proc(device, limits);
}
static WGPUQueue ThreadDispatchDeviceGetQueue(WGPUDevice device) {
    auto* proc = perThreadProcs.deviceGetQueue;
    if (!proc) {
        proc = defaultProc.deviceGetQueue;
    }
return     proc(device);
}
static WGPUTextureUsageFlags ThreadDispatchDeviceGetSupportedSurfaceUsage(WGPUDevice device, WGPUSurface surface) {
    auto* proc = perThreadProcs.deviceGetSupportedSurfaceUsage;
    if (!proc) {
        proc = defaultProc.deviceGetSupportedSurfaceUsage;
    }
return     proc(device, surface);
}
static bool ThreadDispatchDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature) {
    auto* proc = perThreadProcs.deviceHasFeature;
    if (!proc) {
        proc = defaultProc.deviceHasFeature;
    }
return     proc(device, feature);
}
static void ThreadDispatchDeviceInjectError(WGPUDevice device, WGPUErrorType type, char const * message) {
    auto* proc = perThreadProcs.deviceInjectError;
    if (!proc) {
        proc = defaultProc.deviceInjectError;
    }
    proc(device, type, message);
}
static void ThreadDispatchDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    auto* proc = perThreadProcs.devicePopErrorScope;
    if (!proc) {
        proc = defaultProc.devicePopErrorScope;
    }
    proc(device, callback, userdata);
}
static void ThreadDispatchDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) {
    auto* proc = perThreadProcs.devicePushErrorScope;
    if (!proc) {
        proc = defaultProc.devicePushErrorScope;
    }
    proc(device, filter);
}
static void ThreadDispatchDeviceSetDeviceLostCallback(WGPUDevice device, WGPUDeviceLostCallback callback, void * userdata) {
    auto* proc = perThreadProcs.deviceSetDeviceLostCallback;
    if (!proc) {
        proc = defaultProc.deviceSetDeviceLostCallback;
    }
    proc(device, callback, userdata);
}
static void ThreadDispatchDeviceSetLabel(WGPUDevice device, char const * label) {
    auto* proc = perThreadProcs.deviceSetLabel;
    if (!proc) {
        proc = defaultProc.deviceSetLabel;
    }
    proc(device, label);
}
static void ThreadDispatchDeviceSetLoggingCallback(WGPUDevice device, WGPULoggingCallback callback, void * userdata) {
    auto* proc = perThreadProcs.deviceSetLoggingCallback;
    if (!proc) {
        proc = defaultProc.deviceSetLoggingCallback;
    }
    proc(device, callback, userdata);
}
static void ThreadDispatchDeviceSetUncapturedErrorCallback(WGPUDevice device, WGPUErrorCallback callback, void * userdata) {
    auto* proc = perThreadProcs.deviceSetUncapturedErrorCallback;
    if (!proc) {
        proc = defaultProc.deviceSetUncapturedErrorCallback;
    }
    proc(device, callback, userdata);
}
static void ThreadDispatchDeviceTick(WGPUDevice device) {
    auto* proc = perThreadProcs.deviceTick;
    if (!proc) {
        proc = defaultProc.deviceTick;
    }
    proc(device);
}
static void ThreadDispatchDeviceValidateTextureDescriptor(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
    auto* proc = perThreadProcs.deviceValidateTextureDescriptor;
    if (!proc) {
        proc = defaultProc.deviceValidateTextureDescriptor;
    }
    proc(device, descriptor);
}
static void ThreadDispatchDeviceReference(WGPUDevice device) {
    auto* proc = perThreadProcs.deviceReference;
    if (!proc) {
        proc = defaultProc.deviceReference;
    }
    proc(device);
}
static void ThreadDispatchDeviceRelease(WGPUDevice device) {
    auto* proc = perThreadProcs.deviceRelease;
    if (!proc) {
        proc = defaultProc.deviceRelease;
    }
    proc(device);
}
static void ThreadDispatchExternalTextureDestroy(WGPUExternalTexture externalTexture) {
    auto* proc = perThreadProcs.externalTextureDestroy;
    if (!proc) {
        proc = defaultProc.externalTextureDestroy;
    }
    proc(externalTexture);
}
static void ThreadDispatchExternalTextureExpire(WGPUExternalTexture externalTexture) {
    auto* proc = perThreadProcs.externalTextureExpire;
    if (!proc) {
        proc = defaultProc.externalTextureExpire;
    }
    proc(externalTexture);
}
static void ThreadDispatchExternalTextureRefresh(WGPUExternalTexture externalTexture) {
    auto* proc = perThreadProcs.externalTextureRefresh;
    if (!proc) {
        proc = defaultProc.externalTextureRefresh;
    }
    proc(externalTexture);
}
static void ThreadDispatchExternalTextureSetLabel(WGPUExternalTexture externalTexture, char const * label) {
    auto* proc = perThreadProcs.externalTextureSetLabel;
    if (!proc) {
        proc = defaultProc.externalTextureSetLabel;
    }
    proc(externalTexture, label);
}
static void ThreadDispatchExternalTextureReference(WGPUExternalTexture externalTexture) {
    auto* proc = perThreadProcs.externalTextureReference;
    if (!proc) {
        proc = defaultProc.externalTextureReference;
    }
    proc(externalTexture);
}
static void ThreadDispatchExternalTextureRelease(WGPUExternalTexture externalTexture) {
    auto* proc = perThreadProcs.externalTextureRelease;
    if (!proc) {
        proc = defaultProc.externalTextureRelease;
    }
    proc(externalTexture);
}
static WGPUSurface ThreadDispatchInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) {
    auto* proc = perThreadProcs.instanceCreateSurface;
    if (!proc) {
        proc = defaultProc.instanceCreateSurface;
    }
return     proc(instance, descriptor);
}
static void ThreadDispatchInstanceProcessEvents(WGPUInstance instance) {
    auto* proc = perThreadProcs.instanceProcessEvents;
    if (!proc) {
        proc = defaultProc.instanceProcessEvents;
    }
    proc(instance);
}
static void ThreadDispatchInstanceRequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
    auto* proc = perThreadProcs.instanceRequestAdapter;
    if (!proc) {
        proc = defaultProc.instanceRequestAdapter;
    }
    proc(instance, options, callback, userdata);
}
static void ThreadDispatchInstanceReference(WGPUInstance instance) {
    auto* proc = perThreadProcs.instanceReference;
    if (!proc) {
        proc = defaultProc.instanceReference;
    }
    proc(instance);
}
static void ThreadDispatchInstanceRelease(WGPUInstance instance) {
    auto* proc = perThreadProcs.instanceRelease;
    if (!proc) {
        proc = defaultProc.instanceRelease;
    }
    proc(instance);
}
static void ThreadDispatchPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, char const * label) {
    auto* proc = perThreadProcs.pipelineLayoutSetLabel;
    if (!proc) {
        proc = defaultProc.pipelineLayoutSetLabel;
    }
    proc(pipelineLayout, label);
}
static void ThreadDispatchPipelineLayoutReference(WGPUPipelineLayout pipelineLayout) {
    auto* proc = perThreadProcs.pipelineLayoutReference;
    if (!proc) {
        proc = defaultProc.pipelineLayoutReference;
    }
    proc(pipelineLayout);
}
static void ThreadDispatchPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) {
    auto* proc = perThreadProcs.pipelineLayoutRelease;
    if (!proc) {
        proc = defaultProc.pipelineLayoutRelease;
    }
    proc(pipelineLayout);
}
static void ThreadDispatchQuerySetDestroy(WGPUQuerySet querySet) {
    auto* proc = perThreadProcs.querySetDestroy;
    if (!proc) {
        proc = defaultProc.querySetDestroy;
    }
    proc(querySet);
}
static uint32_t ThreadDispatchQuerySetGetCount(WGPUQuerySet querySet) {
    auto* proc = perThreadProcs.querySetGetCount;
    if (!proc) {
        proc = defaultProc.querySetGetCount;
    }
return     proc(querySet);
}
static WGPUQueryType ThreadDispatchQuerySetGetType(WGPUQuerySet querySet) {
    auto* proc = perThreadProcs.querySetGetType;
    if (!proc) {
        proc = defaultProc.querySetGetType;
    }
return     proc(querySet);
}
static void ThreadDispatchQuerySetSetLabel(WGPUQuerySet querySet, char const * label) {
    auto* proc = perThreadProcs.querySetSetLabel;
    if (!proc) {
        proc = defaultProc.querySetSetLabel;
    }
    proc(querySet, label);
}
static void ThreadDispatchQuerySetReference(WGPUQuerySet querySet) {
    auto* proc = perThreadProcs.querySetReference;
    if (!proc) {
        proc = defaultProc.querySetReference;
    }
    proc(querySet);
}
static void ThreadDispatchQuerySetRelease(WGPUQuerySet querySet) {
    auto* proc = perThreadProcs.querySetRelease;
    if (!proc) {
        proc = defaultProc.querySetRelease;
    }
    proc(querySet);
}
static void ThreadDispatchQueueCopyExternalTextureForBrowser(WGPUQueue queue, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
    auto* proc = perThreadProcs.queueCopyExternalTextureForBrowser;
    if (!proc) {
        proc = defaultProc.queueCopyExternalTextureForBrowser;
    }
    proc(queue, source, destination, copySize, options);
}
static void ThreadDispatchQueueCopyTextureForBrowser(WGPUQueue queue, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
    auto* proc = perThreadProcs.queueCopyTextureForBrowser;
    if (!proc) {
        proc = defaultProc.queueCopyTextureForBrowser;
    }
    proc(queue, source, destination, copySize, options);
}
static void ThreadDispatchQueueOnSubmittedWorkDone(WGPUQueue queue, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
    auto* proc = perThreadProcs.queueOnSubmittedWorkDone;
    if (!proc) {
        proc = defaultProc.queueOnSubmittedWorkDone;
    }
    proc(queue, signalValue, callback, userdata);
}
static void ThreadDispatchQueueSetLabel(WGPUQueue queue, char const * label) {
    auto* proc = perThreadProcs.queueSetLabel;
    if (!proc) {
        proc = defaultProc.queueSetLabel;
    }
    proc(queue, label);
}
static void ThreadDispatchQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) {
    auto* proc = perThreadProcs.queueSubmit;
    if (!proc) {
        proc = defaultProc.queueSubmit;
    }
    proc(queue, commandCount, commands);
}
static void ThreadDispatchQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
    auto* proc = perThreadProcs.queueWriteBuffer;
    if (!proc) {
        proc = defaultProc.queueWriteBuffer;
    }
    proc(queue, buffer, bufferOffset, data, size);
}
static void ThreadDispatchQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
    auto* proc = perThreadProcs.queueWriteTexture;
    if (!proc) {
        proc = defaultProc.queueWriteTexture;
    }
    proc(queue, destination, data, dataSize, dataLayout, writeSize);
}
static void ThreadDispatchQueueReference(WGPUQueue queue) {
    auto* proc = perThreadProcs.queueReference;
    if (!proc) {
        proc = defaultProc.queueReference;
    }
    proc(queue);
}
static void ThreadDispatchQueueRelease(WGPUQueue queue) {
    auto* proc = perThreadProcs.queueRelease;
    if (!proc) {
        proc = defaultProc.queueRelease;
    }
    proc(queue);
}
static void ThreadDispatchRenderBundleSetLabel(WGPURenderBundle renderBundle, char const * label) {
    auto* proc = perThreadProcs.renderBundleSetLabel;
    if (!proc) {
        proc = defaultProc.renderBundleSetLabel;
    }
    proc(renderBundle, label);
}
static void ThreadDispatchRenderBundleReference(WGPURenderBundle renderBundle) {
    auto* proc = perThreadProcs.renderBundleReference;
    if (!proc) {
        proc = defaultProc.renderBundleReference;
    }
    proc(renderBundle);
}
static void ThreadDispatchRenderBundleRelease(WGPURenderBundle renderBundle) {
    auto* proc = perThreadProcs.renderBundleRelease;
    if (!proc) {
        proc = defaultProc.renderBundleRelease;
    }
    proc(renderBundle);
}
static void ThreadDispatchRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    auto* proc = perThreadProcs.renderBundleEncoderDraw;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderDraw;
    }
    proc(renderBundleEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void ThreadDispatchRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    auto* proc = perThreadProcs.renderBundleEncoderDrawIndexed;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderDrawIndexed;
    }
    proc(renderBundleEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void ThreadDispatchRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    auto* proc = perThreadProcs.renderBundleEncoderDrawIndexedIndirect;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderDrawIndexedIndirect;
    }
    proc(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    auto* proc = perThreadProcs.renderBundleEncoderDrawIndirect;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderDrawIndirect;
    }
    proc(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static WGPURenderBundle ThreadDispatchRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderBundleDescriptor const * descriptor) {
    auto* proc = perThreadProcs.renderBundleEncoderFinish;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderFinish;
    }
return     proc(renderBundleEncoder, descriptor);
}
static void ThreadDispatchRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel) {
    auto* proc = perThreadProcs.renderBundleEncoderInsertDebugMarker;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderInsertDebugMarker;
    }
    proc(renderBundleEncoder, markerLabel);
}
static void ThreadDispatchRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) {
    auto* proc = perThreadProcs.renderBundleEncoderPopDebugGroup;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderPopDebugGroup;
    }
    proc(renderBundleEncoder);
}
static void ThreadDispatchRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel) {
    auto* proc = perThreadProcs.renderBundleEncoderPushDebugGroup;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderPushDebugGroup;
    }
    proc(renderBundleEncoder, groupLabel);
}
static void ThreadDispatchRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    auto* proc = perThreadProcs.renderBundleEncoderSetBindGroup;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderSetBindGroup;
    }
    proc(renderBundleEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    auto* proc = perThreadProcs.renderBundleEncoderSetIndexBuffer;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderSetIndexBuffer;
    }
    proc(renderBundleEncoder, buffer, format, offset, size);
}
static void ThreadDispatchRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, char const * label) {
    auto* proc = perThreadProcs.renderBundleEncoderSetLabel;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderSetLabel;
    }
    proc(renderBundleEncoder, label);
}
static void ThreadDispatchRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) {
    auto* proc = perThreadProcs.renderBundleEncoderSetPipeline;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderSetPipeline;
    }
    proc(renderBundleEncoder, pipeline);
}
static void ThreadDispatchRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    auto* proc = perThreadProcs.renderBundleEncoderSetVertexBuffer;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderSetVertexBuffer;
    }
    proc(renderBundleEncoder, slot, buffer, offset, size);
}
static void ThreadDispatchRenderBundleEncoderReference(WGPURenderBundleEncoder renderBundleEncoder) {
    auto* proc = perThreadProcs.renderBundleEncoderReference;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderReference;
    }
    proc(renderBundleEncoder);
}
static void ThreadDispatchRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) {
    auto* proc = perThreadProcs.renderBundleEncoderRelease;
    if (!proc) {
        proc = defaultProc.renderBundleEncoderRelease;
    }
    proc(renderBundleEncoder);
}
static void ThreadDispatchRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) {
    auto* proc = perThreadProcs.renderPassEncoderBeginOcclusionQuery;
    if (!proc) {
        proc = defaultProc.renderPassEncoderBeginOcclusionQuery;
    }
    proc(renderPassEncoder, queryIndex);
}
static void ThreadDispatchRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    auto* proc = perThreadProcs.renderPassEncoderDraw;
    if (!proc) {
        proc = defaultProc.renderPassEncoderDraw;
    }
    proc(renderPassEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void ThreadDispatchRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    auto* proc = perThreadProcs.renderPassEncoderDrawIndexed;
    if (!proc) {
        proc = defaultProc.renderPassEncoderDrawIndexed;
    }
    proc(renderPassEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void ThreadDispatchRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    auto* proc = perThreadProcs.renderPassEncoderDrawIndexedIndirect;
    if (!proc) {
        proc = defaultProc.renderPassEncoderDrawIndexedIndirect;
    }
    proc(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    auto* proc = perThreadProcs.renderPassEncoderDrawIndirect;
    if (!proc) {
        proc = defaultProc.renderPassEncoderDrawIndirect;
    }
    proc(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void ThreadDispatchRenderPassEncoderEnd(WGPURenderPassEncoder renderPassEncoder) {
    auto* proc = perThreadProcs.renderPassEncoderEnd;
    if (!proc) {
        proc = defaultProc.renderPassEncoderEnd;
    }
    proc(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder renderPassEncoder) {
    auto* proc = perThreadProcs.renderPassEncoderEndOcclusionQuery;
    if (!proc) {
        proc = defaultProc.renderPassEncoderEndOcclusionQuery;
    }
    proc(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) {
    auto* proc = perThreadProcs.renderPassEncoderExecuteBundles;
    if (!proc) {
        proc = defaultProc.renderPassEncoderExecuteBundles;
    }
    proc(renderPassEncoder, bundleCount, bundles);
}
static void ThreadDispatchRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const * markerLabel) {
    auto* proc = perThreadProcs.renderPassEncoderInsertDebugMarker;
    if (!proc) {
        proc = defaultProc.renderPassEncoderInsertDebugMarker;
    }
    proc(renderPassEncoder, markerLabel);
}
static void ThreadDispatchRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) {
    auto* proc = perThreadProcs.renderPassEncoderPopDebugGroup;
    if (!proc) {
        proc = defaultProc.renderPassEncoderPopDebugGroup;
    }
    proc(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel) {
    auto* proc = perThreadProcs.renderPassEncoderPushDebugGroup;
    if (!proc) {
        proc = defaultProc.renderPassEncoderPushDebugGroup;
    }
    proc(renderPassEncoder, groupLabel);
}
static void ThreadDispatchRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    auto* proc = perThreadProcs.renderPassEncoderSetBindGroup;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetBindGroup;
    }
    proc(renderPassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void ThreadDispatchRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) {
    auto* proc = perThreadProcs.renderPassEncoderSetBlendConstant;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetBlendConstant;
    }
    proc(renderPassEncoder, color);
}
static void ThreadDispatchRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    auto* proc = perThreadProcs.renderPassEncoderSetIndexBuffer;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetIndexBuffer;
    }
    proc(renderPassEncoder, buffer, format, offset, size);
}
static void ThreadDispatchRenderPassEncoderSetLabel(WGPURenderPassEncoder renderPassEncoder, char const * label) {
    auto* proc = perThreadProcs.renderPassEncoderSetLabel;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetLabel;
    }
    proc(renderPassEncoder, label);
}
static void ThreadDispatchRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) {
    auto* proc = perThreadProcs.renderPassEncoderSetPipeline;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetPipeline;
    }
    proc(renderPassEncoder, pipeline);
}
static void ThreadDispatchRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    auto* proc = perThreadProcs.renderPassEncoderSetScissorRect;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetScissorRect;
    }
    proc(renderPassEncoder, x, y, width, height);
}
static void ThreadDispatchRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) {
    auto* proc = perThreadProcs.renderPassEncoderSetStencilReference;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetStencilReference;
    }
    proc(renderPassEncoder, reference);
}
static void ThreadDispatchRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    auto* proc = perThreadProcs.renderPassEncoderSetVertexBuffer;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetVertexBuffer;
    }
    proc(renderPassEncoder, slot, buffer, offset, size);
}
static void ThreadDispatchRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) {
    auto* proc = perThreadProcs.renderPassEncoderSetViewport;
    if (!proc) {
        proc = defaultProc.renderPassEncoderSetViewport;
    }
    proc(renderPassEncoder, x, y, width, height, minDepth, maxDepth);
}
static void ThreadDispatchRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    auto* proc = perThreadProcs.renderPassEncoderWriteTimestamp;
    if (!proc) {
        proc = defaultProc.renderPassEncoderWriteTimestamp;
    }
    proc(renderPassEncoder, querySet, queryIndex);
}
static void ThreadDispatchRenderPassEncoderReference(WGPURenderPassEncoder renderPassEncoder) {
    auto* proc = perThreadProcs.renderPassEncoderReference;
    if (!proc) {
        proc = defaultProc.renderPassEncoderReference;
    }
    proc(renderPassEncoder);
}
static void ThreadDispatchRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) {
    auto* proc = perThreadProcs.renderPassEncoderRelease;
    if (!proc) {
        proc = defaultProc.renderPassEncoderRelease;
    }
    proc(renderPassEncoder);
}
static WGPUBindGroupLayout ThreadDispatchRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) {
    auto* proc = perThreadProcs.renderPipelineGetBindGroupLayout;
    if (!proc) {
        proc = defaultProc.renderPipelineGetBindGroupLayout;
    }
return     proc(renderPipeline, groupIndex);
}
static void ThreadDispatchRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, char const * label) {
    auto* proc = perThreadProcs.renderPipelineSetLabel;
    if (!proc) {
        proc = defaultProc.renderPipelineSetLabel;
    }
    proc(renderPipeline, label);
}
static void ThreadDispatchRenderPipelineReference(WGPURenderPipeline renderPipeline) {
    auto* proc = perThreadProcs.renderPipelineReference;
    if (!proc) {
        proc = defaultProc.renderPipelineReference;
    }
    proc(renderPipeline);
}
static void ThreadDispatchRenderPipelineRelease(WGPURenderPipeline renderPipeline) {
    auto* proc = perThreadProcs.renderPipelineRelease;
    if (!proc) {
        proc = defaultProc.renderPipelineRelease;
    }
    proc(renderPipeline);
}
static void ThreadDispatchSamplerSetLabel(WGPUSampler sampler, char const * label) {
    auto* proc = perThreadProcs.samplerSetLabel;
    if (!proc) {
        proc = defaultProc.samplerSetLabel;
    }
    proc(sampler, label);
}
static void ThreadDispatchSamplerReference(WGPUSampler sampler) {
    auto* proc = perThreadProcs.samplerReference;
    if (!proc) {
        proc = defaultProc.samplerReference;
    }
    proc(sampler);
}
static void ThreadDispatchSamplerRelease(WGPUSampler sampler) {
    auto* proc = perThreadProcs.samplerRelease;
    if (!proc) {
        proc = defaultProc.samplerRelease;
    }
    proc(sampler);
}
static void ThreadDispatchShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule, WGPUCompilationInfoCallback callback, void * userdata) {
    auto* proc = perThreadProcs.shaderModuleGetCompilationInfo;
    if (!proc) {
        proc = defaultProc.shaderModuleGetCompilationInfo;
    }
    proc(shaderModule, callback, userdata);
}
static void ThreadDispatchShaderModuleSetLabel(WGPUShaderModule shaderModule, char const * label) {
    auto* proc = perThreadProcs.shaderModuleSetLabel;
    if (!proc) {
        proc = defaultProc.shaderModuleSetLabel;
    }
    proc(shaderModule, label);
}
static void ThreadDispatchShaderModuleReference(WGPUShaderModule shaderModule) {
    auto* proc = perThreadProcs.shaderModuleReference;
    if (!proc) {
        proc = defaultProc.shaderModuleReference;
    }
    proc(shaderModule);
}
static void ThreadDispatchShaderModuleRelease(WGPUShaderModule shaderModule) {
    auto* proc = perThreadProcs.shaderModuleRelease;
    if (!proc) {
        proc = defaultProc.shaderModuleRelease;
    }
    proc(shaderModule);
}
static void ThreadDispatchSurfaceReference(WGPUSurface surface) {
    auto* proc = perThreadProcs.surfaceReference;
    if (!proc) {
        proc = defaultProc.surfaceReference;
    }
    proc(surface);
}
static void ThreadDispatchSurfaceRelease(WGPUSurface surface) {
    auto* proc = perThreadProcs.surfaceRelease;
    if (!proc) {
        proc = defaultProc.surfaceRelease;
    }
    proc(surface);
}
static WGPUTexture ThreadDispatchSwapChainGetCurrentTexture(WGPUSwapChain swapChain) {
    auto* proc = perThreadProcs.swapChainGetCurrentTexture;
    if (!proc) {
        proc = defaultProc.swapChainGetCurrentTexture;
    }
return     proc(swapChain);
}
static WGPUTextureView ThreadDispatchSwapChainGetCurrentTextureView(WGPUSwapChain swapChain) {
    auto* proc = perThreadProcs.swapChainGetCurrentTextureView;
    if (!proc) {
        proc = defaultProc.swapChainGetCurrentTextureView;
    }
return     proc(swapChain);
}
static void ThreadDispatchSwapChainPresent(WGPUSwapChain swapChain) {
    auto* proc = perThreadProcs.swapChainPresent;
    if (!proc) {
        proc = defaultProc.swapChainPresent;
    }
    proc(swapChain);
}
static void ThreadDispatchSwapChainReference(WGPUSwapChain swapChain) {
    auto* proc = perThreadProcs.swapChainReference;
    if (!proc) {
        proc = defaultProc.swapChainReference;
    }
    proc(swapChain);
}
static void ThreadDispatchSwapChainRelease(WGPUSwapChain swapChain) {
    auto* proc = perThreadProcs.swapChainRelease;
    if (!proc) {
        proc = defaultProc.swapChainRelease;
    }
    proc(swapChain);
}
static WGPUTextureView ThreadDispatchTextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor) {
    auto* proc = perThreadProcs.textureCreateView;
    if (!proc) {
        proc = defaultProc.textureCreateView;
    }
return     proc(texture, descriptor);
}
static void ThreadDispatchTextureDestroy(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureDestroy;
    if (!proc) {
        proc = defaultProc.textureDestroy;
    }
    proc(texture);
}
static uint32_t ThreadDispatchTextureGetDepthOrArrayLayers(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetDepthOrArrayLayers;
    if (!proc) {
        proc = defaultProc.textureGetDepthOrArrayLayers;
    }
return     proc(texture);
}
static WGPUTextureDimension ThreadDispatchTextureGetDimension(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetDimension;
    if (!proc) {
        proc = defaultProc.textureGetDimension;
    }
return     proc(texture);
}
static WGPUTextureFormat ThreadDispatchTextureGetFormat(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetFormat;
    if (!proc) {
        proc = defaultProc.textureGetFormat;
    }
return     proc(texture);
}
static uint32_t ThreadDispatchTextureGetHeight(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetHeight;
    if (!proc) {
        proc = defaultProc.textureGetHeight;
    }
return     proc(texture);
}
static uint32_t ThreadDispatchTextureGetMipLevelCount(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetMipLevelCount;
    if (!proc) {
        proc = defaultProc.textureGetMipLevelCount;
    }
return     proc(texture);
}
static uint32_t ThreadDispatchTextureGetSampleCount(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetSampleCount;
    if (!proc) {
        proc = defaultProc.textureGetSampleCount;
    }
return     proc(texture);
}
static WGPUTextureUsageFlags ThreadDispatchTextureGetUsage(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetUsage;
    if (!proc) {
        proc = defaultProc.textureGetUsage;
    }
return     proc(texture);
}
static uint32_t ThreadDispatchTextureGetWidth(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureGetWidth;
    if (!proc) {
        proc = defaultProc.textureGetWidth;
    }
return     proc(texture);
}
static void ThreadDispatchTextureSetLabel(WGPUTexture texture, char const * label) {
    auto* proc = perThreadProcs.textureSetLabel;
    if (!proc) {
        proc = defaultProc.textureSetLabel;
    }
    proc(texture, label);
}
static void ThreadDispatchTextureReference(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureReference;
    if (!proc) {
        proc = defaultProc.textureReference;
    }
    proc(texture);
}
static void ThreadDispatchTextureRelease(WGPUTexture texture) {
    auto* proc = perThreadProcs.textureRelease;
    if (!proc) {
        proc = defaultProc.textureRelease;
    }
    proc(texture);
}
static void ThreadDispatchTextureViewSetLabel(WGPUTextureView textureView, char const * label) {
    auto* proc = perThreadProcs.textureViewSetLabel;
    if (!proc) {
        proc = defaultProc.textureViewSetLabel;
    }
    proc(textureView, label);
}
static void ThreadDispatchTextureViewReference(WGPUTextureView textureView) {
    auto* proc = perThreadProcs.textureViewReference;
    if (!proc) {
        proc = defaultProc.textureViewReference;
    }
    proc(textureView);
}
static void ThreadDispatchTextureViewRelease(WGPUTextureView textureView) {
    auto* proc = perThreadProcs.textureViewRelease;
    if (!proc) {
        proc = defaultProc.textureViewRelease;
    }
    proc(textureView);
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
