
#ifndef DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_
#define DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_

#include "dawn_wire/ChunkedCommandHandler.h"
#include "dawn_wire/WireCmd_autogen.h"
#include "dawn_wire/client/ApiObjects.h"
#include "dawn_wire/client/ObjectAllocator.h"

namespace dawn_wire { namespace client {

    class ClientBase : public ChunkedCommandHandler, public ObjectIdProvider {
      public:
        ClientBase() = default;
        virtual ~ClientBase() = default;

        const ObjectAllocator<Adapter>& AdapterAllocator() const {
            return mAdapterAllocator;
        }
        ObjectAllocator<Adapter>& AdapterAllocator() {
            return mAdapterAllocator;
        }
        const ObjectAllocator<BindGroup>& BindGroupAllocator() const {
            return mBindGroupAllocator;
        }
        ObjectAllocator<BindGroup>& BindGroupAllocator() {
            return mBindGroupAllocator;
        }
        const ObjectAllocator<BindGroupLayout>& BindGroupLayoutAllocator() const {
            return mBindGroupLayoutAllocator;
        }
        ObjectAllocator<BindGroupLayout>& BindGroupLayoutAllocator() {
            return mBindGroupLayoutAllocator;
        }
        const ObjectAllocator<Buffer>& BufferAllocator() const {
            return mBufferAllocator;
        }
        ObjectAllocator<Buffer>& BufferAllocator() {
            return mBufferAllocator;
        }
        const ObjectAllocator<CommandBuffer>& CommandBufferAllocator() const {
            return mCommandBufferAllocator;
        }
        ObjectAllocator<CommandBuffer>& CommandBufferAllocator() {
            return mCommandBufferAllocator;
        }
        const ObjectAllocator<CommandEncoder>& CommandEncoderAllocator() const {
            return mCommandEncoderAllocator;
        }
        ObjectAllocator<CommandEncoder>& CommandEncoderAllocator() {
            return mCommandEncoderAllocator;
        }
        const ObjectAllocator<ComputePassEncoder>& ComputePassEncoderAllocator() const {
            return mComputePassEncoderAllocator;
        }
        ObjectAllocator<ComputePassEncoder>& ComputePassEncoderAllocator() {
            return mComputePassEncoderAllocator;
        }
        const ObjectAllocator<ComputePipeline>& ComputePipelineAllocator() const {
            return mComputePipelineAllocator;
        }
        ObjectAllocator<ComputePipeline>& ComputePipelineAllocator() {
            return mComputePipelineAllocator;
        }
        const ObjectAllocator<Device>& DeviceAllocator() const {
            return mDeviceAllocator;
        }
        ObjectAllocator<Device>& DeviceAllocator() {
            return mDeviceAllocator;
        }
        const ObjectAllocator<ExternalTexture>& ExternalTextureAllocator() const {
            return mExternalTextureAllocator;
        }
        ObjectAllocator<ExternalTexture>& ExternalTextureAllocator() {
            return mExternalTextureAllocator;
        }
        const ObjectAllocator<Instance>& InstanceAllocator() const {
            return mInstanceAllocator;
        }
        ObjectAllocator<Instance>& InstanceAllocator() {
            return mInstanceAllocator;
        }
        const ObjectAllocator<PipelineLayout>& PipelineLayoutAllocator() const {
            return mPipelineLayoutAllocator;
        }
        ObjectAllocator<PipelineLayout>& PipelineLayoutAllocator() {
            return mPipelineLayoutAllocator;
        }
        const ObjectAllocator<QuerySet>& QuerySetAllocator() const {
            return mQuerySetAllocator;
        }
        ObjectAllocator<QuerySet>& QuerySetAllocator() {
            return mQuerySetAllocator;
        }
        const ObjectAllocator<Queue>& QueueAllocator() const {
            return mQueueAllocator;
        }
        ObjectAllocator<Queue>& QueueAllocator() {
            return mQueueAllocator;
        }
        const ObjectAllocator<RenderBundle>& RenderBundleAllocator() const {
            return mRenderBundleAllocator;
        }
        ObjectAllocator<RenderBundle>& RenderBundleAllocator() {
            return mRenderBundleAllocator;
        }
        const ObjectAllocator<RenderBundleEncoder>& RenderBundleEncoderAllocator() const {
            return mRenderBundleEncoderAllocator;
        }
        ObjectAllocator<RenderBundleEncoder>& RenderBundleEncoderAllocator() {
            return mRenderBundleEncoderAllocator;
        }
        const ObjectAllocator<RenderPassEncoder>& RenderPassEncoderAllocator() const {
            return mRenderPassEncoderAllocator;
        }
        ObjectAllocator<RenderPassEncoder>& RenderPassEncoderAllocator() {
            return mRenderPassEncoderAllocator;
        }
        const ObjectAllocator<RenderPipeline>& RenderPipelineAllocator() const {
            return mRenderPipelineAllocator;
        }
        ObjectAllocator<RenderPipeline>& RenderPipelineAllocator() {
            return mRenderPipelineAllocator;
        }
        const ObjectAllocator<Sampler>& SamplerAllocator() const {
            return mSamplerAllocator;
        }
        ObjectAllocator<Sampler>& SamplerAllocator() {
            return mSamplerAllocator;
        }
        const ObjectAllocator<ShaderModule>& ShaderModuleAllocator() const {
            return mShaderModuleAllocator;
        }
        ObjectAllocator<ShaderModule>& ShaderModuleAllocator() {
            return mShaderModuleAllocator;
        }
        const ObjectAllocator<Surface>& SurfaceAllocator() const {
            return mSurfaceAllocator;
        }
        ObjectAllocator<Surface>& SurfaceAllocator() {
            return mSurfaceAllocator;
        }
        const ObjectAllocator<SwapChain>& SwapChainAllocator() const {
            return mSwapChainAllocator;
        }
        ObjectAllocator<SwapChain>& SwapChainAllocator() {
            return mSwapChainAllocator;
        }
        const ObjectAllocator<Texture>& TextureAllocator() const {
            return mTextureAllocator;
        }
        ObjectAllocator<Texture>& TextureAllocator() {
            return mTextureAllocator;
        }
        const ObjectAllocator<TextureView>& TextureViewAllocator() const {
            return mTextureViewAllocator;
        }
        ObjectAllocator<TextureView>& TextureViewAllocator() {
            return mTextureViewAllocator;
        }

