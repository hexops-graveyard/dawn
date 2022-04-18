
#include "dawn/common/Assert.h"
#include "dawn/wire/server/Server.h"

namespace dawn::wire::server {


    bool Server::DoBindGroupLayoutSetLabel(WGPUBindGroupLayout self, char const * label) {
        
        mProcs.bindGroupLayoutSetLabel(self, label);
        return true;
    }

    bool Server::DoBindGroupSetLabel(WGPUBindGroup self, char const * label) {
        
        mProcs.bindGroupSetLabel(self, label);
        return true;
    }

    bool Server::DoBufferDestroy(WGPUBuffer self) {
        
        mProcs.bufferDestroy(self);
        return true;
    }


    bool Server::DoBufferSetLabel(WGPUBuffer self, char const * label) {
        
        mProcs.bufferSetLabel(self, label);
        return true;
    }

    bool Server::DoBufferUnmap(WGPUBuffer self) {
        
        mProcs.bufferUnmap(self);
        return true;
    }


    bool Server::DoCommandBufferSetLabel(WGPUCommandBuffer self, char const * label) {
        
        mProcs.commandBufferSetLabel(self, label);
        return true;
    }

    bool Server::DoCommandEncoderBeginComputePass(WGPUCommandEncoder self, WGPUComputePassDescriptor const * descriptor, WGPUComputePassEncoder* result) {
        *result =
        mProcs.commandEncoderBeginComputePass(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoCommandEncoderBeginRenderPass(WGPUCommandEncoder self, WGPURenderPassDescriptor const * descriptor, WGPURenderPassEncoder* result) {
        *result =
        mProcs.commandEncoderBeginRenderPass(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoCommandEncoderClearBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        
        mProcs.commandEncoderClearBuffer(self, buffer, offset, size);
        return true;
    }

    bool Server::DoCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder self, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        
        mProcs.commandEncoderCopyBufferToBuffer(self, source, sourceOffset, destination, destinationOffset, size);
        return true;
    }

    bool Server::DoCommandEncoderCopyBufferToTexture(WGPUCommandEncoder self, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyBufferToTexture(self, source, destination, copySize);
        return true;
    }

    bool Server::DoCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyTextureToBuffer(self, source, destination, copySize);
        return true;
    }

    bool Server::DoCommandEncoderCopyTextureToTexture(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyTextureToTexture(self, source, destination, copySize);
        return true;
    }

    bool Server::DoCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyTextureToTextureInternal(self, source, destination, copySize);
        return true;
    }

    bool Server::DoCommandEncoderFinish(WGPUCommandEncoder self, WGPUCommandBufferDescriptor const * descriptor, WGPUCommandBuffer* result) {
        *result =
        mProcs.commandEncoderFinish(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoCommandEncoderInjectValidationError(WGPUCommandEncoder self, char const * message) {
        
        mProcs.commandEncoderInjectValidationError(self, message);
        return true;
    }

    bool Server::DoCommandEncoderInsertDebugMarker(WGPUCommandEncoder self, char const * markerLabel) {
        
        mProcs.commandEncoderInsertDebugMarker(self, markerLabel);
        return true;
    }

    bool Server::DoCommandEncoderPopDebugGroup(WGPUCommandEncoder self) {
        
        mProcs.commandEncoderPopDebugGroup(self);
        return true;
    }

    bool Server::DoCommandEncoderPushDebugGroup(WGPUCommandEncoder self, char const * groupLabel) {
        
        mProcs.commandEncoderPushDebugGroup(self, groupLabel);
        return true;
    }

    bool Server::DoCommandEncoderResolveQuerySet(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        
        mProcs.commandEncoderResolveQuerySet(self, querySet, firstQuery, queryCount, destination, destinationOffset);
        return true;
    }

    bool Server::DoCommandEncoderSetLabel(WGPUCommandEncoder self, char const * label) {
        
        mProcs.commandEncoderSetLabel(self, label);
        return true;
    }

    bool Server::DoCommandEncoderWriteBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        
        mProcs.commandEncoderWriteBuffer(self, buffer, bufferOffset, data, size);
        return true;
    }

    bool Server::DoCommandEncoderWriteTimestamp(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        
        mProcs.commandEncoderWriteTimestamp(self, querySet, queryIndex);
        return true;
    }

    bool Server::DoComputePassEncoderDispatch(WGPUComputePassEncoder self, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        
        mProcs.computePassEncoderDispatch(self, workgroupCountX, workgroupCountY, workgroupCountZ);
        return true;
    }

    bool Server::DoComputePassEncoderDispatchIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.computePassEncoderDispatchIndirect(self, indirectBuffer, indirectOffset);
        return true;
    }

