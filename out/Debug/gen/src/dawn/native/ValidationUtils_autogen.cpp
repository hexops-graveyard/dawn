
#include "dawn/native/ValidationUtils_autogen.h"

namespace dawn::native {

    MaybeError ValidateAdapterType(wgpu::AdapterType value) {
        switch (value) {
            case wgpu::AdapterType::DiscreteGPU:
                return {};
            case wgpu::AdapterType::IntegratedGPU:
                return {};
            case wgpu::AdapterType::CPU:
                return {};
            case wgpu::AdapterType::Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUAdapterType");
        }
    }

    MaybeError ValidateAddressMode(wgpu::AddressMode value) {
        switch (value) {
            case wgpu::AddressMode::Repeat:
                return {};
            case wgpu::AddressMode::MirrorRepeat:
                return {};
            case wgpu::AddressMode::ClampToEdge:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUAddressMode");
        }
    }

    MaybeError ValidateAlphaMode(wgpu::AlphaMode value) {
        switch (value) {
            case wgpu::AlphaMode::Premultiplied:
                return {};
            case wgpu::AlphaMode::Unpremultiplied:
                return {};
            case wgpu::AlphaMode::Opaque:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUAlphaMode");
        }
    }

    MaybeError ValidateBackendType(wgpu::BackendType value) {
        switch (value) {
            case wgpu::BackendType::Null:
                return {};
            case wgpu::BackendType::WebGPU:
                return {};
            case wgpu::BackendType::D3D11:
                return {};
            case wgpu::BackendType::D3D12:
                return {};
            case wgpu::BackendType::Metal:
                return {};
            case wgpu::BackendType::Vulkan:
                return {};
            case wgpu::BackendType::OpenGL:
                return {};
            case wgpu::BackendType::OpenGLES:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBackendType");
        }
    }

    MaybeError ValidateBlendFactor(wgpu::BlendFactor value) {
        switch (value) {
            case wgpu::BlendFactor::Zero:
                return {};
            case wgpu::BlendFactor::One:
                return {};
            case wgpu::BlendFactor::Src:
                return {};
            case wgpu::BlendFactor::OneMinusSrc:
                return {};
            case wgpu::BlendFactor::SrcAlpha:
                return {};
            case wgpu::BlendFactor::OneMinusSrcAlpha:
                return {};
            case wgpu::BlendFactor::Dst:
                return {};
            case wgpu::BlendFactor::OneMinusDst:
                return {};
            case wgpu::BlendFactor::DstAlpha:
                return {};
            case wgpu::BlendFactor::OneMinusDstAlpha:
                return {};
            case wgpu::BlendFactor::SrcAlphaSaturated:
                return {};
            case wgpu::BlendFactor::Constant:
                return {};
            case wgpu::BlendFactor::OneMinusConstant:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBlendFactor");
        }
    }

    MaybeError ValidateBlendOperation(wgpu::BlendOperation value) {
        switch (value) {
            case wgpu::BlendOperation::Add:
                return {};
            case wgpu::BlendOperation::Subtract:
                return {};
            case wgpu::BlendOperation::ReverseSubtract:
                return {};
            case wgpu::BlendOperation::Min:
                return {};
            case wgpu::BlendOperation::Max:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBlendOperation");
        }
    }

    MaybeError ValidateBufferBindingType(wgpu::BufferBindingType value) {
        switch (value) {
            case wgpu::BufferBindingType::Uniform:
                return {};
            case wgpu::BufferBindingType::Storage:
                return {};
            case wgpu::BufferBindingType::ReadOnlyStorage:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBufferBindingType");
        }
    }

    MaybeError ValidateBufferMapAsyncStatus(wgpu::BufferMapAsyncStatus value) {
        switch (value) {
            case wgpu::BufferMapAsyncStatus::Success:
                return {};
            case wgpu::BufferMapAsyncStatus::Error:
                return {};
            case wgpu::BufferMapAsyncStatus::Unknown:
                return {};
            case wgpu::BufferMapAsyncStatus::DeviceLost:
                return {};
            case wgpu::BufferMapAsyncStatus::DestroyedBeforeCallback:
                return {};
            case wgpu::BufferMapAsyncStatus::UnmappedBeforeCallback:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUBufferMapAsyncStatus");
        }
    }

