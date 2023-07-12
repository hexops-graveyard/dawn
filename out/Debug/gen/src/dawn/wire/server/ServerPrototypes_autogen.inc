
// Command handlers & doers
WireResult HandleAdapterGetInstance(DeserializeBuffer* deserializeBuffer);

WireResult DoAdapterGetInstance(WGPUAdapter self, WGPUInstance* result);
WireResult HandleAdapterRequestDevice(DeserializeBuffer* deserializeBuffer);

WireResult DoAdapterRequestDevice(Known<WGPUAdapter> adapterId, uint64_t requestSerial, ObjectHandle deviceObjectHandle, WGPUDeviceDescriptor const * descriptor);
WireResult HandleBindGroupLayoutSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoBindGroupLayoutSetLabel(WGPUBindGroupLayout self, char const * label);
WireResult HandleBindGroupSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoBindGroupSetLabel(WGPUBindGroup self, char const * label);
WireResult HandleBufferDestroy(DeserializeBuffer* deserializeBuffer);

WireResult DoBufferDestroy(WGPUBuffer self);
WireResult HandleBufferMapAsync(DeserializeBuffer* deserializeBuffer);

WireResult DoBufferMapAsync(Known<WGPUBuffer> bufferId, uint64_t requestSerial, WGPUMapModeFlags mode, uint64_t offset, uint64_t size);
WireResult HandleBufferSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoBufferSetLabel(WGPUBuffer self, char const * label);
WireResult HandleBufferUnmap(DeserializeBuffer* deserializeBuffer);

WireResult DoBufferUnmap(WGPUBuffer self);
WireResult HandleBufferUpdateMappedData(DeserializeBuffer* deserializeBuffer);