    bool Server::DoComputePassEncoderEnd(WGPUComputePassEncoder self) {
        
        mProcs.computePassEncoderEnd(self);
        return true;
    }

    bool Server::DoComputePassEncoderEndPass(WGPUComputePassEncoder self) {
        
        mProcs.computePassEncoderEndPass(self);
        return true;
    }

    bool Server::DoComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder self, char const * markerLabel) {
        
        mProcs.computePassEncoderInsertDebugMarker(self, markerLabel);
        return true;
    }

    bool Server::DoComputePassEncoderPopDebugGroup(WGPUComputePassEncoder self) {
        
        mProcs.computePassEncoderPopDebugGroup(self);
        return true;
    }

    bool Server::DoComputePassEncoderPushDebugGroup(WGPUComputePassEncoder self, char const * groupLabel) {
        
        mProcs.computePassEncoderPushDebugGroup(self, groupLabel);
        return true;
    }

    bool Server::DoComputePassEncoderSetBindGroup(WGPUComputePassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        
        mProcs.computePassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
        return true;
    }

    bool Server::DoComputePassEncoderSetLabel(WGPUComputePassEncoder self, char const * label) {
        
        mProcs.computePassEncoderSetLabel(self, label);
        return true;
    }

    bool Server::DoComputePassEncoderSetPipeline(WGPUComputePassEncoder self, WGPUComputePipeline pipeline) {
        
        mProcs.computePassEncoderSetPipeline(self, pipeline);
        return true;
    }

    bool Server::DoComputePassEncoderWriteTimestamp(WGPUComputePassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        
        mProcs.computePassEncoderWriteTimestamp(self, querySet, queryIndex);
        return true;
    }

    bool Server::DoComputePipelineGetBindGroupLayout(WGPUComputePipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result) {
        *result =
        mProcs.computePipelineGetBindGroupLayout(self, groupIndex);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoComputePipelineSetLabel(WGPUComputePipeline self, char const * label) {
        
        mProcs.computePipelineSetLabel(self, label);
        return true;
    }


    bool Server::DoDeviceCreateBindGroup(WGPUDevice self, WGPUBindGroupDescriptor const * descriptor, WGPUBindGroup* result) {
        *result =
        mProcs.deviceCreateBindGroup(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateBindGroupLayout(WGPUDevice self, WGPUBindGroupLayoutDescriptor const * descriptor, WGPUBindGroupLayout* result) {
        *result =
        mProcs.deviceCreateBindGroupLayout(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }


    bool Server::DoDeviceCreateCommandEncoder(WGPUDevice self, WGPUCommandEncoderDescriptor const * descriptor, WGPUCommandEncoder* result) {
        *result =
        mProcs.deviceCreateCommandEncoder(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor, WGPUComputePipeline* result) {
        *result =
        mProcs.deviceCreateComputePipeline(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }


    bool Server::DoDeviceCreateErrorBuffer(WGPUDevice self, WGPUBuffer* result) {
        *result =
        mProcs.deviceCreateErrorBuffer(self);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateExternalTexture(WGPUDevice self, WGPUExternalTextureDescriptor const * externalTextureDescriptor, WGPUExternalTexture* result) {
        *result =
        mProcs.deviceCreateExternalTexture(self, externalTextureDescriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreatePipelineLayout(WGPUDevice self, WGPUPipelineLayoutDescriptor const * descriptor, WGPUPipelineLayout* result) {
        *result =
        mProcs.deviceCreatePipelineLayout(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateQuerySet(WGPUDevice self, WGPUQuerySetDescriptor const * descriptor, WGPUQuerySet* result) {
        *result =
        mProcs.deviceCreateQuerySet(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateRenderBundleEncoder(WGPUDevice self, WGPURenderBundleEncoderDescriptor const * descriptor, WGPURenderBundleEncoder* result) {
        *result =
        mProcs.deviceCreateRenderBundleEncoder(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor, WGPURenderPipeline* result) {
        *result =
        mProcs.deviceCreateRenderPipeline(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }


    bool Server::DoDeviceCreateSampler(WGPUDevice self, WGPUSamplerDescriptor const * descriptor, WGPUSampler* result) {
        *result =
        mProcs.deviceCreateSampler(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, WGPUShaderModule* result) {
        *result =
        mProcs.deviceCreateShaderModule(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateSwapChain(WGPUDevice self, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor, WGPUSwapChain* result) {
        *result =
        mProcs.deviceCreateSwapChain(self, surface, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceCreateTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor, WGPUTexture* result) {
        *result =
        mProcs.deviceCreateTexture(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceDestroy(WGPUDevice self) {
        
        mProcs.deviceDestroy(self);
        return true;
    }

    bool Server::DoDeviceGetQueue(WGPUDevice self, WGPUQueue* result) {
        *result =
        mProcs.deviceGetQueue(self);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoDeviceInjectError(WGPUDevice self, WGPUErrorType type, char const * message) {
        
        mProcs.deviceInjectError(self, type, message);
        return true;
    }

    bool Server::DoDeviceLoseForTesting(WGPUDevice self) {
        
        mProcs.deviceLoseForTesting(self);
        return true;
    }


    bool Server::DoDevicePushErrorScope(WGPUDevice self, WGPUErrorFilter filter) {
        
        mProcs.devicePushErrorScope(self, filter);
        return true;
    }

    bool Server::DoDeviceSetLabel(WGPUDevice self, char const * label) {
        
        mProcs.deviceSetLabel(self, label);
        return true;
    }

    bool Server::DoDeviceTick(WGPUDevice self) {
        
        mProcs.deviceTick(self);
        return true;
    }

    bool Server::DoExternalTextureDestroy(WGPUExternalTexture self) {
        
        mProcs.externalTextureDestroy(self);
        return true;
    }

    bool Server::DoExternalTextureSetLabel(WGPUExternalTexture self, char const * label) {
        
        mProcs.externalTextureSetLabel(self, label);
        return true;
    }

    bool Server::DoInstanceCreateSurface(WGPUInstance self, WGPUSurfaceDescriptor const * descriptor, WGPUSurface* result) {
        *result =
        mProcs.instanceCreateSurface(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }


    bool Server::DoPipelineLayoutSetLabel(WGPUPipelineLayout self, char const * label) {
        
        mProcs.pipelineLayoutSetLabel(self, label);
        return true;
    }

    bool Server::DoQuerySetDestroy(WGPUQuerySet self) {
        
        mProcs.querySetDestroy(self);
        return true;
    }

    bool Server::DoQuerySetSetLabel(WGPUQuerySet self, char const * label) {
        
        mProcs.querySetSetLabel(self, label);
        return true;
    }

    bool Server::DoQueueCopyTextureForBrowser(WGPUQueue self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        
        mProcs.queueCopyTextureForBrowser(self, source, destination, copySize, options);
        return true;
    }


    bool Server::DoQueueSetLabel(WGPUQueue self, char const * label) {
        
        mProcs.queueSetLabel(self, label);
        return true;
    }

    bool Server::DoQueueSubmit(WGPUQueue self, uint32_t commandCount, WGPUCommandBuffer const * commands) {
        
        mProcs.queueSubmit(self, commandCount, commands);
        return true;
    }



    bool Server::DoRenderBundleEncoderDraw(WGPURenderBundleEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        
        mProcs.renderBundleEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
        return true;
    }

    bool Server::DoRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        
        mProcs.renderBundleEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
        return true;
    }

    bool Server::DoRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderBundleEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
        return true;
    }

    bool Server::DoRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderBundleEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
        return true;
    }

    bool Server::DoRenderBundleEncoderFinish(WGPURenderBundleEncoder self, WGPURenderBundleDescriptor const * descriptor, WGPURenderBundle* result) {
        *result =
        mProcs.renderBundleEncoderFinish(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder self, char const * markerLabel) {
        
        mProcs.renderBundleEncoderInsertDebugMarker(self, markerLabel);
        return true;
    }

    bool Server::DoRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder self) {
        
        mProcs.renderBundleEncoderPopDebugGroup(self);
        return true;
    }

    bool Server::DoRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder self, char const * groupLabel) {
        
        mProcs.renderBundleEncoderPushDebugGroup(self, groupLabel);
        return true;
    }

    bool Server::DoRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        
        mProcs.renderBundleEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
        return true;
    }

    bool Server::DoRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        
        mProcs.renderBundleEncoderSetIndexBuffer(self, buffer, format, offset, size);
        return true;
    }

    bool Server::DoRenderBundleEncoderSetLabel(WGPURenderBundleEncoder self, char const * label) {
        
        mProcs.renderBundleEncoderSetLabel(self, label);
        return true;
    }

    bool Server::DoRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder self, WGPURenderPipeline pipeline) {
        
        mProcs.renderBundleEncoderSetPipeline(self, pipeline);
        return true;
    }

    bool Server::DoRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        
        mProcs.renderBundleEncoderSetVertexBuffer(self, slot, buffer, offset, size);
        return true;
    }

    bool Server::DoRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder self, uint32_t queryIndex) {
        
        mProcs.renderPassEncoderBeginOcclusionQuery(self, queryIndex);
        return true;
    }

    bool Server::DoRenderPassEncoderDraw(WGPURenderPassEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        
        mProcs.renderPassEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
        return true;
    }

    bool Server::DoRenderPassEncoderDrawIndexed(WGPURenderPassEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        
        mProcs.renderPassEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
        return true;
    }

    bool Server::DoRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderPassEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
        return true;
    }

    bool Server::DoRenderPassEncoderDrawIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderPassEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
        return true;
    }

    bool Server::DoRenderPassEncoderEnd(WGPURenderPassEncoder self) {
        
        mProcs.renderPassEncoderEnd(self);
        return true;
    }

    bool Server::DoRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder self) {
        
        mProcs.renderPassEncoderEndOcclusionQuery(self);
        return true;
    }

    bool Server::DoRenderPassEncoderEndPass(WGPURenderPassEncoder self) {
        
        mProcs.renderPassEncoderEndPass(self);
        return true;
    }

    bool Server::DoRenderPassEncoderExecuteBundles(WGPURenderPassEncoder self, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
        
        mProcs.renderPassEncoderExecuteBundles(self, bundlesCount, bundles);
        return true;
    }

    bool Server::DoRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder self, char const * markerLabel) {
        
        mProcs.renderPassEncoderInsertDebugMarker(self, markerLabel);
        return true;
    }

    bool Server::DoRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder self) {
        
        mProcs.renderPassEncoderPopDebugGroup(self);
        return true;
    }

    bool Server::DoRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder self, char const * groupLabel) {
        
        mProcs.renderPassEncoderPushDebugGroup(self, groupLabel);
        return true;
    }

    bool Server::DoRenderPassEncoderSetBindGroup(WGPURenderPassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        
        mProcs.renderPassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
        return true;
    }

    bool Server::DoRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder self, WGPUColor const * color) {
        
        mProcs.renderPassEncoderSetBlendConstant(self, color);
        return true;
    }

    bool Server::DoRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        
        mProcs.renderPassEncoderSetIndexBuffer(self, buffer, format, offset, size);
        return true;
    }

    bool Server::DoRenderPassEncoderSetLabel(WGPURenderPassEncoder self, char const * label) {
        
        mProcs.renderPassEncoderSetLabel(self, label);
        return true;
    }

    bool Server::DoRenderPassEncoderSetPipeline(WGPURenderPassEncoder self, WGPURenderPipeline pipeline) {
        
        mProcs.renderPassEncoderSetPipeline(self, pipeline);
        return true;
    }

    bool Server::DoRenderPassEncoderSetScissorRect(WGPURenderPassEncoder self, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        
        mProcs.renderPassEncoderSetScissorRect(self, x, y, width, height);
        return true;
    }

    bool Server::DoRenderPassEncoderSetStencilReference(WGPURenderPassEncoder self, uint32_t reference) {
        
        mProcs.renderPassEncoderSetStencilReference(self, reference);
        return true;
    }

    bool Server::DoRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        
        mProcs.renderPassEncoderSetVertexBuffer(self, slot, buffer, offset, size);
        return true;
    }

    bool Server::DoRenderPassEncoderSetViewport(WGPURenderPassEncoder self, float x, float y, float width, float height, float minDepth, float maxDepth) {
        
        mProcs.renderPassEncoderSetViewport(self, x, y, width, height, minDepth, maxDepth);
        return true;
    }

    bool Server::DoRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        
        mProcs.renderPassEncoderWriteTimestamp(self, querySet, queryIndex);
        return true;
    }

    bool Server::DoRenderPipelineGetBindGroupLayout(WGPURenderPipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result) {
        *result =
        mProcs.renderPipelineGetBindGroupLayout(self, groupIndex);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoRenderPipelineSetLabel(WGPURenderPipeline self, char const * label) {
        
        mProcs.renderPipelineSetLabel(self, label);
        return true;
    }

    bool Server::DoSamplerSetLabel(WGPUSampler self, char const * label) {
        
        mProcs.samplerSetLabel(self, label);
        return true;
    }


    bool Server::DoShaderModuleSetLabel(WGPUShaderModule self, char const * label) {
        
        mProcs.shaderModuleSetLabel(self, label);
        return true;
    }

    bool Server::DoSwapChainConfigure(WGPUSwapChain self, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
        
        mProcs.swapChainConfigure(self, format, allowedUsage, width, height);
        return true;
    }

    bool Server::DoSwapChainGetCurrentTextureView(WGPUSwapChain self, WGPUTextureView* result) {
        *result =
        mProcs.swapChainGetCurrentTextureView(self);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoSwapChainPresent(WGPUSwapChain self) {
        
        mProcs.swapChainPresent(self);
        return true;
    }

    bool Server::DoTextureCreateView(WGPUTexture self, WGPUTextureViewDescriptor const * descriptor, WGPUTextureView* result) {
        *result =
        mProcs.textureCreateView(self, descriptor);
        ASSERT(*result != nullptr);
        return true;
    }

    bool Server::DoTextureDestroy(WGPUTexture self) {
        
        mProcs.textureDestroy(self);
        return true;
    }

    bool Server::DoTextureSetLabel(WGPUTexture self, char const * label) {
        
        mProcs.textureSetLabel(self, label);
        return true;
    }

    bool Server::DoTextureViewSetLabel(WGPUTextureView self, char const * label) {
        
        mProcs.textureViewSetLabel(self, label);
        return true;
    }

    bool Server::DoDestroyObject(ObjectType objectType, ObjectId objectId) {
        if (objectId == 0) {
            return false;
        }

        switch(objectType) {
            case ObjectType::Adapter: {
                auto* data = AdapterObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.adapterRelease(data->handle);
                }
                AdapterObjects().Free(objectId);
                return true;
            }
            case ObjectType::BindGroup: {
                auto* data = BindGroupObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.bindGroupRelease(data->handle);
                }
                BindGroupObjects().Free(objectId);
                return true;
            }
            case ObjectType::BindGroupLayout: {
                auto* data = BindGroupLayoutObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.bindGroupLayoutRelease(data->handle);
                }
                BindGroupLayoutObjects().Free(objectId);
                return true;
            }
            case ObjectType::Buffer: {
                auto* data = BufferObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.bufferRelease(data->handle);
                }
                BufferObjects().Free(objectId);
                return true;
            }
            case ObjectType::CommandBuffer: {
                auto* data = CommandBufferObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.commandBufferRelease(data->handle);
                }
                CommandBufferObjects().Free(objectId);
                return true;
            }
            case ObjectType::CommandEncoder: {
                auto* data = CommandEncoderObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.commandEncoderRelease(data->handle);
                }
                CommandEncoderObjects().Free(objectId);
                return true;
            }
            case ObjectType::ComputePassEncoder: {
                auto* data = ComputePassEncoderObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.computePassEncoderRelease(data->handle);
                }
                ComputePassEncoderObjects().Free(objectId);
                return true;
            }
            case ObjectType::ComputePipeline: {
                auto* data = ComputePipelineObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.computePipelineRelease(data->handle);
                }
                ComputePipelineObjects().Free(objectId);
                return true;
            }
            case ObjectType::Device: {
                auto* data = DeviceObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);

                    while (data->info->childObjectTypesAndIds.size() > 0) {
                        auto [childObjectType, childObjectId] = UnpackObjectTypeAndId(
                            *data->info->childObjectTypesAndIds.begin());
                        if (!DoDestroyObject(childObjectType, childObjectId)) {
                            return false;
                        }
                    }
                    if (data->handle != nullptr) {
                        ClearDeviceCallbacks(data->handle);
                    }

                    mProcs.deviceRelease(data->handle);
                }
                DeviceObjects().Free(objectId);
                return true;
            }
            case ObjectType::ExternalTexture: {
                auto* data = ExternalTextureObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.externalTextureRelease(data->handle);
                }
                ExternalTextureObjects().Free(objectId);
                return true;
            }
            case ObjectType::Instance: {
                auto* data = InstanceObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.instanceRelease(data->handle);
                }
                InstanceObjects().Free(objectId);
                return true;
            }
            case ObjectType::PipelineLayout: {
                auto* data = PipelineLayoutObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.pipelineLayoutRelease(data->handle);
                }
                PipelineLayoutObjects().Free(objectId);
                return true;
            }
            case ObjectType::QuerySet: {
                auto* data = QuerySetObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.querySetRelease(data->handle);
                }
                QuerySetObjects().Free(objectId);
                return true;
            }
            case ObjectType::Queue: {
                auto* data = QueueObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.queueRelease(data->handle);
                }
                QueueObjects().Free(objectId);
                return true;
            }
            case ObjectType::RenderBundle: {
                auto* data = RenderBundleObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.renderBundleRelease(data->handle);
                }
                RenderBundleObjects().Free(objectId);
                return true;
            }
            case ObjectType::RenderBundleEncoder: {
                auto* data = RenderBundleEncoderObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.renderBundleEncoderRelease(data->handle);
                }
                RenderBundleEncoderObjects().Free(objectId);
                return true;
            }
            case ObjectType::RenderPassEncoder: {
                auto* data = RenderPassEncoderObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.renderPassEncoderRelease(data->handle);
                }
                RenderPassEncoderObjects().Free(objectId);
                return true;
            }
            case ObjectType::RenderPipeline: {
                auto* data = RenderPipelineObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.renderPipelineRelease(data->handle);
                }
                RenderPipelineObjects().Free(objectId);
                return true;
            }
            case ObjectType::Sampler: {
                auto* data = SamplerObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.samplerRelease(data->handle);
                }
                SamplerObjects().Free(objectId);
                return true;
            }
            case ObjectType::ShaderModule: {
                auto* data = ShaderModuleObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.shaderModuleRelease(data->handle);
                }
                ShaderModuleObjects().Free(objectId);
                return true;
            }
            case ObjectType::Surface: {
                auto* data = SurfaceObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.surfaceRelease(data->handle);
                }
                SurfaceObjects().Free(objectId);
                return true;
            }
            case ObjectType::SwapChain: {
                auto* data = SwapChainObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.swapChainRelease(data->handle);
                }
                SwapChainObjects().Free(objectId);
                return true;
            }
            case ObjectType::Texture: {
                auto* data = TextureObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.textureRelease(data->handle);
                }
                TextureObjects().Free(objectId);
                return true;
            }
            case ObjectType::TextureView: {
                auto* data = TextureViewObjects().Get(objectId);
                if (data == nullptr) {
                    return false;
                }
                if (data->deviceInfo != nullptr) {
                    if (!UntrackDeviceChild(data->deviceInfo, objectType, objectId)) {
                        return false;
                    }
                }
                if (data->state == AllocationState::Allocated) {
                    ASSERT(data->handle != nullptr);


                    mProcs.textureViewRelease(data->handle);
                }
                TextureViewObjects().Free(objectId);
                return true;
            }
            default:
                return false;
        }
    }

}  // namespace dawn::wire::server
