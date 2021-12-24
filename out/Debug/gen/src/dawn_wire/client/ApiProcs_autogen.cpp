
#include "common/Log.h"
#include "dawn_wire/client/ApiObjects.h"
#include "dawn_wire/client/Client.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

namespace dawn_wire { namespace client {




    static
    WGPUDevice ClientAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->CreateDevice( descriptor);
    }

    static
    uint32_t ClientAdapterEnumerateFeatures(WGPUAdapter cSelf, WGPUFeatureName * features) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->EnumerateFeatures( features);
    }

    static
    bool ClientAdapterGetLimits(WGPUAdapter cSelf, WGPUSupportedLimits * limits) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->GetLimits( limits);
    }

    static
    void ClientAdapterGetProperties(WGPUAdapter cSelf, WGPUAdapterProperties * properties) {
        auto self = reinterpret_cast<Adapter*>(cSelf);
        return self->GetProperties( properties);
    }

    static
    bool ClientAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature) {
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
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Adapter;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->AdapterAllocator().Free(obj);
    }

    void ClientAdapterReference(WGPUAdapter cObj) {
        Adapter* obj = reinterpret_cast<Adapter*>(cObj);
        obj->refcount ++;
    }


    void ClientBindGroupSetLabel(WGPUBindGroup cSelf, char const * label) {
        auto self = reinterpret_cast<BindGroup*>(cSelf);
        BindGroupSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientBindGroupRelease(WGPUBindGroup cObj) {
        BindGroup* obj = reinterpret_cast<BindGroup*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::BindGroup;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->BindGroupAllocator().Free(obj);
    }

    void ClientBindGroupReference(WGPUBindGroup cObj) {
        BindGroup* obj = reinterpret_cast<BindGroup*>(cObj);
        obj->refcount ++;
    }


    void ClientBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, char const * label) {
        auto self = reinterpret_cast<BindGroupLayout*>(cSelf);
        BindGroupLayoutSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientBindGroupLayoutRelease(WGPUBindGroupLayout cObj) {
        BindGroupLayout* obj = reinterpret_cast<BindGroupLayout*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::BindGroupLayout;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->BindGroupLayoutAllocator().Free(obj);
    }

    void ClientBindGroupLayoutReference(WGPUBindGroupLayout cObj) {
        BindGroupLayout* obj = reinterpret_cast<BindGroupLayout*>(cObj);
        obj->refcount ++;
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
    void * ClientBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->GetMappedRange( offset,  size);
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

        self->client->SerializeCommand(cmd);

    }

    static
    void ClientBufferUnmap(WGPUBuffer cSelf) {
        auto self = reinterpret_cast<Buffer*>(cSelf);
        return self->Unmap();
    }

    void ClientBufferRelease(WGPUBuffer cObj) {
        Buffer* obj = reinterpret_cast<Buffer*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Buffer;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->BufferAllocator().Free(obj);
    }

    void ClientBufferReference(WGPUBuffer cObj) {
        Buffer* obj = reinterpret_cast<Buffer*>(cObj);
        obj->refcount ++;
    }


    void ClientCommandBufferSetLabel(WGPUCommandBuffer cSelf, char const * label) {
        auto self = reinterpret_cast<CommandBuffer*>(cSelf);
        CommandBufferSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandBufferRelease(WGPUCommandBuffer cObj) {
        CommandBuffer* obj = reinterpret_cast<CommandBuffer*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::CommandBuffer;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->CommandBufferAllocator().Free(obj);
    }

    void ClientCommandBufferReference(WGPUCommandBuffer cObj) {
        CommandBuffer* obj = reinterpret_cast<CommandBuffer*>(cObj);
        obj->refcount ++;
    }


    WGPUComputePassEncoder ClientCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderBeginComputePassCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->ComputePassEncoderAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUComputePassEncoder>(allocation->object.get());
    }

    WGPURenderPassEncoder ClientCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderBeginRenderPassCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->RenderPassEncoderAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderPassEncoder>(allocation->object.get());
    }

    void ClientCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderClearBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->client->SerializeCommand(cmd);

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

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyBufferToTextureCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyTextureToBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyTextureToTextureCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderCopyTextureToTextureInternal(WGPUCommandEncoder cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderCopyTextureToTextureInternalCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;

        self->client->SerializeCommand(cmd);

    }

    WGPUCommandBuffer ClientCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderFinishCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->CommandBufferAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUCommandBuffer>(allocation->object.get());
    }

    void ClientCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, char const * message) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderInjectValidationErrorCmd cmd;

        cmd.self = cSelf;


        
        cmd.message = message;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->client->SerializeCommand(cmd);

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

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderSetLabel(WGPUCommandEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderWriteBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.bufferOffset = bufferOffset;
        
        cmd.data = data;
        
        cmd.size = size;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = reinterpret_cast<CommandEncoder*>(cSelf);
        CommandEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        
        cmd.querySet = querySet;
        
        cmd.queryIndex = queryIndex;

        self->client->SerializeCommand(cmd);

    }

    void ClientCommandEncoderRelease(WGPUCommandEncoder cObj) {
        CommandEncoder* obj = reinterpret_cast<CommandEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::CommandEncoder;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->CommandEncoderAllocator().Free(obj);
    }

    void ClientCommandEncoderReference(WGPUCommandEncoder cObj) {
        CommandEncoder* obj = reinterpret_cast<CommandEncoder*>(cObj);
        obj->refcount ++;
    }


    void ClientComputePassEncoderDispatch(WGPUComputePassEncoder cSelf, uint32_t x, uint32_t y, uint32_t z) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderDispatchCmd cmd;

        cmd.self = cSelf;


        
        cmd.x = x;
        
        cmd.y = y;
        
        cmd.z = z;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderDispatchIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderDispatchIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderEndPass(WGPUComputePassEncoder cSelf) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderEndPassCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupIndex = groupIndex;
        
        cmd.group = group;
        
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        
        cmd.dynamicOffsets = dynamicOffsets;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        
        cmd.pipeline = pipeline;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = reinterpret_cast<ComputePassEncoder*>(cSelf);
        ComputePassEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        
        cmd.querySet = querySet;
        
        cmd.queryIndex = queryIndex;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePassEncoderRelease(WGPUComputePassEncoder cObj) {
        ComputePassEncoder* obj = reinterpret_cast<ComputePassEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ComputePassEncoder;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->ComputePassEncoderAllocator().Free(obj);
    }

    void ClientComputePassEncoderReference(WGPUComputePassEncoder cObj) {
        ComputePassEncoder* obj = reinterpret_cast<ComputePassEncoder*>(cObj);
        obj->refcount ++;
    }


    WGPUBindGroupLayout ClientComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
        auto self = reinterpret_cast<ComputePipeline*>(cSelf);
        ComputePipelineGetBindGroupLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->BindGroupLayoutAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.groupIndex = groupIndex;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
    }

    void ClientComputePipelineSetLabel(WGPUComputePipeline cSelf, char const * label) {
        auto self = reinterpret_cast<ComputePipeline*>(cSelf);
        ComputePipelineSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientComputePipelineRelease(WGPUComputePipeline cObj) {
        ComputePipeline* obj = reinterpret_cast<ComputePipeline*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ComputePipeline;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->ComputePipelineAllocator().Free(obj);
    }

    void ClientComputePipelineReference(WGPUComputePipeline cObj) {
        ComputePipeline* obj = reinterpret_cast<ComputePipeline*>(cObj);
        obj->refcount ++;
    }


    WGPUBindGroup ClientDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateBindGroupCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->BindGroupAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroup>(allocation->object.get());
    }

    WGPUBindGroupLayout ClientDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateBindGroupLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->BindGroupLayoutAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
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

        auto* allocation = self->client->CommandEncoderAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUCommandEncoder>(allocation->object.get());
    }

    WGPUComputePipeline ClientDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateComputePipelineCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->ComputePipelineAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUComputePipeline>(allocation->object.get());
    }

    static
    void ClientDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateComputePipelineAsync( descriptor,  callback,  userdata);
    }

    static
    WGPUBuffer ClientDeviceCreateErrorBuffer(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->CreateErrorBuffer();
    }

    WGPUExternalTexture ClientDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateExternalTextureCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->ExternalTextureAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.externalTextureDescriptor = externalTextureDescriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUExternalTexture>(allocation->object.get());
    }

    WGPUPipelineLayout ClientDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreatePipelineLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->PipelineLayoutAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUPipelineLayout>(allocation->object.get());
    }

    WGPUQuerySet ClientDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateQuerySetCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->QuerySetAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUQuerySet>(allocation->object.get());
    }

    WGPURenderBundleEncoder ClientDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateRenderBundleEncoderCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->RenderBundleEncoderAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderBundleEncoder>(allocation->object.get());
    }

    WGPURenderPipeline ClientDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateRenderPipelineCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->RenderPipelineAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderPipeline>(allocation->object.get());
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

        auto* allocation = self->client->SamplerAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUSampler>(allocation->object.get());
    }

    WGPUShaderModule ClientDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateShaderModuleCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->ShaderModuleAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUShaderModule>(allocation->object.get());
    }

    WGPUSwapChain ClientDeviceCreateSwapChain(WGPUDevice cSelf, WGPUSurface surface, WGPUSwapChainDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateSwapChainCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->SwapChainAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.surface = surface;
        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUSwapChain>(allocation->object.get());
    }

    WGPUTexture ClientDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceCreateTextureCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->TextureAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUTexture>(allocation->object.get());
    }

    void ClientDeviceDestroy(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceDestroyCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    static
    uint32_t ClientDeviceEnumerateFeatures(WGPUDevice cSelf, WGPUFeatureName * features) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->EnumerateFeatures( features);
    }

    static
    bool ClientDeviceGetLimits(WGPUDevice cSelf, WGPUSupportedLimits * limits) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->GetLimits( limits);
    }

    static
    WGPUQueue ClientDeviceGetQueue(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->GetQueue();
    }

    static
    bool ClientDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->HasFeature( feature);
    }

    static
    void ClientDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, char const * message) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->InjectError( type,  message);
    }

    void ClientDeviceLoseForTesting(WGPUDevice cSelf) {
        auto self = reinterpret_cast<Device*>(cSelf);
        DeviceLoseForTestingCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    static
    bool ClientDevicePopErrorScope(WGPUDevice cSelf, WGPUErrorCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->PopErrorScope( callback,  userdata);
    }

    static
    void ClientDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->PushErrorScope( filter);
    }

    static
    void ClientDeviceSetDeviceLostCallback(WGPUDevice cSelf, WGPUDeviceLostCallback callback, void * userdata) {
        auto self = reinterpret_cast<Device*>(cSelf);
        return self->SetDeviceLostCallback( callback,  userdata);
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



        self->client->SerializeCommand(cmd);

    }

    void ClientDeviceRelease(WGPUDevice cObj) {
        Device* obj = reinterpret_cast<Device*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Device;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->DeviceAllocator().Free(obj);
    }

    void ClientDeviceReference(WGPUDevice cObj) {
        Device* obj = reinterpret_cast<Device*>(cObj);
        obj->refcount ++;
    }


    void ClientExternalTextureDestroy(WGPUExternalTexture cSelf) {
        auto self = reinterpret_cast<ExternalTexture*>(cSelf);
        ExternalTextureDestroyCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientExternalTextureSetLabel(WGPUExternalTexture cSelf, char const * label) {
        auto self = reinterpret_cast<ExternalTexture*>(cSelf);
        ExternalTextureSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientExternalTextureRelease(WGPUExternalTexture cObj) {
        ExternalTexture* obj = reinterpret_cast<ExternalTexture*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ExternalTexture;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->ExternalTextureAllocator().Free(obj);
    }

    void ClientExternalTextureReference(WGPUExternalTexture cObj) {
        ExternalTexture* obj = reinterpret_cast<ExternalTexture*>(cObj);
        obj->refcount ++;
    }


    WGPUSurface ClientInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
        auto self = reinterpret_cast<Instance*>(cSelf);
        InstanceCreateSurfaceCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->SurfaceAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUSurface>(allocation->object.get());
    }

    static
    void ClientInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallback callback, void * userdata) {
        auto self = reinterpret_cast<Instance*>(cSelf);
        return self->RequestAdapter( options,  callback,  userdata);
    }

    void ClientInstanceRelease(WGPUInstance cObj) {
        Instance* obj = reinterpret_cast<Instance*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Instance;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->InstanceAllocator().Free(obj);
    }

    void ClientInstanceReference(WGPUInstance cObj) {
        Instance* obj = reinterpret_cast<Instance*>(cObj);
        obj->refcount ++;
    }


    void ClientPipelineLayoutSetLabel(WGPUPipelineLayout cSelf, char const * label) {
        auto self = reinterpret_cast<PipelineLayout*>(cSelf);
        PipelineLayoutSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientPipelineLayoutRelease(WGPUPipelineLayout cObj) {
        PipelineLayout* obj = reinterpret_cast<PipelineLayout*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::PipelineLayout;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->PipelineLayoutAllocator().Free(obj);
    }

    void ClientPipelineLayoutReference(WGPUPipelineLayout cObj) {
        PipelineLayout* obj = reinterpret_cast<PipelineLayout*>(cObj);
        obj->refcount ++;
    }


    void ClientQuerySetDestroy(WGPUQuerySet cSelf) {
        auto self = reinterpret_cast<QuerySet*>(cSelf);
        QuerySetDestroyCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientQuerySetSetLabel(WGPUQuerySet cSelf, char const * label) {
        auto self = reinterpret_cast<QuerySet*>(cSelf);
        QuerySetSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientQuerySetRelease(WGPUQuerySet cObj) {
        QuerySet* obj = reinterpret_cast<QuerySet*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::QuerySet;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->QuerySetAllocator().Free(obj);
    }

    void ClientQuerySetReference(WGPUQuerySet cObj) {
        QuerySet* obj = reinterpret_cast<QuerySet*>(cObj);
        obj->refcount ++;
    }


    void ClientQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        QueueCopyTextureForBrowserCmd cmd;

        cmd.self = cSelf;


        
        cmd.source = source;
        
        cmd.destination = destination;
        
        cmd.copySize = copySize;
        
        cmd.options = options;

        self->client->SerializeCommand(cmd);

    }

    static
    void ClientQueueOnSubmittedWorkDone(WGPUQueue cSelf, uint64_t signalValue, WGPUQueueWorkDoneCallback callback, void * userdata) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        return self->OnSubmittedWorkDone( signalValue,  callback,  userdata);
    }

    void ClientQueueSubmit(WGPUQueue cSelf, uint32_t commandCount, WGPUCommandBuffer const * commands) {
        auto self = reinterpret_cast<Queue*>(cSelf);
        QueueSubmitCmd cmd;

        cmd.self = cSelf;


        
        cmd.commandCount = commandCount;
        
        cmd.commands = commands;

        self->client->SerializeCommand(cmd);

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
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Queue;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->QueueAllocator().Free(obj);
    }

    void ClientQueueReference(WGPUQueue cObj) {
        Queue* obj = reinterpret_cast<Queue*>(cObj);
        obj->refcount ++;
    }


    void ClientRenderBundleRelease(WGPURenderBundle cObj) {
        RenderBundle* obj = reinterpret_cast<RenderBundle*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderBundle;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->RenderBundleAllocator().Free(obj);
    }

    void ClientRenderBundleReference(WGPURenderBundle cObj) {
        RenderBundle* obj = reinterpret_cast<RenderBundle*>(cObj);
        obj->refcount ++;
    }


    void ClientRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderDrawCmd cmd;

        cmd.self = cSelf;


        
        cmd.vertexCount = vertexCount;
        
        cmd.instanceCount = instanceCount;
        
        cmd.firstVertex = firstVertex;
        
        cmd.firstInstance = firstInstance;

        self->client->SerializeCommand(cmd);

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

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderDrawIndexedIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderDrawIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->client->SerializeCommand(cmd);

    }

    WGPURenderBundle ClientRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderFinishCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->RenderBundleAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPURenderBundle>(allocation->object.get());
    }

    void ClientRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupIndex = groupIndex;
        
        cmd.group = group;
        
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        
        cmd.dynamicOffsets = dynamicOffsets;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetIndexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.format = format;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        
        cmd.pipeline = pipeline;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderBundleEncoder*>(cSelf);
        RenderBundleEncoderSetVertexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.slot = slot;
        
        cmd.buffer = buffer;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderBundleEncoderRelease(WGPURenderBundleEncoder cObj) {
        RenderBundleEncoder* obj = reinterpret_cast<RenderBundleEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderBundleEncoder;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->RenderBundleEncoderAllocator().Free(obj);
    }

    void ClientRenderBundleEncoderReference(WGPURenderBundleEncoder cObj) {
        RenderBundleEncoder* obj = reinterpret_cast<RenderBundleEncoder*>(cObj);
        obj->refcount ++;
    }


    void ClientRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderBeginOcclusionQueryCmd cmd;

        cmd.self = cSelf;


        
        cmd.queryIndex = queryIndex;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderDrawCmd cmd;

        cmd.self = cSelf;


        
        cmd.vertexCount = vertexCount;
        
        cmd.instanceCount = instanceCount;
        
        cmd.firstVertex = firstVertex;
        
        cmd.firstInstance = firstInstance;

        self->client->SerializeCommand(cmd);

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

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderDrawIndexedIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderDrawIndirectCmd cmd;

        cmd.self = cSelf;


        
        cmd.indirectBuffer = indirectBuffer;
        
        cmd.indirectOffset = indirectOffset;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderEndOcclusionQueryCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderEndPass(WGPURenderPassEncoder cSelf) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderEndPassCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, uint32_t bundlesCount, WGPURenderBundle const * bundles) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderExecuteBundlesCmd cmd;

        cmd.self = cSelf;


        
        cmd.bundlesCount = bundlesCount;
        
        cmd.bundles = bundles;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, char const * markerLabel) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderInsertDebugMarkerCmd cmd;

        cmd.self = cSelf;


        
        cmd.markerLabel = markerLabel;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderPopDebugGroupCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, char const * groupLabel) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderPushDebugGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupLabel = groupLabel;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetBindGroupCmd cmd;

        cmd.self = cSelf;


        
        cmd.groupIndex = groupIndex;
        
        cmd.group = group;
        
        cmd.dynamicOffsetCount = dynamicOffsetCount;
        
        cmd.dynamicOffsets = dynamicOffsets;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetBlendConstantCmd cmd;

        cmd.self = cSelf;


        
        cmd.color = color;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetIndexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.buffer = buffer;
        
        cmd.format = format;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, char const * label) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetPipelineCmd cmd;

        cmd.self = cSelf;


        
        cmd.pipeline = pipeline;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetScissorRectCmd cmd;

        cmd.self = cSelf;


        
        cmd.x = x;
        
        cmd.y = y;
        
        cmd.width = width;
        
        cmd.height = height;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetStencilReferenceCmd cmd;

        cmd.self = cSelf;


        
        cmd.reference = reference;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderSetVertexBufferCmd cmd;

        cmd.self = cSelf;


        
        cmd.slot = slot;
        
        cmd.buffer = buffer;
        
        cmd.offset = offset;
        
        cmd.size = size;

        self->client->SerializeCommand(cmd);

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

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = reinterpret_cast<RenderPassEncoder*>(cSelf);
        RenderPassEncoderWriteTimestampCmd cmd;

        cmd.self = cSelf;


        
        cmd.querySet = querySet;
        
        cmd.queryIndex = queryIndex;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPassEncoderRelease(WGPURenderPassEncoder cObj) {
        RenderPassEncoder* obj = reinterpret_cast<RenderPassEncoder*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderPassEncoder;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->RenderPassEncoderAllocator().Free(obj);
    }

    void ClientRenderPassEncoderReference(WGPURenderPassEncoder cObj) {
        RenderPassEncoder* obj = reinterpret_cast<RenderPassEncoder*>(cObj);
        obj->refcount ++;
    }


    WGPUBindGroupLayout ClientRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
        auto self = reinterpret_cast<RenderPipeline*>(cSelf);
        RenderPipelineGetBindGroupLayoutCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->BindGroupLayoutAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.groupIndex = groupIndex;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUBindGroupLayout>(allocation->object.get());
    }

    void ClientRenderPipelineSetLabel(WGPURenderPipeline cSelf, char const * label) {
        auto self = reinterpret_cast<RenderPipeline*>(cSelf);
        RenderPipelineSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientRenderPipelineRelease(WGPURenderPipeline cObj) {
        RenderPipeline* obj = reinterpret_cast<RenderPipeline*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::RenderPipeline;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->RenderPipelineAllocator().Free(obj);
    }

    void ClientRenderPipelineReference(WGPURenderPipeline cObj) {
        RenderPipeline* obj = reinterpret_cast<RenderPipeline*>(cObj);
        obj->refcount ++;
    }


    void ClientSamplerSetLabel(WGPUSampler cSelf, char const * label) {
        auto self = reinterpret_cast<Sampler*>(cSelf);
        SamplerSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientSamplerRelease(WGPUSampler cObj) {
        Sampler* obj = reinterpret_cast<Sampler*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Sampler;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->SamplerAllocator().Free(obj);
    }

    void ClientSamplerReference(WGPUSampler cObj) {
        Sampler* obj = reinterpret_cast<Sampler*>(cObj);
        obj->refcount ++;
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

        self->client->SerializeCommand(cmd);

    }

    void ClientShaderModuleRelease(WGPUShaderModule cObj) {
        ShaderModule* obj = reinterpret_cast<ShaderModule*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::ShaderModule;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->ShaderModuleAllocator().Free(obj);
    }

    void ClientShaderModuleReference(WGPUShaderModule cObj) {
        ShaderModule* obj = reinterpret_cast<ShaderModule*>(cObj);
        obj->refcount ++;
    }


    void ClientSurfaceRelease(WGPUSurface cObj) {
        Surface* obj = reinterpret_cast<Surface*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Surface;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->SurfaceAllocator().Free(obj);
    }

    void ClientSurfaceReference(WGPUSurface cObj) {
        Surface* obj = reinterpret_cast<Surface*>(cObj);
        obj->refcount ++;
    }


    void ClientSwapChainConfigure(WGPUSwapChain cSelf, WGPUTextureFormat format, WGPUTextureUsageFlags allowedUsage, uint32_t width, uint32_t height) {
        auto self = reinterpret_cast<SwapChain*>(cSelf);
        SwapChainConfigureCmd cmd;

        cmd.self = cSelf;


        
        cmd.format = format;
        
        cmd.allowedUsage = allowedUsage;
        
        cmd.width = width;
        
        cmd.height = height;

        self->client->SerializeCommand(cmd);

    }

    WGPUTextureView ClientSwapChainGetCurrentTextureView(WGPUSwapChain cSelf) {
        auto self = reinterpret_cast<SwapChain*>(cSelf);
        SwapChainGetCurrentTextureViewCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->TextureViewAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};


        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUTextureView>(allocation->object.get());
    }

    void ClientSwapChainPresent(WGPUSwapChain cSelf) {
        auto self = reinterpret_cast<SwapChain*>(cSelf);
        SwapChainPresentCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientSwapChainRelease(WGPUSwapChain cObj) {
        SwapChain* obj = reinterpret_cast<SwapChain*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::SwapChain;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->SwapChainAllocator().Free(obj);
    }

    void ClientSwapChainReference(WGPUSwapChain cObj) {
        SwapChain* obj = reinterpret_cast<SwapChain*>(cObj);
        obj->refcount ++;
    }


    WGPUTextureView ClientTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        TextureCreateViewCmd cmd;

        cmd.self = cSelf;

        auto* allocation = self->client->TextureViewAllocator().New(self->client);
        cmd.result = ObjectHandle{allocation->object->id, allocation->generation};

        
        cmd.descriptor = descriptor;

        self->client->SerializeCommand(cmd);

        return reinterpret_cast<WGPUTextureView>(allocation->object.get());
    }

    void ClientTextureDestroy(WGPUTexture cSelf) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        TextureDestroyCmd cmd;

        cmd.self = cSelf;



        self->client->SerializeCommand(cmd);

    }

    void ClientTextureSetLabel(WGPUTexture cSelf, char const * label) {
        auto self = reinterpret_cast<Texture*>(cSelf);
        TextureSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientTextureRelease(WGPUTexture cObj) {
        Texture* obj = reinterpret_cast<Texture*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::Texture;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->TextureAllocator().Free(obj);
    }

    void ClientTextureReference(WGPUTexture cObj) {
        Texture* obj = reinterpret_cast<Texture*>(cObj);
        obj->refcount ++;
    }


    void ClientTextureViewSetLabel(WGPUTextureView cSelf, char const * label) {
        auto self = reinterpret_cast<TextureView*>(cSelf);
        TextureViewSetLabelCmd cmd;

        cmd.self = cSelf;


        
        cmd.label = label;

        self->client->SerializeCommand(cmd);

    }

    void ClientTextureViewRelease(WGPUTextureView cObj) {
        TextureView* obj = reinterpret_cast<TextureView*>(cObj);
        obj->refcount --;

        if (obj->refcount > 0) {
            return;
        }

        DestroyObjectCmd cmd;
        cmd.objectType = ObjectType::TextureView;
        cmd.objectId = obj->id;

        obj->client->SerializeCommand(cmd);
        obj->client->TextureViewAllocator().Free(obj);
    }

    void ClientTextureViewReference(WGPUTextureView cObj) {
        TextureView* obj = reinterpret_cast<TextureView*>(cObj);
        obj->refcount ++;
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
            { reinterpret_cast<WGPUProc>(ClientBufferGetMappedRange), "wgpuBufferGetMappedRange" },
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
            { reinterpret_cast<WGPUProc>(ClientCommandEncoderCopyTextureToTextureInternal), "wgpuCommandEncoderCopyTextureToTextureInternal" },
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
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderDispatch), "wgpuComputePassEncoderDispatch" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderDispatchIndirect), "wgpuComputePassEncoderDispatchIndirect" },
            { reinterpret_cast<WGPUProc>(ClientComputePassEncoderEndPass), "wgpuComputePassEncoderEndPass" },
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
            { reinterpret_cast<WGPUProc>(ClientDeviceGetLimits), "wgpuDeviceGetLimits" },
            { reinterpret_cast<WGPUProc>(ClientDeviceGetQueue), "wgpuDeviceGetQueue" },
            { reinterpret_cast<WGPUProc>(ClientDeviceHasFeature), "wgpuDeviceHasFeature" },
            { reinterpret_cast<WGPUProc>(ClientDeviceInjectError), "wgpuDeviceInjectError" },
            { reinterpret_cast<WGPUProc>(ClientDeviceLoseForTesting), "wgpuDeviceLoseForTesting" },
            { reinterpret_cast<WGPUProc>(ClientDevicePopErrorScope), "wgpuDevicePopErrorScope" },
            { reinterpret_cast<WGPUProc>(ClientDevicePushErrorScope), "wgpuDevicePushErrorScope" },
            { reinterpret_cast<WGPUProc>(ClientDeviceReference), "wgpuDeviceReference" },
            { reinterpret_cast<WGPUProc>(ClientDeviceRelease), "wgpuDeviceRelease" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetDeviceLostCallback), "wgpuDeviceSetDeviceLostCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetLoggingCallback), "wgpuDeviceSetLoggingCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceSetUncapturedErrorCallback), "wgpuDeviceSetUncapturedErrorCallback" },
            { reinterpret_cast<WGPUProc>(ClientDeviceTick), "wgpuDeviceTick" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureDestroy), "wgpuExternalTextureDestroy" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureReference), "wgpuExternalTextureReference" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureRelease), "wgpuExternalTextureRelease" },
            { reinterpret_cast<WGPUProc>(ClientExternalTextureSetLabel), "wgpuExternalTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientInstanceCreateSurface), "wgpuInstanceCreateSurface" },
            { reinterpret_cast<WGPUProc>(ClientInstanceReference), "wgpuInstanceReference" },
            { reinterpret_cast<WGPUProc>(ClientInstanceRelease), "wgpuInstanceRelease" },
            { reinterpret_cast<WGPUProc>(ClientInstanceRequestAdapter), "wgpuInstanceRequestAdapter" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutReference), "wgpuPipelineLayoutReference" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutRelease), "wgpuPipelineLayoutRelease" },
            { reinterpret_cast<WGPUProc>(ClientPipelineLayoutSetLabel), "wgpuPipelineLayoutSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetDestroy), "wgpuQuerySetDestroy" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetReference), "wgpuQuerySetReference" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetRelease), "wgpuQuerySetRelease" },
            { reinterpret_cast<WGPUProc>(ClientQuerySetSetLabel), "wgpuQuerySetSetLabel" },
            { reinterpret_cast<WGPUProc>(ClientQueueCopyTextureForBrowser), "wgpuQueueCopyTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(ClientQueueOnSubmittedWorkDone), "wgpuQueueOnSubmittedWorkDone" },
            { reinterpret_cast<WGPUProc>(ClientQueueReference), "wgpuQueueReference" },
            { reinterpret_cast<WGPUProc>(ClientQueueRelease), "wgpuQueueRelease" },
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
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderBeginOcclusionQuery), "wgpuRenderPassEncoderBeginOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDraw), "wgpuRenderPassEncoderDraw" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndexed), "wgpuRenderPassEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndexedIndirect), "wgpuRenderPassEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderDrawIndirect), "wgpuRenderPassEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderEndOcclusionQuery), "wgpuRenderPassEncoderEndOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(ClientRenderPassEncoderEndPass), "wgpuRenderPassEncoderEndPass" },
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
            { reinterpret_cast<WGPUProc>(ClientSwapChainConfigure), "wgpuSwapChainConfigure" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainGetCurrentTextureView), "wgpuSwapChainGetCurrentTextureView" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainPresent), "wgpuSwapChainPresent" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainReference), "wgpuSwapChainReference" },
            { reinterpret_cast<WGPUProc>(ClientSwapChainRelease), "wgpuSwapChainRelease" },
            { reinterpret_cast<WGPUProc>(ClientTextureCreateView), "wgpuTextureCreateView" },
            { reinterpret_cast<WGPUProc>(ClientTextureDestroy), "wgpuTextureDestroy" },
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

    static DawnProcTable gProcTable = {
        ClientCreateInstance,
        ClientGetProcAddress,
        ClientAdapterCreateDevice,
        ClientAdapterEnumerateFeatures,
        ClientAdapterGetLimits,
        ClientAdapterGetProperties,
        ClientAdapterHasFeature,
        ClientAdapterRequestDevice,
        ClientAdapterReference,
        ClientAdapterRelease,
        ClientBindGroupSetLabel,
        ClientBindGroupReference,
        ClientBindGroupRelease,
        ClientBindGroupLayoutSetLabel,
        ClientBindGroupLayoutReference,
        ClientBindGroupLayoutRelease,
        ClientBufferDestroy,
        ClientBufferGetConstMappedRange,
        ClientBufferGetMappedRange,
        ClientBufferMapAsync,
        ClientBufferSetLabel,
        ClientBufferUnmap,
        ClientBufferReference,
        ClientBufferRelease,
        ClientCommandBufferSetLabel,
        ClientCommandBufferReference,
        ClientCommandBufferRelease,
        ClientCommandEncoderBeginComputePass,
        ClientCommandEncoderBeginRenderPass,
        ClientCommandEncoderClearBuffer,
        ClientCommandEncoderCopyBufferToBuffer,
        ClientCommandEncoderCopyBufferToTexture,
        ClientCommandEncoderCopyTextureToBuffer,
        ClientCommandEncoderCopyTextureToTexture,
        ClientCommandEncoderCopyTextureToTextureInternal,
        ClientCommandEncoderFinish,
        ClientCommandEncoderInjectValidationError,
        ClientCommandEncoderInsertDebugMarker,
        ClientCommandEncoderPopDebugGroup,
        ClientCommandEncoderPushDebugGroup,
        ClientCommandEncoderResolveQuerySet,
        ClientCommandEncoderSetLabel,
        ClientCommandEncoderWriteBuffer,
        ClientCommandEncoderWriteTimestamp,
        ClientCommandEncoderReference,
        ClientCommandEncoderRelease,
        ClientComputePassEncoderDispatch,
        ClientComputePassEncoderDispatchIndirect,
        ClientComputePassEncoderEndPass,
        ClientComputePassEncoderInsertDebugMarker,
        ClientComputePassEncoderPopDebugGroup,
        ClientComputePassEncoderPushDebugGroup,
        ClientComputePassEncoderSetBindGroup,
        ClientComputePassEncoderSetLabel,
        ClientComputePassEncoderSetPipeline,
        ClientComputePassEncoderWriteTimestamp,
        ClientComputePassEncoderReference,
        ClientComputePassEncoderRelease,
        ClientComputePipelineGetBindGroupLayout,
        ClientComputePipelineSetLabel,
        ClientComputePipelineReference,
        ClientComputePipelineRelease,
        ClientDeviceCreateBindGroup,
        ClientDeviceCreateBindGroupLayout,
        ClientDeviceCreateBuffer,
        ClientDeviceCreateCommandEncoder,
        ClientDeviceCreateComputePipeline,
        ClientDeviceCreateComputePipelineAsync,
        ClientDeviceCreateErrorBuffer,
        ClientDeviceCreateExternalTexture,
        ClientDeviceCreatePipelineLayout,
        ClientDeviceCreateQuerySet,
        ClientDeviceCreateRenderBundleEncoder,
        ClientDeviceCreateRenderPipeline,
        ClientDeviceCreateRenderPipelineAsync,
        ClientDeviceCreateSampler,
        ClientDeviceCreateShaderModule,
        ClientDeviceCreateSwapChain,
        ClientDeviceCreateTexture,
        ClientDeviceDestroy,
        ClientDeviceEnumerateFeatures,
        ClientDeviceGetLimits,
        ClientDeviceGetQueue,
        ClientDeviceHasFeature,
        ClientDeviceInjectError,
        ClientDeviceLoseForTesting,
        ClientDevicePopErrorScope,
        ClientDevicePushErrorScope,
        ClientDeviceSetDeviceLostCallback,
        ClientDeviceSetLoggingCallback,
        ClientDeviceSetUncapturedErrorCallback,
        ClientDeviceTick,
        ClientDeviceReference,
        ClientDeviceRelease,
        ClientExternalTextureDestroy,
        ClientExternalTextureSetLabel,
        ClientExternalTextureReference,
        ClientExternalTextureRelease,
        ClientInstanceCreateSurface,
        ClientInstanceRequestAdapter,
        ClientInstanceReference,
        ClientInstanceRelease,
        ClientPipelineLayoutSetLabel,
        ClientPipelineLayoutReference,
        ClientPipelineLayoutRelease,
        ClientQuerySetDestroy,
        ClientQuerySetSetLabel,
        ClientQuerySetReference,
        ClientQuerySetRelease,
        ClientQueueCopyTextureForBrowser,
        ClientQueueOnSubmittedWorkDone,
        ClientQueueSubmit,
        ClientQueueWriteBuffer,
        ClientQueueWriteTexture,
        ClientQueueReference,
        ClientQueueRelease,
        ClientRenderBundleReference,
        ClientRenderBundleRelease,
        ClientRenderBundleEncoderDraw,
        ClientRenderBundleEncoderDrawIndexed,
        ClientRenderBundleEncoderDrawIndexedIndirect,
        ClientRenderBundleEncoderDrawIndirect,
        ClientRenderBundleEncoderFinish,
        ClientRenderBundleEncoderInsertDebugMarker,
        ClientRenderBundleEncoderPopDebugGroup,
        ClientRenderBundleEncoderPushDebugGroup,
        ClientRenderBundleEncoderSetBindGroup,
        ClientRenderBundleEncoderSetIndexBuffer,
        ClientRenderBundleEncoderSetLabel,
        ClientRenderBundleEncoderSetPipeline,
        ClientRenderBundleEncoderSetVertexBuffer,
        ClientRenderBundleEncoderReference,
        ClientRenderBundleEncoderRelease,
        ClientRenderPassEncoderBeginOcclusionQuery,
        ClientRenderPassEncoderDraw,
        ClientRenderPassEncoderDrawIndexed,
        ClientRenderPassEncoderDrawIndexedIndirect,
        ClientRenderPassEncoderDrawIndirect,
        ClientRenderPassEncoderEndOcclusionQuery,
        ClientRenderPassEncoderEndPass,
        ClientRenderPassEncoderExecuteBundles,
        ClientRenderPassEncoderInsertDebugMarker,
        ClientRenderPassEncoderPopDebugGroup,
        ClientRenderPassEncoderPushDebugGroup,
        ClientRenderPassEncoderSetBindGroup,
        ClientRenderPassEncoderSetBlendConstant,
        ClientRenderPassEncoderSetIndexBuffer,
        ClientRenderPassEncoderSetLabel,
        ClientRenderPassEncoderSetPipeline,
        ClientRenderPassEncoderSetScissorRect,
        ClientRenderPassEncoderSetStencilReference,
        ClientRenderPassEncoderSetVertexBuffer,
        ClientRenderPassEncoderSetViewport,
        ClientRenderPassEncoderWriteTimestamp,
        ClientRenderPassEncoderReference,
        ClientRenderPassEncoderRelease,
        ClientRenderPipelineGetBindGroupLayout,
        ClientRenderPipelineSetLabel,
        ClientRenderPipelineReference,
        ClientRenderPipelineRelease,
        ClientSamplerSetLabel,
        ClientSamplerReference,
        ClientSamplerRelease,
        ClientShaderModuleGetCompilationInfo,
        ClientShaderModuleSetLabel,
        ClientShaderModuleReference,
        ClientShaderModuleRelease,
        ClientSurfaceReference,
        ClientSurfaceRelease,
        ClientSwapChainConfigure,
        ClientSwapChainGetCurrentTextureView,
        ClientSwapChainPresent,
        ClientSwapChainReference,
        ClientSwapChainRelease,
        ClientTextureCreateView,
        ClientTextureDestroy,
        ClientTextureSetLabel,
        ClientTextureReference,
        ClientTextureRelease,
        ClientTextureViewSetLabel,
        ClientTextureViewReference,
        ClientTextureViewRelease,
    };
    const DawnProcTable& GetProcs() {
        return gProcTable;
    }
}}  // namespace dawn_wire::client
