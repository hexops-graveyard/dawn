
bool HandleAdapterRequestDeviceCallback(DeserializeBuffer* deserializeBuffer);
bool HandleBufferMapAsyncCallback(DeserializeBuffer* deserializeBuffer);
bool HandleDeviceCreateComputePipelineAsyncCallback(DeserializeBuffer* deserializeBuffer);
bool HandleDeviceCreateRenderPipelineAsyncCallback(DeserializeBuffer* deserializeBuffer);
bool HandleDeviceLoggingCallback(DeserializeBuffer* deserializeBuffer);
bool HandleDeviceLostCallback(DeserializeBuffer* deserializeBuffer);
bool HandleDevicePopErrorScopeCallback(DeserializeBuffer* deserializeBuffer);
bool HandleDeviceUncapturedErrorCallback(DeserializeBuffer* deserializeBuffer);
bool HandleInstanceRequestAdapterCallback(DeserializeBuffer* deserializeBuffer);
bool HandleQueueWorkDoneCallback(DeserializeBuffer* deserializeBuffer);
bool HandleShaderModuleGetCompilationInfoCallback(DeserializeBuffer* deserializeBuffer);

bool DoAdapterRequestDeviceCallback(Adapter* adapter, uint64_t requestSerial, WGPURequestDeviceStatus status, char const * message, WGPUSupportedLimits const * limits, uint32_t featuresCount, WGPUFeatureName const * features);
bool DoBufferMapAsyncCallback(Buffer* buffer, uint64_t requestSerial, uint32_t status, uint64_t readDataUpdateInfoLength, uint8_t const * readDataUpdateInfo);
bool DoDeviceCreateComputePipelineAsyncCallback(Device* device, uint64_t requestSerial, WGPUCreatePipelineAsyncStatus status, char const * message);
bool DoDeviceCreateRenderPipelineAsyncCallback(Device* device, uint64_t requestSerial, WGPUCreatePipelineAsyncStatus status, char const * message);
bool DoDeviceLoggingCallback(Device* device, WGPULoggingType type, char const * message);
bool DoDeviceLostCallback(Device* device, WGPUDeviceLostReason reason, char const * message);
bool DoDevicePopErrorScopeCallback(Device* device, uint64_t requestSerial, WGPUErrorType type, char const * message);
bool DoDeviceUncapturedErrorCallback(Device* device, WGPUErrorType type, char const * message);
bool DoInstanceRequestAdapterCallback(Instance* instance, uint64_t requestSerial, WGPURequestAdapterStatus status, char const * message, WGPUAdapterProperties const * properties, WGPUSupportedLimits const * limits, uint32_t featuresCount, WGPUFeatureName const * features);
bool DoQueueWorkDoneCallback(Queue* queue, uint64_t requestSerial, WGPUQueueWorkDoneStatus status);
bool DoShaderModuleGetCompilationInfoCallback(ShaderModule* shaderModule, uint64_t requestSerial, WGPUCompilationInfoRequestStatus status, WGPUCompilationInfo const * info);