    MaybeError ValidateCompareFunction(wgpu::CompareFunction value) {
        switch (value) {
            case wgpu::CompareFunction::Never:
                return {};
            case wgpu::CompareFunction::Less:
                return {};
            case wgpu::CompareFunction::LessEqual:
                return {};
            case wgpu::CompareFunction::Greater:
                return {};
            case wgpu::CompareFunction::GreaterEqual:
                return {};
            case wgpu::CompareFunction::Equal:
                return {};
            case wgpu::CompareFunction::NotEqual:
                return {};
            case wgpu::CompareFunction::Always:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCompareFunction");
        }
    }

    MaybeError ValidateCompilationInfoRequestStatus(wgpu::CompilationInfoRequestStatus value) {
        switch (value) {
            case wgpu::CompilationInfoRequestStatus::Success:
                return {};
            case wgpu::CompilationInfoRequestStatus::Error:
                return {};
            case wgpu::CompilationInfoRequestStatus::DeviceLost:
                return {};
            case wgpu::CompilationInfoRequestStatus::Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCompilationInfoRequestStatus");
        }
    }

    MaybeError ValidateCompilationMessageType(wgpu::CompilationMessageType value) {
        switch (value) {
            case wgpu::CompilationMessageType::Error:
                return {};
            case wgpu::CompilationMessageType::Warning:
                return {};
            case wgpu::CompilationMessageType::Info:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCompilationMessageType");
        }
    }

    MaybeError ValidateComputePassTimestampLocation(wgpu::ComputePassTimestampLocation value) {
        switch (value) {
            case wgpu::ComputePassTimestampLocation::Beginning:
                return {};
            case wgpu::ComputePassTimestampLocation::End:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUComputePassTimestampLocation");
        }
    }

    MaybeError ValidateCreatePipelineAsyncStatus(wgpu::CreatePipelineAsyncStatus value) {
        switch (value) {
            case wgpu::CreatePipelineAsyncStatus::Success:
                return {};
            case wgpu::CreatePipelineAsyncStatus::Error:
                return {};
            case wgpu::CreatePipelineAsyncStatus::DeviceLost:
                return {};
            case wgpu::CreatePipelineAsyncStatus::DeviceDestroyed:
                return {};
            case wgpu::CreatePipelineAsyncStatus::Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCreatePipelineAsyncStatus");
        }
    }

    MaybeError ValidateCullMode(wgpu::CullMode value) {
        switch (value) {
            case wgpu::CullMode::None:
                return {};
            case wgpu::CullMode::Front:
                return {};
            case wgpu::CullMode::Back:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUCullMode");
        }
    }

    MaybeError ValidateDeviceLostReason(wgpu::DeviceLostReason value) {
        switch (value) {
            case wgpu::DeviceLostReason::Undefined:
                return {};
            case wgpu::DeviceLostReason::Destroyed:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUDeviceLostReason");
        }
    }

    MaybeError ValidateErrorFilter(wgpu::ErrorFilter value) {
        switch (value) {
            case wgpu::ErrorFilter::Validation:
                return {};
            case wgpu::ErrorFilter::OutOfMemory:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUErrorFilter");
        }
    }

    MaybeError ValidateErrorType(wgpu::ErrorType value) {
        switch (value) {
            case wgpu::ErrorType::NoError:
                return {};
            case wgpu::ErrorType::Validation:
                return {};
            case wgpu::ErrorType::OutOfMemory:
                return {};
            case wgpu::ErrorType::Unknown:
                return {};
            case wgpu::ErrorType::DeviceLost:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUErrorType");
        }
    }

