
#include "dawn/common/Assert.h"
#include "dawn/wire/client/Client.h"

#include <string>

namespace dawn::wire::client {
    bool Client::HandleAdapterRequestDeviceCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnAdapterRequestDeviceCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Adapter* adapter = Get<Adapter>(cmd.adapter.id);
        if (adapter != nullptr && adapter->GetWireGeneration() != cmd.adapter.generation) {
            adapter = nullptr;
        }

        return DoAdapterRequestDeviceCallback(adapter, cmd.requestSerial, cmd.status, cmd.message, cmd.limits, cmd.featuresCount, cmd.features);
    }
    bool Client::HandleBufferMapAsyncCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnBufferMapAsyncCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Buffer* buffer = Get<Buffer>(cmd.buffer.id);
        if (buffer != nullptr && buffer->GetWireGeneration() != cmd.buffer.generation) {
            buffer = nullptr;
        }

        return DoBufferMapAsyncCallback(buffer, cmd.requestSerial, cmd.status, cmd.readDataUpdateInfoLength, cmd.readDataUpdateInfo);
    }
    bool Client::HandleDeviceCreateComputePipelineAsyncCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnDeviceCreateComputePipelineAsyncCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Device* device = Get<Device>(cmd.device.id);
        if (device != nullptr && device->GetWireGeneration() != cmd.device.generation) {
            device = nullptr;
        }

        return DoDeviceCreateComputePipelineAsyncCallback(device, cmd.requestSerial, cmd.status, cmd.message);
    }
    bool Client::HandleDeviceCreateRenderPipelineAsyncCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnDeviceCreateRenderPipelineAsyncCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Device* device = Get<Device>(cmd.device.id);
        if (device != nullptr && device->GetWireGeneration() != cmd.device.generation) {
            device = nullptr;
        }

        return DoDeviceCreateRenderPipelineAsyncCallback(device, cmd.requestSerial, cmd.status, cmd.message);
    }
    bool Client::HandleDeviceLoggingCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnDeviceLoggingCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Device* device = Get<Device>(cmd.device.id);
        if (device != nullptr && device->GetWireGeneration() != cmd.device.generation) {
            device = nullptr;
        }

        return DoDeviceLoggingCallback(device, cmd.type, cmd.message);
    }
    bool Client::HandleDeviceLostCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnDeviceLostCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Device* device = Get<Device>(cmd.device.id);
        if (device != nullptr && device->GetWireGeneration() != cmd.device.generation) {
            device = nullptr;
        }

        return DoDeviceLostCallback(device, cmd.reason, cmd.message);
    }
    bool Client::HandleDevicePopErrorScopeCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnDevicePopErrorScopeCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Device* device = Get<Device>(cmd.device.id);
        if (device != nullptr && device->GetWireGeneration() != cmd.device.generation) {
            device = nullptr;
        }

        return DoDevicePopErrorScopeCallback(device, cmd.requestSerial, cmd.type, cmd.message);
    }
    bool Client::HandleDeviceUncapturedErrorCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnDeviceUncapturedErrorCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Device* device = Get<Device>(cmd.device.id);
        if (device != nullptr && device->GetWireGeneration() != cmd.device.generation) {
            device = nullptr;
        }

        return DoDeviceUncapturedErrorCallback(device, cmd.type, cmd.message);
    }
    bool Client::HandleInstanceRequestAdapterCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnInstanceRequestAdapterCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Instance* instance = Get<Instance>(cmd.instance.id);
        if (instance != nullptr && instance->GetWireGeneration() != cmd.instance.generation) {
            instance = nullptr;
        }

        return DoInstanceRequestAdapterCallback(instance, cmd.requestSerial, cmd.status, cmd.message, cmd.properties, cmd.limits, cmd.featuresCount, cmd.features);
    }
    bool Client::HandleQueueWorkDoneCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnQueueWorkDoneCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        Queue* queue = Get<Queue>(cmd.queue.id);
        if (queue != nullptr && queue->GetWireGeneration() != cmd.queue.generation) {
            queue = nullptr;
        }

        return DoQueueWorkDoneCallback(queue, cmd.requestSerial, cmd.status);
    }
    bool Client::HandleShaderModuleGetCompilationInfoCallback(DeserializeBuffer* deserializeBuffer) {
        ReturnShaderModuleGetCompilationInfoCallbackCmd cmd;
        WireResult deserializeResult = cmd.Deserialize(deserializeBuffer, &mWireCommandAllocator);

        if (deserializeResult == WireResult::FatalError) {
            return false;
        }


        ShaderModule* shaderModule = Get<ShaderModule>(cmd.shaderModule.id);
        if (shaderModule != nullptr && shaderModule->GetWireGeneration() != cmd.shaderModule.generation) {
            shaderModule = nullptr;
        }

        return DoShaderModuleGetCompilationInfoCallback(shaderModule, cmd.requestSerial, cmd.status, cmd.info);
    }

    const volatile char* Client::HandleCommandsImpl(const volatile char* commands, size_t size) {
        DeserializeBuffer deserializeBuffer(commands, size);

        while (deserializeBuffer.AvailableSize() >= sizeof(CmdHeader) + sizeof(ReturnWireCmd)) {
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

            ReturnWireCmd cmdId = *static_cast<const volatile ReturnWireCmd*>(static_cast<const volatile void*>(
                deserializeBuffer.Buffer() + sizeof(CmdHeader)));
            bool success = false;
            switch (cmdId) {
                case ReturnWireCmd::AdapterRequestDeviceCallback:
                    success = HandleAdapterRequestDeviceCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::BufferMapAsyncCallback:
                    success = HandleBufferMapAsyncCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::DeviceCreateComputePipelineAsyncCallback:
                    success = HandleDeviceCreateComputePipelineAsyncCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::DeviceCreateRenderPipelineAsyncCallback:
                    success = HandleDeviceCreateRenderPipelineAsyncCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::DeviceLoggingCallback:
                    success = HandleDeviceLoggingCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::DeviceLostCallback:
                    success = HandleDeviceLostCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::DevicePopErrorScopeCallback:
                    success = HandleDevicePopErrorScopeCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::DeviceUncapturedErrorCallback:
                    success = HandleDeviceUncapturedErrorCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::InstanceRequestAdapterCallback:
                    success = HandleInstanceRequestAdapterCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::QueueWorkDoneCallback:
                    success = HandleQueueWorkDoneCallback(&deserializeBuffer);
                    break;
                case ReturnWireCmd::ShaderModuleGetCompilationInfoCallback:
                    success = HandleShaderModuleGetCompilationInfoCallback(&deserializeBuffer);
                    break;
                default:
                    success = false;
            }

            if (!success) {
                return nullptr;
            }
            mWireCommandAllocator.Reset();
        }

        if (deserializeBuffer.AvailableSize() != 0) {
            return nullptr;
        }

        return commands;
    }
}  // namespace dawn::wire::client
