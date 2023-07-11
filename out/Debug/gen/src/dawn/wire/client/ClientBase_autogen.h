
#ifndef DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_
#define DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_

#include "dawn/wire/ChunkedCommandHandler.h"
#include "dawn/wire/WireCmd_autogen.h"
#include "dawn/wire/client/ApiObjects.h"

namespace dawn::wire::client {

    class ClientBase : public ChunkedCommandHandler, public ObjectIdProvider {
      public:
        ClientBase() = default;
        ~ClientBase() override = default;

      private:
        // Implementation of the ObjectIdProvider interface
        WireResult GetId(WGPUAdapter object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Adapter*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUAdapter object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Adapter*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUBindGroup object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<BindGroup*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUBindGroup object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<BindGroup*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUBindGroupLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<BindGroupLayout*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUBindGroupLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<BindGroupLayout*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Buffer*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Buffer*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUCommandBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<CommandBuffer*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUCommandBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<CommandBuffer*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUCommandEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<CommandEncoder*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUCommandEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<CommandEncoder*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUComputePassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ComputePassEncoder*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUComputePassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ComputePassEncoder*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUComputePipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ComputePipeline*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUComputePipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ComputePipeline*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUDevice object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Device*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUDevice object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Device*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUExternalTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ExternalTexture*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUExternalTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ExternalTexture*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUInstance object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Instance*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUInstance object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Instance*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUPipelineLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<PipelineLayout*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUPipelineLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<PipelineLayout*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUQuerySet object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<QuerySet*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUQuerySet object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<QuerySet*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUQueue object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Queue*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUQueue object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Queue*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderBundle object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderBundle*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderBundle object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderBundle*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderBundleEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderBundleEncoder*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderBundleEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderBundleEncoder*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderPassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderPassEncoder*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderPassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderPassEncoder*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderPipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderPipeline*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderPipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderPipeline*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUSampler object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Sampler*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUSampler object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Sampler*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUShaderModule object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ShaderModule*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUShaderModule object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ShaderModule*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUSurface object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Surface*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUSurface object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Surface*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUSwapChain object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<SwapChain*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUSwapChain object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<SwapChain*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Texture*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Texture*>(object)->GetWireId());
            return WireResult::Success;
        }
        WireResult GetId(WGPUTextureView object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<TextureView*>(object)->GetWireId();
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUTextureView object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<TextureView*>(object)->GetWireId());
            return WireResult::Success;
        }
    };

}  // namespace dawn::wire::client

#endif  // DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_