    MaybeError ValidateFeatureName(wgpu::FeatureName value) {
        switch (value) {
            case wgpu::FeatureName::Undefined:
                return {};
            case wgpu::FeatureName::DepthClipControl:
                return {};
            case wgpu::FeatureName::Depth32FloatStencil8:
                return {};
            case wgpu::FeatureName::TimestampQuery:
                return {};
            case wgpu::FeatureName::PipelineStatisticsQuery:
                return {};
            case wgpu::FeatureName::TextureCompressionBC:
                return {};
            case wgpu::FeatureName::TextureCompressionETC2:
                return {};
            case wgpu::FeatureName::TextureCompressionASTC:
                return {};
            case wgpu::FeatureName::IndirectFirstInstance:
                return {};
            case wgpu::FeatureName::DawnShaderFloat16:
                return {};
            case wgpu::FeatureName::DawnInternalUsages:
                return {};
            case wgpu::FeatureName::DawnMultiPlanarFormats:
                return {};
            case wgpu::FeatureName::DawnNative:
                return {};
            case wgpu::FeatureName::ChromiumExperimentalDp4a:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUFeatureName");
        }
    }

    MaybeError ValidateFilterMode(wgpu::FilterMode value) {
        switch (value) {
            case wgpu::FilterMode::Nearest:
                return {};
            case wgpu::FilterMode::Linear:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUFilterMode");
        }
    }

    MaybeError ValidateFrontFace(wgpu::FrontFace value) {
        switch (value) {
            case wgpu::FrontFace::CCW:
                return {};
            case wgpu::FrontFace::CW:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUFrontFace");
        }
    }

    MaybeError ValidateIndexFormat(wgpu::IndexFormat value) {
        switch (value) {
            case wgpu::IndexFormat::Undefined:
                return {};
            case wgpu::IndexFormat::Uint16:
                return {};
            case wgpu::IndexFormat::Uint32:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUIndexFormat");
        }
    }

    MaybeError ValidateLoadOp(wgpu::LoadOp value) {
        switch (value) {
            case wgpu::LoadOp::Undefined:
                return {};
            case wgpu::LoadOp::Clear:
                return {};
            case wgpu::LoadOp::Load:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPULoadOp");
        }
    }

    MaybeError ValidateLoggingType(wgpu::LoggingType value) {
        switch (value) {
            case wgpu::LoggingType::Verbose:
                return {};
            case wgpu::LoggingType::Info:
                return {};
            case wgpu::LoggingType::Warning:
                return {};
            case wgpu::LoggingType::Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPULoggingType");
        }
    }

    MaybeError ValidatePipelineStatisticName(wgpu::PipelineStatisticName value) {
        switch (value) {
            case wgpu::PipelineStatisticName::VertexShaderInvocations:
                return {};
            case wgpu::PipelineStatisticName::ClipperInvocations:
                return {};
            case wgpu::PipelineStatisticName::ClipperPrimitivesOut:
                return {};
            case wgpu::PipelineStatisticName::FragmentShaderInvocations:
                return {};
            case wgpu::PipelineStatisticName::ComputeShaderInvocations:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUPipelineStatisticName");
        }
    }

    MaybeError ValidatePowerPreference(wgpu::PowerPreference value) {
        switch (value) {
            case wgpu::PowerPreference::Undefined:
                return {};
            case wgpu::PowerPreference::LowPower:
                return {};
            case wgpu::PowerPreference::HighPerformance:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUPowerPreference");
        }
    }

    MaybeError ValidatePresentMode(wgpu::PresentMode value) {
        switch (value) {
            case wgpu::PresentMode::Immediate:
                return {};
            case wgpu::PresentMode::Mailbox:
                return {};
            case wgpu::PresentMode::Fifo:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUPresentMode");
        }
    }

    MaybeError ValidatePrimitiveTopology(wgpu::PrimitiveTopology value) {
        switch (value) {
            case wgpu::PrimitiveTopology::PointList:
                return {};
            case wgpu::PrimitiveTopology::LineList:
                return {};
            case wgpu::PrimitiveTopology::LineStrip:
                return {};
            case wgpu::PrimitiveTopology::TriangleList:
                return {};
            case wgpu::PrimitiveTopology::TriangleStrip:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUPrimitiveTopology");
        }
    }

    MaybeError ValidateQueryType(wgpu::QueryType value) {
        switch (value) {
            case wgpu::QueryType::Occlusion:
                return {};
            case wgpu::QueryType::PipelineStatistics:
                return {};
            case wgpu::QueryType::Timestamp:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUQueryType");
        }
    }

