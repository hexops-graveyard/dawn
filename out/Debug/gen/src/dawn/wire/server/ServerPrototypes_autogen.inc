
// Command handlers & doers
bool HandleAdapterRequestDevice(DeserializeBuffer* deserializeBuffer);

bool DoAdapterRequestDevice(ObjectId adapterId, uint64_t requestSerial, ObjectHandle deviceObjectHandle, WGPUDeviceDescriptor const * descriptor);
bool HandleBindGroupLayoutSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoBindGroupLayoutSetLabel(WGPUBindGroupLayout self, char const * label);
bool HandleBindGroupSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoBindGroupSetLabel(WGPUBindGroup self, char const * label);
bool HandleBufferDestroy(DeserializeBuffer* deserializeBuffer);

bool DoBufferDestroy(WGPUBuffer self);
bool HandleBufferMapAsync(DeserializeBuffer* deserializeBuffer);

bool DoBufferMapAsync(ObjectId bufferId, uint64_t requestSerial, WGPUMapModeFlags mode, uint64_t offset, uint64_t size);
bool HandleBufferSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoBufferSetLabel(WGPUBuffer self, char const * label);
bool HandleBufferUnmap(DeserializeBuffer* deserializeBuffer);

bool DoBufferUnmap(WGPUBuffer self);
bool HandleBufferUpdateMappedData(DeserializeBuffer* deserializeBuffer);