        void FreeObject(ObjectType objectType, ObjectBase* obj) {
            switch (objectType) {
                case ObjectType::Adapter:
                    mAdapterAllocator.Free(static_cast<Adapter*>(obj));
                    break;
                case ObjectType::BindGroup:
                    mBindGroupAllocator.Free(static_cast<BindGroup*>(obj));
                    break;
                case ObjectType::BindGroupLayout:
                    mBindGroupLayoutAllocator.Free(static_cast<BindGroupLayout*>(obj));
                    break;
                case ObjectType::Buffer:
                    mBufferAllocator.Free(static_cast<Buffer*>(obj));
                    break;
                case ObjectType::CommandBuffer:
                    mCommandBufferAllocator.Free(static_cast<CommandBuffer*>(obj));
                    break;
                case ObjectType::CommandEncoder:
                    mCommandEncoderAllocator.Free(static_cast<CommandEncoder*>(obj));
                    break;
                case ObjectType::ComputePassEncoder:
                    mComputePassEncoderAllocator.Free(static_cast<ComputePassEncoder*>(obj));
                    break;
                case ObjectType::ComputePipeline:
                    mComputePipelineAllocator.Free(static_cast<ComputePipeline*>(obj));
                    break;
                case ObjectType::Device:
                    mDeviceAllocator.Free(static_cast<Device*>(obj));
                    break;
                case ObjectType::ExternalTexture:
                    mExternalTextureAllocator.Free(static_cast<ExternalTexture*>(obj));
                    break;
                case ObjectType::Instance:
                    mInstanceAllocator.Free(static_cast<Instance*>(obj));
                    break;
                case ObjectType::PipelineLayout:
                    mPipelineLayoutAllocator.Free(static_cast<PipelineLayout*>(obj));
                    break;
                case ObjectType::QuerySet:
                    mQuerySetAllocator.Free(static_cast<QuerySet*>(obj));
                    break;
                case ObjectType::Queue:
                    mQueueAllocator.Free(static_cast<Queue*>(obj));
                    break;
                case ObjectType::RenderBundle:
                    mRenderBundleAllocator.Free(static_cast<RenderBundle*>(obj));
                    break;
                case ObjectType::RenderBundleEncoder:
                    mRenderBundleEncoderAllocator.Free(static_cast<RenderBundleEncoder*>(obj));
                    break;
                case ObjectType::RenderPassEncoder:
                    mRenderPassEncoderAllocator.Free(static_cast<RenderPassEncoder*>(obj));
                    break;
                case ObjectType::RenderPipeline:
                    mRenderPipelineAllocator.Free(static_cast<RenderPipeline*>(obj));
                    break;
                case ObjectType::Sampler:
                    mSamplerAllocator.Free(static_cast<Sampler*>(obj));
                    break;
                case ObjectType::ShaderModule:
                    mShaderModuleAllocator.Free(static_cast<ShaderModule*>(obj));
                    break;
                case ObjectType::Surface:
                    mSurfaceAllocator.Free(static_cast<Surface*>(obj));
                    break;
                case ObjectType::SwapChain:
                    mSwapChainAllocator.Free(static_cast<SwapChain*>(obj));
                    break;
                case ObjectType::Texture:
                    mTextureAllocator.Free(static_cast<Texture*>(obj));
                    break;
                case ObjectType::TextureView:
                    mTextureViewAllocator.Free(static_cast<TextureView*>(obj));
                    break;
            }
        }