    MaybeError ValidateQueueWorkDoneStatus(wgpu::QueueWorkDoneStatus value) {
        switch (value) {
            case wgpu::QueueWorkDoneStatus::Success:
                return {};
            case wgpu::QueueWorkDoneStatus::Error:
                return {};
            case wgpu::QueueWorkDoneStatus::Unknown:
                return {};
            case wgpu::QueueWorkDoneStatus::DeviceLost:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUQueueWorkDoneStatus");
        }
    }

    MaybeError ValidateRenderPassTimestampLocation(wgpu::RenderPassTimestampLocation value) {
        switch (value) {
            case wgpu::RenderPassTimestampLocation::Beginning:
                return {};
            case wgpu::RenderPassTimestampLocation::End:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPURenderPassTimestampLocation");
        }
    }

    MaybeError ValidateRequestAdapterStatus(wgpu::RequestAdapterStatus value) {
        switch (value) {
            case wgpu::RequestAdapterStatus::Success:
                return {};
            case wgpu::RequestAdapterStatus::Unavailable:
                return {};
            case wgpu::RequestAdapterStatus::Error:
                return {};
            case wgpu::RequestAdapterStatus::Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPURequestAdapterStatus");
        }
    }

    MaybeError ValidateRequestDeviceStatus(wgpu::RequestDeviceStatus value) {
        switch (value) {
            case wgpu::RequestDeviceStatus::Success:
                return {};
            case wgpu::RequestDeviceStatus::Error:
                return {};
            case wgpu::RequestDeviceStatus::Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPURequestDeviceStatus");
        }
    }

    MaybeError ValidateSType(wgpu::SType value) {
        switch (value) {
            case wgpu::SType::SurfaceDescriptorFromMetalLayer:
                return {};
            case wgpu::SType::SurfaceDescriptorFromWindowsHWND:
                return {};
            case wgpu::SType::SurfaceDescriptorFromXlibWindow:
                return {};
            case wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector:
                return {};
            case wgpu::SType::ShaderModuleSPIRVDescriptor:
                return {};
            case wgpu::SType::ShaderModuleWGSLDescriptor:
                return {};
            case wgpu::SType::PrimitiveDepthClipControl:
                return {};
            case wgpu::SType::SurfaceDescriptorFromWaylandSurface:
                return {};
            case wgpu::SType::SurfaceDescriptorFromAndroidNativeWindow:
                return {};
            case wgpu::SType::SurfaceDescriptorFromWindowsCoreWindow:
                return {};
            case wgpu::SType::ExternalTextureBindingEntry:
                return {};
            case wgpu::SType::ExternalTextureBindingLayout:
                return {};
            case wgpu::SType::SurfaceDescriptorFromWindowsSwapChainPanel:
                return {};
            case wgpu::SType::RenderPassDescriptorMaxDrawCount:
                return {};
            case wgpu::SType::DawnTextureInternalUsageDescriptor:
                return {};
            case wgpu::SType::DawnTogglesDeviceDescriptor:
                return {};
            case wgpu::SType::DawnEncoderInternalUsageDescriptor:
                return {};
            case wgpu::SType::DawnInstanceDescriptor:
                return {};
            case wgpu::SType::DawnCacheDeviceDescriptor:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUSType");
        }
    }

    MaybeError ValidateSamplerBindingType(wgpu::SamplerBindingType value) {
        switch (value) {
            case wgpu::SamplerBindingType::Filtering:
                return {};
            case wgpu::SamplerBindingType::NonFiltering:
                return {};
            case wgpu::SamplerBindingType::Comparison:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUSamplerBindingType");
        }
    }

    MaybeError ValidateStencilOperation(wgpu::StencilOperation value) {
        switch (value) {
            case wgpu::StencilOperation::Keep:
                return {};
            case wgpu::StencilOperation::Zero:
                return {};
            case wgpu::StencilOperation::Replace:
                return {};
            case wgpu::StencilOperation::Invert:
                return {};
            case wgpu::StencilOperation::IncrementClamp:
                return {};
            case wgpu::StencilOperation::DecrementClamp:
                return {};
            case wgpu::StencilOperation::IncrementWrap:
                return {};
            case wgpu::StencilOperation::DecrementWrap:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUStencilOperation");
        }
    }

