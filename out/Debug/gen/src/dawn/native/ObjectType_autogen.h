
#ifndef DAWNNATIVE_OBJECTTPYE_AUTOGEN_H_
#define DAWNNATIVE_OBJECTTPYE_AUTOGEN_H_

#include "dawn/common/ityp_array.h"

#include <cstdint>

namespace dawn::native {

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

    const char* ObjectTypeAsString(ObjectType type);

} // namespace dawn::native


#endif  // DAWNNATIVE_OBJECTTPYE_AUTOGEN_H_
