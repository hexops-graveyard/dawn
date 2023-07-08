
#ifndef DAWNWIRE_WIRECMD_AUTOGEN_H_
#define DAWNWIRE_WIRECMD_AUTOGEN_H_

#include "dawn/webgpu.h"

#include "dawn/wire/BufferConsumer.h"
#include "dawn/wire/ObjectType_autogen.h"
#include "dawn/wire/ObjectHandle.h"
#include "dawn/wire/WireResult.h"

namespace dawn::wire {

    // Interface to allocate more space to deserialize pointed-to data.
    // nullptr is treated as an error.
    class DeserializeAllocator {
        public:
            virtual void* GetSpace(size_t size) = 0;
    };

    // Interface to convert an ID to a server object, if possible.
    // Methods return FatalError if the ID is for a non-existent object and Success otherwise.
    class ObjectIdResolver {
        public:
            virtual WireResult GetFromId(ObjectId id, WGPUAdapter* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUAdapter* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUBindGroup* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUBindGroup* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUBindGroupLayout* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUBindGroupLayout* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUBuffer* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUBuffer* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUCommandBuffer* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUCommandBuffer* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUCommandEncoder* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUCommandEncoder* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUComputePassEncoder* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUComputePassEncoder* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUComputePipeline* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUComputePipeline* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUDevice* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUDevice* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUExternalTexture* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUExternalTexture* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUInstance* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUInstance* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUPipelineLayout* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUPipelineLayout* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUQuerySet* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUQuerySet* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUQueue* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUQueue* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPURenderBundle* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPURenderBundle* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPURenderBundleEncoder* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPURenderBundleEncoder* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPURenderPassEncoder* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPURenderPassEncoder* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPURenderPipeline* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPURenderPipeline* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUSampler* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUSampler* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUShaderModule* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUShaderModule* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUSurface* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUSurface* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUSwapChain* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUSwapChain* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUTexture* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUTexture* out) const = 0;
            virtual WireResult GetFromId(ObjectId id, WGPUTextureView* out) const = 0;
            virtual WireResult GetOptionalFromId(ObjectId id, WGPUTextureView* out) const = 0;
    };

    // Interface to convert a client object to its ID for the wiring.
    class ObjectIdProvider {
        public:
            virtual WireResult GetId(WGPUAdapter object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUAdapter object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUBindGroup object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUBindGroup object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUBindGroupLayout object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUBindGroupLayout object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUBuffer object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUBuffer object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUCommandBuffer object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUCommandBuffer object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUCommandEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUCommandEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUComputePassEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUComputePassEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUComputePipeline object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUComputePipeline object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUDevice object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUDevice object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUExternalTexture object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUExternalTexture object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUInstance object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUInstance object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUPipelineLayout object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUPipelineLayout object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUQuerySet object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUQuerySet object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUQueue object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUQueue object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPURenderBundle object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPURenderBundle object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPURenderBundleEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPURenderBundleEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPURenderPassEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPURenderPassEncoder object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPURenderPipeline object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPURenderPipeline object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUSampler object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUSampler object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUShaderModule object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUShaderModule object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUSurface object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUSurface object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUSwapChain object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUSwapChain object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUTexture object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUTexture object, ObjectId* out) const = 0;
            virtual WireResult GetId(WGPUTextureView object, ObjectId* out) const = 0;
            virtual WireResult GetOptionalId(WGPUTextureView object, ObjectId* out) const = 0;
    };