    MaybeError ValidateStorageTextureAccess(wgpu::StorageTextureAccess value) {
        switch (value) {
            case wgpu::StorageTextureAccess::WriteOnly:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUStorageTextureAccess");
        }
    }

    MaybeError ValidateStoreOp(wgpu::StoreOp value) {
        switch (value) {
            case wgpu::StoreOp::Undefined:
                return {};
            case wgpu::StoreOp::Store:
                return {};
            case wgpu::StoreOp::Discard:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUStoreOp");
        }
    }

    MaybeError ValidateTextureAspect(wgpu::TextureAspect value) {
        switch (value) {
            case wgpu::TextureAspect::All:
                return {};
            case wgpu::TextureAspect::StencilOnly:
                return {};
            case wgpu::TextureAspect::DepthOnly:
                return {};
            case wgpu::TextureAspect::Plane0Only:
                return {};
            case wgpu::TextureAspect::Plane1Only:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureAspect");
        }
    }

    MaybeError ValidateTextureComponentType(wgpu::TextureComponentType value) {
        switch (value) {
            case wgpu::TextureComponentType::Float:
                return {};
            case wgpu::TextureComponentType::Sint:
                return {};
            case wgpu::TextureComponentType::Uint:
                return {};
            case wgpu::TextureComponentType::DepthComparison:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureComponentType");
        }
    }

    MaybeError ValidateTextureDimension(wgpu::TextureDimension value) {
        switch (value) {
            case wgpu::TextureDimension::e1D:
                return {};
            case wgpu::TextureDimension::e2D:
                return {};
            case wgpu::TextureDimension::e3D:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureDimension");
        }
    }

