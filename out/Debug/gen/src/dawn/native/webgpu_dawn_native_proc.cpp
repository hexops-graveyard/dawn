// Copyright 2021 The Dawn Authors
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

#include "dawn/webgpu.h"

namespace dawn::native {

// This file should be kept in sync with generator/templates/dawn/native/ProcTable.cpp

extern WGPUInstance NativeCreateInstance(WGPUInstanceDescriptor const * descriptor);
extern WGPUProc NativeGetProcAddress(WGPUDevice device, char const * procName);
extern WGPUDevice NativeAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor);
extern size_t NativeAdapterEnumerateFeatures(WGPUAdapter cSelf, WGPUFeatureName * features);
extern WGPUInstance NativeAdapterGetInstance(WGPUAdapter cSelf);
extern bool NativeAdapterGetLimits(WGPUAdapter cSelf, WGPUSupportedLimits * limits);
extern void NativeAdapterGetProperties(WGPUAdapter cSelf, WGPUAdapterProperties * properties);
extern bool NativeAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature);
extern void NativeAdapterRequestDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata);
extern void NativeAdapterReference(WGPUAdapter cSelf);
extern void NativeAdapterRelease(WGPUAdapter cSelf);
extern void NativeBindGroupSetLabel(WGPUBindGroup cSelf, char const * label);
extern void NativeBindGroupReference(WGPUBindGroup cSelf);
extern void NativeBindGroupRelease(WGPUBindGroup cSelf);
extern void NativeBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, char const * label);
extern void NativeBindGroupLayoutReference(WGPUBindGroupLayout cSelf);
extern void NativeBindGroupLayoutRelease(WGPUBindGroupLayout cSelf);
extern void NativeBufferDestroy(WGPUBuffer cSelf);
extern void const * NativeBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size);
extern WGPUBufferMapState NativeBufferGetMapState(WGPUBuffer cSelf);
extern void * NativeBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size);
extern uint64_t NativeBufferGetSize(WGPUBuffer cSelf);
extern WGPUBufferUsageFlags NativeBufferGetUsage(WGPUBuffer cSelf);
extern void NativeBufferMapAsync(WGPUBuffer cSelf, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata);
extern void NativeBufferSetLabel(WGPUBuffer cSelf, char const * label);
extern void NativeBufferUnmap(WGPUBuffer cSelf);
extern void NativeBufferReference(WGPUBuffer cSelf);
extern void NativeBufferRelease(WGPUBuffer cSelf);
extern void NativeCommandBufferSetLabel(WGPUCommandBuffer cSelf, char const * label);
extern void NativeCommandBufferReference(WGPUCommandBuffer cSelf);
extern void NativeCommandBufferRelease(WGPUCommandBuffer cSelf);
extern WGPUComputePassEncoder NativeCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor);
extern WGPURenderPassEncoder NativeCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor);
extern void NativeCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size);
extern void NativeCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
extern void NativeCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
extern void NativeCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize);
extern void NativeCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
extern void NativeCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
extern WGPUCommandBuffer NativeCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor);
extern void NativeCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, char const * message);
extern void NativeCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel);
extern void NativeCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf);
extern void NativeCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel);
extern void NativeCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset);
extern void NativeCommandEncoderSetLabel(WGPUCommandEncoder cSelf, char const * label);
extern void NativeCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size);
extern void NativeCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex);
extern void NativeCommandEncoderReference(WGPUCommandEncoder cSelf);
extern void NativeCommandEncoderRelease(WGPUCommandEncoder cSelf);
extern void NativeComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder cSelf, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ);
extern void NativeComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeComputePassEncoderEnd(WGPUComputePassEncoder cSelf);
extern void NativeComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel);
extern void NativeComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf);
extern void NativeComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel);
extern void NativeComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
extern void NativeComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, char const * label);
extern void NativeComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline);
extern void NativeComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex);
extern void NativeComputePassEncoderReference(WGPUComputePassEncoder cSelf);
extern void NativeComputePassEncoderRelease(WGPUComputePassEncoder cSelf);
extern WGPUBindGroupLayout NativeComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex);
extern void NativeComputePipelineSetLabel(WGPUComputePipeline cSelf, char const * label);
extern void NativeComputePipelineReference(WGPUComputePipeline cSelf);
extern void NativeComputePipelineRelease(WGPUComputePipeline cSelf);
extern WGPUBindGroup NativeDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor);
extern WGPUBindGroupLayout NativeDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor);
extern WGPUBuffer NativeDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor);
extern WGPUCommandEncoder NativeDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor);
extern WGPUComputePipeline NativeDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor);
extern void NativeDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata);
extern WGPUBuffer NativeDeviceCreateErrorBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor);
extern WGPUExternalTexture NativeDeviceCreateErrorExternalTexture(WGPUDevice cSelf);
extern WGPUShaderModule NativeDeviceCreateErrorShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage);
extern WGPUTexture NativeDeviceCreateErrorTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor);
extern WGPUExternalTexture NativeDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor);
extern WGPUPipelineLayout NativeDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor);
extern WGPUQuerySet NativeDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor);
extern WGPURenderBundleEncoder NativeDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor);
extern WGPURenderPipeline NativeDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor);
extern void NativeDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata);
extern WGPUSampler NativeDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor);
extern WGPUShaderModule NativeDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor);
extern WGPUSwapChain NativeDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor);
extern WGPUTexture NativeDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor);
extern void NativeDeviceDestroy(WGPUDevice cSelf);
extern size_t NativeDeviceEnumerateFeatures(WGPUDevice cSelf, WGPUFeatureName * features);
extern void NativeDeviceForceLoss(WGPUDevice cSelf, WGPUDeviceLostReason type, char const * message);
extern WGPUAdapter NativeDeviceGetAdapter(WGPUDevice cSelf);
extern bool NativeDeviceGetLimits(WGPUDevice cSelf, WGPUSupportedLimits * limits);
extern WGPUQueue NativeDeviceGetQueue(WGPUDevice cSelf);
extern WGPUTextureUsageFlags NativeDeviceGetSupportedSurfaceUsage(WGPUDevice cSelf, WGPUSurface surface);
extern bool NativeDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature);
extern void NativeDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message);
extern void NativeDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata);
extern void NativeDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter);
extern void NativeDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata);
extern void NativeDeviceSetLabel(WGPUDevice cSelf, char const * label);
extern void NativeDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallback callback, void * userdata);
extern void NativeDeviceSetUncapturedErrorCallback(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata);
extern void NativeDeviceTick(WGPUDevice cSelf);
extern void NativeDeviceValidateTextureDescriptor(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor);
extern void NativeDeviceReference(WGPUDevice cSelf);
extern void NativeDeviceRelease(WGPUDevice cSelf);
extern void NativeExternalTextureDestroy(WGPUExternalTexture cSelf);
extern void NativeExternalTextureExpire(WGPUExternalTexture cSelf);
extern void NativeExternalTextureRefresh(WGPUExternalTexture cSelf);
extern void NativeExternalTextureSetLabel(WGPUExternalTexture cSelf, char const * label);
extern void NativeExternalTextureReference(WGPUExternalTexture cSelf);
extern void NativeExternalTextureRelease(WGPUExternalTexture cSelf);
extern WGPUSurface NativeInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor);
extern void NativeInstanceProcessEvents(WGPUInstance cSelf);
extern void NativeInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata);
extern void NativeInstanceReference(WGPUInstance cSelf);
extern void NativeInstanceRelease(WGPUInstance cSelf);
extern void NativePipelineLayoutSetLabel(WGPUPipelineLayout cSelf, char const * label);
extern void NativePipelineLayoutReference(WGPUPipelineLayout cSelf);
extern void NativePipelineLayoutRelease(WGPUPipelineLayout cSelf);
extern void NativeQuerySetDestroy(WGPUQuerySet cSelf);
extern uint32_t NativeQuerySetGetCount(WGPUQuerySet cSelf);
extern WGPUQueryType NativeQuerySetGetType(WGPUQuerySet cSelf);
extern void NativeQuerySetSetLabel(WGPUQuerySet cSelf, char const * label);
extern void NativeQuerySetReference(WGPUQuerySet cSelf);
extern void NativeQuerySetRelease(WGPUQuerySet cSelf);
extern void NativeQueueCopyExternalTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options);
extern void NativeQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options);
extern void NativeQueueOnSubmittedWorkDone(WGPUQueue cSelf, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata);
extern void NativeQueueSetLabel(WGPUQueue cSelf, char const * label);
extern void NativeQueueSubmit(WGPUQueue cSelf, size_t commandCount, WGPUCommandBuffer const * commands);
extern void NativeQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size);
extern void NativeQueueWriteTexture(WGPUQueue cSelf, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize);
extern void NativeQueueReference(WGPUQueue cSelf);
extern void NativeQueueRelease(WGPUQueue cSelf);
extern void NativeRenderBundleSetLabel(WGPURenderBundle cSelf, char const * label);
extern void NativeRenderBundleReference(WGPURenderBundle cSelf);
extern void NativeRenderBundleRelease(WGPURenderBundle cSelf);
extern void NativeRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
extern void NativeRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
extern void NativeRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern WGPURenderBundle NativeRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor);
extern void NativeRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel);
extern void NativeRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf);
extern void NativeRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel);
extern void NativeRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
extern void NativeRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
extern void NativeRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, char const * label);
extern void NativeRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline);
extern void NativeRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
extern void NativeRenderBundleEncoderReference(WGPURenderBundleEncoder cSelf);
extern void NativeRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf);
extern void NativeRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex);
extern void NativeRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
extern void NativeRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
extern void NativeRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeRenderPassEncoderEnd(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, size_t bundleCount, WGPURenderBundle const * bundles);
extern void NativeRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel);
extern void NativeRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel);
extern void NativeRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
extern void NativeRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color);
extern void NativeRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
extern void NativeRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, char const * label);
extern void NativeRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline);
extern void NativeRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
extern void NativeRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference);
extern void NativeRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
extern void NativeRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth);
extern void NativeRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex);
extern void NativeRenderPassEncoderReference(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderRelease(WGPURenderPassEncoder cSelf);
extern WGPUBindGroupLayout NativeRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex);
extern void NativeRenderPipelineSetLabel(WGPURenderPipeline cSelf, char const * label);
extern void NativeRenderPipelineReference(WGPURenderPipeline cSelf);
extern void NativeRenderPipelineRelease(WGPURenderPipeline cSelf);
extern void NativeSamplerSetLabel(WGPUSampler cSelf, char const * label);
extern void NativeSamplerReference(WGPUSampler cSelf);
extern void NativeSamplerRelease(WGPUSampler cSelf);
extern void NativeShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallback callback, void * userdata);
extern void NativeShaderModuleSetLabel(WGPUShaderModule cSelf, char const * label);
extern void NativeShaderModuleReference(WGPUShaderModule cSelf);
extern void NativeShaderModuleRelease(WGPUShaderModule cSelf);
extern void NativeSurfaceReference(WGPUSurface cSelf);
extern void NativeSurfaceRelease(WGPUSurface cSelf);
extern WGPUTexture NativeSwapChainGetCurrentTexture(WGPUSwapChain cSelf);
extern WGPUTextureView NativeSwapChainGetCurrentTextureView(WGPUSwapChain cSelf);
extern void NativeSwapChainPresent(WGPUSwapChain cSelf);
extern void NativeSwapChainReference(WGPUSwapChain cSelf);
extern void NativeSwapChainRelease(WGPUSwapChain cSelf);
extern WGPUTextureView NativeTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor);
extern void NativeTextureDestroy(WGPUTexture cSelf);
extern uint32_t NativeTextureGetDepthOrArrayLayers(WGPUTexture cSelf);
extern WGPUTextureDimension NativeTextureGetDimension(WGPUTexture cSelf);
extern WGPUTextureFormat NativeTextureGetFormat(WGPUTexture cSelf);
extern uint32_t NativeTextureGetHeight(WGPUTexture cSelf);
extern uint32_t NativeTextureGetMipLevelCount(WGPUTexture cSelf);
extern uint32_t NativeTextureGetSampleCount(WGPUTexture cSelf);
extern WGPUTextureUsageFlags NativeTextureGetUsage(WGPUTexture cSelf);
extern uint32_t NativeTextureGetWidth(WGPUTexture cSelf);
extern void NativeTextureSetLabel(WGPUTexture cSelf, char const * label);
extern void NativeTextureReference(WGPUTexture cSelf);
extern void NativeTextureRelease(WGPUTexture cSelf);
extern void NativeTextureViewSetLabel(WGPUTextureView cSelf, char const * label);
extern void NativeTextureViewReference(WGPUTextureView cSelf);
extern void NativeTextureViewRelease(WGPUTextureView cSelf);

}

