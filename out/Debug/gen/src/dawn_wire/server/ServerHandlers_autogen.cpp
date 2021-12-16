
#include "common/Assert.h"
#include "dawn_wire/server/Server.h"

namespace dawn_wire { namespace server {

    bool Server::HandleAdapterRequestDevice(DeserializeBuffer* deserializeBuffer) {
        AdapterRequestDeviceCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoAdapterRequestDevice(cmd.adapterId, cmd.requestSerial, cmd.deviceObjectHandle, cmd.descriptor);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBindGroupLayoutSetLabel(DeserializeBuffer* deserializeBuffer) {
        BindGroupLayoutSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoBindGroupLayoutSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBindGroupSetLabel(DeserializeBuffer* deserializeBuffer) {
        BindGroupSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoBindGroupSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferDestroy(DeserializeBuffer* deserializeBuffer) {
        BufferDestroyCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }

        if (!PreHandleBufferDestroy(cmd)) {
            return false;
        }

        bool success = DoBufferDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferMapAsync(DeserializeBuffer* deserializeBuffer) {
        BufferMapAsyncCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoBufferMapAsync(cmd.bufferId, cmd.requestSerial, cmd.mode, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferSetLabel(DeserializeBuffer* deserializeBuffer) {
        BufferSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoBufferSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferUnmap(DeserializeBuffer* deserializeBuffer) {
        BufferUnmapCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }

        if (!PreHandleBufferUnmap(cmd)) {
            return false;
        }

        bool success = DoBufferUnmap(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleBufferUpdateMappedData(DeserializeBuffer* deserializeBuffer) {
        BufferUpdateMappedDataCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoBufferUpdateMappedData(cmd.bufferId, cmd.writeDataUpdateInfoLength, cmd.writeDataUpdateInfo, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandBufferSetLabel(DeserializeBuffer* deserializeBuffer) {
        CommandBufferSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandBufferSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderBeginComputePass(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderBeginComputePassCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = ComputePassEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = CommandEncoderObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::ComputePassEncoder, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoCommandEncoderBeginComputePass(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleCommandEncoderBeginRenderPass(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderBeginRenderPassCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = RenderPassEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = CommandEncoderObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::RenderPassEncoder, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoCommandEncoderBeginRenderPass(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleCommandEncoderClearBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderClearBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderClearBuffer(cmd.self, cmd.buffer, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyBufferToBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyBufferToBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyBufferToBuffer(cmd.self, cmd.source, cmd.sourceOffset, cmd.destination, cmd.destinationOffset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyBufferToTexture(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyBufferToTextureCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyBufferToTexture(cmd.self, cmd.source, cmd.destination, cmd.copySize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyTextureToBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyTextureToBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyTextureToBuffer(cmd.self, cmd.source, cmd.destination, cmd.copySize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyTextureToTexture(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyTextureToTextureCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyTextureToTexture(cmd.self, cmd.source, cmd.destination, cmd.copySize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderCopyTextureToTextureInternal(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyTextureToTextureInternalCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderCopyTextureToTextureInternal(cmd.self, cmd.source, cmd.destination, cmd.copySize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderFinish(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderFinishCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = CommandBufferObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = CommandEncoderObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::CommandBuffer, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoCommandEncoderFinish(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleCommandEncoderInjectValidationError(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderInjectValidationErrorCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderInjectValidationError(cmd.self, cmd.message);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderInsertDebugMarkerCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderPopDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderPushDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderResolveQuerySet(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderResolveQuerySetCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderResolveQuerySet(cmd.self, cmd.querySet, cmd.firstQuery, cmd.queryCount, cmd.destination, cmd.destinationOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderWriteBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderWriteBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderWriteBuffer(cmd.self, cmd.buffer, cmd.bufferOffset, cmd.data, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleCommandEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderWriteTimestampCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoCommandEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderDispatch(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderDispatchCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderDispatch(cmd.self, cmd.x, cmd.y, cmd.z);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderDispatchIndirect(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderDispatchIndirectCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderDispatchIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderEndPass(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderEndPassCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderEndPass(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderInsertDebugMarkerCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderPopDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderPushDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderSetBindGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderSetPipelineCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderSetPipeline(cmd.self, cmd.pipeline);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderWriteTimestampCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePassEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleComputePipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer) {
        ComputePipelineGetBindGroupLayoutCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = ComputePipelineObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::BindGroupLayout, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoComputePipelineGetBindGroupLayout(cmd.self, cmd.groupIndex, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleComputePipelineSetLabel(DeserializeBuffer* deserializeBuffer) {
        ComputePipelineSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoComputePipelineSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDestroyObject(DeserializeBuffer* deserializeBuffer) {
        DestroyObjectCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDestroyObject(cmd.objectType, cmd.objectId);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateBindGroup(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateBindGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::BindGroup, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateBindGroup(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateBindGroupLayout(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateBindGroupLayoutCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::BindGroupLayout, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateBindGroupLayout(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateBuffer(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDeviceCreateBuffer(cmd.deviceId, cmd.descriptor, cmd.result, cmd.readHandleCreateInfoLength, cmd.readHandleCreateInfo, cmd.writeHandleCreateInfoLength, cmd.writeHandleCreateInfo);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateCommandEncoder(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateCommandEncoderCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = CommandEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::CommandEncoder, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateCommandEncoder(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateComputePipeline(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateComputePipelineCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = ComputePipelineObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::ComputePipeline, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateComputePipeline(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateComputePipelineAsync(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateComputePipelineAsyncCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDeviceCreateComputePipelineAsync(cmd.deviceId, cmd.requestSerial, cmd.pipelineObjectHandle, cmd.descriptor);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateErrorBuffer(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateErrorBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = BufferObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::Buffer, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateErrorBuffer(cmd.self, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateExternalTexture(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateExternalTextureCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = ExternalTextureObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::ExternalTexture, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateExternalTexture(cmd.self, cmd.externalTextureDescriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreatePipelineLayout(DeserializeBuffer* deserializeBuffer) {
        DeviceCreatePipelineLayoutCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = PipelineLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::PipelineLayout, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreatePipelineLayout(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateQuerySet(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateQuerySetCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = QuerySetObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::QuerySet, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateQuerySet(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateRenderBundleEncoder(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateRenderBundleEncoderCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = RenderBundleEncoderObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::RenderBundleEncoder, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateRenderBundleEncoder(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateRenderPipeline(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateRenderPipelineCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = RenderPipelineObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::RenderPipeline, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateRenderPipeline(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateRenderPipelineAsync(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateRenderPipelineAsyncCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDeviceCreateRenderPipelineAsync(cmd.deviceId, cmd.requestSerial, cmd.pipelineObjectHandle, cmd.descriptor);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceCreateSampler(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateSamplerCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = SamplerObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::Sampler, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateSampler(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateShaderModule(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateShaderModuleCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = ShaderModuleObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::ShaderModule, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateShaderModule(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateSwapChain(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateSwapChainCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = SwapChainObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::SwapChain, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateSwapChain(cmd.self, cmd.surface, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceCreateTexture(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateTextureCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = TextureObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::Texture, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceCreateTexture(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceDestroy(DeserializeBuffer* deserializeBuffer) {
        DeviceDestroyCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDeviceDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceGetQueue(DeserializeBuffer* deserializeBuffer) {
        DeviceGetQueueCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = QueueObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        resultData->deviceInfo = DeviceObjects().Get(cmd.selfId)->info.get();
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::Queue, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoDeviceGetQueue(cmd.self, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleDeviceInjectError(DeserializeBuffer* deserializeBuffer) {
        DeviceInjectErrorCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDeviceInjectError(cmd.self, cmd.type, cmd.message);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceLoseForTesting(DeserializeBuffer* deserializeBuffer) {
        DeviceLoseForTestingCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDeviceLoseForTesting(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDevicePopErrorScope(DeserializeBuffer* deserializeBuffer) {
        DevicePopErrorScopeCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDevicePopErrorScope(cmd.deviceId, cmd.requestSerial);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDevicePushErrorScope(DeserializeBuffer* deserializeBuffer) {
        DevicePushErrorScopeCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDevicePushErrorScope(cmd.self, cmd.filter);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleDeviceTick(DeserializeBuffer* deserializeBuffer) {
        DeviceTickCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoDeviceTick(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleExternalTextureDestroy(DeserializeBuffer* deserializeBuffer) {
        ExternalTextureDestroyCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoExternalTextureDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleExternalTextureSetLabel(DeserializeBuffer* deserializeBuffer) {
        ExternalTextureSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoExternalTextureSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleInstanceCreateSurface(DeserializeBuffer* deserializeBuffer) {
        InstanceCreateSurfaceCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = SurfaceObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = InstanceObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::Surface, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoInstanceCreateSurface(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleInstanceRequestAdapter(DeserializeBuffer* deserializeBuffer) {
        InstanceRequestAdapterCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoInstanceRequestAdapter(cmd.instanceId, cmd.requestSerial, cmd.adapterObjectHandle, cmd.options);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandlePipelineLayoutSetLabel(DeserializeBuffer* deserializeBuffer) {
        PipelineLayoutSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoPipelineLayoutSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQuerySetDestroy(DeserializeBuffer* deserializeBuffer) {
        QuerySetDestroyCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoQuerySetDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQuerySetSetLabel(DeserializeBuffer* deserializeBuffer) {
        QuerySetSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoQuerySetSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueCopyTextureForBrowser(DeserializeBuffer* deserializeBuffer) {
        QueueCopyTextureForBrowserCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoQueueCopyTextureForBrowser(cmd.self, cmd.source, cmd.destination, cmd.copySize, cmd.options);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueOnSubmittedWorkDone(DeserializeBuffer* deserializeBuffer) {
        QueueOnSubmittedWorkDoneCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoQueueOnSubmittedWorkDone(cmd.queueId, cmd.signalValue, cmd.requestSerial);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueSubmit(DeserializeBuffer* deserializeBuffer) {
        QueueSubmitCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoQueueSubmit(cmd.self, cmd.commandCount, cmd.commands);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueWriteBuffer(DeserializeBuffer* deserializeBuffer) {
        QueueWriteBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoQueueWriteBuffer(cmd.queueId, cmd.bufferId, cmd.bufferOffset, cmd.data, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleQueueWriteTexture(DeserializeBuffer* deserializeBuffer) {
        QueueWriteTextureCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoQueueWriteTexture(cmd.queueId, cmd.destination, cmd.data, cmd.dataSize, cmd.dataLayout, cmd.writeSize);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDraw(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDraw(cmd.self, cmd.vertexCount, cmd.instanceCount, cmd.firstVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawIndexedCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDrawIndexed(cmd.self, cmd.indexCount, cmd.instanceCount, cmd.firstIndex, cmd.baseVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawIndexedIndirectCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDrawIndexedIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawIndirectCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderDrawIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderFinish(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderFinishCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = RenderBundleObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = RenderBundleEncoderObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::RenderBundle, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoRenderBundleEncoderFinish(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleRenderBundleEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderInsertDebugMarkerCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderPopDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderPushDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetBindGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetIndexBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetIndexBuffer(cmd.self, cmd.buffer, cmd.format, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetPipeline(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetPipelineCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetPipeline(cmd.self, cmd.pipeline);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderBundleEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetVertexBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderBundleEncoderSetVertexBuffer(cmd.self, cmd.slot, cmd.buffer, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderBeginOcclusionQuery(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderBeginOcclusionQueryCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderBeginOcclusionQuery(cmd.self, cmd.queryIndex);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDraw(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDraw(cmd.self, cmd.vertexCount, cmd.instanceCount, cmd.firstVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawIndexedCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDrawIndexed(cmd.self, cmd.indexCount, cmd.instanceCount, cmd.firstIndex, cmd.baseVertex, cmd.firstInstance);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawIndexedIndirectCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDrawIndexedIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawIndirectCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderDrawIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderEndOcclusionQuery(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderEndOcclusionQueryCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderEndOcclusionQuery(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderEndPass(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderEndPassCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderEndPass(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderExecuteBundles(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderExecuteBundlesCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderExecuteBundles(cmd.self, cmd.bundlesCount, cmd.bundles);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderInsertDebugMarkerCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderInsertDebugMarker(cmd.self, cmd.markerLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderPopDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderPopDebugGroup(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderPushDebugGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderPushDebugGroup(cmd.self, cmd.groupLabel);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetBindGroupCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetBlendConstant(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetBlendConstantCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetBlendConstant(cmd.self, cmd.color);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetIndexBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetIndexBuffer(cmd.self, cmd.buffer, cmd.format, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetPipelineCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetPipeline(cmd.self, cmd.pipeline);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetScissorRect(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetScissorRectCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetScissorRect(cmd.self, cmd.x, cmd.y, cmd.width, cmd.height);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetStencilReference(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetStencilReferenceCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetStencilReference(cmd.self, cmd.reference);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetVertexBufferCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetVertexBuffer(cmd.self, cmd.slot, cmd.buffer, cmd.offset, cmd.size);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderSetViewport(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetViewportCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderSetViewport(cmd.self, cmd.x, cmd.y, cmd.width, cmd.height, cmd.minDepth, cmd.maxDepth);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderWriteTimestampCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPassEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleRenderPipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer) {
        RenderPipelineGetBindGroupLayoutCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = BindGroupLayoutObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = RenderPipelineObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::BindGroupLayout, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoRenderPipelineGetBindGroupLayout(cmd.self, cmd.groupIndex, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleRenderPipelineSetLabel(DeserializeBuffer* deserializeBuffer) {
        RenderPipelineSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoRenderPipelineSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleSamplerSetLabel(DeserializeBuffer* deserializeBuffer) {
        SamplerSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoSamplerSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleShaderModuleGetCompilationInfo(DeserializeBuffer* deserializeBuffer) {
        ShaderModuleGetCompilationInfoCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoShaderModuleGetCompilationInfo(cmd.shaderModuleId, cmd.requestSerial);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleShaderModuleSetLabel(DeserializeBuffer* deserializeBuffer) {
        ShaderModuleSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoShaderModuleSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleSwapChainConfigure(DeserializeBuffer* deserializeBuffer) {
        SwapChainConfigureCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoSwapChainConfigure(cmd.self, cmd.format, cmd.allowedUsage, cmd.width, cmd.height);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleSwapChainGetCurrentTextureView(DeserializeBuffer* deserializeBuffer) {
        SwapChainGetCurrentTextureViewCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = TextureViewObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = SwapChainObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::TextureView, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoSwapChainGetCurrentTextureView(cmd.self, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleSwapChainPresent(DeserializeBuffer* deserializeBuffer) {
        SwapChainPresentCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoSwapChainPresent(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleTextureCreateView(DeserializeBuffer* deserializeBuffer) {
        TextureCreateViewCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }



        auto* resultData = TextureViewObjects().Allocate(cmd.result.id);
        if (resultData == nullptr) {
            return false;
        }
        resultData->generation = cmd.result.generation;

        auto* selfData = TextureObjects().Get(cmd.selfId);
        resultData->deviceInfo = selfData->deviceInfo;
        if (resultData->deviceInfo != nullptr) {
            if (!TrackDeviceChild(resultData->deviceInfo, ObjectType::TextureView, cmd.result.id)) {
                return false;
            }
        }

        bool success = DoTextureCreateView(cmd.self, cmd.descriptor, &resultData->handle);

        if (!success) {
            return false;
        }

        return true;
    }

    bool Server::HandleTextureDestroy(DeserializeBuffer* deserializeBuffer) {
        TextureDestroyCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoTextureDestroy(cmd.self);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleTextureSetLabel(DeserializeBuffer* deserializeBuffer) {
        TextureSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoTextureSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    bool Server::HandleTextureViewSetLabel(DeserializeBuffer* deserializeBuffer) {
        TextureViewSetLabelCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mAllocator, *this);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        bool success = DoTextureViewSetLabel(cmd.self, cmd.label);

        if (!success) {
            return false;
        }
        return true;
    }

    const volatile char* Server::HandleCommandsImpl(const volatile char* commands, size_t size) {
        DeserializeBuffer deserializeBuffer(commands, size);

        while (deserializeBuffer.AvailableSize() >= sizeof(CmdHeader) + sizeof(WireCmd)) {
            // Start by chunked command handling, if it is done, then it means the whole buffer
            // was consumed by it, so we return a pointer to the end of the commands.
            switch (HandleChunkedCommands(deserializeBuffer.Buffer(), deserializeBuffer.AvailableSize())) {
                case ChunkedCommandsResult::Consumed:
                    return commands + size;
                case ChunkedCommandsResult::Error:
                    return nullptr;
                case ChunkedCommandsResult::Passthrough:
                    break;
            }

            WireCmd cmdId = *static_cast<const volatile WireCmd*>(static_cast<const volatile void*>(
                deserializeBuffer.Buffer() + sizeof(CmdHeader)));
            bool success = false;
            switch (cmdId) {
                case WireCmd::AdapterRequestDevice:
                    success = HandleAdapterRequestDevice(&deserializeBuffer);
                    break;
                case WireCmd::BindGroupLayoutSetLabel:
                    success = HandleBindGroupLayoutSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::BindGroupSetLabel:
                    success = HandleBindGroupSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::BufferDestroy:
                    success = HandleBufferDestroy(&deserializeBuffer);
                    break;
                case WireCmd::BufferMapAsync:
                    success = HandleBufferMapAsync(&deserializeBuffer);
                    break;
                case WireCmd::BufferSetLabel:
                    success = HandleBufferSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::BufferUnmap:
                    success = HandleBufferUnmap(&deserializeBuffer);
                    break;
                case WireCmd::BufferUpdateMappedData:
                    success = HandleBufferUpdateMappedData(&deserializeBuffer);
                    break;
                case WireCmd::CommandBufferSetLabel:
                    success = HandleCommandBufferSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderBeginComputePass:
                    success = HandleCommandEncoderBeginComputePass(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderBeginRenderPass:
                    success = HandleCommandEncoderBeginRenderPass(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderClearBuffer:
                    success = HandleCommandEncoderClearBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyBufferToBuffer:
                    success = HandleCommandEncoderCopyBufferToBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyBufferToTexture:
                    success = HandleCommandEncoderCopyBufferToTexture(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyTextureToBuffer:
                    success = HandleCommandEncoderCopyTextureToBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyTextureToTexture:
                    success = HandleCommandEncoderCopyTextureToTexture(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyTextureToTextureInternal:
                    success = HandleCommandEncoderCopyTextureToTextureInternal(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderFinish:
                    success = HandleCommandEncoderFinish(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderInjectValidationError:
                    success = HandleCommandEncoderInjectValidationError(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderInsertDebugMarker:
                    success = HandleCommandEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderPopDebugGroup:
                    success = HandleCommandEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderPushDebugGroup:
                    success = HandleCommandEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderResolveQuerySet:
                    success = HandleCommandEncoderResolveQuerySet(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderSetLabel:
                    success = HandleCommandEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderWriteBuffer:
                    success = HandleCommandEncoderWriteBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderWriteTimestamp:
                    success = HandleCommandEncoderWriteTimestamp(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderDispatch:
                    success = HandleComputePassEncoderDispatch(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderDispatchIndirect:
                    success = HandleComputePassEncoderDispatchIndirect(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderEndPass:
                    success = HandleComputePassEncoderEndPass(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderInsertDebugMarker:
                    success = HandleComputePassEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderPopDebugGroup:
                    success = HandleComputePassEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderPushDebugGroup:
                    success = HandleComputePassEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderSetBindGroup:
                    success = HandleComputePassEncoderSetBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderSetLabel:
                    success = HandleComputePassEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderSetPipeline:
                    success = HandleComputePassEncoderSetPipeline(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderWriteTimestamp:
                    success = HandleComputePassEncoderWriteTimestamp(&deserializeBuffer);
                    break;
                case WireCmd::ComputePipelineGetBindGroupLayout:
                    success = HandleComputePipelineGetBindGroupLayout(&deserializeBuffer);
                    break;
                case WireCmd::ComputePipelineSetLabel:
                    success = HandleComputePipelineSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::DestroyObject:
                    success = HandleDestroyObject(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateBindGroup:
                    success = HandleDeviceCreateBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateBindGroupLayout:
                    success = HandleDeviceCreateBindGroupLayout(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateBuffer:
                    success = HandleDeviceCreateBuffer(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateCommandEncoder:
                    success = HandleDeviceCreateCommandEncoder(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateComputePipeline:
                    success = HandleDeviceCreateComputePipeline(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateComputePipelineAsync:
                    success = HandleDeviceCreateComputePipelineAsync(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateErrorBuffer:
                    success = HandleDeviceCreateErrorBuffer(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateExternalTexture:
                    success = HandleDeviceCreateExternalTexture(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreatePipelineLayout:
                    success = HandleDeviceCreatePipelineLayout(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateQuerySet:
                    success = HandleDeviceCreateQuerySet(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateRenderBundleEncoder:
                    success = HandleDeviceCreateRenderBundleEncoder(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateRenderPipeline:
                    success = HandleDeviceCreateRenderPipeline(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateRenderPipelineAsync:
                    success = HandleDeviceCreateRenderPipelineAsync(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateSampler:
                    success = HandleDeviceCreateSampler(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateShaderModule:
                    success = HandleDeviceCreateShaderModule(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateSwapChain:
                    success = HandleDeviceCreateSwapChain(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateTexture:
                    success = HandleDeviceCreateTexture(&deserializeBuffer);
                    break;
                case WireCmd::DeviceDestroy:
                    success = HandleDeviceDestroy(&deserializeBuffer);
                    break;
                case WireCmd::DeviceGetQueue:
                    success = HandleDeviceGetQueue(&deserializeBuffer);
                    break;
                case WireCmd::DeviceInjectError:
                    success = HandleDeviceInjectError(&deserializeBuffer);
                    break;
                case WireCmd::DeviceLoseForTesting:
                    success = HandleDeviceLoseForTesting(&deserializeBuffer);
                    break;
                case WireCmd::DevicePopErrorScope:
                    success = HandleDevicePopErrorScope(&deserializeBuffer);
                    break;
                case WireCmd::DevicePushErrorScope:
                    success = HandleDevicePushErrorScope(&deserializeBuffer);
                    break;
                case WireCmd::DeviceTick:
                    success = HandleDeviceTick(&deserializeBuffer);
                    break;
                case WireCmd::ExternalTextureDestroy:
                    success = HandleExternalTextureDestroy(&deserializeBuffer);
                    break;
                case WireCmd::ExternalTextureSetLabel:
                    success = HandleExternalTextureSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::InstanceCreateSurface:
                    success = HandleInstanceCreateSurface(&deserializeBuffer);
                    break;
                case WireCmd::InstanceRequestAdapter:
                    success = HandleInstanceRequestAdapter(&deserializeBuffer);
                    break;
                case WireCmd::PipelineLayoutSetLabel:
                    success = HandlePipelineLayoutSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::QuerySetDestroy:
                    success = HandleQuerySetDestroy(&deserializeBuffer);
                    break;
                case WireCmd::QuerySetSetLabel:
                    success = HandleQuerySetSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::QueueCopyTextureForBrowser:
                    success = HandleQueueCopyTextureForBrowser(&deserializeBuffer);
                    break;
                case WireCmd::QueueOnSubmittedWorkDone:
                    success = HandleQueueOnSubmittedWorkDone(&deserializeBuffer);
                    break;
                case WireCmd::QueueSubmit:
                    success = HandleQueueSubmit(&deserializeBuffer);
                    break;
                case WireCmd::QueueWriteBuffer:
                    success = HandleQueueWriteBuffer(&deserializeBuffer);
                    break;
                case WireCmd::QueueWriteTexture:
                    success = HandleQueueWriteTexture(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDraw:
                    success = HandleRenderBundleEncoderDraw(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndexed:
                    success = HandleRenderBundleEncoderDrawIndexed(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndexedIndirect:
                    success = HandleRenderBundleEncoderDrawIndexedIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndirect:
                    success = HandleRenderBundleEncoderDrawIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderFinish:
                    success = HandleRenderBundleEncoderFinish(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderInsertDebugMarker:
                    success = HandleRenderBundleEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderPopDebugGroup:
                    success = HandleRenderBundleEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderPushDebugGroup:
                    success = HandleRenderBundleEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetBindGroup:
                    success = HandleRenderBundleEncoderSetBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetIndexBuffer:
                    success = HandleRenderBundleEncoderSetIndexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetLabel:
                    success = HandleRenderBundleEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetPipeline:
                    success = HandleRenderBundleEncoderSetPipeline(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetVertexBuffer:
                    success = HandleRenderBundleEncoderSetVertexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderBeginOcclusionQuery:
                    success = HandleRenderPassEncoderBeginOcclusionQuery(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDraw:
                    success = HandleRenderPassEncoderDraw(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDrawIndexed:
                    success = HandleRenderPassEncoderDrawIndexed(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDrawIndexedIndirect:
                    success = HandleRenderPassEncoderDrawIndexedIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDrawIndirect:
                    success = HandleRenderPassEncoderDrawIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderEndOcclusionQuery:
                    success = HandleRenderPassEncoderEndOcclusionQuery(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderEndPass:
                    success = HandleRenderPassEncoderEndPass(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderExecuteBundles:
                    success = HandleRenderPassEncoderExecuteBundles(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderInsertDebugMarker:
                    success = HandleRenderPassEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderPopDebugGroup:
                    success = HandleRenderPassEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderPushDebugGroup:
                    success = HandleRenderPassEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetBindGroup:
                    success = HandleRenderPassEncoderSetBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetBlendConstant:
                    success = HandleRenderPassEncoderSetBlendConstant(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetIndexBuffer:
                    success = HandleRenderPassEncoderSetIndexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetLabel:
                    success = HandleRenderPassEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetPipeline:
                    success = HandleRenderPassEncoderSetPipeline(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetScissorRect:
                    success = HandleRenderPassEncoderSetScissorRect(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetStencilReference:
                    success = HandleRenderPassEncoderSetStencilReference(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetVertexBuffer:
                    success = HandleRenderPassEncoderSetVertexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetViewport:
                    success = HandleRenderPassEncoderSetViewport(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderWriteTimestamp:
                    success = HandleRenderPassEncoderWriteTimestamp(&deserializeBuffer);
                    break;
                case WireCmd::RenderPipelineGetBindGroupLayout:
                    success = HandleRenderPipelineGetBindGroupLayout(&deserializeBuffer);
                    break;
                case WireCmd::RenderPipelineSetLabel:
                    success = HandleRenderPipelineSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::SamplerSetLabel:
                    success = HandleSamplerSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::ShaderModuleGetCompilationInfo:
                    success = HandleShaderModuleGetCompilationInfo(&deserializeBuffer);
                    break;
                case WireCmd::ShaderModuleSetLabel:
                    success = HandleShaderModuleSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::SwapChainConfigure:
                    success = HandleSwapChainConfigure(&deserializeBuffer);
                    break;
                case WireCmd::SwapChainGetCurrentTextureView:
                    success = HandleSwapChainGetCurrentTextureView(&deserializeBuffer);
                    break;
                case WireCmd::SwapChainPresent:
                    success = HandleSwapChainPresent(&deserializeBuffer);
                    break;
                case WireCmd::TextureCreateView:
                    success = HandleTextureCreateView(&deserializeBuffer);
                    break;
                case WireCmd::TextureDestroy:
                    success = HandleTextureDestroy(&deserializeBuffer);
                    break;
                case WireCmd::TextureSetLabel:
                    success = HandleTextureSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::TextureViewSetLabel:
                    success = HandleTextureViewSetLabel(&deserializeBuffer);
                    break;
                default:
                    success = false;
            }

            if (!success) {
                return nullptr;
            }
            mAllocator.Reset();
        }

        if (deserializeBuffer.AvailableSize() != 0) {
            return nullptr;
        }

        return commands;
    }

}}  // namespace dawn_wire::server
