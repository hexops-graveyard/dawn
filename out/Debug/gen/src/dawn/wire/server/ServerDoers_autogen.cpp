
#include "dawn/common/Assert.h"
#include "dawn/wire/server/Server.h"

namespace dawn::wire::server {

    WireResult Server::DoAdapterGetInstance(WGPUAdapter self, WGPUInstance* result) {
        *result =
        mProcs.adapterGetInstance(self);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }


    WireResult Server::DoBindGroupLayoutSetLabel(WGPUBindGroupLayout self, char const * label) {
        
        mProcs.bindGroupLayoutSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoBindGroupSetLabel(WGPUBindGroup self, char const * label) {
        
        mProcs.bindGroupSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoBufferDestroy(WGPUBuffer self) {
        
        mProcs.bufferDestroy(self);
        return WireResult::Success;
    }


    WireResult Server::DoBufferSetLabel(WGPUBuffer self, char const * label) {
        
        mProcs.bufferSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoBufferUnmap(WGPUBuffer self) {
        
        mProcs.bufferUnmap(self);
        return WireResult::Success;
    }


    WireResult Server::DoCommandBufferSetLabel(WGPUCommandBuffer self, char const * label) {
        
        mProcs.commandBufferSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderBeginComputePass(WGPUCommandEncoder self, WGPUComputePassDescriptor const * descriptor, WGPUComputePassEncoder* result) {
        *result =
        mProcs.commandEncoderBeginComputePass(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderBeginRenderPass(WGPUCommandEncoder self, WGPURenderPassDescriptor const * descriptor, WGPURenderPassEncoder* result) {
        *result =
        mProcs.commandEncoderBeginRenderPass(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderClearBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        
        mProcs.commandEncoderClearBuffer(self, buffer, offset, size);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder self, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        
        mProcs.commandEncoderCopyBufferToBuffer(self, source, sourceOffset, destination, destinationOffset, size);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderCopyBufferToTexture(WGPUCommandEncoder self, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyBufferToTexture(self, source, destination, copySize);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyTextureToBuffer(self, source, destination, copySize);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderCopyTextureToTexture(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyTextureToTexture(self, source, destination, copySize);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        
        mProcs.commandEncoderCopyTextureToTextureInternal(self, source, destination, copySize);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderFinish(WGPUCommandEncoder self, WGPUCommandBufferDescriptor const * descriptor, WGPUCommandBuffer* result) {
        *result =
        mProcs.commandEncoderFinish(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderInjectValidationError(WGPUCommandEncoder self, char const * message) {
        
        mProcs.commandEncoderInjectValidationError(self, message);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderInsertDebugMarker(WGPUCommandEncoder self, char const * markerLabel) {
        
        mProcs.commandEncoderInsertDebugMarker(self, markerLabel);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderPopDebugGroup(WGPUCommandEncoder self) {
        
        mProcs.commandEncoderPopDebugGroup(self);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderPushDebugGroup(WGPUCommandEncoder self, char const * groupLabel) {
        
        mProcs.commandEncoderPushDebugGroup(self, groupLabel);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderResolveQuerySet(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        
        mProcs.commandEncoderResolveQuerySet(self, querySet, firstQuery, queryCount, destination, destinationOffset);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderSetLabel(WGPUCommandEncoder self, char const * label) {
        
        mProcs.commandEncoderSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderWriteBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        
        mProcs.commandEncoderWriteBuffer(self, buffer, bufferOffset, data, size);
        return WireResult::Success;
    }

    WireResult Server::DoCommandEncoderWriteTimestamp(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        
        mProcs.commandEncoderWriteTimestamp(self, querySet, queryIndex);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder self, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        
        mProcs.computePassEncoderDispatchWorkgroups(self, workgroupCountX, workgroupCountY, workgroupCountZ);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.computePassEncoderDispatchWorkgroupsIndirect(self, indirectBuffer, indirectOffset);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderEnd(WGPUComputePassEncoder self) {
        
        mProcs.computePassEncoderEnd(self);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder self, char const * markerLabel) {
        
        mProcs.computePassEncoderInsertDebugMarker(self, markerLabel);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderPopDebugGroup(WGPUComputePassEncoder self) {
        
        mProcs.computePassEncoderPopDebugGroup(self);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderPushDebugGroup(WGPUComputePassEncoder self, char const * groupLabel) {
        
        mProcs.computePassEncoderPushDebugGroup(self, groupLabel);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderSetBindGroup(WGPUComputePassEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        
        mProcs.computePassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderSetLabel(WGPUComputePassEncoder self, char const * label) {
        
        mProcs.computePassEncoderSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderSetPipeline(WGPUComputePassEncoder self, WGPUComputePipeline pipeline) {
        
        mProcs.computePassEncoderSetPipeline(self, pipeline);
        return WireResult::Success;
    }

    WireResult Server::DoComputePassEncoderWriteTimestamp(WGPUComputePassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        
        mProcs.computePassEncoderWriteTimestamp(self, querySet, queryIndex);
        return WireResult::Success;
    }

    WireResult Server::DoComputePipelineGetBindGroupLayout(WGPUComputePipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result) {
        *result =
        mProcs.computePipelineGetBindGroupLayout(self, groupIndex);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoComputePipelineSetLabel(WGPUComputePipeline self, char const * label) {
        
        mProcs.computePipelineSetLabel(self, label);
        return WireResult::Success;
    }


    WireResult Server::DoDeviceCreateBindGroup(WGPUDevice self, WGPUBindGroupDescriptor const * descriptor, WGPUBindGroup* result) {
        *result =
        mProcs.deviceCreateBindGroup(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateBindGroupLayout(WGPUDevice self, WGPUBindGroupLayoutDescriptor const * descriptor, WGPUBindGroupLayout* result) {
        *result =
        mProcs.deviceCreateBindGroupLayout(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }


    WireResult Server::DoDeviceCreateCommandEncoder(WGPUDevice self, WGPUCommandEncoderDescriptor const * descriptor, WGPUCommandEncoder* result) {
        *result =
        mProcs.deviceCreateCommandEncoder(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor, WGPUComputePipeline* result) {
        *result =
        mProcs.deviceCreateComputePipeline(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }


    WireResult Server::DoDeviceCreateErrorBuffer(WGPUDevice self, WGPUBufferDescriptor const * descriptor, WGPUBuffer* result) {
        *result =
        mProcs.deviceCreateErrorBuffer(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateErrorExternalTexture(WGPUDevice self, WGPUExternalTexture* result) {
        *result =
        mProcs.deviceCreateErrorExternalTexture(self);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateErrorShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage, WGPUShaderModule* result) {
        *result =
        mProcs.deviceCreateErrorShaderModule(self, descriptor, errorMessage);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateErrorTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor, WGPUTexture* result) {
        *result =
        mProcs.deviceCreateErrorTexture(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateExternalTexture(WGPUDevice self, WGPUExternalTextureDescriptor const * externalTextureDescriptor, WGPUExternalTexture* result) {
        *result =
        mProcs.deviceCreateExternalTexture(self, externalTextureDescriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreatePipelineLayout(WGPUDevice self, WGPUPipelineLayoutDescriptor const * descriptor, WGPUPipelineLayout* result) {
        *result =
        mProcs.deviceCreatePipelineLayout(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateQuerySet(WGPUDevice self, WGPUQuerySetDescriptor const * descriptor, WGPUQuerySet* result) {
        *result =
        mProcs.deviceCreateQuerySet(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateRenderBundleEncoder(WGPUDevice self, WGPURenderBundleEncoderDescriptor const * descriptor, WGPURenderBundleEncoder* result) {
        *result =
        mProcs.deviceCreateRenderBundleEncoder(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor, WGPURenderPipeline* result) {
        *result =
        mProcs.deviceCreateRenderPipeline(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }


    WireResult Server::DoDeviceCreateSampler(WGPUDevice self, WGPUSamplerDescriptor const * descriptor, WGPUSampler* result) {
        *result =
        mProcs.deviceCreateSampler(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, WGPUShaderModule* result) {
        *result =
        mProcs.deviceCreateShaderModule(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateSwapChain(WGPUDevice self, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor, WGPUSwapChain* result) {
        *result =
        mProcs.deviceCreateSwapChain(self, surface, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceCreateTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor, WGPUTexture* result) {
        *result =
        mProcs.deviceCreateTexture(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceDestroy(WGPUDevice self) {
        
        mProcs.deviceDestroy(self);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceForceLoss(WGPUDevice self, WGPUDeviceLostReason type, char const * message) {
        
        mProcs.deviceForceLoss(self, type, message);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceGetAdapter(WGPUDevice self, WGPUAdapter* result) {
        *result =
        mProcs.deviceGetAdapter(self);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceGetQueue(WGPUDevice self, WGPUQueue* result) {
        *result =
        mProcs.deviceGetQueue(self);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceInjectError(WGPUDevice self, WGPUErrorType type, char const * message) {
        
        mProcs.deviceInjectError(self, type, message);
        return WireResult::Success;
    }


    WireResult Server::DoDevicePushErrorScope(WGPUDevice self, WGPUErrorFilter filter) {
        
        mProcs.devicePushErrorScope(self, filter);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceSetLabel(WGPUDevice self, char const * label) {
        
        mProcs.deviceSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceTick(WGPUDevice self) {
        
        mProcs.deviceTick(self);
        return WireResult::Success;
    }

    WireResult Server::DoDeviceValidateTextureDescriptor(WGPUDevice self, WGPUTextureDescriptor const * descriptor) {
        
        mProcs.deviceValidateTextureDescriptor(self, descriptor);
        return WireResult::Success;
    }

    WireResult Server::DoExternalTextureDestroy(WGPUExternalTexture self) {
        
        mProcs.externalTextureDestroy(self);
        return WireResult::Success;
    }

    WireResult Server::DoExternalTextureExpire(WGPUExternalTexture self) {
        
        mProcs.externalTextureExpire(self);
        return WireResult::Success;
    }

    WireResult Server::DoExternalTextureRefresh(WGPUExternalTexture self) {
        
        mProcs.externalTextureRefresh(self);
        return WireResult::Success;
    }

    WireResult Server::DoExternalTextureSetLabel(WGPUExternalTexture self, char const * label) {
        
        mProcs.externalTextureSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoInstanceCreateSurface(WGPUInstance self, WGPUSurfaceDescriptor const * descriptor, WGPUSurface* result) {
        *result =
        mProcs.instanceCreateSurface(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoInstanceProcessEvents(WGPUInstance self) {
        
        mProcs.instanceProcessEvents(self);
        return WireResult::Success;
    }


    WireResult Server::DoPipelineLayoutSetLabel(WGPUPipelineLayout self, char const * label) {
        
        mProcs.pipelineLayoutSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoQuerySetDestroy(WGPUQuerySet self) {
        
        mProcs.querySetDestroy(self);
        return WireResult::Success;
    }

    WireResult Server::DoQuerySetSetLabel(WGPUQuerySet self, char const * label) {
        
        mProcs.querySetSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoQueueCopyExternalTextureForBrowser(WGPUQueue self, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        
        mProcs.queueCopyExternalTextureForBrowser(self, source, destination, copySize, options);
        return WireResult::Success;
    }

    WireResult Server::DoQueueCopyTextureForBrowser(WGPUQueue self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        
        mProcs.queueCopyTextureForBrowser(self, source, destination, copySize, options);
        return WireResult::Success;
    }


    WireResult Server::DoQueueSetLabel(WGPUQueue self, char const * label) {
        
        mProcs.queueSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoQueueSubmit(WGPUQueue self, size_t commandCount, WGPUCommandBuffer const * commands) {
        
        mProcs.queueSubmit(self, commandCount, commands);
        return WireResult::Success;
    }



    WireResult Server::DoRenderBundleEncoderDraw(WGPURenderBundleEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        
        mProcs.renderBundleEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        
        mProcs.renderBundleEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderBundleEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderBundleEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderFinish(WGPURenderBundleEncoder self, WGPURenderBundleDescriptor const * descriptor, WGPURenderBundle* result) {
        *result =
        mProcs.renderBundleEncoderFinish(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder self, char const * markerLabel) {
        
        mProcs.renderBundleEncoderInsertDebugMarker(self, markerLabel);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder self) {
        
        mProcs.renderBundleEncoderPopDebugGroup(self);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder self, char const * groupLabel) {
        
        mProcs.renderBundleEncoderPushDebugGroup(self, groupLabel);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        
        mProcs.renderBundleEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        
        mProcs.renderBundleEncoderSetIndexBuffer(self, buffer, format, offset, size);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderSetLabel(WGPURenderBundleEncoder self, char const * label) {
        
        mProcs.renderBundleEncoderSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder self, WGPURenderPipeline pipeline) {
        
        mProcs.renderBundleEncoderSetPipeline(self, pipeline);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        
        mProcs.renderBundleEncoderSetVertexBuffer(self, slot, buffer, offset, size);
        return WireResult::Success;
    }

    WireResult Server::DoRenderBundleSetLabel(WGPURenderBundle self, char const * label) {
        
        mProcs.renderBundleSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder self, uint32_t queryIndex) {
        
        mProcs.renderPassEncoderBeginOcclusionQuery(self, queryIndex);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderDraw(WGPURenderPassEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        
        mProcs.renderPassEncoderDraw(self, vertexCount, instanceCount, firstVertex, firstInstance);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderDrawIndexed(WGPURenderPassEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        
        mProcs.renderPassEncoderDrawIndexed(self, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderPassEncoderDrawIndexedIndirect(self, indirectBuffer, indirectOffset);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderDrawIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        
        mProcs.renderPassEncoderDrawIndirect(self, indirectBuffer, indirectOffset);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderEnd(WGPURenderPassEncoder self) {
        
        mProcs.renderPassEncoderEnd(self);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder self) {
        
        mProcs.renderPassEncoderEndOcclusionQuery(self);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderExecuteBundles(WGPURenderPassEncoder self, size_t bundleCount, WGPURenderBundle const * bundles) {
        
        mProcs.renderPassEncoderExecuteBundles(self, bundleCount, bundles);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder self, char const * markerLabel) {
        
        mProcs.renderPassEncoderInsertDebugMarker(self, markerLabel);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder self) {
        
        mProcs.renderPassEncoderPopDebugGroup(self);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder self, char const * groupLabel) {
        
        mProcs.renderPassEncoderPushDebugGroup(self, groupLabel);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetBindGroup(WGPURenderPassEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        
        mProcs.renderPassEncoderSetBindGroup(self, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder self, WGPUColor const * color) {
        
        mProcs.renderPassEncoderSetBlendConstant(self, color);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        
        mProcs.renderPassEncoderSetIndexBuffer(self, buffer, format, offset, size);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetLabel(WGPURenderPassEncoder self, char const * label) {
        
        mProcs.renderPassEncoderSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetPipeline(WGPURenderPassEncoder self, WGPURenderPipeline pipeline) {
        
        mProcs.renderPassEncoderSetPipeline(self, pipeline);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetScissorRect(WGPURenderPassEncoder self, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        
        mProcs.renderPassEncoderSetScissorRect(self, x, y, width, height);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetStencilReference(WGPURenderPassEncoder self, uint32_t reference) {
        
        mProcs.renderPassEncoderSetStencilReference(self, reference);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        
        mProcs.renderPassEncoderSetVertexBuffer(self, slot, buffer, offset, size);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderSetViewport(WGPURenderPassEncoder self, float x, float y, float width, float height, float minDepth, float maxDepth) {
        
        mProcs.renderPassEncoderSetViewport(self, x, y, width, height, minDepth, maxDepth);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex) {
        
        mProcs.renderPassEncoderWriteTimestamp(self, querySet, queryIndex);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPipelineGetBindGroupLayout(WGPURenderPipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result) {
        *result =
        mProcs.renderPipelineGetBindGroupLayout(self, groupIndex);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoRenderPipelineSetLabel(WGPURenderPipeline self, char const * label) {
        
        mProcs.renderPipelineSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoSamplerSetLabel(WGPUSampler self, char const * label) {
        
        mProcs.samplerSetLabel(self, label);
        return WireResult::Success;
    }


    WireResult Server::DoShaderModuleSetLabel(WGPUShaderModule self, char const * label) {
        
        mProcs.shaderModuleSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoSwapChainGetCurrentTexture(WGPUSwapChain self, WGPUTexture* result) {
        *result =
        mProcs.swapChainGetCurrentTexture(self);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoSwapChainGetCurrentTextureView(WGPUSwapChain self, WGPUTextureView* result) {
        *result =
        mProcs.swapChainGetCurrentTextureView(self);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoSwapChainPresent(WGPUSwapChain self) {
        
        mProcs.swapChainPresent(self);
        return WireResult::Success;
    }

    WireResult Server::DoTextureCreateView(WGPUTexture self, WGPUTextureViewDescriptor const * descriptor, WGPUTextureView* result) {
        *result =
        mProcs.textureCreateView(self, descriptor);
        ASSERT(*result != nullptr);
        return WireResult::Success;
    }

    WireResult Server::DoTextureDestroy(WGPUTexture self) {
        
        mProcs.textureDestroy(self);
        return WireResult::Success;
    }

    WireResult Server::DoTextureSetLabel(WGPUTexture self, char const * label) {
        
        mProcs.textureSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoTextureViewSetLabel(WGPUTextureView self, char const * label) {
        
        mProcs.textureViewSetLabel(self, label);
        return WireResult::Success;
    }

    WireResult Server::DoDestroyObject(ObjectType objectType, ObjectId objectId) {
        switch(objectType) {
            case ObjectType::Adapter: {
                Known<WGPUAdapter> obj;
                WIRE_TRY(AdapterObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.adapterRelease(obj->handle);
                }
                AdapterObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::BindGroup: {
                Known<WGPUBindGroup> obj;
                WIRE_TRY(BindGroupObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.bindGroupRelease(obj->handle);
                }
                BindGroupObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::BindGroupLayout: {
                Known<WGPUBindGroupLayout> obj;
                WIRE_TRY(BindGroupLayoutObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.bindGroupLayoutRelease(obj->handle);
                }
                BindGroupLayoutObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::Buffer: {
                Known<WGPUBuffer> obj;
                WIRE_TRY(BufferObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.bufferRelease(obj->handle);
                }
                BufferObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::CommandBuffer: {
                Known<WGPUCommandBuffer> obj;
                WIRE_TRY(CommandBufferObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.commandBufferRelease(obj->handle);
                }
                CommandBufferObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::CommandEncoder: {
                Known<WGPUCommandEncoder> obj;
                WIRE_TRY(CommandEncoderObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.commandEncoderRelease(obj->handle);
                }
                CommandEncoderObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::ComputePassEncoder: {
                Known<WGPUComputePassEncoder> obj;
                WIRE_TRY(ComputePassEncoderObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.computePassEncoderRelease(obj->handle);
                }
                ComputePassEncoderObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::ComputePipeline: {
                Known<WGPUComputePipeline> obj;
                WIRE_TRY(ComputePipelineObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.computePipelineRelease(obj->handle);
                }
                ComputePipelineObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::Device: {
                Known<WGPUDevice> obj;
                WIRE_TRY(DeviceObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);

                    if (obj->handle != nullptr) {
                        ClearDeviceCallbacks(obj->handle);
                    }

                    mProcs.deviceRelease(obj->handle);
                }
                DeviceObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::ExternalTexture: {
                Known<WGPUExternalTexture> obj;
                WIRE_TRY(ExternalTextureObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.externalTextureRelease(obj->handle);
                }
                ExternalTextureObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::Instance: {
                Known<WGPUInstance> obj;
                WIRE_TRY(InstanceObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.instanceRelease(obj->handle);
                }
                InstanceObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::PipelineLayout: {
                Known<WGPUPipelineLayout> obj;
                WIRE_TRY(PipelineLayoutObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.pipelineLayoutRelease(obj->handle);
                }
                PipelineLayoutObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::QuerySet: {
                Known<WGPUQuerySet> obj;
                WIRE_TRY(QuerySetObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.querySetRelease(obj->handle);
                }
                QuerySetObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::Queue: {
                Known<WGPUQueue> obj;
                WIRE_TRY(QueueObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.queueRelease(obj->handle);
                }
                QueueObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::RenderBundle: {
                Known<WGPURenderBundle> obj;
                WIRE_TRY(RenderBundleObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.renderBundleRelease(obj->handle);
                }
                RenderBundleObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::RenderBundleEncoder: {
                Known<WGPURenderBundleEncoder> obj;
                WIRE_TRY(RenderBundleEncoderObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.renderBundleEncoderRelease(obj->handle);
                }
                RenderBundleEncoderObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::RenderPassEncoder: {
                Known<WGPURenderPassEncoder> obj;
                WIRE_TRY(RenderPassEncoderObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.renderPassEncoderRelease(obj->handle);
                }
                RenderPassEncoderObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::RenderPipeline: {
                Known<WGPURenderPipeline> obj;
                WIRE_TRY(RenderPipelineObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.renderPipelineRelease(obj->handle);
                }
                RenderPipelineObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::Sampler: {
                Known<WGPUSampler> obj;
                WIRE_TRY(SamplerObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.samplerRelease(obj->handle);
                }
                SamplerObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::ShaderModule: {
                Known<WGPUShaderModule> obj;
                WIRE_TRY(ShaderModuleObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.shaderModuleRelease(obj->handle);
                }
                ShaderModuleObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::Surface: {
                Known<WGPUSurface> obj;
                WIRE_TRY(SurfaceObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.surfaceRelease(obj->handle);
                }
                SurfaceObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::SwapChain: {
                Known<WGPUSwapChain> obj;
                WIRE_TRY(SwapChainObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.swapChainRelease(obj->handle);
                }
                SwapChainObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::Texture: {
                Known<WGPUTexture> obj;
                WIRE_TRY(TextureObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.textureRelease(obj->handle);
                }
                TextureObjects().Free(objectId);
                return WireResult::Success;
            }
            case ObjectType::TextureView: {
                Known<WGPUTextureView> obj;
                WIRE_TRY(TextureViewObjects().Get(objectId, &obj));

                if (obj->state == AllocationState::Allocated) {
                    ASSERT(obj->handle != nullptr);


                    mProcs.textureViewRelease(obj->handle);
                }
                TextureViewObjects().Free(objectId);
                return WireResult::Success;
            }
            default:
                return WireResult::FatalError;
        }
    }

}  // namespace dawn::wire::server
