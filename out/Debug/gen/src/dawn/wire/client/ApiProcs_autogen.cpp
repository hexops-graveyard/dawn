
#include "dawn/wire/client/ApiObjects.h"
#include "dawn/wire/client/Client.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

namespace dawn::wire::client {




    static
    WGPUDevice ClientAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->CreateDevice( descriptor);
    }

    static
    size_t ClientAdapterEnumerateFeatures(WGPUAdapter cSelf, WGPUFeatureName * features) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->EnumerateFeatures( features);
    }

    static
    WGPUInstance ClientAdapterGetInstance(WGPUAdapter cSelf) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->GetInstance();
    }

    static
    WGPUBool ClientAdapterGetLimits(WGPUAdapter cSelf, WGPUSupportedLimits * limits) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->GetLimits( limits);
    }

    static
    void ClientAdapterGetProperties(WGPUAdapter cSelf, WGPUAdapterProperties * properties) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->GetProperties( properties);
    }

    static
    WGPUBool ClientAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->HasFeature( feature);
    }

    static
    void ClientAdapterRequestDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallback callback, void * userdata) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->RequestDevice( descriptor,  callback,  userdata);
    }

    void ClientAdapterRelease(WGPUAdapter cObj) {
        Adapter* obj = reinterpret_cast<Adapter*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Adapter;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientAdapterReference(WGPUAdapter cObj) {
        reinterpret_cast<Adapter*>(cObj)->Reference();
    }


    void ClientBindGroupSetLabel(WGPUBindGroup cSelf, char const * label) {
        auto self = reinterpret_cast<BindGroup*>(cSelf);
        BindGroupSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientBindGroupRelease(WGPUBindGroup cObj) {
        BindGroup* obj = reinterpret_cast<BindGroup*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::BindGroup;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientBindGroupReference(WGPUBindGroup cObj) {
        reinterpret_cast<BindGroup*>(cObj)->Reference();
    }


    void ClientBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, char const * label) {
        auto self = reinterpret_cast<BindGroupLayout*>(cSelf);
        BindGroupLayoutSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientBindGroupLayoutRelease(WGPUBindGroupLayout cObj) {
        BindGroupLayout* obj = reinterpret_cast<BindGroupLayout*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::BindGroupLayout;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientBindGroupLayoutReference(WGPUBindGroupLayout cObj) {
        reinterpret_cast<BindGroupLayout*>(cObj)->Reference();
    }


    static
    void ClientBufferDestroy(WGPUBuffer cSelf) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->Destroy();
    }

    static
    void const * ClientBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetConstMappedRange( offset,  size);
    }

    static
    WGPUBufferMapState ClientBufferGetMapState(WGPUBuffer cSelf) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetMapState();
    }

    static
    void * ClientBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetMappedRange( offset,  size);
    }

    static
    uint64_t ClientBufferGetSize(WGPUBuffer cSelf) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetSize();
    }

    static
    WGPUBufferUsageFlags ClientBufferGetUsage(WGPUBuffer cSelf) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetUsage();
    }

    static
    void ClientBufferMapAsync(WGPUBuffer cSelf, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void * userdata) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->MapAsync( mode,  offset,  size,  callback,  userdata);
    }

    void ClientBufferSetLabel(WGPUBuffer cSelf, char const * label) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        BufferSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    static
    void ClientBufferUnmap(WGPUBuffer cSelf) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->Unmap();
    }

    void ClientBufferRelease(WGPUBuffer cObj) {
        Buffer* obj = reinterpret_cast<Buffer*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Buffer;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientBufferReference(WGPUBuffer cObj) {
        reinterpret_cast<Buffer*>(cObj)->Reference();
    }


    void ClientCommandBufferSetLabel(WGPUCommandBuffer cSelf, char const * label) {
        auto self = reinterpret_cast<CommandBuffer*>(cSelf);
        CommandBufferSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandBufferRelease(WGPUCommandBuffer cObj) {
        CommandBuffer* obj = reinterpret_cast<CommandBuffer*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::CommandBuffer;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientCommandBufferReference(WGPUCommandBuffer cObj) {
        reinterpret_cast<CommandBuffer*>(cObj)->Reference();
    }


    WGPUComputePassEncoder ClientCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderBeginComputePassCmd cmd;

        cmd.self = cSelf;


        ComputePassEncoder* returnObject;
        if constexpr (std::is_constructible_v<ComputePassEncoder, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<ComputePassEncoder>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<ComputePassEncoder>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPURenderPassEncoder ClientCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderBeginRenderPassCmd cmd;

        cmd.self = cSelf;


        RenderPassEncoder* returnObject;
        if constexpr (std::is_constructible_v<RenderPassEncoder, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<RenderPassEncoder>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<RenderPassEncoder>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderClearBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyBufferToBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.sourceOffset = sourceOffset;
        
        cmd.destination = destination;
        
        cmd.destinationOffset = destinationOffset;
        
        cmd.size = size;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyBufferToTextureCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyTextureToBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyTextureToTextureCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;

        self->GetClient()->SerializeCommand(cmd);

    }

    WGPUCommandBuffer ClientCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderFinishCmd cmd;

        cmd.self = cSelf;


        CommandBuffer* returnObject;
        if constexpr (std::is_constructible_v<CommandBuffer, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<CommandBuffer>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<CommandBuffer>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, char const * message) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderInjectValidationErrorCmd cmd;

        cmd.self = cSelf;


        
        cmd.message = message;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderResolveQuerySetCmd cmd;

        cmd.self = cSelf;


        
        cmd.querySet = querySet;
        
        cmd.firstQuery = firstQuery;
        
        cmd.queryCount = queryCount;
        
        cmd.destination = destination;
        
        cmd.destinationOffset = destinationOffset;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderSetLabel(WGPUCommandEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderWriteBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.bufferOffset = bufferOffset;
        
        cmd.data = data;
        
        cmd.size = size;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        
        cmd.querySet = querySet;
        
        cmd.queryIndex = queryIndex;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientCommandEncoderRelease(WGPUCommandEncoder cObj) {
        CommandEncoder* obj = reinterpret_cast<CommandEncoder*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::CommandEncoder;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientCommandEncoderReference(WGPUCommandEncoder cObj) {
        reinterpret_cast<CommandEncoder*>(cObj)->Reference();
    }


    void ClientComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder cSelf, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderDispatchWorkgroupsCmd cmd;

        cmd.self = cSelf;


        
        cmd.workgroupCountX = workgroupCountX;
        
        cmd.workgroupCountY = workgroupCountY;
        
        cmd.workgroupCountZ = workgroupCountZ;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderDispatchWorkgroupsIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderEnd(WGPUComputePassEncoder cSelf) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderEndCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupIndex = groupIndex;
        
        cmd.group = group;
        
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        
        cmd.dynamicOffsets = dynamicOffsets;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        
        cmd.pipeline = pipeline;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        
        cmd.querySet = querySet;
        
        cmd.queryIndex = queryIndex;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderRelease(WGPUComputePassEncoder cObj) {
        ComputePassEncoder* obj = reinterpret_cast<ComputePassEncoder*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ComputePassEncoder;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientComputePassEncoderReference(WGPUComputePassEncoder cObj) {
        reinterpret_cast<ComputePassEncoder*>(cObj)->Reference();
    }


    WGPUBindGroupLayout ClientComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
        auto self = reinterpret_cast<ComputePipeline*>(cSelf);
        ComputePipelineGetBindGroupLayoutCmd cmd;

        cmd.self = cSelf;


        BindGroupLayout* returnObject;
        if constexpr (std::is_constructible_v<BindGroupLayout, const ObjectBaseParams&, decltype(groupIndex)>) {
            returnObject = self->GetClient()->Make<BindGroupLayout>(groupIndex);
        } else {
            returnObject = self->GetClient()->Make<BindGroupLayout>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.groupIndex = groupIndex;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientComputePipelineSetLabel(WGPUComputePipeline cSelf, char const * label) {
        auto self = reinterpret_cast<ComputePipeline*>(cSelf);
        ComputePipelineSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientComputePipelineRelease(WGPUComputePipeline cObj) {
        ComputePipeline* obj = reinterpret_cast<ComputePipeline*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ComputePipeline;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientComputePipelineReference(WGPUComputePipeline cObj) {
        reinterpret_cast<ComputePipeline*>(cObj)->Reference();
    }


    WGPUBindGroup ClientDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateBindGroupCmd cmd;

        cmd.self = cSelf;


        BindGroup* returnObject;
        if constexpr (std::is_constructible_v<BindGroup, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<BindGroup>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<BindGroup>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUBindGroupLayout ClientDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateBindGroupLayoutCmd cmd;

        cmd.self = cSelf;


        BindGroupLayout* returnObject;
        if constexpr (std::is_constructible_v<BindGroupLayout, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<BindGroupLayout>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<BindGroupLayout>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    static
    WGPUBuffer ClientDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateBuffer( descriptor);
    }

    WGPUCommandEncoder ClientDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateCommandEncoderCmd cmd;

        cmd.self = cSelf;


        CommandEncoder* returnObject;
        if constexpr (std::is_constructible_v<CommandEncoder, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<CommandEncoder>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<CommandEncoder>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUComputePipeline ClientDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateComputePipelineCmd cmd;

        cmd.self = cSelf;


        ComputePipeline* returnObject;
        if constexpr (std::is_constructible_v<ComputePipeline, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<ComputePipeline>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<ComputePipeline>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    static
    void ClientDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateComputePipelineAsync( descriptor,  callback,  userdata);
    }

    WGPUBuffer ClientDeviceCreateErrorBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateErrorBufferCmd cmd;

        cmd.self = cSelf;


        Buffer* returnObject;
        if constexpr (std::is_constructible_v<Buffer, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<Buffer>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<Buffer>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUExternalTexture ClientDeviceCreateErrorExternalTexture(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateErrorExternalTextureCmd cmd;

        cmd.self = cSelf;


        ExternalTexture* returnObject;
        if constexpr (std::is_constructible_v<ExternalTexture, const ObjectBaseParams&>) {
            returnObject = self->GetClient()->Make<ExternalTexture>();
        } else {
            returnObject = self->GetClient()->Make<ExternalTexture>();
        }
        cmd.result = returnObject->GetWireHandle();


        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUShaderModule ClientDeviceCreateErrorShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor, char const * errorMessage) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateErrorShaderModuleCmd cmd;

        cmd.self = cSelf;


        ShaderModule* returnObject;
        if constexpr (std::is_constructible_v<ShaderModule, const ObjectBaseParams&, decltype(descriptor), decltype(errorMessage)>) {
            returnObject = self->GetClient()->Make<ShaderModule>(descriptor, errorMessage);
        } else {
            returnObject = self->GetClient()->Make<ShaderModule>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;
        
        cmd.errorMessage = errorMessage;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUTexture ClientDeviceCreateErrorTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateErrorTextureCmd cmd;

        cmd.self = cSelf;


        Texture* returnObject;
        if constexpr (std::is_constructible_v<Texture, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<Texture>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<Texture>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUExternalTexture ClientDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateExternalTextureCmd cmd;

        cmd.self = cSelf;


        ExternalTexture* returnObject;
        if constexpr (std::is_constructible_v<ExternalTexture, const ObjectBaseParams&, decltype(externalTextureDescriptor)>) {
            returnObject = self->GetClient()->Make<ExternalTexture>(externalTextureDescriptor);
        } else {
            returnObject = self->GetClient()->Make<ExternalTexture>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.externalTextureDescriptor = externalTextureDescriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUPipelineLayout ClientDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreatePipelineLayoutCmd cmd;

        cmd.self = cSelf;


        PipelineLayout* returnObject;
        if constexpr (std::is_constructible_v<PipelineLayout, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<PipelineLayout>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<PipelineLayout>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUQuerySet ClientDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateQuerySetCmd cmd;

        cmd.self = cSelf;


        QuerySet* returnObject;
        if constexpr (std::is_constructible_v<QuerySet, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<QuerySet>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<QuerySet>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPURenderBundleEncoder ClientDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateRenderBundleEncoderCmd cmd;

        cmd.self = cSelf;


        RenderBundleEncoder* returnObject;
        if constexpr (std::is_constructible_v<RenderBundleEncoder, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<RenderBundleEncoder>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<RenderBundleEncoder>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPURenderPipeline ClientDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateRenderPipelineCmd cmd;

        cmd.self = cSelf;


        RenderPipeline* returnObject;
        if constexpr (std::is_constructible_v<RenderPipeline, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<RenderPipeline>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<RenderPipeline>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    static
    void ClientDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateRenderPipelineAsync( descriptor,  callback,  userdata);
    }

    WGPUSampler ClientDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateSamplerCmd cmd;

        cmd.self = cSelf;


        Sampler* returnObject;
        if constexpr (std::is_constructible_v<Sampler, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<Sampler>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<Sampler>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUShaderModule ClientDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateShaderModuleCmd cmd;

        cmd.self = cSelf;


        ShaderModule* returnObject;
        if constexpr (std::is_constructible_v<ShaderModule, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<ShaderModule>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<ShaderModule>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUSwapChain ClientDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateSwapChainCmd cmd;

        cmd.self = cSelf;


        SwapChain* returnObject;
        if constexpr (std::is_constructible_v<SwapChain, const ObjectBaseParams&, decltype(surface), decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<SwapChain>(surface, descriptor);
        } else {
            returnObject = self->GetClient()->Make<SwapChain>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.surface = surface;
        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    WGPUTexture ClientDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateTextureCmd cmd;

        cmd.self = cSelf;


        Texture* returnObject;
        if constexpr (std::is_constructible_v<Texture, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<Texture>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<Texture>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientDeviceDestroy(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceDestroyCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    static
    size_t ClientDeviceEnumerateFeatures(WGPUDevice cSelf, WGPUFeatureName * features) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->EnumerateFeatures( features);
    }

    void ClientDeviceForceLoss(WGPUDevice cSelf, WGPUDeviceLostReason type, char const * message) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceForceLossCmd cmd;

        cmd.self = cSelf;


        
        cmd.type = type;
        
        cmd.message = message;

        self->GetClient()->SerializeCommand(cmd);

    }

    static
    WGPUBool ClientDeviceGetLimits(WGPUDevice cSelf, WGPUSupportedLimits * limits) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->GetLimits( limits);
    }

    static
    WGPUQueue ClientDeviceGetQueue(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->GetQueue();
    }

    static
    WGPUBool ClientDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->HasFeature( feature);
    }

    static
    void ClientDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->InjectError( type,  message);
    }

    static
    void ClientDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->PopErrorScope( callback,  userdata);
    }

    void ClientDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DevicePushErrorScopeCmd cmd;

        cmd.self = cSelf;


        
        cmd.filter = filter;

        self->GetClient()->SerializeCommand(cmd);

    }

    static
    void ClientDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->SetDeviceLostCallback( callback,  userdata);
    }

    void ClientDeviceSetLabel(WGPUDevice cSelf, char const * label) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    static
    void ClientDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->SetLoggingCallback( callback,  userdata);
    }

    static
    void ClientDeviceSetUncapturedErrorCallback(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->SetUncapturedErrorCallback( callback,  userdata);
    }

    void ClientDeviceTick(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceTickCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientDeviceValidateTextureDescriptor(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceValidateTextureDescriptorCmd cmd;

        cmd.self = cSelf;


        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientDeviceRelease(WGPUDevice cObj) {
        Device* obj = reinterpret_cast<Device*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Device;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientDeviceReference(WGPUDevice cObj) {
        reinterpret_cast<Device*>(cObj)->Reference();
    }


    void ClientExternalTextureDestroy(WGPUExternalTexture cSelf) {
        auto self = reinterpret_cast<ExternalTexture*>(cSelf);
        ExternalTextureDestroyCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientExternalTextureExpire(WGPUExternalTexture cSelf) {
        auto self = reinterpret_cast<ExternalTexture*>(cSelf);
        ExternalTextureExpireCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientExternalTextureRefresh(WGPUExternalTexture cSelf) {
        auto self = reinterpret_cast<ExternalTexture*>(cSelf);
        ExternalTextureRefreshCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientExternalTextureSetLabel(WGPUExternalTexture cSelf, char const * label) {
        auto self = reinterpret_cast<ExternalTexture*>(cSelf);
        ExternalTextureSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientExternalTextureRelease(WGPUExternalTexture cObj) {
        ExternalTexture* obj = reinterpret_cast<ExternalTexture*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ExternalTexture;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientExternalTextureReference(WGPUExternalTexture cObj) {
        reinterpret_cast<ExternalTexture*>(cObj)->Reference();
    }


    WGPUSurface ClientInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
        auto self = reinterpret_cast<Instance*>(cSelf);
        InstanceCreateSurfaceCmd cmd;

        cmd.self = cSelf;


        Surface* returnObject;
        if constexpr (std::is_constructible_v<Surface, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<Surface>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<Surface>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientInstanceProcessEvents(WGPUInstance cSelf) {
        auto self = reinterpret_cast<Instance*>(cSelf);
        InstanceProcessEventsCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    static
    void ClientInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
        auto self = reinterpret_cast<Instance*>(cSelf);
        return self->RequestAdapter( options,  callback,  userdata);
    }

    void ClientInstanceRelease(WGPUInstance cObj) {
        Instance* obj = reinterpret_cast<Instance*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Instance;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientInstanceReference(WGPUInstance cObj) {
        reinterpret_cast<Instance*>(cObj)->Reference();
    }


    void ClientPipelineLayoutSetLabel(WGPUPipelineLayout cSelf, char const * label) {
        auto self = reinterpret_cast<PipelineLayout*>(cSelf);
        PipelineLayoutSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientPipelineLayoutRelease(WGPUPipelineLayout cObj) {
        PipelineLayout* obj = reinterpret_cast<PipelineLayout*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::PipelineLayout;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientPipelineLayoutReference(WGPUPipelineLayout cObj) {
        reinterpret_cast<PipelineLayout*>(cObj)->Reference();
    }


    void ClientQuerySetDestroy(WGPUQuerySet cSelf) {
        auto self = reinterpret_cast<QuerySet*>(cSelf);
        QuerySetDestroyCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    static
    uint32_t ClientQuerySetGetCount(WGPUQuerySet cSelf) {
        auto self = reinterpret_cast<QuerySet*>(cSelf);
        return self->GetCount();
    }

    static
    WGPUQueryType ClientQuerySetGetType(WGPUQuerySet cSelf) {
        auto self = reinterpret_cast<QuerySet*>(cSelf);
        return self->GetType();
    }

    void ClientQuerySetSetLabel(WGPUQuerySet cSelf, char const * label) {
        auto self = reinterpret_cast<QuerySet*>(cSelf);
        QuerySetSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientQuerySetRelease(WGPUQuerySet cObj) {
        QuerySet* obj = reinterpret_cast<QuerySet*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::QuerySet;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientQuerySetReference(WGPUQuerySet cObj) {
        reinterpret_cast<QuerySet*>(cObj)->Reference();
    }


    void ClientQueueCopyExternalTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyExternalTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        QueueCopyExternalTextureForBrowserCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;
        
        cmd.options = options;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        QueueCopyTextureForBrowserCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;
        
        cmd.options = options;

        self->GetClient()->SerializeCommand(cmd);

    }

    static
    void ClientQueueOnSubmittedWorkDone(WGPUQueue cSelf, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        return self->OnSubmittedWorkDone( signalValue,  callback,  userdata);
    }

    void ClientQueueSetLabel(WGPUQueue cSelf, char const * label) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        QueueSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientQueueSubmit(WGPUQueue cSelf, size_t commandCount, WGPUCommandBuffer const * commands) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        QueueSubmitCmd cmd;

        cmd.self = cSelf;


        
        cmd.commandCount = commandCount;
        
        cmd.commands = commands;

        self->GetClient()->SerializeCommand(cmd);

    }

    static
    void ClientQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        return self->WriteBuffer( buffer,  bufferOffset,  data,  size);
    }

    static
    void ClientQueueWriteTexture(WGPUQueue cSelf, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        return self->WriteTexture( destination,  data,  dataSize,  dataLayout,  writeSize);
    }

    void ClientQueueRelease(WGPUQueue cObj) {
        Queue* obj = reinterpret_cast<Queue*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Queue;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientQueueReference(WGPUQueue cObj) {
        reinterpret_cast<Queue*>(cObj)->Reference();
    }


    void ClientRenderBundleSetLabel(WGPURenderBundle cSelf, char const * label) {
        auto self = reinterpret_cast<RenderBundle*>(cSelf);
        RenderBundleSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleRelease(WGPURenderBundle cObj) {
        RenderBundle* obj = reinterpret_cast<RenderBundle*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderBundle;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientRenderBundleReference(WGPURenderBundle cObj) {
        reinterpret_cast<RenderBundle*>(cObj)->Reference();
    }


    void ClientRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderDrawCmd cmd;

        cmd.self = cSelf;


        
        cmd.vertexCount = vertexCount;
        
        cmd.instanceCount = instanceCount;
        
        cmd.firstVertex = firstVertex;
        
        cmd.firstInstance = firstInstance;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderDrawIndexedCmd cmd;

        cmd.self = cSelf;


        
        cmd.indexCount = indexCount;
        
        cmd.instanceCount = instanceCount;
        
        cmd.firstIndex = firstIndex;
        
        cmd.baseVertex = baseVertex;
        
        cmd.firstInstance = firstInstance;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderDrawIndexedIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderDrawIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->GetClient()->SerializeCommand(cmd);

    }

    WGPURenderBundle ClientRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderFinishCmd cmd;

        cmd.self = cSelf;


        RenderBundle* returnObject;
        if constexpr (std::is_constructible_v<RenderBundle, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<RenderBundle>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<RenderBundle>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupIndex = groupIndex;
        
        cmd.group = group;
        
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        
        cmd.dynamicOffsets = dynamicOffsets;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetIndexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.format = format;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        
        cmd.pipeline = pipeline;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetVertexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.slot = slot;
        
        cmd.buffer = buffer;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderRelease(WGPURenderBundleEncoder cObj) {
        RenderBundleEncoder* obj = reinterpret_cast<RenderBundleEncoder*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderBundleEncoder;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientRenderBundleEncoderReference(WGPURenderBundleEncoder cObj) {
        reinterpret_cast<RenderBundleEncoder*>(cObj)->Reference();
    }


    void ClientRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderBeginOcclusionQueryCmd cmd;

        cmd.self = cSelf;


        
        cmd.queryIndex = queryIndex;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderDrawCmd cmd;

        cmd.self = cSelf;


        
        cmd.vertexCount = vertexCount;
        
        cmd.instanceCount = instanceCount;
        
        cmd.firstVertex = firstVertex;
        
        cmd.firstInstance = firstInstance;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderDrawIndexedCmd cmd;

        cmd.self = cSelf;


        
        cmd.indexCount = indexCount;
        
        cmd.instanceCount = instanceCount;
        
        cmd.firstIndex = firstIndex;
        
        cmd.baseVertex = baseVertex;
        
        cmd.firstInstance = firstInstance;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderDrawIndexedIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderDrawIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderEnd(WGPURenderPassEncoder cSelf) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderEndCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderEndOcclusionQueryCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, size_t bundleCount, WGPURenderBundle const * bundles) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderExecuteBundlesCmd cmd;

        cmd.self = cSelf;


        
        cmd.bundleCount = bundleCount;
        
        cmd.bundles = bundles;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupIndex = groupIndex;
        
        cmd.group = group;
        
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        
        cmd.dynamicOffsets = dynamicOffsets;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetBlendConstantCmd cmd;

        cmd.self = cSelf;


        
        cmd.color = color;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetIndexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.format = format;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        
        cmd.pipeline = pipeline;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetScissorRectCmd cmd;

        cmd.self = cSelf;


        
        cmd.x = x;
        
        cmd.y = y;
        
        cmd.width = width;
        
        cmd.height = height;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetStencilReferenceCmd cmd;

        cmd.self = cSelf;


        
        cmd.reference = reference;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetVertexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.slot = slot;
        
        cmd.buffer = buffer;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetViewportCmd cmd;

        cmd.self = cSelf;


        
        cmd.x = x;
        
        cmd.y = y;
        
        cmd.width = width;
        
        cmd.height = height;
        
        cmd.minDepth = minDepth;
        
        cmd.maxDepth = maxDepth;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        
        cmd.querySet = querySet;
        
        cmd.queryIndex = queryIndex;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderRelease(WGPURenderPassEncoder cObj) {
        RenderPassEncoder* obj = reinterpret_cast<RenderPassEncoder*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderPassEncoder;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientRenderPassEncoderReference(WGPURenderPassEncoder cObj) {
        reinterpret_cast<RenderPassEncoder*>(cObj)->Reference();
    }


    WGPUBindGroupLayout ClientRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
        auto self = reinterpret_cast<RenderPipeline*>(cSelf);
        RenderPipelineGetBindGroupLayoutCmd cmd;

        cmd.self = cSelf;


        BindGroupLayout* returnObject;
        if constexpr (std::is_constructible_v<BindGroupLayout, const ObjectBaseParams&, decltype(groupIndex)>) {
            returnObject = self->GetClient()->Make<BindGroupLayout>(groupIndex);
        } else {
            returnObject = self->GetClient()->Make<BindGroupLayout>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.groupIndex = groupIndex;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientRenderPipelineSetLabel(WGPURenderPipeline cSelf, char const * label) {
        auto self = reinterpret_cast<RenderPipeline*>(cSelf);
        RenderPipelineSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientRenderPipelineRelease(WGPURenderPipeline cObj) {
        RenderPipeline* obj = reinterpret_cast<RenderPipeline*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderPipeline;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientRenderPipelineReference(WGPURenderPipeline cObj) {
        reinterpret_cast<RenderPipeline*>(cObj)->Reference();
    }


    void ClientSamplerSetLabel(WGPUSampler cSelf, char const * label) {
        auto self = reinterpret_cast<Sampler*>(cSelf);
        SamplerSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientSamplerRelease(WGPUSampler cObj) {
        Sampler* obj = reinterpret_cast<Sampler*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Sampler;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientSamplerReference(WGPUSampler cObj) {
        reinterpret_cast<Sampler*>(cObj)->Reference();
    }


    static
    void ClientShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallback callback, void * userdata) {
        auto self = reinterpret_cast<ShaderModule*>(cSelf);
        return self->GetCompilationInfo( callback,  userdata);
    }

    void ClientShaderModuleSetLabel(WGPUShaderModule cSelf, char const * label) {
        auto self = reinterpret_cast<ShaderModule*>(cSelf);
        ShaderModuleSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientShaderModuleRelease(WGPUShaderModule cObj) {
        ShaderModule* obj = reinterpret_cast<ShaderModule*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ShaderModule;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientShaderModuleReference(WGPUShaderModule cObj) {
        reinterpret_cast<ShaderModule*>(cObj)->Reference();
    }


    void ClientSurfaceRelease(WGPUSurface cObj) {
        Surface* obj = reinterpret_cast<Surface*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Surface;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientSurfaceReference(WGPUSurface cObj) {
        reinterpret_cast<Surface*>(cObj)->Reference();
    }


    static
    WGPUTexture ClientSwapChainGetCurrentTexture(WGPUSwapChain cSelf) {
        auto self = reinterpret_cast<SwapChain*>(cSelf);
        return self->GetCurrentTexture();
    }

    WGPUTextureView ClientSwapChainGetCurrentTextureView(WGPUSwapChain cSelf) {
        auto self = reinterpret_cast<SwapChain*>(cSelf);
        SwapChainGetCurrentTextureViewCmd cmd;

        cmd.self = cSelf;


        TextureView* returnObject;
        if constexpr (std::is_constructible_v<TextureView, const ObjectBaseParams&>) {
            returnObject = self->GetClient()->Make<TextureView>();
        } else {
            returnObject = self->GetClient()->Make<TextureView>();
        }
        cmd.result = returnObject->GetWireHandle();


        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientSwapChainPresent(WGPUSwapChain cSelf) {
        auto self = reinterpret_cast<SwapChain*>(cSelf);
        SwapChainPresentCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientSwapChainRelease(WGPUSwapChain cObj) {
        SwapChain* obj = reinterpret_cast<SwapChain*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::SwapChain;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientSwapChainReference(WGPUSwapChain cObj) {
        reinterpret_cast<SwapChain*>(cObj)->Reference();
    }


    WGPUTextureView ClientTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        TextureCreateViewCmd cmd;

        cmd.self = cSelf;


        TextureView* returnObject;
        if constexpr (std::is_constructible_v<TextureView, const ObjectBaseParams&, decltype(descriptor)>) {
            returnObject = self->GetClient()->Make<TextureView>(descriptor);
        } else {
            returnObject = self->GetClient()->Make<TextureView>();
        }
        cmd.result = returnObject->GetWireHandle();

        
        cmd.descriptor = descriptor;

        self->GetClient()->SerializeCommand(cmd);

        return ToAPI(returnObject);
    }

    void ClientTextureDestroy(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        TextureDestroyCmd cmd;

        cmd.self = cSelf;



        self->GetClient()->SerializeCommand(cmd);

    }

    static
    uint32_t ClientTextureGetDepthOrArrayLayers(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetDepthOrArrayLayers();
    }

    static
    WGPUTextureDimension ClientTextureGetDimension(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetDimension();
    }

    static
    WGPUTextureFormat ClientTextureGetFormat(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetFormat();
    }

    static
    uint32_t ClientTextureGetHeight(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetHeight();
    }

    static
    uint32_t ClientTextureGetMipLevelCount(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetMipLevelCount();
    }

    static
    uint32_t ClientTextureGetSampleCount(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetSampleCount();
    }

    static
    WGPUTextureUsageFlags ClientTextureGetUsage(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetUsage();
    }

    static
    uint32_t ClientTextureGetWidth(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        return self->GetWidth();
    }

    void ClientTextureSetLabel(WGPUTexture cSelf, char const * label) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        TextureSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientTextureRelease(WGPUTexture cObj) {
        Texture* obj = reinterpret_cast<Texture*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Texture;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientTextureReference(WGPUTexture cObj) {
        reinterpret_cast<Texture*>(cObj)->Reference();
    }


    void ClientTextureViewSetLabel(WGPUTextureView cSelf, char const * label) {
        auto self = reinterpret_cast<TextureView*>(cSelf);
        TextureViewSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->GetClient()->SerializeCommand(cmd);

    }

    void ClientTextureViewRelease(WGPUTextureView cObj) {
        TextureView* obj = reinterpret_cast<TextureView*>(cObj);

        if (!obj->Release()) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::TextureView;
        cmd.objectId = obj->GetWireId();

        Client* client = obj->GetClient();
        client->SerializeCommand(cmd);
        client->Free(obj);
    }

    void ClientTextureViewReference(WGPUTextureView cObj) {
        reinterpret_cast<TextureView*>(cObj)->Reference();
    }

    namespace {
        WGPUInstance ClientCreateInstance(WGPUInstanceDescriptor const* descriptor) {
            UNREACHABLE();
            return nullptr;
        }

        struct ProcEntry {
            WGPUProc proc;
            const char* name;
        };
        static const ProcEntry sProcMap[] = {
            { reinterpret_cast<WGPUProc>(ClientAdapterCreateDevice), "wgpuAdapterCreateDevice" },
            { reinterpret_cast<WGPUProc>(ClientAdapterEnumerateFeatures), "wgpuAdapterEnumerateFeatures" },
            { reinterpret_cast<WGPUProc>(ClientAdapterGetInstance), "wgpuAdapterGetInstance" },
            { reinterpret_cast<WGPUProc>(ClientAdapterGetLimits), "wgpuAdapterGetLimits" },
            { reinterpret_cast<WGPUProc>(ClientAdapterGetProperties), "wgpuAdapterGetProperties" },
            { reinterpret_cast<WGPUProc>(ClientAdapterHasFeature), "wgpuAdapterHasFeature" },
            { reinterpret_cast<WGPUProc>(ClientAdapterReference), "wgpuAdapterReference" },
            { reinterpret_cast<WGPUProc>(ClientAdapterRelease), "wgpuAdapterRelease" },
            { reinterpret_cast<WGPUProc>(ClientAdapterRequestDevice), "wgpuAdapterRequestDevice" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupLayoutReference), "wgpuBindGroupLayoutReference" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupLayoutRelease), "wgpuBindGroupLayoutRelease" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupLayoutSetLabel), "wgpuBindGroupLayoutSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupReference), "wgpuBindGroupReference" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupRelease), "wgpuBindGroupRelease" },
            { reinterpret_cast<WGPUProc>(ClientBindGroupSetLabel), "wgpuBindGroupSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientBufferDestroy), "wgpuBufferDestroy" },
            { reinterpret_cast<WGPUProc>(ClientBufferGetConstMappedRange), "wgpuBufferGetConstMappedRange" },
            { reinterpret_cast<WGPUProc>(ClientBufferGetMapState), "wgpuBufferGetMapState" },
            { reinterpret_cast<WGPUProc>(ClientBufferGetMappedRange), "wgpuBufferGetMappedRange" },
            { reinterpret_cast<WGPUProc>(ClientBufferGetSize), "wgpuBufferGetSize" },
            { reinterpret_cast<WGPUProc>(ClientBufferGetUsage), "wgpuBufferGetUsage" },
            { reinterpret_cast<WGPUProc>(ClientBufferMapAsync), "wgpuBufferMapAsync" },
            { reinterpret_cast<WGPUProc>(ClientBufferReference), "wgpuBufferReference" },
            { reinterpret_cast<WGPUProc>(ClientBufferRelease), "wgpuBufferRelease" },
            { reinterpret_cast<WGPUProc>(ClientBufferSetLabel), "wgpuBufferSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientBufferUnmap), "wgpuBufferUnmap" },
            { reinterpret_cast<WGPUProc>(ClientCommandBufferReference), "wgpuCommandBufferReference" },
            { reinterpret_cast<WGPUProc>(ClientCommandBufferRelease), "wgpuCommandBufferRelease" },
            { reinterpret_cast<WGPUProc>(ClientCommandBufferSetLabel), "wgpuCommandBufferSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderBeginComputePass), "wgpuCommandEncoderBeginComputePass" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderBeginRenderPass), "wgpuCommandEncoderBeginRenderPass" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderClearBuffer), "wgpuCommandEncoderClearBuffer" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyBufferToBuffer), "wgpuCommandEncoderCopyBufferToBuffer" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyBufferToTexture), "wgpuCommandEncoderCopyBufferToTexture" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyTextureToBuffer), "wgpuCommandEncoderCopyTextureToBuffer" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyTextureToTexture), "wgpuCommandEncoderCopyTextureToTexture" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderFinish), "wgpuCommandEncoderFinish" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderInjectValidationError), "wgpuCommandEncoderInjectValidationError" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderInsertDebugMarker), "wgpuCommandEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderPopDebugGroup), "wgpuCommandEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderPushDebugGroup), "wgpuCommandEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderReference), "wgpuCommandEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderRelease), "wgpuCommandEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderResolveQuerySet), "wgpuCommandEncoderResolveQuerySet" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderSetLabel), "wgpuCommandEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderWriteBuffer), "wgpuCommandEncoderWriteBuffer" },
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderWriteTimestamp), "wgpuCommandEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderDispatchWorkgroups), "wgpuComputePassEncoderDispatchWorkgroups" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderDispatchWorkgroupsIndirect), "wgpuComputePassEncoderDispatchWorkgroupsIndirect" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderEnd), "wgpuComputePassEncoderEnd" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderInsertDebugMarker), "wgpuComputePassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderPopDebugGroup), "wgpuComputePassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderPushDebugGroup), "wgpuComputePassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderReference), "wgpuComputePassEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderRelease), "wgpuComputePassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderSetBindGroup), "wgpuComputePassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderSetLabel), "wgpuComputePassEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderSetPipeline), "wgpuComputePassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderWriteTimestamp), "wgpuComputePassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(ClientComputePipelineGetBindGroupLayout), "wgpuComputePipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(ClientComputePipelineReference), "wgpuComputePipelineReference" },
            { reinterpret_cast<WGPUProc>(ClientComputePipelineRelease), "wgpuComputePipelineRelease" },
            { reinterpret_cast<WGPUProc>(ClientComputePipelineSetLabel), "wgpuComputePipelineSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateBindGroup), "wgpuDeviceCreateBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateBindGroupLayout), "wgpuDeviceCreateBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateBuffer), "wgpuDeviceCreateBuffer" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateCommandEncoder), "wgpuDeviceCreateCommandEncoder" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateComputePipeline), "wgpuDeviceCreateComputePipeline" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateComputePipelineAsync), "wgpuDeviceCreateComputePipelineAsync" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateErrorBuffer), "wgpuDeviceCreateErrorBuffer" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateErrorExternalTexture), "wgpuDeviceCreateErrorExternalTexture" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateErrorShaderModule), "wgpuDeviceCreateErrorShaderModule" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateErrorTexture), "wgpuDeviceCreateErrorTexture" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateExternalTexture), "wgpuDeviceCreateExternalTexture" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreatePipelineLayout), "wgpuDeviceCreatePipelineLayout" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateQuerySet), "wgpuDeviceCreateQuerySet" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateRenderBundleEncoder), "wgpuDeviceCreateRenderBundleEncoder" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateRenderPipeline), "wgpuDeviceCreateRenderPipeline" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateRenderPipelineAsync), "wgpuDeviceCreateRenderPipelineAsync" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateSampler), "wgpuDeviceCreateSampler" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateShaderModule), "wgpuDeviceCreateShaderModule" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateSwapChain), "wgpuDeviceCreateSwapChain" },
            { reinterpret_cast<WGPUProc>(ClientDeviceCreateTexture), "wgpuDeviceCreateTexture" },
            { reinterpret_cast<WGPUProc>(ClientDeviceDestroy), "wgpuDeviceDestroy" },
            { reinterpret_cast<WGPUProc>(ClientDeviceEnumerateFeatures), "wgpuDeviceEnumerateFeatures" },
            { reinterpret_cast<WGPUProc>(ClientDeviceForceLoss), "wgpuDeviceForceLoss" },
            { reinterpret_cast<WGPUProc>(ClientDeviceGetLimits), "wgpuDeviceGetLimits" },
            { reinterpret_cast<WGPUProc>(ClientDeviceGetQueue), "wgpuDeviceGetQueue" },
            { reinterpret_cast<WGPUProc>(ClientDeviceHasFeature), "wgpuDeviceHasFeature" },
            { reinterpret_cast<WGPUProc>(ClientDeviceInjectError), "wgpuDeviceInjectError" },
            { reinterpret_cast<WGPUProc>(ClientDevicePopErrorScope), "wgpuDevicePopErrorScope" },
            { reinterpret_cast<WGPUProc>(ClientDevicePushErrorScope), "wgpuDevicePushErrorScope" },
            { reinterpret_cast<WGPUProc>(ClientDeviceReference), "wgpuDeviceReference" },
            { reinterpret_cast<WGPUProc>(ClientDeviceRelease), "wgpuDeviceRelease" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetDeviceLostCallback), "wgpuDeviceSetDeviceLostCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetLabel), "wgpuDeviceSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetLoggingCallback), "wgpuDeviceSetLoggingCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetUncapturedErrorCallback), "wgpuDeviceSetUncapturedErrorCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceTick), "wgpuDeviceTick" },
            { reinterpret_cast<WGPUProc>(ClientDeviceValidateTextureDescriptor), "wgpuDeviceValidateTextureDescriptor" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureDestroy), "wgpuExternalTextureDestroy" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureExpire), "wgpuExternalTextureExpire" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureReference), "wgpuExternalTextureReference" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureRefresh), "wgpuExternalTextureRefresh" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureRelease), "wgpuExternalTextureRelease" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureSetLabel), "wgpuExternalTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientInstanceCreateSurface), "wgpuInstanceCreateSurface" },
            { reinterpret_cast<WGPUProc>(ClientInstanceProcessEvents), "wgpuInstanceProcessEvents" },
            { reinterpret_cast<WGPUProc>(ClientInstanceReference), "wgpuInstanceReference" },
            { reinterpret_cast<WGPUProc>(ClientInstanceRelease), "wgpuInstanceRelease" },
            { reinterpret_cast<WGPUProc>(ClientInstanceRequestAdapter), "wgpuInstanceRequestAdapter" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutReference), "wgpuPipelineLayoutReference" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutRelease), "wgpuPipelineLayoutRelease" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutSetLabel), "wgpuPipelineLayoutSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetDestroy), "wgpuQuerySetDestroy" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetGetCount), "wgpuQuerySetGetCount" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetGetType), "wgpuQuerySetGetType" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetReference), "wgpuQuerySetReference" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetRelease), "wgpuQuerySetRelease" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetSetLabel), "wgpuQuerySetSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientQueueCopyExternalTextureForBrowser), "wgpuQueueCopyExternalTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(ClientQueueCopyTextureForBrowser), "wgpuQueueCopyTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(ClientQueueOnSubmittedWorkDone), "wgpuQueueOnSubmittedWorkDone" },
            { reinterpret_cast<WGPUProc>(ClientQueueReference), "wgpuQueueReference" },
            { reinterpret_cast<WGPUProc>(ClientQueueRelease), "wgpuQueueRelease" },
            { reinterpret_cast<WGPUProc>(ClientQueueSetLabel), "wgpuQueueSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientQueueSubmit), "wgpuQueueSubmit" },
            { reinterpret_cast<WGPUProc>(ClientQueueWriteBuffer), "wgpuQueueWriteBuffer" },
            { reinterpret_cast<WGPUProc>(ClientQueueWriteTexture), "wgpuQueueWriteTexture" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDraw), "wgpuRenderBundleEncoderDraw" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDrawIndexed), "wgpuRenderBundleEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDrawIndexedIndirect), "wgpuRenderBundleEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderDrawIndirect), "wgpuRenderBundleEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderFinish), "wgpuRenderBundleEncoderFinish" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderInsertDebugMarker), "wgpuRenderBundleEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderPopDebugGroup), "wgpuRenderBundleEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderPushDebugGroup), "wgpuRenderBundleEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderReference), "wgpuRenderBundleEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderRelease), "wgpuRenderBundleEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetBindGroup), "wgpuRenderBundleEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetIndexBuffer), "wgpuRenderBundleEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetLabel), "wgpuRenderBundleEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetPipeline), "wgpuRenderBundleEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleEncoderSetVertexBuffer), "wgpuRenderBundleEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleReference), "wgpuRenderBundleReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleRelease), "wgpuRenderBundleRelease" },
            { reinterpret_cast<WGPUProc>(ClientRenderBundleSetLabel), "wgpuRenderBundleSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderBeginOcclusionQuery), "wgpuRenderPassEncoderBeginOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDraw), "wgpuRenderPassEncoderDraw" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndexed), "wgpuRenderPassEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndexedIndirect), "wgpuRenderPassEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndirect), "wgpuRenderPassEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderEnd), "wgpuRenderPassEncoderEnd" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderEndOcclusionQuery), "wgpuRenderPassEncoderEndOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderExecuteBundles), "wgpuRenderPassEncoderExecuteBundles" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderInsertDebugMarker), "wgpuRenderPassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderPopDebugGroup), "wgpuRenderPassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderPushDebugGroup), "wgpuRenderPassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderReference), "wgpuRenderPassEncoderReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderRelease), "wgpuRenderPassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetBindGroup), "wgpuRenderPassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetBlendConstant), "wgpuRenderPassEncoderSetBlendConstant" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetIndexBuffer), "wgpuRenderPassEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetLabel), "wgpuRenderPassEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetPipeline), "wgpuRenderPassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetScissorRect), "wgpuRenderPassEncoderSetScissorRect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetStencilReference), "wgpuRenderPassEncoderSetStencilReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetVertexBuffer), "wgpuRenderPassEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderSetViewport), "wgpuRenderPassEncoderSetViewport" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderWriteTimestamp), "wgpuRenderPassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(ClientRenderPipelineGetBindGroupLayout), "wgpuRenderPipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(ClientRenderPipelineReference), "wgpuRenderPipelineReference" },
            { reinterpret_cast<WGPUProc>(ClientRenderPipelineRelease), "wgpuRenderPipelineRelease" },
            { reinterpret_cast<WGPUProc>(ClientRenderPipelineSetLabel), "wgpuRenderPipelineSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientSamplerReference), "wgpuSamplerReference" },
            { reinterpret_cast<WGPUProc>(ClientSamplerRelease), "wgpuSamplerRelease" },
            { reinterpret_cast<WGPUProc>(ClientSamplerSetLabel), "wgpuSamplerSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientShaderModuleGetCompilationInfo), "wgpuShaderModuleGetCompilationInfo" },
            { reinterpret_cast<WGPUProc>(ClientShaderModuleReference), "wgpuShaderModuleReference" },
            { reinterpret_cast<WGPUProc>(ClientShaderModuleRelease), "wgpuShaderModuleRelease" },
            { reinterpret_cast<WGPUProc>(ClientShaderModuleSetLabel), "wgpuShaderModuleSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientSurfaceReference), "wgpuSurfaceReference" },
            { reinterpret_cast<WGPUProc>(ClientSurfaceRelease), "wgpuSurfaceRelease" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainGetCurrentTexture), "wgpuSwapChainGetCurrentTexture" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainGetCurrentTextureView), "wgpuSwapChainGetCurrentTextureView" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainPresent), "wgpuSwapChainPresent" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainReference), "wgpuSwapChainReference" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainRelease), "wgpuSwapChainRelease" },
            { reinterpret_cast<WGPUProc>(ClientTextureCreateView), "wgpuTextureCreateView" },
            { reinterpret_cast<WGPUProc>(ClientTextureDestroy), "wgpuTextureDestroy" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetDepthOrArrayLayers), "wgpuTextureGetDepthOrArrayLayers" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetDimension), "wgpuTextureGetDimension" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetFormat), "wgpuTextureGetFormat" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetHeight), "wgpuTextureGetHeight" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetMipLevelCount), "wgpuTextureGetMipLevelCount" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetSampleCount), "wgpuTextureGetSampleCount" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetUsage), "wgpuTextureGetUsage" },
            { reinterpret_cast<WGPUProc>(ClientTextureGetWidth), "wgpuTextureGetWidth" },
            { reinterpret_cast<WGPUProc>(ClientTextureReference), "wgpuTextureReference" },
            { reinterpret_cast<WGPUProc>(ClientTextureRelease), "wgpuTextureRelease" },
            { reinterpret_cast<WGPUProc>(ClientTextureSetLabel), "wgpuTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientTextureViewReference), "wgpuTextureViewReference" },
            { reinterpret_cast<WGPUProc>(ClientTextureViewRelease), "wgpuTextureViewRelease" },
            { reinterpret_cast<WGPUProc>(ClientTextureViewSetLabel), "wgpuTextureViewSetLabel" },
        };
        static constexpr size_t sProcMapSize = sizeof(sProcMap) / sizeof(sProcMap[0]);
    }  // anonymous namespace

    WGPUProc ClientGetProcAddress(WGPUDevice, const char* procName) {
        if (procName == nullptr) {
            return nullptr;
        }

        const ProcEntry* entry = std::lower_bound(&sProcMap[0], &sProcMap[sProcMapSize], procName,
            [](const ProcEntry &a, const char *b) -> bool {
                return strcmp(a.name, b) < 0;
            }
        );

        if (entry != &sProcMap[sProcMapSize] && strcmp(entry->name, procName) == 0) {
            return entry->proc;
        }

        // Special case the two free-standing functions of the API.
        if (strcmp(procName, "wgpuGetProcAddress") == 0) {
            return reinterpret_cast<WGPUProc>(ClientGetProcAddress);
        }

        if (strcmp(procName, "wgpuCreateInstance") == 0) {
            return reinterpret_cast<WGPUProc>(ClientCreateInstance);
        }

        return nullptr;
    }

    std::vector<const char*> GetProcMapNamesForTesting() {
        std::vector<const char*> result;
        result.reserve(sProcMapSize);
        for (const ProcEntry& entry : sProcMap) {
            result.push_back(entry.name);
        }
        return result;
    }


    template <typename... MemberPtrPairs>
    constexpr DawnProcTable MakeProcTable(int, MemberPtrPairs... pairs) {
        DawnProcTable procs = {};
        ([&](auto& pair){
            procs.*(pair.first) = pair.second;
        }(pairs), ...);
        return procs;
    }

    static DawnProcTable gProcTable = MakeProcTable(
        /* unused */ 0
        , std::make_pair(&DawnProcTable::adapterPropertiesFreeMembers, ClientAdapterPropertiesFreeMembers)
        , std::make_pair(&DawnProcTable::createInstance, ClientCreateInstance)
        , std::make_pair(&DawnProcTable::getProcAddress, ClientGetProcAddress)
        , std::make_pair(&DawnProcTable::adapterCreateDevice, ClientAdapterCreateDevice)
        , std::make_pair(&DawnProcTable::adapterEnumerateFeatures, ClientAdapterEnumerateFeatures)
        , std::make_pair(&DawnProcTable::adapterGetInstance, ClientAdapterGetInstance)
        , std::make_pair(&DawnProcTable::adapterGetLimits, ClientAdapterGetLimits)
        , std::make_pair(&DawnProcTable::adapterGetProperties, ClientAdapterGetProperties)
        , std::make_pair(&DawnProcTable::adapterHasFeature, ClientAdapterHasFeature)
        , std::make_pair(&DawnProcTable::adapterRequestDevice, ClientAdapterRequestDevice)
        , std::make_pair(&DawnProcTable::adapterReference, ClientAdapterReference)
        , std::make_pair(&DawnProcTable::adapterRelease, ClientAdapterRelease)
        , std::make_pair(&DawnProcTable::bindGroupSetLabel, ClientBindGroupSetLabel)
        , std::make_pair(&DawnProcTable::bindGroupReference, ClientBindGroupReference)
        , std::make_pair(&DawnProcTable::bindGroupRelease, ClientBindGroupRelease)
        , std::make_pair(&DawnProcTable::bindGroupLayoutSetLabel, ClientBindGroupLayoutSetLabel)
        , std::make_pair(&DawnProcTable::bindGroupLayoutReference, ClientBindGroupLayoutReference)
        , std::make_pair(&DawnProcTable::bindGroupLayoutRelease, ClientBindGroupLayoutRelease)
        , std::make_pair(&DawnProcTable::bufferDestroy, ClientBufferDestroy)
        , std::make_pair(&DawnProcTable::bufferGetConstMappedRange, ClientBufferGetConstMappedRange)
        , std::make_pair(&DawnProcTable::bufferGetMapState, ClientBufferGetMapState)
        , std::make_pair(&DawnProcTable::bufferGetMappedRange, ClientBufferGetMappedRange)
        , std::make_pair(&DawnProcTable::bufferGetSize, ClientBufferGetSize)
        , std::make_pair(&DawnProcTable::bufferGetUsage, ClientBufferGetUsage)
        , std::make_pair(&DawnProcTable::bufferMapAsync, ClientBufferMapAsync)
        , std::make_pair(&DawnProcTable::bufferSetLabel, ClientBufferSetLabel)
        , std::make_pair(&DawnProcTable::bufferUnmap, ClientBufferUnmap)
        , std::make_pair(&DawnProcTable::bufferReference, ClientBufferReference)
        , std::make_pair(&DawnProcTable::bufferRelease, ClientBufferRelease)
        , std::make_pair(&DawnProcTable::commandBufferSetLabel, ClientCommandBufferSetLabel)
        , std::make_pair(&DawnProcTable::commandBufferReference, ClientCommandBufferReference)
        , std::make_pair(&DawnProcTable::commandBufferRelease, ClientCommandBufferRelease)
        , std::make_pair(&DawnProcTable::commandEncoderBeginComputePass, ClientCommandEncoderBeginComputePass)
        , std::make_pair(&DawnProcTable::commandEncoderBeginRenderPass, ClientCommandEncoderBeginRenderPass)
        , std::make_pair(&DawnProcTable::commandEncoderClearBuffer, ClientCommandEncoderClearBuffer)
        , std::make_pair(&DawnProcTable::commandEncoderCopyBufferToBuffer, ClientCommandEncoderCopyBufferToBuffer)
        , std::make_pair(&DawnProcTable::commandEncoderCopyBufferToTexture, ClientCommandEncoderCopyBufferToTexture)
        , std::make_pair(&DawnProcTable::commandEncoderCopyTextureToBuffer, ClientCommandEncoderCopyTextureToBuffer)
        , std::make_pair(&DawnProcTable::commandEncoderCopyTextureToTexture, ClientCommandEncoderCopyTextureToTexture)
        , std::make_pair(&DawnProcTable::commandEncoderFinish, ClientCommandEncoderFinish)
        , std::make_pair(&DawnProcTable::commandEncoderInjectValidationError, ClientCommandEncoderInjectValidationError)
        , std::make_pair(&DawnProcTable::commandEncoderInsertDebugMarker, ClientCommandEncoderInsertDebugMarker)
        , std::make_pair(&DawnProcTable::commandEncoderPopDebugGroup, ClientCommandEncoderPopDebugGroup)
        , std::make_pair(&DawnProcTable::commandEncoderPushDebugGroup, ClientCommandEncoderPushDebugGroup)
        , std::make_pair(&DawnProcTable::commandEncoderResolveQuerySet, ClientCommandEncoderResolveQuerySet)
        , std::make_pair(&DawnProcTable::commandEncoderSetLabel, ClientCommandEncoderSetLabel)
        , std::make_pair(&DawnProcTable::commandEncoderWriteBuffer, ClientCommandEncoderWriteBuffer)
        , std::make_pair(&DawnProcTable::commandEncoderWriteTimestamp, ClientCommandEncoderWriteTimestamp)
        , std::make_pair(&DawnProcTable::commandEncoderReference, ClientCommandEncoderReference)
        , std::make_pair(&DawnProcTable::commandEncoderRelease, ClientCommandEncoderRelease)
        , std::make_pair(&DawnProcTable::computePassEncoderDispatchWorkgroups, ClientComputePassEncoderDispatchWorkgroups)
        , std::make_pair(&DawnProcTable::computePassEncoderDispatchWorkgroupsIndirect, ClientComputePassEncoderDispatchWorkgroupsIndirect)
        , std::make_pair(&DawnProcTable::computePassEncoderEnd, ClientComputePassEncoderEnd)
        , std::make_pair(&DawnProcTable::computePassEncoderInsertDebugMarker, ClientComputePassEncoderInsertDebugMarker)
        , std::make_pair(&DawnProcTable::computePassEncoderPopDebugGroup, ClientComputePassEncoderPopDebugGroup)
        , std::make_pair(&DawnProcTable::computePassEncoderPushDebugGroup, ClientComputePassEncoderPushDebugGroup)
        , std::make_pair(&DawnProcTable::computePassEncoderSetBindGroup, ClientComputePassEncoderSetBindGroup)
        , std::make_pair(&DawnProcTable::computePassEncoderSetLabel, ClientComputePassEncoderSetLabel)
        , std::make_pair(&DawnProcTable::computePassEncoderSetPipeline, ClientComputePassEncoderSetPipeline)
        , std::make_pair(&DawnProcTable::computePassEncoderWriteTimestamp, ClientComputePassEncoderWriteTimestamp)
        , std::make_pair(&DawnProcTable::computePassEncoderReference, ClientComputePassEncoderReference)
        , std::make_pair(&DawnProcTable::computePassEncoderRelease, ClientComputePassEncoderRelease)
        , std::make_pair(&DawnProcTable::computePipelineGetBindGroupLayout, ClientComputePipelineGetBindGroupLayout)
        , std::make_pair(&DawnProcTable::computePipelineSetLabel, ClientComputePipelineSetLabel)
        , std::make_pair(&DawnProcTable::computePipelineReference, ClientComputePipelineReference)
        , std::make_pair(&DawnProcTable::computePipelineRelease, ClientComputePipelineRelease)
        , std::make_pair(&DawnProcTable::deviceCreateBindGroup, ClientDeviceCreateBindGroup)
        , std::make_pair(&DawnProcTable::deviceCreateBindGroupLayout, ClientDeviceCreateBindGroupLayout)
        , std::make_pair(&DawnProcTable::deviceCreateBuffer, ClientDeviceCreateBuffer)
        , std::make_pair(&DawnProcTable::deviceCreateCommandEncoder, ClientDeviceCreateCommandEncoder)
        , std::make_pair(&DawnProcTable::deviceCreateComputePipeline, ClientDeviceCreateComputePipeline)
        , std::make_pair(&DawnProcTable::deviceCreateComputePipelineAsync, ClientDeviceCreateComputePipelineAsync)
        , std::make_pair(&DawnProcTable::deviceCreateErrorBuffer, ClientDeviceCreateErrorBuffer)
        , std::make_pair(&DawnProcTable::deviceCreateErrorExternalTexture, ClientDeviceCreateErrorExternalTexture)
        , std::make_pair(&DawnProcTable::deviceCreateErrorShaderModule, ClientDeviceCreateErrorShaderModule)
        , std::make_pair(&DawnProcTable::deviceCreateErrorTexture, ClientDeviceCreateErrorTexture)
        , std::make_pair(&DawnProcTable::deviceCreateExternalTexture, ClientDeviceCreateExternalTexture)
        , std::make_pair(&DawnProcTable::deviceCreatePipelineLayout, ClientDeviceCreatePipelineLayout)
        , std::make_pair(&DawnProcTable::deviceCreateQuerySet, ClientDeviceCreateQuerySet)
        , std::make_pair(&DawnProcTable::deviceCreateRenderBundleEncoder, ClientDeviceCreateRenderBundleEncoder)
        , std::make_pair(&DawnProcTable::deviceCreateRenderPipeline, ClientDeviceCreateRenderPipeline)
        , std::make_pair(&DawnProcTable::deviceCreateRenderPipelineAsync, ClientDeviceCreateRenderPipelineAsync)
        , std::make_pair(&DawnProcTable::deviceCreateSampler, ClientDeviceCreateSampler)
        , std::make_pair(&DawnProcTable::deviceCreateShaderModule, ClientDeviceCreateShaderModule)
        , std::make_pair(&DawnProcTable::deviceCreateSwapChain, ClientDeviceCreateSwapChain)
        , std::make_pair(&DawnProcTable::deviceCreateTexture, ClientDeviceCreateTexture)
        , std::make_pair(&DawnProcTable::deviceDestroy, ClientDeviceDestroy)
        , std::make_pair(&DawnProcTable::deviceEnumerateFeatures, ClientDeviceEnumerateFeatures)
        , std::make_pair(&DawnProcTable::deviceForceLoss, ClientDeviceForceLoss)
        , std::make_pair(&DawnProcTable::deviceGetLimits, ClientDeviceGetLimits)
        , std::make_pair(&DawnProcTable::deviceGetQueue, ClientDeviceGetQueue)
        , std::make_pair(&DawnProcTable::deviceHasFeature, ClientDeviceHasFeature)
        , std::make_pair(&DawnProcTable::deviceInjectError, ClientDeviceInjectError)
        , std::make_pair(&DawnProcTable::devicePopErrorScope, ClientDevicePopErrorScope)
        , std::make_pair(&DawnProcTable::devicePushErrorScope, ClientDevicePushErrorScope)
        , std::make_pair(&DawnProcTable::deviceSetDeviceLostCallback, ClientDeviceSetDeviceLostCallback)
        , std::make_pair(&DawnProcTable::deviceSetLabel, ClientDeviceSetLabel)
        , std::make_pair(&DawnProcTable::deviceSetLoggingCallback, ClientDeviceSetLoggingCallback)
        , std::make_pair(&DawnProcTable::deviceSetUncapturedErrorCallback, ClientDeviceSetUncapturedErrorCallback)
        , std::make_pair(&DawnProcTable::deviceTick, ClientDeviceTick)
        , std::make_pair(&DawnProcTable::deviceValidateTextureDescriptor, ClientDeviceValidateTextureDescriptor)
        , std::make_pair(&DawnProcTable::deviceReference, ClientDeviceReference)
        , std::make_pair(&DawnProcTable::deviceRelease, ClientDeviceRelease)
        , std::make_pair(&DawnProcTable::externalTextureDestroy, ClientExternalTextureDestroy)
        , std::make_pair(&DawnProcTable::externalTextureExpire, ClientExternalTextureExpire)
        , std::make_pair(&DawnProcTable::externalTextureRefresh, ClientExternalTextureRefresh)
        , std::make_pair(&DawnProcTable::externalTextureSetLabel, ClientExternalTextureSetLabel)
        , std::make_pair(&DawnProcTable::externalTextureReference, ClientExternalTextureReference)
        , std::make_pair(&DawnProcTable::externalTextureRelease, ClientExternalTextureRelease)
        , std::make_pair(&DawnProcTable::instanceCreateSurface, ClientInstanceCreateSurface)
        , std::make_pair(&DawnProcTable::instanceProcessEvents, ClientInstanceProcessEvents)
        , std::make_pair(&DawnProcTable::instanceRequestAdapter, ClientInstanceRequestAdapter)
        , std::make_pair(&DawnProcTable::instanceReference, ClientInstanceReference)
        , std::make_pair(&DawnProcTable::instanceRelease, ClientInstanceRelease)
        , std::make_pair(&DawnProcTable::pipelineLayoutSetLabel, ClientPipelineLayoutSetLabel)
        , std::make_pair(&DawnProcTable::pipelineLayoutReference, ClientPipelineLayoutReference)
        , std::make_pair(&DawnProcTable::pipelineLayoutRelease, ClientPipelineLayoutRelease)
        , std::make_pair(&DawnProcTable::querySetDestroy, ClientQuerySetDestroy)
        , std::make_pair(&DawnProcTable::querySetGetCount, ClientQuerySetGetCount)
        , std::make_pair(&DawnProcTable::querySetGetType, ClientQuerySetGetType)
        , std::make_pair(&DawnProcTable::querySetSetLabel, ClientQuerySetSetLabel)
        , std::make_pair(&DawnProcTable::querySetReference, ClientQuerySetReference)
        , std::make_pair(&DawnProcTable::querySetRelease, ClientQuerySetRelease)
        , std::make_pair(&DawnProcTable::queueCopyExternalTextureForBrowser, ClientQueueCopyExternalTextureForBrowser)
        , std::make_pair(&DawnProcTable::queueCopyTextureForBrowser, ClientQueueCopyTextureForBrowser)
        , std::make_pair(&DawnProcTable::queueOnSubmittedWorkDone, ClientQueueOnSubmittedWorkDone)
        , std::make_pair(&DawnProcTable::queueSetLabel, ClientQueueSetLabel)
        , std::make_pair(&DawnProcTable::queueSubmit, ClientQueueSubmit)
        , std::make_pair(&DawnProcTable::queueWriteBuffer, ClientQueueWriteBuffer)
        , std::make_pair(&DawnProcTable::queueWriteTexture, ClientQueueWriteTexture)
        , std::make_pair(&DawnProcTable::queueReference, ClientQueueReference)
        , std::make_pair(&DawnProcTable::queueRelease, ClientQueueRelease)
        , std::make_pair(&DawnProcTable::renderBundleSetLabel, ClientRenderBundleSetLabel)
        , std::make_pair(&DawnProcTable::renderBundleReference, ClientRenderBundleReference)
        , std::make_pair(&DawnProcTable::renderBundleRelease, ClientRenderBundleRelease)
        , std::make_pair(&DawnProcTable::renderBundleEncoderDraw, ClientRenderBundleEncoderDraw)
        , std::make_pair(&DawnProcTable::renderBundleEncoderDrawIndexed, ClientRenderBundleEncoderDrawIndexed)
        , std::make_pair(&DawnProcTable::renderBundleEncoderDrawIndexedIndirect, ClientRenderBundleEncoderDrawIndexedIndirect)
        , std::make_pair(&DawnProcTable::renderBundleEncoderDrawIndirect, ClientRenderBundleEncoderDrawIndirect)
        , std::make_pair(&DawnProcTable::renderBundleEncoderFinish, ClientRenderBundleEncoderFinish)
        , std::make_pair(&DawnProcTable::renderBundleEncoderInsertDebugMarker, ClientRenderBundleEncoderInsertDebugMarker)
        , std::make_pair(&DawnProcTable::renderBundleEncoderPopDebugGroup, ClientRenderBundleEncoderPopDebugGroup)
        , std::make_pair(&DawnProcTable::renderBundleEncoderPushDebugGroup, ClientRenderBundleEncoderPushDebugGroup)
        , std::make_pair(&DawnProcTable::renderBundleEncoderSetBindGroup, ClientRenderBundleEncoderSetBindGroup)
        , std::make_pair(&DawnProcTable::renderBundleEncoderSetIndexBuffer, ClientRenderBundleEncoderSetIndexBuffer)
        , std::make_pair(&DawnProcTable::renderBundleEncoderSetLabel, ClientRenderBundleEncoderSetLabel)
        , std::make_pair(&DawnProcTable::renderBundleEncoderSetPipeline, ClientRenderBundleEncoderSetPipeline)
        , std::make_pair(&DawnProcTable::renderBundleEncoderSetVertexBuffer, ClientRenderBundleEncoderSetVertexBuffer)
        , std::make_pair(&DawnProcTable::renderBundleEncoderReference, ClientRenderBundleEncoderReference)
        , std::make_pair(&DawnProcTable::renderBundleEncoderRelease, ClientRenderBundleEncoderRelease)
        , std::make_pair(&DawnProcTable::renderPassEncoderBeginOcclusionQuery, ClientRenderPassEncoderBeginOcclusionQuery)
        , std::make_pair(&DawnProcTable::renderPassEncoderDraw, ClientRenderPassEncoderDraw)
        , std::make_pair(&DawnProcTable::renderPassEncoderDrawIndexed, ClientRenderPassEncoderDrawIndexed)
        , std::make_pair(&DawnProcTable::renderPassEncoderDrawIndexedIndirect, ClientRenderPassEncoderDrawIndexedIndirect)
        , std::make_pair(&DawnProcTable::renderPassEncoderDrawIndirect, ClientRenderPassEncoderDrawIndirect)
        , std::make_pair(&DawnProcTable::renderPassEncoderEnd, ClientRenderPassEncoderEnd)
        , std::make_pair(&DawnProcTable::renderPassEncoderEndOcclusionQuery, ClientRenderPassEncoderEndOcclusionQuery)
        , std::make_pair(&DawnProcTable::renderPassEncoderExecuteBundles, ClientRenderPassEncoderExecuteBundles)
        , std::make_pair(&DawnProcTable::renderPassEncoderInsertDebugMarker, ClientRenderPassEncoderInsertDebugMarker)
        , std::make_pair(&DawnProcTable::renderPassEncoderPopDebugGroup, ClientRenderPassEncoderPopDebugGroup)
        , std::make_pair(&DawnProcTable::renderPassEncoderPushDebugGroup, ClientRenderPassEncoderPushDebugGroup)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetBindGroup, ClientRenderPassEncoderSetBindGroup)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetBlendConstant, ClientRenderPassEncoderSetBlendConstant)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetIndexBuffer, ClientRenderPassEncoderSetIndexBuffer)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetLabel, ClientRenderPassEncoderSetLabel)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetPipeline, ClientRenderPassEncoderSetPipeline)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetScissorRect, ClientRenderPassEncoderSetScissorRect)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetStencilReference, ClientRenderPassEncoderSetStencilReference)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetVertexBuffer, ClientRenderPassEncoderSetVertexBuffer)
        , std::make_pair(&DawnProcTable::renderPassEncoderSetViewport, ClientRenderPassEncoderSetViewport)
        , std::make_pair(&DawnProcTable::renderPassEncoderWriteTimestamp, ClientRenderPassEncoderWriteTimestamp)
        , std::make_pair(&DawnProcTable::renderPassEncoderReference, ClientRenderPassEncoderReference)
        , std::make_pair(&DawnProcTable::renderPassEncoderRelease, ClientRenderPassEncoderRelease)
        , std::make_pair(&DawnProcTable::renderPipelineGetBindGroupLayout, ClientRenderPipelineGetBindGroupLayout)
        , std::make_pair(&DawnProcTable::renderPipelineSetLabel, ClientRenderPipelineSetLabel)
        , std::make_pair(&DawnProcTable::renderPipelineReference, ClientRenderPipelineReference)
        , std::make_pair(&DawnProcTable::renderPipelineRelease, ClientRenderPipelineRelease)
        , std::make_pair(&DawnProcTable::samplerSetLabel, ClientSamplerSetLabel)
        , std::make_pair(&DawnProcTable::samplerReference, ClientSamplerReference)
        , std::make_pair(&DawnProcTable::samplerRelease, ClientSamplerRelease)
        , std::make_pair(&DawnProcTable::shaderModuleGetCompilationInfo, ClientShaderModuleGetCompilationInfo)
        , std::make_pair(&DawnProcTable::shaderModuleSetLabel, ClientShaderModuleSetLabel)
        , std::make_pair(&DawnProcTable::shaderModuleReference, ClientShaderModuleReference)
        , std::make_pair(&DawnProcTable::shaderModuleRelease, ClientShaderModuleRelease)
        , std::make_pair(&DawnProcTable::surfaceReference, ClientSurfaceReference)
        , std::make_pair(&DawnProcTable::surfaceRelease, ClientSurfaceRelease)
        , std::make_pair(&DawnProcTable::swapChainGetCurrentTexture, ClientSwapChainGetCurrentTexture)
        , std::make_pair(&DawnProcTable::swapChainGetCurrentTextureView, ClientSwapChainGetCurrentTextureView)
        , std::make_pair(&DawnProcTable::swapChainPresent, ClientSwapChainPresent)
        , std::make_pair(&DawnProcTable::swapChainReference, ClientSwapChainReference)
        , std::make_pair(&DawnProcTable::swapChainRelease, ClientSwapChainRelease)
        , std::make_pair(&DawnProcTable::textureCreateView, ClientTextureCreateView)
        , std::make_pair(&DawnProcTable::textureDestroy, ClientTextureDestroy)
        , std::make_pair(&DawnProcTable::textureGetDepthOrArrayLayers, ClientTextureGetDepthOrArrayLayers)
        , std::make_pair(&DawnProcTable::textureGetDimension, ClientTextureGetDimension)
        , std::make_pair(&DawnProcTable::textureGetFormat, ClientTextureGetFormat)
        , std::make_pair(&DawnProcTable::textureGetHeight, ClientTextureGetHeight)
        , std::make_pair(&DawnProcTable::textureGetMipLevelCount, ClientTextureGetMipLevelCount)
        , std::make_pair(&DawnProcTable::textureGetSampleCount, ClientTextureGetSampleCount)
        , std::make_pair(&DawnProcTable::textureGetUsage, ClientTextureGetUsage)
        , std::make_pair(&DawnProcTable::textureGetWidth, ClientTextureGetWidth)
        , std::make_pair(&DawnProcTable::textureSetLabel, ClientTextureSetLabel)
        , std::make_pair(&DawnProcTable::textureReference, ClientTextureReference)
        , std::make_pair(&DawnProcTable::textureRelease, ClientTextureRelease)
        , std::make_pair(&DawnProcTable::textureViewSetLabel, ClientTextureViewSetLabel)
        , std::make_pair(&DawnProcTable::textureViewReference, ClientTextureViewReference)
        , std::make_pair(&DawnProcTable::textureViewRelease, ClientTextureViewRelease)
    );

    const DawnProcTable& GetProcs() {
        return gProcTable;
    }
}  // namespace dawn::wire::client
