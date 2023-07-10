
#ifndef BACKEND_VALIDATIONUTILS_H_
#define BACKEND_VALIDATIONUTILS_H_

#include "dawn/webgpu_cpp.h"

#include "dawn/native/Error.h"

namespace dawn::native {

    // Helper functions to check the value of enums and bitmasks
    MaybeError ValidateAdapterType(wgpu::AdapterType value);
    MaybeError ValidateAddressMode(wgpu::AddressMode value);
    MaybeError ValidateAlphaMode(wgpu::AlphaMode value);
    MaybeError ValidateBackendType(wgpu::BackendType value);
    MaybeError ValidateBlendFactor(wgpu::BlendFactor value);
    MaybeError ValidateBlendOperation(wgpu::BlendOperation value);
    MaybeError ValidateBufferBindingType(wgpu::BufferBindingType value);
    MaybeError ValidateBufferMapAsyncStatus(wgpu::BufferMapAsyncStatus value);
    MaybeError ValidateBufferMapState(wgpu::BufferMapState value);
    MaybeError ValidateCompareFunction(wgpu::CompareFunction value);
    MaybeError ValidateCompilationInfoRequestStatus(wgpu::CompilationInfoRequestStatus value);
    MaybeError ValidateCompilationMessageType(wgpu::CompilationMessageType value);
    MaybeError ValidateComputePassTimestampLocation(wgpu::ComputePassTimestampLocation value);
    MaybeError ValidateCreatePipelineAsyncStatus(wgpu::CreatePipelineAsyncStatus value);
    MaybeError ValidateCullMode(wgpu::CullMode value);
    MaybeError ValidateDeviceLostReason(wgpu::DeviceLostReason value);
    MaybeError ValidateErrorFilter(wgpu::ErrorFilter value);
    MaybeError ValidateErrorType(wgpu::ErrorType value);
    MaybeError ValidateExternalTextureRotation(wgpu::ExternalTextureRotation value);
    MaybeError ValidateFeatureName(wgpu::FeatureName value);
    MaybeError ValidateFilterMode(wgpu::FilterMode value);
    MaybeError ValidateFrontFace(wgpu::FrontFace value);
    MaybeError ValidateIndexFormat(wgpu::IndexFormat value);
    MaybeError ValidateLoadOp(wgpu::LoadOp value);
    MaybeError ValidateLoggingType(wgpu::LoggingType value);
    MaybeError ValidateMipmapFilterMode(wgpu::MipmapFilterMode value);
    MaybeError ValidatePipelineStatisticName(wgpu::PipelineStatisticName value);
    MaybeError ValidatePowerPreference(wgpu::PowerPreference value);
    MaybeError ValidatePresentMode(wgpu::PresentMode value);
    MaybeError ValidatePrimitiveTopology(wgpu::PrimitiveTopology value);
    MaybeError ValidateQueryType(wgpu::QueryType value);
    MaybeError ValidateQueueWorkDoneStatus(wgpu::QueueWorkDoneStatus value);
    MaybeError ValidateRenderPassTimestampLocation(wgpu::RenderPassTimestampLocation value);
    MaybeError ValidateRequestAdapterStatus(wgpu::RequestAdapterStatus value);
    MaybeError ValidateRequestDeviceStatus(wgpu::RequestDeviceStatus value);
    MaybeError ValidateSType(wgpu::SType value);
    MaybeError ValidateSamplerBindingType(wgpu::SamplerBindingType value);
    MaybeError ValidateStencilOperation(wgpu::StencilOperation value);
    MaybeError ValidateStorageTextureAccess(wgpu::StorageTextureAccess value);
    MaybeError ValidateStoreOp(wgpu::StoreOp value);
    MaybeError ValidateTextureAspect(wgpu::TextureAspect value);
    MaybeError ValidateTextureDimension(wgpu::TextureDimension value);
    MaybeError ValidateTextureFormat(wgpu::TextureFormat value);
    MaybeError ValidateTextureSampleType(wgpu::TextureSampleType value);
    MaybeError ValidateTextureViewDimension(wgpu::TextureViewDimension value);
    MaybeError ValidateVertexFormat(wgpu::VertexFormat value);
    MaybeError ValidateVertexStepMode(wgpu::VertexStepMode value);
    MaybeError ValidateBufferUsage(wgpu::BufferUsage value);
    MaybeError ValidateColorWriteMask(wgpu::ColorWriteMask value);
    MaybeError ValidateMapMode(wgpu::MapMode value);
    MaybeError ValidateShaderStage(wgpu::ShaderStage value);
    MaybeError ValidateTextureUsage(wgpu::TextureUsage value);

} // namespace dawn::native

#endif  // BACKEND_VALIDATIONUTILS_H_