extern "C" {
    using namespace dawn::native;

    WGPUInstance wgpuCreateInstance (WGPUInstanceDescriptor const * descriptor) {
        return NativeCreateInstance(descriptor);
    }
    WGPUProc wgpuGetProcAddress (WGPUDevice device, char const * procName) {
        return NativeGetProcAddress(device, procName);
    }

    WGPUDevice wgpuAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor) {
        return NativeAdapterCreateDevice(
            cSelf, descriptor);
    }
    size_t wgpuAdapterEnumerateFeatures(WGPUAdapter cSelf, WGPUFeatureName * features) {
        return NativeAdapterEnumerateFeatures(
            cSelf, features);
    }
    WGPUInstance wgpuAdapterGetInstance(WGPUAdapter cSelf) {
        return NativeAdapterGetInstance(
            cSelf);
    }
    bool wgpuAdapterGetLimits(WGPUAdapter cSelf, WGPUSupportedLimits * limits) {
        return NativeAdapterGetLimits(
            cSelf, limits);
    }
    void wgpuAdapterGetProperties(WGPUAdapter cSelf, WGPUAdapterProperties * properties) {
        return NativeAdapterGetProperties(
            cSelf, properties);
    }
    bool wgpuAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature) {
        return NativeAdapterHasFeature(
            cSelf, feature);
    }
    void wgpuAdapterRequestDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata) {
        return NativeAdapterRequestDevice(
            cSelf, descriptor, callback, userdata);
    }
    void wgpuAdapterReference(WGPUAdapter cSelf) {
        return NativeAdapterReference(
            cSelf);
    }
    void wgpuAdapterRelease(WGPUAdapter cSelf) {
        return NativeAdapterRelease(
            cSelf);
    }
    void wgpuBindGroupSetLabel(WGPUBindGroup cSelf, char const * label) {
        return NativeBindGroupSetLabel(
            cSelf, label);
    }
    void wgpuBindGroupReference(WGPUBindGroup cSelf) {
        return NativeBindGroupReference(
            cSelf);
    }
    void wgpuBindGroupRelease(WGPUBindGroup cSelf) {
        return NativeBindGroupRelease(
            cSelf);
    }
    void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, char const * label) {
        return NativeBindGroupLayoutSetLabel(
            cSelf, label);
    }
    void wgpuBindGroupLayoutReference(WGPUBindGroupLayout cSelf) {
        return NativeBindGroupLayoutReference(
            cSelf);
    }
    void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout cSelf) {
        return NativeBindGroupLayoutRelease(
            cSelf);
    }
    void wgpuBufferDestroy(WGPUBuffer cSelf) {
        return NativeBufferDestroy(
            cSelf);
    }
    void const * wgpuBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        return NativeBufferGetConstMappedRange(
            cSelf, offset, size);
    }
    WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer cSelf) {
        return NativeBufferGetMapState(
            cSelf);
    }
    void * wgpuBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        return NativeBufferGetMappedRange(
            cSelf, offset, size);
    }
    uint64_t wgpuBufferGetSize(WGPUBuffer cSelf) {
        return NativeBufferGetSize(
            cSelf);
    }
    WGPUBufferUsageFlags wgpuBufferGetUsage(WGPUBuffer cSelf) {
        return NativeBufferGetUsage(
            cSelf);
    }
    void wgpuBufferMapAsync(WGPUBuffer cSelf, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
        return NativeBufferMapAsync(
            cSelf, mode, offset, size, callback, userdata);
    }
    void wgpuBufferSetLabel(WGPUBuffer cSelf, char const * label) {
        return NativeBufferSetLabel(
            cSelf, label);
    }
    void wgpuBufferUnmap(WGPUBuffer cSelf) {
        return NativeBufferUnmap(
            cSelf);
    }
    void wgpuBufferReference(WGPUBuffer cSelf) {
        return NativeBufferReference(
            cSelf);
    }
    void wgpuBufferRelease(WGPUBuffer cSelf) {
        return NativeBufferRelease(
            cSelf);
    }
    void wgpuCommandBufferSetLabel(WGPUCommandBuffer cSelf, char const * label) {
        return NativeCommandBufferSetLabel(
            cSelf, label);
    }
    void wgpuCommandBufferReference(WGPUCommandBuffer cSelf) {
        return NativeCommandBufferReference(
            cSelf);
    }
    void wgpuCommandBufferRelease(WGPUCommandBuffer cSelf) {
        return NativeCommandBufferRelease(
            cSelf);
    }
    WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
        return NativeCommandEncoderBeginComputePass(
            cSelf, descriptor);
    }
    WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
        return NativeCommandEncoderBeginRenderPass(
            cSelf, descriptor);
    }
    void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        return NativeCommandEncoderClearBuffer(
            cSelf, buffer, offset, size);
    }
    void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        return NativeCommandEncoderCopyBufferToBuffer(
            cSelf, source, sourceOffset, destination, destinationOffset, size);
    }
    void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        return NativeCommandEncoderCopyBufferToTexture(
            cSelf, source, destination, copySize);
    }
    void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
        return NativeCommandEncoderCopyTextureToBuffer(
            cSelf, source, destination, copySize);
    }
    void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        return NativeCommandEncoderCopyTextureToTexture(
            cSelf, source, destination, copySize);
    }
    void wgpuCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        return NativeCommandEncoderCopyTextureToTextureInternal(
            cSelf, source, destination, copySize);
    }
    WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
        return NativeCommandEncoderFinish(
            cSelf, descriptor);
    }
    void wgpuCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, char const * message) {
        return NativeCommandEncoderInjectValidationError(
            cSelf, message);
    }
    void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel) {
        return NativeCommandEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
        return NativeCommandEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel) {
        return NativeCommandEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        return NativeCommandEncoderResolveQuerySet(
            cSelf, querySet, firstQuery, queryCount, destination, destinationOffset);
    }
    void wgpuCommandEncoderSetLabel(WGPUCommandEncoder cSelf, char const * label) {
        return NativeCommandEncoderSetLabel(
            cSelf, label);
    }
    void wgpuCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        return NativeCommandEncoderWriteBuffer(
            cSelf, buffer, bufferOffset, data, size);
    }
    void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        return NativeCommandEncoderWriteTimestamp(
            cSelf, querySet, queryIndex);
    }
    void wgpuCommandEncoderReference(WGPUCommandEncoder cSelf) {
        return NativeCommandEncoderReference(
            cSelf);
    }
    void wgpuCommandEncoderRelease(WGPUCommandEncoder cSelf) {
        return NativeCommandEncoderRelease(
            cSelf);
    }
    void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder cSelf, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        return NativeComputePassEncoderDispatchWorkgroups(
            cSelf, workgroupCountX, workgroupCountY, workgroupCountZ);
    }
    void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeComputePassEncoderDispatchWorkgroupsIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuComputePassEncoderEnd(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderEnd(
            cSelf);
    }
    void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel) {
        return NativeComputePassEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel) {
        return NativeComputePassEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        return NativeComputePassEncoderSetBindGroup(
            cSelf, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, char const * label) {
        return NativeComputePassEncoderSetLabel(
            cSelf, label);
    }
    void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
        return NativeComputePassEncoderSetPipeline(
            cSelf, pipeline);
    }
    void wgpuComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        return NativeComputePassEncoderWriteTimestamp(
            cSelf, querySet, queryIndex);
    }
    void wgpuComputePassEncoderReference(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderReference(
            cSelf);
    }
    void wgpuComputePassEncoderRelease(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderRelease(
            cSelf);
    }
    WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
        return NativeComputePipelineGetBindGroupLayout(
            cSelf, groupIndex);
    }
    void wgpuComputePipelineSetLabel(WGPUComputePipeline cSelf, char const * label) {
        return NativeComputePipelineSetLabel(
            cSelf, label);
    }
    void wgpuComputePipelineReference(WGPUComputePipeline cSelf) {
        return NativeComputePipelineReference(
            cSelf);
    }
    void wgpuComputePipelineRelease(WGPUComputePipeline cSelf) {
        return NativeComputePipelineRelease(
            cSelf);
    }
    WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
        return NativeDeviceCreateBindGroup(
            cSelf, descriptor);
    }
    WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
        return NativeDeviceCreateBindGroupLayout(
            cSelf, descriptor);
    }
    WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        return NativeDeviceCreateBuffer(
            cSelf, descriptor);
    }
    WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
        return NativeDeviceCreateCommandEncoder(
            cSelf, descriptor);
    }
    WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
        return NativeDeviceCreateComputePipeline(
            cSelf, descriptor);
    }
    void wgpuDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
        return NativeDeviceCreateComputePipelineAsync(
            cSelf, descriptor, callback, userdata);
    }
    WGPUBuffer wgpuDeviceCreateErrorBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        return NativeDeviceCreateErrorBuffer(
            cSelf, descriptor);
    }
    WGPUExternalTexture wgpuDeviceCreateErrorExternalTexture(WGPUDevice cSelf) {
        return NativeDeviceCreateErrorExternalTexture(
            cSelf);
    }
    WGPUShaderModule wgpuDeviceCreateErrorShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage) {
        return NativeDeviceCreateErrorShaderModule(
            cSelf, descriptor, errorMessage);
    }
    WGPUTexture wgpuDeviceCreateErrorTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        return NativeDeviceCreateErrorTexture(
            cSelf, descriptor);
    }
    WGPUExternalTexture wgpuDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
        return NativeDeviceCreateExternalTexture(
            cSelf, externalTextureDescriptor);
    }
    WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
        return NativeDeviceCreatePipelineLayout(
            cSelf, descriptor);
    }
    WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
        return NativeDeviceCreateQuerySet(
            cSelf, descriptor);
    }
    WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
        return NativeDeviceCreateRenderBundleEncoder(
            cSelf, descriptor);
    }
    WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
        return NativeDeviceCreateRenderPipeline(
            cSelf, descriptor);
    }
    void wgpuDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
        return NativeDeviceCreateRenderPipelineAsync(
            cSelf, descriptor, callback, userdata);
    }
    WGPUSampler wgpuDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
        return NativeDeviceCreateSampler(
            cSelf, descriptor);
    }
    WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
        return NativeDeviceCreateShaderModule(
            cSelf, descriptor);
    }
    WGPUSwapChain wgpuDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
        return NativeDeviceCreateSwapChain(
            cSelf, surface, descriptor);
    }
    WGPUTexture wgpuDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        return NativeDeviceCreateTexture(
            cSelf, descriptor);
    }
    void wgpuDeviceDestroy(WGPUDevice cSelf) {
        return NativeDeviceDestroy(
            cSelf);
    }
    size_t wgpuDeviceEnumerateFeatures(WGPUDevice cSelf, WGPUFeatureName * features) {
        return NativeDeviceEnumerateFeatures(
            cSelf, features);
    }
    void wgpuDeviceForceLoss(WGPUDevice cSelf, WGPUDeviceLostReason type, char const * message) {
        return NativeDeviceForceLoss(
            cSelf, type, message);
    }
    WGPUAdapter wgpuDeviceGetAdapter(WGPUDevice cSelf) {
        return NativeDeviceGetAdapter(
            cSelf);
    }
    bool wgpuDeviceGetLimits(WGPUDevice cSelf, WGPUSupportedLimits * limits) {
        return NativeDeviceGetLimits(
            cSelf, limits);
    }
    WGPUQueue wgpuDeviceGetQueue(WGPUDevice cSelf) {
        return NativeDeviceGetQueue(
            cSelf);
    }
    WGPUTextureUsageFlags wgpuDeviceGetSupportedSurfaceUsage(WGPUDevice cSelf, WGPUSurface surface) {
        return NativeDeviceGetSupportedSurfaceUsage(
            cSelf, surface);
    }
    bool wgpuDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature) {
        return NativeDeviceHasFeature(
            cSelf, feature);
    }
    void wgpuDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message) {
        return NativeDeviceInjectError(
            cSelf, type, message);
    }
    void wgpuDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        return NativeDevicePopErrorScope(
            cSelf, callback, userdata);
    }
    void wgpuDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
        return NativeDevicePushErrorScope(
            cSelf, filter);
    }
    void wgpuDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata) {
        return NativeDeviceSetDeviceLostCallback(
            cSelf, callback, userdata);
    }
    void wgpuDeviceSetLabel(WGPUDevice cSelf, char const * label) {
        return NativeDeviceSetLabel(
            cSelf, label);
    }
    void wgpuDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallback callback, void * userdata) {
        return NativeDeviceSetLoggingCallback(
            cSelf, callback, userdata);
    }
    void wgpuDeviceSetUncapturedErrorCallback(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        return NativeDeviceSetUncapturedErrorCallback(
            cSelf, callback, userdata);
    }
    void wgpuDeviceTick(WGPUDevice cSelf) {
        return NativeDeviceTick(
            cSelf);
    }
    void wgpuDeviceValidateTextureDescriptor(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        return NativeDeviceValidateTextureDescriptor(
            cSelf, descriptor);
    }
    void wgpuDeviceReference(WGPUDevice cSelf) {
        return NativeDeviceReference(
            cSelf);
    }
    void wgpuDeviceRelease(WGPUDevice cSelf) {
        return NativeDeviceRelease(
            cSelf);
    }
    void wgpuExternalTextureDestroy(WGPUExternalTexture cSelf) {
        return NativeExternalTextureDestroy(
            cSelf);
    }
    void wgpuExternalTextureExpire(WGPUExternalTexture cSelf) {
        return NativeExternalTextureExpire(
            cSelf);
    }
    void wgpuExternalTextureRefresh(WGPUExternalTexture cSelf) {
        return NativeExternalTextureRefresh(
            cSelf);
    }
    void wgpuExternalTextureSetLabel(WGPUExternalTexture cSelf, char const * label) {
        return NativeExternalTextureSetLabel(
            cSelf, label);
    }
    void wgpuExternalTextureReference(WGPUExternalTexture cSelf) {
        return NativeExternalTextureReference(
            cSelf);
    }
    void wgpuExternalTextureRelease(WGPUExternalTexture cSelf) {
        return NativeExternalTextureRelease(
            cSelf);
    }
    WGPUSurface wgpuInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
        return NativeInstanceCreateSurface(
            cSelf, descriptor);
    }
    void wgpuInstanceProcessEvents(WGPUInstance cSelf) {
        return NativeInstanceProcessEvents(
            cSelf);
    }
    void wgpuInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
        return NativeInstanceRequestAdapter(
            cSelf, options, callback, userdata);
    }
    void wgpuInstanceReference(WGPUInstance cSelf) {
        return NativeInstanceReference(
            cSelf);
    }
    void wgpuInstanceRelease(WGPUInstance cSelf) {
        return NativeInstanceRelease(
            cSelf);
    }
    void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout cSelf, char const * label) {
        return NativePipelineLayoutSetLabel(
            cSelf, label);
    }
    void wgpuPipelineLayoutReference(WGPUPipelineLayout cSelf) {
        return NativePipelineLayoutReference(
            cSelf);
    }
    void wgpuPipelineLayoutRelease(WGPUPipelineLayout cSelf) {
        return NativePipelineLayoutRelease(
            cSelf);
    }
    void wgpuQuerySetDestroy(WGPUQuerySet cSelf) {
        return NativeQuerySetDestroy(
            cSelf);
    }
    uint32_t wgpuQuerySetGetCount(WGPUQuerySet cSelf) {
        return NativeQuerySetGetCount(
            cSelf);
    }
    WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet cSelf) {
        return NativeQuerySetGetType(
            cSelf);
    }
    void wgpuQuerySetSetLabel(WGPUQuerySet cSelf, char const * label) {
        return NativeQuerySetSetLabel(
            cSelf, label);
    }
    void wgpuQuerySetReference(WGPUQuerySet cSelf) {
        return NativeQuerySetReference(
            cSelf);
    }
    void wgpuQuerySetRelease(WGPUQuerySet cSelf) {
        return NativeQuerySetRelease(
            cSelf);
    }
    void wgpuQueueCopyExternalTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        return NativeQueueCopyExternalTextureForBrowser(
            cSelf, source, destination, copySize, options);
    }
    void wgpuQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        return NativeQueueCopyTextureForBrowser(
            cSelf, source, destination, copySize, options);
    }
    void wgpuQueueOnSubmittedWorkDone(WGPUQueue cSelf, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
        return NativeQueueOnSubmittedWorkDone(
            cSelf, signalValue, callback, userdata);
    }
    void wgpuQueueSetLabel(WGPUQueue cSelf, char const * label) {
        return NativeQueueSetLabel(
            cSelf, label);
    }
    void wgpuQueueSubmit(WGPUQueue cSelf, size_t commandCount, WGPUCommandBuffer const * commands) {
        return NativeQueueSubmit(
            cSelf, commandCount, commands);
    }
    void wgpuQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        return NativeQueueWriteBuffer(
            cSelf, buffer, bufferOffset, data, size);
    }
    void wgpuQueueWriteTexture(WGPUQueue cSelf, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        return NativeQueueWriteTexture(
            cSelf, destination, data, dataSize, dataLayout, writeSize);
    }
    void wgpuQueueReference(WGPUQueue cSelf) {
        return NativeQueueReference(
            cSelf);
    }
    void wgpuQueueRelease(WGPUQueue cSelf) {
        return NativeQueueRelease(
            cSelf);
    }
    void wgpuRenderBundleSetLabel(WGPURenderBundle cSelf, char const * label) {
        return NativeRenderBundleSetLabel(
            cSelf, label);
    }
    void wgpuRenderBundleReference(WGPURenderBundle cSelf) {
        return NativeRenderBundleReference(
            cSelf);
    }
    void wgpuRenderBundleRelease(WGPURenderBundle cSelf) {
        return NativeRenderBundleRelease(
            cSelf);
    }
    void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        return NativeRenderBundleEncoderDraw(
            cSelf, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        return NativeRenderBundleEncoderDrawIndexed(
            cSelf, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderBundleEncoderDrawIndexedIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderBundleEncoderDrawIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
        return NativeRenderBundleEncoderFinish(
            cSelf, descriptor);
    }
    void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel) {
        return NativeRenderBundleEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
        return NativeRenderBundleEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel) {
        return NativeRenderBundleEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        return NativeRenderBundleEncoderSetBindGroup(
            cSelf, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        return NativeRenderBundleEncoderSetIndexBuffer(
            cSelf, buffer, format, offset, size);
    }
    void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, char const * label) {
        return NativeRenderBundleEncoderSetLabel(
            cSelf, label);
    }
    void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
        return NativeRenderBundleEncoderSetPipeline(
            cSelf, pipeline);
    }
    void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        return NativeRenderBundleEncoderSetVertexBuffer(
            cSelf, slot, buffer, offset, size);
    }
    void wgpuRenderBundleEncoderReference(WGPURenderBundleEncoder cSelf) {
        return NativeRenderBundleEncoderReference(
            cSelf);
    }
    void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf) {
        return NativeRenderBundleEncoderRelease(
            cSelf);
    }
    void wgpuRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex) {
        return NativeRenderPassEncoderBeginOcclusionQuery(
            cSelf, queryIndex);
    }
    void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        return NativeRenderPassEncoderDraw(
            cSelf, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        return NativeRenderPassEncoderDrawIndexed(
            cSelf, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderPassEncoderDrawIndexedIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderPassEncoderDrawIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuRenderPassEncoderEnd(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderEnd(
            cSelf);
    }
    void wgpuRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderEndOcclusionQuery(
            cSelf);
    }
    void wgpuRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, size_t bundleCount, WGPURenderBundle const * bundles) {
        return NativeRenderPassEncoderExecuteBundles(
            cSelf, bundleCount, bundles);
    }
    void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel) {
        return NativeRenderPassEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel) {
        return NativeRenderPassEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        return NativeRenderPassEncoderSetBindGroup(
            cSelf, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
        return NativeRenderPassEncoderSetBlendConstant(
            cSelf, color);
    }
    void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        return NativeRenderPassEncoderSetIndexBuffer(
            cSelf, buffer, format, offset, size);
    }
    void wgpuRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, char const * label) {
        return NativeRenderPassEncoderSetLabel(
            cSelf, label);
    }
    void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
        return NativeRenderPassEncoderSetPipeline(
            cSelf, pipeline);
    }
    void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        return NativeRenderPassEncoderSetScissorRect(
            cSelf, x, y, width, height);
    }
    void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
        return NativeRenderPassEncoderSetStencilReference(
            cSelf, reference);
    }
    void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        return NativeRenderPassEncoderSetVertexBuffer(
            cSelf, slot, buffer, offset, size);
    }
    void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
        return NativeRenderPassEncoderSetViewport(
            cSelf, x, y, width, height, minDepth, maxDepth);
    }
    void wgpuRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        return NativeRenderPassEncoderWriteTimestamp(
            cSelf, querySet, queryIndex);
    }
    void wgpuRenderPassEncoderReference(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderReference(
            cSelf);
    }
    void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderRelease(
            cSelf);
    }
    WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
        return NativeRenderPipelineGetBindGroupLayout(
            cSelf, groupIndex);
    }
    void wgpuRenderPipelineSetLabel(WGPURenderPipeline cSelf, char const * label) {
        return NativeRenderPipelineSetLabel(
            cSelf, label);
    }
    void wgpuRenderPipelineReference(WGPURenderPipeline cSelf) {
        return NativeRenderPipelineReference(
            cSelf);
    }
    void wgpuRenderPipelineRelease(WGPURenderPipeline cSelf) {
        return NativeRenderPipelineRelease(
            cSelf);
    }
    void wgpuSamplerSetLabel(WGPUSampler cSelf, char const * label) {
        return NativeSamplerSetLabel(
            cSelf, label);
    }
    void wgpuSamplerReference(WGPUSampler cSelf) {
        return NativeSamplerReference(
            cSelf);
    }
    void wgpuSamplerRelease(WGPUSampler cSelf) {
        return NativeSamplerRelease(
            cSelf);
    }
    void wgpuShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallback callback, void * userdata) {
        return NativeShaderModuleGetCompilationInfo(
            cSelf, callback, userdata);
    }
    void wgpuShaderModuleSetLabel(WGPUShaderModule cSelf, char const * label) {
        return NativeShaderModuleSetLabel(
            cSelf, label);
    }
    void wgpuShaderModuleReference(WGPUShaderModule cSelf) {
        return NativeShaderModuleReference(
            cSelf);
    }
    void wgpuShaderModuleRelease(WGPUShaderModule cSelf) {
        return NativeShaderModuleRelease(
            cSelf);
    }
    void wgpuSurfaceReference(WGPUSurface cSelf) {
        return NativeSurfaceReference(
            cSelf);
    }
    void wgpuSurfaceRelease(WGPUSurface cSelf) {
        return NativeSurfaceRelease(
            cSelf);
    }
    WGPUTexture wgpuSwapChainGetCurrentTexture(WGPUSwapChain cSelf) {
        return NativeSwapChainGetCurrentTexture(
            cSelf);
    }
    WGPUTextureView wgpuSwapChainGetCurrentTextureView(WGPUSwapChain cSelf) {
        return NativeSwapChainGetCurrentTextureView(
            cSelf);
    }
    void wgpuSwapChainPresent(WGPUSwapChain cSelf) {
        return NativeSwapChainPresent(
            cSelf);
    }
    void wgpuSwapChainReference(WGPUSwapChain cSelf) {
        return NativeSwapChainReference(
            cSelf);
    }
    void wgpuSwapChainRelease(WGPUSwapChain cSelf) {
        return NativeSwapChainRelease(
            cSelf);
    }
    WGPUTextureView wgpuTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        return NativeTextureCreateView(
            cSelf, descriptor);
    }
    void wgpuTextureDestroy(WGPUTexture cSelf) {
        return NativeTextureDestroy(
            cSelf);
    }
    uint32_t wgpuTextureGetDepthOrArrayLayers(WGPUTexture cSelf) {
        return NativeTextureGetDepthOrArrayLayers(
            cSelf);
    }
    WGPUTextureDimension wgpuTextureGetDimension(WGPUTexture cSelf) {
        return NativeTextureGetDimension(
            cSelf);
    }
    WGPUTextureFormat wgpuTextureGetFormat(WGPUTexture cSelf) {
        return NativeTextureGetFormat(
            cSelf);
    }
    uint32_t wgpuTextureGetHeight(WGPUTexture cSelf) {
        return NativeTextureGetHeight(
            cSelf);
    }
    uint32_t wgpuTextureGetMipLevelCount(WGPUTexture cSelf) {
        return NativeTextureGetMipLevelCount(
            cSelf);
    }
    uint32_t wgpuTextureGetSampleCount(WGPUTexture cSelf) {
        return NativeTextureGetSampleCount(
            cSelf);
    }
    WGPUTextureUsageFlags wgpuTextureGetUsage(WGPUTexture cSelf) {
        return NativeTextureGetUsage(
            cSelf);
    }
    uint32_t wgpuTextureGetWidth(WGPUTexture cSelf) {
        return NativeTextureGetWidth(
            cSelf);
    }
    void wgpuTextureSetLabel(WGPUTexture cSelf, char const * label) {
        return NativeTextureSetLabel(
            cSelf, label);
    }
    void wgpuTextureReference(WGPUTexture cSelf) {
        return NativeTextureReference(
            cSelf);
    }
    void wgpuTextureRelease(WGPUTexture cSelf) {
        return NativeTextureRelease(
            cSelf);
    }
    void wgpuTextureViewSetLabel(WGPUTextureView cSelf, char const * label) {
        return NativeTextureViewSetLabel(
            cSelf, label);
    }
    void wgpuTextureViewReference(WGPUTextureView cSelf) {
        return NativeTextureViewReference(
            cSelf);
    }
    void wgpuTextureViewRelease(WGPUTextureView cSelf) {
        return NativeTextureViewRelease(
            cSelf);
    }
}