    MaybeError ValidateTextureFormat(wgpu::TextureFormat value) {
        switch (value) {
            case wgpu::TextureFormat::R8Unorm:
                return {};
            case wgpu::TextureFormat::R8Snorm:
                return {};
            case wgpu::TextureFormat::R8Uint:
                return {};
            case wgpu::TextureFormat::R8Sint:
                return {};
            case wgpu::TextureFormat::R16Uint:
                return {};
            case wgpu::TextureFormat::R16Sint:
                return {};
            case wgpu::TextureFormat::R16Float:
                return {};
            case wgpu::TextureFormat::RG8Unorm:
                return {};
            case wgpu::TextureFormat::RG8Snorm:
                return {};
            case wgpu::TextureFormat::RG8Uint:
                return {};
            case wgpu::TextureFormat::RG8Sint:
                return {};
            case wgpu::TextureFormat::R32Float:
                return {};
            case wgpu::TextureFormat::R32Uint:
                return {};
            case wgpu::TextureFormat::R32Sint:
                return {};
            case wgpu::TextureFormat::RG16Uint:
                return {};
            case wgpu::TextureFormat::RG16Sint:
                return {};
            case wgpu::TextureFormat::RG16Float:
                return {};
            case wgpu::TextureFormat::RGBA8Unorm:
                return {};
            case wgpu::TextureFormat::RGBA8UnormSrgb:
                return {};
            case wgpu::TextureFormat::RGBA8Snorm:
                return {};
            case wgpu::TextureFormat::RGBA8Uint:
                return {};
            case wgpu::TextureFormat::RGBA8Sint:
                return {};
            case wgpu::TextureFormat::BGRA8Unorm:
                return {};
            case wgpu::TextureFormat::BGRA8UnormSrgb:
                return {};
            case wgpu::TextureFormat::RGB10A2Unorm:
                return {};
            case wgpu::TextureFormat::RG11B10Ufloat:
                return {};
            case wgpu::TextureFormat::RGB9E5Ufloat:
                return {};
            case wgpu::TextureFormat::RG32Float:
                return {};
            case wgpu::TextureFormat::RG32Uint:
                return {};
            case wgpu::TextureFormat::RG32Sint:
                return {};
            case wgpu::TextureFormat::RGBA16Uint:
                return {};
            case wgpu::TextureFormat::RGBA16Sint:
                return {};
            case wgpu::TextureFormat::RGBA16Float:
                return {};
            case wgpu::TextureFormat::RGBA32Float:
                return {};
            case wgpu::TextureFormat::RGBA32Uint:
                return {};
            case wgpu::TextureFormat::RGBA32Sint:
                return {};
            case wgpu::TextureFormat::Stencil8:
                return {};
            case wgpu::TextureFormat::Depth16Unorm:
                return {};
            case wgpu::TextureFormat::Depth24Plus:
                return {};
            case wgpu::TextureFormat::Depth24PlusStencil8:
                return {};
            case wgpu::TextureFormat::Depth32Float:
                return {};
            case wgpu::TextureFormat::Depth32FloatStencil8:
                return {};
            case wgpu::TextureFormat::BC1RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC1RGBAUnormSrgb:
                return {};
            case wgpu::TextureFormat::BC2RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC2RGBAUnormSrgb:
                return {};
            case wgpu::TextureFormat::BC3RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC3RGBAUnormSrgb:
                return {};
            case wgpu::TextureFormat::BC4RUnorm:
                return {};
            case wgpu::TextureFormat::BC4RSnorm:
                return {};
            case wgpu::TextureFormat::BC5RGUnorm:
                return {};
            case wgpu::TextureFormat::BC5RGSnorm:
                return {};
            case wgpu::TextureFormat::BC6HRGBUfloat:
                return {};
            case wgpu::TextureFormat::BC6HRGBFloat:
                return {};
            case wgpu::TextureFormat::BC7RGBAUnorm:
                return {};
            case wgpu::TextureFormat::BC7RGBAUnormSrgb:
                return {};
            case wgpu::TextureFormat::ETC2RGB8Unorm:
                return {};
            case wgpu::TextureFormat::ETC2RGB8UnormSrgb:
                return {};
            case wgpu::TextureFormat::ETC2RGB8A1Unorm:
                return {};
            case wgpu::TextureFormat::ETC2RGB8A1UnormSrgb:
                return {};
            case wgpu::TextureFormat::ETC2RGBA8Unorm:
                return {};
            case wgpu::TextureFormat::ETC2RGBA8UnormSrgb:
                return {};
            case wgpu::TextureFormat::EACR11Unorm:
                return {};
            case wgpu::TextureFormat::EACR11Snorm:
                return {};
            case wgpu::TextureFormat::EACRG11Unorm:
                return {};
            case wgpu::TextureFormat::EACRG11Snorm:
                return {};
            case wgpu::TextureFormat::ASTC4x4Unorm:
                return {};
            case wgpu::TextureFormat::ASTC4x4UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC5x4Unorm:
                return {};
            case wgpu::TextureFormat::ASTC5x4UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC5x5Unorm:
                return {};
            case wgpu::TextureFormat::ASTC5x5UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC6x5Unorm:
                return {};
            case wgpu::TextureFormat::ASTC6x5UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC6x6Unorm:
                return {};
            case wgpu::TextureFormat::ASTC6x6UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC8x5Unorm:
                return {};
            case wgpu::TextureFormat::ASTC8x5UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC8x6Unorm:
                return {};
            case wgpu::TextureFormat::ASTC8x6UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC8x8Unorm:
                return {};
            case wgpu::TextureFormat::ASTC8x8UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC10x5Unorm:
                return {};
            case wgpu::TextureFormat::ASTC10x5UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC10x6Unorm:
                return {};
            case wgpu::TextureFormat::ASTC10x6UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC10x8Unorm:
                return {};
            case wgpu::TextureFormat::ASTC10x8UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC10x10Unorm:
                return {};
            case wgpu::TextureFormat::ASTC10x10UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC12x10Unorm:
                return {};
            case wgpu::TextureFormat::ASTC12x10UnormSrgb:
                return {};
            case wgpu::TextureFormat::ASTC12x12Unorm:
                return {};
            case wgpu::TextureFormat::ASTC12x12UnormSrgb:
                return {};
            case wgpu::TextureFormat::R8BG8Biplanar420Unorm:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureFormat");
        }
    }

    MaybeError ValidateTextureSampleType(wgpu::TextureSampleType value) {
        switch (value) {
            case wgpu::TextureSampleType::Float:
                return {};
            case wgpu::TextureSampleType::UnfilterableFloat:
                return {};
            case wgpu::TextureSampleType::Depth:
                return {};
            case wgpu::TextureSampleType::Sint:
                return {};
            case wgpu::TextureSampleType::Uint:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureSampleType");
        }
    }

