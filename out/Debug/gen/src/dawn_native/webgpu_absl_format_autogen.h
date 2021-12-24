
#ifndef WEBGPU_ABSL_FORMAT_H_
#define WEBGPU_ABSL_FORMAT_H_

#include "dawn_native/dawn_platform.h"

#include "absl/strings/str_format.h"

namespace dawn_native {

    //
    // Descriptors
    //

    // Only includes structures that have a 'label' member.
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BufferDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const CommandBufferDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const CommandEncoderDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ComputePassDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ExternalTextureDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const PipelineLayoutDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const QuerySetDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderBundleDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderBundleEncoderDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SamplerDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ShaderModuleDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SurfaceDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SwapChainDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureViewDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BindGroupDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BindGroupLayoutDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ComputePipelineDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const DeviceDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderPassDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderPipelineDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
} // namespace dawn_native

namespace wgpu {

    //
    // Enums
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(AdapterType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(AddressMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(AlphaMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BackendType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BlendFactor value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BlendOperation value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BufferBindingType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BufferMapAsyncStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CompareFunction value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CompilationInfoRequestStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CompilationMessageType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CreatePipelineAsyncStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CullMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(DeviceLostReason value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ErrorFilter value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ErrorType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(FeatureName value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(FilterMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(FrontFace value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(IndexFormat value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(LoadOp value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(LoggingType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(PipelineStatisticName value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(PowerPreference value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(PresentMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(PrimitiveTopology value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(QueryType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(QueueWorkDoneStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(RequestAdapterStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(RequestDeviceStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(SType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(SamplerBindingType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(StencilOperation value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(StorageTextureAccess value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(StoreOp value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureAspect value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureComponentType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureDimension value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureFormat value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureSampleType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureViewDimension value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(VertexFormat value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(VertexStepMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    //
    // Bitmasks
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BufferUsage value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ColorWriteMask value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(MapMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ShaderStage value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureUsage value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

}  // namespace wgpu

#endif // WEBGPU_ABSL_FORMAT_H_
