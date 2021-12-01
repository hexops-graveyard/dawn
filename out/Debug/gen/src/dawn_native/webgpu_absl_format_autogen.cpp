
#include "dawn_native/webgpu_absl_format_autogen.h"

#include "dawn_native/Device.h"
#include "dawn_native/ObjectBase.h"
#include "dawn_native/ObjectType_autogen.h"
#include "dawn_native/Texture.h"

namespace dawn_native {

    //
    // Structs (Manually written)
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const Color* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append(absl::StrFormat("[Color r:%f, g:%f, b:%f, a:%f]",
            value->r, value->g, value->b, value->a));
        return {true};
    }

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const Extent3D* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append(absl::StrFormat("[Extent3D width:%u, height:%u, depthOrArrayLayers:%u]",
            value->width, value->height, value->depthOrArrayLayers));
        return {true};
    }

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const Origin3D* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append(absl::StrFormat("[Origin3D x:%u, y:%u, z:%u]",
            value->x, value->y, value->z));
        return {true};
    }

    //
    // Objects
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const DeviceBase* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[Device");
        const std::string& label = value->GetLabel();
        if (!label.empty()) {
            s->Append(absl::StrFormat(" \"%s\"", label));
        }
        s->Append("]");
        return {true};
    }

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ApiObjectBase* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[");
        if (value->IsError()) {
            s->Append("Invalid ");
        }
        s->Append(ObjectTypeAsString(value->GetType()));
        const std::string& label = value->GetLabel();
        if (!label.empty()) {
            s->Append(absl::StrFormat(" \"%s\"", label));
        }
        s->Append("]");
        return {true};
    }

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureViewBase* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[");
        if (value->IsError()) {
            s->Append("Invalid ");
        }
        s->Append(ObjectTypeAsString(value->GetType()));
        const std::string& label = value->GetLabel();
        if (!label.empty()) {
            s->Append(absl::StrFormat(" \"%s\"", label));
        }
        const std::string& textureLabel = value->GetTexture()->GetLabel();
        if (!textureLabel.empty()) {
            s->Append(absl::StrFormat(" of Texture \"%s\"", textureLabel));
        }
        s->Append("]");
        return {true};
    }

    //
    // Descriptors
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BufferDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[BufferDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const CommandBufferDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[CommandBufferDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const CommandEncoderDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[CommandEncoderDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ComputePassDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ComputePassDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ExternalTextureDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ExternalTextureDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const PipelineLayoutDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[PipelineLayoutDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const QuerySetDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[QuerySetDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderBundleDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderBundleDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderBundleEncoderDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderBundleEncoderDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SamplerDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SamplerDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ShaderModuleDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ShaderModuleDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SurfaceDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SurfaceDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SwapChainDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SwapChainDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureViewDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[TextureViewDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BindGroupDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[BindGroupDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[TextureDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BindGroupLayoutDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[BindGroupLayoutDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ComputePipelineDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ComputePipelineDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderPassDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderPassDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderPipelineDescriptor* value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderPipelineDescriptor");
        if (value->label != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }

}  // namespace dawn_native

namespace wgpu {

    //
    // Enums
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(AdapterType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("AdapterType::");
        switch (value) {
        case AdapterType::DiscreteGPU:
        s->Append("DiscreteGPU");
        break;
        case AdapterType::IntegratedGPU:
        s->Append("IntegratedGPU");
        break;
        case AdapterType::CPU:
        s->Append("CPU");
        break;
        case AdapterType::Unknown:
        s->Append("Unknown");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<AdapterType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(AddressMode value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("AddressMode::");
        switch (value) {
        case AddressMode::Repeat:
        s->Append("Repeat");
        break;
        case AddressMode::MirrorRepeat:
        s->Append("MirrorRepeat");
        break;
        case AddressMode::ClampToEdge:
        s->Append("ClampToEdge");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<AddressMode>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(AlphaOp value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("AlphaOp::");
        switch (value) {
        case AlphaOp::DontChange:
        s->Append("DontChange");
        break;
        case AlphaOp::Premultiply:
        s->Append("Premultiply");
        break;
        case AlphaOp::Unpremultiply:
        s->Append("Unpremultiply");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<AlphaOp>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BackendType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("BackendType::");
        switch (value) {
        case BackendType::Null:
        s->Append("Null");
        break;
        case BackendType::WebGPU:
        s->Append("WebGPU");
        break;
        case BackendType::D3D11:
        s->Append("D3D11");
        break;
        case BackendType::D3D12:
        s->Append("D3D12");
        break;
        case BackendType::Metal:
        s->Append("Metal");
        break;
        case BackendType::Vulkan:
        s->Append("Vulkan");
        break;
        case BackendType::OpenGL:
        s->Append("OpenGL");
        break;
        case BackendType::OpenGLES:
        s->Append("OpenGLES");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<BackendType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BlendFactor value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("BlendFactor::");
        switch (value) {
        case BlendFactor::Zero:
        s->Append("Zero");
        break;
        case BlendFactor::One:
        s->Append("One");
        break;
        case BlendFactor::Src:
        s->Append("Src");
        break;
        case BlendFactor::OneMinusSrc:
        s->Append("OneMinusSrc");
        break;
        case BlendFactor::SrcAlpha:
        s->Append("SrcAlpha");
        break;
        case BlendFactor::OneMinusSrcAlpha:
        s->Append("OneMinusSrcAlpha");
        break;
        case BlendFactor::Dst:
        s->Append("Dst");
        break;
        case BlendFactor::OneMinusDst:
        s->Append("OneMinusDst");
        break;
        case BlendFactor::DstAlpha:
        s->Append("DstAlpha");
        break;
        case BlendFactor::OneMinusDstAlpha:
        s->Append("OneMinusDstAlpha");
        break;
        case BlendFactor::SrcAlphaSaturated:
        s->Append("SrcAlphaSaturated");
        break;
        case BlendFactor::Constant:
        s->Append("Constant");
        break;
        case BlendFactor::OneMinusConstant:
        s->Append("OneMinusConstant");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<BlendFactor>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BlendOperation value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("BlendOperation::");
        switch (value) {
        case BlendOperation::Add:
        s->Append("Add");
        break;
        case BlendOperation::Subtract:
        s->Append("Subtract");
        break;
        case BlendOperation::ReverseSubtract:
        s->Append("ReverseSubtract");
        break;
        case BlendOperation::Min:
        s->Append("Min");
        break;
        case BlendOperation::Max:
        s->Append("Max");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<BlendOperation>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BufferBindingType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("BufferBindingType::");
        switch (value) {
        case BufferBindingType::Undefined:
        s->Append("Undefined");
        break;
        case BufferBindingType::Uniform:
        s->Append("Uniform");
        break;
        case BufferBindingType::Storage:
        s->Append("Storage");
        break;
        case BufferBindingType::ReadOnlyStorage:
        s->Append("ReadOnlyStorage");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<BufferBindingType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BufferMapAsyncStatus value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("BufferMapAsyncStatus::");
        switch (value) {
        case BufferMapAsyncStatus::Success:
        s->Append("Success");
        break;
        case BufferMapAsyncStatus::Error:
        s->Append("Error");
        break;
        case BufferMapAsyncStatus::Unknown:
        s->Append("Unknown");
        break;
        case BufferMapAsyncStatus::DeviceLost:
        s->Append("DeviceLost");
        break;
        case BufferMapAsyncStatus::DestroyedBeforeCallback:
        s->Append("DestroyedBeforeCallback");
        break;
        case BufferMapAsyncStatus::UnmappedBeforeCallback:
        s->Append("UnmappedBeforeCallback");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<BufferMapAsyncStatus>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CompareFunction value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("CompareFunction::");
        switch (value) {
        case CompareFunction::Undefined:
        s->Append("Undefined");
        break;
        case CompareFunction::Never:
        s->Append("Never");
        break;
        case CompareFunction::Less:
        s->Append("Less");
        break;
        case CompareFunction::LessEqual:
        s->Append("LessEqual");
        break;
        case CompareFunction::Greater:
        s->Append("Greater");
        break;
        case CompareFunction::GreaterEqual:
        s->Append("GreaterEqual");
        break;
        case CompareFunction::Equal:
        s->Append("Equal");
        break;
        case CompareFunction::NotEqual:
        s->Append("NotEqual");
        break;
        case CompareFunction::Always:
        s->Append("Always");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<CompareFunction>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CompilationInfoRequestStatus value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("CompilationInfoRequestStatus::");
        switch (value) {
        case CompilationInfoRequestStatus::Success:
        s->Append("Success");
        break;
        case CompilationInfoRequestStatus::Error:
        s->Append("Error");
        break;
        case CompilationInfoRequestStatus::DeviceLost:
        s->Append("DeviceLost");
        break;
        case CompilationInfoRequestStatus::Unknown:
        s->Append("Unknown");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<CompilationInfoRequestStatus>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CompilationMessageType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("CompilationMessageType::");
        switch (value) {
        case CompilationMessageType::Error:
        s->Append("Error");
        break;
        case CompilationMessageType::Warning:
        s->Append("Warning");
        break;
        case CompilationMessageType::Info:
        s->Append("Info");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<CompilationMessageType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CreatePipelineAsyncStatus value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("CreatePipelineAsyncStatus::");
        switch (value) {
        case CreatePipelineAsyncStatus::Success:
        s->Append("Success");
        break;
        case CreatePipelineAsyncStatus::Error:
        s->Append("Error");
        break;
        case CreatePipelineAsyncStatus::DeviceLost:
        s->Append("DeviceLost");
        break;
        case CreatePipelineAsyncStatus::DeviceDestroyed:
        s->Append("DeviceDestroyed");
        break;
        case CreatePipelineAsyncStatus::Unknown:
        s->Append("Unknown");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<CreatePipelineAsyncStatus>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(CullMode value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("CullMode::");
        switch (value) {
        case CullMode::None:
        s->Append("None");
        break;
        case CullMode::Front:
        s->Append("Front");
        break;
        case CullMode::Back:
        s->Append("Back");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<CullMode>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(DeviceLostReason value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("DeviceLostReason::");
        switch (value) {
        case DeviceLostReason::Undefined:
        s->Append("Undefined");
        break;
        case DeviceLostReason::Destroyed:
        s->Append("Destroyed");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<DeviceLostReason>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ErrorFilter value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("ErrorFilter::");
        switch (value) {
        case ErrorFilter::None:
        s->Append("None");
        break;
        case ErrorFilter::Validation:
        s->Append("Validation");
        break;
        case ErrorFilter::OutOfMemory:
        s->Append("OutOfMemory");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<ErrorFilter>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ErrorType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("ErrorType::");
        switch (value) {
        case ErrorType::NoError:
        s->Append("NoError");
        break;
        case ErrorType::Validation:
        s->Append("Validation");
        break;
        case ErrorType::OutOfMemory:
        s->Append("OutOfMemory");
        break;
        case ErrorType::Unknown:
        s->Append("Unknown");
        break;
        case ErrorType::DeviceLost:
        s->Append("DeviceLost");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<ErrorType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(FilterMode value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("FilterMode::");
        switch (value) {
        case FilterMode::Nearest:
        s->Append("Nearest");
        break;
        case FilterMode::Linear:
        s->Append("Linear");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<FilterMode>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(FrontFace value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("FrontFace::");
        switch (value) {
        case FrontFace::CCW:
        s->Append("CCW");
        break;
        case FrontFace::CW:
        s->Append("CW");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<FrontFace>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(IndexFormat value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("IndexFormat::");
        switch (value) {
        case IndexFormat::Undefined:
        s->Append("Undefined");
        break;
        case IndexFormat::Uint16:
        s->Append("Uint16");
        break;
        case IndexFormat::Uint32:
        s->Append("Uint32");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<IndexFormat>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(LoadOp value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("LoadOp::");
        switch (value) {
        case LoadOp::Clear:
        s->Append("Clear");
        break;
        case LoadOp::Load:
        s->Append("Load");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<LoadOp>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(LoggingType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("LoggingType::");
        switch (value) {
        case LoggingType::Verbose:
        s->Append("Verbose");
        break;
        case LoggingType::Info:
        s->Append("Info");
        break;
        case LoggingType::Warning:
        s->Append("Warning");
        break;
        case LoggingType::Error:
        s->Append("Error");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<LoggingType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(PipelineStatisticName value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("PipelineStatisticName::");
        switch (value) {
        case PipelineStatisticName::VertexShaderInvocations:
        s->Append("VertexShaderInvocations");
        break;
        case PipelineStatisticName::ClipperInvocations:
        s->Append("ClipperInvocations");
        break;
        case PipelineStatisticName::ClipperPrimitivesOut:
        s->Append("ClipperPrimitivesOut");
        break;
        case PipelineStatisticName::FragmentShaderInvocations:
        s->Append("FragmentShaderInvocations");
        break;
        case PipelineStatisticName::ComputeShaderInvocations:
        s->Append("ComputeShaderInvocations");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<PipelineStatisticName>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(PresentMode value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("PresentMode::");
        switch (value) {
        case PresentMode::Immediate:
        s->Append("Immediate");
        break;
        case PresentMode::Mailbox:
        s->Append("Mailbox");
        break;
        case PresentMode::Fifo:
        s->Append("Fifo");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<PresentMode>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(PrimitiveTopology value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("PrimitiveTopology::");
        switch (value) {
        case PrimitiveTopology::PointList:
        s->Append("PointList");
        break;
        case PrimitiveTopology::LineList:
        s->Append("LineList");
        break;
        case PrimitiveTopology::LineStrip:
        s->Append("LineStrip");
        break;
        case PrimitiveTopology::TriangleList:
        s->Append("TriangleList");
        break;
        case PrimitiveTopology::TriangleStrip:
        s->Append("TriangleStrip");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<PrimitiveTopology>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(QueryType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("QueryType::");
        switch (value) {
        case QueryType::Occlusion:
        s->Append("Occlusion");
        break;
        case QueryType::PipelineStatistics:
        s->Append("PipelineStatistics");
        break;
        case QueryType::Timestamp:
        s->Append("Timestamp");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<QueryType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(QueueWorkDoneStatus value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("QueueWorkDoneStatus::");
        switch (value) {
        case QueueWorkDoneStatus::Success:
        s->Append("Success");
        break;
        case QueueWorkDoneStatus::Error:
        s->Append("Error");
        break;
        case QueueWorkDoneStatus::Unknown:
        s->Append("Unknown");
        break;
        case QueueWorkDoneStatus::DeviceLost:
        s->Append("DeviceLost");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<QueueWorkDoneStatus>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(RequestDeviceStatus value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("RequestDeviceStatus::");
        switch (value) {
        case RequestDeviceStatus::Success:
        s->Append("Success");
        break;
        case RequestDeviceStatus::Error:
        s->Append("Error");
        break;
        case RequestDeviceStatus::Unknown:
        s->Append("Unknown");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<RequestDeviceStatus>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(SType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("SType::");
        switch (value) {
        case SType::Invalid:
        s->Append("Invalid");
        break;
        case SType::SurfaceDescriptorFromMetalLayer:
        s->Append("SurfaceDescriptorFromMetalLayer");
        break;
        case SType::SurfaceDescriptorFromWindowsHWND:
        s->Append("SurfaceDescriptorFromWindowsHWND");
        break;
        case SType::SurfaceDescriptorFromXlib:
        s->Append("SurfaceDescriptorFromXlib");
        break;
        case SType::SurfaceDescriptorFromCanvasHTMLSelector:
        s->Append("SurfaceDescriptorFromCanvasHTMLSelector");
        break;
        case SType::ShaderModuleSPIRVDescriptor:
        s->Append("ShaderModuleSPIRVDescriptor");
        break;
        case SType::ShaderModuleWGSLDescriptor:
        s->Append("ShaderModuleWGSLDescriptor");
        break;
        case SType::SurfaceDescriptorFromWindowsCoreWindow:
        s->Append("SurfaceDescriptorFromWindowsCoreWindow");
        break;
        case SType::ExternalTextureBindingEntry:
        s->Append("ExternalTextureBindingEntry");
        break;
        case SType::ExternalTextureBindingLayout:
        s->Append("ExternalTextureBindingLayout");
        break;
        case SType::SurfaceDescriptorFromWindowsSwapChainPanel:
        s->Append("SurfaceDescriptorFromWindowsSwapChainPanel");
        break;
        case SType::DawnTextureInternalUsageDescriptor:
        s->Append("DawnTextureInternalUsageDescriptor");
        break;
        case SType::PrimitiveDepthClampingState:
        s->Append("PrimitiveDepthClampingState");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<SType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(SamplerBindingType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("SamplerBindingType::");
        switch (value) {
        case SamplerBindingType::Undefined:
        s->Append("Undefined");
        break;
        case SamplerBindingType::Filtering:
        s->Append("Filtering");
        break;
        case SamplerBindingType::NonFiltering:
        s->Append("NonFiltering");
        break;
        case SamplerBindingType::Comparison:
        s->Append("Comparison");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<SamplerBindingType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(StencilOperation value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("StencilOperation::");
        switch (value) {
        case StencilOperation::Keep:
        s->Append("Keep");
        break;
        case StencilOperation::Zero:
        s->Append("Zero");
        break;
        case StencilOperation::Replace:
        s->Append("Replace");
        break;
        case StencilOperation::Invert:
        s->Append("Invert");
        break;
        case StencilOperation::IncrementClamp:
        s->Append("IncrementClamp");
        break;
        case StencilOperation::DecrementClamp:
        s->Append("DecrementClamp");
        break;
        case StencilOperation::IncrementWrap:
        s->Append("IncrementWrap");
        break;
        case StencilOperation::DecrementWrap:
        s->Append("DecrementWrap");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<StencilOperation>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(StorageTextureAccess value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("StorageTextureAccess::");
        switch (value) {
        case StorageTextureAccess::Undefined:
        s->Append("Undefined");
        break;
        case StorageTextureAccess::WriteOnly:
        s->Append("WriteOnly");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<StorageTextureAccess>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(StoreOp value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("StoreOp::");
        switch (value) {
        case StoreOp::Store:
        s->Append("Store");
        break;
        case StoreOp::Discard:
        s->Append("Discard");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<StoreOp>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureAspect value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("TextureAspect::");
        switch (value) {
        case TextureAspect::All:
        s->Append("All");
        break;
        case TextureAspect::StencilOnly:
        s->Append("StencilOnly");
        break;
        case TextureAspect::DepthOnly:
        s->Append("DepthOnly");
        break;
        case TextureAspect::Plane0Only:
        s->Append("Plane0Only");
        break;
        case TextureAspect::Plane1Only:
        s->Append("Plane1Only");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<TextureAspect>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureComponentType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("TextureComponentType::");
        switch (value) {
        case TextureComponentType::Float:
        s->Append("Float");
        break;
        case TextureComponentType::Sint:
        s->Append("Sint");
        break;
        case TextureComponentType::Uint:
        s->Append("Uint");
        break;
        case TextureComponentType::DepthComparison:
        s->Append("DepthComparison");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<TextureComponentType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureDimension value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("TextureDimension::");
        switch (value) {
        case TextureDimension::e1D:
        s->Append("e1D");
        break;
        case TextureDimension::e2D:
        s->Append("e2D");
        break;
        case TextureDimension::e3D:
        s->Append("e3D");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<TextureDimension>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureFormat value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("TextureFormat::");
        switch (value) {
        case TextureFormat::Undefined:
        s->Append("Undefined");
        break;
        case TextureFormat::R8Unorm:
        s->Append("R8Unorm");
        break;
        case TextureFormat::R8Snorm:
        s->Append("R8Snorm");
        break;
        case TextureFormat::R8Uint:
        s->Append("R8Uint");
        break;
        case TextureFormat::R8Sint:
        s->Append("R8Sint");
        break;
        case TextureFormat::R16Uint:
        s->Append("R16Uint");
        break;
        case TextureFormat::R16Sint:
        s->Append("R16Sint");
        break;
        case TextureFormat::R16Float:
        s->Append("R16Float");
        break;
        case TextureFormat::RG8Unorm:
        s->Append("RG8Unorm");
        break;
        case TextureFormat::RG8Snorm:
        s->Append("RG8Snorm");
        break;
        case TextureFormat::RG8Uint:
        s->Append("RG8Uint");
        break;
        case TextureFormat::RG8Sint:
        s->Append("RG8Sint");
        break;
        case TextureFormat::R32Float:
        s->Append("R32Float");
        break;
        case TextureFormat::R32Uint:
        s->Append("R32Uint");
        break;
        case TextureFormat::R32Sint:
        s->Append("R32Sint");
        break;
        case TextureFormat::RG16Uint:
        s->Append("RG16Uint");
        break;
        case TextureFormat::RG16Sint:
        s->Append("RG16Sint");
        break;
        case TextureFormat::RG16Float:
        s->Append("RG16Float");
        break;
        case TextureFormat::RGBA8Unorm:
        s->Append("RGBA8Unorm");
        break;
        case TextureFormat::RGBA8UnormSrgb:
        s->Append("RGBA8UnormSrgb");
        break;
        case TextureFormat::RGBA8Snorm:
        s->Append("RGBA8Snorm");
        break;
        case TextureFormat::RGBA8Uint:
        s->Append("RGBA8Uint");
        break;
        case TextureFormat::RGBA8Sint:
        s->Append("RGBA8Sint");
        break;
        case TextureFormat::BGRA8Unorm:
        s->Append("BGRA8Unorm");
        break;
        case TextureFormat::BGRA8UnormSrgb:
        s->Append("BGRA8UnormSrgb");
        break;
        case TextureFormat::RGB10A2Unorm:
        s->Append("RGB10A2Unorm");
        break;
        case TextureFormat::RG11B10Ufloat:
        s->Append("RG11B10Ufloat");
        break;
        case TextureFormat::RGB9E5Ufloat:
        s->Append("RGB9E5Ufloat");
        break;
        case TextureFormat::RG32Float:
        s->Append("RG32Float");
        break;
        case TextureFormat::RG32Uint:
        s->Append("RG32Uint");
        break;
        case TextureFormat::RG32Sint:
        s->Append("RG32Sint");
        break;
        case TextureFormat::RGBA16Uint:
        s->Append("RGBA16Uint");
        break;
        case TextureFormat::RGBA16Sint:
        s->Append("RGBA16Sint");
        break;
        case TextureFormat::RGBA16Float:
        s->Append("RGBA16Float");
        break;
        case TextureFormat::RGBA32Float:
        s->Append("RGBA32Float");
        break;
        case TextureFormat::RGBA32Uint:
        s->Append("RGBA32Uint");
        break;
        case TextureFormat::RGBA32Sint:
        s->Append("RGBA32Sint");
        break;
        case TextureFormat::Stencil8:
        s->Append("Stencil8");
        break;
        case TextureFormat::Depth16Unorm:
        s->Append("Depth16Unorm");
        break;
        case TextureFormat::Depth24Plus:
        s->Append("Depth24Plus");
        break;
        case TextureFormat::Depth24PlusStencil8:
        s->Append("Depth24PlusStencil8");
        break;
        case TextureFormat::Depth24UnormStencil8:
        s->Append("Depth24UnormStencil8");
        break;
        case TextureFormat::Depth32Float:
        s->Append("Depth32Float");
        break;
        case TextureFormat::Depth32FloatStencil8:
        s->Append("Depth32FloatStencil8");
        break;
        case TextureFormat::BC1RGBAUnorm:
        s->Append("BC1RGBAUnorm");
        break;
        case TextureFormat::BC1RGBAUnormSrgb:
        s->Append("BC1RGBAUnormSrgb");
        break;
        case TextureFormat::BC2RGBAUnorm:
        s->Append("BC2RGBAUnorm");
        break;
        case TextureFormat::BC2RGBAUnormSrgb:
        s->Append("BC2RGBAUnormSrgb");
        break;
        case TextureFormat::BC3RGBAUnorm:
        s->Append("BC3RGBAUnorm");
        break;
        case TextureFormat::BC3RGBAUnormSrgb:
        s->Append("BC3RGBAUnormSrgb");
        break;
        case TextureFormat::BC4RUnorm:
        s->Append("BC4RUnorm");
        break;
        case TextureFormat::BC4RSnorm:
        s->Append("BC4RSnorm");
        break;
        case TextureFormat::BC5RGUnorm:
        s->Append("BC5RGUnorm");
        break;
        case TextureFormat::BC5RGSnorm:
        s->Append("BC5RGSnorm");
        break;
        case TextureFormat::BC6HRGBUfloat:
        s->Append("BC6HRGBUfloat");
        break;
        case TextureFormat::BC6HRGBFloat:
        s->Append("BC6HRGBFloat");
        break;
        case TextureFormat::BC7RGBAUnorm:
        s->Append("BC7RGBAUnorm");
        break;
        case TextureFormat::BC7RGBAUnormSrgb:
        s->Append("BC7RGBAUnormSrgb");
        break;
        case TextureFormat::ETC2RGB8Unorm:
        s->Append("ETC2RGB8Unorm");
        break;
        case TextureFormat::ETC2RGB8UnormSrgb:
        s->Append("ETC2RGB8UnormSrgb");
        break;
        case TextureFormat::ETC2RGB8A1Unorm:
        s->Append("ETC2RGB8A1Unorm");
        break;
        case TextureFormat::ETC2RGB8A1UnormSrgb:
        s->Append("ETC2RGB8A1UnormSrgb");
        break;
        case TextureFormat::ETC2RGBA8Unorm:
        s->Append("ETC2RGBA8Unorm");
        break;
        case TextureFormat::ETC2RGBA8UnormSrgb:
        s->Append("ETC2RGBA8UnormSrgb");
        break;
        case TextureFormat::EACR11Unorm:
        s->Append("EACR11Unorm");
        break;
        case TextureFormat::EACR11Snorm:
        s->Append("EACR11Snorm");
        break;
        case TextureFormat::EACRG11Unorm:
        s->Append("EACRG11Unorm");
        break;
        case TextureFormat::EACRG11Snorm:
        s->Append("EACRG11Snorm");
        break;
        case TextureFormat::ASTC4x4Unorm:
        s->Append("ASTC4x4Unorm");
        break;
        case TextureFormat::ASTC4x4UnormSrgb:
        s->Append("ASTC4x4UnormSrgb");
        break;
        case TextureFormat::ASTC5x4Unorm:
        s->Append("ASTC5x4Unorm");
        break;
        case TextureFormat::ASTC5x4UnormSrgb:
        s->Append("ASTC5x4UnormSrgb");
        break;
        case TextureFormat::ASTC5x5Unorm:
        s->Append("ASTC5x5Unorm");
        break;
        case TextureFormat::ASTC5x5UnormSrgb:
        s->Append("ASTC5x5UnormSrgb");
        break;
        case TextureFormat::ASTC6x5Unorm:
        s->Append("ASTC6x5Unorm");
        break;
        case TextureFormat::ASTC6x5UnormSrgb:
        s->Append("ASTC6x5UnormSrgb");
        break;
        case TextureFormat::ASTC6x6Unorm:
        s->Append("ASTC6x6Unorm");
        break;
        case TextureFormat::ASTC6x6UnormSrgb:
        s->Append("ASTC6x6UnormSrgb");
        break;
        case TextureFormat::ASTC8x5Unorm:
        s->Append("ASTC8x5Unorm");
        break;
        case TextureFormat::ASTC8x5UnormSrgb:
        s->Append("ASTC8x5UnormSrgb");
        break;
        case TextureFormat::ASTC8x6Unorm:
        s->Append("ASTC8x6Unorm");
        break;
        case TextureFormat::ASTC8x6UnormSrgb:
        s->Append("ASTC8x6UnormSrgb");
        break;
        case TextureFormat::ASTC8x8Unorm:
        s->Append("ASTC8x8Unorm");
        break;
        case TextureFormat::ASTC8x8UnormSrgb:
        s->Append("ASTC8x8UnormSrgb");
        break;
        case TextureFormat::ASTC10x5Unorm:
        s->Append("ASTC10x5Unorm");
        break;
        case TextureFormat::ASTC10x5UnormSrgb:
        s->Append("ASTC10x5UnormSrgb");
        break;
        case TextureFormat::ASTC10x6Unorm:
        s->Append("ASTC10x6Unorm");
        break;
        case TextureFormat::ASTC10x6UnormSrgb:
        s->Append("ASTC10x6UnormSrgb");
        break;
        case TextureFormat::ASTC10x8Unorm:
        s->Append("ASTC10x8Unorm");
        break;
        case TextureFormat::ASTC10x8UnormSrgb:
        s->Append("ASTC10x8UnormSrgb");
        break;
        case TextureFormat::ASTC10x10Unorm:
        s->Append("ASTC10x10Unorm");
        break;
        case TextureFormat::ASTC10x10UnormSrgb:
        s->Append("ASTC10x10UnormSrgb");
        break;
        case TextureFormat::ASTC12x10Unorm:
        s->Append("ASTC12x10Unorm");
        break;
        case TextureFormat::ASTC12x10UnormSrgb:
        s->Append("ASTC12x10UnormSrgb");
        break;
        case TextureFormat::ASTC12x12Unorm:
        s->Append("ASTC12x12Unorm");
        break;
        case TextureFormat::ASTC12x12UnormSrgb:
        s->Append("ASTC12x12UnormSrgb");
        break;
        case TextureFormat::R8BG8Biplanar420Unorm:
        s->Append("R8BG8Biplanar420Unorm");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<TextureFormat>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureSampleType value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("TextureSampleType::");
        switch (value) {
        case TextureSampleType::Undefined:
        s->Append("Undefined");
        break;
        case TextureSampleType::Float:
        s->Append("Float");
        break;
        case TextureSampleType::UnfilterableFloat:
        s->Append("UnfilterableFloat");
        break;
        case TextureSampleType::Depth:
        s->Append("Depth");
        break;
        case TextureSampleType::Sint:
        s->Append("Sint");
        break;
        case TextureSampleType::Uint:
        s->Append("Uint");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<TextureSampleType>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureViewDimension value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("TextureViewDimension::");
        switch (value) {
        case TextureViewDimension::Undefined:
        s->Append("Undefined");
        break;
        case TextureViewDimension::e1D:
        s->Append("e1D");
        break;
        case TextureViewDimension::e2D:
        s->Append("e2D");
        break;
        case TextureViewDimension::e2DArray:
        s->Append("e2DArray");
        break;
        case TextureViewDimension::Cube:
        s->Append("Cube");
        break;
        case TextureViewDimension::CubeArray:
        s->Append("CubeArray");
        break;
        case TextureViewDimension::e3D:
        s->Append("e3D");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<TextureViewDimension>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(VertexFormat value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("VertexFormat::");
        switch (value) {
        case VertexFormat::Undefined:
        s->Append("Undefined");
        break;
        case VertexFormat::Uint8x2:
        s->Append("Uint8x2");
        break;
        case VertexFormat::Uint8x4:
        s->Append("Uint8x4");
        break;
        case VertexFormat::Sint8x2:
        s->Append("Sint8x2");
        break;
        case VertexFormat::Sint8x4:
        s->Append("Sint8x4");
        break;
        case VertexFormat::Unorm8x2:
        s->Append("Unorm8x2");
        break;
        case VertexFormat::Unorm8x4:
        s->Append("Unorm8x4");
        break;
        case VertexFormat::Snorm8x2:
        s->Append("Snorm8x2");
        break;
        case VertexFormat::Snorm8x4:
        s->Append("Snorm8x4");
        break;
        case VertexFormat::Uint16x2:
        s->Append("Uint16x2");
        break;
        case VertexFormat::Uint16x4:
        s->Append("Uint16x4");
        break;
        case VertexFormat::Sint16x2:
        s->Append("Sint16x2");
        break;
        case VertexFormat::Sint16x4:
        s->Append("Sint16x4");
        break;
        case VertexFormat::Unorm16x2:
        s->Append("Unorm16x2");
        break;
        case VertexFormat::Unorm16x4:
        s->Append("Unorm16x4");
        break;
        case VertexFormat::Snorm16x2:
        s->Append("Snorm16x2");
        break;
        case VertexFormat::Snorm16x4:
        s->Append("Snorm16x4");
        break;
        case VertexFormat::Float16x2:
        s->Append("Float16x2");
        break;
        case VertexFormat::Float16x4:
        s->Append("Float16x4");
        break;
        case VertexFormat::Float32:
        s->Append("Float32");
        break;
        case VertexFormat::Float32x2:
        s->Append("Float32x2");
        break;
        case VertexFormat::Float32x3:
        s->Append("Float32x3");
        break;
        case VertexFormat::Float32x4:
        s->Append("Float32x4");
        break;
        case VertexFormat::Uint32:
        s->Append("Uint32");
        break;
        case VertexFormat::Uint32x2:
        s->Append("Uint32x2");
        break;
        case VertexFormat::Uint32x3:
        s->Append("Uint32x3");
        break;
        case VertexFormat::Uint32x4:
        s->Append("Uint32x4");
        break;
        case VertexFormat::Sint32:
        s->Append("Sint32");
        break;
        case VertexFormat::Sint32x2:
        s->Append("Sint32x2");
        break;
        case VertexFormat::Sint32x3:
        s->Append("Sint32x3");
        break;
        case VertexFormat::Sint32x4:
        s->Append("Sint32x4");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<VertexFormat>::type>(value)));
        }
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(VertexStepMode value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("VertexStepMode::");
        switch (value) {
        case VertexStepMode::Vertex:
        s->Append("Vertex");
        break;
        case VertexStepMode::Instance:
        s->Append("Instance");
        break;
            default:
            s->Append(absl::StrFormat("%x", static_cast<typename std::underlying_type<VertexStepMode>::type>(value)));
        }
        return {true};
    }

    //
    // Bitmasks
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(BufferUsage value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("BufferUsage::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & BufferUsage::MapRead) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("MapRead");
            value &= ~BufferUsage::MapRead;
        }
        if (value & BufferUsage::MapWrite) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("MapWrite");
            value &= ~BufferUsage::MapWrite;
        }
        if (value & BufferUsage::CopySrc) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopySrc");
            value &= ~BufferUsage::CopySrc;
        }
        if (value & BufferUsage::CopyDst) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopyDst");
            value &= ~BufferUsage::CopyDst;
        }
        if (value & BufferUsage::Index) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Index");
            value &= ~BufferUsage::Index;
        }
        if (value & BufferUsage::Vertex) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Vertex");
            value &= ~BufferUsage::Vertex;
        }
        if (value & BufferUsage::Uniform) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Uniform");
            value &= ~BufferUsage::Uniform;
        }
        if (value & BufferUsage::Storage) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Storage");
            value &= ~BufferUsage::Storage;
        }
        if (value & BufferUsage::Indirect) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Indirect");
            value &= ~BufferUsage::Indirect;
        }
        if (value & BufferUsage::QueryResolve) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("QueryResolve");
            value &= ~BufferUsage::QueryResolve;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("BufferUsage::%x", static_cast<typename std::underlying_type<BufferUsage>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }

        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ColorWriteMask value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("ColorWriteMask::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & ColorWriteMask::Red) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Red");
            value &= ~ColorWriteMask::Red;
        }
        if (value & ColorWriteMask::Green) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Green");
            value &= ~ColorWriteMask::Green;
        }
        if (value & ColorWriteMask::Blue) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Blue");
            value &= ~ColorWriteMask::Blue;
        }
        if (value & ColorWriteMask::Alpha) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Alpha");
            value &= ~ColorWriteMask::Alpha;
        }
        if (value & ColorWriteMask::All) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("All");
            value &= ~ColorWriteMask::All;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("ColorWriteMask::%x", static_cast<typename std::underlying_type<ColorWriteMask>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }

        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(MapMode value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("MapMode::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & MapMode::Read) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Read");
            value &= ~MapMode::Read;
        }
        if (value & MapMode::Write) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Write");
            value &= ~MapMode::Write;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("MapMode::%x", static_cast<typename std::underlying_type<MapMode>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }

        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(ShaderStage value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("ShaderStage::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & ShaderStage::Vertex) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Vertex");
            value &= ~ShaderStage::Vertex;
        }
        if (value & ShaderStage::Fragment) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Fragment");
            value &= ~ShaderStage::Fragment;
        }
        if (value & ShaderStage::Compute) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Compute");
            value &= ~ShaderStage::Compute;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("ShaderStage::%x", static_cast<typename std::underlying_type<ShaderStage>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }

        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(TextureUsage value,
                        const absl::FormatConversionSpec& spec,
                        absl::FormatSink* s) {
        s->Append("TextureUsage::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & TextureUsage::CopySrc) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopySrc");
            value &= ~TextureUsage::CopySrc;
        }
        if (value & TextureUsage::CopyDst) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopyDst");
            value &= ~TextureUsage::CopyDst;
        }
        if (value & TextureUsage::TextureBinding) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("TextureBinding");
            value &= ~TextureUsage::TextureBinding;
        }
        if (value & TextureUsage::StorageBinding) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("StorageBinding");
            value &= ~TextureUsage::StorageBinding;
        }
        if (value & TextureUsage::RenderAttachment) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("RenderAttachment");
            value &= ~TextureUsage::RenderAttachment;
        }
        if (value & TextureUsage::Present) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Present");
            value &= ~TextureUsage::Present;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("TextureUsage::%x", static_cast<typename std::underlying_type<TextureUsage>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }

        return {true};
    }

}  // namespace wgpu