    MaybeError ValidateTextureViewDimension(wgpu::TextureViewDimension value) {
        switch (value) {
            case wgpu::TextureViewDimension::e1D:
                return {};
            case wgpu::TextureViewDimension::e2D:
                return {};
            case wgpu::TextureViewDimension::e2DArray:
                return {};
            case wgpu::TextureViewDimension::Cube:
                return {};
            case wgpu::TextureViewDimension::CubeArray:
                return {};
            case wgpu::TextureViewDimension::e3D:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureViewDimension");
        }
    }

    MaybeError ValidateVertexFormat(wgpu::VertexFormat value) {
        switch (value) {
            case wgpu::VertexFormat::Uint8x2:
                return {};
            case wgpu::VertexFormat::Uint8x4:
                return {};
            case wgpu::VertexFormat::Sint8x2:
                return {};
            case wgpu::VertexFormat::Sint8x4:
                return {};
            case wgpu::VertexFormat::Unorm8x2:
                return {};
            case wgpu::VertexFormat::Unorm8x4:
                return {};
            case wgpu::VertexFormat::Snorm8x2:
                return {};
            case wgpu::VertexFormat::Snorm8x4:
                return {};
            case wgpu::VertexFormat::Uint16x2:
                return {};
            case wgpu::VertexFormat::Uint16x4:
                return {};
            case wgpu::VertexFormat::Sint16x2:
                return {};
            case wgpu::VertexFormat::Sint16x4:
                return {};
            case wgpu::VertexFormat::Unorm16x2:
                return {};
            case wgpu::VertexFormat::Unorm16x4:
                return {};
            case wgpu::VertexFormat::Snorm16x2:
                return {};
            case wgpu::VertexFormat::Snorm16x4:
                return {};
            case wgpu::VertexFormat::Float16x2:
                return {};
            case wgpu::VertexFormat::Float16x4:
                return {};
            case wgpu::VertexFormat::Float32:
                return {};
            case wgpu::VertexFormat::Float32x2:
                return {};
            case wgpu::VertexFormat::Float32x3:
                return {};
            case wgpu::VertexFormat::Float32x4:
                return {};
            case wgpu::VertexFormat::Uint32:
                return {};
            case wgpu::VertexFormat::Uint32x2:
                return {};
            case wgpu::VertexFormat::Uint32x3:
                return {};
            case wgpu::VertexFormat::Uint32x4:
                return {};
            case wgpu::VertexFormat::Sint32:
                return {};
            case wgpu::VertexFormat::Sint32x2:
                return {};
            case wgpu::VertexFormat::Sint32x3:
                return {};
            case wgpu::VertexFormat::Sint32x4:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUVertexFormat");
        }
    }

    MaybeError ValidateVertexStepMode(wgpu::VertexStepMode value) {
        switch (value) {
            case wgpu::VertexStepMode::Vertex:
                return {};
            case wgpu::VertexStepMode::Instance:
                return {};
            case wgpu::VertexStepMode::VertexBufferNotUsed:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Invalid value for WGPUVertexStepMode");
        }
    }


    MaybeError ValidateBufferUsage(wgpu::BufferUsage value) {
        if ((value & static_cast<wgpu::BufferUsage>(~1023)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUBufferUsage");
    }

    MaybeError ValidateColorWriteMask(wgpu::ColorWriteMask value) {
        if ((value & static_cast<wgpu::ColorWriteMask>(~15)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUColorWriteMask");
    }

    MaybeError ValidateMapMode(wgpu::MapMode value) {
        if ((value & static_cast<wgpu::MapMode>(~3)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUMapMode");
    }

    MaybeError ValidateShaderStage(wgpu::ShaderStage value) {
        if ((value & static_cast<wgpu::ShaderStage>(~7)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUShaderStage");
    }

    MaybeError ValidateTextureUsage(wgpu::TextureUsage value) {
        if ((value & static_cast<wgpu::TextureUsage>(~63)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Invalid value for WGPUTextureUsage");
    }


} // namespace dawn::native