    enum class WireCmd : uint32_t {
        AdapterGetInstance,
        AdapterRequestDevice,
        BindGroupLayoutSetLabel,
        BindGroupSetLabel,
        BufferDestroy,
        BufferMapAsync,
        BufferSetLabel,
        BufferUnmap,
        BufferUpdateMappedData,
        CommandBufferSetLabel,
        CommandEncoderBeginComputePass,
        CommandEncoderBeginRenderPass,
        CommandEncoderClearBuffer,
        CommandEncoderCopyBufferToBuffer,
        CommandEncoderCopyBufferToTexture,
        CommandEncoderCopyTextureToBuffer,
        CommandEncoderCopyTextureToTexture,
        CommandEncoderCopyTextureToTextureInternal,
        CommandEncoderFinish,
        CommandEncoderInjectValidationError,
        CommandEncoderInsertDebugMarker,
        CommandEncoderPopDebugGroup,
        CommandEncoderPushDebugGroup,
        CommandEncoderResolveQuerySet,
        CommandEncoderSetLabel,
        CommandEncoderWriteBuffer,
        CommandEncoderWriteTimestamp,
        ComputePassEncoderDispatchWorkgroups,
        ComputePassEncoderDispatchWorkgroupsIndirect,
        ComputePassEncoderEnd,
        ComputePassEncoderInsertDebugMarker,
        ComputePassEncoderPopDebugGroup,
        ComputePassEncoderPushDebugGroup,
        ComputePassEncoderSetBindGroup,
        ComputePassEncoderSetLabel,
        ComputePassEncoderSetPipeline,
        ComputePassEncoderWriteTimestamp,
        ComputePipelineGetBindGroupLayout,
        ComputePipelineSetLabel,
        DestroyObject,
        DeviceCreateBindGroup,
        DeviceCreateBindGroupLayout,
        DeviceCreateBuffer,
        DeviceCreateCommandEncoder,
        DeviceCreateComputePipeline,
        DeviceCreateComputePipelineAsync,
        DeviceCreateErrorBuffer,
        DeviceCreateErrorExternalTexture,
        DeviceCreateErrorShaderModule,
        DeviceCreateErrorTexture,
        DeviceCreateExternalTexture,
        DeviceCreatePipelineLayout,
        DeviceCreateQuerySet,
        DeviceCreateRenderBundleEncoder,
        DeviceCreateRenderPipeline,
        DeviceCreateRenderPipelineAsync,
        DeviceCreateSampler,
        DeviceCreateShaderModule,
        DeviceCreateSwapChain,
        DeviceCreateTexture,
        DeviceDestroy,
        DeviceForceLoss,
        DeviceGetAdapter,
        DeviceGetQueue,
        DeviceInjectError,
        DevicePopErrorScope,
        DevicePushErrorScope,
        DeviceSetLabel,
        DeviceTick,
        DeviceValidateTextureDescriptor,
        ExternalTextureDestroy,
        ExternalTextureExpire,
        ExternalTextureRefresh,
        ExternalTextureSetLabel,
        InstanceCreateSurface,
        InstanceProcessEvents,
        InstanceRequestAdapter,
        PipelineLayoutSetLabel,
        QuerySetDestroy,
        QuerySetSetLabel,
        QueueCopyExternalTextureForBrowser,
        QueueCopyTextureForBrowser,
        QueueOnSubmittedWorkDone,
        QueueSetLabel,
        QueueSubmit,
        QueueWriteBuffer,
        QueueWriteTexture,
        RenderBundleEncoderDraw,
        RenderBundleEncoderDrawIndexed,
        RenderBundleEncoderDrawIndexedIndirect,
        RenderBundleEncoderDrawIndirect,
        RenderBundleEncoderFinish,
        RenderBundleEncoderInsertDebugMarker,
        RenderBundleEncoderPopDebugGroup,
        RenderBundleEncoderPushDebugGroup,
        RenderBundleEncoderSetBindGroup,
        RenderBundleEncoderSetIndexBuffer,
        RenderBundleEncoderSetLabel,
        RenderBundleEncoderSetPipeline,
        RenderBundleEncoderSetVertexBuffer,
        RenderBundleSetLabel,
        RenderPassEncoderBeginOcclusionQuery,
        RenderPassEncoderDraw,
        RenderPassEncoderDrawIndexed,
        RenderPassEncoderDrawIndexedIndirect,
        RenderPassEncoderDrawIndirect,
        RenderPassEncoderEnd,
        RenderPassEncoderEndOcclusionQuery,
        RenderPassEncoderExecuteBundles,
        RenderPassEncoderInsertDebugMarker,
        RenderPassEncoderPopDebugGroup,
        RenderPassEncoderPushDebugGroup,
        RenderPassEncoderSetBindGroup,
        RenderPassEncoderSetBlendConstant,
        RenderPassEncoderSetIndexBuffer,
        RenderPassEncoderSetLabel,
        RenderPassEncoderSetPipeline,
        RenderPassEncoderSetScissorRect,
        RenderPassEncoderSetStencilReference,
        RenderPassEncoderSetVertexBuffer,
        RenderPassEncoderSetViewport,
        RenderPassEncoderWriteTimestamp,
        RenderPipelineGetBindGroupLayout,
        RenderPipelineSetLabel,
        SamplerSetLabel,
        ShaderModuleGetCompilationInfo,
        ShaderModuleSetLabel,
        SwapChainGetCurrentTexture,
        SwapChainGetCurrentTextureView,
        SwapChainPresent,
        TextureCreateView,
        TextureDestroy,
        TextureSetLabel,
        TextureViewSetLabel,
    };

