
#ifndef DAWNWIRE_CLIENT_APIOBJECTS_AUTOGEN_H_
#define DAWNWIRE_CLIENT_APIOBJECTS_AUTOGEN_H_

#include "dawn_wire/ObjectType_autogen.h"
#include "dawn_wire/client/ObjectBase.h"

namespace dawn_wire { namespace client {

    template <typename T>
    struct ObjectTypeToTypeEnum {
        static constexpr ObjectType value = static_cast<ObjectType>(-1);
    };

    struct BindGroup final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline BindGroup* FromAPI(WGPUBindGroup obj) {
        return reinterpret_cast<BindGroup*>(obj);
    }
    inline WGPUBindGroup ToAPI(BindGroup* obj) {
        return reinterpret_cast<WGPUBindGroup>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<BindGroup> {
        static constexpr ObjectType value = ObjectType::BindGroup;
    };

    struct BindGroupLayout final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline BindGroupLayout* FromAPI(WGPUBindGroupLayout obj) {
        return reinterpret_cast<BindGroupLayout*>(obj);
    }
    inline WGPUBindGroupLayout ToAPI(BindGroupLayout* obj) {
        return reinterpret_cast<WGPUBindGroupLayout>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<BindGroupLayout> {
        static constexpr ObjectType value = ObjectType::BindGroupLayout;
    };

    class Buffer;

    inline Buffer* FromAPI(WGPUBuffer obj) {
        return reinterpret_cast<Buffer*>(obj);
    }
    inline WGPUBuffer ToAPI(Buffer* obj) {
        return reinterpret_cast<WGPUBuffer>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<Buffer> {
        static constexpr ObjectType value = ObjectType::Buffer;
    };

    struct CommandBuffer final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline CommandBuffer* FromAPI(WGPUCommandBuffer obj) {
        return reinterpret_cast<CommandBuffer*>(obj);
    }
    inline WGPUCommandBuffer ToAPI(CommandBuffer* obj) {
        return reinterpret_cast<WGPUCommandBuffer>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<CommandBuffer> {
        static constexpr ObjectType value = ObjectType::CommandBuffer;
    };

    struct CommandEncoder final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline CommandEncoder* FromAPI(WGPUCommandEncoder obj) {
        return reinterpret_cast<CommandEncoder*>(obj);
    }
    inline WGPUCommandEncoder ToAPI(CommandEncoder* obj) {
        return reinterpret_cast<WGPUCommandEncoder>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<CommandEncoder> {
        static constexpr ObjectType value = ObjectType::CommandEncoder;
    };

    struct ComputePassEncoder final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline ComputePassEncoder* FromAPI(WGPUComputePassEncoder obj) {
        return reinterpret_cast<ComputePassEncoder*>(obj);
    }
    inline WGPUComputePassEncoder ToAPI(ComputePassEncoder* obj) {
        return reinterpret_cast<WGPUComputePassEncoder>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<ComputePassEncoder> {
        static constexpr ObjectType value = ObjectType::ComputePassEncoder;
    };

    struct ComputePipeline final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline ComputePipeline* FromAPI(WGPUComputePipeline obj) {
        return reinterpret_cast<ComputePipeline*>(obj);
    }
    inline WGPUComputePipeline ToAPI(ComputePipeline* obj) {
        return reinterpret_cast<WGPUComputePipeline>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<ComputePipeline> {
        static constexpr ObjectType value = ObjectType::ComputePipeline;
    };

    class Device;

    inline Device* FromAPI(WGPUDevice obj) {
        return reinterpret_cast<Device*>(obj);
    }
    inline WGPUDevice ToAPI(Device* obj) {
        return reinterpret_cast<WGPUDevice>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<Device> {
        static constexpr ObjectType value = ObjectType::Device;
    };

    struct ExternalTexture final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline ExternalTexture* FromAPI(WGPUExternalTexture obj) {
        return reinterpret_cast<ExternalTexture*>(obj);
    }
    inline WGPUExternalTexture ToAPI(ExternalTexture* obj) {
        return reinterpret_cast<WGPUExternalTexture>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<ExternalTexture> {
        static constexpr ObjectType value = ObjectType::ExternalTexture;
    };

    struct Instance final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Instance* FromAPI(WGPUInstance obj) {
        return reinterpret_cast<Instance*>(obj);
    }
    inline WGPUInstance ToAPI(Instance* obj) {
        return reinterpret_cast<WGPUInstance>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<Instance> {
        static constexpr ObjectType value = ObjectType::Instance;
    };

    struct PipelineLayout final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline PipelineLayout* FromAPI(WGPUPipelineLayout obj) {
        return reinterpret_cast<PipelineLayout*>(obj);
    }
    inline WGPUPipelineLayout ToAPI(PipelineLayout* obj) {
        return reinterpret_cast<WGPUPipelineLayout>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<PipelineLayout> {
        static constexpr ObjectType value = ObjectType::PipelineLayout;
    };

    struct QuerySet final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline QuerySet* FromAPI(WGPUQuerySet obj) {
        return reinterpret_cast<QuerySet*>(obj);
    }
    inline WGPUQuerySet ToAPI(QuerySet* obj) {
        return reinterpret_cast<WGPUQuerySet>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<QuerySet> {
        static constexpr ObjectType value = ObjectType::QuerySet;
    };

    class Queue;

    inline Queue* FromAPI(WGPUQueue obj) {
        return reinterpret_cast<Queue*>(obj);
    }
    inline WGPUQueue ToAPI(Queue* obj) {
        return reinterpret_cast<WGPUQueue>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<Queue> {
        static constexpr ObjectType value = ObjectType::Queue;
    };

    struct RenderBundle final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderBundle* FromAPI(WGPURenderBundle obj) {
        return reinterpret_cast<RenderBundle*>(obj);
    }
    inline WGPURenderBundle ToAPI(RenderBundle* obj) {
        return reinterpret_cast<WGPURenderBundle>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<RenderBundle> {
        static constexpr ObjectType value = ObjectType::RenderBundle;
    };

    struct RenderBundleEncoder final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderBundleEncoder* FromAPI(WGPURenderBundleEncoder obj) {
        return reinterpret_cast<RenderBundleEncoder*>(obj);
    }
    inline WGPURenderBundleEncoder ToAPI(RenderBundleEncoder* obj) {
        return reinterpret_cast<WGPURenderBundleEncoder>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<RenderBundleEncoder> {
        static constexpr ObjectType value = ObjectType::RenderBundleEncoder;
    };

    struct RenderPassEncoder final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderPassEncoder* FromAPI(WGPURenderPassEncoder obj) {
        return reinterpret_cast<RenderPassEncoder*>(obj);
    }
    inline WGPURenderPassEncoder ToAPI(RenderPassEncoder* obj) {
        return reinterpret_cast<WGPURenderPassEncoder>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<RenderPassEncoder> {
        static constexpr ObjectType value = ObjectType::RenderPassEncoder;
    };

    struct RenderPipeline final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline RenderPipeline* FromAPI(WGPURenderPipeline obj) {
        return reinterpret_cast<RenderPipeline*>(obj);
    }
    inline WGPURenderPipeline ToAPI(RenderPipeline* obj) {
        return reinterpret_cast<WGPURenderPipeline>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<RenderPipeline> {
        static constexpr ObjectType value = ObjectType::RenderPipeline;
    };

    struct Sampler final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Sampler* FromAPI(WGPUSampler obj) {
        return reinterpret_cast<Sampler*>(obj);
    }
    inline WGPUSampler ToAPI(Sampler* obj) {
        return reinterpret_cast<WGPUSampler>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<Sampler> {
        static constexpr ObjectType value = ObjectType::Sampler;
    };

    class ShaderModule;

    inline ShaderModule* FromAPI(WGPUShaderModule obj) {
        return reinterpret_cast<ShaderModule*>(obj);
    }
    inline WGPUShaderModule ToAPI(ShaderModule* obj) {
        return reinterpret_cast<WGPUShaderModule>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<ShaderModule> {
        static constexpr ObjectType value = ObjectType::ShaderModule;
    };

    struct Surface final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Surface* FromAPI(WGPUSurface obj) {
        return reinterpret_cast<Surface*>(obj);
    }
    inline WGPUSurface ToAPI(Surface* obj) {
        return reinterpret_cast<WGPUSurface>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<Surface> {
        static constexpr ObjectType value = ObjectType::Surface;
    };

    struct SwapChain final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline SwapChain* FromAPI(WGPUSwapChain obj) {
        return reinterpret_cast<SwapChain*>(obj);
    }
    inline WGPUSwapChain ToAPI(SwapChain* obj) {
        return reinterpret_cast<WGPUSwapChain>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<SwapChain> {
        static constexpr ObjectType value = ObjectType::SwapChain;
    };

    struct Texture final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline Texture* FromAPI(WGPUTexture obj) {
        return reinterpret_cast<Texture*>(obj);
    }
    inline WGPUTexture ToAPI(Texture* obj) {
        return reinterpret_cast<WGPUTexture>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<Texture> {
        static constexpr ObjectType value = ObjectType::Texture;
    };

    struct TextureView final : ObjectBase {
        using ObjectBase::ObjectBase;
    };

    inline TextureView* FromAPI(WGPUTextureView obj) {
        return reinterpret_cast<TextureView*>(obj);
    }
    inline WGPUTextureView ToAPI(TextureView* obj) {
        return reinterpret_cast<WGPUTextureView>(obj);
    }

    template <>
    struct ObjectTypeToTypeEnum<TextureView> {
        static constexpr ObjectType value = ObjectType::TextureView;
    };

}}  // namespace dawn_wire::client

#endif  // DAWNWIRE_CLIENT_APIOBJECTS_AUTOGEN_H_
