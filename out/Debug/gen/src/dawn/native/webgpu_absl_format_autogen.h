
#ifndef WEBGPU_ABSL_FORMAT_H_
#define WEBGPU_ABSL_FORMAT_H_

#include "dawn/native/dawn_platform.h"

#include "absl/strings/str_format.h"

namespace dawn::native {

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
        AbslFormatConvert(const PipelineLayoutDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const QuerySetDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const QueueDescriptor* value,
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
        AbslFormatConvert(const ComputePassDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const ExternalTextureDescriptor* value,
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

    //
    // Compatible with absl::StrFormat (Needs to be disjoint from having a 'label' for now.)
    // Currently uses a hard-coded list to determine which structures are actually supported. If
    // additional structures are added, be sure to update the cpp file's list as well.
    //
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const BufferBindingLayout& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const SamplerBindingLayout& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const StorageTextureBindingLayout& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const TextureBindingLayout& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);

} // namespace dawn::native

namespace wgpu {

    //
    // Enums
    //

        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(AdapterType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(AddressMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(AlphaMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(BackendType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(BlendFactor value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(BlendOperation value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(BufferBindingType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(BufferMapAsyncStatus value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(BufferMapState value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(CompareFunction value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(CompilationInfoRequestStatus value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(CompilationMessageType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(ComputePassTimestampLocation value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(CreatePipelineAsyncStatus value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(CullMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(DeviceLostReason value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(ErrorFilter value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(ErrorType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(ExternalTextureRotation value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(FeatureName value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(FilterMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(FrontFace value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(IndexFormat value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(LoadOp value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(LoggingType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(MipmapFilterMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(PipelineStatisticName value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(PowerPreference value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(PresentMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(PrimitiveTopology value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(QueryType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(QueueWorkDoneStatus value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(RenderPassTimestampLocation value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(RequestAdapterStatus value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(RequestDeviceStatus value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(SType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(SamplerBindingType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(StencilOperation value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(StorageTextureAccess value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(StoreOp value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(TextureAspect value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(TextureDimension value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(TextureFormat value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(TextureSampleType value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(TextureViewDimension value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(VertexFormat value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(VertexStepMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);

    //
    // Bitmasks
    //

        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(BufferUsage value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(ColorWriteMask value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(MapMode value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(ShaderStage value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
        AbslFormatConvert(TextureUsage value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);

}  // namespace wgpu

#endif // WEBGPU_ABSL_FORMAT_H_