WireResult DoBufferUpdateMappedData(Known<WGPUBuffer> bufferId, uint64_t writeDataUpdateInfoLength, uint8_t const * writeDataUpdateInfo, uint64_t offset, uint64_t size);
WireResult HandleCommandBufferSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandBufferSetLabel(WGPUCommandBuffer self, char const * label);
WireResult HandleCommandEncoderBeginComputePass(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderBeginComputePass(WGPUCommandEncoder self, WGPUComputePassDescriptor const * descriptor, WGPUComputePassEncoder* result);
WireResult HandleCommandEncoderBeginRenderPass(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderBeginRenderPass(WGPUCommandEncoder self, WGPURenderPassDescriptor const * descriptor, WGPURenderPassEncoder* result);
WireResult HandleCommandEncoderClearBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderClearBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size);
WireResult HandleCommandEncoderCopyBufferToBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder self, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
WireResult HandleCommandEncoderCopyBufferToTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderCopyBufferToTexture(WGPUCommandEncoder self, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
WireResult HandleCommandEncoderCopyTextureToBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize);
WireResult HandleCommandEncoderCopyTextureToTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderCopyTextureToTexture(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
WireResult HandleCommandEncoderCopyTextureToTextureInternal(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
WireResult HandleCommandEncoderFinish(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderFinish(WGPUCommandEncoder self, WGPUCommandBufferDescriptor const * descriptor, WGPUCommandBuffer* result);
WireResult HandleCommandEncoderInjectValidationError(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderInjectValidationError(WGPUCommandEncoder self, char const * message);
WireResult HandleCommandEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderInsertDebugMarker(WGPUCommandEncoder self, char const * markerLabel);
WireResult HandleCommandEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderPopDebugGroup(WGPUCommandEncoder self);
WireResult HandleCommandEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderPushDebugGroup(WGPUCommandEncoder self, char const * groupLabel);
WireResult HandleCommandEncoderResolveQuerySet(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderResolveQuerySet(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset);
WireResult HandleCommandEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderSetLabel(WGPUCommandEncoder self, char const * label);
WireResult HandleCommandEncoderWriteBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderWriteBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size);
WireResult HandleCommandEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer);

WireResult DoCommandEncoderWriteTimestamp(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
WireResult HandleComputePassEncoderDispatchWorkgroups(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder self, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ);
WireResult HandleComputePassEncoderDispatchWorkgroupsIndirect(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WireResult HandleComputePassEncoderEnd(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderEnd(WGPUComputePassEncoder self);
WireResult HandleComputePassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder self, char const * markerLabel);
WireResult HandleComputePassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderPopDebugGroup(WGPUComputePassEncoder self);
WireResult HandleComputePassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderPushDebugGroup(WGPUComputePassEncoder self, char const * groupLabel);
WireResult HandleComputePassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderSetBindGroup(WGPUComputePassEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
WireResult HandleComputePassEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderSetLabel(WGPUComputePassEncoder self, char const * label);
WireResult HandleComputePassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderSetPipeline(WGPUComputePassEncoder self, WGPUComputePipeline pipeline);
WireResult HandleComputePassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePassEncoderWriteTimestamp(WGPUComputePassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
WireResult HandleComputePipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePipelineGetBindGroupLayout(WGPUComputePipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result);
WireResult HandleComputePipelineSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoComputePipelineSetLabel(WGPUComputePipeline self, char const * label);
WireResult HandleDestroyObject(DeserializeBuffer* deserializeBuffer);

WireResult DoDestroyObject(ObjectType objectType, ObjectId objectId);
WireResult HandleDeviceCreateBindGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateBindGroup(WGPUDevice self, WGPUBindGroupDescriptor const * descriptor, WGPUBindGroup* result);
WireResult HandleDeviceCreateBindGroupLayout(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateBindGroupLayout(WGPUDevice self, WGPUBindGroupLayoutDescriptor const * descriptor, WGPUBindGroupLayout* result);
WireResult HandleDeviceCreateBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateBuffer(Known<WGPUDevice> deviceId, WGPUBufferDescriptor const * descriptor, ObjectHandle result, uint64_t readHandleCreateInfoLength, uint8_t const * readHandleCreateInfo, uint64_t writeHandleCreateInfoLength, uint8_t const * writeHandleCreateInfo);
WireResult HandleDeviceCreateCommandEncoder(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateCommandEncoder(WGPUDevice self, WGPUCommandEncoderDescriptor const * descriptor, WGPUCommandEncoder* result);
WireResult HandleDeviceCreateComputePipeline(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor, WGPUComputePipeline* result);
WireResult HandleDeviceCreateComputePipelineAsync(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateComputePipelineAsync(Known<WGPUDevice> deviceId, uint64_t requestSerial, ObjectHandle pipelineObjectHandle, WGPUComputePipelineDescriptor const * descriptor);
WireResult HandleDeviceCreateErrorBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateErrorBuffer(WGPUDevice self, WGPUBufferDescriptor const * descriptor, WGPUBuffer* result);
WireResult HandleDeviceCreateErrorExternalTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateErrorExternalTexture(WGPUDevice self, WGPUExternalTexture* result);
WireResult HandleDeviceCreateErrorShaderModule(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateErrorShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage, WGPUShaderModule* result);
WireResult HandleDeviceCreateErrorTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateErrorTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor, WGPUTexture* result);
WireResult HandleDeviceCreateExternalTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateExternalTexture(WGPUDevice self, WGPUExternalTextureDescriptor const * externalTextureDescriptor, WGPUExternalTexture* result);
WireResult HandleDeviceCreatePipelineLayout(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreatePipelineLayout(WGPUDevice self, WGPUPipelineLayoutDescriptor const * descriptor, WGPUPipelineLayout* result);
WireResult HandleDeviceCreateQuerySet(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateQuerySet(WGPUDevice self, WGPUQuerySetDescriptor const * descriptor, WGPUQuerySet* result);
WireResult HandleDeviceCreateRenderBundleEncoder(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateRenderBundleEncoder(WGPUDevice self, WGPURenderBundleEncoderDescriptor const * descriptor, WGPURenderBundleEncoder* result);
WireResult HandleDeviceCreateRenderPipeline(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor, WGPURenderPipeline* result);
WireResult HandleDeviceCreateRenderPipelineAsync(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateRenderPipelineAsync(Known<WGPUDevice> deviceId, uint64_t requestSerial, ObjectHandle pipelineObjectHandle, WGPURenderPipelineDescriptor const * descriptor);
WireResult HandleDeviceCreateSampler(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateSampler(WGPUDevice self, WGPUSamplerDescriptor const * descriptor, WGPUSampler* result);
WireResult HandleDeviceCreateShaderModule(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, WGPUShaderModule* result);
WireResult HandleDeviceCreateSwapChain(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateSwapChain(WGPUDevice self, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor, WGPUSwapChain* result);
WireResult HandleDeviceCreateTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceCreateTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor, WGPUTexture* result);
WireResult HandleDeviceDestroy(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceDestroy(WGPUDevice self);
WireResult HandleDeviceForceLoss(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceForceLoss(WGPUDevice self, WGPUDeviceLostReason type, char const * message);
WireResult HandleDeviceGetAdapter(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceGetAdapter(WGPUDevice self, WGPUAdapter* result);
WireResult HandleDeviceGetQueue(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceGetQueue(WGPUDevice self, WGPUQueue* result);
WireResult HandleDeviceInjectError(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceInjectError(WGPUDevice self, WGPUErrorType type, char const * message);
WireResult HandleDevicePopErrorScope(DeserializeBuffer* deserializeBuffer);

WireResult DoDevicePopErrorScope(Known<WGPUDevice> deviceId, uint64_t requestSerial);
WireResult HandleDevicePushErrorScope(DeserializeBuffer* deserializeBuffer);

WireResult DoDevicePushErrorScope(WGPUDevice self, WGPUErrorFilter filter);
WireResult HandleDeviceSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceSetLabel(WGPUDevice self, char const * label);
WireResult HandleDeviceTick(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceTick(WGPUDevice self);
WireResult HandleDeviceValidateTextureDescriptor(DeserializeBuffer* deserializeBuffer);

WireResult DoDeviceValidateTextureDescriptor(WGPUDevice self, WGPUTextureDescriptor const * descriptor);
WireResult HandleExternalTextureDestroy(DeserializeBuffer* deserializeBuffer);

WireResult DoExternalTextureDestroy(WGPUExternalTexture self);
WireResult HandleExternalTextureExpire(DeserializeBuffer* deserializeBuffer);

WireResult DoExternalTextureExpire(WGPUExternalTexture self);
WireResult HandleExternalTextureRefresh(DeserializeBuffer* deserializeBuffer);

WireResult DoExternalTextureRefresh(WGPUExternalTexture self);
WireResult HandleExternalTextureSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoExternalTextureSetLabel(WGPUExternalTexture self, char const * label);
WireResult HandleInstanceCreateSurface(DeserializeBuffer* deserializeBuffer);

WireResult DoInstanceCreateSurface(WGPUInstance self, WGPUSurfaceDescriptor const * descriptor, WGPUSurface* result);
WireResult HandleInstanceProcessEvents(DeserializeBuffer* deserializeBuffer);

WireResult DoInstanceProcessEvents(WGPUInstance self);
WireResult HandleInstanceRequestAdapter(DeserializeBuffer* deserializeBuffer);

WireResult DoInstanceRequestAdapter(Known<WGPUInstance> instanceId, uint64_t requestSerial, ObjectHandle adapterObjectHandle, WGPURequestAdapterOptions const * options);
WireResult HandlePipelineLayoutSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoPipelineLayoutSetLabel(WGPUPipelineLayout self, char const * label);
WireResult HandleQuerySetDestroy(DeserializeBuffer* deserializeBuffer);

WireResult DoQuerySetDestroy(WGPUQuerySet self);
WireResult HandleQuerySetSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoQuerySetSetLabel(WGPUQuerySet self, char const * label);
WireResult HandleQueueCopyExternalTextureForBrowser(DeserializeBuffer* deserializeBuffer);

WireResult DoQueueCopyExternalTextureForBrowser(WGPUQueue self, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options);
WireResult HandleQueueCopyTextureForBrowser(DeserializeBuffer* deserializeBuffer);

WireResult DoQueueCopyTextureForBrowser(WGPUQueue self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options);
WireResult HandleQueueOnSubmittedWorkDone(DeserializeBuffer* deserializeBuffer);

WireResult DoQueueOnSubmittedWorkDone(Known<WGPUQueue> queueId, uint64_t signalValue, uint64_t requestSerial);
WireResult HandleQueueSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoQueueSetLabel(WGPUQueue self, char const * label);
WireResult HandleQueueSubmit(DeserializeBuffer* deserializeBuffer);

WireResult DoQueueSubmit(WGPUQueue self, size_t commandCount, WGPUCommandBuffer const * commands);
WireResult HandleQueueWriteBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoQueueWriteBuffer(Known<WGPUQueue> queueId, Known<WGPUBuffer> bufferId, uint64_t bufferOffset, uint8_t const * data, uint64_t size);
WireResult HandleQueueWriteTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoQueueWriteTexture(Known<WGPUQueue> queueId, WGPUImageCopyTexture const * destination, uint8_t const * data, uint64_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize);
WireResult HandleRenderBundleEncoderDraw(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderDraw(WGPURenderBundleEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
WireResult HandleRenderBundleEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
WireResult HandleRenderBundleEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WireResult HandleRenderBundleEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WireResult HandleRenderBundleEncoderFinish(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderFinish(WGPURenderBundleEncoder self, WGPURenderBundleDescriptor const * descriptor, WGPURenderBundle* result);
WireResult HandleRenderBundleEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder self, char const * markerLabel);
WireResult HandleRenderBundleEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder self);
WireResult HandleRenderBundleEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder self, char const * groupLabel);
WireResult HandleRenderBundleEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
WireResult HandleRenderBundleEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
WireResult HandleRenderBundleEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderSetLabel(WGPURenderBundleEncoder self, char const * label);
WireResult HandleRenderBundleEncoderSetPipeline(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder self, WGPURenderPipeline pipeline);
WireResult HandleRenderBundleEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
WireResult HandleRenderBundleSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderBundleSetLabel(WGPURenderBundle self, char const * label);
WireResult HandleRenderPassEncoderBeginOcclusionQuery(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder self, uint32_t queryIndex);
WireResult HandleRenderPassEncoderDraw(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderDraw(WGPURenderPassEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
WireResult HandleRenderPassEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderDrawIndexed(WGPURenderPassEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
WireResult HandleRenderPassEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WireResult HandleRenderPassEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderDrawIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WireResult HandleRenderPassEncoderEnd(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderEnd(WGPURenderPassEncoder self);
WireResult HandleRenderPassEncoderEndOcclusionQuery(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder self);
WireResult HandleRenderPassEncoderExecuteBundles(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderExecuteBundles(WGPURenderPassEncoder self, size_t bundleCount, WGPURenderBundle const * bundles);
WireResult HandleRenderPassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder self, char const * markerLabel);
WireResult HandleRenderPassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder self);
WireResult HandleRenderPassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder self, char const * groupLabel);
WireResult HandleRenderPassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetBindGroup(WGPURenderPassEncoder self, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
WireResult HandleRenderPassEncoderSetBlendConstant(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder self, WGPUColor const * color);
WireResult HandleRenderPassEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
WireResult HandleRenderPassEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetLabel(WGPURenderPassEncoder self, char const * label);
WireResult HandleRenderPassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetPipeline(WGPURenderPassEncoder self, WGPURenderPipeline pipeline);
WireResult HandleRenderPassEncoderSetScissorRect(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetScissorRect(WGPURenderPassEncoder self, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
WireResult HandleRenderPassEncoderSetStencilReference(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetStencilReference(WGPURenderPassEncoder self, uint32_t reference);
WireResult HandleRenderPassEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
WireResult HandleRenderPassEncoderSetViewport(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderSetViewport(WGPURenderPassEncoder self, float x, float y, float width, float height, float minDepth, float maxDepth);
WireResult HandleRenderPassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
WireResult HandleRenderPipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPipelineGetBindGroupLayout(WGPURenderPipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result);
WireResult HandleRenderPipelineSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoRenderPipelineSetLabel(WGPURenderPipeline self, char const * label);
WireResult HandleSamplerSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoSamplerSetLabel(WGPUSampler self, char const * label);
WireResult HandleShaderModuleGetCompilationInfo(DeserializeBuffer* deserializeBuffer);

WireResult DoShaderModuleGetCompilationInfo(Known<WGPUShaderModule> shaderModuleId, uint64_t requestSerial);
WireResult HandleShaderModuleSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoShaderModuleSetLabel(WGPUShaderModule self, char const * label);
WireResult HandleSwapChainGetCurrentTexture(DeserializeBuffer* deserializeBuffer);

WireResult DoSwapChainGetCurrentTexture(WGPUSwapChain self, WGPUTexture* result);
WireResult HandleSwapChainGetCurrentTextureView(DeserializeBuffer* deserializeBuffer);

WireResult DoSwapChainGetCurrentTextureView(WGPUSwapChain self, WGPUTextureView* result);
WireResult HandleSwapChainPresent(DeserializeBuffer* deserializeBuffer);

WireResult DoSwapChainPresent(WGPUSwapChain self);
WireResult HandleTextureCreateView(DeserializeBuffer* deserializeBuffer);

WireResult DoTextureCreateView(WGPUTexture self, WGPUTextureViewDescriptor const * descriptor, WGPUTextureView* result);
WireResult HandleTextureDestroy(DeserializeBuffer* deserializeBuffer);

WireResult DoTextureDestroy(WGPUTexture self);
WireResult HandleTextureSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoTextureSetLabel(WGPUTexture self, char const * label);
WireResult HandleTextureViewSetLabel(DeserializeBuffer* deserializeBuffer);

WireResult DoTextureViewSetLabel(WGPUTextureView self, char const * label);

WireResult PreHandleBufferDestroy(const BufferDestroyCmd& cmd);
WireResult PreHandleBufferUnmap(const BufferUnmapCmd& cmd);
