
#ifndef DAWNWIRE_OBJECTTPYE_AUTOGEN_H_
#define DAWNWIRE_OBJECTTPYE_AUTOGEN_H_

#include "dawn/common/ityp_array.h"

namespace dawn::wire {

    constexpr uint32_t kObjectTypes = 24;

    enum class ObjectType : uint32_t {
        Adapter,
        BindGroup,
        BindGroupLayout,
        Buffer,
        CommandBuffer,
        CommandEncoder,
        ComputePassEncoder,
        ComputePipeline,
        Device,
        ExternalTexture,
        Instance,
        PipelineLayout,
        QuerySet,
        Queue,
        RenderBundle,
        RenderBundleEncoder,
        RenderPassEncoder,
        RenderPipeline,
        Sampler,
        ShaderModule,
        Surface,
        SwapChain,
        Texture,
        TextureView,
    };

    template <typename T>
    using PerObjectType = ityp::array<ObjectType, T, 24>;

} // namespace dawn::wire


#endif  // DAWNWIRE_OBJECTTPYE_AUTOGEN_H_