bool DoBufferUpdateMappedData(ObjectId bufferId, uint64_t writeDataUpdateInfoLength, uint8_t const * writeDataUpdateInfo, uint64_t offset, uint64_t size);
bool HandleCommandBufferSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoCommandBufferSetLabel(WGPUCommandBuffer self, char const * label);
bool HandleCommandEncoderBeginComputePass(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderBeginComputePass(WGPUCommandEncoder self, WGPUComputePassDescriptor const * descriptor, WGPUComputePassEncoder* result);
bool HandleCommandEncoderBeginRenderPass(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderBeginRenderPass(WGPUCommandEncoder self, WGPURenderPassDescriptor const * descriptor, WGPURenderPassEncoder* result);
bool HandleCommandEncoderClearBuffer(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderClearBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t offset, uint64_t size);
bool HandleCommandEncoderCopyBufferToBuffer(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder self, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
bool HandleCommandEncoderCopyBufferToTexture(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderCopyBufferToTexture(WGPUCommandEncoder self, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
bool HandleCommandEncoderCopyTextureToBuffer(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize);
bool HandleCommandEncoderCopyTextureToTexture(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderCopyTextureToTexture(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
bool HandleCommandEncoderCopyTextureToTextureInternal(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize);
bool HandleCommandEncoderFinish(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderFinish(WGPUCommandEncoder self, WGPUCommandBufferDescriptor const * descriptor, WGPUCommandBuffer* result);
bool HandleCommandEncoderInjectValidationError(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderInjectValidationError(WGPUCommandEncoder self, char const * message);
bool HandleCommandEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderInsertDebugMarker(WGPUCommandEncoder self, char const * markerLabel);
bool HandleCommandEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderPopDebugGroup(WGPUCommandEncoder self);
bool HandleCommandEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderPushDebugGroup(WGPUCommandEncoder self, char const * groupLabel);
bool HandleCommandEncoderResolveQuerySet(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderResolveQuerySet(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset);
bool HandleCommandEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderSetLabel(WGPUCommandEncoder self, char const * label);
bool HandleCommandEncoderWriteBuffer(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderWriteBuffer(WGPUCommandEncoder self, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size);
bool HandleCommandEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer);

bool DoCommandEncoderWriteTimestamp(WGPUCommandEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
bool HandleComputePassEncoderDispatch(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderDispatch(WGPUComputePassEncoder self, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ);
bool HandleComputePassEncoderDispatchIndirect(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderDispatchIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleComputePassEncoderDispatchWorkgroups(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder self, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ);
bool HandleComputePassEncoderDispatchWorkgroupsIndirect(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleComputePassEncoderEnd(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderEnd(WGPUComputePassEncoder self);
bool HandleComputePassEncoderEndPass(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderEndPass(WGPUComputePassEncoder self);
bool HandleComputePassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder self, char const * markerLabel);
bool HandleComputePassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderPopDebugGroup(WGPUComputePassEncoder self);
bool HandleComputePassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderPushDebugGroup(WGPUComputePassEncoder self, char const * groupLabel);
bool HandleComputePassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderSetBindGroup(WGPUComputePassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
bool HandleComputePassEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderSetLabel(WGPUComputePassEncoder self, char const * label);
bool HandleComputePassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderSetPipeline(WGPUComputePassEncoder self, WGPUComputePipeline pipeline);
bool HandleComputePassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer);

bool DoComputePassEncoderWriteTimestamp(WGPUComputePassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
bool HandleComputePipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer);

bool DoComputePipelineGetBindGroupLayout(WGPUComputePipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result);
bool HandleComputePipelineSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoComputePipelineSetLabel(WGPUComputePipeline self, char const * label);
bool HandleDestroyObject(DeserializeBuffer* deserializeBuffer);

bool DoDestroyObject(ObjectType objectType, ObjectId objectId);
bool HandleDeviceCreateBindGroup(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateBindGroup(WGPUDevice self, WGPUBindGroupDescriptor const * descriptor, WGPUBindGroup* result);
bool HandleDeviceCreateBindGroupLayout(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateBindGroupLayout(WGPUDevice self, WGPUBindGroupLayoutDescriptor const * descriptor, WGPUBindGroupLayout* result);
bool HandleDeviceCreateBuffer(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateBuffer(ObjectId deviceId, WGPUBufferDescriptor const * descriptor, ObjectHandle result, uint64_t readHandleCreateInfoLength, uint8_t const * readHandleCreateInfo, uint64_t writeHandleCreateInfoLength, uint8_t const * writeHandleCreateInfo);
bool HandleDeviceCreateCommandEncoder(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateCommandEncoder(WGPUDevice self, WGPUCommandEncoderDescriptor const * descriptor, WGPUCommandEncoder* result);
bool HandleDeviceCreateComputePipeline(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateComputePipeline(WGPUDevice self, WGPUComputePipelineDescriptor const * descriptor, WGPUComputePipeline* result);
bool HandleDeviceCreateComputePipelineAsync(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateComputePipelineAsync(ObjectId deviceId, uint64_t requestSerial, ObjectHandle pipelineObjectHandle, WGPUComputePipelineDescriptor const * descriptor);
bool HandleDeviceCreateErrorBuffer(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateErrorBuffer(WGPUDevice self, WGPUBuffer* result);
bool HandleDeviceCreateErrorExternalTexture(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateErrorExternalTexture(WGPUDevice self, WGPUExternalTexture* result);
bool HandleDeviceCreateExternalTexture(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateExternalTexture(WGPUDevice self, WGPUExternalTextureDescriptor const * externalTextureDescriptor, WGPUExternalTexture* result);
bool HandleDeviceCreatePipelineLayout(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreatePipelineLayout(WGPUDevice self, WGPUPipelineLayoutDescriptor const * descriptor, WGPUPipelineLayout* result);
bool HandleDeviceCreateQuerySet(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateQuerySet(WGPUDevice self, WGPUQuerySetDescriptor const * descriptor, WGPUQuerySet* result);
bool HandleDeviceCreateRenderBundleEncoder(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateRenderBundleEncoder(WGPUDevice self, WGPURenderBundleEncoderDescriptor const * descriptor, WGPURenderBundleEncoder* result);
bool HandleDeviceCreateRenderPipeline(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateRenderPipeline(WGPUDevice self, WGPURenderPipelineDescriptor const * descriptor, WGPURenderPipeline* result);
bool HandleDeviceCreateRenderPipelineAsync(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateRenderPipelineAsync(ObjectId deviceId, uint64_t requestSerial, ObjectHandle pipelineObjectHandle, WGPURenderPipelineDescriptor const * descriptor);
bool HandleDeviceCreateSampler(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateSampler(WGPUDevice self, WGPUSamplerDescriptor const * descriptor, WGPUSampler* result);
bool HandleDeviceCreateShaderModule(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateShaderModule(WGPUDevice self, WGPUShaderModuleDescriptor const * descriptor, WGPUShaderModule* result);
bool HandleDeviceCreateSwapChain(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateSwapChain(WGPUDevice self, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor, WGPUSwapChain* result);
bool HandleDeviceCreateTexture(DeserializeBuffer* deserializeBuffer);

bool DoDeviceCreateTexture(WGPUDevice self, WGPUTextureDescriptor const * descriptor, WGPUTexture* result);
bool HandleDeviceDestroy(DeserializeBuffer* deserializeBuffer);

bool DoDeviceDestroy(WGPUDevice self);
bool HandleDeviceGetQueue(DeserializeBuffer* deserializeBuffer);

bool DoDeviceGetQueue(WGPUDevice self, WGPUQueue* result);
bool HandleDeviceInjectError(DeserializeBuffer* deserializeBuffer);

bool DoDeviceInjectError(WGPUDevice self, WGPUErrorType type, char const * message);
bool HandleDeviceLoseForTesting(DeserializeBuffer* deserializeBuffer);

bool DoDeviceLoseForTesting(WGPUDevice self);
bool HandleDevicePopErrorScope(DeserializeBuffer* deserializeBuffer);

bool DoDevicePopErrorScope(ObjectId deviceId, uint64_t requestSerial);
bool HandleDevicePushErrorScope(DeserializeBuffer* deserializeBuffer);

bool DoDevicePushErrorScope(WGPUDevice self, WGPUErrorFilter filter);
bool HandleDeviceSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoDeviceSetLabel(WGPUDevice self, char const * label);
bool HandleDeviceTick(DeserializeBuffer* deserializeBuffer);

bool DoDeviceTick(WGPUDevice self);
bool HandleExternalTextureDestroy(DeserializeBuffer* deserializeBuffer);

bool DoExternalTextureDestroy(WGPUExternalTexture self);
bool HandleExternalTextureSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoExternalTextureSetLabel(WGPUExternalTexture self, char const * label);
bool HandleInstanceCreateSurface(DeserializeBuffer* deserializeBuffer);

bool DoInstanceCreateSurface(WGPUInstance self, WGPUSurfaceDescriptor const * descriptor, WGPUSurface* result);
bool HandleInstanceRequestAdapter(DeserializeBuffer* deserializeBuffer);

bool DoInstanceRequestAdapter(ObjectId instanceId, uint64_t requestSerial, ObjectHandle adapterObjectHandle, WGPURequestAdapterOptions const * options);
bool HandlePipelineLayoutSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoPipelineLayoutSetLabel(WGPUPipelineLayout self, char const * label);
bool HandleQuerySetDestroy(DeserializeBuffer* deserializeBuffer);

bool DoQuerySetDestroy(WGPUQuerySet self);
bool HandleQuerySetSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoQuerySetSetLabel(WGPUQuerySet self, char const * label);
bool HandleQueueCopyTextureForBrowser(DeserializeBuffer* deserializeBuffer);

bool DoQueueCopyTextureForBrowser(WGPUQueue self, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options);
bool HandleQueueOnSubmittedWorkDone(DeserializeBuffer* deserializeBuffer);

bool DoQueueOnSubmittedWorkDone(ObjectId queueId, uint64_t signalValue, uint64_t requestSerial);
bool HandleQueueSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoQueueSetLabel(WGPUQueue self, char const * label);
bool HandleQueueSubmit(DeserializeBuffer* deserializeBuffer);

bool DoQueueSubmit(WGPUQueue self, uint32_t commandCount, WGPUCommandBuffer const * commands);
bool HandleQueueWriteBuffer(DeserializeBuffer* deserializeBuffer);

bool DoQueueWriteBuffer(ObjectId queueId, ObjectId bufferId, uint64_t bufferOffset, uint8_t const * data, uint64_t size);
bool HandleQueueWriteTexture(DeserializeBuffer* deserializeBuffer);

bool DoQueueWriteTexture(ObjectId queueId, WGPUImageCopyTexture const * destination, uint8_t const * data, uint64_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize);
bool HandleRenderBundleEncoderDraw(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderDraw(WGPURenderBundleEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
bool HandleRenderBundleEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
bool HandleRenderBundleEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderBundleEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderBundleEncoderFinish(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderFinish(WGPURenderBundleEncoder self, WGPURenderBundleDescriptor const * descriptor, WGPURenderBundle* result);
bool HandleRenderBundleEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder self, char const * markerLabel);
bool HandleRenderBundleEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder self);
bool HandleRenderBundleEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder self, char const * groupLabel);
bool HandleRenderBundleEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
bool HandleRenderBundleEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
bool HandleRenderBundleEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderSetLabel(WGPURenderBundleEncoder self, char const * label);
bool HandleRenderBundleEncoderSetPipeline(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder self, WGPURenderPipeline pipeline);
bool HandleRenderBundleEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer);

bool DoRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
bool HandleRenderPassEncoderBeginOcclusionQuery(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder self, uint32_t queryIndex);
bool HandleRenderPassEncoderDraw(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderDraw(WGPURenderPassEncoder self, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
bool HandleRenderPassEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderDrawIndexed(WGPURenderPassEncoder self, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
bool HandleRenderPassEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderPassEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderDrawIndirect(WGPURenderPassEncoder self, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
bool HandleRenderPassEncoderEnd(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderEnd(WGPURenderPassEncoder self);
bool HandleRenderPassEncoderEndOcclusionQuery(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder self);
bool HandleRenderPassEncoderEndPass(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderEndPass(WGPURenderPassEncoder self);
bool HandleRenderPassEncoderExecuteBundles(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderExecuteBundles(WGPURenderPassEncoder self, uint32_t bundlesCount, WGPURenderBundle const * bundles);
bool HandleRenderPassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder self, char const * markerLabel);
bool HandleRenderPassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder self);
bool HandleRenderPassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder self, char const * groupLabel);
bool HandleRenderPassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetBindGroup(WGPURenderPassEncoder self, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
bool HandleRenderPassEncoderSetBlendConstant(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder self, WGPUColor const * color);
bool HandleRenderPassEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder self, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
bool HandleRenderPassEncoderSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetLabel(WGPURenderPassEncoder self, char const * label);
bool HandleRenderPassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetPipeline(WGPURenderPassEncoder self, WGPURenderPipeline pipeline);
bool HandleRenderPassEncoderSetScissorRect(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetScissorRect(WGPURenderPassEncoder self, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
bool HandleRenderPassEncoderSetStencilReference(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetStencilReference(WGPURenderPassEncoder self, uint32_t reference);
bool HandleRenderPassEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder self, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
bool HandleRenderPassEncoderSetViewport(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderSetViewport(WGPURenderPassEncoder self, float x, float y, float width, float height, float minDepth, float maxDepth);
bool HandleRenderPassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer);

bool DoRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder self, WGPUQuerySet querySet, uint32_t queryIndex);
bool HandleRenderPipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer);

bool DoRenderPipelineGetBindGroupLayout(WGPURenderPipeline self, uint32_t groupIndex, WGPUBindGroupLayout* result);
bool HandleRenderPipelineSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoRenderPipelineSetLabel(WGPURenderPipeline self, char const * label);
bool HandleSamplerSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoSamplerSetLabel(WGPUSampler self, char const * label);
bool HandleShaderModuleGetCompilationInfo(DeserializeBuffer* deserializeBuffer);

bool DoShaderModuleGetCompilationInfo(ObjectId shaderModuleId, uint64_t requestSerial);
bool HandleShaderModuleSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoShaderModuleSetLabel(WGPUShaderModule self, char const * label);
bool HandleSwapChainConfigure(DeserializeBuffer* deserializeBuffer);

bool DoSwapChainConfigure(WGPUSwapChain self, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height);
bool HandleSwapChainGetCurrentTextureView(DeserializeBuffer* deserializeBuffer);

bool DoSwapChainGetCurrentTextureView(WGPUSwapChain self, WGPUTextureView* result);
bool HandleSwapChainPresent(DeserializeBuffer* deserializeBuffer);

bool DoSwapChainPresent(WGPUSwapChain self);
bool HandleTextureCreateView(DeserializeBuffer* deserializeBuffer);

bool DoTextureCreateView(WGPUTexture self, WGPUTextureViewDescriptor const * descriptor, WGPUTextureView* result);
bool HandleTextureDestroy(DeserializeBuffer* deserializeBuffer);

bool DoTextureDestroy(WGPUTexture self);
bool HandleTextureSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoTextureSetLabel(WGPUTexture self, char const * label);
bool HandleTextureViewSetLabel(DeserializeBuffer* deserializeBuffer);

bool DoTextureViewSetLabel(WGPUTextureView self, char const * label);

bool PreHandleBufferDestroy(const BufferDestroyCmd& cmd);
bool PreHandleBufferUnmap(const BufferUnmapCmd& cmd);