    enum class ReturnWireCmd : uint32_t {
        AdapterRequestDeviceCallback,
        BufferMapAsyncCallback,
        DeviceCreateComputePipelineAsyncCallback,
        DeviceCreateRenderPipelineAsyncCallback,
        DeviceLoggingCallback,
        DeviceLostCallback,
        DevicePopErrorScopeCallback,
        DeviceUncapturedErrorCallback,
        InstanceRequestAdapterCallback,
        QueueWorkDoneCallback,
        ShaderModuleGetCompilationInfoCallback,
    };

    struct CmdHeader {
        uint64_t commandSize;
    };


    struct AdapterGetInstanceCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUAdapter self;
    ObjectHandle result;
};

    struct AdapterRequestDeviceCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId adapterId;
    uint64_t requestSerial;
    ObjectHandle deviceObjectHandle;
    WGPUDeviceDescriptor const * descriptor;
};

    struct BindGroupLayoutSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUBindGroupLayout self;
    char const * label;
};

    struct BindGroupSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUBindGroup self;
    char const * label;
};

    struct BufferDestroyCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUBuffer self;
};

    struct BufferMapAsyncCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId bufferId;
    uint64_t requestSerial;
    WGPUMapModeFlags mode;
    uint64_t offset;
    uint64_t size;
};

    struct BufferSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUBuffer self;
    char const * label;
};

    struct BufferUnmapCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUBuffer self;
};

    struct BufferUpdateMappedDataCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId bufferId;
    uint64_t writeDataUpdateInfoLength;
    uint8_t const * writeDataUpdateInfo;
    uint64_t offset;
    uint64_t size;
};

    struct CommandBufferSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandBuffer self;
    char const * label;
};

    struct CommandEncoderBeginComputePassCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUComputePassDescriptor const * descriptor;
    ObjectHandle result;
};

    struct CommandEncoderBeginRenderPassCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPURenderPassDescriptor const * descriptor;
    ObjectHandle result;
};

    struct CommandEncoderClearBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
};

    struct CommandEncoderCopyBufferToBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUBuffer source;
    uint64_t sourceOffset;
    WGPUBuffer destination;
    uint64_t destinationOffset;
    uint64_t size;
};

    struct CommandEncoderCopyBufferToTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUImageCopyBuffer const * source;
    WGPUImageCopyTexture const * destination;
    WGPUExtent3D const * copySize;
};

    struct CommandEncoderCopyTextureToBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUImageCopyTexture const * source;
    WGPUImageCopyBuffer const * destination;
    WGPUExtent3D const * copySize;
};

    struct CommandEncoderCopyTextureToTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUImageCopyTexture const * source;
    WGPUImageCopyTexture const * destination;
    WGPUExtent3D const * copySize;
};

    struct CommandEncoderCopyTextureToTextureInternalCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUImageCopyTexture const * source;
    WGPUImageCopyTexture const * destination;
    WGPUExtent3D const * copySize;
};

    struct CommandEncoderFinishCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUCommandBufferDescriptor const * descriptor;
    ObjectHandle result;
};

    struct CommandEncoderInjectValidationErrorCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    char const * message;
};

    struct CommandEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    char const * markerLabel;
};

    struct CommandEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
};

    struct CommandEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    char const * groupLabel;
};

    struct CommandEncoderResolveQuerySetCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUQuerySet querySet;
    uint32_t firstQuery;
    uint32_t queryCount;
    WGPUBuffer destination;
    uint64_t destinationOffset;
};

    struct CommandEncoderSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    char const * label;
};

    struct CommandEncoderWriteBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUBuffer buffer;
    uint64_t bufferOffset;
    uint8_t const * data;
    uint64_t size;
};

    struct CommandEncoderWriteTimestampCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUCommandEncoder self;
    WGPUQuerySet querySet;
    uint32_t queryIndex;
};

    struct ComputePassEncoderDispatchWorkgroupsCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    uint32_t workgroupCountX;
    uint32_t workgroupCountY;
    uint32_t workgroupCountZ;
};

    struct ComputePassEncoderDispatchWorkgroupsIndirectCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct ComputePassEncoderEndCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
};

    struct ComputePassEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    char const * markerLabel;
};

    struct ComputePassEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
};

    struct ComputePassEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    char const * groupLabel;
};

    struct ComputePassEncoderSetBindGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    uint32_t groupIndex;
    WGPUBindGroup group;
    size_t dynamicOffsetCount;
    uint32_t const * dynamicOffsets;
};

    struct ComputePassEncoderSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    char const * label;
};

    struct ComputePassEncoderSetPipelineCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    WGPUComputePipeline pipeline;
};

    struct ComputePassEncoderWriteTimestampCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePassEncoder self;
    WGPUQuerySet querySet;
    uint32_t queryIndex;
};

    struct ComputePipelineGetBindGroupLayoutCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePipeline self;
    uint32_t groupIndex;
    ObjectHandle result;
};

    struct ComputePipelineSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUComputePipeline self;
    char const * label;
};

    struct DestroyObjectCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectType objectType;
    ObjectId objectId;
};

    struct DeviceCreateBindGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUBindGroupDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateBindGroupLayoutCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUBindGroupLayoutDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId deviceId;
    WGPUBufferDescriptor const * descriptor;
    ObjectHandle result;
    uint64_t readHandleCreateInfoLength;
    uint8_t const * readHandleCreateInfo;
    uint64_t writeHandleCreateInfoLength;
    uint8_t const * writeHandleCreateInfo;
};

    struct DeviceCreateCommandEncoderCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUCommandEncoderDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateComputePipelineCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUComputePipelineDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateComputePipelineAsyncCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId deviceId;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;
    WGPUComputePipelineDescriptor const * descriptor;
};

    struct DeviceCreateErrorBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUBufferDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateErrorExternalTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    ObjectHandle result;
};

    struct DeviceCreateErrorShaderModuleCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUShaderModuleDescriptor const * descriptor;
    char const * errorMessage;
    ObjectHandle result;
};

    struct DeviceCreateErrorTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUTextureDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateExternalTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUExternalTextureDescriptor const * externalTextureDescriptor;
    ObjectHandle result;
};

    struct DeviceCreatePipelineLayoutCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUPipelineLayoutDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateQuerySetCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUQuerySetDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateRenderBundleEncoderCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPURenderBundleEncoderDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateRenderPipelineCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPURenderPipelineDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateRenderPipelineAsyncCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId deviceId;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;
    WGPURenderPipelineDescriptor const * descriptor;
};

    struct DeviceCreateSamplerCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUSamplerDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateShaderModuleCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUShaderModuleDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateSwapChainCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUSurface surface;
    WGPUSwapChainDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceCreateTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUTextureDescriptor const * descriptor;
    ObjectHandle result;
};

    struct DeviceDestroyCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
};

    struct DeviceForceLossCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUDeviceLostReason type;
    char const * message;
};

    struct DeviceGetAdapterCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    ObjectHandle result;
};

    struct DeviceGetQueueCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    ObjectHandle result;
};

    struct DeviceInjectErrorCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUErrorType type;
    char const * message;
};

    struct DevicePopErrorScopeCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId deviceId;
    uint64_t requestSerial;
};

    struct DevicePushErrorScopeCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUErrorFilter filter;
};

    struct DeviceSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    char const * label;
};

    struct DeviceTickCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
};

    struct DeviceValidateTextureDescriptorCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUDevice self;
    WGPUTextureDescriptor const * descriptor;
};

    struct ExternalTextureDestroyCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUExternalTexture self;
};

    struct ExternalTextureExpireCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUExternalTexture self;
};

    struct ExternalTextureRefreshCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUExternalTexture self;
};

    struct ExternalTextureSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUExternalTexture self;
    char const * label;
};

    struct InstanceCreateSurfaceCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUInstance self;
    WGPUSurfaceDescriptor const * descriptor;
    ObjectHandle result;
};

    struct InstanceProcessEventsCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUInstance self;
};

    struct InstanceRequestAdapterCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId instanceId;
    uint64_t requestSerial;
    ObjectHandle adapterObjectHandle;
    WGPURequestAdapterOptions const * options;
};

    struct PipelineLayoutSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUPipelineLayout self;
    char const * label;
};

    struct QuerySetDestroyCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUQuerySet self;
};

    struct QuerySetSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUQuerySet self;
    char const * label;
};

    struct QueueCopyExternalTextureForBrowserCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUQueue self;
    WGPUImageCopyExternalTexture const * source;
    WGPUImageCopyTexture const * destination;
    WGPUExtent3D const * copySize;
    WGPUCopyTextureForBrowserOptions const * options;
};

    struct QueueCopyTextureForBrowserCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUQueue self;
    WGPUImageCopyTexture const * source;
    WGPUImageCopyTexture const * destination;
    WGPUExtent3D const * copySize;
    WGPUCopyTextureForBrowserOptions const * options;
};

    struct QueueOnSubmittedWorkDoneCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId queueId;
    uint64_t signalValue;
    uint64_t requestSerial;
};

    struct QueueSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUQueue self;
    char const * label;
};

    struct QueueSubmitCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUQueue self;
    size_t commandCount;
    WGPUCommandBuffer const * commands;
};

    struct QueueWriteBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId queueId;
    ObjectId bufferId;
    uint64_t bufferOffset;
    uint8_t const * data;
    uint64_t size;
};

    struct QueueWriteTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId queueId;
    WGPUImageCopyTexture const * destination;
    uint8_t const * data;
    uint64_t dataSize;
    WGPUTextureDataLayout const * dataLayout;
    WGPUExtent3D const * writeSize;
};

    struct RenderBundleEncoderDrawCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

    struct RenderBundleEncoderDrawIndexedCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;
};

    struct RenderBundleEncoderDrawIndexedIndirectCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderBundleEncoderDrawIndirectCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderBundleEncoderFinishCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPURenderBundleDescriptor const * descriptor;
    ObjectHandle result;
};

    struct RenderBundleEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    char const * markerLabel;
};

    struct RenderBundleEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
};

    struct RenderBundleEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    char const * groupLabel;
};

    struct RenderBundleEncoderSetBindGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t groupIndex;
    WGPUBindGroup group;
    size_t dynamicOffsetCount;
    uint32_t const * dynamicOffsets;
};

    struct RenderBundleEncoderSetIndexBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPUBuffer buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;
};

    struct RenderBundleEncoderSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    char const * label;
};

    struct RenderBundleEncoderSetPipelineCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    WGPURenderPipeline pipeline;
};

    struct RenderBundleEncoderSetVertexBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundleEncoder self;
    uint32_t slot;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
};

    struct RenderBundleSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderBundle self;
    char const * label;
};

    struct RenderPassEncoderBeginOcclusionQueryCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t queryIndex;
};

    struct RenderPassEncoderDrawCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

    struct RenderPassEncoderDrawIndexedCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;
};

    struct RenderPassEncoderDrawIndexedIndirectCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderPassEncoderDrawIndirectCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUBuffer indirectBuffer;
    uint64_t indirectOffset;
};

    struct RenderPassEncoderEndCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
};

    struct RenderPassEncoderEndOcclusionQueryCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
};

    struct RenderPassEncoderExecuteBundlesCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    size_t bundleCount;
    WGPURenderBundle const * bundles;
};

    struct RenderPassEncoderInsertDebugMarkerCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    char const * markerLabel;
};

    struct RenderPassEncoderPopDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
};

    struct RenderPassEncoderPushDebugGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    char const * groupLabel;
};

    struct RenderPassEncoderSetBindGroupCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t groupIndex;
    WGPUBindGroup group;
    size_t dynamicOffsetCount;
    uint32_t const * dynamicOffsets;
};

    struct RenderPassEncoderSetBlendConstantCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUColor const * color;
};

    struct RenderPassEncoderSetIndexBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUBuffer buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;
};

    struct RenderPassEncoderSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    char const * label;
};

    struct RenderPassEncoderSetPipelineCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPURenderPipeline pipeline;
};

    struct RenderPassEncoderSetScissorRectCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

    struct RenderPassEncoderSetStencilReferenceCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t reference;
};

    struct RenderPassEncoderSetVertexBufferCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    uint32_t slot;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
};

    struct RenderPassEncoderSetViewportCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;
};

    struct RenderPassEncoderWriteTimestampCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPassEncoder self;
    WGPUQuerySet querySet;
    uint32_t queryIndex;
};

    struct RenderPipelineGetBindGroupLayoutCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPipeline self;
    uint32_t groupIndex;
    ObjectHandle result;
};

    struct RenderPipelineSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPURenderPipeline self;
    char const * label;
};

    struct SamplerSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUSampler self;
    char const * label;
};

    struct ShaderModuleGetCompilationInfoCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectId shaderModuleId;
    uint64_t requestSerial;
};

    struct ShaderModuleSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUShaderModule self;
    char const * label;
};

    struct SwapChainGetCurrentTextureCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUSwapChain self;
    ObjectHandle result;
};

    struct SwapChainGetCurrentTextureViewCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUSwapChain self;
    ObjectHandle result;
};

    struct SwapChainPresentCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUSwapChain self;
};

    struct TextureCreateViewCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUTexture self;
    WGPUTextureViewDescriptor const * descriptor;
    ObjectHandle result;
};

    struct TextureDestroyCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUTexture self;
};

    struct TextureSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUTexture self;
    char const * label;
};

    struct TextureViewSetLabelCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);

    ObjectId selfId;

    WGPUTextureView self;
    char const * label;
};


    struct ReturnAdapterRequestDeviceCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle adapter;
    uint64_t requestSerial;
    WGPURequestDeviceStatus status;
    char const * message;
    WGPUSupportedLimits const * limits;
    uint32_t featuresCount;
    WGPUFeatureName const * features;
};

    struct ReturnBufferMapAsyncCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle buffer;
    uint64_t requestSerial;
    uint32_t status;
    uint64_t readDataUpdateInfoLength;
    uint8_t const * readDataUpdateInfo;
};

    struct ReturnDeviceCreateComputePipelineAsyncCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle device;
    uint64_t requestSerial;
    WGPUCreatePipelineAsyncStatus status;
    char const * message;
};

    struct ReturnDeviceCreateRenderPipelineAsyncCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle device;
    uint64_t requestSerial;
    WGPUCreatePipelineAsyncStatus status;
    char const * message;
};

    struct ReturnDeviceLoggingCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle device;
    WGPULoggingType type;
    char const * message;
};

    struct ReturnDeviceLostCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle device;
    WGPUDeviceLostReason reason;
    char const * message;
};

    struct ReturnDevicePopErrorScopeCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle device;
    uint64_t requestSerial;
    WGPUErrorType type;
    char const * message;
};

    struct ReturnDeviceUncapturedErrorCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle device;
    WGPUErrorType type;
    char const * message;
};

    struct ReturnInstanceRequestAdapterCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle instance;
    uint64_t requestSerial;
    WGPURequestAdapterStatus status;
    char const * message;
    WGPUAdapterProperties const * properties;
    WGPUSupportedLimits const * limits;
    uint32_t featuresCount;
    WGPUFeatureName const * features;
};

    struct ReturnQueueWorkDoneCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle queue;
    uint64_t requestSerial;
    WGPUQueueWorkDoneStatus status;
};

    struct ReturnShaderModuleGetCompilationInfoCallbackCmd {
    size_t GetRequiredSize() const;

    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer, const ObjectIdProvider& objectIdProvider) const;
    // Override which produces a FatalError if any object is used.
    WireResult Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const;

    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator, const ObjectIdResolver& resolver);
    // Override which produces a FatalError if any object is used.
    WireResult Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator);


    ObjectHandle shaderModule;
    uint64_t requestSerial;
    WGPUCompilationInfoRequestStatus status;
    WGPUCompilationInfo const * info;
};


}  // namespace dawn::wire

#endif // DAWNWIRE_WIRECMD_AUTOGEN_H_
