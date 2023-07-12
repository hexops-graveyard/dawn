
#include "dawn/common/Assert.h"
#include "dawn/wire/server/Server.h"

namespace dawn::wire::server {

    WireResult Server::HandleAdapterGetInstance(DeserializeBuffer* deserializeBuffer) {
        AdapterGetInstanceCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUInstance> resultData;
        WIRE_TRY(InstanceObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoAdapterGetInstance(cmd.self, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleAdapterRequestDevice(DeserializeBuffer* deserializeBuffer) {
        AdapterRequestDeviceCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        Known<WGPUAdapter> adapterIdHandle;
        WIRE_TRY(AdapterObjects().Get(cmd.adapterId, &adapterIdHandle));WIRE_TRY(DoAdapterRequestDevice(adapterIdHandle, cmd.requestSerial, cmd.deviceObjectHandle, cmd.descriptor));
        return WireResult::Success;
    }

    WireResult Server::HandleBindGroupLayoutSetLabel(DeserializeBuffer* deserializeBuffer) {
        BindGroupLayoutSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoBindGroupLayoutSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleBindGroupSetLabel(DeserializeBuffer* deserializeBuffer) {
        BindGroupSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoBindGroupSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleBufferDestroy(DeserializeBuffer* deserializeBuffer) {
        BufferDestroyCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        WIRE_TRY(PreHandleBufferDestroy(cmd));
WIRE_TRY(DoBufferDestroy(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleBufferMapAsync(DeserializeBuffer* deserializeBuffer) {
        BufferMapAsyncCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator));

        Known<WGPUBuffer> bufferIdHandle;
        WIRE_TRY(BufferObjects().Get(cmd.bufferId, &bufferIdHandle));WIRE_TRY(DoBufferMapAsync(bufferIdHandle, cmd.requestSerial, cmd.mode, cmd.offset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleBufferSetLabel(DeserializeBuffer* deserializeBuffer) {
        BufferSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoBufferSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleBufferUnmap(DeserializeBuffer* deserializeBuffer) {
        BufferUnmapCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        WIRE_TRY(PreHandleBufferUnmap(cmd));
WIRE_TRY(DoBufferUnmap(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleBufferUpdateMappedData(DeserializeBuffer* deserializeBuffer) {
        BufferUpdateMappedDataCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator));

        Known<WGPUBuffer> bufferIdHandle;
        WIRE_TRY(BufferObjects().Get(cmd.bufferId, &bufferIdHandle));WIRE_TRY(DoBufferUpdateMappedData(bufferIdHandle, cmd.writeDataUpdateInfoLength, cmd.writeDataUpdateInfo, cmd.offset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandBufferSetLabel(DeserializeBuffer* deserializeBuffer) {
        CommandBufferSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandBufferSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderBeginComputePass(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderBeginComputePassCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUComputePassEncoder> resultData;
        WIRE_TRY(ComputePassEncoderObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoCommandEncoderBeginComputePass(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderBeginRenderPass(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderBeginRenderPassCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPURenderPassEncoder> resultData;
        WIRE_TRY(RenderPassEncoderObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoCommandEncoderBeginRenderPass(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderClearBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderClearBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderClearBuffer(cmd.self, cmd.buffer, cmd.offset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderCopyBufferToBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyBufferToBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderCopyBufferToBuffer(cmd.self, cmd.source, cmd.sourceOffset, cmd.destination, cmd.destinationOffset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderCopyBufferToTexture(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyBufferToTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderCopyBufferToTexture(cmd.self, cmd.source, cmd.destination, cmd.copySize));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderCopyTextureToBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyTextureToBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderCopyTextureToBuffer(cmd.self, cmd.source, cmd.destination, cmd.copySize));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderCopyTextureToTexture(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyTextureToTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderCopyTextureToTexture(cmd.self, cmd.source, cmd.destination, cmd.copySize));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderCopyTextureToTextureInternal(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderCopyTextureToTextureInternalCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderCopyTextureToTextureInternal(cmd.self, cmd.source, cmd.destination, cmd.copySize));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderFinish(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderFinishCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUCommandBuffer> resultData;
        WIRE_TRY(CommandBufferObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoCommandEncoderFinish(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderInjectValidationError(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderInjectValidationErrorCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderInjectValidationError(cmd.self, cmd.message));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderInsertDebugMarkerCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderInsertDebugMarker(cmd.self, cmd.markerLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderPopDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderPopDebugGroup(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderPushDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderPushDebugGroup(cmd.self, cmd.groupLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderResolveQuerySet(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderResolveQuerySetCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderResolveQuerySet(cmd.self, cmd.querySet, cmd.firstQuery, cmd.queryCount, cmd.destination, cmd.destinationOffset));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderWriteBuffer(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderWriteBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderWriteBuffer(cmd.self, cmd.buffer, cmd.bufferOffset, cmd.data, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleCommandEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer) {
        CommandEncoderWriteTimestampCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoCommandEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderDispatchWorkgroups(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderDispatchWorkgroupsCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderDispatchWorkgroups(cmd.self, cmd.workgroupCountX, cmd.workgroupCountY, cmd.workgroupCountZ));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderDispatchWorkgroupsIndirect(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderDispatchWorkgroupsIndirectCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderDispatchWorkgroupsIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderEnd(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderEndCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderEnd(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderInsertDebugMarkerCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderInsertDebugMarker(cmd.self, cmd.markerLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderPopDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderPopDebugGroup(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderPushDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderPushDebugGroup(cmd.self, cmd.groupLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderSetBindGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderSetPipelineCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderSetPipeline(cmd.self, cmd.pipeline));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer) {
        ComputePassEncoderWriteTimestampCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePassEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex));
        return WireResult::Success;
    }

    WireResult Server::HandleComputePipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer) {
        ComputePipelineGetBindGroupLayoutCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUBindGroupLayout> resultData;
        WIRE_TRY(BindGroupLayoutObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoComputePipelineGetBindGroupLayout(cmd.self, cmd.groupIndex, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleComputePipelineSetLabel(DeserializeBuffer* deserializeBuffer) {
        ComputePipelineSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoComputePipelineSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleDestroyObject(DeserializeBuffer* deserializeBuffer) {
        DestroyObjectCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator));

WIRE_TRY(DoDestroyObject(cmd.objectType, cmd.objectId));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateBindGroup(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateBindGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUBindGroup> resultData;
        WIRE_TRY(BindGroupObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateBindGroup(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateBindGroupLayout(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateBindGroupLayoutCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUBindGroupLayout> resultData;
        WIRE_TRY(BindGroupLayoutObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateBindGroupLayout(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateBuffer(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        Known<WGPUDevice> deviceIdHandle;
        WIRE_TRY(DeviceObjects().Get(cmd.deviceId, &deviceIdHandle));WIRE_TRY(DoDeviceCreateBuffer(deviceIdHandle, cmd.descriptor, cmd.result, cmd.readHandleCreateInfoLength, cmd.readHandleCreateInfo, cmd.writeHandleCreateInfoLength, cmd.writeHandleCreateInfo));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateCommandEncoder(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateCommandEncoderCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUCommandEncoder> resultData;
        WIRE_TRY(CommandEncoderObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateCommandEncoder(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateComputePipeline(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateComputePipelineCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUComputePipeline> resultData;
        WIRE_TRY(ComputePipelineObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateComputePipeline(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateComputePipelineAsync(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateComputePipelineAsyncCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        Known<WGPUDevice> deviceIdHandle;
        WIRE_TRY(DeviceObjects().Get(cmd.deviceId, &deviceIdHandle));WIRE_TRY(DoDeviceCreateComputePipelineAsync(deviceIdHandle, cmd.requestSerial, cmd.pipelineObjectHandle, cmd.descriptor));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateErrorBuffer(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateErrorBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUBuffer> resultData;
        WIRE_TRY(BufferObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateErrorBuffer(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateErrorExternalTexture(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateErrorExternalTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUExternalTexture> resultData;
        WIRE_TRY(ExternalTextureObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateErrorExternalTexture(cmd.self, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateErrorShaderModule(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateErrorShaderModuleCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUShaderModule> resultData;
        WIRE_TRY(ShaderModuleObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateErrorShaderModule(cmd.self, cmd.descriptor, cmd.errorMessage, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateErrorTexture(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateErrorTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUTexture> resultData;
        WIRE_TRY(TextureObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateErrorTexture(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateExternalTexture(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateExternalTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUExternalTexture> resultData;
        WIRE_TRY(ExternalTextureObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateExternalTexture(cmd.self, cmd.externalTextureDescriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreatePipelineLayout(DeserializeBuffer* deserializeBuffer) {
        DeviceCreatePipelineLayoutCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUPipelineLayout> resultData;
        WIRE_TRY(PipelineLayoutObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreatePipelineLayout(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateQuerySet(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateQuerySetCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUQuerySet> resultData;
        WIRE_TRY(QuerySetObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateQuerySet(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateRenderBundleEncoder(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateRenderBundleEncoderCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPURenderBundleEncoder> resultData;
        WIRE_TRY(RenderBundleEncoderObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateRenderBundleEncoder(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateRenderPipeline(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateRenderPipelineCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPURenderPipeline> resultData;
        WIRE_TRY(RenderPipelineObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateRenderPipeline(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateRenderPipelineAsync(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateRenderPipelineAsyncCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        Known<WGPUDevice> deviceIdHandle;
        WIRE_TRY(DeviceObjects().Get(cmd.deviceId, &deviceIdHandle));WIRE_TRY(DoDeviceCreateRenderPipelineAsync(deviceIdHandle, cmd.requestSerial, cmd.pipelineObjectHandle, cmd.descriptor));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateSampler(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateSamplerCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUSampler> resultData;
        WIRE_TRY(SamplerObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateSampler(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateShaderModule(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateShaderModuleCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUShaderModule> resultData;
        WIRE_TRY(ShaderModuleObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateShaderModule(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateSwapChain(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateSwapChainCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUSwapChain> resultData;
        WIRE_TRY(SwapChainObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateSwapChain(cmd.self, cmd.surface, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceCreateTexture(DeserializeBuffer* deserializeBuffer) {
        DeviceCreateTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUTexture> resultData;
        WIRE_TRY(TextureObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceCreateTexture(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceDestroy(DeserializeBuffer* deserializeBuffer) {
        DeviceDestroyCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoDeviceDestroy(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceForceLoss(DeserializeBuffer* deserializeBuffer) {
        DeviceForceLossCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoDeviceForceLoss(cmd.self, cmd.type, cmd.message));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceGetAdapter(DeserializeBuffer* deserializeBuffer) {
        DeviceGetAdapterCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUAdapter> resultData;
        WIRE_TRY(AdapterObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceGetAdapter(cmd.self, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceGetQueue(DeserializeBuffer* deserializeBuffer) {
        DeviceGetQueueCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUQueue> resultData;
        WIRE_TRY(QueueObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoDeviceGetQueue(cmd.self, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleDeviceInjectError(DeserializeBuffer* deserializeBuffer) {
        DeviceInjectErrorCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoDeviceInjectError(cmd.self, cmd.type, cmd.message));
        return WireResult::Success;
    }

    WireResult Server::HandleDevicePopErrorScope(DeserializeBuffer* deserializeBuffer) {
        DevicePopErrorScopeCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator));

        Known<WGPUDevice> deviceIdHandle;
        WIRE_TRY(DeviceObjects().Get(cmd.deviceId, &deviceIdHandle));WIRE_TRY(DoDevicePopErrorScope(deviceIdHandle, cmd.requestSerial));
        return WireResult::Success;
    }

    WireResult Server::HandleDevicePushErrorScope(DeserializeBuffer* deserializeBuffer) {
        DevicePushErrorScopeCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoDevicePushErrorScope(cmd.self, cmd.filter));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceSetLabel(DeserializeBuffer* deserializeBuffer) {
        DeviceSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoDeviceSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceTick(DeserializeBuffer* deserializeBuffer) {
        DeviceTickCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoDeviceTick(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleDeviceValidateTextureDescriptor(DeserializeBuffer* deserializeBuffer) {
        DeviceValidateTextureDescriptorCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoDeviceValidateTextureDescriptor(cmd.self, cmd.descriptor));
        return WireResult::Success;
    }

    WireResult Server::HandleExternalTextureDestroy(DeserializeBuffer* deserializeBuffer) {
        ExternalTextureDestroyCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoExternalTextureDestroy(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleExternalTextureExpire(DeserializeBuffer* deserializeBuffer) {
        ExternalTextureExpireCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoExternalTextureExpire(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleExternalTextureRefresh(DeserializeBuffer* deserializeBuffer) {
        ExternalTextureRefreshCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoExternalTextureRefresh(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleExternalTextureSetLabel(DeserializeBuffer* deserializeBuffer) {
        ExternalTextureSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoExternalTextureSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleInstanceCreateSurface(DeserializeBuffer* deserializeBuffer) {
        InstanceCreateSurfaceCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUSurface> resultData;
        WIRE_TRY(SurfaceObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoInstanceCreateSurface(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleInstanceProcessEvents(DeserializeBuffer* deserializeBuffer) {
        InstanceProcessEventsCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoInstanceProcessEvents(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleInstanceRequestAdapter(DeserializeBuffer* deserializeBuffer) {
        InstanceRequestAdapterCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        Known<WGPUInstance> instanceIdHandle;
        WIRE_TRY(InstanceObjects().Get(cmd.instanceId, &instanceIdHandle));WIRE_TRY(DoInstanceRequestAdapter(instanceIdHandle, cmd.requestSerial, cmd.adapterObjectHandle, cmd.options));
        return WireResult::Success;
    }

    WireResult Server::HandlePipelineLayoutSetLabel(DeserializeBuffer* deserializeBuffer) {
        PipelineLayoutSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoPipelineLayoutSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleQuerySetDestroy(DeserializeBuffer* deserializeBuffer) {
        QuerySetDestroyCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoQuerySetDestroy(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleQuerySetSetLabel(DeserializeBuffer* deserializeBuffer) {
        QuerySetSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoQuerySetSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleQueueCopyExternalTextureForBrowser(DeserializeBuffer* deserializeBuffer) {
        QueueCopyExternalTextureForBrowserCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoQueueCopyExternalTextureForBrowser(cmd.self, cmd.source, cmd.destination, cmd.copySize, cmd.options));
        return WireResult::Success;
    }

    WireResult Server::HandleQueueCopyTextureForBrowser(DeserializeBuffer* deserializeBuffer) {
        QueueCopyTextureForBrowserCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoQueueCopyTextureForBrowser(cmd.self, cmd.source, cmd.destination, cmd.copySize, cmd.options));
        return WireResult::Success;
    }

    WireResult Server::HandleQueueOnSubmittedWorkDone(DeserializeBuffer* deserializeBuffer) {
        QueueOnSubmittedWorkDoneCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator));

        Known<WGPUQueue> queueIdHandle;
        WIRE_TRY(QueueObjects().Get(cmd.queueId, &queueIdHandle));WIRE_TRY(DoQueueOnSubmittedWorkDone(queueIdHandle, cmd.signalValue, cmd.requestSerial));
        return WireResult::Success;
    }

    WireResult Server::HandleQueueSetLabel(DeserializeBuffer* deserializeBuffer) {
        QueueSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoQueueSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleQueueSubmit(DeserializeBuffer* deserializeBuffer) {
        QueueSubmitCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoQueueSubmit(cmd.self, cmd.commandCount, cmd.commands));
        return WireResult::Success;
    }

    WireResult Server::HandleQueueWriteBuffer(DeserializeBuffer* deserializeBuffer) {
        QueueWriteBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator));

        Known<WGPUQueue> queueIdHandle;
        WIRE_TRY(QueueObjects().Get(cmd.queueId, &queueIdHandle));        Known<WGPUBuffer> bufferIdHandle;
        WIRE_TRY(BufferObjects().Get(cmd.bufferId, &bufferIdHandle));WIRE_TRY(DoQueueWriteBuffer(queueIdHandle, bufferIdHandle, cmd.bufferOffset, cmd.data, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleQueueWriteTexture(DeserializeBuffer* deserializeBuffer) {
        QueueWriteTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

        Known<WGPUQueue> queueIdHandle;
        WIRE_TRY(QueueObjects().Get(cmd.queueId, &queueIdHandle));WIRE_TRY(DoQueueWriteTexture(queueIdHandle, cmd.destination, cmd.data, cmd.dataSize, cmd.dataLayout, cmd.writeSize));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderDraw(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderDraw(cmd.self, cmd.vertexCount, cmd.instanceCount, cmd.firstVertex, cmd.firstInstance));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawIndexedCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderDrawIndexed(cmd.self, cmd.indexCount, cmd.instanceCount, cmd.firstIndex, cmd.baseVertex, cmd.firstInstance));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawIndexedIndirectCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderDrawIndexedIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderDrawIndirectCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderDrawIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderFinish(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderFinishCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPURenderBundle> resultData;
        WIRE_TRY(RenderBundleObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoRenderBundleEncoderFinish(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderInsertDebugMarkerCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderInsertDebugMarker(cmd.self, cmd.markerLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderPopDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderPopDebugGroup(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderPushDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderPushDebugGroup(cmd.self, cmd.groupLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetBindGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetIndexBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderSetIndexBuffer(cmd.self, cmd.buffer, cmd.format, cmd.offset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderSetPipeline(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetPipelineCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderSetPipeline(cmd.self, cmd.pipeline));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderBundleEncoderSetVertexBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleEncoderSetVertexBuffer(cmd.self, cmd.slot, cmd.buffer, cmd.offset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderBundleSetLabel(DeserializeBuffer* deserializeBuffer) {
        RenderBundleSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderBundleSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderBeginOcclusionQuery(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderBeginOcclusionQueryCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderBeginOcclusionQuery(cmd.self, cmd.queryIndex));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderDraw(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderDraw(cmd.self, cmd.vertexCount, cmd.instanceCount, cmd.firstVertex, cmd.firstInstance));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderDrawIndexed(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawIndexedCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderDrawIndexed(cmd.self, cmd.indexCount, cmd.instanceCount, cmd.firstIndex, cmd.baseVertex, cmd.firstInstance));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderDrawIndexedIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawIndexedIndirectCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderDrawIndexedIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderDrawIndirect(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderDrawIndirectCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderDrawIndirect(cmd.self, cmd.indirectBuffer, cmd.indirectOffset));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderEnd(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderEndCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderEnd(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderEndOcclusionQuery(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderEndOcclusionQueryCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderEndOcclusionQuery(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderExecuteBundles(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderExecuteBundlesCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderExecuteBundles(cmd.self, cmd.bundleCount, cmd.bundles));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderInsertDebugMarker(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderInsertDebugMarkerCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderInsertDebugMarker(cmd.self, cmd.markerLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderPopDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderPopDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderPopDebugGroup(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderPushDebugGroup(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderPushDebugGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderPushDebugGroup(cmd.self, cmd.groupLabel));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetBindGroup(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetBindGroupCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetBindGroup(cmd.self, cmd.groupIndex, cmd.group, cmd.dynamicOffsetCount, cmd.dynamicOffsets));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetBlendConstant(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetBlendConstantCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetBlendConstant(cmd.self, cmd.color));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetIndexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetIndexBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetIndexBuffer(cmd.self, cmd.buffer, cmd.format, cmd.offset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetLabel(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetPipeline(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetPipelineCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetPipeline(cmd.self, cmd.pipeline));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetScissorRect(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetScissorRectCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetScissorRect(cmd.self, cmd.x, cmd.y, cmd.width, cmd.height));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetStencilReference(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetStencilReferenceCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetStencilReference(cmd.self, cmd.reference));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetVertexBuffer(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetVertexBufferCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetVertexBuffer(cmd.self, cmd.slot, cmd.buffer, cmd.offset, cmd.size));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderSetViewport(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderSetViewportCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderSetViewport(cmd.self, cmd.x, cmd.y, cmd.width, cmd.height, cmd.minDepth, cmd.maxDepth));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPassEncoderWriteTimestamp(DeserializeBuffer* deserializeBuffer) {
        RenderPassEncoderWriteTimestampCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPassEncoderWriteTimestamp(cmd.self, cmd.querySet, cmd.queryIndex));
        return WireResult::Success;
    }

    WireResult Server::HandleRenderPipelineGetBindGroupLayout(DeserializeBuffer* deserializeBuffer) {
        RenderPipelineGetBindGroupLayoutCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUBindGroupLayout> resultData;
        WIRE_TRY(BindGroupLayoutObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoRenderPipelineGetBindGroupLayout(cmd.self, cmd.groupIndex, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleRenderPipelineSetLabel(DeserializeBuffer* deserializeBuffer) {
        RenderPipelineSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoRenderPipelineSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleSamplerSetLabel(DeserializeBuffer* deserializeBuffer) {
        SamplerSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoSamplerSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleShaderModuleGetCompilationInfo(DeserializeBuffer* deserializeBuffer) {
        ShaderModuleGetCompilationInfoCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator));

        Known<WGPUShaderModule> shaderModuleIdHandle;
        WIRE_TRY(ShaderModuleObjects().Get(cmd.shaderModuleId, &shaderModuleIdHandle));WIRE_TRY(DoShaderModuleGetCompilationInfo(shaderModuleIdHandle, cmd.requestSerial));
        return WireResult::Success;
    }

    WireResult Server::HandleShaderModuleSetLabel(DeserializeBuffer* deserializeBuffer) {
        ShaderModuleSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoShaderModuleSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleSwapChainGetCurrentTexture(DeserializeBuffer* deserializeBuffer) {
        SwapChainGetCurrentTextureCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUTexture> resultData;
        WIRE_TRY(TextureObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoSwapChainGetCurrentTexture(cmd.self, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleSwapChainGetCurrentTextureView(DeserializeBuffer* deserializeBuffer) {
        SwapChainGetCurrentTextureViewCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUTextureView> resultData;
        WIRE_TRY(TextureViewObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoSwapChainGetCurrentTextureView(cmd.self, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleSwapChainPresent(DeserializeBuffer* deserializeBuffer) {
        SwapChainPresentCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoSwapChainPresent(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleTextureCreateView(DeserializeBuffer* deserializeBuffer) {
        TextureCreateViewCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));



        Known<WGPUTextureView> resultData;
        WIRE_TRY(TextureViewObjects().Allocate(&resultData, cmd.result));
        resultData->generation = cmd.result.generation;
WIRE_TRY(DoTextureCreateView(cmd.self, cmd.descriptor, &resultData->handle));

        return WireResult::Success;
    }

    WireResult Server::HandleTextureDestroy(DeserializeBuffer* deserializeBuffer) {
        TextureDestroyCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoTextureDestroy(cmd.self));
        return WireResult::Success;
    }

    WireResult Server::HandleTextureSetLabel(DeserializeBuffer* deserializeBuffer) {
        TextureSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoTextureSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
    }

    WireResult Server::HandleTextureViewSetLabel(DeserializeBuffer* deserializeBuffer) {
        TextureViewSetLabelCmd cmd;
        WIRE_TRY(cmd.Deserialize(deserializeBuffer, &mAllocator, *this));

WIRE_TRY(DoTextureViewSetLabel(cmd.self, cmd.label));
        return WireResult::Success;
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
            WireResult result;
            switch (cmdId) {
                case WireCmd::AdapterGetInstance:
                    result = HandleAdapterGetInstance(&deserializeBuffer);
                    break;
                case WireCmd::AdapterRequestDevice:
                    result = HandleAdapterRequestDevice(&deserializeBuffer);
                    break;
                case WireCmd::BindGroupLayoutSetLabel:
                    result = HandleBindGroupLayoutSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::BindGroupSetLabel:
                    result = HandleBindGroupSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::BufferDestroy:
                    result = HandleBufferDestroy(&deserializeBuffer);
                    break;
                case WireCmd::BufferMapAsync:
                    result = HandleBufferMapAsync(&deserializeBuffer);
                    break;
                case WireCmd::BufferSetLabel:
                    result = HandleBufferSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::BufferUnmap:
                    result = HandleBufferUnmap(&deserializeBuffer);
                    break;
                case WireCmd::BufferUpdateMappedData:
                    result = HandleBufferUpdateMappedData(&deserializeBuffer);
                    break;
                case WireCmd::CommandBufferSetLabel:
                    result = HandleCommandBufferSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderBeginComputePass:
                    result = HandleCommandEncoderBeginComputePass(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderBeginRenderPass:
                    result = HandleCommandEncoderBeginRenderPass(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderClearBuffer:
                    result = HandleCommandEncoderClearBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyBufferToBuffer:
                    result = HandleCommandEncoderCopyBufferToBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyBufferToTexture:
                    result = HandleCommandEncoderCopyBufferToTexture(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyTextureToBuffer:
                    result = HandleCommandEncoderCopyTextureToBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyTextureToTexture:
                    result = HandleCommandEncoderCopyTextureToTexture(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderCopyTextureToTextureInternal:
                    result = HandleCommandEncoderCopyTextureToTextureInternal(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderFinish:
                    result = HandleCommandEncoderFinish(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderInjectValidationError:
                    result = HandleCommandEncoderInjectValidationError(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderInsertDebugMarker:
                    result = HandleCommandEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderPopDebugGroup:
                    result = HandleCommandEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderPushDebugGroup:
                    result = HandleCommandEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderResolveQuerySet:
                    result = HandleCommandEncoderResolveQuerySet(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderSetLabel:
                    result = HandleCommandEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderWriteBuffer:
                    result = HandleCommandEncoderWriteBuffer(&deserializeBuffer);
                    break;
                case WireCmd::CommandEncoderWriteTimestamp:
                    result = HandleCommandEncoderWriteTimestamp(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderDispatchWorkgroups:
                    result = HandleComputePassEncoderDispatchWorkgroups(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderDispatchWorkgroupsIndirect:
                    result = HandleComputePassEncoderDispatchWorkgroupsIndirect(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderEnd:
                    result = HandleComputePassEncoderEnd(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderInsertDebugMarker:
                    result = HandleComputePassEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderPopDebugGroup:
                    result = HandleComputePassEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderPushDebugGroup:
                    result = HandleComputePassEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderSetBindGroup:
                    result = HandleComputePassEncoderSetBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderSetLabel:
                    result = HandleComputePassEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderSetPipeline:
                    result = HandleComputePassEncoderSetPipeline(&deserializeBuffer);
                    break;
                case WireCmd::ComputePassEncoderWriteTimestamp:
                    result = HandleComputePassEncoderWriteTimestamp(&deserializeBuffer);
                    break;
                case WireCmd::ComputePipelineGetBindGroupLayout:
                    result = HandleComputePipelineGetBindGroupLayout(&deserializeBuffer);
                    break;
                case WireCmd::ComputePipelineSetLabel:
                    result = HandleComputePipelineSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::DestroyObject:
                    result = HandleDestroyObject(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateBindGroup:
                    result = HandleDeviceCreateBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateBindGroupLayout:
                    result = HandleDeviceCreateBindGroupLayout(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateBuffer:
                    result = HandleDeviceCreateBuffer(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateCommandEncoder:
                    result = HandleDeviceCreateCommandEncoder(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateComputePipeline:
                    result = HandleDeviceCreateComputePipeline(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateComputePipelineAsync:
                    result = HandleDeviceCreateComputePipelineAsync(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateErrorBuffer:
                    result = HandleDeviceCreateErrorBuffer(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateErrorExternalTexture:
                    result = HandleDeviceCreateErrorExternalTexture(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateErrorShaderModule:
                    result = HandleDeviceCreateErrorShaderModule(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateErrorTexture:
                    result = HandleDeviceCreateErrorTexture(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateExternalTexture:
                    result = HandleDeviceCreateExternalTexture(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreatePipelineLayout:
                    result = HandleDeviceCreatePipelineLayout(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateQuerySet:
                    result = HandleDeviceCreateQuerySet(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateRenderBundleEncoder:
                    result = HandleDeviceCreateRenderBundleEncoder(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateRenderPipeline:
                    result = HandleDeviceCreateRenderPipeline(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateRenderPipelineAsync:
                    result = HandleDeviceCreateRenderPipelineAsync(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateSampler:
                    result = HandleDeviceCreateSampler(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateShaderModule:
                    result = HandleDeviceCreateShaderModule(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateSwapChain:
                    result = HandleDeviceCreateSwapChain(&deserializeBuffer);
                    break;
                case WireCmd::DeviceCreateTexture:
                    result = HandleDeviceCreateTexture(&deserializeBuffer);
                    break;
                case WireCmd::DeviceDestroy:
                    result = HandleDeviceDestroy(&deserializeBuffer);
                    break;
                case WireCmd::DeviceForceLoss:
                    result = HandleDeviceForceLoss(&deserializeBuffer);
                    break;
                case WireCmd::DeviceGetAdapter:
                    result = HandleDeviceGetAdapter(&deserializeBuffer);
                    break;
                case WireCmd::DeviceGetQueue:
                    result = HandleDeviceGetQueue(&deserializeBuffer);
                    break;
                case WireCmd::DeviceInjectError:
                    result = HandleDeviceInjectError(&deserializeBuffer);
                    break;
                case WireCmd::DevicePopErrorScope:
                    result = HandleDevicePopErrorScope(&deserializeBuffer);
                    break;
                case WireCmd::DevicePushErrorScope:
                    result = HandleDevicePushErrorScope(&deserializeBuffer);
                    break;
                case WireCmd::DeviceSetLabel:
                    result = HandleDeviceSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::DeviceTick:
                    result = HandleDeviceTick(&deserializeBuffer);
                    break;
                case WireCmd::DeviceValidateTextureDescriptor:
                    result = HandleDeviceValidateTextureDescriptor(&deserializeBuffer);
                    break;
                case WireCmd::ExternalTextureDestroy:
                    result = HandleExternalTextureDestroy(&deserializeBuffer);
                    break;
                case WireCmd::ExternalTextureExpire:
                    result = HandleExternalTextureExpire(&deserializeBuffer);
                    break;
                case WireCmd::ExternalTextureRefresh:
                    result = HandleExternalTextureRefresh(&deserializeBuffer);
                    break;
                case WireCmd::ExternalTextureSetLabel:
                    result = HandleExternalTextureSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::InstanceCreateSurface:
                    result = HandleInstanceCreateSurface(&deserializeBuffer);
                    break;
                case WireCmd::InstanceProcessEvents:
                    result = HandleInstanceProcessEvents(&deserializeBuffer);
                    break;
                case WireCmd::InstanceRequestAdapter:
                    result = HandleInstanceRequestAdapter(&deserializeBuffer);
                    break;
                case WireCmd::PipelineLayoutSetLabel:
                    result = HandlePipelineLayoutSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::QuerySetDestroy:
                    result = HandleQuerySetDestroy(&deserializeBuffer);
                    break;
                case WireCmd::QuerySetSetLabel:
                    result = HandleQuerySetSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::QueueCopyExternalTextureForBrowser:
                    result = HandleQueueCopyExternalTextureForBrowser(&deserializeBuffer);
                    break;
                case WireCmd::QueueCopyTextureForBrowser:
                    result = HandleQueueCopyTextureForBrowser(&deserializeBuffer);
                    break;
                case WireCmd::QueueOnSubmittedWorkDone:
                    result = HandleQueueOnSubmittedWorkDone(&deserializeBuffer);
                    break;
                case WireCmd::QueueSetLabel:
                    result = HandleQueueSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::QueueSubmit:
                    result = HandleQueueSubmit(&deserializeBuffer);
                    break;
                case WireCmd::QueueWriteBuffer:
                    result = HandleQueueWriteBuffer(&deserializeBuffer);
                    break;
                case WireCmd::QueueWriteTexture:
                    result = HandleQueueWriteTexture(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDraw:
                    result = HandleRenderBundleEncoderDraw(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndexed:
                    result = HandleRenderBundleEncoderDrawIndexed(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndexedIndirect:
                    result = HandleRenderBundleEncoderDrawIndexedIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderDrawIndirect:
                    result = HandleRenderBundleEncoderDrawIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderFinish:
                    result = HandleRenderBundleEncoderFinish(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderInsertDebugMarker:
                    result = HandleRenderBundleEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderPopDebugGroup:
                    result = HandleRenderBundleEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderPushDebugGroup:
                    result = HandleRenderBundleEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetBindGroup:
                    result = HandleRenderBundleEncoderSetBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetIndexBuffer:
                    result = HandleRenderBundleEncoderSetIndexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetLabel:
                    result = HandleRenderBundleEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetPipeline:
                    result = HandleRenderBundleEncoderSetPipeline(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleEncoderSetVertexBuffer:
                    result = HandleRenderBundleEncoderSetVertexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderBundleSetLabel:
                    result = HandleRenderBundleSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderBeginOcclusionQuery:
                    result = HandleRenderPassEncoderBeginOcclusionQuery(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDraw:
                    result = HandleRenderPassEncoderDraw(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDrawIndexed:
                    result = HandleRenderPassEncoderDrawIndexed(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDrawIndexedIndirect:
                    result = HandleRenderPassEncoderDrawIndexedIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderDrawIndirect:
                    result = HandleRenderPassEncoderDrawIndirect(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderEnd:
                    result = HandleRenderPassEncoderEnd(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderEndOcclusionQuery:
                    result = HandleRenderPassEncoderEndOcclusionQuery(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderExecuteBundles:
                    result = HandleRenderPassEncoderExecuteBundles(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderInsertDebugMarker:
                    result = HandleRenderPassEncoderInsertDebugMarker(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderPopDebugGroup:
                    result = HandleRenderPassEncoderPopDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderPushDebugGroup:
                    result = HandleRenderPassEncoderPushDebugGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetBindGroup:
                    result = HandleRenderPassEncoderSetBindGroup(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetBlendConstant:
                    result = HandleRenderPassEncoderSetBlendConstant(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetIndexBuffer:
                    result = HandleRenderPassEncoderSetIndexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetLabel:
                    result = HandleRenderPassEncoderSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetPipeline:
                    result = HandleRenderPassEncoderSetPipeline(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetScissorRect:
                    result = HandleRenderPassEncoderSetScissorRect(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetStencilReference:
                    result = HandleRenderPassEncoderSetStencilReference(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetVertexBuffer:
                    result = HandleRenderPassEncoderSetVertexBuffer(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderSetViewport:
                    result = HandleRenderPassEncoderSetViewport(&deserializeBuffer);
                    break;
                case WireCmd::RenderPassEncoderWriteTimestamp:
                    result = HandleRenderPassEncoderWriteTimestamp(&deserializeBuffer);
                    break;
                case WireCmd::RenderPipelineGetBindGroupLayout:
                    result = HandleRenderPipelineGetBindGroupLayout(&deserializeBuffer);
                    break;
                case WireCmd::RenderPipelineSetLabel:
                    result = HandleRenderPipelineSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::SamplerSetLabel:
                    result = HandleSamplerSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::ShaderModuleGetCompilationInfo:
                    result = HandleShaderModuleGetCompilationInfo(&deserializeBuffer);
                    break;
                case WireCmd::ShaderModuleSetLabel:
                    result = HandleShaderModuleSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::SwapChainGetCurrentTexture:
                    result = HandleSwapChainGetCurrentTexture(&deserializeBuffer);
                    break;
                case WireCmd::SwapChainGetCurrentTextureView:
                    result = HandleSwapChainGetCurrentTextureView(&deserializeBuffer);
                    break;
                case WireCmd::SwapChainPresent:
                    result = HandleSwapChainPresent(&deserializeBuffer);
                    break;
                case WireCmd::TextureCreateView:
                    result = HandleTextureCreateView(&deserializeBuffer);
                    break;
                case WireCmd::TextureDestroy:
                    result = HandleTextureDestroy(&deserializeBuffer);
                    break;
                case WireCmd::TextureSetLabel:
                    result = HandleTextureSetLabel(&deserializeBuffer);
                    break;
                case WireCmd::TextureViewSetLabel:
                    result = HandleTextureViewSetLabel(&deserializeBuffer);
                    break;
                default:
                    result = WireResult::FatalError;
            }

            if (result != WireResult::Success) {
                return nullptr;
            }
            mAllocator.Reset();
        }

        if (deserializeBuffer.AvailableSize() != 0) {
            return nullptr;
        }

        return commands;
    }

}  // namespace dawn::wire::server