      private:
        // Implementation of the ObjectIdProvider interface
        WireResult GetId(WGPUAdapter object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Adapter*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUAdapter object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Adapter*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUBindGroup object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<BindGroup*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUBindGroup object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<BindGroup*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUBindGroupLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<BindGroupLayout*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUBindGroupLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<BindGroupLayout*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Buffer*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Buffer*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUCommandBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<CommandBuffer*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUCommandBuffer object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<CommandBuffer*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUCommandEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<CommandEncoder*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUCommandEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<CommandEncoder*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUComputePassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ComputePassEncoder*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUComputePassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ComputePassEncoder*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUComputePipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ComputePipeline*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUComputePipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ComputePipeline*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUDevice object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Device*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUDevice object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Device*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUExternalTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ExternalTexture*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUExternalTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ExternalTexture*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUInstance object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Instance*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUInstance object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Instance*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUPipelineLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<PipelineLayout*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUPipelineLayout object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<PipelineLayout*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUQuerySet object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<QuerySet*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUQuerySet object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<QuerySet*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUQueue object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Queue*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUQueue object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Queue*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderBundle object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderBundle*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderBundle object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderBundle*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderBundleEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderBundleEncoder*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderBundleEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderBundleEncoder*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderPassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderPassEncoder*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderPassEncoder object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderPassEncoder*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPURenderPipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<RenderPipeline*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPURenderPipeline object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<RenderPipeline*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUSampler object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Sampler*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUSampler object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Sampler*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUShaderModule object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<ShaderModule*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUShaderModule object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<ShaderModule*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUSurface object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Surface*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUSurface object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Surface*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUSwapChain object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<SwapChain*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUSwapChain object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<SwapChain*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<Texture*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUTexture object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<Texture*>(object)->id);
            return WireResult::Success;
        }
        WireResult GetId(WGPUTextureView object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            if (object == nullptr) {
                return WireResult::FatalError;
            }
            *out = reinterpret_cast<TextureView*>(object)->id;
            return WireResult::Success;
        }
        WireResult GetOptionalId(WGPUTextureView object, ObjectId* out) const final {
            ASSERT(out != nullptr);
            *out = (object == nullptr ? 0 : reinterpret_cast<TextureView*>(object)->id);
            return WireResult::Success;
        }

        ObjectAllocator<Adapter> mAdapterAllocator;
        ObjectAllocator<BindGroup> mBindGroupAllocator;
        ObjectAllocator<BindGroupLayout> mBindGroupLayoutAllocator;
        ObjectAllocator<Buffer> mBufferAllocator;
        ObjectAllocator<CommandBuffer> mCommandBufferAllocator;
        ObjectAllocator<CommandEncoder> mCommandEncoderAllocator;
        ObjectAllocator<ComputePassEncoder> mComputePassEncoderAllocator;
        ObjectAllocator<ComputePipeline> mComputePipelineAllocator;
        ObjectAllocator<Device> mDeviceAllocator;
        ObjectAllocator<ExternalTexture> mExternalTextureAllocator;
        ObjectAllocator<Instance> mInstanceAllocator;
        ObjectAllocator<PipelineLayout> mPipelineLayoutAllocator;
        ObjectAllocator<QuerySet> mQuerySetAllocator;
        ObjectAllocator<Queue> mQueueAllocator;
        ObjectAllocator<RenderBundle> mRenderBundleAllocator;
        ObjectAllocator<RenderBundleEncoder> mRenderBundleEncoderAllocator;
        ObjectAllocator<RenderPassEncoder> mRenderPassEncoderAllocator;
        ObjectAllocator<RenderPipeline> mRenderPipelineAllocator;
        ObjectAllocator<Sampler> mSamplerAllocator;
        ObjectAllocator<ShaderModule> mShaderModuleAllocator;
        ObjectAllocator<Surface> mSurfaceAllocator;
        ObjectAllocator<SwapChain> mSwapChainAllocator;
        ObjectAllocator<Texture> mTextureAllocator;
        ObjectAllocator<TextureView> mTextureViewAllocator;
    };

}}  // namespace dawn_wire::client

#endif  // DAWNWIRE_CLIENT_CLIENTBASE_AUTOGEN_H_
