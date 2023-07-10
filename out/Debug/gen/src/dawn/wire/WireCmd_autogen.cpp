
#include "dawn/wire/WireCmd_autogen.h"

#include "dawn/common/Assert.h"
#include "dawn/common/Log.h"
#include "dawn/common/Numeric.h"
#include "dawn/wire/BufferConsumer_impl.h"
#include "dawn/wire/Wire.h"

#include <algorithm>
#include <cstring>
#include <limits>

#ifdef __GNUC__
// error: 'offsetof' within non-standard-layout type 'wgpu::XXX' is conditionally-supported
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

namespace dawn::wire {
namespace {

// Allocates enough space from allocator to countain T[count] and return it in out.
// Return FatalError if the allocator couldn't allocate the memory.
// Always writes to |out| on success.
template <typename T, typename N>
WireResult GetSpace(DeserializeAllocator* allocator, N count, T** out) {
    // Because we use this function extensively when `count` == 1, we can optimize the
    // size computations a bit more for those cases via constexpr version of the
    // alignment computation.
    constexpr size_t kSizeofT = WireAlignSizeof<T>();
    size_t size = 0;
    if (count == 1) {
      size = kSizeofT;
    } else {
      auto sizeN = WireAlignSizeofN<T>(count);
      // A size of 0 indicates an overflow, so return an error.
      if (!sizeN) {
        return WireResult::FatalError;
      }
      size = *sizeN;
    }

    *out = static_cast<T*>(allocator->GetSpace(size));
    if (*out == nullptr) {
        return WireResult::FatalError;
    }

    return WireResult::Success;
}

struct WGPUChainedStructTransfer {
    WGPUSType sType;
    bool hasNext;
};

size_t GetChainedStructExtraRequiredSize(const WGPUChainedStruct* chainedStruct);
[[nodiscard]] WireResult SerializeChainedStruct(const WGPUChainedStruct* chainedStruct,
                                                  SerializeBuffer* buffer,
                                                  const ObjectIdProvider& provider);
WireResult DeserializeChainedStruct(const WGPUChainedStruct** outChainNext,
                                    DeserializeBuffer* deserializeBuffer,
                                    DeserializeAllocator* allocator,
                                    const ObjectIdResolver& resolver);

size_t GetChainedStructExtraRequiredSize(WGPUChainedStructOut* chainedStruct);
[[nodiscard]] WireResult SerializeChainedStruct(WGPUChainedStructOut* chainedStruct,
                                                  SerializeBuffer* buffer,
                                                  const ObjectIdProvider& provider);
WireResult DeserializeChainedStruct(WGPUChainedStructOut** outChainNext,
                                    DeserializeBuffer* deserializeBuffer,
                                    DeserializeAllocator* allocator,
                                    const ObjectIdResolver& resolver);


struct WGPUAdapterPropertiesTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t vendorID;
    uint64_t vendorNameStrlen;
    uint64_t architectureStrlen;
    uint32_t deviceID;
    uint64_t nameStrlen;
    uint64_t driverDescriptionStrlen;
    WGPUAdapterType adapterType;
    WGPUBackendType backendType;
    bool compatibilityMode;
};


DAWN_DECLARE_UNUSED size_t WGPUAdapterPropertiesGetExtraRequiredSize(const WGPUAdapterProperties& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    ASSERT(record.vendorName != nullptr);
    result += Align(std::strlen(record.vendorName), kWireBufferAlignment);
    ASSERT(record.architecture != nullptr);
    result += Align(std::strlen(record.architecture), kWireBufferAlignment);
    ASSERT(record.name != nullptr);
    result += Align(std::strlen(record.name), kWireBufferAlignment);
    ASSERT(record.driverDescription != nullptr);
    result += Align(std::strlen(record.driverDescription), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUAdapterPropertiesGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUAdapterPropertiesSerialize(
    const WGPUAdapterProperties& record,
    WGPUAdapterPropertiesTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->vendorID = record.vendorID;
    transfer->deviceID = record.deviceID;
    transfer->adapterType = record.adapterType;
    transfer->backendType = record.backendType;
    transfer->compatibilityMode = record.compatibilityMode;
    {
        transfer->vendorNameStrlen = std::strlen(record.vendorName);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->vendorNameStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.vendorName, transfer->vendorNameStrlen);
    }
    {
        transfer->architectureStrlen = std::strlen(record.architecture);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->architectureStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.architecture, transfer->architectureStrlen);
    }
    {
        transfer->nameStrlen = std::strlen(record.name);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->nameStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.name, transfer->nameStrlen);
    }
    {
        transfer->driverDescriptionStrlen = std::strlen(record.driverDescription);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->driverDescriptionStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.driverDescription, transfer->driverDescriptionStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUAdapterPropertiesSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUAdapterPropertiesDeserialize(
    WGPUAdapterProperties* record,
    const volatile WGPUAdapterPropertiesTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->vendorID) >= sizeof(transfer->vendorID), "Deserialize assignment may not narrow.");
    record->vendorID = transfer->vendorID;
    static_assert(sizeof(record->deviceID) >= sizeof(transfer->deviceID), "Deserialize assignment may not narrow.");
    record->deviceID = transfer->deviceID;
    static_assert(sizeof(record->adapterType) >= sizeof(transfer->adapterType), "Deserialize assignment may not narrow.");
    record->adapterType = transfer->adapterType;
    static_assert(sizeof(record->backendType) >= sizeof(transfer->backendType), "Deserialize assignment may not narrow.");
    record->backendType = transfer->backendType;
    static_assert(sizeof(record->compatibilityMode) >= sizeof(transfer->compatibilityMode), "Deserialize assignment may not narrow.");
    record->compatibilityMode = transfer->compatibilityMode;
    {
        uint64_t stringLength64 = transfer->vendorNameStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->vendorName = copiedString;
    }
    {
        uint64_t stringLength64 = transfer->architectureStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->architecture = copiedString;
    }
    {
        uint64_t stringLength64 = transfer->nameStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->name = copiedString;
    }
    {
        uint64_t stringLength64 = transfer->driverDescriptionStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->driverDescription = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUAdapterPropertiesDeserialize);

struct WGPUBindGroupEntryTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t binding;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;
    ObjectId sampler;
    ObjectId textureView;
};


DAWN_DECLARE_UNUSED size_t WGPUBindGroupEntryGetExtraRequiredSize(const WGPUBindGroupEntry& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupEntryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupEntrySerialize(
    const WGPUBindGroupEntry& record,
    WGPUBindGroupEntryTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->binding = record.binding;
    WIRE_TRY(provider.GetOptionalId(record.buffer, &transfer->buffer));
    transfer->offset = record.offset;
    transfer->size = record.size;
    WIRE_TRY(provider.GetOptionalId(record.sampler, &transfer->sampler));
    WIRE_TRY(provider.GetOptionalId(record.textureView, &transfer->textureView));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupEntrySerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupEntryDeserialize(
    WGPUBindGroupEntry* record,
    const volatile WGPUBindGroupEntryTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->binding) >= sizeof(transfer->binding), "Deserialize assignment may not narrow.");
    record->binding = transfer->binding;
    WIRE_TRY(resolver.GetOptionalFromId(transfer->buffer, &record->buffer));
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;
    WIRE_TRY(resolver.GetOptionalFromId(transfer->sampler, &record->sampler));
    WIRE_TRY(resolver.GetOptionalFromId(transfer->textureView, &record->textureView));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupEntryDeserialize);

struct WGPUBlendComponentTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    WGPUBlendOperation operation;
    WGPUBlendFactor srcFactor;
    WGPUBlendFactor dstFactor;
};


DAWN_DECLARE_UNUSED size_t WGPUBlendComponentGetExtraRequiredSize(const WGPUBlendComponent& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBlendComponentGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBlendComponentSerialize(
    const WGPUBlendComponent& record,
    WGPUBlendComponentTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->operation = record.operation;
    transfer->srcFactor = record.srcFactor;
    transfer->dstFactor = record.dstFactor;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBlendComponentSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBlendComponentDeserialize(
    WGPUBlendComponent* record,
    const volatile WGPUBlendComponentTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->operation) >= sizeof(transfer->operation), "Deserialize assignment may not narrow.");
    record->operation = transfer->operation;
    static_assert(sizeof(record->srcFactor) >= sizeof(transfer->srcFactor), "Deserialize assignment may not narrow.");
    record->srcFactor = transfer->srcFactor;
    static_assert(sizeof(record->dstFactor) >= sizeof(transfer->dstFactor), "Deserialize assignment may not narrow.");
    record->dstFactor = transfer->dstFactor;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBlendComponentDeserialize);

struct WGPUBufferBindingLayoutTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUBufferBindingType type;
    bool hasDynamicOffset;
    uint64_t minBindingSize;
};


DAWN_DECLARE_UNUSED size_t WGPUBufferBindingLayoutGetExtraRequiredSize(const WGPUBufferBindingLayout& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBufferBindingLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBufferBindingLayoutSerialize(
    const WGPUBufferBindingLayout& record,
    WGPUBufferBindingLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->type = record.type;
    transfer->hasDynamicOffset = record.hasDynamicOffset;
    transfer->minBindingSize = record.minBindingSize;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBufferBindingLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBufferBindingLayoutDeserialize(
    WGPUBufferBindingLayout* record,
    const volatile WGPUBufferBindingLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    static_assert(sizeof(record->hasDynamicOffset) >= sizeof(transfer->hasDynamicOffset), "Deserialize assignment may not narrow.");
    record->hasDynamicOffset = transfer->hasDynamicOffset;
    static_assert(sizeof(record->minBindingSize) >= sizeof(transfer->minBindingSize), "Deserialize assignment may not narrow.");
    record->minBindingSize = transfer->minBindingSize;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBufferBindingLayoutDeserialize);

struct WGPUBufferDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    WGPUBufferUsageFlags usage;
    uint64_t size;
    bool mappedAtCreation;
};


DAWN_DECLARE_UNUSED size_t WGPUBufferDescriptorGetExtraRequiredSize(const WGPUBufferDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBufferDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBufferDescriptorSerialize(
    const WGPUBufferDescriptor& record,
    WGPUBufferDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->usage = record.usage;
    transfer->size = record.size;
    transfer->mappedAtCreation = record.mappedAtCreation;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBufferDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBufferDescriptorDeserialize(
    WGPUBufferDescriptor* record,
    const volatile WGPUBufferDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->usage) >= sizeof(transfer->usage), "Deserialize assignment may not narrow.");
    record->usage = transfer->usage;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;
    static_assert(sizeof(record->mappedAtCreation) >= sizeof(transfer->mappedAtCreation), "Deserialize assignment may not narrow.");
    record->mappedAtCreation = transfer->mappedAtCreation;
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBufferDescriptorDeserialize);

struct WGPUColorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    double r;
    double g;
    double b;
    double a;
};


DAWN_DECLARE_UNUSED size_t WGPUColorGetExtraRequiredSize(const WGPUColor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUColorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUColorSerialize(
    const WGPUColor& record,
    WGPUColorTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->r = record.r;
    transfer->g = record.g;
    transfer->b = record.b;
    transfer->a = record.a;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUColorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUColorDeserialize(
    WGPUColor* record,
    const volatile WGPUColorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->r) >= sizeof(transfer->r), "Deserialize assignment may not narrow.");
    record->r = transfer->r;
    static_assert(sizeof(record->g) >= sizeof(transfer->g), "Deserialize assignment may not narrow.");
    record->g = transfer->g;
    static_assert(sizeof(record->b) >= sizeof(transfer->b), "Deserialize assignment may not narrow.");
    record->b = transfer->b;
    static_assert(sizeof(record->a) >= sizeof(transfer->a), "Deserialize assignment may not narrow.");
    record->a = transfer->a;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUColorDeserialize);

struct WGPUCommandBufferDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
};


DAWN_DECLARE_UNUSED size_t WGPUCommandBufferDescriptorGetExtraRequiredSize(const WGPUCommandBufferDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUCommandBufferDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUCommandBufferDescriptorSerialize(
    const WGPUCommandBufferDescriptor& record,
    WGPUCommandBufferDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCommandBufferDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUCommandBufferDescriptorDeserialize(
    WGPUCommandBufferDescriptor* record,
    const volatile WGPUCommandBufferDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCommandBufferDescriptorDeserialize);

struct WGPUCommandEncoderDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
};


DAWN_DECLARE_UNUSED size_t WGPUCommandEncoderDescriptorGetExtraRequiredSize(const WGPUCommandEncoderDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUCommandEncoderDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUCommandEncoderDescriptorSerialize(
    const WGPUCommandEncoderDescriptor& record,
    WGPUCommandEncoderDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCommandEncoderDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUCommandEncoderDescriptorDeserialize(
    WGPUCommandEncoderDescriptor* record,
    const volatile WGPUCommandEncoderDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCommandEncoderDescriptorDeserialize);

struct WGPUCompilationMessageTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t messageStrlen;
    bool has_message;
    WGPUCompilationMessageType type;
    uint64_t lineNum;
    uint64_t linePos;
    uint64_t offset;
    uint64_t length;
    uint64_t utf16LinePos;
    uint64_t utf16Offset;
    uint64_t utf16Length;
};


DAWN_DECLARE_UNUSED size_t WGPUCompilationMessageGetExtraRequiredSize(const WGPUCompilationMessage& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.message != nullptr) {
        result += Align(std::strlen(record.message), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUCompilationMessageGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUCompilationMessageSerialize(
    const WGPUCompilationMessage& record,
    WGPUCompilationMessageTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->type = record.type;
    transfer->lineNum = record.lineNum;
    transfer->linePos = record.linePos;
    transfer->offset = record.offset;
    transfer->length = record.length;
    transfer->utf16LinePos = record.utf16LinePos;
    transfer->utf16Offset = record.utf16Offset;
    transfer->utf16Length = record.utf16Length;
    bool has_message = record.message != nullptr;
    transfer->has_message = has_message;
    if (has_message) {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCompilationMessageSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUCompilationMessageDeserialize(
    WGPUCompilationMessage* record,
    const volatile WGPUCompilationMessageTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    static_assert(sizeof(record->lineNum) >= sizeof(transfer->lineNum), "Deserialize assignment may not narrow.");
    record->lineNum = transfer->lineNum;
    static_assert(sizeof(record->linePos) >= sizeof(transfer->linePos), "Deserialize assignment may not narrow.");
    record->linePos = transfer->linePos;
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->length) >= sizeof(transfer->length), "Deserialize assignment may not narrow.");
    record->length = transfer->length;
    static_assert(sizeof(record->utf16LinePos) >= sizeof(transfer->utf16LinePos), "Deserialize assignment may not narrow.");
    record->utf16LinePos = transfer->utf16LinePos;
    static_assert(sizeof(record->utf16Offset) >= sizeof(transfer->utf16Offset), "Deserialize assignment may not narrow.");
    record->utf16Offset = transfer->utf16Offset;
    static_assert(sizeof(record->utf16Length) >= sizeof(transfer->utf16Length), "Deserialize assignment may not narrow.");
    record->utf16Length = transfer->utf16Length;
    bool has_message = transfer->has_message;
    record->message = nullptr;
    if (has_message) {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCompilationMessageDeserialize);

struct WGPUComputePassTimestampWriteTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    ObjectId querySet;
    uint32_t queryIndex;
    WGPUComputePassTimestampLocation location;
};


DAWN_DECLARE_UNUSED size_t WGPUComputePassTimestampWriteGetExtraRequiredSize(const WGPUComputePassTimestampWrite& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUComputePassTimestampWriteGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUComputePassTimestampWriteSerialize(
    const WGPUComputePassTimestampWrite& record,
    WGPUComputePassTimestampWriteTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    WIRE_TRY(provider.GetId(record.querySet, &transfer->querySet));
    transfer->queryIndex = record.queryIndex;
    transfer->location = record.location;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePassTimestampWriteSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUComputePassTimestampWriteDeserialize(
    WGPUComputePassTimestampWrite* record,
    const volatile WGPUComputePassTimestampWriteTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);



    WIRE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    static_assert(sizeof(record->queryIndex) >= sizeof(transfer->queryIndex), "Deserialize assignment may not narrow.");
    record->queryIndex = transfer->queryIndex;
    static_assert(sizeof(record->location) >= sizeof(transfer->location), "Deserialize assignment may not narrow.");
    record->location = transfer->location;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePassTimestampWriteDeserialize);

struct WGPUConstantEntryTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t keyStrlen;
    double value;
};


DAWN_DECLARE_UNUSED size_t WGPUConstantEntryGetExtraRequiredSize(const WGPUConstantEntry& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    ASSERT(record.key != nullptr);
    result += Align(std::strlen(record.key), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUConstantEntryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUConstantEntrySerialize(
    const WGPUConstantEntry& record,
    WGPUConstantEntryTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->value = record.value;
    {
        transfer->keyStrlen = std::strlen(record.key);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->keyStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.key, transfer->keyStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUConstantEntrySerialize);

DAWN_DECLARE_UNUSED WireResult WGPUConstantEntryDeserialize(
    WGPUConstantEntry* record,
    const volatile WGPUConstantEntryTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->value) >= sizeof(transfer->value), "Deserialize assignment may not narrow.");
    record->value = transfer->value;
    {
        uint64_t stringLength64 = transfer->keyStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->key = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUConstantEntryDeserialize);

struct WGPUCopyTextureForBrowserOptionsTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    bool flipY;
    bool needsColorSpaceConversion;
    WGPUAlphaMode srcAlphaMode;
    bool has_srcTransferFunctionParameters;
    bool has_conversionMatrix;
    bool has_dstTransferFunctionParameters;
    WGPUAlphaMode dstAlphaMode;
    bool internalUsage;
};


DAWN_DECLARE_UNUSED size_t WGPUCopyTextureForBrowserOptionsGetExtraRequiredSize(const WGPUCopyTextureForBrowserOptions& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.srcTransferFunctionParameters != nullptr) {
        auto memberLength = 7u;
        auto size = WireAlignSizeofN<float>(memberLength);
        ASSERT(size);
        result += *size;
    }
    if (record.conversionMatrix != nullptr) {
        auto memberLength = 9u;
        auto size = WireAlignSizeofN<float>(memberLength);
        ASSERT(size);
        result += *size;
    }
    if (record.dstTransferFunctionParameters != nullptr) {
        auto memberLength = 7u;
        auto size = WireAlignSizeofN<float>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUCopyTextureForBrowserOptionsGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUCopyTextureForBrowserOptionsSerialize(
    const WGPUCopyTextureForBrowserOptions& record,
    WGPUCopyTextureForBrowserOptionsTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->flipY = record.flipY;
    transfer->needsColorSpaceConversion = record.needsColorSpaceConversion;
    transfer->srcAlphaMode = record.srcAlphaMode;
    transfer->dstAlphaMode = record.dstAlphaMode;
    transfer->internalUsage = record.internalUsage;
    bool has_srcTransferFunctionParameters = record.srcTransferFunctionParameters != nullptr;
    transfer->has_srcTransferFunctionParameters = has_srcTransferFunctionParameters;
    if (has_srcTransferFunctionParameters) {
        auto memberLength = 7u;

        float* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.srcTransferFunctionParameters,
            sizeof(float) * memberLength);
    }
    bool has_conversionMatrix = record.conversionMatrix != nullptr;
    transfer->has_conversionMatrix = has_conversionMatrix;
    if (has_conversionMatrix) {
        auto memberLength = 9u;

        float* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.conversionMatrix,
            sizeof(float) * memberLength);
    }
    bool has_dstTransferFunctionParameters = record.dstTransferFunctionParameters != nullptr;
    transfer->has_dstTransferFunctionParameters = has_dstTransferFunctionParameters;
    if (has_dstTransferFunctionParameters) {
        auto memberLength = 7u;

        float* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.dstTransferFunctionParameters,
            sizeof(float) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCopyTextureForBrowserOptionsSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUCopyTextureForBrowserOptionsDeserialize(
    WGPUCopyTextureForBrowserOptions* record,
    const volatile WGPUCopyTextureForBrowserOptionsTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->flipY) >= sizeof(transfer->flipY), "Deserialize assignment may not narrow.");
    record->flipY = transfer->flipY;
    static_assert(sizeof(record->needsColorSpaceConversion) >= sizeof(transfer->needsColorSpaceConversion), "Deserialize assignment may not narrow.");
    record->needsColorSpaceConversion = transfer->needsColorSpaceConversion;
    static_assert(sizeof(record->srcAlphaMode) >= sizeof(transfer->srcAlphaMode), "Deserialize assignment may not narrow.");
    record->srcAlphaMode = transfer->srcAlphaMode;
    static_assert(sizeof(record->dstAlphaMode) >= sizeof(transfer->dstAlphaMode), "Deserialize assignment may not narrow.");
    record->dstAlphaMode = transfer->dstAlphaMode;
    static_assert(sizeof(record->internalUsage) >= sizeof(transfer->internalUsage), "Deserialize assignment may not narrow.");
    record->internalUsage = transfer->internalUsage;
    bool has_srcTransferFunctionParameters = transfer->has_srcTransferFunctionParameters;
    record->srcTransferFunctionParameters = nullptr;
    if (has_srcTransferFunctionParameters) {
        auto memberLength = 7u;
        const volatile float* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        float* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->srcTransferFunctionParameters = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const float*>(memberBuffer),
           sizeof(float) * memberLength);
    }
    bool has_conversionMatrix = transfer->has_conversionMatrix;
    record->conversionMatrix = nullptr;
    if (has_conversionMatrix) {
        auto memberLength = 9u;
        const volatile float* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        float* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->conversionMatrix = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const float*>(memberBuffer),
           sizeof(float) * memberLength);
    }
    bool has_dstTransferFunctionParameters = transfer->has_dstTransferFunctionParameters;
    record->dstTransferFunctionParameters = nullptr;
    if (has_dstTransferFunctionParameters) {
        auto memberLength = 7u;
        const volatile float* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        float* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dstTransferFunctionParameters = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const float*>(memberBuffer),
           sizeof(float) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCopyTextureForBrowserOptionsDeserialize);

struct WGPUDawnAdapterPropertiesPowerPreferenceTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    WGPUPowerPreference powerPreference;
};

static_assert(offsetof(WGPUDawnAdapterPropertiesPowerPreferenceTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUDawnAdapterPropertiesPowerPreferenceGetExtraRequiredSize(const WGPUDawnAdapterPropertiesPowerPreference& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDawnAdapterPropertiesPowerPreferenceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnAdapterPropertiesPowerPreferenceSerialize(
    const WGPUDawnAdapterPropertiesPowerPreference& record,
    WGPUDawnAdapterPropertiesPowerPreferenceTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_DawnAdapterPropertiesPowerPreference);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->powerPreference = record.powerPreference;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnAdapterPropertiesPowerPreferenceSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnAdapterPropertiesPowerPreferenceDeserialize(
    WGPUDawnAdapterPropertiesPowerPreference* record,
    const volatile WGPUDawnAdapterPropertiesPowerPreferenceTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_DawnAdapterPropertiesPowerPreference);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->powerPreference) >= sizeof(transfer->powerPreference), "Deserialize assignment may not narrow.");
    record->powerPreference = transfer->powerPreference;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnAdapterPropertiesPowerPreferenceDeserialize);

struct WGPUDawnBufferDescriptorErrorInfoFromWireClientTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    bool outOfMemory;
};

static_assert(offsetof(WGPUDawnBufferDescriptorErrorInfoFromWireClientTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUDawnBufferDescriptorErrorInfoFromWireClientGetExtraRequiredSize(const WGPUDawnBufferDescriptorErrorInfoFromWireClient& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDawnBufferDescriptorErrorInfoFromWireClientGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnBufferDescriptorErrorInfoFromWireClientSerialize(
    const WGPUDawnBufferDescriptorErrorInfoFromWireClient& record,
    WGPUDawnBufferDescriptorErrorInfoFromWireClientTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->outOfMemory = record.outOfMemory;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnBufferDescriptorErrorInfoFromWireClientSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnBufferDescriptorErrorInfoFromWireClientDeserialize(
    WGPUDawnBufferDescriptorErrorInfoFromWireClient* record,
    const volatile WGPUDawnBufferDescriptorErrorInfoFromWireClientTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->outOfMemory) >= sizeof(transfer->outOfMemory), "Deserialize assignment may not narrow.");
    record->outOfMemory = transfer->outOfMemory;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnBufferDescriptorErrorInfoFromWireClientDeserialize);

struct WGPUDawnEncoderInternalUsageDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    bool useInternalUsages;
};

static_assert(offsetof(WGPUDawnEncoderInternalUsageDescriptorTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUDawnEncoderInternalUsageDescriptorGetExtraRequiredSize(const WGPUDawnEncoderInternalUsageDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDawnEncoderInternalUsageDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnEncoderInternalUsageDescriptorSerialize(
    const WGPUDawnEncoderInternalUsageDescriptor& record,
    WGPUDawnEncoderInternalUsageDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_DawnEncoderInternalUsageDescriptor);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->useInternalUsages = record.useInternalUsages;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnEncoderInternalUsageDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnEncoderInternalUsageDescriptorDeserialize(
    WGPUDawnEncoderInternalUsageDescriptor* record,
    const volatile WGPUDawnEncoderInternalUsageDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_DawnEncoderInternalUsageDescriptor);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->useInternalUsages) >= sizeof(transfer->useInternalUsages), "Deserialize assignment may not narrow.");
    record->useInternalUsages = transfer->useInternalUsages;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnEncoderInternalUsageDescriptorDeserialize);

struct WGPUDawnMultisampleStateRenderToSingleSampledTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    bool enabled;
};

static_assert(offsetof(WGPUDawnMultisampleStateRenderToSingleSampledTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUDawnMultisampleStateRenderToSingleSampledGetExtraRequiredSize(const WGPUDawnMultisampleStateRenderToSingleSampled& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDawnMultisampleStateRenderToSingleSampledGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnMultisampleStateRenderToSingleSampledSerialize(
    const WGPUDawnMultisampleStateRenderToSingleSampled& record,
    WGPUDawnMultisampleStateRenderToSingleSampledTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_DawnMultisampleStateRenderToSingleSampled);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->enabled = record.enabled;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnMultisampleStateRenderToSingleSampledSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnMultisampleStateRenderToSingleSampledDeserialize(
    WGPUDawnMultisampleStateRenderToSingleSampled* record,
    const volatile WGPUDawnMultisampleStateRenderToSingleSampledTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_DawnMultisampleStateRenderToSingleSampled);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->enabled) >= sizeof(transfer->enabled), "Deserialize assignment may not narrow.");
    record->enabled = transfer->enabled;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnMultisampleStateRenderToSingleSampledDeserialize);

struct WGPUDawnRenderPassColorAttachmentRenderToSingleSampledTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    uint32_t implicitSampleCount;
};

static_assert(offsetof(WGPUDawnRenderPassColorAttachmentRenderToSingleSampledTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUDawnRenderPassColorAttachmentRenderToSingleSampledGetExtraRequiredSize(const WGPUDawnRenderPassColorAttachmentRenderToSingleSampled& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDawnRenderPassColorAttachmentRenderToSingleSampledGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnRenderPassColorAttachmentRenderToSingleSampledSerialize(
    const WGPUDawnRenderPassColorAttachmentRenderToSingleSampled& record,
    WGPUDawnRenderPassColorAttachmentRenderToSingleSampledTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_DawnRenderPassColorAttachmentRenderToSingleSampled);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->implicitSampleCount = record.implicitSampleCount;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnRenderPassColorAttachmentRenderToSingleSampledSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnRenderPassColorAttachmentRenderToSingleSampledDeserialize(
    WGPUDawnRenderPassColorAttachmentRenderToSingleSampled* record,
    const volatile WGPUDawnRenderPassColorAttachmentRenderToSingleSampledTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_DawnRenderPassColorAttachmentRenderToSingleSampled);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->implicitSampleCount) >= sizeof(transfer->implicitSampleCount), "Deserialize assignment may not narrow.");
    record->implicitSampleCount = transfer->implicitSampleCount;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnRenderPassColorAttachmentRenderToSingleSampledDeserialize);

struct WGPUDawnShaderModuleSPIRVOptionsDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    bool allowNonUniformDerivatives;
};

static_assert(offsetof(WGPUDawnShaderModuleSPIRVOptionsDescriptorTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUDawnShaderModuleSPIRVOptionsDescriptorGetExtraRequiredSize(const WGPUDawnShaderModuleSPIRVOptionsDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDawnShaderModuleSPIRVOptionsDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnShaderModuleSPIRVOptionsDescriptorSerialize(
    const WGPUDawnShaderModuleSPIRVOptionsDescriptor& record,
    WGPUDawnShaderModuleSPIRVOptionsDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->allowNonUniformDerivatives = record.allowNonUniformDerivatives;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnShaderModuleSPIRVOptionsDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnShaderModuleSPIRVOptionsDescriptorDeserialize(
    WGPUDawnShaderModuleSPIRVOptionsDescriptor* record,
    const volatile WGPUDawnShaderModuleSPIRVOptionsDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->allowNonUniformDerivatives) >= sizeof(transfer->allowNonUniformDerivatives), "Deserialize assignment may not narrow.");
    record->allowNonUniformDerivatives = transfer->allowNonUniformDerivatives;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnShaderModuleSPIRVOptionsDescriptorDeserialize);

struct WGPUDawnTextureInternalUsageDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    WGPUTextureUsageFlags internalUsage;
};

static_assert(offsetof(WGPUDawnTextureInternalUsageDescriptorTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUDawnTextureInternalUsageDescriptorGetExtraRequiredSize(const WGPUDawnTextureInternalUsageDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDawnTextureInternalUsageDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnTextureInternalUsageDescriptorSerialize(
    const WGPUDawnTextureInternalUsageDescriptor& record,
    WGPUDawnTextureInternalUsageDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_DawnTextureInternalUsageDescriptor);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->internalUsage = record.internalUsage;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnTextureInternalUsageDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDawnTextureInternalUsageDescriptorDeserialize(
    WGPUDawnTextureInternalUsageDescriptor* record,
    const volatile WGPUDawnTextureInternalUsageDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_DawnTextureInternalUsageDescriptor);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->internalUsage) >= sizeof(transfer->internalUsage), "Deserialize assignment may not narrow.");
    record->internalUsage = transfer->internalUsage;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDawnTextureInternalUsageDescriptorDeserialize);

struct WGPUExtent2DTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t width;
    uint32_t height;
};


DAWN_DECLARE_UNUSED size_t WGPUExtent2DGetExtraRequiredSize(const WGPUExtent2D& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUExtent2DGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUExtent2DSerialize(
    const WGPUExtent2D& record,
    WGPUExtent2DTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->width = record.width;
    transfer->height = record.height;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExtent2DSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUExtent2DDeserialize(
    WGPUExtent2D* record,
    const volatile WGPUExtent2DTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->width) >= sizeof(transfer->width), "Deserialize assignment may not narrow.");
    record->width = transfer->width;
    static_assert(sizeof(record->height) >= sizeof(transfer->height), "Deserialize assignment may not narrow.");
    record->height = transfer->height;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExtent2DDeserialize);

struct WGPUExtent3DTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t width;
    uint32_t height;
    uint32_t depthOrArrayLayers;
};


DAWN_DECLARE_UNUSED size_t WGPUExtent3DGetExtraRequiredSize(const WGPUExtent3D& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUExtent3DGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUExtent3DSerialize(
    const WGPUExtent3D& record,
    WGPUExtent3DTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->width = record.width;
    transfer->height = record.height;
    transfer->depthOrArrayLayers = record.depthOrArrayLayers;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExtent3DSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUExtent3DDeserialize(
    WGPUExtent3D* record,
    const volatile WGPUExtent3DTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->width) >= sizeof(transfer->width), "Deserialize assignment may not narrow.");
    record->width = transfer->width;
    static_assert(sizeof(record->height) >= sizeof(transfer->height), "Deserialize assignment may not narrow.");
    record->height = transfer->height;
    static_assert(sizeof(record->depthOrArrayLayers) >= sizeof(transfer->depthOrArrayLayers), "Deserialize assignment may not narrow.");
    record->depthOrArrayLayers = transfer->depthOrArrayLayers;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExtent3DDeserialize);

struct WGPUExternalTextureBindingEntryTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    ObjectId externalTexture;
};

static_assert(offsetof(WGPUExternalTextureBindingEntryTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUExternalTextureBindingEntryGetExtraRequiredSize(const WGPUExternalTextureBindingEntry& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUExternalTextureBindingEntryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUExternalTextureBindingEntrySerialize(
    const WGPUExternalTextureBindingEntry& record,
    WGPUExternalTextureBindingEntryTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_ExternalTextureBindingEntry);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    WIRE_TRY(provider.GetId(record.externalTexture, &transfer->externalTexture));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExternalTextureBindingEntrySerialize);

DAWN_DECLARE_UNUSED WireResult WGPUExternalTextureBindingEntryDeserialize(
    WGPUExternalTextureBindingEntry* record,
    const volatile WGPUExternalTextureBindingEntryTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_ExternalTextureBindingEntry);
    ASSERT(record->chain.next == nullptr);

    WIRE_TRY(resolver.GetFromId(transfer->externalTexture, &record->externalTexture));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExternalTextureBindingEntryDeserialize);

struct WGPUExternalTextureBindingLayoutTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

};

static_assert(offsetof(WGPUExternalTextureBindingLayoutTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUExternalTextureBindingLayoutGetExtraRequiredSize(const WGPUExternalTextureBindingLayout& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUExternalTextureBindingLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUExternalTextureBindingLayoutSerialize(
    const WGPUExternalTextureBindingLayout& record,
    WGPUExternalTextureBindingLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_ExternalTextureBindingLayout);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));


    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExternalTextureBindingLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUExternalTextureBindingLayoutDeserialize(
    WGPUExternalTextureBindingLayout* record,
    const volatile WGPUExternalTextureBindingLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_ExternalTextureBindingLayout);
    ASSERT(record->chain.next == nullptr);


    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExternalTextureBindingLayoutDeserialize);

struct WGPUInstanceDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

};


DAWN_DECLARE_UNUSED size_t WGPUInstanceDescriptorGetExtraRequiredSize(const WGPUInstanceDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUInstanceDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUInstanceDescriptorSerialize(
    const WGPUInstanceDescriptor& record,
    WGPUInstanceDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }


    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUInstanceDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUInstanceDescriptorDeserialize(
    WGPUInstanceDescriptor* record,
    const volatile WGPUInstanceDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }


    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUInstanceDescriptorDeserialize);

struct WGPULimitsTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t maxTextureDimension1D;
    uint32_t maxTextureDimension2D;
    uint32_t maxTextureDimension3D;
    uint32_t maxTextureArrayLayers;
    uint32_t maxBindGroups;
    uint32_t maxBindGroupsPlusVertexBuffers;
    uint32_t maxBindingsPerBindGroup;
    uint32_t maxDynamicUniformBuffersPerPipelineLayout;
    uint32_t maxDynamicStorageBuffersPerPipelineLayout;
    uint32_t maxSampledTexturesPerShaderStage;
    uint32_t maxSamplersPerShaderStage;
    uint32_t maxStorageBuffersPerShaderStage;
    uint32_t maxStorageTexturesPerShaderStage;
    uint32_t maxUniformBuffersPerShaderStage;
    uint64_t maxUniformBufferBindingSize;
    uint64_t maxStorageBufferBindingSize;
    uint32_t minUniformBufferOffsetAlignment;
    uint32_t minStorageBufferOffsetAlignment;
    uint32_t maxVertexBuffers;
    uint64_t maxBufferSize;
    uint32_t maxVertexAttributes;
    uint32_t maxVertexBufferArrayStride;
    uint32_t maxInterStageShaderComponents;
    uint32_t maxInterStageShaderVariables;
    uint32_t maxColorAttachments;
    uint32_t maxColorAttachmentBytesPerSample;
    uint32_t maxComputeWorkgroupStorageSize;
    uint32_t maxComputeInvocationsPerWorkgroup;
    uint32_t maxComputeWorkgroupSizeX;
    uint32_t maxComputeWorkgroupSizeY;
    uint32_t maxComputeWorkgroupSizeZ;
    uint32_t maxComputeWorkgroupsPerDimension;
};


DAWN_DECLARE_UNUSED size_t WGPULimitsGetExtraRequiredSize(const WGPULimits& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPULimitsGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPULimitsSerialize(
    const WGPULimits& record,
    WGPULimitsTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->maxTextureDimension1D = record.maxTextureDimension1D;
    transfer->maxTextureDimension2D = record.maxTextureDimension2D;
    transfer->maxTextureDimension3D = record.maxTextureDimension3D;
    transfer->maxTextureArrayLayers = record.maxTextureArrayLayers;
    transfer->maxBindGroups = record.maxBindGroups;
    transfer->maxBindGroupsPlusVertexBuffers = record.maxBindGroupsPlusVertexBuffers;
    transfer->maxBindingsPerBindGroup = record.maxBindingsPerBindGroup;
    transfer->maxDynamicUniformBuffersPerPipelineLayout = record.maxDynamicUniformBuffersPerPipelineLayout;
    transfer->maxDynamicStorageBuffersPerPipelineLayout = record.maxDynamicStorageBuffersPerPipelineLayout;
    transfer->maxSampledTexturesPerShaderStage = record.maxSampledTexturesPerShaderStage;
    transfer->maxSamplersPerShaderStage = record.maxSamplersPerShaderStage;
    transfer->maxStorageBuffersPerShaderStage = record.maxStorageBuffersPerShaderStage;
    transfer->maxStorageTexturesPerShaderStage = record.maxStorageTexturesPerShaderStage;
    transfer->maxUniformBuffersPerShaderStage = record.maxUniformBuffersPerShaderStage;
    transfer->maxUniformBufferBindingSize = record.maxUniformBufferBindingSize;
    transfer->maxStorageBufferBindingSize = record.maxStorageBufferBindingSize;
    transfer->minUniformBufferOffsetAlignment = record.minUniformBufferOffsetAlignment;
    transfer->minStorageBufferOffsetAlignment = record.minStorageBufferOffsetAlignment;
    transfer->maxVertexBuffers = record.maxVertexBuffers;
    transfer->maxBufferSize = record.maxBufferSize;
    transfer->maxVertexAttributes = record.maxVertexAttributes;
    transfer->maxVertexBufferArrayStride = record.maxVertexBufferArrayStride;
    transfer->maxInterStageShaderComponents = record.maxInterStageShaderComponents;
    transfer->maxInterStageShaderVariables = record.maxInterStageShaderVariables;
    transfer->maxColorAttachments = record.maxColorAttachments;
    transfer->maxColorAttachmentBytesPerSample = record.maxColorAttachmentBytesPerSample;
    transfer->maxComputeWorkgroupStorageSize = record.maxComputeWorkgroupStorageSize;
    transfer->maxComputeInvocationsPerWorkgroup = record.maxComputeInvocationsPerWorkgroup;
    transfer->maxComputeWorkgroupSizeX = record.maxComputeWorkgroupSizeX;
    transfer->maxComputeWorkgroupSizeY = record.maxComputeWorkgroupSizeY;
    transfer->maxComputeWorkgroupSizeZ = record.maxComputeWorkgroupSizeZ;
    transfer->maxComputeWorkgroupsPerDimension = record.maxComputeWorkgroupsPerDimension;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPULimitsSerialize);

DAWN_DECLARE_UNUSED WireResult WGPULimitsDeserialize(
    WGPULimits* record,
    const volatile WGPULimitsTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->maxTextureDimension1D) >= sizeof(transfer->maxTextureDimension1D), "Deserialize assignment may not narrow.");
    record->maxTextureDimension1D = transfer->maxTextureDimension1D;
    static_assert(sizeof(record->maxTextureDimension2D) >= sizeof(transfer->maxTextureDimension2D), "Deserialize assignment may not narrow.");
    record->maxTextureDimension2D = transfer->maxTextureDimension2D;
    static_assert(sizeof(record->maxTextureDimension3D) >= sizeof(transfer->maxTextureDimension3D), "Deserialize assignment may not narrow.");
    record->maxTextureDimension3D = transfer->maxTextureDimension3D;
    static_assert(sizeof(record->maxTextureArrayLayers) >= sizeof(transfer->maxTextureArrayLayers), "Deserialize assignment may not narrow.");
    record->maxTextureArrayLayers = transfer->maxTextureArrayLayers;
    static_assert(sizeof(record->maxBindGroups) >= sizeof(transfer->maxBindGroups), "Deserialize assignment may not narrow.");
    record->maxBindGroups = transfer->maxBindGroups;
    static_assert(sizeof(record->maxBindGroupsPlusVertexBuffers) >= sizeof(transfer->maxBindGroupsPlusVertexBuffers), "Deserialize assignment may not narrow.");
    record->maxBindGroupsPlusVertexBuffers = transfer->maxBindGroupsPlusVertexBuffers;
    static_assert(sizeof(record->maxBindingsPerBindGroup) >= sizeof(transfer->maxBindingsPerBindGroup), "Deserialize assignment may not narrow.");
    record->maxBindingsPerBindGroup = transfer->maxBindingsPerBindGroup;
    static_assert(sizeof(record->maxDynamicUniformBuffersPerPipelineLayout) >= sizeof(transfer->maxDynamicUniformBuffersPerPipelineLayout), "Deserialize assignment may not narrow.");
    record->maxDynamicUniformBuffersPerPipelineLayout = transfer->maxDynamicUniformBuffersPerPipelineLayout;
    static_assert(sizeof(record->maxDynamicStorageBuffersPerPipelineLayout) >= sizeof(transfer->maxDynamicStorageBuffersPerPipelineLayout), "Deserialize assignment may not narrow.");
    record->maxDynamicStorageBuffersPerPipelineLayout = transfer->maxDynamicStorageBuffersPerPipelineLayout;
    static_assert(sizeof(record->maxSampledTexturesPerShaderStage) >= sizeof(transfer->maxSampledTexturesPerShaderStage), "Deserialize assignment may not narrow.");
    record->maxSampledTexturesPerShaderStage = transfer->maxSampledTexturesPerShaderStage;
    static_assert(sizeof(record->maxSamplersPerShaderStage) >= sizeof(transfer->maxSamplersPerShaderStage), "Deserialize assignment may not narrow.");
    record->maxSamplersPerShaderStage = transfer->maxSamplersPerShaderStage;
    static_assert(sizeof(record->maxStorageBuffersPerShaderStage) >= sizeof(transfer->maxStorageBuffersPerShaderStage), "Deserialize assignment may not narrow.");
    record->maxStorageBuffersPerShaderStage = transfer->maxStorageBuffersPerShaderStage;
    static_assert(sizeof(record->maxStorageTexturesPerShaderStage) >= sizeof(transfer->maxStorageTexturesPerShaderStage), "Deserialize assignment may not narrow.");
    record->maxStorageTexturesPerShaderStage = transfer->maxStorageTexturesPerShaderStage;
    static_assert(sizeof(record->maxUniformBuffersPerShaderStage) >= sizeof(transfer->maxUniformBuffersPerShaderStage), "Deserialize assignment may not narrow.");
    record->maxUniformBuffersPerShaderStage = transfer->maxUniformBuffersPerShaderStage;
    static_assert(sizeof(record->maxUniformBufferBindingSize) >= sizeof(transfer->maxUniformBufferBindingSize), "Deserialize assignment may not narrow.");
    record->maxUniformBufferBindingSize = transfer->maxUniformBufferBindingSize;
    static_assert(sizeof(record->maxStorageBufferBindingSize) >= sizeof(transfer->maxStorageBufferBindingSize), "Deserialize assignment may not narrow.");
    record->maxStorageBufferBindingSize = transfer->maxStorageBufferBindingSize;
    static_assert(sizeof(record->minUniformBufferOffsetAlignment) >= sizeof(transfer->minUniformBufferOffsetAlignment), "Deserialize assignment may not narrow.");
    record->minUniformBufferOffsetAlignment = transfer->minUniformBufferOffsetAlignment;
    static_assert(sizeof(record->minStorageBufferOffsetAlignment) >= sizeof(transfer->minStorageBufferOffsetAlignment), "Deserialize assignment may not narrow.");
    record->minStorageBufferOffsetAlignment = transfer->minStorageBufferOffsetAlignment;
    static_assert(sizeof(record->maxVertexBuffers) >= sizeof(transfer->maxVertexBuffers), "Deserialize assignment may not narrow.");
    record->maxVertexBuffers = transfer->maxVertexBuffers;
    static_assert(sizeof(record->maxBufferSize) >= sizeof(transfer->maxBufferSize), "Deserialize assignment may not narrow.");
    record->maxBufferSize = transfer->maxBufferSize;
    static_assert(sizeof(record->maxVertexAttributes) >= sizeof(transfer->maxVertexAttributes), "Deserialize assignment may not narrow.");
    record->maxVertexAttributes = transfer->maxVertexAttributes;
    static_assert(sizeof(record->maxVertexBufferArrayStride) >= sizeof(transfer->maxVertexBufferArrayStride), "Deserialize assignment may not narrow.");
    record->maxVertexBufferArrayStride = transfer->maxVertexBufferArrayStride;
    static_assert(sizeof(record->maxInterStageShaderComponents) >= sizeof(transfer->maxInterStageShaderComponents), "Deserialize assignment may not narrow.");
    record->maxInterStageShaderComponents = transfer->maxInterStageShaderComponents;
    static_assert(sizeof(record->maxInterStageShaderVariables) >= sizeof(transfer->maxInterStageShaderVariables), "Deserialize assignment may not narrow.");
    record->maxInterStageShaderVariables = transfer->maxInterStageShaderVariables;
    static_assert(sizeof(record->maxColorAttachments) >= sizeof(transfer->maxColorAttachments), "Deserialize assignment may not narrow.");
    record->maxColorAttachments = transfer->maxColorAttachments;
    static_assert(sizeof(record->maxColorAttachmentBytesPerSample) >= sizeof(transfer->maxColorAttachmentBytesPerSample), "Deserialize assignment may not narrow.");
    record->maxColorAttachmentBytesPerSample = transfer->maxColorAttachmentBytesPerSample;
    static_assert(sizeof(record->maxComputeWorkgroupStorageSize) >= sizeof(transfer->maxComputeWorkgroupStorageSize), "Deserialize assignment may not narrow.");
    record->maxComputeWorkgroupStorageSize = transfer->maxComputeWorkgroupStorageSize;
    static_assert(sizeof(record->maxComputeInvocationsPerWorkgroup) >= sizeof(transfer->maxComputeInvocationsPerWorkgroup), "Deserialize assignment may not narrow.");
    record->maxComputeInvocationsPerWorkgroup = transfer->maxComputeInvocationsPerWorkgroup;
    static_assert(sizeof(record->maxComputeWorkgroupSizeX) >= sizeof(transfer->maxComputeWorkgroupSizeX), "Deserialize assignment may not narrow.");
    record->maxComputeWorkgroupSizeX = transfer->maxComputeWorkgroupSizeX;
    static_assert(sizeof(record->maxComputeWorkgroupSizeY) >= sizeof(transfer->maxComputeWorkgroupSizeY), "Deserialize assignment may not narrow.");
    record->maxComputeWorkgroupSizeY = transfer->maxComputeWorkgroupSizeY;
    static_assert(sizeof(record->maxComputeWorkgroupSizeZ) >= sizeof(transfer->maxComputeWorkgroupSizeZ), "Deserialize assignment may not narrow.");
    record->maxComputeWorkgroupSizeZ = transfer->maxComputeWorkgroupSizeZ;
    static_assert(sizeof(record->maxComputeWorkgroupsPerDimension) >= sizeof(transfer->maxComputeWorkgroupsPerDimension), "Deserialize assignment may not narrow.");
    record->maxComputeWorkgroupsPerDimension = transfer->maxComputeWorkgroupsPerDimension;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPULimitsDeserialize);

struct WGPUMultisampleStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t count;
    uint32_t mask;
    bool alphaToCoverageEnabled;
};


DAWN_DECLARE_UNUSED size_t WGPUMultisampleStateGetExtraRequiredSize(const WGPUMultisampleState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUMultisampleStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUMultisampleStateSerialize(
    const WGPUMultisampleState& record,
    WGPUMultisampleStateTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->count = record.count;
    transfer->mask = record.mask;
    transfer->alphaToCoverageEnabled = record.alphaToCoverageEnabled;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUMultisampleStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUMultisampleStateDeserialize(
    WGPUMultisampleState* record,
    const volatile WGPUMultisampleStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->count) >= sizeof(transfer->count), "Deserialize assignment may not narrow.");
    record->count = transfer->count;
    static_assert(sizeof(record->mask) >= sizeof(transfer->mask), "Deserialize assignment may not narrow.");
    record->mask = transfer->mask;
    static_assert(sizeof(record->alphaToCoverageEnabled) >= sizeof(transfer->alphaToCoverageEnabled), "Deserialize assignment may not narrow.");
    record->alphaToCoverageEnabled = transfer->alphaToCoverageEnabled;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUMultisampleStateDeserialize);

struct WGPUOrigin2DTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t x;
    uint32_t y;
};


DAWN_DECLARE_UNUSED size_t WGPUOrigin2DGetExtraRequiredSize(const WGPUOrigin2D& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUOrigin2DGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUOrigin2DSerialize(
    const WGPUOrigin2D& record,
    WGPUOrigin2DTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->x = record.x;
    transfer->y = record.y;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUOrigin2DSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUOrigin2DDeserialize(
    WGPUOrigin2D* record,
    const volatile WGPUOrigin2DTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->x) >= sizeof(transfer->x), "Deserialize assignment may not narrow.");
    record->x = transfer->x;
    static_assert(sizeof(record->y) >= sizeof(transfer->y), "Deserialize assignment may not narrow.");
    record->y = transfer->y;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUOrigin2DDeserialize);

struct WGPUOrigin3DTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint32_t x;
    uint32_t y;
    uint32_t z;
};


DAWN_DECLARE_UNUSED size_t WGPUOrigin3DGetExtraRequiredSize(const WGPUOrigin3D& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUOrigin3DGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUOrigin3DSerialize(
    const WGPUOrigin3D& record,
    WGPUOrigin3DTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->x = record.x;
    transfer->y = record.y;
    transfer->z = record.z;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUOrigin3DSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUOrigin3DDeserialize(
    WGPUOrigin3D* record,
    const volatile WGPUOrigin3DTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->x) >= sizeof(transfer->x), "Deserialize assignment may not narrow.");
    record->x = transfer->x;
    static_assert(sizeof(record->y) >= sizeof(transfer->y), "Deserialize assignment may not narrow.");
    record->y = transfer->y;
    static_assert(sizeof(record->z) >= sizeof(transfer->z), "Deserialize assignment may not narrow.");
    record->z = transfer->z;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUOrigin3DDeserialize);

struct WGPUPipelineLayoutDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    uint64_t bindGroupLayoutCount;
};


DAWN_DECLARE_UNUSED size_t WGPUPipelineLayoutDescriptorGetExtraRequiredSize(const WGPUPipelineLayoutDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.bindGroupLayoutCount;
        auto size = WireAlignSizeofN<ObjectId>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUPipelineLayoutDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUPipelineLayoutDescriptorSerialize(
    const WGPUPipelineLayoutDescriptor& record,
    WGPUPipelineLayoutDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->bindGroupLayoutCount = record.bindGroupLayoutCount;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.bindGroupLayoutCount;

        ObjectId* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(provider.GetId(record.bindGroupLayouts[i], &memberBuffer[i]));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUPipelineLayoutDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUPipelineLayoutDescriptorDeserialize(
    WGPUPipelineLayoutDescriptor* record,
    const volatile WGPUPipelineLayoutDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    if (transfer->bindGroupLayoutCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->bindGroupLayoutCount = checked_cast<size_t>(transfer->bindGroupLayoutCount);
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->bindGroupLayoutCount;
        const volatile ObjectId* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBindGroupLayout* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->bindGroupLayouts = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(resolver.GetFromId(memberBuffer[i], &copiedMembers[i]));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUPipelineLayoutDescriptorDeserialize);

struct WGPUPrimitiveDepthClipControlTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    bool unclippedDepth;
};

static_assert(offsetof(WGPUPrimitiveDepthClipControlTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUPrimitiveDepthClipControlGetExtraRequiredSize(const WGPUPrimitiveDepthClipControl& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUPrimitiveDepthClipControlGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUPrimitiveDepthClipControlSerialize(
    const WGPUPrimitiveDepthClipControl& record,
    WGPUPrimitiveDepthClipControlTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_PrimitiveDepthClipControl);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->unclippedDepth = record.unclippedDepth;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUPrimitiveDepthClipControlSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUPrimitiveDepthClipControlDeserialize(
    WGPUPrimitiveDepthClipControl* record,
    const volatile WGPUPrimitiveDepthClipControlTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_PrimitiveDepthClipControl);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->unclippedDepth) >= sizeof(transfer->unclippedDepth), "Deserialize assignment may not narrow.");
    record->unclippedDepth = transfer->unclippedDepth;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUPrimitiveDepthClipControlDeserialize);

struct WGPUPrimitiveStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUPrimitiveTopology topology;
    WGPUIndexFormat stripIndexFormat;
    WGPUFrontFace frontFace;
    WGPUCullMode cullMode;
};


DAWN_DECLARE_UNUSED size_t WGPUPrimitiveStateGetExtraRequiredSize(const WGPUPrimitiveState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUPrimitiveStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUPrimitiveStateSerialize(
    const WGPUPrimitiveState& record,
    WGPUPrimitiveStateTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->topology = record.topology;
    transfer->stripIndexFormat = record.stripIndexFormat;
    transfer->frontFace = record.frontFace;
    transfer->cullMode = record.cullMode;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUPrimitiveStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUPrimitiveStateDeserialize(
    WGPUPrimitiveState* record,
    const volatile WGPUPrimitiveStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->topology) >= sizeof(transfer->topology), "Deserialize assignment may not narrow.");
    record->topology = transfer->topology;
    static_assert(sizeof(record->stripIndexFormat) >= sizeof(transfer->stripIndexFormat), "Deserialize assignment may not narrow.");
    record->stripIndexFormat = transfer->stripIndexFormat;
    static_assert(sizeof(record->frontFace) >= sizeof(transfer->frontFace), "Deserialize assignment may not narrow.");
    record->frontFace = transfer->frontFace;
    static_assert(sizeof(record->cullMode) >= sizeof(transfer->cullMode), "Deserialize assignment may not narrow.");
    record->cullMode = transfer->cullMode;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUPrimitiveStateDeserialize);

struct WGPUQuerySetDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    WGPUQueryType type;
    uint32_t count;
    uint64_t pipelineStatisticsCount;
};


DAWN_DECLARE_UNUSED size_t WGPUQuerySetDescriptorGetExtraRequiredSize(const WGPUQuerySetDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.pipelineStatisticsCount;
        auto size = WireAlignSizeofN<WGPUPipelineStatisticName>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUQuerySetDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUQuerySetDescriptorSerialize(
    const WGPUQuerySetDescriptor& record,
    WGPUQuerySetDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->type = record.type;
    transfer->count = record.count;
    transfer->pipelineStatisticsCount = record.pipelineStatisticsCount;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.pipelineStatisticsCount;

        WGPUPipelineStatisticName* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.pipelineStatistics,
            sizeof(WGPUPipelineStatisticName) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUQuerySetDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUQuerySetDescriptorDeserialize(
    WGPUQuerySetDescriptor* record,
    const volatile WGPUQuerySetDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    static_assert(sizeof(record->count) >= sizeof(transfer->count), "Deserialize assignment may not narrow.");
    record->count = transfer->count;
    if (transfer->pipelineStatisticsCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->pipelineStatisticsCount = checked_cast<size_t>(transfer->pipelineStatisticsCount);
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->pipelineStatisticsCount;
        const volatile WGPUPipelineStatisticName* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUPipelineStatisticName* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->pipelineStatistics = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUPipelineStatisticName*>(memberBuffer),
           sizeof(WGPUPipelineStatisticName) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUQuerySetDescriptorDeserialize);

struct WGPUQueueDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
};


DAWN_DECLARE_UNUSED size_t WGPUQueueDescriptorGetExtraRequiredSize(const WGPUQueueDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUQueueDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUQueueDescriptorSerialize(
    const WGPUQueueDescriptor& record,
    WGPUQueueDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUQueueDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUQueueDescriptorDeserialize(
    WGPUQueueDescriptor* record,
    const volatile WGPUQueueDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUQueueDescriptorDeserialize);

struct WGPURenderBundleDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
};


DAWN_DECLARE_UNUSED size_t WGPURenderBundleDescriptorGetExtraRequiredSize(const WGPURenderBundleDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderBundleDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderBundleDescriptorSerialize(
    const WGPURenderBundleDescriptor& record,
    WGPURenderBundleDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderBundleDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderBundleDescriptorDeserialize(
    WGPURenderBundleDescriptor* record,
    const volatile WGPURenderBundleDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderBundleDescriptorDeserialize);

struct WGPURenderBundleEncoderDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    uint64_t colorFormatsCount;
    WGPUTextureFormat depthStencilFormat;
    uint32_t sampleCount;
    bool depthReadOnly;
    bool stencilReadOnly;
};


DAWN_DECLARE_UNUSED size_t WGPURenderBundleEncoderDescriptorGetExtraRequiredSize(const WGPURenderBundleEncoderDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.colorFormatsCount;
        auto size = WireAlignSizeofN<WGPUTextureFormat>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderBundleEncoderDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderBundleEncoderDescriptorSerialize(
    const WGPURenderBundleEncoderDescriptor& record,
    WGPURenderBundleEncoderDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->colorFormatsCount = record.colorFormatsCount;
    transfer->depthStencilFormat = record.depthStencilFormat;
    transfer->sampleCount = record.sampleCount;
    transfer->depthReadOnly = record.depthReadOnly;
    transfer->stencilReadOnly = record.stencilReadOnly;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.colorFormatsCount;

        WGPUTextureFormat* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.colorFormats,
            sizeof(WGPUTextureFormat) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderBundleEncoderDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderBundleEncoderDescriptorDeserialize(
    WGPURenderBundleEncoderDescriptor* record,
    const volatile WGPURenderBundleEncoderDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    if (transfer->colorFormatsCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->colorFormatsCount = checked_cast<size_t>(transfer->colorFormatsCount);
    static_assert(sizeof(record->depthStencilFormat) >= sizeof(transfer->depthStencilFormat), "Deserialize assignment may not narrow.");
    record->depthStencilFormat = transfer->depthStencilFormat;
    static_assert(sizeof(record->sampleCount) >= sizeof(transfer->sampleCount), "Deserialize assignment may not narrow.");
    record->sampleCount = transfer->sampleCount;
    static_assert(sizeof(record->depthReadOnly) >= sizeof(transfer->depthReadOnly), "Deserialize assignment may not narrow.");
    record->depthReadOnly = transfer->depthReadOnly;
    static_assert(sizeof(record->stencilReadOnly) >= sizeof(transfer->stencilReadOnly), "Deserialize assignment may not narrow.");
    record->stencilReadOnly = transfer->stencilReadOnly;
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->colorFormatsCount;
        const volatile WGPUTextureFormat* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUTextureFormat* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->colorFormats = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUTextureFormat*>(memberBuffer),
           sizeof(WGPUTextureFormat) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderBundleEncoderDescriptorDeserialize);

struct WGPURenderPassDepthStencilAttachmentTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    ObjectId view;
    WGPULoadOp depthLoadOp;
    WGPUStoreOp depthStoreOp;
    float depthClearValue;
    bool depthReadOnly;
    WGPULoadOp stencilLoadOp;
    WGPUStoreOp stencilStoreOp;
    uint32_t stencilClearValue;
    bool stencilReadOnly;
};


DAWN_DECLARE_UNUSED size_t WGPURenderPassDepthStencilAttachmentGetExtraRequiredSize(const WGPURenderPassDepthStencilAttachment& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassDepthStencilAttachmentGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassDepthStencilAttachmentSerialize(
    const WGPURenderPassDepthStencilAttachment& record,
    WGPURenderPassDepthStencilAttachmentTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    WIRE_TRY(provider.GetId(record.view, &transfer->view));
    transfer->depthLoadOp = record.depthLoadOp;
    transfer->depthStoreOp = record.depthStoreOp;
    transfer->depthClearValue = record.depthClearValue;
    transfer->depthReadOnly = record.depthReadOnly;
    transfer->stencilLoadOp = record.stencilLoadOp;
    transfer->stencilStoreOp = record.stencilStoreOp;
    transfer->stencilClearValue = record.stencilClearValue;
    transfer->stencilReadOnly = record.stencilReadOnly;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDepthStencilAttachmentSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassDepthStencilAttachmentDeserialize(
    WGPURenderPassDepthStencilAttachment* record,
    const volatile WGPURenderPassDepthStencilAttachmentTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);



    WIRE_TRY(resolver.GetFromId(transfer->view, &record->view));
    static_assert(sizeof(record->depthLoadOp) >= sizeof(transfer->depthLoadOp), "Deserialize assignment may not narrow.");
    record->depthLoadOp = transfer->depthLoadOp;
    static_assert(sizeof(record->depthStoreOp) >= sizeof(transfer->depthStoreOp), "Deserialize assignment may not narrow.");
    record->depthStoreOp = transfer->depthStoreOp;
    static_assert(sizeof(record->depthClearValue) >= sizeof(transfer->depthClearValue), "Deserialize assignment may not narrow.");
    record->depthClearValue = transfer->depthClearValue;
    static_assert(sizeof(record->depthReadOnly) >= sizeof(transfer->depthReadOnly), "Deserialize assignment may not narrow.");
    record->depthReadOnly = transfer->depthReadOnly;
    static_assert(sizeof(record->stencilLoadOp) >= sizeof(transfer->stencilLoadOp), "Deserialize assignment may not narrow.");
    record->stencilLoadOp = transfer->stencilLoadOp;
    static_assert(sizeof(record->stencilStoreOp) >= sizeof(transfer->stencilStoreOp), "Deserialize assignment may not narrow.");
    record->stencilStoreOp = transfer->stencilStoreOp;
    static_assert(sizeof(record->stencilClearValue) >= sizeof(transfer->stencilClearValue), "Deserialize assignment may not narrow.");
    record->stencilClearValue = transfer->stencilClearValue;
    static_assert(sizeof(record->stencilReadOnly) >= sizeof(transfer->stencilReadOnly), "Deserialize assignment may not narrow.");
    record->stencilReadOnly = transfer->stencilReadOnly;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDepthStencilAttachmentDeserialize);

struct WGPURenderPassDescriptorMaxDrawCountTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    uint64_t maxDrawCount;
};

static_assert(offsetof(WGPURenderPassDescriptorMaxDrawCountTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPURenderPassDescriptorMaxDrawCountGetExtraRequiredSize(const WGPURenderPassDescriptorMaxDrawCount& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorMaxDrawCountGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassDescriptorMaxDrawCountSerialize(
    const WGPURenderPassDescriptorMaxDrawCount& record,
    WGPURenderPassDescriptorMaxDrawCountTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_RenderPassDescriptorMaxDrawCount);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->maxDrawCount = record.maxDrawCount;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorMaxDrawCountSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassDescriptorMaxDrawCountDeserialize(
    WGPURenderPassDescriptorMaxDrawCount* record,
    const volatile WGPURenderPassDescriptorMaxDrawCountTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_RenderPassDescriptorMaxDrawCount);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->maxDrawCount) >= sizeof(transfer->maxDrawCount), "Deserialize assignment may not narrow.");
    record->maxDrawCount = transfer->maxDrawCount;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorMaxDrawCountDeserialize);

struct WGPURenderPassTimestampWriteTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    ObjectId querySet;
    uint32_t queryIndex;
    WGPURenderPassTimestampLocation location;
};


DAWN_DECLARE_UNUSED size_t WGPURenderPassTimestampWriteGetExtraRequiredSize(const WGPURenderPassTimestampWrite& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassTimestampWriteGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassTimestampWriteSerialize(
    const WGPURenderPassTimestampWrite& record,
    WGPURenderPassTimestampWriteTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);


    WIRE_TRY(provider.GetId(record.querySet, &transfer->querySet));
    transfer->queryIndex = record.queryIndex;
    transfer->location = record.location;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassTimestampWriteSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassTimestampWriteDeserialize(
    WGPURenderPassTimestampWrite* record,
    const volatile WGPURenderPassTimestampWriteTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);



    WIRE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    static_assert(sizeof(record->queryIndex) >= sizeof(transfer->queryIndex), "Deserialize assignment may not narrow.");
    record->queryIndex = transfer->queryIndex;
    static_assert(sizeof(record->location) >= sizeof(transfer->location), "Deserialize assignment may not narrow.");
    record->location = transfer->location;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassTimestampWriteDeserialize);

struct WGPURequestAdapterOptionsTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId compatibleSurface;
    WGPUPowerPreference powerPreference;
    WGPUBackendType backendType;
    bool forceFallbackAdapter;
    bool compatibilityMode;
};


DAWN_DECLARE_UNUSED size_t WGPURequestAdapterOptionsGetExtraRequiredSize(const WGPURequestAdapterOptions& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURequestAdapterOptionsGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURequestAdapterOptionsSerialize(
    const WGPURequestAdapterOptions& record,
    WGPURequestAdapterOptionsTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetOptionalId(record.compatibleSurface, &transfer->compatibleSurface));
    transfer->powerPreference = record.powerPreference;
    transfer->backendType = record.backendType;
    transfer->forceFallbackAdapter = record.forceFallbackAdapter;
    transfer->compatibilityMode = record.compatibilityMode;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURequestAdapterOptionsSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURequestAdapterOptionsDeserialize(
    WGPURequestAdapterOptions* record,
    const volatile WGPURequestAdapterOptionsTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetOptionalFromId(transfer->compatibleSurface, &record->compatibleSurface));
    static_assert(sizeof(record->powerPreference) >= sizeof(transfer->powerPreference), "Deserialize assignment may not narrow.");
    record->powerPreference = transfer->powerPreference;
    static_assert(sizeof(record->backendType) >= sizeof(transfer->backendType), "Deserialize assignment may not narrow.");
    record->backendType = transfer->backendType;
    static_assert(sizeof(record->forceFallbackAdapter) >= sizeof(transfer->forceFallbackAdapter), "Deserialize assignment may not narrow.");
    record->forceFallbackAdapter = transfer->forceFallbackAdapter;
    static_assert(sizeof(record->compatibilityMode) >= sizeof(transfer->compatibilityMode), "Deserialize assignment may not narrow.");
    record->compatibilityMode = transfer->compatibilityMode;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURequestAdapterOptionsDeserialize);

struct WGPUSamplerBindingLayoutTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUSamplerBindingType type;
};


DAWN_DECLARE_UNUSED size_t WGPUSamplerBindingLayoutGetExtraRequiredSize(const WGPUSamplerBindingLayout& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSamplerBindingLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUSamplerBindingLayoutSerialize(
    const WGPUSamplerBindingLayout& record,
    WGPUSamplerBindingLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->type = record.type;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSamplerBindingLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUSamplerBindingLayoutDeserialize(
    WGPUSamplerBindingLayout* record,
    const volatile WGPUSamplerBindingLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSamplerBindingLayoutDeserialize);

struct WGPUSamplerDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    WGPUAddressMode addressModeU;
    WGPUAddressMode addressModeV;
    WGPUAddressMode addressModeW;
    WGPUFilterMode magFilter;
    WGPUFilterMode minFilter;
    WGPUMipmapFilterMode mipmapFilter;
    float lodMinClamp;
    float lodMaxClamp;
    WGPUCompareFunction compare;
    uint16_t maxAnisotropy;
};


DAWN_DECLARE_UNUSED size_t WGPUSamplerDescriptorGetExtraRequiredSize(const WGPUSamplerDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUSamplerDescriptorSerialize(
    const WGPUSamplerDescriptor& record,
    WGPUSamplerDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->addressModeU = record.addressModeU;
    transfer->addressModeV = record.addressModeV;
    transfer->addressModeW = record.addressModeW;
    transfer->magFilter = record.magFilter;
    transfer->minFilter = record.minFilter;
    transfer->mipmapFilter = record.mipmapFilter;
    transfer->lodMinClamp = record.lodMinClamp;
    transfer->lodMaxClamp = record.lodMaxClamp;
    transfer->compare = record.compare;
    transfer->maxAnisotropy = record.maxAnisotropy;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUSamplerDescriptorDeserialize(
    WGPUSamplerDescriptor* record,
    const volatile WGPUSamplerDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->addressModeU) >= sizeof(transfer->addressModeU), "Deserialize assignment may not narrow.");
    record->addressModeU = transfer->addressModeU;
    static_assert(sizeof(record->addressModeV) >= sizeof(transfer->addressModeV), "Deserialize assignment may not narrow.");
    record->addressModeV = transfer->addressModeV;
    static_assert(sizeof(record->addressModeW) >= sizeof(transfer->addressModeW), "Deserialize assignment may not narrow.");
    record->addressModeW = transfer->addressModeW;
    static_assert(sizeof(record->magFilter) >= sizeof(transfer->magFilter), "Deserialize assignment may not narrow.");
    record->magFilter = transfer->magFilter;
    static_assert(sizeof(record->minFilter) >= sizeof(transfer->minFilter), "Deserialize assignment may not narrow.");
    record->minFilter = transfer->minFilter;
    static_assert(sizeof(record->mipmapFilter) >= sizeof(transfer->mipmapFilter), "Deserialize assignment may not narrow.");
    record->mipmapFilter = transfer->mipmapFilter;
    static_assert(sizeof(record->lodMinClamp) >= sizeof(transfer->lodMinClamp), "Deserialize assignment may not narrow.");
    record->lodMinClamp = transfer->lodMinClamp;
    static_assert(sizeof(record->lodMaxClamp) >= sizeof(transfer->lodMaxClamp), "Deserialize assignment may not narrow.");
    record->lodMaxClamp = transfer->lodMaxClamp;
    static_assert(sizeof(record->compare) >= sizeof(transfer->compare), "Deserialize assignment may not narrow.");
    record->compare = transfer->compare;
    static_assert(sizeof(record->maxAnisotropy) >= sizeof(transfer->maxAnisotropy), "Deserialize assignment may not narrow.");
    record->maxAnisotropy = transfer->maxAnisotropy;
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSamplerDescriptorDeserialize);

struct WGPUShaderModuleDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
};


DAWN_DECLARE_UNUSED size_t WGPUShaderModuleDescriptorGetExtraRequiredSize(const WGPUShaderModuleDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUShaderModuleDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUShaderModuleDescriptorSerialize(
    const WGPUShaderModuleDescriptor& record,
    WGPUShaderModuleDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUShaderModuleDescriptorDeserialize(
    WGPUShaderModuleDescriptor* record,
    const volatile WGPUShaderModuleDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleDescriptorDeserialize);

struct WGPUShaderModuleSPIRVDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    uint32_t codeSize;
};

static_assert(offsetof(WGPUShaderModuleSPIRVDescriptorTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUShaderModuleSPIRVDescriptorGetExtraRequiredSize(const WGPUShaderModuleSPIRVDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.codeSize;
        auto size = WireAlignSizeofN<uint32_t>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUShaderModuleSPIRVDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUShaderModuleSPIRVDescriptorSerialize(
    const WGPUShaderModuleSPIRVDescriptor& record,
    WGPUShaderModuleSPIRVDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_ShaderModuleSPIRVDescriptor);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    transfer->codeSize = record.codeSize;
    {
        auto memberLength = record.codeSize;

        uint32_t* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.code,
            sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleSPIRVDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUShaderModuleSPIRVDescriptorDeserialize(
    WGPUShaderModuleSPIRVDescriptor* record,
    const volatile WGPUShaderModuleSPIRVDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_ShaderModuleSPIRVDescriptor);
    ASSERT(record->chain.next == nullptr);

    static_assert(sizeof(record->codeSize) >= sizeof(transfer->codeSize), "Deserialize assignment may not narrow.");
    record->codeSize = transfer->codeSize;
    {
        auto memberLength = record->codeSize;
        const volatile uint32_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint32_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->code = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint32_t*>(memberBuffer),
           sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleSPIRVDescriptorDeserialize);

struct WGPUShaderModuleWGSLDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    uint64_t codeStrlen;
};

static_assert(offsetof(WGPUShaderModuleWGSLDescriptorTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUShaderModuleWGSLDescriptorGetExtraRequiredSize(const WGPUShaderModuleWGSLDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.code != nullptr);
    result += Align(std::strlen(record.code), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUShaderModuleWGSLDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUShaderModuleWGSLDescriptorSerialize(
    const WGPUShaderModuleWGSLDescriptor& record,
    WGPUShaderModuleWGSLDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_ShaderModuleWGSLDescriptor);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    {
        transfer->codeStrlen = std::strlen(record.code);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->codeStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.code, transfer->codeStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleWGSLDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUShaderModuleWGSLDescriptorDeserialize(
    WGPUShaderModuleWGSLDescriptor* record,
    const volatile WGPUShaderModuleWGSLDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_ShaderModuleWGSLDescriptor);
    ASSERT(record->chain.next == nullptr);

    {
        uint64_t stringLength64 = transfer->codeStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->code = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUShaderModuleWGSLDescriptorDeserialize);

struct WGPUStencilFaceStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    WGPUCompareFunction compare;
    WGPUStencilOperation failOp;
    WGPUStencilOperation depthFailOp;
    WGPUStencilOperation passOp;
};


DAWN_DECLARE_UNUSED size_t WGPUStencilFaceStateGetExtraRequiredSize(const WGPUStencilFaceState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUStencilFaceStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUStencilFaceStateSerialize(
    const WGPUStencilFaceState& record,
    WGPUStencilFaceStateTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->compare = record.compare;
    transfer->failOp = record.failOp;
    transfer->depthFailOp = record.depthFailOp;
    transfer->passOp = record.passOp;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUStencilFaceStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUStencilFaceStateDeserialize(
    WGPUStencilFaceState* record,
    const volatile WGPUStencilFaceStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->compare) >= sizeof(transfer->compare), "Deserialize assignment may not narrow.");
    record->compare = transfer->compare;
    static_assert(sizeof(record->failOp) >= sizeof(transfer->failOp), "Deserialize assignment may not narrow.");
    record->failOp = transfer->failOp;
    static_assert(sizeof(record->depthFailOp) >= sizeof(transfer->depthFailOp), "Deserialize assignment may not narrow.");
    record->depthFailOp = transfer->depthFailOp;
    static_assert(sizeof(record->passOp) >= sizeof(transfer->passOp), "Deserialize assignment may not narrow.");
    record->passOp = transfer->passOp;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUStencilFaceStateDeserialize);

struct WGPUStorageTextureBindingLayoutTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUStorageTextureAccess access;
    WGPUTextureFormat format;
    WGPUTextureViewDimension viewDimension;
};


DAWN_DECLARE_UNUSED size_t WGPUStorageTextureBindingLayoutGetExtraRequiredSize(const WGPUStorageTextureBindingLayout& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUStorageTextureBindingLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUStorageTextureBindingLayoutSerialize(
    const WGPUStorageTextureBindingLayout& record,
    WGPUStorageTextureBindingLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->access = record.access;
    transfer->format = record.format;
    transfer->viewDimension = record.viewDimension;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUStorageTextureBindingLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUStorageTextureBindingLayoutDeserialize(
    WGPUStorageTextureBindingLayout* record,
    const volatile WGPUStorageTextureBindingLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->access) >= sizeof(transfer->access), "Deserialize assignment may not narrow.");
    record->access = transfer->access;
    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->viewDimension) >= sizeof(transfer->viewDimension), "Deserialize assignment may not narrow.");
    record->viewDimension = transfer->viewDimension;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUStorageTextureBindingLayoutDeserialize);

struct WGPUSurfaceDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
};


DAWN_DECLARE_UNUSED size_t WGPUSurfaceDescriptorGetExtraRequiredSize(const WGPUSurfaceDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUSurfaceDescriptorSerialize(
    const WGPUSurfaceDescriptor& record,
    WGPUSurfaceDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUSurfaceDescriptorDeserialize(
    WGPUSurfaceDescriptor* record,
    const volatile WGPUSurfaceDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorDeserialize);

struct WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WGPUChainedStructTransfer chain;

    uint64_t selectorStrlen;
};

static_assert(offsetof(WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer, chain) == 0);

DAWN_DECLARE_UNUSED size_t WGPUSurfaceDescriptorFromCanvasHTMLSelectorGetExtraRequiredSize(const WGPUSurfaceDescriptorFromCanvasHTMLSelector& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.selector != nullptr);
    result += Align(std::strlen(record.selector), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorFromCanvasHTMLSelectorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUSurfaceDescriptorFromCanvasHTMLSelectorSerialize(
    const WGPUSurfaceDescriptorFromCanvasHTMLSelector& record,
    WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    ASSERT(transfer->chain.sType == WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector);
    ASSERT(transfer->chain.hasNext == (record.chain.next != nullptr));

    {
        transfer->selectorStrlen = std::strlen(record.selector);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->selectorStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.selector, transfer->selectorStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorFromCanvasHTMLSelectorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUSurfaceDescriptorFromCanvasHTMLSelectorDeserialize(
    WGPUSurfaceDescriptorFromCanvasHTMLSelector* record,
    const volatile WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    ASSERT(record->chain.sType == WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector);
    ASSERT(record->chain.next == nullptr);

    {
        uint64_t stringLength64 = transfer->selectorStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->selector = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSurfaceDescriptorFromCanvasHTMLSelectorDeserialize);

struct WGPUSwapChainDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    WGPUTextureUsageFlags usage;
    WGPUTextureFormat format;
    uint32_t width;
    uint32_t height;
    WGPUPresentMode presentMode;
};


DAWN_DECLARE_UNUSED size_t WGPUSwapChainDescriptorGetExtraRequiredSize(const WGPUSwapChainDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSwapChainDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUSwapChainDescriptorSerialize(
    const WGPUSwapChainDescriptor& record,
    WGPUSwapChainDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->usage = record.usage;
    transfer->format = record.format;
    transfer->width = record.width;
    transfer->height = record.height;
    transfer->presentMode = record.presentMode;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSwapChainDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUSwapChainDescriptorDeserialize(
    WGPUSwapChainDescriptor* record,
    const volatile WGPUSwapChainDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->usage) >= sizeof(transfer->usage), "Deserialize assignment may not narrow.");
    record->usage = transfer->usage;
    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->width) >= sizeof(transfer->width), "Deserialize assignment may not narrow.");
    record->width = transfer->width;
    static_assert(sizeof(record->height) >= sizeof(transfer->height), "Deserialize assignment may not narrow.");
    record->height = transfer->height;
    static_assert(sizeof(record->presentMode) >= sizeof(transfer->presentMode), "Deserialize assignment may not narrow.");
    record->presentMode = transfer->presentMode;
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSwapChainDescriptorDeserialize);

struct WGPUTextureBindingLayoutTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureSampleType sampleType;
    WGPUTextureViewDimension viewDimension;
    bool multisampled;
};


DAWN_DECLARE_UNUSED size_t WGPUTextureBindingLayoutGetExtraRequiredSize(const WGPUTextureBindingLayout& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureBindingLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureBindingLayoutSerialize(
    const WGPUTextureBindingLayout& record,
    WGPUTextureBindingLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->sampleType = record.sampleType;
    transfer->viewDimension = record.viewDimension;
    transfer->multisampled = record.multisampled;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureBindingLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureBindingLayoutDeserialize(
    WGPUTextureBindingLayout* record,
    const volatile WGPUTextureBindingLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->sampleType) >= sizeof(transfer->sampleType), "Deserialize assignment may not narrow.");
    record->sampleType = transfer->sampleType;
    static_assert(sizeof(record->viewDimension) >= sizeof(transfer->viewDimension), "Deserialize assignment may not narrow.");
    record->viewDimension = transfer->viewDimension;
    static_assert(sizeof(record->multisampled) >= sizeof(transfer->multisampled), "Deserialize assignment may not narrow.");
    record->multisampled = transfer->multisampled;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureBindingLayoutDeserialize);

struct WGPUTextureDataLayoutTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t offset;
    uint32_t bytesPerRow;
    uint32_t rowsPerImage;
};


DAWN_DECLARE_UNUSED size_t WGPUTextureDataLayoutGetExtraRequiredSize(const WGPUTextureDataLayout& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureDataLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureDataLayoutSerialize(
    const WGPUTextureDataLayout& record,
    WGPUTextureDataLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->offset = record.offset;
    transfer->bytesPerRow = record.bytesPerRow;
    transfer->rowsPerImage = record.rowsPerImage;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureDataLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureDataLayoutDeserialize(
    WGPUTextureDataLayout* record,
    const volatile WGPUTextureDataLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->bytesPerRow) >= sizeof(transfer->bytesPerRow), "Deserialize assignment may not narrow.");
    record->bytesPerRow = transfer->bytesPerRow;
    static_assert(sizeof(record->rowsPerImage) >= sizeof(transfer->rowsPerImage), "Deserialize assignment may not narrow.");
    record->rowsPerImage = transfer->rowsPerImage;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureDataLayoutDeserialize);

struct WGPUTextureViewDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    WGPUTextureFormat format;
    WGPUTextureViewDimension dimension;
    uint32_t baseMipLevel;
    uint32_t mipLevelCount;
    uint32_t baseArrayLayer;
    uint32_t arrayLayerCount;
    WGPUTextureAspect aspect;
};


DAWN_DECLARE_UNUSED size_t WGPUTextureViewDescriptorGetExtraRequiredSize(const WGPUTextureViewDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureViewDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureViewDescriptorSerialize(
    const WGPUTextureViewDescriptor& record,
    WGPUTextureViewDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->format = record.format;
    transfer->dimension = record.dimension;
    transfer->baseMipLevel = record.baseMipLevel;
    transfer->mipLevelCount = record.mipLevelCount;
    transfer->baseArrayLayer = record.baseArrayLayer;
    transfer->arrayLayerCount = record.arrayLayerCount;
    transfer->aspect = record.aspect;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureViewDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureViewDescriptorDeserialize(
    WGPUTextureViewDescriptor* record,
    const volatile WGPUTextureViewDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->dimension) >= sizeof(transfer->dimension), "Deserialize assignment may not narrow.");
    record->dimension = transfer->dimension;
    static_assert(sizeof(record->baseMipLevel) >= sizeof(transfer->baseMipLevel), "Deserialize assignment may not narrow.");
    record->baseMipLevel = transfer->baseMipLevel;
    static_assert(sizeof(record->mipLevelCount) >= sizeof(transfer->mipLevelCount), "Deserialize assignment may not narrow.");
    record->mipLevelCount = transfer->mipLevelCount;
    static_assert(sizeof(record->baseArrayLayer) >= sizeof(transfer->baseArrayLayer), "Deserialize assignment may not narrow.");
    record->baseArrayLayer = transfer->baseArrayLayer;
    static_assert(sizeof(record->arrayLayerCount) >= sizeof(transfer->arrayLayerCount), "Deserialize assignment may not narrow.");
    record->arrayLayerCount = transfer->arrayLayerCount;
    static_assert(sizeof(record->aspect) >= sizeof(transfer->aspect), "Deserialize assignment may not narrow.");
    record->aspect = transfer->aspect;
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureViewDescriptorDeserialize);

struct WGPUVertexAttributeTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    WGPUVertexFormat format;
    uint64_t offset;
    uint32_t shaderLocation;
};


DAWN_DECLARE_UNUSED size_t WGPUVertexAttributeGetExtraRequiredSize(const WGPUVertexAttribute& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUVertexAttributeGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUVertexAttributeSerialize(
    const WGPUVertexAttribute& record,
    WGPUVertexAttributeTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->format = record.format;
    transfer->offset = record.offset;
    transfer->shaderLocation = record.shaderLocation;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexAttributeSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUVertexAttributeDeserialize(
    WGPUVertexAttribute* record,
    const volatile WGPUVertexAttributeTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->shaderLocation) >= sizeof(transfer->shaderLocation), "Deserialize assignment may not narrow.");
    record->shaderLocation = transfer->shaderLocation;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexAttributeDeserialize);

struct WGPUBindGroupDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    ObjectId layout;
    uint64_t entryCount;
};


DAWN_DECLARE_UNUSED size_t WGPUBindGroupDescriptorGetExtraRequiredSize(const WGPUBindGroupDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.entryCount;
        auto size = WireAlignSizeofN<WGPUBindGroupEntryTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUBindGroupEntryGetExtraRequiredSize(record.entries[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupDescriptorSerialize(
    const WGPUBindGroupDescriptor& record,
    WGPUBindGroupDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetId(record.layout, &transfer->layout));
    transfer->entryCount = record.entryCount;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.entryCount;

        WGPUBindGroupEntryTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupEntrySerialize(record.entries[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupDescriptorDeserialize(
    WGPUBindGroupDescriptor* record,
    const volatile WGPUBindGroupDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetFromId(transfer->layout, &record->layout));
    if (transfer->entryCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->entryCount = checked_cast<size_t>(transfer->entryCount);
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->entryCount;
        const volatile WGPUBindGroupEntryTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBindGroupEntry* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->entries = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupEntryDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupDescriptorDeserialize);

struct WGPUBindGroupLayoutEntryTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint32_t binding;
    WGPUShaderStageFlags visibility;
    WGPUBufferBindingLayoutTransfer buffer;
    WGPUSamplerBindingLayoutTransfer sampler;
    WGPUTextureBindingLayoutTransfer texture;
    WGPUStorageTextureBindingLayoutTransfer storageTexture;
};


DAWN_DECLARE_UNUSED size_t WGPUBindGroupLayoutEntryGetExtraRequiredSize(const WGPUBindGroupLayoutEntry& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPUBufferBindingLayoutGetExtraRequiredSize(record.buffer);
    }
    {
        result += WGPUSamplerBindingLayoutGetExtraRequiredSize(record.sampler);
    }
    {
        result += WGPUTextureBindingLayoutGetExtraRequiredSize(record.texture);
    }
    {
        result += WGPUStorageTextureBindingLayoutGetExtraRequiredSize(record.storageTexture);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutEntryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupLayoutEntrySerialize(
    const WGPUBindGroupLayoutEntry& record,
    WGPUBindGroupLayoutEntryTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->binding = record.binding;
    transfer->visibility = record.visibility;
    WIRE_TRY(WGPUBufferBindingLayoutSerialize(record.buffer, &transfer->buffer, buffer, provider));
    WIRE_TRY(WGPUSamplerBindingLayoutSerialize(record.sampler, &transfer->sampler, buffer, provider));
    WIRE_TRY(WGPUTextureBindingLayoutSerialize(record.texture, &transfer->texture, buffer, provider));
    WIRE_TRY(WGPUStorageTextureBindingLayoutSerialize(record.storageTexture, &transfer->storageTexture, buffer, provider));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutEntrySerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupLayoutEntryDeserialize(
    WGPUBindGroupLayoutEntry* record,
    const volatile WGPUBindGroupLayoutEntryTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->binding) >= sizeof(transfer->binding), "Deserialize assignment may not narrow.");
    record->binding = transfer->binding;
    static_assert(sizeof(record->visibility) >= sizeof(transfer->visibility), "Deserialize assignment may not narrow.");
    record->visibility = transfer->visibility;
    WIRE_TRY(WGPUBufferBindingLayoutDeserialize(&record->buffer, &transfer->buffer, deserializeBuffer, allocator, resolver));
    WIRE_TRY(WGPUSamplerBindingLayoutDeserialize(&record->sampler, &transfer->sampler, deserializeBuffer, allocator, resolver));
    WIRE_TRY(WGPUTextureBindingLayoutDeserialize(&record->texture, &transfer->texture, deserializeBuffer, allocator, resolver));
    WIRE_TRY(WGPUStorageTextureBindingLayoutDeserialize(&record->storageTexture, &transfer->storageTexture, deserializeBuffer, allocator, resolver));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutEntryDeserialize);

struct WGPUBlendStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    WGPUBlendComponentTransfer color;
    WGPUBlendComponentTransfer alpha;
};


DAWN_DECLARE_UNUSED size_t WGPUBlendStateGetExtraRequiredSize(const WGPUBlendState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        result += WGPUBlendComponentGetExtraRequiredSize(record.color);
    }
    {
        result += WGPUBlendComponentGetExtraRequiredSize(record.alpha);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBlendStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBlendStateSerialize(
    const WGPUBlendState& record,
    WGPUBlendStateTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    WIRE_TRY(WGPUBlendComponentSerialize(record.color, &transfer->color, buffer));
    WIRE_TRY(WGPUBlendComponentSerialize(record.alpha, &transfer->alpha, buffer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBlendStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBlendStateDeserialize(
    WGPUBlendState* record,
    const volatile WGPUBlendStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->color) == sizeof(transfer->color), "Deserialize memcpy size must match.");
    memcpy(&record->color, const_cast<const WGPUBlendComponentTransfer*>(&transfer->color), sizeof(WGPUBlendComponentTransfer));
    static_assert(sizeof(record->alpha) == sizeof(transfer->alpha), "Deserialize memcpy size must match.");
    memcpy(&record->alpha, const_cast<const WGPUBlendComponentTransfer*>(&transfer->alpha), sizeof(WGPUBlendComponentTransfer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBlendStateDeserialize);

struct WGPUCompilationInfoTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t messageCount;
};


DAWN_DECLARE_UNUSED size_t WGPUCompilationInfoGetExtraRequiredSize(const WGPUCompilationInfo& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        auto memberLength = record.messageCount;
        auto size = WireAlignSizeofN<WGPUCompilationMessageTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUCompilationMessageGetExtraRequiredSize(record.messages[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUCompilationInfoGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUCompilationInfoSerialize(
    const WGPUCompilationInfo& record,
    WGPUCompilationInfoTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->messageCount = record.messageCount;
    {
        auto memberLength = record.messageCount;

        WGPUCompilationMessageTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCompilationMessageSerialize(record.messages[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCompilationInfoSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUCompilationInfoDeserialize(
    WGPUCompilationInfo* record,
    const volatile WGPUCompilationInfoTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    if (transfer->messageCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->messageCount = checked_cast<size_t>(transfer->messageCount);
    {
        auto memberLength = record->messageCount;
        const volatile WGPUCompilationMessageTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUCompilationMessage* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->messages = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCompilationMessageDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUCompilationInfoDeserialize);

struct WGPUComputePassDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    uint64_t timestampWriteCount;
};


DAWN_DECLARE_UNUSED size_t WGPUComputePassDescriptorGetExtraRequiredSize(const WGPUComputePassDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.timestampWriteCount;
        auto size = WireAlignSizeofN<WGPUComputePassTimestampWriteTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUComputePassTimestampWriteGetExtraRequiredSize(record.timestampWrites[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUComputePassDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUComputePassDescriptorSerialize(
    const WGPUComputePassDescriptor& record,
    WGPUComputePassDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->timestampWriteCount = record.timestampWriteCount;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.timestampWriteCount;

        WGPUComputePassTimestampWriteTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePassTimestampWriteSerialize(record.timestampWrites[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePassDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUComputePassDescriptorDeserialize(
    WGPUComputePassDescriptor* record,
    const volatile WGPUComputePassDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    if (transfer->timestampWriteCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->timestampWriteCount = checked_cast<size_t>(transfer->timestampWriteCount);
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->timestampWriteCount;
        const volatile WGPUComputePassTimestampWriteTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUComputePassTimestampWrite* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->timestampWrites = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePassTimestampWriteDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePassDescriptorDeserialize);

struct WGPUDepthStencilStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureFormat format;
    bool depthWriteEnabled;
    WGPUCompareFunction depthCompare;
    WGPUStencilFaceStateTransfer stencilFront;
    WGPUStencilFaceStateTransfer stencilBack;
    uint32_t stencilReadMask;
    uint32_t stencilWriteMask;
    int32_t depthBias;
    float depthBiasSlopeScale;
    float depthBiasClamp;
};


DAWN_DECLARE_UNUSED size_t WGPUDepthStencilStateGetExtraRequiredSize(const WGPUDepthStencilState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPUStencilFaceStateGetExtraRequiredSize(record.stencilFront);
    }
    {
        result += WGPUStencilFaceStateGetExtraRequiredSize(record.stencilBack);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDepthStencilStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDepthStencilStateSerialize(
    const WGPUDepthStencilState& record,
    WGPUDepthStencilStateTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->format = record.format;
    transfer->depthWriteEnabled = record.depthWriteEnabled;
    transfer->depthCompare = record.depthCompare;
    WIRE_TRY(WGPUStencilFaceStateSerialize(record.stencilFront, &transfer->stencilFront, buffer));
    WIRE_TRY(WGPUStencilFaceStateSerialize(record.stencilBack, &transfer->stencilBack, buffer));
    transfer->stencilReadMask = record.stencilReadMask;
    transfer->stencilWriteMask = record.stencilWriteMask;
    transfer->depthBias = record.depthBias;
    transfer->depthBiasSlopeScale = record.depthBiasSlopeScale;
    transfer->depthBiasClamp = record.depthBiasClamp;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDepthStencilStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDepthStencilStateDeserialize(
    WGPUDepthStencilState* record,
    const volatile WGPUDepthStencilStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->depthWriteEnabled) >= sizeof(transfer->depthWriteEnabled), "Deserialize assignment may not narrow.");
    record->depthWriteEnabled = transfer->depthWriteEnabled;
    static_assert(sizeof(record->depthCompare) >= sizeof(transfer->depthCompare), "Deserialize assignment may not narrow.");
    record->depthCompare = transfer->depthCompare;
    static_assert(sizeof(record->stencilFront) == sizeof(transfer->stencilFront), "Deserialize memcpy size must match.");
    memcpy(&record->stencilFront, const_cast<const WGPUStencilFaceStateTransfer*>(&transfer->stencilFront), sizeof(WGPUStencilFaceStateTransfer));
    static_assert(sizeof(record->stencilBack) == sizeof(transfer->stencilBack), "Deserialize memcpy size must match.");
    memcpy(&record->stencilBack, const_cast<const WGPUStencilFaceStateTransfer*>(&transfer->stencilBack), sizeof(WGPUStencilFaceStateTransfer));
    static_assert(sizeof(record->stencilReadMask) >= sizeof(transfer->stencilReadMask), "Deserialize assignment may not narrow.");
    record->stencilReadMask = transfer->stencilReadMask;
    static_assert(sizeof(record->stencilWriteMask) >= sizeof(transfer->stencilWriteMask), "Deserialize assignment may not narrow.");
    record->stencilWriteMask = transfer->stencilWriteMask;
    static_assert(sizeof(record->depthBias) >= sizeof(transfer->depthBias), "Deserialize assignment may not narrow.");
    record->depthBias = transfer->depthBias;
    static_assert(sizeof(record->depthBiasSlopeScale) >= sizeof(transfer->depthBiasSlopeScale), "Deserialize assignment may not narrow.");
    record->depthBiasSlopeScale = transfer->depthBiasSlopeScale;
    static_assert(sizeof(record->depthBiasClamp) >= sizeof(transfer->depthBiasClamp), "Deserialize assignment may not narrow.");
    record->depthBiasClamp = transfer->depthBiasClamp;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDepthStencilStateDeserialize);

struct WGPUExternalTextureDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    ObjectId plane0;
    ObjectId plane1;
    WGPUOrigin2DTransfer visibleOrigin;
    WGPUExtent2DTransfer visibleSize;
    bool doYuvToRgbConversionOnly;
    bool has_yuvToRgbConversionMatrix;
    bool flipY;
    WGPUExternalTextureRotation rotation;
};


DAWN_DECLARE_UNUSED size_t WGPUExternalTextureDescriptorGetExtraRequiredSize(const WGPUExternalTextureDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        result += WGPUOrigin2DGetExtraRequiredSize(record.visibleOrigin);
    }
    {
        result += WGPUExtent2DGetExtraRequiredSize(record.visibleSize);
    }
    if (record.yuvToRgbConversionMatrix != nullptr) {
        auto memberLength = 12u;
        auto size = WireAlignSizeofN<float>(memberLength);
        ASSERT(size);
        result += *size;
    }
    {
        auto memberLength = 7u;
        auto size = WireAlignSizeofN<float>(memberLength);
        ASSERT(size);
        result += *size;
    }
    {
        auto memberLength = 7u;
        auto size = WireAlignSizeofN<float>(memberLength);
        ASSERT(size);
        result += *size;
    }
    {
        auto memberLength = 9u;
        auto size = WireAlignSizeofN<float>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUExternalTextureDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUExternalTextureDescriptorSerialize(
    const WGPUExternalTextureDescriptor& record,
    WGPUExternalTextureDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetId(record.plane0, &transfer->plane0));
    WIRE_TRY(provider.GetOptionalId(record.plane1, &transfer->plane1));
    WIRE_TRY(WGPUOrigin2DSerialize(record.visibleOrigin, &transfer->visibleOrigin, buffer));
    WIRE_TRY(WGPUExtent2DSerialize(record.visibleSize, &transfer->visibleSize, buffer));
    transfer->doYuvToRgbConversionOnly = record.doYuvToRgbConversionOnly;
    transfer->flipY = record.flipY;
    transfer->rotation = record.rotation;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    bool has_yuvToRgbConversionMatrix = record.yuvToRgbConversionMatrix != nullptr;
    transfer->has_yuvToRgbConversionMatrix = has_yuvToRgbConversionMatrix;
    if (has_yuvToRgbConversionMatrix) {
        auto memberLength = 12u;

        float* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.yuvToRgbConversionMatrix,
            sizeof(float) * memberLength);
    }
    {
        auto memberLength = 7u;

        float* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.srcTransferFunctionParameters,
            sizeof(float) * memberLength);
    }
    {
        auto memberLength = 7u;

        float* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.dstTransferFunctionParameters,
            sizeof(float) * memberLength);
    }
    {
        auto memberLength = 9u;

        float* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.gamutConversionMatrix,
            sizeof(float) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExternalTextureDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUExternalTextureDescriptorDeserialize(
    WGPUExternalTextureDescriptor* record,
    const volatile WGPUExternalTextureDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetFromId(transfer->plane0, &record->plane0));
    WIRE_TRY(resolver.GetOptionalFromId(transfer->plane1, &record->plane1));
    static_assert(sizeof(record->visibleOrigin) == sizeof(transfer->visibleOrigin), "Deserialize memcpy size must match.");
    memcpy(&record->visibleOrigin, const_cast<const WGPUOrigin2DTransfer*>(&transfer->visibleOrigin), sizeof(WGPUOrigin2DTransfer));
    static_assert(sizeof(record->visibleSize) == sizeof(transfer->visibleSize), "Deserialize memcpy size must match.");
    memcpy(&record->visibleSize, const_cast<const WGPUExtent2DTransfer*>(&transfer->visibleSize), sizeof(WGPUExtent2DTransfer));
    static_assert(sizeof(record->doYuvToRgbConversionOnly) >= sizeof(transfer->doYuvToRgbConversionOnly), "Deserialize assignment may not narrow.");
    record->doYuvToRgbConversionOnly = transfer->doYuvToRgbConversionOnly;
    static_assert(sizeof(record->flipY) >= sizeof(transfer->flipY), "Deserialize assignment may not narrow.");
    record->flipY = transfer->flipY;
    static_assert(sizeof(record->rotation) >= sizeof(transfer->rotation), "Deserialize assignment may not narrow.");
    record->rotation = transfer->rotation;
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    bool has_yuvToRgbConversionMatrix = transfer->has_yuvToRgbConversionMatrix;
    record->yuvToRgbConversionMatrix = nullptr;
    if (has_yuvToRgbConversionMatrix) {
        auto memberLength = 12u;
        const volatile float* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        float* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->yuvToRgbConversionMatrix = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const float*>(memberBuffer),
           sizeof(float) * memberLength);
    }
    {
        auto memberLength = 7u;
        const volatile float* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        float* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->srcTransferFunctionParameters = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const float*>(memberBuffer),
           sizeof(float) * memberLength);
    }
    {
        auto memberLength = 7u;
        const volatile float* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        float* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dstTransferFunctionParameters = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const float*>(memberBuffer),
           sizeof(float) * memberLength);
    }
    {
        auto memberLength = 9u;
        const volatile float* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        float* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->gamutConversionMatrix = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const float*>(memberBuffer),
           sizeof(float) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUExternalTextureDescriptorDeserialize);

struct WGPUImageCopyBufferTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureDataLayoutTransfer layout;
    ObjectId buffer;
};


DAWN_DECLARE_UNUSED size_t WGPUImageCopyBufferGetExtraRequiredSize(const WGPUImageCopyBuffer& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPUTextureDataLayoutGetExtraRequiredSize(record.layout);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUImageCopyBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUImageCopyBufferSerialize(
    const WGPUImageCopyBuffer& record,
    WGPUImageCopyBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(WGPUTextureDataLayoutSerialize(record.layout, &transfer->layout, buffer, provider));
    WIRE_TRY(provider.GetId(record.buffer, &transfer->buffer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUImageCopyBufferSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUImageCopyBufferDeserialize(
    WGPUImageCopyBuffer* record,
    const volatile WGPUImageCopyBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(WGPUTextureDataLayoutDeserialize(&record->layout, &transfer->layout, deserializeBuffer, allocator, resolver));
    WIRE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUImageCopyBufferDeserialize);

struct WGPUImageCopyExternalTextureTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId externalTexture;
    WGPUOrigin3DTransfer origin;
    WGPUExtent2DTransfer naturalSize;
};


DAWN_DECLARE_UNUSED size_t WGPUImageCopyExternalTextureGetExtraRequiredSize(const WGPUImageCopyExternalTexture& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPUOrigin3DGetExtraRequiredSize(record.origin);
    }
    {
        result += WGPUExtent2DGetExtraRequiredSize(record.naturalSize);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUImageCopyExternalTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUImageCopyExternalTextureSerialize(
    const WGPUImageCopyExternalTexture& record,
    WGPUImageCopyExternalTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetId(record.externalTexture, &transfer->externalTexture));
    WIRE_TRY(WGPUOrigin3DSerialize(record.origin, &transfer->origin, buffer));
    WIRE_TRY(WGPUExtent2DSerialize(record.naturalSize, &transfer->naturalSize, buffer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUImageCopyExternalTextureSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUImageCopyExternalTextureDeserialize(
    WGPUImageCopyExternalTexture* record,
    const volatile WGPUImageCopyExternalTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetFromId(transfer->externalTexture, &record->externalTexture));
    static_assert(sizeof(record->origin) == sizeof(transfer->origin), "Deserialize memcpy size must match.");
    memcpy(&record->origin, const_cast<const WGPUOrigin3DTransfer*>(&transfer->origin), sizeof(WGPUOrigin3DTransfer));
    static_assert(sizeof(record->naturalSize) == sizeof(transfer->naturalSize), "Deserialize memcpy size must match.");
    memcpy(&record->naturalSize, const_cast<const WGPUExtent2DTransfer*>(&transfer->naturalSize), sizeof(WGPUExtent2DTransfer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUImageCopyExternalTextureDeserialize);

struct WGPUImageCopyTextureTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId texture;
    uint32_t mipLevel;
    WGPUOrigin3DTransfer origin;
    WGPUTextureAspect aspect;
};


DAWN_DECLARE_UNUSED size_t WGPUImageCopyTextureGetExtraRequiredSize(const WGPUImageCopyTexture& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPUOrigin3DGetExtraRequiredSize(record.origin);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUImageCopyTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUImageCopyTextureSerialize(
    const WGPUImageCopyTexture& record,
    WGPUImageCopyTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetId(record.texture, &transfer->texture));
    transfer->mipLevel = record.mipLevel;
    WIRE_TRY(WGPUOrigin3DSerialize(record.origin, &transfer->origin, buffer));
    transfer->aspect = record.aspect;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUImageCopyTextureSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUImageCopyTextureDeserialize(
    WGPUImageCopyTexture* record,
    const volatile WGPUImageCopyTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetFromId(transfer->texture, &record->texture));
    static_assert(sizeof(record->mipLevel) >= sizeof(transfer->mipLevel), "Deserialize assignment may not narrow.");
    record->mipLevel = transfer->mipLevel;
    static_assert(sizeof(record->origin) == sizeof(transfer->origin), "Deserialize memcpy size must match.");
    memcpy(&record->origin, const_cast<const WGPUOrigin3DTransfer*>(&transfer->origin), sizeof(WGPUOrigin3DTransfer));
    static_assert(sizeof(record->aspect) >= sizeof(transfer->aspect), "Deserialize assignment may not narrow.");
    record->aspect = transfer->aspect;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUImageCopyTextureDeserialize);

struct WGPUProgrammableStageDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId module;
    uint64_t entryPointStrlen;
    uint64_t constantCount;
};


DAWN_DECLARE_UNUSED size_t WGPUProgrammableStageDescriptorGetExtraRequiredSize(const WGPUProgrammableStageDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    ASSERT(record.entryPoint != nullptr);
    result += Align(std::strlen(record.entryPoint), kWireBufferAlignment);
    {
        auto memberLength = record.constantCount;
        auto size = WireAlignSizeofN<WGPUConstantEntryTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUConstantEntryGetExtraRequiredSize(record.constants[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUProgrammableStageDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUProgrammableStageDescriptorSerialize(
    const WGPUProgrammableStageDescriptor& record,
    WGPUProgrammableStageDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetId(record.module, &transfer->module));
    transfer->constantCount = record.constantCount;
    {
        transfer->entryPointStrlen = std::strlen(record.entryPoint);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->entryPointStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.entryPoint, transfer->entryPointStrlen);
    }
    {
        auto memberLength = record.constantCount;

        WGPUConstantEntryTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUConstantEntrySerialize(record.constants[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUProgrammableStageDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUProgrammableStageDescriptorDeserialize(
    WGPUProgrammableStageDescriptor* record,
    const volatile WGPUProgrammableStageDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetFromId(transfer->module, &record->module));
    if (transfer->constantCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->constantCount = checked_cast<size_t>(transfer->constantCount);
    {
        uint64_t stringLength64 = transfer->entryPointStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->entryPoint = copiedString;
    }
    {
        auto memberLength = record->constantCount;
        const volatile WGPUConstantEntryTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUConstantEntry* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->constants = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUConstantEntryDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUProgrammableStageDescriptorDeserialize);

struct WGPURenderPassColorAttachmentTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId view;
    ObjectId resolveTarget;
    WGPULoadOp loadOp;
    WGPUStoreOp storeOp;
    WGPUColorTransfer clearValue;
};


DAWN_DECLARE_UNUSED size_t WGPURenderPassColorAttachmentGetExtraRequiredSize(const WGPURenderPassColorAttachment& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPUColorGetExtraRequiredSize(record.clearValue);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassColorAttachmentGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassColorAttachmentSerialize(
    const WGPURenderPassColorAttachment& record,
    WGPURenderPassColorAttachmentTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetOptionalId(record.view, &transfer->view));
    WIRE_TRY(provider.GetOptionalId(record.resolveTarget, &transfer->resolveTarget));
    transfer->loadOp = record.loadOp;
    transfer->storeOp = record.storeOp;
    WIRE_TRY(WGPUColorSerialize(record.clearValue, &transfer->clearValue, buffer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassColorAttachmentSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassColorAttachmentDeserialize(
    WGPURenderPassColorAttachment* record,
    const volatile WGPURenderPassColorAttachmentTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetOptionalFromId(transfer->view, &record->view));
    WIRE_TRY(resolver.GetOptionalFromId(transfer->resolveTarget, &record->resolveTarget));
    static_assert(sizeof(record->loadOp) >= sizeof(transfer->loadOp), "Deserialize assignment may not narrow.");
    record->loadOp = transfer->loadOp;
    static_assert(sizeof(record->storeOp) >= sizeof(transfer->storeOp), "Deserialize assignment may not narrow.");
    record->storeOp = transfer->storeOp;
    static_assert(sizeof(record->clearValue) == sizeof(transfer->clearValue), "Deserialize memcpy size must match.");
    memcpy(&record->clearValue, const_cast<const WGPUColorTransfer*>(&transfer->clearValue), sizeof(WGPUColorTransfer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassColorAttachmentDeserialize);

struct WGPURequiredLimitsTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPULimitsTransfer limits;
};


DAWN_DECLARE_UNUSED size_t WGPURequiredLimitsGetExtraRequiredSize(const WGPURequiredLimits& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPULimitsGetExtraRequiredSize(record.limits);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURequiredLimitsGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURequiredLimitsSerialize(
    const WGPURequiredLimits& record,
    WGPURequiredLimitsTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(WGPULimitsSerialize(record.limits, &transfer->limits, buffer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURequiredLimitsSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURequiredLimitsDeserialize(
    WGPURequiredLimits* record,
    const volatile WGPURequiredLimitsTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->limits) == sizeof(transfer->limits), "Deserialize memcpy size must match.");
    memcpy(&record->limits, const_cast<const WGPULimitsTransfer*>(&transfer->limits), sizeof(WGPULimitsTransfer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURequiredLimitsDeserialize);

struct WGPUSupportedLimitsTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPULimitsTransfer limits;
};


DAWN_DECLARE_UNUSED size_t WGPUSupportedLimitsGetExtraRequiredSize(const WGPUSupportedLimits& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    {
        result += WGPULimitsGetExtraRequiredSize(record.limits);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUSupportedLimitsGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUSupportedLimitsSerialize(
    const WGPUSupportedLimits& record,
    WGPUSupportedLimitsTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(WGPULimitsSerialize(record.limits, &transfer->limits, buffer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSupportedLimitsSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUSupportedLimitsDeserialize(
    WGPUSupportedLimits* record,
    const volatile WGPUSupportedLimitsTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->limits) == sizeof(transfer->limits), "Deserialize memcpy size must match.");
    memcpy(&record->limits, const_cast<const WGPULimitsTransfer*>(&transfer->limits), sizeof(WGPULimitsTransfer));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUSupportedLimitsDeserialize);

struct WGPUTextureDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    WGPUTextureUsageFlags usage;
    WGPUTextureDimension dimension;
    WGPUExtent3DTransfer size;
    WGPUTextureFormat format;
    uint32_t mipLevelCount;
    uint32_t sampleCount;
    uint64_t viewFormatCount;
};


DAWN_DECLARE_UNUSED size_t WGPUTextureDescriptorGetExtraRequiredSize(const WGPUTextureDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        result += WGPUExtent3DGetExtraRequiredSize(record.size);
    }
    {
        auto memberLength = record.viewFormatCount;
        auto size = WireAlignSizeofN<WGPUTextureFormat>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUTextureDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureDescriptorSerialize(
    const WGPUTextureDescriptor& record,
    WGPUTextureDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->usage = record.usage;
    transfer->dimension = record.dimension;
    WIRE_TRY(WGPUExtent3DSerialize(record.size, &transfer->size, buffer));
    transfer->format = record.format;
    transfer->mipLevelCount = record.mipLevelCount;
    transfer->sampleCount = record.sampleCount;
    transfer->viewFormatCount = record.viewFormatCount;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.viewFormatCount;

        WGPUTextureFormat* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.viewFormats,
            sizeof(WGPUTextureFormat) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUTextureDescriptorDeserialize(
    WGPUTextureDescriptor* record,
    const volatile WGPUTextureDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->usage) >= sizeof(transfer->usage), "Deserialize assignment may not narrow.");
    record->usage = transfer->usage;
    static_assert(sizeof(record->dimension) >= sizeof(transfer->dimension), "Deserialize assignment may not narrow.");
    record->dimension = transfer->dimension;
    static_assert(sizeof(record->size) == sizeof(transfer->size), "Deserialize memcpy size must match.");
    memcpy(&record->size, const_cast<const WGPUExtent3DTransfer*>(&transfer->size), sizeof(WGPUExtent3DTransfer));
    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->mipLevelCount) >= sizeof(transfer->mipLevelCount), "Deserialize assignment may not narrow.");
    record->mipLevelCount = transfer->mipLevelCount;
    static_assert(sizeof(record->sampleCount) >= sizeof(transfer->sampleCount), "Deserialize assignment may not narrow.");
    record->sampleCount = transfer->sampleCount;
    if (transfer->viewFormatCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->viewFormatCount = checked_cast<size_t>(transfer->viewFormatCount);
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->viewFormatCount;
        const volatile WGPUTextureFormat* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUTextureFormat* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->viewFormats = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUTextureFormat*>(memberBuffer),
           sizeof(WGPUTextureFormat) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUTextureDescriptorDeserialize);

struct WGPUVertexBufferLayoutTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");

    uint64_t arrayStride;
    WGPUVertexStepMode stepMode;
    uint64_t attributeCount;
};


DAWN_DECLARE_UNUSED size_t WGPUVertexBufferLayoutGetExtraRequiredSize(const WGPUVertexBufferLayout& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.attributeCount;
        auto size = WireAlignSizeofN<WGPUVertexAttributeTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUVertexAttributeGetExtraRequiredSize(record.attributes[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUVertexBufferLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUVertexBufferLayoutSerialize(
    const WGPUVertexBufferLayout& record,
    WGPUVertexBufferLayoutTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);


    transfer->arrayStride = record.arrayStride;
    transfer->stepMode = record.stepMode;
    transfer->attributeCount = record.attributeCount;
    {
        auto memberLength = record.attributeCount;

        WGPUVertexAttributeTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.attributes,
            sizeof(WGPUVertexAttributeTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexBufferLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUVertexBufferLayoutDeserialize(
    WGPUVertexBufferLayout* record,
    const volatile WGPUVertexBufferLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);



    static_assert(sizeof(record->arrayStride) >= sizeof(transfer->arrayStride), "Deserialize assignment may not narrow.");
    record->arrayStride = transfer->arrayStride;
    static_assert(sizeof(record->stepMode) >= sizeof(transfer->stepMode), "Deserialize assignment may not narrow.");
    record->stepMode = transfer->stepMode;
    if (transfer->attributeCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->attributeCount = checked_cast<size_t>(transfer->attributeCount);
    {
        auto memberLength = record->attributeCount;
        const volatile WGPUVertexAttributeTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUVertexAttribute* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->attributes = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUVertexAttributeTransfer*>(memberBuffer),
           sizeof(WGPUVertexAttributeTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexBufferLayoutDeserialize);

struct WGPUBindGroupLayoutDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    uint64_t entryCount;
};


DAWN_DECLARE_UNUSED size_t WGPUBindGroupLayoutDescriptorGetExtraRequiredSize(const WGPUBindGroupLayoutDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.entryCount;
        auto size = WireAlignSizeofN<WGPUBindGroupLayoutEntryTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUBindGroupLayoutEntryGetExtraRequiredSize(record.entries[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupLayoutDescriptorSerialize(
    const WGPUBindGroupLayoutDescriptor& record,
    WGPUBindGroupLayoutDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->entryCount = record.entryCount;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.entryCount;

        WGPUBindGroupLayoutEntryTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupLayoutEntrySerialize(record.entries[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUBindGroupLayoutDescriptorDeserialize(
    WGPUBindGroupLayoutDescriptor* record,
    const volatile WGPUBindGroupLayoutDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    if (transfer->entryCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->entryCount = checked_cast<size_t>(transfer->entryCount);
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->entryCount;
        const volatile WGPUBindGroupLayoutEntryTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBindGroupLayoutEntry* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->entries = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupLayoutEntryDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUBindGroupLayoutDescriptorDeserialize);

struct WGPUColorTargetStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    WGPUTextureFormat format;
    bool has_blend;
    WGPUColorWriteMaskFlags writeMask;
};


DAWN_DECLARE_UNUSED size_t WGPUColorTargetStateGetExtraRequiredSize(const WGPUColorTargetState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.blend != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUBlendStateTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUBlendStateGetExtraRequiredSize(record.blend[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUColorTargetStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUColorTargetStateSerialize(
    const WGPUColorTargetState& record,
    WGPUColorTargetStateTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->format = record.format;
    transfer->writeMask = record.writeMask;
    bool has_blend = record.blend != nullptr;
    transfer->has_blend = has_blend;
    if (has_blend) {
        auto memberLength = 1u;

        WGPUBlendStateTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.blend,
            sizeof(WGPUBlendStateTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUColorTargetStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUColorTargetStateDeserialize(
    WGPUColorTargetState* record,
    const volatile WGPUColorTargetStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->writeMask) >= sizeof(transfer->writeMask), "Deserialize assignment may not narrow.");
    record->writeMask = transfer->writeMask;
    bool has_blend = transfer->has_blend;
    record->blend = nullptr;
    if (has_blend) {
        auto memberLength = 1u;
        const volatile WGPUBlendStateTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBlendState* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->blend = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUBlendStateTransfer*>(memberBuffer),
           sizeof(WGPUBlendStateTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUColorTargetStateDeserialize);

struct WGPUComputePipelineDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    ObjectId layout;
    WGPUProgrammableStageDescriptorTransfer compute;
};


DAWN_DECLARE_UNUSED size_t WGPUComputePipelineDescriptorGetExtraRequiredSize(const WGPUComputePipelineDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        result += WGPUProgrammableStageDescriptorGetExtraRequiredSize(record.compute);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUComputePipelineDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUComputePipelineDescriptorSerialize(
    const WGPUComputePipelineDescriptor& record,
    WGPUComputePipelineDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetOptionalId(record.layout, &transfer->layout));
    WIRE_TRY(WGPUProgrammableStageDescriptorSerialize(record.compute, &transfer->compute, buffer, provider));
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePipelineDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUComputePipelineDescriptorDeserialize(
    WGPUComputePipelineDescriptor* record,
    const volatile WGPUComputePipelineDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetOptionalFromId(transfer->layout, &record->layout));
    WIRE_TRY(WGPUProgrammableStageDescriptorDeserialize(&record->compute, &transfer->compute, deserializeBuffer, allocator, resolver));
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUComputePipelineDescriptorDeserialize);

struct WGPUDeviceDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    uint64_t requiredFeaturesCount;
    bool has_requiredLimits;
    WGPUQueueDescriptorTransfer defaultQueue;
};


DAWN_DECLARE_UNUSED size_t WGPUDeviceDescriptorGetExtraRequiredSize(const WGPUDeviceDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.requiredFeaturesCount;
        auto size = WireAlignSizeofN<WGPUFeatureName>(memberLength);
        ASSERT(size);
        result += *size;
    }
    if (record.requiredLimits != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURequiredLimitsTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURequiredLimitsGetExtraRequiredSize(record.requiredLimits[i]);
        }
    }
    {
        result += WGPUQueueDescriptorGetExtraRequiredSize(record.defaultQueue);
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUDeviceDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUDeviceDescriptorSerialize(
    const WGPUDeviceDescriptor& record,
    WGPUDeviceDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->requiredFeaturesCount = record.requiredFeaturesCount;
    WIRE_TRY(WGPUQueueDescriptorSerialize(record.defaultQueue, &transfer->defaultQueue, buffer, provider));
    if (record.deviceLostCallback != nullptr) return WireResult::FatalError;
    if (record.deviceLostUserdata != nullptr) return WireResult::FatalError;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.requiredFeaturesCount;

        WGPUFeatureName* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.requiredFeatures,
            sizeof(WGPUFeatureName) * memberLength);
    }
    bool has_requiredLimits = record.requiredLimits != nullptr;
    transfer->has_requiredLimits = has_requiredLimits;
    if (has_requiredLimits) {
        auto memberLength = 1u;

        WGPURequiredLimitsTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURequiredLimitsSerialize(record.requiredLimits[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDeviceDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUDeviceDescriptorDeserialize(
    WGPUDeviceDescriptor* record,
    const volatile WGPUDeviceDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    if (transfer->requiredFeaturesCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->requiredFeaturesCount = checked_cast<size_t>(transfer->requiredFeaturesCount);
    WIRE_TRY(WGPUQueueDescriptorDeserialize(&record->defaultQueue, &transfer->defaultQueue, deserializeBuffer, allocator, resolver));
    record->deviceLostCallback = nullptr;
    record->deviceLostUserdata = nullptr;
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->requiredFeaturesCount;
        const volatile WGPUFeatureName* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUFeatureName* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->requiredFeatures = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUFeatureName*>(memberBuffer),
           sizeof(WGPUFeatureName) * memberLength);
    }
    bool has_requiredLimits = transfer->has_requiredLimits;
    record->requiredLimits = nullptr;
    if (has_requiredLimits) {
        auto memberLength = 1u;
        const volatile WGPURequiredLimitsTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURequiredLimits* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->requiredLimits = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURequiredLimitsDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUDeviceDescriptorDeserialize);

struct WGPURenderPassDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    uint64_t colorAttachmentCount;
    bool has_depthStencilAttachment;
    ObjectId occlusionQuerySet;
    uint64_t timestampWriteCount;
};


DAWN_DECLARE_UNUSED size_t WGPURenderPassDescriptorGetExtraRequiredSize(const WGPURenderPassDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        auto memberLength = record.colorAttachmentCount;
        auto size = WireAlignSizeofN<WGPURenderPassColorAttachmentTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderPassColorAttachmentGetExtraRequiredSize(record.colorAttachments[i]);
        }
    }
    if (record.depthStencilAttachment != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURenderPassDepthStencilAttachmentTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderPassDepthStencilAttachmentGetExtraRequiredSize(record.depthStencilAttachment[i]);
        }
    }
    {
        auto memberLength = record.timestampWriteCount;
        auto size = WireAlignSizeofN<WGPURenderPassTimestampWriteTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderPassTimestampWriteGetExtraRequiredSize(record.timestampWrites[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassDescriptorSerialize(
    const WGPURenderPassDescriptor& record,
    WGPURenderPassDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    transfer->colorAttachmentCount = record.colorAttachmentCount;
    WIRE_TRY(provider.GetOptionalId(record.occlusionQuerySet, &transfer->occlusionQuerySet));
    transfer->timestampWriteCount = record.timestampWriteCount;
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    {
        auto memberLength = record.colorAttachmentCount;

        WGPURenderPassColorAttachmentTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassColorAttachmentSerialize(record.colorAttachments[i], &memberBuffer[i], buffer, provider));
        }
    }
    bool has_depthStencilAttachment = record.depthStencilAttachment != nullptr;
    transfer->has_depthStencilAttachment = has_depthStencilAttachment;
    if (has_depthStencilAttachment) {
        auto memberLength = 1u;

        WGPURenderPassDepthStencilAttachmentTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassDepthStencilAttachmentSerialize(record.depthStencilAttachment[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = record.timestampWriteCount;

        WGPURenderPassTimestampWriteTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassTimestampWriteSerialize(record.timestampWrites[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPassDescriptorDeserialize(
    WGPURenderPassDescriptor* record,
    const volatile WGPURenderPassDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    if (transfer->colorAttachmentCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->colorAttachmentCount = checked_cast<size_t>(transfer->colorAttachmentCount);
    WIRE_TRY(resolver.GetOptionalFromId(transfer->occlusionQuerySet, &record->occlusionQuerySet));
    if (transfer->timestampWriteCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->timestampWriteCount = checked_cast<size_t>(transfer->timestampWriteCount);
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    {
        auto memberLength = record->colorAttachmentCount;
        const volatile WGPURenderPassColorAttachmentTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderPassColorAttachment* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->colorAttachments = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassColorAttachmentDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    bool has_depthStencilAttachment = transfer->has_depthStencilAttachment;
    record->depthStencilAttachment = nullptr;
    if (has_depthStencilAttachment) {
        auto memberLength = 1u;
        const volatile WGPURenderPassDepthStencilAttachmentTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderPassDepthStencilAttachment* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->depthStencilAttachment = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassDepthStencilAttachmentDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = record->timestampWriteCount;
        const volatile WGPURenderPassTimestampWriteTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderPassTimestampWrite* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->timestampWrites = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassTimestampWriteDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPassDescriptorDeserialize);

struct WGPUVertexStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId module;
    uint64_t entryPointStrlen;
    uint64_t constantCount;
    uint64_t bufferCount;
};


DAWN_DECLARE_UNUSED size_t WGPUVertexStateGetExtraRequiredSize(const WGPUVertexState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    ASSERT(record.entryPoint != nullptr);
    result += Align(std::strlen(record.entryPoint), kWireBufferAlignment);
    {
        auto memberLength = record.constantCount;
        auto size = WireAlignSizeofN<WGPUConstantEntryTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUConstantEntryGetExtraRequiredSize(record.constants[i]);
        }
    }
    {
        auto memberLength = record.bufferCount;
        auto size = WireAlignSizeofN<WGPUVertexBufferLayoutTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUVertexBufferLayoutGetExtraRequiredSize(record.buffers[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUVertexStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUVertexStateSerialize(
    const WGPUVertexState& record,
    WGPUVertexStateTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetId(record.module, &transfer->module));
    transfer->constantCount = record.constantCount;
    transfer->bufferCount = record.bufferCount;
    {
        transfer->entryPointStrlen = std::strlen(record.entryPoint);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->entryPointStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.entryPoint, transfer->entryPointStrlen);
    }
    {
        auto memberLength = record.constantCount;

        WGPUConstantEntryTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUConstantEntrySerialize(record.constants[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = record.bufferCount;

        WGPUVertexBufferLayoutTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUVertexBufferLayoutSerialize(record.buffers[i], &memberBuffer[i], buffer));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUVertexStateDeserialize(
    WGPUVertexState* record,
    const volatile WGPUVertexStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetFromId(transfer->module, &record->module));
    if (transfer->constantCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->constantCount = checked_cast<size_t>(transfer->constantCount);
    if (transfer->bufferCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->bufferCount = checked_cast<size_t>(transfer->bufferCount);
    {
        uint64_t stringLength64 = transfer->entryPointStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->entryPoint = copiedString;
    }
    {
        auto memberLength = record->constantCount;
        const volatile WGPUConstantEntryTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUConstantEntry* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->constants = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUConstantEntryDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = record->bufferCount;
        const volatile WGPUVertexBufferLayoutTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUVertexBufferLayout* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->buffers = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUVertexBufferLayoutDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUVertexStateDeserialize);

struct WGPUFragmentStateTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    ObjectId module;
    uint64_t entryPointStrlen;
    uint64_t constantCount;
    uint64_t targetCount;
};


DAWN_DECLARE_UNUSED size_t WGPUFragmentStateGetExtraRequiredSize(const WGPUFragmentState& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    ASSERT(record.entryPoint != nullptr);
    result += Align(std::strlen(record.entryPoint), kWireBufferAlignment);
    {
        auto memberLength = record.constantCount;
        auto size = WireAlignSizeofN<WGPUConstantEntryTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUConstantEntryGetExtraRequiredSize(record.constants[i]);
        }
    }
    {
        auto memberLength = record.targetCount;
        auto size = WireAlignSizeofN<WGPUColorTargetStateTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUColorTargetStateGetExtraRequiredSize(record.targets[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPUFragmentStateGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPUFragmentStateSerialize(
    const WGPUFragmentState& record,
    WGPUFragmentStateTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetId(record.module, &transfer->module));
    transfer->constantCount = record.constantCount;
    transfer->targetCount = record.targetCount;
    {
        transfer->entryPointStrlen = std::strlen(record.entryPoint);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->entryPointStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.entryPoint, transfer->entryPointStrlen);
    }
    {
        auto memberLength = record.constantCount;

        WGPUConstantEntryTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUConstantEntrySerialize(record.constants[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = record.targetCount;

        WGPUColorTargetStateTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUColorTargetStateSerialize(record.targets[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUFragmentStateSerialize);

DAWN_DECLARE_UNUSED WireResult WGPUFragmentStateDeserialize(
    WGPUFragmentState* record,
    const volatile WGPUFragmentStateTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetFromId(transfer->module, &record->module));
    if (transfer->constantCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->constantCount = checked_cast<size_t>(transfer->constantCount);
    if (transfer->targetCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->targetCount = checked_cast<size_t>(transfer->targetCount);
    {
        uint64_t stringLength64 = transfer->entryPointStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->entryPoint = copiedString;
    }
    {
        auto memberLength = record->constantCount;
        const volatile WGPUConstantEntryTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUConstantEntry* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->constants = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUConstantEntryDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = record->targetCount;
        const volatile WGPUColorTargetStateTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUColorTargetState* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->targets = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUColorTargetStateDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPUFragmentStateDeserialize);

struct WGPURenderPipelineDescriptorTransfer {
    static_assert(0 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    bool hasNextInChain;

    uint64_t labelStrlen;
    bool has_label;
    ObjectId layout;
    WGPUVertexStateTransfer vertex;
    WGPUPrimitiveStateTransfer primitive;
    bool has_depthStencil;
    WGPUMultisampleStateTransfer multisample;
    bool has_fragment;
};


DAWN_DECLARE_UNUSED size_t WGPURenderPipelineDescriptorGetExtraRequiredSize(const WGPURenderPipelineDescriptor& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.nextInChain != nullptr) {
        result += GetChainedStructExtraRequiredSize(record.nextInChain);
    }
    if (record.label != nullptr) {
        result += Align(std::strlen(record.label), kWireBufferAlignment);
    }
    {
        result += WGPUVertexStateGetExtraRequiredSize(record.vertex);
    }
    {
        result += WGPUPrimitiveStateGetExtraRequiredSize(record.primitive);
    }
    if (record.depthStencil != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUDepthStencilStateTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUDepthStencilStateGetExtraRequiredSize(record.depthStencil[i]);
        }
    }
    {
        result += WGPUMultisampleStateGetExtraRequiredSize(record.multisample);
    }
    if (record.fragment != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUFragmentStateTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUFragmentStateGetExtraRequiredSize(record.fragment[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPipelineDescriptorSerialize(
    const WGPURenderPipelineDescriptor& record,
    WGPURenderPipelineDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);

    if (record.nextInChain != nullptr) {
        transfer->hasNextInChain = true;
        WIRE_TRY(SerializeChainedStruct(record.nextInChain, buffer, provider));
    } else {
        transfer->hasNextInChain = false;
    }

    WIRE_TRY(provider.GetOptionalId(record.layout, &transfer->layout));
    WIRE_TRY(WGPUVertexStateSerialize(record.vertex, &transfer->vertex, buffer, provider));
    WIRE_TRY(WGPUPrimitiveStateSerialize(record.primitive, &transfer->primitive, buffer, provider));
    WIRE_TRY(WGPUMultisampleStateSerialize(record.multisample, &transfer->multisample, buffer, provider));
    bool has_label = record.label != nullptr;
    transfer->has_label = has_label;
    if (has_label) {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }
    bool has_depthStencil = record.depthStencil != nullptr;
    transfer->has_depthStencil = has_depthStencil;
    if (has_depthStencil) {
        auto memberLength = 1u;

        WGPUDepthStencilStateTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUDepthStencilStateSerialize(record.depthStencil[i], &memberBuffer[i], buffer, provider));
        }
    }
    bool has_fragment = record.fragment != nullptr;
    transfer->has_fragment = has_fragment;
    if (has_fragment) {
        auto memberLength = 1u;

        WGPUFragmentStateTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUFragmentStateSerialize(record.fragment[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult WGPURenderPipelineDescriptorDeserialize(
    WGPURenderPipelineDescriptor* record,
    const volatile WGPURenderPipelineDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);


    record->nextInChain = nullptr;
    if (transfer->hasNextInChain) {
        WIRE_TRY(DeserializeChainedStruct(&record->nextInChain, deserializeBuffer, allocator, resolver));
    }

    WIRE_TRY(resolver.GetOptionalFromId(transfer->layout, &record->layout));
    WIRE_TRY(WGPUVertexStateDeserialize(&record->vertex, &transfer->vertex, deserializeBuffer, allocator, resolver));
    WIRE_TRY(WGPUPrimitiveStateDeserialize(&record->primitive, &transfer->primitive, deserializeBuffer, allocator, resolver));
    WIRE_TRY(WGPUMultisampleStateDeserialize(&record->multisample, &transfer->multisample, deserializeBuffer, allocator, resolver));
    bool has_label = transfer->has_label;
    record->label = nullptr;
    if (has_label) {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }
    bool has_depthStencil = transfer->has_depthStencil;
    record->depthStencil = nullptr;
    if (has_depthStencil) {
        auto memberLength = 1u;
        const volatile WGPUDepthStencilStateTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUDepthStencilState* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->depthStencil = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUDepthStencilStateDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    bool has_fragment = transfer->has_fragment;
    record->fragment = nullptr;
    if (has_fragment) {
        auto memberLength = 1u;
        const volatile WGPUFragmentStateTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUFragmentState* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->fragment = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUFragmentStateDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(WGPURenderPipelineDescriptorDeserialize);


size_t GetChainedStructExtraRequiredSize(const WGPUChainedStruct* chainedStruct) {
    ASSERT(chainedStruct != nullptr);
    size_t result = 0;
    while (chainedStruct != nullptr) {
        switch (chainedStruct->sType) {
            case WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector: {
                const auto& typedStruct = *reinterpret_cast<WGPUSurfaceDescriptorFromCanvasHTMLSelector const *>(chainedStruct);
                result += WireAlignSizeof<WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer>();
                result += WGPUSurfaceDescriptorFromCanvasHTMLSelectorGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_ShaderModuleSPIRVDescriptor: {
                const auto& typedStruct = *reinterpret_cast<WGPUShaderModuleSPIRVDescriptor const *>(chainedStruct);
                result += WireAlignSizeof<WGPUShaderModuleSPIRVDescriptorTransfer>();
                result += WGPUShaderModuleSPIRVDescriptorGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_ShaderModuleWGSLDescriptor: {
                const auto& typedStruct = *reinterpret_cast<WGPUShaderModuleWGSLDescriptor const *>(chainedStruct);
                result += WireAlignSizeof<WGPUShaderModuleWGSLDescriptorTransfer>();
                result += WGPUShaderModuleWGSLDescriptorGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_PrimitiveDepthClipControl: {
                const auto& typedStruct = *reinterpret_cast<WGPUPrimitiveDepthClipControl const *>(chainedStruct);
                result += WireAlignSizeof<WGPUPrimitiveDepthClipControlTransfer>();
                result += WGPUPrimitiveDepthClipControlGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_ExternalTextureBindingEntry: {
                const auto& typedStruct = *reinterpret_cast<WGPUExternalTextureBindingEntry const *>(chainedStruct);
                result += WireAlignSizeof<WGPUExternalTextureBindingEntryTransfer>();
                result += WGPUExternalTextureBindingEntryGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_ExternalTextureBindingLayout: {
                const auto& typedStruct = *reinterpret_cast<WGPUExternalTextureBindingLayout const *>(chainedStruct);
                result += WireAlignSizeof<WGPUExternalTextureBindingLayoutTransfer>();
                result += WGPUExternalTextureBindingLayoutGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_RenderPassDescriptorMaxDrawCount: {
                const auto& typedStruct = *reinterpret_cast<WGPURenderPassDescriptorMaxDrawCount const *>(chainedStruct);
                result += WireAlignSizeof<WGPURenderPassDescriptorMaxDrawCountTransfer>();
                result += WGPURenderPassDescriptorMaxDrawCountGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_DawnTextureInternalUsageDescriptor: {
                const auto& typedStruct = *reinterpret_cast<WGPUDawnTextureInternalUsageDescriptor const *>(chainedStruct);
                result += WireAlignSizeof<WGPUDawnTextureInternalUsageDescriptorTransfer>();
                result += WGPUDawnTextureInternalUsageDescriptorGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_DawnEncoderInternalUsageDescriptor: {
                const auto& typedStruct = *reinterpret_cast<WGPUDawnEncoderInternalUsageDescriptor const *>(chainedStruct);
                result += WireAlignSizeof<WGPUDawnEncoderInternalUsageDescriptorTransfer>();
                result += WGPUDawnEncoderInternalUsageDescriptorGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient: {
                const auto& typedStruct = *reinterpret_cast<WGPUDawnBufferDescriptorErrorInfoFromWireClient const *>(chainedStruct);
                result += WireAlignSizeof<WGPUDawnBufferDescriptorErrorInfoFromWireClientTransfer>();
                result += WGPUDawnBufferDescriptorErrorInfoFromWireClientGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor: {
                const auto& typedStruct = *reinterpret_cast<WGPUDawnShaderModuleSPIRVOptionsDescriptor const *>(chainedStruct);
                result += WireAlignSizeof<WGPUDawnShaderModuleSPIRVOptionsDescriptorTransfer>();
                result += WGPUDawnShaderModuleSPIRVOptionsDescriptorGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_DawnMultisampleStateRenderToSingleSampled: {
                const auto& typedStruct = *reinterpret_cast<WGPUDawnMultisampleStateRenderToSingleSampled const *>(chainedStruct);
                result += WireAlignSizeof<WGPUDawnMultisampleStateRenderToSingleSampledTransfer>();
                result += WGPUDawnMultisampleStateRenderToSingleSampledGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            case WGPUSType_DawnRenderPassColorAttachmentRenderToSingleSampled: {
                const auto& typedStruct = *reinterpret_cast<WGPUDawnRenderPassColorAttachmentRenderToSingleSampled const *>(chainedStruct);
                result += WireAlignSizeof<WGPUDawnRenderPassColorAttachmentRenderToSingleSampledTransfer>();
                result += WGPUDawnRenderPassColorAttachmentRenderToSingleSampledGetExtraRequiredSize(typedStruct);
                chainedStruct = typedStruct.chain.next;
                break;
            }
            // Explicitly list the Invalid enum. MSVC complains about no case labels.
            case WGPUSType_Invalid:
            default:
                // Invalid enum. Reserve space just for the transfer header (sType and hasNext).
                result += WireAlignSizeof<WGPUChainedStructTransfer>();
                chainedStruct = chainedStruct->next;
                break;
        }
    }
    return result;
}

[[nodiscard]] WireResult SerializeChainedStruct(const WGPUChainedStruct* chainedStruct,
                                                SerializeBuffer* buffer,
                                                const ObjectIdProvider& provider) {
    ASSERT(chainedStruct != nullptr);
    ASSERT(buffer != nullptr);
    do {
        switch (chainedStruct->sType) {
            case WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector: {
                WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUSurfaceDescriptorFromCanvasHTMLSelectorSerialize(*reinterpret_cast<WGPUSurfaceDescriptorFromCanvasHTMLSelector const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_ShaderModuleSPIRVDescriptor: {
                WGPUShaderModuleSPIRVDescriptorTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUShaderModuleSPIRVDescriptorSerialize(*reinterpret_cast<WGPUShaderModuleSPIRVDescriptor const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_ShaderModuleWGSLDescriptor: {
                WGPUShaderModuleWGSLDescriptorTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUShaderModuleWGSLDescriptorSerialize(*reinterpret_cast<WGPUShaderModuleWGSLDescriptor const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_PrimitiveDepthClipControl: {
                WGPUPrimitiveDepthClipControlTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUPrimitiveDepthClipControlSerialize(*reinterpret_cast<WGPUPrimitiveDepthClipControl const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_ExternalTextureBindingEntry: {
                WGPUExternalTextureBindingEntryTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUExternalTextureBindingEntrySerialize(*reinterpret_cast<WGPUExternalTextureBindingEntry const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_ExternalTextureBindingLayout: {
                WGPUExternalTextureBindingLayoutTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUExternalTextureBindingLayoutSerialize(*reinterpret_cast<WGPUExternalTextureBindingLayout const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_RenderPassDescriptorMaxDrawCount: {
                WGPURenderPassDescriptorMaxDrawCountTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPURenderPassDescriptorMaxDrawCountSerialize(*reinterpret_cast<WGPURenderPassDescriptorMaxDrawCount const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_DawnTextureInternalUsageDescriptor: {
                WGPUDawnTextureInternalUsageDescriptorTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUDawnTextureInternalUsageDescriptorSerialize(*reinterpret_cast<WGPUDawnTextureInternalUsageDescriptor const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_DawnEncoderInternalUsageDescriptor: {
                WGPUDawnEncoderInternalUsageDescriptorTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUDawnEncoderInternalUsageDescriptorSerialize(*reinterpret_cast<WGPUDawnEncoderInternalUsageDescriptor const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient: {
                WGPUDawnBufferDescriptorErrorInfoFromWireClientTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUDawnBufferDescriptorErrorInfoFromWireClientSerialize(*reinterpret_cast<WGPUDawnBufferDescriptorErrorInfoFromWireClient const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor: {
                WGPUDawnShaderModuleSPIRVOptionsDescriptorTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUDawnShaderModuleSPIRVOptionsDescriptorSerialize(*reinterpret_cast<WGPUDawnShaderModuleSPIRVOptionsDescriptor const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_DawnMultisampleStateRenderToSingleSampled: {
                WGPUDawnMultisampleStateRenderToSingleSampledTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUDawnMultisampleStateRenderToSingleSampledSerialize(*reinterpret_cast<WGPUDawnMultisampleStateRenderToSingleSampled const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            case WGPUSType_DawnRenderPassColorAttachmentRenderToSingleSampled: {
                WGPUDawnRenderPassColorAttachmentRenderToSingleSampledTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->chain.sType = chainedStruct->sType;
                transfer->chain.hasNext = chainedStruct->next != nullptr;

                WIRE_TRY(WGPUDawnRenderPassColorAttachmentRenderToSingleSampledSerialize(*reinterpret_cast<WGPUDawnRenderPassColorAttachmentRenderToSingleSampled const*>(chainedStruct), transfer, buffer, provider));

                chainedStruct = chainedStruct->next;
            } break;
            // Explicitly list the Invalid enum. MSVC complains about no case labels.
            case WGPUSType_Invalid:
            default: {
                // Invalid enum. Serialize just the transfer header with Invalid as the sType.
                // TODO(crbug.com/dawn/369): Unknown sTypes are silently discarded.
                if (chainedStruct->sType != WGPUSType_Invalid) {
                    dawn::WarningLog() << "Unknown sType " << chainedStruct->sType << " discarded.";
                }

                WGPUChainedStructTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->sType = WGPUSType_Invalid;
                transfer->hasNext = chainedStruct->next != nullptr;

                // Still move on in case there are valid structs after this.
                chainedStruct = chainedStruct->next;
                break;
            }
        }
    } while (chainedStruct != nullptr);
    return WireResult::Success;
}

WireResult DeserializeChainedStruct(const WGPUChainedStruct** outChainNext,
                                    DeserializeBuffer* deserializeBuffer,
                                    DeserializeAllocator* allocator,
                                    const ObjectIdResolver& resolver) {
    bool hasNext;
    do {
        const volatile WGPUChainedStructTransfer* header;
        WIRE_TRY(deserializeBuffer->Peek(&header));
        WGPUSType sType = header->sType;
        switch (sType) {
            case WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector: {
                const volatile WGPUSurfaceDescriptorFromCanvasHTMLSelectorTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUSurfaceDescriptorFromCanvasHTMLSelector* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUSurfaceDescriptorFromCanvasHTMLSelectorDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_ShaderModuleSPIRVDescriptor: {
                const volatile WGPUShaderModuleSPIRVDescriptorTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUShaderModuleSPIRVDescriptor* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUShaderModuleSPIRVDescriptorDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_ShaderModuleWGSLDescriptor: {
                const volatile WGPUShaderModuleWGSLDescriptorTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUShaderModuleWGSLDescriptor* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUShaderModuleWGSLDescriptorDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_PrimitiveDepthClipControl: {
                const volatile WGPUPrimitiveDepthClipControlTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUPrimitiveDepthClipControl* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUPrimitiveDepthClipControlDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_ExternalTextureBindingEntry: {
                const volatile WGPUExternalTextureBindingEntryTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUExternalTextureBindingEntry* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUExternalTextureBindingEntryDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_ExternalTextureBindingLayout: {
                const volatile WGPUExternalTextureBindingLayoutTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUExternalTextureBindingLayout* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUExternalTextureBindingLayoutDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_RenderPassDescriptorMaxDrawCount: {
                const volatile WGPURenderPassDescriptorMaxDrawCountTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPURenderPassDescriptorMaxDrawCount* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPURenderPassDescriptorMaxDrawCountDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_DawnTextureInternalUsageDescriptor: {
                const volatile WGPUDawnTextureInternalUsageDescriptorTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUDawnTextureInternalUsageDescriptor* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUDawnTextureInternalUsageDescriptorDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_DawnEncoderInternalUsageDescriptor: {
                const volatile WGPUDawnEncoderInternalUsageDescriptorTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUDawnEncoderInternalUsageDescriptor* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUDawnEncoderInternalUsageDescriptorDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient: {
                const volatile WGPUDawnBufferDescriptorErrorInfoFromWireClientTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUDawnBufferDescriptorErrorInfoFromWireClient* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUDawnBufferDescriptorErrorInfoFromWireClientDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor: {
                const volatile WGPUDawnShaderModuleSPIRVOptionsDescriptorTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUDawnShaderModuleSPIRVOptionsDescriptor* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUDawnShaderModuleSPIRVOptionsDescriptorDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_DawnMultisampleStateRenderToSingleSampled: {
                const volatile WGPUDawnMultisampleStateRenderToSingleSampledTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUDawnMultisampleStateRenderToSingleSampled* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUDawnMultisampleStateRenderToSingleSampledDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            case WGPUSType_DawnRenderPassColorAttachmentRenderToSingleSampled: {
                const volatile WGPUDawnRenderPassColorAttachmentRenderToSingleSampledTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUDawnRenderPassColorAttachmentRenderToSingleSampled* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->chain.sType = sType;
                outStruct->chain.next = nullptr;

                *outChainNext = &outStruct->chain;
                outChainNext = &outStruct->chain.next;

                WIRE_TRY(WGPUDawnRenderPassColorAttachmentRenderToSingleSampledDeserialize(outStruct, transfer, deserializeBuffer, allocator, resolver));

                hasNext = transfer->chain.hasNext;
            } break;
            // Explicitly list the Invalid enum. MSVC complains about no case labels.
            case WGPUSType_Invalid:
            default: {
                // Invalid enum. Deserialize just the transfer header with Invalid as the sType.
                // TODO(crbug.com/dawn/369): Unknown sTypes are silently discarded.
                if (sType != WGPUSType_Invalid) {
                    dawn::WarningLog() << "Unknown sType " << sType << " discarded.";
                }

                const volatile WGPUChainedStructTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUChainedStruct* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->sType = WGPUSType_Invalid;
                outStruct->next = nullptr;

                // Still move on in case there are valid structs after this.
                *outChainNext = outStruct;
                outChainNext = &outStruct->next;
                hasNext = transfer->hasNext;
                break;
            }
        }
    } while (hasNext);
    return WireResult::Success;
}


size_t GetChainedStructExtraRequiredSize(WGPUChainedStructOut* chainedStruct) {
    ASSERT(chainedStruct != nullptr);
    size_t result = 0;
    while (chainedStruct != nullptr) {
        switch (chainedStruct->sType) {
            // Explicitly list the Invalid enum. MSVC complains about no case labels.
            case WGPUSType_Invalid:
            default:
                // Invalid enum. Reserve space just for the transfer header (sType and hasNext).
                result += WireAlignSizeof<WGPUChainedStructTransfer>();
                chainedStruct = chainedStruct->next;
                break;
        }
    }
    return result;
}

[[nodiscard]] WireResult SerializeChainedStruct(WGPUChainedStructOut* chainedStruct,
                                                SerializeBuffer* buffer,
                                                const ObjectIdProvider& provider) {
    ASSERT(chainedStruct != nullptr);
    ASSERT(buffer != nullptr);
    do {
        switch (chainedStruct->sType) {
            // Explicitly list the Invalid enum. MSVC complains about no case labels.
            case WGPUSType_Invalid:
            default: {
                // Invalid enum. Serialize just the transfer header with Invalid as the sType.
                // TODO(crbug.com/dawn/369): Unknown sTypes are silently discarded.
                if (chainedStruct->sType != WGPUSType_Invalid) {
                    dawn::WarningLog() << "Unknown sType " << chainedStruct->sType << " discarded.";
                }

                WGPUChainedStructTransfer* transfer;
                WIRE_TRY(buffer->Next(&transfer));
                transfer->sType = WGPUSType_Invalid;
                transfer->hasNext = chainedStruct->next != nullptr;

                // Still move on in case there are valid structs after this.
                chainedStruct = chainedStruct->next;
                break;
            }
        }
    } while (chainedStruct != nullptr);
    return WireResult::Success;
}

WireResult DeserializeChainedStruct(WGPUChainedStructOut** outChainNext,
                                    DeserializeBuffer* deserializeBuffer,
                                    DeserializeAllocator* allocator,
                                    const ObjectIdResolver& resolver) {
    bool hasNext;
    do {
        const volatile WGPUChainedStructTransfer* header;
        WIRE_TRY(deserializeBuffer->Peek(&header));
        WGPUSType sType = header->sType;
        switch (sType) {
            // Explicitly list the Invalid enum. MSVC complains about no case labels.
            case WGPUSType_Invalid:
            default: {
                // Invalid enum. Deserialize just the transfer header with Invalid as the sType.
                // TODO(crbug.com/dawn/369): Unknown sTypes are silently discarded.
                if (sType != WGPUSType_Invalid) {
                    dawn::WarningLog() << "Unknown sType " << sType << " discarded.";
                }

                const volatile WGPUChainedStructTransfer* transfer;
                WIRE_TRY(deserializeBuffer->Read(&transfer));

                WGPUChainedStructOut* outStruct;
                WIRE_TRY(GetSpace(allocator, 1u, &outStruct));
                outStruct->sType = WGPUSType_Invalid;
                outStruct->next = nullptr;

                // Still move on in case there are valid structs after this.
                *outChainNext = outStruct;
                outChainNext = &outStruct->next;
                hasNext = transfer->hasNext;
                break;
            }
        }
    } while (hasNext);
    return WireResult::Success;
}



struct AdapterGetInstanceTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(AdapterGetInstanceTransfer, commandSize) == 0);
static_assert(offsetof(AdapterGetInstanceTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t AdapterGetInstanceGetExtraRequiredSize(const AdapterGetInstanceCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(AdapterGetInstanceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult AdapterGetInstanceSerialize(
    const AdapterGetInstanceCmd& record,
    AdapterGetInstanceTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::AdapterGetInstance;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(AdapterGetInstanceSerialize);

DAWN_DECLARE_UNUSED WireResult AdapterGetInstanceDeserialize(
    AdapterGetInstanceCmd* record,
    const volatile AdapterGetInstanceTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::AdapterGetInstance);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(AdapterGetInstanceDeserialize);

struct AdapterRequestDeviceTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId adapterId;
    uint64_t requestSerial;
    ObjectHandle deviceObjectHandle;
};

static_assert(offsetof(AdapterRequestDeviceTransfer, commandSize) == 0);
static_assert(offsetof(AdapterRequestDeviceTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t AdapterRequestDeviceGetExtraRequiredSize(const AdapterRequestDeviceCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUDeviceDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUDeviceDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(AdapterRequestDeviceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult AdapterRequestDeviceSerialize(
    const AdapterRequestDeviceCmd& record,
    AdapterRequestDeviceTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::AdapterRequestDevice;


    transfer->adapterId = record.adapterId;
    transfer->requestSerial = record.requestSerial;
    transfer->deviceObjectHandle = record.deviceObjectHandle;
    {
        auto memberLength = 1u;

        WGPUDeviceDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUDeviceDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(AdapterRequestDeviceSerialize);

DAWN_DECLARE_UNUSED WireResult AdapterRequestDeviceDeserialize(
    AdapterRequestDeviceCmd* record,
    const volatile AdapterRequestDeviceTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::AdapterRequestDevice);


    static_assert(sizeof(record->adapterId) >= sizeof(transfer->adapterId), "Deserialize assignment may not narrow.");
    record->adapterId = transfer->adapterId;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->deviceObjectHandle) >= sizeof(transfer->deviceObjectHandle), "Deserialize assignment may not narrow.");
    record->deviceObjectHandle = transfer->deviceObjectHandle;
    {
        auto memberLength = 1u;
        const volatile WGPUDeviceDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUDeviceDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUDeviceDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(AdapterRequestDeviceDeserialize);

struct BindGroupLayoutSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(BindGroupLayoutSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(BindGroupLayoutSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t BindGroupLayoutSetLabelGetExtraRequiredSize(const BindGroupLayoutSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BindGroupLayoutSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult BindGroupLayoutSetLabelSerialize(
    const BindGroupLayoutSetLabelCmd& record,
    BindGroupLayoutSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::BindGroupLayoutSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BindGroupLayoutSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult BindGroupLayoutSetLabelDeserialize(
    BindGroupLayoutSetLabelCmd* record,
    const volatile BindGroupLayoutSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::BindGroupLayoutSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BindGroupLayoutSetLabelDeserialize);

struct BindGroupSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(BindGroupSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(BindGroupSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t BindGroupSetLabelGetExtraRequiredSize(const BindGroupSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BindGroupSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult BindGroupSetLabelSerialize(
    const BindGroupSetLabelCmd& record,
    BindGroupSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::BindGroupSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BindGroupSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult BindGroupSetLabelDeserialize(
    BindGroupSetLabelCmd* record,
    const volatile BindGroupSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::BindGroupSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BindGroupSetLabelDeserialize);

struct BufferDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(BufferDestroyTransfer, commandSize) == 0);
static_assert(offsetof(BufferDestroyTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t BufferDestroyGetExtraRequiredSize(const BufferDestroyCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult BufferDestroySerialize(
    const BufferDestroyCmd& record,
    BufferDestroyTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::BufferDestroy;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferDestroySerialize);

DAWN_DECLARE_UNUSED WireResult BufferDestroyDeserialize(
    BufferDestroyCmd* record,
    const volatile BufferDestroyTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::BufferDestroy);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferDestroyDeserialize);

struct BufferMapAsyncTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId bufferId;
    uint64_t requestSerial;
    WGPUMapModeFlags mode;
    uint64_t offset;
    uint64_t size;
};

static_assert(offsetof(BufferMapAsyncTransfer, commandSize) == 0);
static_assert(offsetof(BufferMapAsyncTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t BufferMapAsyncGetExtraRequiredSize(const BufferMapAsyncCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferMapAsyncGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult BufferMapAsyncSerialize(
    const BufferMapAsyncCmd& record,
    BufferMapAsyncTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::BufferMapAsync;


    transfer->bufferId = record.bufferId;
    transfer->requestSerial = record.requestSerial;
    transfer->mode = record.mode;
    transfer->offset = record.offset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferMapAsyncSerialize);

DAWN_DECLARE_UNUSED WireResult BufferMapAsyncDeserialize(
    BufferMapAsyncCmd* record,
    const volatile BufferMapAsyncTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::BufferMapAsync);


    static_assert(sizeof(record->bufferId) >= sizeof(transfer->bufferId), "Deserialize assignment may not narrow.");
    record->bufferId = transfer->bufferId;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->mode) >= sizeof(transfer->mode), "Deserialize assignment may not narrow.");
    record->mode = transfer->mode;
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferMapAsyncDeserialize);

struct BufferSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(BufferSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(BufferSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t BufferSetLabelGetExtraRequiredSize(const BufferSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult BufferSetLabelSerialize(
    const BufferSetLabelCmd& record,
    BufferSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::BufferSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult BufferSetLabelDeserialize(
    BufferSetLabelCmd* record,
    const volatile BufferSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::BufferSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferSetLabelDeserialize);

struct BufferUnmapTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(BufferUnmapTransfer, commandSize) == 0);
static_assert(offsetof(BufferUnmapTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t BufferUnmapGetExtraRequiredSize(const BufferUnmapCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferUnmapGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult BufferUnmapSerialize(
    const BufferUnmapCmd& record,
    BufferUnmapTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::BufferUnmap;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferUnmapSerialize);

DAWN_DECLARE_UNUSED WireResult BufferUnmapDeserialize(
    BufferUnmapCmd* record,
    const volatile BufferUnmapTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::BufferUnmap);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferUnmapDeserialize);

struct BufferUpdateMappedDataTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId bufferId;
    uint64_t writeDataUpdateInfoLength;
    uint64_t offset;
    uint64_t size;
};

static_assert(offsetof(BufferUpdateMappedDataTransfer, commandSize) == 0);
static_assert(offsetof(BufferUpdateMappedDataTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t BufferUpdateMappedDataGetExtraRequiredSize(const BufferUpdateMappedDataCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(BufferUpdateMappedDataGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult BufferUpdateMappedDataSerialize(
    const BufferUpdateMappedDataCmd& record,
    BufferUpdateMappedDataTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::BufferUpdateMappedData;


    transfer->bufferId = record.bufferId;
    transfer->writeDataUpdateInfoLength = record.writeDataUpdateInfoLength;
    transfer->offset = record.offset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferUpdateMappedDataSerialize);

DAWN_DECLARE_UNUSED WireResult BufferUpdateMappedDataDeserialize(
    BufferUpdateMappedDataCmd* record,
    const volatile BufferUpdateMappedDataTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::BufferUpdateMappedData);


    static_assert(sizeof(record->bufferId) >= sizeof(transfer->bufferId), "Deserialize assignment may not narrow.");
    record->bufferId = transfer->bufferId;
    static_assert(sizeof(record->writeDataUpdateInfoLength) >= sizeof(transfer->writeDataUpdateInfoLength), "Deserialize assignment may not narrow.");
    record->writeDataUpdateInfoLength = transfer->writeDataUpdateInfoLength;
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;
    {
        auto memberLength = record->writeDataUpdateInfoLength;
        const volatile uint8_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint8_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->writeDataUpdateInfo = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint8_t*>(memberBuffer),
           sizeof(uint8_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(BufferUpdateMappedDataDeserialize);

struct CommandBufferSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(CommandBufferSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(CommandBufferSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandBufferSetLabelGetExtraRequiredSize(const CommandBufferSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandBufferSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandBufferSetLabelSerialize(
    const CommandBufferSetLabelCmd& record,
    CommandBufferSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandBufferSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandBufferSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult CommandBufferSetLabelDeserialize(
    CommandBufferSetLabelCmd* record,
    const volatile CommandBufferSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandBufferSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandBufferSetLabelDeserialize);

struct CommandEncoderBeginComputePassTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    bool has_descriptor;
    ObjectHandle result;
};

static_assert(offsetof(CommandEncoderBeginComputePassTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderBeginComputePassTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderBeginComputePassGetExtraRequiredSize(const CommandEncoderBeginComputePassCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.descriptor != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUComputePassDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUComputePassDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderBeginComputePassGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderBeginComputePassSerialize(
    const CommandEncoderBeginComputePassCmd& record,
    CommandEncoderBeginComputePassTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderBeginComputePass;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor) {
        auto memberLength = 1u;

        WGPUComputePassDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePassDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderBeginComputePassSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderBeginComputePassDeserialize(
    CommandEncoderBeginComputePassCmd* record,
    const volatile CommandEncoderBeginComputePassTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderBeginComputePass);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor) {
        auto memberLength = 1u;
        const volatile WGPUComputePassDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUComputePassDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePassDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderBeginComputePassDeserialize);

struct CommandEncoderBeginRenderPassTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(CommandEncoderBeginRenderPassTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderBeginRenderPassTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderBeginRenderPassGetExtraRequiredSize(const CommandEncoderBeginRenderPassCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURenderPassDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderPassDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderBeginRenderPassGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderBeginRenderPassSerialize(
    const CommandEncoderBeginRenderPassCmd& record,
    CommandEncoderBeginRenderPassTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderBeginRenderPass;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPURenderPassDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderBeginRenderPassSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderBeginRenderPassDeserialize(
    CommandEncoderBeginRenderPassCmd* record,
    const volatile CommandEncoderBeginRenderPassTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderBeginRenderPass);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPURenderPassDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderPassDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPassDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderBeginRenderPassDeserialize);

struct CommandEncoderClearBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;
};

static_assert(offsetof(CommandEncoderClearBufferTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderClearBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderClearBufferGetExtraRequiredSize(const CommandEncoderClearBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderClearBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderClearBufferSerialize(
    const CommandEncoderClearBufferCmd& record,
    CommandEncoderClearBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderClearBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.buffer, &transfer->buffer));
    transfer->offset = record.offset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderClearBufferSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderClearBufferDeserialize(
    CommandEncoderClearBufferCmd* record,
    const volatile CommandEncoderClearBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderClearBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderClearBufferDeserialize);

struct CommandEncoderCopyBufferToBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId source;
    uint64_t sourceOffset;
    ObjectId destination;
    uint64_t destinationOffset;
    uint64_t size;
};

static_assert(offsetof(CommandEncoderCopyBufferToBufferTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderCopyBufferToBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderCopyBufferToBufferGetExtraRequiredSize(const CommandEncoderCopyBufferToBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyBufferToBufferSerialize(
    const CommandEncoderCopyBufferToBufferCmd& record,
    CommandEncoderCopyBufferToBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderCopyBufferToBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.source, &transfer->source));
    transfer->sourceOffset = record.sourceOffset;
    WIRE_TRY(provider.GetId(record.destination, &transfer->destination));
    transfer->destinationOffset = record.destinationOffset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToBufferSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyBufferToBufferDeserialize(
    CommandEncoderCopyBufferToBufferCmd* record,
    const volatile CommandEncoderCopyBufferToBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyBufferToBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->source, &record->source));
    static_assert(sizeof(record->sourceOffset) >= sizeof(transfer->sourceOffset), "Deserialize assignment may not narrow.");
    record->sourceOffset = transfer->sourceOffset;
    WIRE_TRY(resolver.GetFromId(transfer->destination, &record->destination));
    static_assert(sizeof(record->destinationOffset) >= sizeof(transfer->destinationOffset), "Deserialize assignment may not narrow.");
    record->destinationOffset = transfer->destinationOffset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToBufferDeserialize);

struct CommandEncoderCopyBufferToTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(CommandEncoderCopyBufferToTextureTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderCopyBufferToTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderCopyBufferToTextureGetExtraRequiredSize(const CommandEncoderCopyBufferToTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyBufferTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyBufferGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExtent3DTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyBufferToTextureSerialize(
    const CommandEncoderCopyBufferToTextureCmd& record,
    CommandEncoderCopyBufferToTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderCopyBufferToTexture;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUImageCopyBufferTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyBufferSerialize(record.source[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.destination[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.copySize,
            sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToTextureSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyBufferToTextureDeserialize(
    CommandEncoderCopyBufferToTextureCmd* record,
    const volatile CommandEncoderCopyBufferToTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyBufferToTexture);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyBufferTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyBuffer* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyBufferDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUExtent3DTransfer*>(memberBuffer),
           sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyBufferToTextureDeserialize);

struct CommandEncoderCopyTextureToBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(CommandEncoderCopyTextureToBufferTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderCopyTextureToBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderCopyTextureToBufferGetExtraRequiredSize(const CommandEncoderCopyTextureToBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyBufferTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyBufferGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExtent3DTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyTextureToBufferSerialize(
    const CommandEncoderCopyTextureToBufferCmd& record,
    CommandEncoderCopyTextureToBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderCopyTextureToBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.source[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUImageCopyBufferTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyBufferSerialize(record.destination[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.copySize,
            sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToBufferSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyTextureToBufferDeserialize(
    CommandEncoderCopyTextureToBufferCmd* record,
    const volatile CommandEncoderCopyTextureToBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyTextureToBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyBufferTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyBuffer* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyBufferDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUExtent3DTransfer*>(memberBuffer),
           sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToBufferDeserialize);

struct CommandEncoderCopyTextureToTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(CommandEncoderCopyTextureToTextureTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderCopyTextureToTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderCopyTextureToTextureGetExtraRequiredSize(const CommandEncoderCopyTextureToTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExtent3DTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyTextureToTextureSerialize(
    const CommandEncoderCopyTextureToTextureCmd& record,
    CommandEncoderCopyTextureToTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderCopyTextureToTexture;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.source[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.destination[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.copySize,
            sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyTextureToTextureDeserialize(
    CommandEncoderCopyTextureToTextureCmd* record,
    const volatile CommandEncoderCopyTextureToTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyTextureToTexture);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUExtent3DTransfer*>(memberBuffer),
           sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureDeserialize);

struct CommandEncoderCopyTextureToTextureInternalTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(CommandEncoderCopyTextureToTextureInternalTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderCopyTextureToTextureInternalTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderCopyTextureToTextureInternalGetExtraRequiredSize(const CommandEncoderCopyTextureToTextureInternalCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExtent3DTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureInternalGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyTextureToTextureInternalSerialize(
    const CommandEncoderCopyTextureToTextureInternalCmd& record,
    CommandEncoderCopyTextureToTextureInternalTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderCopyTextureToTextureInternal;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.source[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.destination[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.copySize,
            sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureInternalSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderCopyTextureToTextureInternalDeserialize(
    CommandEncoderCopyTextureToTextureInternalCmd* record,
    const volatile CommandEncoderCopyTextureToTextureInternalTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderCopyTextureToTextureInternal);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUExtent3DTransfer*>(memberBuffer),
           sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderCopyTextureToTextureInternalDeserialize);

struct CommandEncoderFinishTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    bool has_descriptor;
    ObjectHandle result;
};

static_assert(offsetof(CommandEncoderFinishTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderFinishTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderFinishGetExtraRequiredSize(const CommandEncoderFinishCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.descriptor != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUCommandBufferDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUCommandBufferDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderFinishGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderFinishSerialize(
    const CommandEncoderFinishCmd& record,
    CommandEncoderFinishTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderFinish;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor) {
        auto memberLength = 1u;

        WGPUCommandBufferDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCommandBufferDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderFinishSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderFinishDeserialize(
    CommandEncoderFinishCmd* record,
    const volatile CommandEncoderFinishTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderFinish);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor) {
        auto memberLength = 1u;
        const volatile WGPUCommandBufferDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUCommandBufferDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCommandBufferDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderFinishDeserialize);

struct CommandEncoderInjectValidationErrorTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t messageStrlen;
};

static_assert(offsetof(CommandEncoderInjectValidationErrorTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderInjectValidationErrorTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderInjectValidationErrorGetExtraRequiredSize(const CommandEncoderInjectValidationErrorCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderInjectValidationErrorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderInjectValidationErrorSerialize(
    const CommandEncoderInjectValidationErrorCmd& record,
    CommandEncoderInjectValidationErrorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderInjectValidationError;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderInjectValidationErrorSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderInjectValidationErrorDeserialize(
    CommandEncoderInjectValidationErrorCmd* record,
    const volatile CommandEncoderInjectValidationErrorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderInjectValidationError);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderInjectValidationErrorDeserialize);

struct CommandEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t markerLabelStrlen;
};

static_assert(offsetof(CommandEncoderInsertDebugMarkerTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderInsertDebugMarkerGetExtraRequiredSize(const CommandEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.markerLabel != nullptr);
    result += Align(std::strlen(record.markerLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderInsertDebugMarkerSerialize(
    const CommandEncoderInsertDebugMarkerCmd& record,
    CommandEncoderInsertDebugMarkerTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderInsertDebugMarker;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->markerLabelStrlen = std::strlen(record.markerLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->markerLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.markerLabel, transfer->markerLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderInsertDebugMarkerDeserialize(
    CommandEncoderInsertDebugMarkerCmd* record,
    const volatile CommandEncoderInsertDebugMarkerTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderInsertDebugMarker);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->markerLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderInsertDebugMarkerDeserialize);

struct CommandEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(CommandEncoderPopDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderPopDebugGroupGetExtraRequiredSize(const CommandEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderPopDebugGroupSerialize(
    const CommandEncoderPopDebugGroupCmd& record,
    CommandEncoderPopDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderPopDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderPopDebugGroupDeserialize(
    CommandEncoderPopDebugGroupCmd* record,
    const volatile CommandEncoderPopDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderPopDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderPopDebugGroupDeserialize);

struct CommandEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t groupLabelStrlen;
};

static_assert(offsetof(CommandEncoderPushDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderPushDebugGroupGetExtraRequiredSize(const CommandEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.groupLabel != nullptr);
    result += Align(std::strlen(record.groupLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderPushDebugGroupSerialize(
    const CommandEncoderPushDebugGroupCmd& record,
    CommandEncoderPushDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderPushDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->groupLabelStrlen = std::strlen(record.groupLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->groupLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.groupLabel, transfer->groupLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderPushDebugGroupDeserialize(
    CommandEncoderPushDebugGroupCmd* record,
    const volatile CommandEncoderPushDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderPushDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->groupLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderPushDebugGroupDeserialize);

struct CommandEncoderResolveQuerySetTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t firstQuery;
    uint32_t queryCount;
    ObjectId destination;
    uint64_t destinationOffset;
};

static_assert(offsetof(CommandEncoderResolveQuerySetTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderResolveQuerySetTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderResolveQuerySetGetExtraRequiredSize(const CommandEncoderResolveQuerySetCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderResolveQuerySetGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderResolveQuerySetSerialize(
    const CommandEncoderResolveQuerySetCmd& record,
    CommandEncoderResolveQuerySetTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderResolveQuerySet;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.querySet, &transfer->querySet));
    transfer->firstQuery = record.firstQuery;
    transfer->queryCount = record.queryCount;
    WIRE_TRY(provider.GetId(record.destination, &transfer->destination));
    transfer->destinationOffset = record.destinationOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderResolveQuerySetSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderResolveQuerySetDeserialize(
    CommandEncoderResolveQuerySetCmd* record,
    const volatile CommandEncoderResolveQuerySetTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderResolveQuerySet);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    static_assert(sizeof(record->firstQuery) >= sizeof(transfer->firstQuery), "Deserialize assignment may not narrow.");
    record->firstQuery = transfer->firstQuery;
    static_assert(sizeof(record->queryCount) >= sizeof(transfer->queryCount), "Deserialize assignment may not narrow.");
    record->queryCount = transfer->queryCount;
    WIRE_TRY(resolver.GetFromId(transfer->destination, &record->destination));
    static_assert(sizeof(record->destinationOffset) >= sizeof(transfer->destinationOffset), "Deserialize assignment may not narrow.");
    record->destinationOffset = transfer->destinationOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderResolveQuerySetDeserialize);

struct CommandEncoderSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(CommandEncoderSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderSetLabelGetExtraRequiredSize(const CommandEncoderSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderSetLabelSerialize(
    const CommandEncoderSetLabelCmd& record,
    CommandEncoderSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderSetLabelDeserialize(
    CommandEncoderSetLabelCmd* record,
    const volatile CommandEncoderSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderSetLabelDeserialize);

struct CommandEncoderWriteBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    uint64_t bufferOffset;
    uint64_t size;
};

static_assert(offsetof(CommandEncoderWriteBufferTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderWriteBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderWriteBufferGetExtraRequiredSize(const CommandEncoderWriteBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.size;
        auto size = WireAlignSizeofN<uint8_t>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderWriteBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderWriteBufferSerialize(
    const CommandEncoderWriteBufferCmd& record,
    CommandEncoderWriteBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderWriteBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.buffer, &transfer->buffer));
    transfer->bufferOffset = record.bufferOffset;
    transfer->size = record.size;
    {
        auto memberLength = record.size;

        uint8_t* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.data,
            sizeof(uint8_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderWriteBufferSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderWriteBufferDeserialize(
    CommandEncoderWriteBufferCmd* record,
    const volatile CommandEncoderWriteBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderWriteBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    static_assert(sizeof(record->bufferOffset) >= sizeof(transfer->bufferOffset), "Deserialize assignment may not narrow.");
    record->bufferOffset = transfer->bufferOffset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;
    {
        auto memberLength = record->size;
        const volatile uint8_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint8_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->data = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint8_t*>(memberBuffer),
           sizeof(uint8_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderWriteBufferDeserialize);

struct CommandEncoderWriteTimestampTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t queryIndex;
};

static_assert(offsetof(CommandEncoderWriteTimestampTransfer, commandSize) == 0);
static_assert(offsetof(CommandEncoderWriteTimestampTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t CommandEncoderWriteTimestampGetExtraRequiredSize(const CommandEncoderWriteTimestampCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(CommandEncoderWriteTimestampGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderWriteTimestampSerialize(
    const CommandEncoderWriteTimestampCmd& record,
    CommandEncoderWriteTimestampTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::CommandEncoderWriteTimestamp;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.querySet, &transfer->querySet));
    transfer->queryIndex = record.queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderWriteTimestampSerialize);

DAWN_DECLARE_UNUSED WireResult CommandEncoderWriteTimestampDeserialize(
    CommandEncoderWriteTimestampCmd* record,
    const volatile CommandEncoderWriteTimestampTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::CommandEncoderWriteTimestamp);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    static_assert(sizeof(record->queryIndex) >= sizeof(transfer->queryIndex), "Deserialize assignment may not narrow.");
    record->queryIndex = transfer->queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(CommandEncoderWriteTimestampDeserialize);

struct ComputePassEncoderDispatchWorkgroupsTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t workgroupCountX;
    uint32_t workgroupCountY;
    uint32_t workgroupCountZ;
};

static_assert(offsetof(ComputePassEncoderDispatchWorkgroupsTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderDispatchWorkgroupsTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderDispatchWorkgroupsGetExtraRequiredSize(const ComputePassEncoderDispatchWorkgroupsCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchWorkgroupsGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderDispatchWorkgroupsSerialize(
    const ComputePassEncoderDispatchWorkgroupsCmd& record,
    ComputePassEncoderDispatchWorkgroupsTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderDispatchWorkgroups;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->workgroupCountX = record.workgroupCountX;
    transfer->workgroupCountY = record.workgroupCountY;
    transfer->workgroupCountZ = record.workgroupCountZ;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchWorkgroupsSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderDispatchWorkgroupsDeserialize(
    ComputePassEncoderDispatchWorkgroupsCmd* record,
    const volatile ComputePassEncoderDispatchWorkgroupsTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderDispatchWorkgroups);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->workgroupCountX) >= sizeof(transfer->workgroupCountX), "Deserialize assignment may not narrow.");
    record->workgroupCountX = transfer->workgroupCountX;
    static_assert(sizeof(record->workgroupCountY) >= sizeof(transfer->workgroupCountY), "Deserialize assignment may not narrow.");
    record->workgroupCountY = transfer->workgroupCountY;
    static_assert(sizeof(record->workgroupCountZ) >= sizeof(transfer->workgroupCountZ), "Deserialize assignment may not narrow.");
    record->workgroupCountZ = transfer->workgroupCountZ;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchWorkgroupsDeserialize);

struct ComputePassEncoderDispatchWorkgroupsIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;
};

static_assert(offsetof(ComputePassEncoderDispatchWorkgroupsIndirectTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderDispatchWorkgroupsIndirectTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderDispatchWorkgroupsIndirectGetExtraRequiredSize(const ComputePassEncoderDispatchWorkgroupsIndirectCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchWorkgroupsIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderDispatchWorkgroupsIndirectSerialize(
    const ComputePassEncoderDispatchWorkgroupsIndirectCmd& record,
    ComputePassEncoderDispatchWorkgroupsIndirectTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderDispatchWorkgroupsIndirect;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.indirectBuffer, &transfer->indirectBuffer));
    transfer->indirectOffset = record.indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchWorkgroupsIndirectSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderDispatchWorkgroupsIndirectDeserialize(
    ComputePassEncoderDispatchWorkgroupsIndirectCmd* record,
    const volatile ComputePassEncoderDispatchWorkgroupsIndirectTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderDispatchWorkgroupsIndirect);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    static_assert(sizeof(record->indirectOffset) >= sizeof(transfer->indirectOffset), "Deserialize assignment may not narrow.");
    record->indirectOffset = transfer->indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderDispatchWorkgroupsIndirectDeserialize);

struct ComputePassEncoderEndTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(ComputePassEncoderEndTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderEndTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderEndGetExtraRequiredSize(const ComputePassEncoderEndCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderEndGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderEndSerialize(
    const ComputePassEncoderEndCmd& record,
    ComputePassEncoderEndTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderEnd;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderEndSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderEndDeserialize(
    ComputePassEncoderEndCmd* record,
    const volatile ComputePassEncoderEndTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderEnd);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderEndDeserialize);

struct ComputePassEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t markerLabelStrlen;
};

static_assert(offsetof(ComputePassEncoderInsertDebugMarkerTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderInsertDebugMarkerGetExtraRequiredSize(const ComputePassEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.markerLabel != nullptr);
    result += Align(std::strlen(record.markerLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderInsertDebugMarkerSerialize(
    const ComputePassEncoderInsertDebugMarkerCmd& record,
    ComputePassEncoderInsertDebugMarkerTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderInsertDebugMarker;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->markerLabelStrlen = std::strlen(record.markerLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->markerLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.markerLabel, transfer->markerLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderInsertDebugMarkerDeserialize(
    ComputePassEncoderInsertDebugMarkerCmd* record,
    const volatile ComputePassEncoderInsertDebugMarkerTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderInsertDebugMarker);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->markerLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderInsertDebugMarkerDeserialize);

struct ComputePassEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(ComputePassEncoderPopDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderPopDebugGroupGetExtraRequiredSize(const ComputePassEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderPopDebugGroupSerialize(
    const ComputePassEncoderPopDebugGroupCmd& record,
    ComputePassEncoderPopDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderPopDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderPopDebugGroupDeserialize(
    ComputePassEncoderPopDebugGroupCmd* record,
    const volatile ComputePassEncoderPopDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderPopDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderPopDebugGroupDeserialize);

struct ComputePassEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t groupLabelStrlen;
};

static_assert(offsetof(ComputePassEncoderPushDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderPushDebugGroupGetExtraRequiredSize(const ComputePassEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.groupLabel != nullptr);
    result += Align(std::strlen(record.groupLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderPushDebugGroupSerialize(
    const ComputePassEncoderPushDebugGroupCmd& record,
    ComputePassEncoderPushDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderPushDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->groupLabelStrlen = std::strlen(record.groupLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->groupLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.groupLabel, transfer->groupLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderPushDebugGroupDeserialize(
    ComputePassEncoderPushDebugGroupCmd* record,
    const volatile ComputePassEncoderPushDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderPushDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->groupLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderPushDebugGroupDeserialize);

struct ComputePassEncoderSetBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectId group;
    uint64_t dynamicOffsetCount;
};

static_assert(offsetof(ComputePassEncoderSetBindGroupTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderSetBindGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderSetBindGroupGetExtraRequiredSize(const ComputePassEncoderSetBindGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.dynamicOffsetCount;
        auto size = WireAlignSizeofN<uint32_t>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderSetBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderSetBindGroupSerialize(
    const ComputePassEncoderSetBindGroupCmd& record,
    ComputePassEncoderSetBindGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderSetBindGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->groupIndex = record.groupIndex;
    WIRE_TRY(provider.GetOptionalId(record.group, &transfer->group));
    transfer->dynamicOffsetCount = record.dynamicOffsetCount;
    {
        auto memberLength = record.dynamicOffsetCount;

        uint32_t* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.dynamicOffsets,
            sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetBindGroupSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderSetBindGroupDeserialize(
    ComputePassEncoderSetBindGroupCmd* record,
    const volatile ComputePassEncoderSetBindGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderSetBindGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->groupIndex) >= sizeof(transfer->groupIndex), "Deserialize assignment may not narrow.");
    record->groupIndex = transfer->groupIndex;
    WIRE_TRY(resolver.GetOptionalFromId(transfer->group, &record->group));
    if (transfer->dynamicOffsetCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->dynamicOffsetCount = checked_cast<size_t>(transfer->dynamicOffsetCount);
    {
        auto memberLength = record->dynamicOffsetCount;
        const volatile uint32_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint32_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dynamicOffsets = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint32_t*>(memberBuffer),
           sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetBindGroupDeserialize);

struct ComputePassEncoderSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(ComputePassEncoderSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderSetLabelGetExtraRequiredSize(const ComputePassEncoderSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderSetLabelSerialize(
    const ComputePassEncoderSetLabelCmd& record,
    ComputePassEncoderSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderSetLabelDeserialize(
    ComputePassEncoderSetLabelCmd* record,
    const volatile ComputePassEncoderSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetLabelDeserialize);

struct ComputePassEncoderSetPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId pipeline;
};

static_assert(offsetof(ComputePassEncoderSetPipelineTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderSetPipelineTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderSetPipelineGetExtraRequiredSize(const ComputePassEncoderSetPipelineCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderSetPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderSetPipelineSerialize(
    const ComputePassEncoderSetPipelineCmd& record,
    ComputePassEncoderSetPipelineTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderSetPipeline;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.pipeline, &transfer->pipeline));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetPipelineSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderSetPipelineDeserialize(
    ComputePassEncoderSetPipelineCmd* record,
    const volatile ComputePassEncoderSetPipelineTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderSetPipeline);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->pipeline, &record->pipeline));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderSetPipelineDeserialize);

struct ComputePassEncoderWriteTimestampTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t queryIndex;
};

static_assert(offsetof(ComputePassEncoderWriteTimestampTransfer, commandSize) == 0);
static_assert(offsetof(ComputePassEncoderWriteTimestampTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePassEncoderWriteTimestampGetExtraRequiredSize(const ComputePassEncoderWriteTimestampCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePassEncoderWriteTimestampGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderWriteTimestampSerialize(
    const ComputePassEncoderWriteTimestampCmd& record,
    ComputePassEncoderWriteTimestampTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePassEncoderWriteTimestamp;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.querySet, &transfer->querySet));
    transfer->queryIndex = record.queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderWriteTimestampSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePassEncoderWriteTimestampDeserialize(
    ComputePassEncoderWriteTimestampCmd* record,
    const volatile ComputePassEncoderWriteTimestampTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePassEncoderWriteTimestamp);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    static_assert(sizeof(record->queryIndex) >= sizeof(transfer->queryIndex), "Deserialize assignment may not narrow.");
    record->queryIndex = transfer->queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePassEncoderWriteTimestampDeserialize);

struct ComputePipelineGetBindGroupLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectHandle result;
};

static_assert(offsetof(ComputePipelineGetBindGroupLayoutTransfer, commandSize) == 0);
static_assert(offsetof(ComputePipelineGetBindGroupLayoutTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePipelineGetBindGroupLayoutGetExtraRequiredSize(const ComputePipelineGetBindGroupLayoutCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePipelineGetBindGroupLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePipelineGetBindGroupLayoutSerialize(
    const ComputePipelineGetBindGroupLayoutCmd& record,
    ComputePipelineGetBindGroupLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePipelineGetBindGroupLayout;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->groupIndex = record.groupIndex;
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePipelineGetBindGroupLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePipelineGetBindGroupLayoutDeserialize(
    ComputePipelineGetBindGroupLayoutCmd* record,
    const volatile ComputePipelineGetBindGroupLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePipelineGetBindGroupLayout);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->groupIndex) >= sizeof(transfer->groupIndex), "Deserialize assignment may not narrow.");
    record->groupIndex = transfer->groupIndex;
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePipelineGetBindGroupLayoutDeserialize);

struct ComputePipelineSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(ComputePipelineSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(ComputePipelineSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ComputePipelineSetLabelGetExtraRequiredSize(const ComputePipelineSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ComputePipelineSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ComputePipelineSetLabelSerialize(
    const ComputePipelineSetLabelCmd& record,
    ComputePipelineSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ComputePipelineSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePipelineSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult ComputePipelineSetLabelDeserialize(
    ComputePipelineSetLabelCmd* record,
    const volatile ComputePipelineSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ComputePipelineSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ComputePipelineSetLabelDeserialize);

struct DestroyObjectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectType objectType;
    ObjectId objectId;
};

static_assert(offsetof(DestroyObjectTransfer, commandSize) == 0);
static_assert(offsetof(DestroyObjectTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DestroyObjectGetExtraRequiredSize(const DestroyObjectCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DestroyObjectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DestroyObjectSerialize(
    const DestroyObjectCmd& record,
    DestroyObjectTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DestroyObject;


    transfer->objectType = record.objectType;
    transfer->objectId = record.objectId;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DestroyObjectSerialize);

DAWN_DECLARE_UNUSED WireResult DestroyObjectDeserialize(
    DestroyObjectCmd* record,
    const volatile DestroyObjectTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DestroyObject);


    static_assert(sizeof(record->objectType) >= sizeof(transfer->objectType), "Deserialize assignment may not narrow.");
    record->objectType = transfer->objectType;
    static_assert(sizeof(record->objectId) >= sizeof(transfer->objectId), "Deserialize assignment may not narrow.");
    record->objectId = transfer->objectId;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DestroyObjectDeserialize);

struct DeviceCreateBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateBindGroupTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateBindGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateBindGroupGetExtraRequiredSize(const DeviceCreateBindGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUBindGroupDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUBindGroupDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateBindGroupSerialize(
    const DeviceCreateBindGroupCmd& record,
    DeviceCreateBindGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateBindGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUBindGroupDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateBindGroupDeserialize(
    DeviceCreateBindGroupCmd* record,
    const volatile DeviceCreateBindGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateBindGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUBindGroupDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBindGroupDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupDeserialize);

struct DeviceCreateBindGroupLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateBindGroupLayoutTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateBindGroupLayoutTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateBindGroupLayoutGetExtraRequiredSize(const DeviceCreateBindGroupLayoutCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUBindGroupLayoutDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUBindGroupLayoutDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateBindGroupLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateBindGroupLayoutSerialize(
    const DeviceCreateBindGroupLayoutCmd& record,
    DeviceCreateBindGroupLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateBindGroupLayout;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUBindGroupLayoutDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupLayoutDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateBindGroupLayoutDeserialize(
    DeviceCreateBindGroupLayoutCmd* record,
    const volatile DeviceCreateBindGroupLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateBindGroupLayout);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUBindGroupLayoutDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBindGroupLayoutDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBindGroupLayoutDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBindGroupLayoutDeserialize);

struct DeviceCreateBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId deviceId;
    ObjectHandle result;
    uint64_t readHandleCreateInfoLength;
    uint64_t writeHandleCreateInfoLength;
};

static_assert(offsetof(DeviceCreateBufferTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateBufferGetExtraRequiredSize(const DeviceCreateBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUBufferDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUBufferDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateBufferSerialize(
    const DeviceCreateBufferCmd& record,
    DeviceCreateBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateBuffer;


    transfer->deviceId = record.deviceId;
    transfer->result = record.result;
    transfer->readHandleCreateInfoLength = record.readHandleCreateInfoLength;
    transfer->writeHandleCreateInfoLength = record.writeHandleCreateInfoLength;
    {
        auto memberLength = 1u;

        WGPUBufferDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBufferDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBufferSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateBufferDeserialize(
    DeviceCreateBufferCmd* record,
    const volatile DeviceCreateBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateBuffer);


    static_assert(sizeof(record->deviceId) >= sizeof(transfer->deviceId), "Deserialize assignment may not narrow.");
    record->deviceId = transfer->deviceId;
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    static_assert(sizeof(record->readHandleCreateInfoLength) >= sizeof(transfer->readHandleCreateInfoLength), "Deserialize assignment may not narrow.");
    record->readHandleCreateInfoLength = transfer->readHandleCreateInfoLength;
    static_assert(sizeof(record->writeHandleCreateInfoLength) >= sizeof(transfer->writeHandleCreateInfoLength), "Deserialize assignment may not narrow.");
    record->writeHandleCreateInfoLength = transfer->writeHandleCreateInfoLength;
    {
        auto memberLength = 1u;
        const volatile WGPUBufferDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBufferDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBufferDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = record->readHandleCreateInfoLength;
        const volatile uint8_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint8_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->readHandleCreateInfo = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint8_t*>(memberBuffer),
           sizeof(uint8_t) * memberLength);
    }
    {
        auto memberLength = record->writeHandleCreateInfoLength;
        const volatile uint8_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint8_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->writeHandleCreateInfo = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint8_t*>(memberBuffer),
           sizeof(uint8_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateBufferDeserialize);

struct DeviceCreateCommandEncoderTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    bool has_descriptor;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateCommandEncoderTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateCommandEncoderTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateCommandEncoderGetExtraRequiredSize(const DeviceCreateCommandEncoderCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.descriptor != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUCommandEncoderDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUCommandEncoderDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateCommandEncoderGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateCommandEncoderSerialize(
    const DeviceCreateCommandEncoderCmd& record,
    DeviceCreateCommandEncoderTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateCommandEncoder;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor) {
        auto memberLength = 1u;

        WGPUCommandEncoderDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCommandEncoderDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateCommandEncoderSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateCommandEncoderDeserialize(
    DeviceCreateCommandEncoderCmd* record,
    const volatile DeviceCreateCommandEncoderTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateCommandEncoder);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor) {
        auto memberLength = 1u;
        const volatile WGPUCommandEncoderDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUCommandEncoderDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCommandEncoderDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateCommandEncoderDeserialize);

struct DeviceCreateComputePipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateComputePipelineTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateComputePipelineTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateComputePipelineGetExtraRequiredSize(const DeviceCreateComputePipelineCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUComputePipelineDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUComputePipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateComputePipelineSerialize(
    const DeviceCreateComputePipelineCmd& record,
    DeviceCreateComputePipelineTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateComputePipeline;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUComputePipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateComputePipelineDeserialize(
    DeviceCreateComputePipelineCmd* record,
    const volatile DeviceCreateComputePipelineTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateComputePipeline);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUComputePipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUComputePipelineDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineDeserialize);

struct DeviceCreateComputePipelineAsyncTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId deviceId;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;
};

static_assert(offsetof(DeviceCreateComputePipelineAsyncTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateComputePipelineAsyncTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateComputePipelineAsyncGetExtraRequiredSize(const DeviceCreateComputePipelineAsyncCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUComputePipelineDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUComputePipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineAsyncGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateComputePipelineAsyncSerialize(
    const DeviceCreateComputePipelineAsyncCmd& record,
    DeviceCreateComputePipelineAsyncTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateComputePipelineAsync;


    transfer->deviceId = record.deviceId;
    transfer->requestSerial = record.requestSerial;
    transfer->pipelineObjectHandle = record.pipelineObjectHandle;
    {
        auto memberLength = 1u;

        WGPUComputePipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineAsyncSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateComputePipelineAsyncDeserialize(
    DeviceCreateComputePipelineAsyncCmd* record,
    const volatile DeviceCreateComputePipelineAsyncTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateComputePipelineAsync);


    static_assert(sizeof(record->deviceId) >= sizeof(transfer->deviceId), "Deserialize assignment may not narrow.");
    record->deviceId = transfer->deviceId;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->pipelineObjectHandle) >= sizeof(transfer->pipelineObjectHandle), "Deserialize assignment may not narrow.");
    record->pipelineObjectHandle = transfer->pipelineObjectHandle;
    {
        auto memberLength = 1u;
        const volatile WGPUComputePipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUComputePipelineDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUComputePipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateComputePipelineAsyncDeserialize);

struct DeviceCreateErrorBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateErrorBufferTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateErrorBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateErrorBufferGetExtraRequiredSize(const DeviceCreateErrorBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUBufferDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUBufferDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateErrorBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorBufferSerialize(
    const DeviceCreateErrorBufferCmd& record,
    DeviceCreateErrorBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateErrorBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUBufferDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBufferDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorBufferSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorBufferDeserialize(
    DeviceCreateErrorBufferCmd* record,
    const volatile DeviceCreateErrorBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateErrorBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUBufferDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUBufferDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUBufferDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorBufferDeserialize);

struct DeviceCreateErrorExternalTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateErrorExternalTextureTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateErrorExternalTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateErrorExternalTextureGetExtraRequiredSize(const DeviceCreateErrorExternalTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateErrorExternalTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorExternalTextureSerialize(
    const DeviceCreateErrorExternalTextureCmd& record,
    DeviceCreateErrorExternalTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateErrorExternalTexture;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorExternalTextureSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorExternalTextureDeserialize(
    DeviceCreateErrorExternalTextureCmd* record,
    const volatile DeviceCreateErrorExternalTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateErrorExternalTexture);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorExternalTextureDeserialize);

struct DeviceCreateErrorShaderModuleTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t errorMessageStrlen;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateErrorShaderModuleTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateErrorShaderModuleTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateErrorShaderModuleGetExtraRequiredSize(const DeviceCreateErrorShaderModuleCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUShaderModuleDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUShaderModuleDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    ASSERT(record.errorMessage != nullptr);
    result += Align(std::strlen(record.errorMessage), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateErrorShaderModuleGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorShaderModuleSerialize(
    const DeviceCreateErrorShaderModuleCmd& record,
    DeviceCreateErrorShaderModuleTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateErrorShaderModule;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUShaderModuleDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUShaderModuleDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        transfer->errorMessageStrlen = std::strlen(record.errorMessage);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->errorMessageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.errorMessage, transfer->errorMessageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorShaderModuleSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorShaderModuleDeserialize(
    DeviceCreateErrorShaderModuleCmd* record,
    const volatile DeviceCreateErrorShaderModuleTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateErrorShaderModule);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUShaderModuleDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUShaderModuleDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUShaderModuleDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        uint64_t stringLength64 = transfer->errorMessageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->errorMessage = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorShaderModuleDeserialize);

struct DeviceCreateErrorTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateErrorTextureTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateErrorTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateErrorTextureGetExtraRequiredSize(const DeviceCreateErrorTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUTextureDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUTextureDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateErrorTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorTextureSerialize(
    const DeviceCreateErrorTextureCmd& record,
    DeviceCreateErrorTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateErrorTexture;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorTextureSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateErrorTextureDeserialize(
    DeviceCreateErrorTextureCmd* record,
    const volatile DeviceCreateErrorTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateErrorTexture);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUTextureDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateErrorTextureDeserialize);

struct DeviceCreateExternalTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateExternalTextureTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateExternalTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateExternalTextureGetExtraRequiredSize(const DeviceCreateExternalTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExternalTextureDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExternalTextureDescriptorGetExtraRequiredSize(record.externalTextureDescriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateExternalTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateExternalTextureSerialize(
    const DeviceCreateExternalTextureCmd& record,
    DeviceCreateExternalTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateExternalTexture;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUExternalTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUExternalTextureDescriptorSerialize(record.externalTextureDescriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateExternalTextureSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateExternalTextureDeserialize(
    DeviceCreateExternalTextureCmd* record,
    const volatile DeviceCreateExternalTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateExternalTexture);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUExternalTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExternalTextureDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->externalTextureDescriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUExternalTextureDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateExternalTextureDeserialize);

struct DeviceCreatePipelineLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreatePipelineLayoutTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreatePipelineLayoutTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreatePipelineLayoutGetExtraRequiredSize(const DeviceCreatePipelineLayoutCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUPipelineLayoutDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUPipelineLayoutDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreatePipelineLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreatePipelineLayoutSerialize(
    const DeviceCreatePipelineLayoutCmd& record,
    DeviceCreatePipelineLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreatePipelineLayout;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUPipelineLayoutDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUPipelineLayoutDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreatePipelineLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreatePipelineLayoutDeserialize(
    DeviceCreatePipelineLayoutCmd* record,
    const volatile DeviceCreatePipelineLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreatePipelineLayout);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUPipelineLayoutDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUPipelineLayoutDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUPipelineLayoutDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreatePipelineLayoutDeserialize);

struct DeviceCreateQuerySetTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateQuerySetTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateQuerySetTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateQuerySetGetExtraRequiredSize(const DeviceCreateQuerySetCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUQuerySetDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUQuerySetDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateQuerySetGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateQuerySetSerialize(
    const DeviceCreateQuerySetCmd& record,
    DeviceCreateQuerySetTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateQuerySet;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUQuerySetDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUQuerySetDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateQuerySetSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateQuerySetDeserialize(
    DeviceCreateQuerySetCmd* record,
    const volatile DeviceCreateQuerySetTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateQuerySet);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUQuerySetDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUQuerySetDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUQuerySetDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateQuerySetDeserialize);

struct DeviceCreateRenderBundleEncoderTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateRenderBundleEncoderTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateRenderBundleEncoderTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateRenderBundleEncoderGetExtraRequiredSize(const DeviceCreateRenderBundleEncoderCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURenderBundleEncoderDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderBundleEncoderDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateRenderBundleEncoderGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateRenderBundleEncoderSerialize(
    const DeviceCreateRenderBundleEncoderCmd& record,
    DeviceCreateRenderBundleEncoderTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateRenderBundleEncoder;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPURenderBundleEncoderDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderBundleEncoderDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderBundleEncoderSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateRenderBundleEncoderDeserialize(
    DeviceCreateRenderBundleEncoderCmd* record,
    const volatile DeviceCreateRenderBundleEncoderTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateRenderBundleEncoder);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPURenderBundleEncoderDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderBundleEncoderDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderBundleEncoderDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderBundleEncoderDeserialize);

struct DeviceCreateRenderPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateRenderPipelineTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateRenderPipelineTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateRenderPipelineGetExtraRequiredSize(const DeviceCreateRenderPipelineCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURenderPipelineDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderPipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateRenderPipelineSerialize(
    const DeviceCreateRenderPipelineCmd& record,
    DeviceCreateRenderPipelineTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateRenderPipeline;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPURenderPipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateRenderPipelineDeserialize(
    DeviceCreateRenderPipelineCmd* record,
    const volatile DeviceCreateRenderPipelineTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateRenderPipeline);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPURenderPipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderPipelineDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineDeserialize);

struct DeviceCreateRenderPipelineAsyncTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId deviceId;
    uint64_t requestSerial;
    ObjectHandle pipelineObjectHandle;
};

static_assert(offsetof(DeviceCreateRenderPipelineAsyncTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateRenderPipelineAsyncTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateRenderPipelineAsyncGetExtraRequiredSize(const DeviceCreateRenderPipelineAsyncCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURenderPipelineDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderPipelineDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineAsyncGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateRenderPipelineAsyncSerialize(
    const DeviceCreateRenderPipelineAsyncCmd& record,
    DeviceCreateRenderPipelineAsyncTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateRenderPipelineAsync;


    transfer->deviceId = record.deviceId;
    transfer->requestSerial = record.requestSerial;
    transfer->pipelineObjectHandle = record.pipelineObjectHandle;
    {
        auto memberLength = 1u;

        WGPURenderPipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPipelineDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineAsyncSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateRenderPipelineAsyncDeserialize(
    DeviceCreateRenderPipelineAsyncCmd* record,
    const volatile DeviceCreateRenderPipelineAsyncTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateRenderPipelineAsync);


    static_assert(sizeof(record->deviceId) >= sizeof(transfer->deviceId), "Deserialize assignment may not narrow.");
    record->deviceId = transfer->deviceId;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->pipelineObjectHandle) >= sizeof(transfer->pipelineObjectHandle), "Deserialize assignment may not narrow.");
    record->pipelineObjectHandle = transfer->pipelineObjectHandle;
    {
        auto memberLength = 1u;
        const volatile WGPURenderPipelineDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderPipelineDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderPipelineDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateRenderPipelineAsyncDeserialize);

struct DeviceCreateSamplerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    bool has_descriptor;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateSamplerTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateSamplerTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateSamplerGetExtraRequiredSize(const DeviceCreateSamplerCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.descriptor != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUSamplerDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUSamplerDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateSamplerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateSamplerSerialize(
    const DeviceCreateSamplerCmd& record,
    DeviceCreateSamplerTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateSampler;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor) {
        auto memberLength = 1u;

        WGPUSamplerDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSamplerDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateSamplerSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateSamplerDeserialize(
    DeviceCreateSamplerCmd* record,
    const volatile DeviceCreateSamplerTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateSampler);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor) {
        auto memberLength = 1u;
        const volatile WGPUSamplerDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUSamplerDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSamplerDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateSamplerDeserialize);

struct DeviceCreateShaderModuleTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateShaderModuleTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateShaderModuleTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateShaderModuleGetExtraRequiredSize(const DeviceCreateShaderModuleCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUShaderModuleDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUShaderModuleDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateShaderModuleGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateShaderModuleSerialize(
    const DeviceCreateShaderModuleCmd& record,
    DeviceCreateShaderModuleTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateShaderModule;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUShaderModuleDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUShaderModuleDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateShaderModuleSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateShaderModuleDeserialize(
    DeviceCreateShaderModuleCmd* record,
    const volatile DeviceCreateShaderModuleTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateShaderModule);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUShaderModuleDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUShaderModuleDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUShaderModuleDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateShaderModuleDeserialize);

struct DeviceCreateSwapChainTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId surface;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateSwapChainTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateSwapChainTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateSwapChainGetExtraRequiredSize(const DeviceCreateSwapChainCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUSwapChainDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUSwapChainDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateSwapChainGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateSwapChainSerialize(
    const DeviceCreateSwapChainCmd& record,
    DeviceCreateSwapChainTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateSwapChain;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.surface, &transfer->surface));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUSwapChainDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSwapChainDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateSwapChainSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateSwapChainDeserialize(
    DeviceCreateSwapChainCmd* record,
    const volatile DeviceCreateSwapChainTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateSwapChain);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->surface, &record->surface));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUSwapChainDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUSwapChainDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSwapChainDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateSwapChainDeserialize);

struct DeviceCreateTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceCreateTextureTransfer, commandSize) == 0);
static_assert(offsetof(DeviceCreateTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceCreateTextureGetExtraRequiredSize(const DeviceCreateTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUTextureDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUTextureDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceCreateTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateTextureSerialize(
    const DeviceCreateTextureCmd& record,
    DeviceCreateTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceCreateTexture;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateTextureSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceCreateTextureDeserialize(
    DeviceCreateTextureCmd* record,
    const volatile DeviceCreateTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceCreateTexture);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUTextureDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceCreateTextureDeserialize);

struct DeviceDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(DeviceDestroyTransfer, commandSize) == 0);
static_assert(offsetof(DeviceDestroyTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceDestroyGetExtraRequiredSize(const DeviceDestroyCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceDestroySerialize(
    const DeviceDestroyCmd& record,
    DeviceDestroyTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceDestroy;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceDestroySerialize);

DAWN_DECLARE_UNUSED WireResult DeviceDestroyDeserialize(
    DeviceDestroyCmd* record,
    const volatile DeviceDestroyTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceDestroy);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceDestroyDeserialize);

struct DeviceForceLossTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    WGPUDeviceLostReason type;
    uint64_t messageStrlen;
};

static_assert(offsetof(DeviceForceLossTransfer, commandSize) == 0);
static_assert(offsetof(DeviceForceLossTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceForceLossGetExtraRequiredSize(const DeviceForceLossCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceForceLossGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceForceLossSerialize(
    const DeviceForceLossCmd& record,
    DeviceForceLossTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceForceLoss;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->type = record.type;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceForceLossSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceForceLossDeserialize(
    DeviceForceLossCmd* record,
    const volatile DeviceForceLossTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceForceLoss);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceForceLossDeserialize);

struct DeviceGetAdapterTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceGetAdapterTransfer, commandSize) == 0);
static_assert(offsetof(DeviceGetAdapterTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceGetAdapterGetExtraRequiredSize(const DeviceGetAdapterCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceGetAdapterGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceGetAdapterSerialize(
    const DeviceGetAdapterCmd& record,
    DeviceGetAdapterTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceGetAdapter;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceGetAdapterSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceGetAdapterDeserialize(
    DeviceGetAdapterCmd* record,
    const volatile DeviceGetAdapterTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceGetAdapter);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceGetAdapterDeserialize);

struct DeviceGetQueueTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(DeviceGetQueueTransfer, commandSize) == 0);
static_assert(offsetof(DeviceGetQueueTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceGetQueueGetExtraRequiredSize(const DeviceGetQueueCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceGetQueueGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceGetQueueSerialize(
    const DeviceGetQueueCmd& record,
    DeviceGetQueueTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceGetQueue;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceGetQueueSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceGetQueueDeserialize(
    DeviceGetQueueCmd* record,
    const volatile DeviceGetQueueTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceGetQueue);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceGetQueueDeserialize);

struct DeviceInjectErrorTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    WGPUErrorType type;
    uint64_t messageStrlen;
};

static_assert(offsetof(DeviceInjectErrorTransfer, commandSize) == 0);
static_assert(offsetof(DeviceInjectErrorTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceInjectErrorGetExtraRequiredSize(const DeviceInjectErrorCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceInjectErrorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceInjectErrorSerialize(
    const DeviceInjectErrorCmd& record,
    DeviceInjectErrorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceInjectError;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->type = record.type;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceInjectErrorSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceInjectErrorDeserialize(
    DeviceInjectErrorCmd* record,
    const volatile DeviceInjectErrorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceInjectError);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceInjectErrorDeserialize);

struct DevicePopErrorScopeTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId deviceId;
    uint64_t requestSerial;
};

static_assert(offsetof(DevicePopErrorScopeTransfer, commandSize) == 0);
static_assert(offsetof(DevicePopErrorScopeTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DevicePopErrorScopeGetExtraRequiredSize(const DevicePopErrorScopeCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DevicePopErrorScopeGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DevicePopErrorScopeSerialize(
    const DevicePopErrorScopeCmd& record,
    DevicePopErrorScopeTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DevicePopErrorScope;


    transfer->deviceId = record.deviceId;
    transfer->requestSerial = record.requestSerial;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DevicePopErrorScopeSerialize);

DAWN_DECLARE_UNUSED WireResult DevicePopErrorScopeDeserialize(
    DevicePopErrorScopeCmd* record,
    const volatile DevicePopErrorScopeTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DevicePopErrorScope);


    static_assert(sizeof(record->deviceId) >= sizeof(transfer->deviceId), "Deserialize assignment may not narrow.");
    record->deviceId = transfer->deviceId;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DevicePopErrorScopeDeserialize);

struct DevicePushErrorScopeTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    WGPUErrorFilter filter;
};

static_assert(offsetof(DevicePushErrorScopeTransfer, commandSize) == 0);
static_assert(offsetof(DevicePushErrorScopeTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DevicePushErrorScopeGetExtraRequiredSize(const DevicePushErrorScopeCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DevicePushErrorScopeGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DevicePushErrorScopeSerialize(
    const DevicePushErrorScopeCmd& record,
    DevicePushErrorScopeTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DevicePushErrorScope;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->filter = record.filter;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DevicePushErrorScopeSerialize);

DAWN_DECLARE_UNUSED WireResult DevicePushErrorScopeDeserialize(
    DevicePushErrorScopeCmd* record,
    const volatile DevicePushErrorScopeTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DevicePushErrorScope);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->filter) >= sizeof(transfer->filter), "Deserialize assignment may not narrow.");
    record->filter = transfer->filter;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DevicePushErrorScopeDeserialize);

struct DeviceSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(DeviceSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(DeviceSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceSetLabelGetExtraRequiredSize(const DeviceSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceSetLabelSerialize(
    const DeviceSetLabelCmd& record,
    DeviceSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceSetLabelDeserialize(
    DeviceSetLabelCmd* record,
    const volatile DeviceSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceSetLabelDeserialize);

struct DeviceTickTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(DeviceTickTransfer, commandSize) == 0);
static_assert(offsetof(DeviceTickTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceTickGetExtraRequiredSize(const DeviceTickCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceTickGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceTickSerialize(
    const DeviceTickCmd& record,
    DeviceTickTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceTick;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceTickSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceTickDeserialize(
    DeviceTickCmd* record,
    const volatile DeviceTickTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceTick);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceTickDeserialize);

struct DeviceValidateTextureDescriptorTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(DeviceValidateTextureDescriptorTransfer, commandSize) == 0);
static_assert(offsetof(DeviceValidateTextureDescriptorTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t DeviceValidateTextureDescriptorGetExtraRequiredSize(const DeviceValidateTextureDescriptorCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUTextureDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUTextureDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(DeviceValidateTextureDescriptorGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult DeviceValidateTextureDescriptorSerialize(
    const DeviceValidateTextureDescriptorCmd& record,
    DeviceValidateTextureDescriptorTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::DeviceValidateTextureDescriptor;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceValidateTextureDescriptorSerialize);

DAWN_DECLARE_UNUSED WireResult DeviceValidateTextureDescriptorDeserialize(
    DeviceValidateTextureDescriptorCmd* record,
    const volatile DeviceValidateTextureDescriptorTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::DeviceValidateTextureDescriptor);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUTextureDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUTextureDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(DeviceValidateTextureDescriptorDeserialize);

struct ExternalTextureDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(ExternalTextureDestroyTransfer, commandSize) == 0);
static_assert(offsetof(ExternalTextureDestroyTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ExternalTextureDestroyGetExtraRequiredSize(const ExternalTextureDestroyCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ExternalTextureDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureDestroySerialize(
    const ExternalTextureDestroyCmd& record,
    ExternalTextureDestroyTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ExternalTextureDestroy;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureDestroySerialize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureDestroyDeserialize(
    ExternalTextureDestroyCmd* record,
    const volatile ExternalTextureDestroyTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ExternalTextureDestroy);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureDestroyDeserialize);

struct ExternalTextureExpireTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(ExternalTextureExpireTransfer, commandSize) == 0);
static_assert(offsetof(ExternalTextureExpireTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ExternalTextureExpireGetExtraRequiredSize(const ExternalTextureExpireCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ExternalTextureExpireGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureExpireSerialize(
    const ExternalTextureExpireCmd& record,
    ExternalTextureExpireTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ExternalTextureExpire;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureExpireSerialize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureExpireDeserialize(
    ExternalTextureExpireCmd* record,
    const volatile ExternalTextureExpireTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ExternalTextureExpire);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureExpireDeserialize);

struct ExternalTextureRefreshTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(ExternalTextureRefreshTransfer, commandSize) == 0);
static_assert(offsetof(ExternalTextureRefreshTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ExternalTextureRefreshGetExtraRequiredSize(const ExternalTextureRefreshCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ExternalTextureRefreshGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureRefreshSerialize(
    const ExternalTextureRefreshCmd& record,
    ExternalTextureRefreshTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ExternalTextureRefresh;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureRefreshSerialize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureRefreshDeserialize(
    ExternalTextureRefreshCmd* record,
    const volatile ExternalTextureRefreshTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ExternalTextureRefresh);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureRefreshDeserialize);

struct ExternalTextureSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(ExternalTextureSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(ExternalTextureSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ExternalTextureSetLabelGetExtraRequiredSize(const ExternalTextureSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ExternalTextureSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureSetLabelSerialize(
    const ExternalTextureSetLabelCmd& record,
    ExternalTextureSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ExternalTextureSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult ExternalTextureSetLabelDeserialize(
    ExternalTextureSetLabelCmd* record,
    const volatile ExternalTextureSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ExternalTextureSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ExternalTextureSetLabelDeserialize);

struct InstanceCreateSurfaceTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(InstanceCreateSurfaceTransfer, commandSize) == 0);
static_assert(offsetof(InstanceCreateSurfaceTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t InstanceCreateSurfaceGetExtraRequiredSize(const InstanceCreateSurfaceCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUSurfaceDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUSurfaceDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(InstanceCreateSurfaceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult InstanceCreateSurfaceSerialize(
    const InstanceCreateSurfaceCmd& record,
    InstanceCreateSurfaceTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::InstanceCreateSurface;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    {
        auto memberLength = 1u;

        WGPUSurfaceDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSurfaceDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(InstanceCreateSurfaceSerialize);

DAWN_DECLARE_UNUSED WireResult InstanceCreateSurfaceDeserialize(
    InstanceCreateSurfaceCmd* record,
    const volatile InstanceCreateSurfaceTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::InstanceCreateSurface);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    {
        auto memberLength = 1u;
        const volatile WGPUSurfaceDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUSurfaceDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSurfaceDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(InstanceCreateSurfaceDeserialize);

struct InstanceProcessEventsTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(InstanceProcessEventsTransfer, commandSize) == 0);
static_assert(offsetof(InstanceProcessEventsTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t InstanceProcessEventsGetExtraRequiredSize(const InstanceProcessEventsCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(InstanceProcessEventsGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult InstanceProcessEventsSerialize(
    const InstanceProcessEventsCmd& record,
    InstanceProcessEventsTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::InstanceProcessEvents;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(InstanceProcessEventsSerialize);

DAWN_DECLARE_UNUSED WireResult InstanceProcessEventsDeserialize(
    InstanceProcessEventsCmd* record,
    const volatile InstanceProcessEventsTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::InstanceProcessEvents);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(InstanceProcessEventsDeserialize);

struct InstanceRequestAdapterTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId instanceId;
    uint64_t requestSerial;
    ObjectHandle adapterObjectHandle;
    bool has_options;
};

static_assert(offsetof(InstanceRequestAdapterTransfer, commandSize) == 0);
static_assert(offsetof(InstanceRequestAdapterTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t InstanceRequestAdapterGetExtraRequiredSize(const InstanceRequestAdapterCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.options != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURequestAdapterOptionsTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURequestAdapterOptionsGetExtraRequiredSize(record.options[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(InstanceRequestAdapterGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult InstanceRequestAdapterSerialize(
    const InstanceRequestAdapterCmd& record,
    InstanceRequestAdapterTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::InstanceRequestAdapter;


    transfer->instanceId = record.instanceId;
    transfer->requestSerial = record.requestSerial;
    transfer->adapterObjectHandle = record.adapterObjectHandle;
    bool has_options = record.options != nullptr;
    transfer->has_options = has_options;
    if (has_options) {
        auto memberLength = 1u;

        WGPURequestAdapterOptionsTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURequestAdapterOptionsSerialize(record.options[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(InstanceRequestAdapterSerialize);

DAWN_DECLARE_UNUSED WireResult InstanceRequestAdapterDeserialize(
    InstanceRequestAdapterCmd* record,
    const volatile InstanceRequestAdapterTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::InstanceRequestAdapter);


    static_assert(sizeof(record->instanceId) >= sizeof(transfer->instanceId), "Deserialize assignment may not narrow.");
    record->instanceId = transfer->instanceId;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->adapterObjectHandle) >= sizeof(transfer->adapterObjectHandle), "Deserialize assignment may not narrow.");
    record->adapterObjectHandle = transfer->adapterObjectHandle;
    bool has_options = transfer->has_options;
    record->options = nullptr;
    if (has_options) {
        auto memberLength = 1u;
        const volatile WGPURequestAdapterOptionsTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURequestAdapterOptions* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->options = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURequestAdapterOptionsDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(InstanceRequestAdapterDeserialize);

struct PipelineLayoutSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(PipelineLayoutSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(PipelineLayoutSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t PipelineLayoutSetLabelGetExtraRequiredSize(const PipelineLayoutSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(PipelineLayoutSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult PipelineLayoutSetLabelSerialize(
    const PipelineLayoutSetLabelCmd& record,
    PipelineLayoutSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::PipelineLayoutSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(PipelineLayoutSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult PipelineLayoutSetLabelDeserialize(
    PipelineLayoutSetLabelCmd* record,
    const volatile PipelineLayoutSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::PipelineLayoutSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(PipelineLayoutSetLabelDeserialize);

struct QuerySetDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(QuerySetDestroyTransfer, commandSize) == 0);
static_assert(offsetof(QuerySetDestroyTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QuerySetDestroyGetExtraRequiredSize(const QuerySetDestroyCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QuerySetDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QuerySetDestroySerialize(
    const QuerySetDestroyCmd& record,
    QuerySetDestroyTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QuerySetDestroy;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QuerySetDestroySerialize);

DAWN_DECLARE_UNUSED WireResult QuerySetDestroyDeserialize(
    QuerySetDestroyCmd* record,
    const volatile QuerySetDestroyTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QuerySetDestroy);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QuerySetDestroyDeserialize);

struct QuerySetSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(QuerySetSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(QuerySetSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QuerySetSetLabelGetExtraRequiredSize(const QuerySetSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QuerySetSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QuerySetSetLabelSerialize(
    const QuerySetSetLabelCmd& record,
    QuerySetSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QuerySetSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QuerySetSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult QuerySetSetLabelDeserialize(
    QuerySetSetLabelCmd* record,
    const volatile QuerySetSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QuerySetSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QuerySetSetLabelDeserialize);

struct QueueCopyExternalTextureForBrowserTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(QueueCopyExternalTextureForBrowserTransfer, commandSize) == 0);
static_assert(offsetof(QueueCopyExternalTextureForBrowserTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QueueCopyExternalTextureForBrowserGetExtraRequiredSize(const QueueCopyExternalTextureForBrowserCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyExternalTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyExternalTextureGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExtent3DTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUCopyTextureForBrowserOptionsTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUCopyTextureForBrowserOptionsGetExtraRequiredSize(record.options[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueCopyExternalTextureForBrowserGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QueueCopyExternalTextureForBrowserSerialize(
    const QueueCopyExternalTextureForBrowserCmd& record,
    QueueCopyExternalTextureForBrowserTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QueueCopyExternalTextureForBrowser;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUImageCopyExternalTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyExternalTextureSerialize(record.source[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.destination[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.copySize,
            sizeof(WGPUExtent3DTransfer) * memberLength);
    }
    {
        auto memberLength = 1u;

        WGPUCopyTextureForBrowserOptionsTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCopyTextureForBrowserOptionsSerialize(record.options[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueCopyExternalTextureForBrowserSerialize);

DAWN_DECLARE_UNUSED WireResult QueueCopyExternalTextureForBrowserDeserialize(
    QueueCopyExternalTextureForBrowserCmd* record,
    const volatile QueueCopyExternalTextureForBrowserTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QueueCopyExternalTextureForBrowser);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyExternalTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyExternalTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyExternalTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUExtent3DTransfer*>(memberBuffer),
           sizeof(WGPUExtent3DTransfer) * memberLength);
    }
    {
        auto memberLength = 1u;
        const volatile WGPUCopyTextureForBrowserOptionsTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUCopyTextureForBrowserOptions* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->options = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCopyTextureForBrowserOptionsDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueCopyExternalTextureForBrowserDeserialize);

struct QueueCopyTextureForBrowserTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(QueueCopyTextureForBrowserTransfer, commandSize) == 0);
static_assert(offsetof(QueueCopyTextureForBrowserTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QueueCopyTextureForBrowserGetExtraRequiredSize(const QueueCopyTextureForBrowserCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.source[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExtent3DTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExtent3DGetExtraRequiredSize(record.copySize[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUCopyTextureForBrowserOptionsTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUCopyTextureForBrowserOptionsGetExtraRequiredSize(record.options[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueCopyTextureForBrowserGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QueueCopyTextureForBrowserSerialize(
    const QueueCopyTextureForBrowserCmd& record,
    QueueCopyTextureForBrowserTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QueueCopyTextureForBrowser;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.source[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.destination[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.copySize,
            sizeof(WGPUExtent3DTransfer) * memberLength);
    }
    {
        auto memberLength = 1u;

        WGPUCopyTextureForBrowserOptionsTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCopyTextureForBrowserOptionsSerialize(record.options[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueCopyTextureForBrowserSerialize);

DAWN_DECLARE_UNUSED WireResult QueueCopyTextureForBrowserDeserialize(
    QueueCopyTextureForBrowserCmd* record,
    const volatile QueueCopyTextureForBrowserTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QueueCopyTextureForBrowser);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->source = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->copySize = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUExtent3DTransfer*>(memberBuffer),
           sizeof(WGPUExtent3DTransfer) * memberLength);
    }
    {
        auto memberLength = 1u;
        const volatile WGPUCopyTextureForBrowserOptionsTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUCopyTextureForBrowserOptions* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->options = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCopyTextureForBrowserOptionsDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueCopyTextureForBrowserDeserialize);

struct QueueOnSubmittedWorkDoneTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId queueId;
    uint64_t signalValue;
    uint64_t requestSerial;
};

static_assert(offsetof(QueueOnSubmittedWorkDoneTransfer, commandSize) == 0);
static_assert(offsetof(QueueOnSubmittedWorkDoneTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QueueOnSubmittedWorkDoneGetExtraRequiredSize(const QueueOnSubmittedWorkDoneCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueOnSubmittedWorkDoneGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QueueOnSubmittedWorkDoneSerialize(
    const QueueOnSubmittedWorkDoneCmd& record,
    QueueOnSubmittedWorkDoneTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QueueOnSubmittedWorkDone;


    transfer->queueId = record.queueId;
    transfer->signalValue = record.signalValue;
    transfer->requestSerial = record.requestSerial;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueOnSubmittedWorkDoneSerialize);

DAWN_DECLARE_UNUSED WireResult QueueOnSubmittedWorkDoneDeserialize(
    QueueOnSubmittedWorkDoneCmd* record,
    const volatile QueueOnSubmittedWorkDoneTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QueueOnSubmittedWorkDone);


    static_assert(sizeof(record->queueId) >= sizeof(transfer->queueId), "Deserialize assignment may not narrow.");
    record->queueId = transfer->queueId;
    static_assert(sizeof(record->signalValue) >= sizeof(transfer->signalValue), "Deserialize assignment may not narrow.");
    record->signalValue = transfer->signalValue;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueOnSubmittedWorkDoneDeserialize);

struct QueueSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(QueueSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(QueueSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QueueSetLabelGetExtraRequiredSize(const QueueSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QueueSetLabelSerialize(
    const QueueSetLabelCmd& record,
    QueueSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QueueSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult QueueSetLabelDeserialize(
    QueueSetLabelCmd* record,
    const volatile QueueSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QueueSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueSetLabelDeserialize);

struct QueueSubmitTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t commandCount;
};

static_assert(offsetof(QueueSubmitTransfer, commandSize) == 0);
static_assert(offsetof(QueueSubmitTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QueueSubmitGetExtraRequiredSize(const QueueSubmitCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.commandCount;
        auto size = WireAlignSizeofN<ObjectId>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueSubmitGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QueueSubmitSerialize(
    const QueueSubmitCmd& record,
    QueueSubmitTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QueueSubmit;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->commandCount = record.commandCount;
    {
        auto memberLength = record.commandCount;

        ObjectId* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(provider.GetId(record.commands[i], &memberBuffer[i]));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueSubmitSerialize);

DAWN_DECLARE_UNUSED WireResult QueueSubmitDeserialize(
    QueueSubmitCmd* record,
    const volatile QueueSubmitTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QueueSubmit);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    if (transfer->commandCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->commandCount = checked_cast<size_t>(transfer->commandCount);
    {
        auto memberLength = record->commandCount;
        const volatile ObjectId* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUCommandBuffer* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->commands = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(resolver.GetFromId(memberBuffer[i], &copiedMembers[i]));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueSubmitDeserialize);

struct QueueWriteBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId queueId;
    ObjectId bufferId;
    uint64_t bufferOffset;
    uint64_t size;
};

static_assert(offsetof(QueueWriteBufferTransfer, commandSize) == 0);
static_assert(offsetof(QueueWriteBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QueueWriteBufferGetExtraRequiredSize(const QueueWriteBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.size;
        auto size = WireAlignSizeofN<uint8_t>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueWriteBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QueueWriteBufferSerialize(
    const QueueWriteBufferCmd& record,
    QueueWriteBufferTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QueueWriteBuffer;


    transfer->queueId = record.queueId;
    transfer->bufferId = record.bufferId;
    transfer->bufferOffset = record.bufferOffset;
    transfer->size = record.size;
    {
        auto memberLength = record.size;

        uint8_t* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.data,
            sizeof(uint8_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueWriteBufferSerialize);

DAWN_DECLARE_UNUSED WireResult QueueWriteBufferDeserialize(
    QueueWriteBufferCmd* record,
    const volatile QueueWriteBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QueueWriteBuffer);


    static_assert(sizeof(record->queueId) >= sizeof(transfer->queueId), "Deserialize assignment may not narrow.");
    record->queueId = transfer->queueId;
    static_assert(sizeof(record->bufferId) >= sizeof(transfer->bufferId), "Deserialize assignment may not narrow.");
    record->bufferId = transfer->bufferId;
    static_assert(sizeof(record->bufferOffset) >= sizeof(transfer->bufferOffset), "Deserialize assignment may not narrow.");
    record->bufferOffset = transfer->bufferOffset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;
    {
        auto memberLength = record->size;
        const volatile uint8_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        record->data =
            const_cast<const uint8_t*>(memberBuffer);

    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueWriteBufferDeserialize);

struct QueueWriteTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId queueId;
    uint64_t dataSize;
};

static_assert(offsetof(QueueWriteTextureTransfer, commandSize) == 0);
static_assert(offsetof(QueueWriteTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t QueueWriteTextureGetExtraRequiredSize(const QueueWriteTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUImageCopyTextureTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUImageCopyTextureGetExtraRequiredSize(record.destination[i]);
        }
    }
    {
        auto memberLength = record.dataSize;
        auto size = WireAlignSizeofN<uint8_t>(memberLength);
        ASSERT(size);
        result += *size;
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUTextureDataLayoutTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUTextureDataLayoutGetExtraRequiredSize(record.dataLayout[i]);
        }
    }
    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUExtent3DTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUExtent3DGetExtraRequiredSize(record.writeSize[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(QueueWriteTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult QueueWriteTextureSerialize(
    const QueueWriteTextureCmd& record,
    QueueWriteTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::QueueWriteTexture;


    transfer->queueId = record.queueId;
    transfer->dataSize = record.dataSize;
    {
        auto memberLength = 1u;

        WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureSerialize(record.destination[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = record.dataSize;

        uint8_t* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.data,
            sizeof(uint8_t) * memberLength);
    }
    {
        auto memberLength = 1u;

        WGPUTextureDataLayoutTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDataLayoutSerialize(record.dataLayout[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = 1u;

        WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.writeSize,
            sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueWriteTextureSerialize);

DAWN_DECLARE_UNUSED WireResult QueueWriteTextureDeserialize(
    QueueWriteTextureCmd* record,
    const volatile QueueWriteTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::QueueWriteTexture);


    static_assert(sizeof(record->queueId) >= sizeof(transfer->queueId), "Deserialize assignment may not narrow.");
    record->queueId = transfer->queueId;
    static_assert(sizeof(record->dataSize) >= sizeof(transfer->dataSize), "Deserialize assignment may not narrow.");
    record->dataSize = transfer->dataSize;
    {
        auto memberLength = 1u;
        const volatile WGPUImageCopyTextureTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUImageCopyTexture* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->destination = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUImageCopyTextureDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = record->dataSize;
        const volatile uint8_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        record->data =
            const_cast<const uint8_t*>(memberBuffer);

    }
    {
        auto memberLength = 1u;
        const volatile WGPUTextureDataLayoutTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUTextureDataLayout* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dataLayout = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureDataLayoutDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = 1u;
        const volatile WGPUExtent3DTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUExtent3D* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->writeSize = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUExtent3DTransfer*>(memberBuffer),
           sizeof(WGPUExtent3DTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(QueueWriteTextureDeserialize);

struct RenderBundleEncoderDrawTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

static_assert(offsetof(RenderBundleEncoderDrawTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderDrawTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawGetExtraRequiredSize(const RenderBundleEncoderDrawCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawSerialize(
    const RenderBundleEncoderDrawCmd& record,
    RenderBundleEncoderDrawTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderDraw;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->vertexCount = record.vertexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstVertex = record.firstVertex;
    transfer->firstInstance = record.firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawDeserialize(
    RenderBundleEncoderDrawCmd* record,
    const volatile RenderBundleEncoderDrawTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDraw);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->vertexCount) >= sizeof(transfer->vertexCount), "Deserialize assignment may not narrow.");
    record->vertexCount = transfer->vertexCount;
    static_assert(sizeof(record->instanceCount) >= sizeof(transfer->instanceCount), "Deserialize assignment may not narrow.");
    record->instanceCount = transfer->instanceCount;
    static_assert(sizeof(record->firstVertex) >= sizeof(transfer->firstVertex), "Deserialize assignment may not narrow.");
    record->firstVertex = transfer->firstVertex;
    static_assert(sizeof(record->firstInstance) >= sizeof(transfer->firstInstance), "Deserialize assignment may not narrow.");
    record->firstInstance = transfer->firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawDeserialize);

struct RenderBundleEncoderDrawIndexedTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;
};

static_assert(offsetof(RenderBundleEncoderDrawIndexedTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderDrawIndexedTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawIndexedGetExtraRequiredSize(const RenderBundleEncoderDrawIndexedCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawIndexedSerialize(
    const RenderBundleEncoderDrawIndexedCmd& record,
    RenderBundleEncoderDrawIndexedTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderDrawIndexed;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->indexCount = record.indexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstIndex = record.firstIndex;
    transfer->baseVertex = record.baseVertex;
    transfer->firstInstance = record.firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawIndexedDeserialize(
    RenderBundleEncoderDrawIndexedCmd* record,
    const volatile RenderBundleEncoderDrawIndexedTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDrawIndexed);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->indexCount) >= sizeof(transfer->indexCount), "Deserialize assignment may not narrow.");
    record->indexCount = transfer->indexCount;
    static_assert(sizeof(record->instanceCount) >= sizeof(transfer->instanceCount), "Deserialize assignment may not narrow.");
    record->instanceCount = transfer->instanceCount;
    static_assert(sizeof(record->firstIndex) >= sizeof(transfer->firstIndex), "Deserialize assignment may not narrow.");
    record->firstIndex = transfer->firstIndex;
    static_assert(sizeof(record->baseVertex) >= sizeof(transfer->baseVertex), "Deserialize assignment may not narrow.");
    record->baseVertex = transfer->baseVertex;
    static_assert(sizeof(record->firstInstance) >= sizeof(transfer->firstInstance), "Deserialize assignment may not narrow.");
    record->firstInstance = transfer->firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedDeserialize);

struct RenderBundleEncoderDrawIndexedIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;
};

static_assert(offsetof(RenderBundleEncoderDrawIndexedIndirectTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderDrawIndexedIndirectTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawIndexedIndirectGetExtraRequiredSize(const RenderBundleEncoderDrawIndexedIndirectCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawIndexedIndirectSerialize(
    const RenderBundleEncoderDrawIndexedIndirectCmd& record,
    RenderBundleEncoderDrawIndexedIndirectTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderDrawIndexedIndirect;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.indirectBuffer, &transfer->indirectBuffer));
    transfer->indirectOffset = record.indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedIndirectSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawIndexedIndirectDeserialize(
    RenderBundleEncoderDrawIndexedIndirectCmd* record,
    const volatile RenderBundleEncoderDrawIndexedIndirectTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDrawIndexedIndirect);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    static_assert(sizeof(record->indirectOffset) >= sizeof(transfer->indirectOffset), "Deserialize assignment may not narrow.");
    record->indirectOffset = transfer->indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndexedIndirectDeserialize);

struct RenderBundleEncoderDrawIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;
};

static_assert(offsetof(RenderBundleEncoderDrawIndirectTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderDrawIndirectTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderDrawIndirectGetExtraRequiredSize(const RenderBundleEncoderDrawIndirectCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawIndirectSerialize(
    const RenderBundleEncoderDrawIndirectCmd& record,
    RenderBundleEncoderDrawIndirectTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderDrawIndirect;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.indirectBuffer, &transfer->indirectBuffer));
    transfer->indirectOffset = record.indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndirectSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderDrawIndirectDeserialize(
    RenderBundleEncoderDrawIndirectCmd* record,
    const volatile RenderBundleEncoderDrawIndirectTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderDrawIndirect);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    static_assert(sizeof(record->indirectOffset) >= sizeof(transfer->indirectOffset), "Deserialize assignment may not narrow.");
    record->indirectOffset = transfer->indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderDrawIndirectDeserialize);

struct RenderBundleEncoderFinishTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    bool has_descriptor;
    ObjectHandle result;
};

static_assert(offsetof(RenderBundleEncoderFinishTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderFinishTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderFinishGetExtraRequiredSize(const RenderBundleEncoderFinishCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.descriptor != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPURenderBundleDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPURenderBundleDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderFinishGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderFinishSerialize(
    const RenderBundleEncoderFinishCmd& record,
    RenderBundleEncoderFinishTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderFinish;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor) {
        auto memberLength = 1u;

        WGPURenderBundleDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderBundleDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderFinishSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderFinishDeserialize(
    RenderBundleEncoderFinishCmd* record,
    const volatile RenderBundleEncoderFinishTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderFinish);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor) {
        auto memberLength = 1u;
        const volatile WGPURenderBundleDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderBundleDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPURenderBundleDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderFinishDeserialize);

struct RenderBundleEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t markerLabelStrlen;
};

static_assert(offsetof(RenderBundleEncoderInsertDebugMarkerTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderInsertDebugMarkerGetExtraRequiredSize(const RenderBundleEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.markerLabel != nullptr);
    result += Align(std::strlen(record.markerLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderInsertDebugMarkerSerialize(
    const RenderBundleEncoderInsertDebugMarkerCmd& record,
    RenderBundleEncoderInsertDebugMarkerTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderInsertDebugMarker;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->markerLabelStrlen = std::strlen(record.markerLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->markerLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.markerLabel, transfer->markerLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderInsertDebugMarkerDeserialize(
    RenderBundleEncoderInsertDebugMarkerCmd* record,
    const volatile RenderBundleEncoderInsertDebugMarkerTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderInsertDebugMarker);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->markerLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderInsertDebugMarkerDeserialize);

struct RenderBundleEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(RenderBundleEncoderPopDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderPopDebugGroupGetExtraRequiredSize(const RenderBundleEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderPopDebugGroupSerialize(
    const RenderBundleEncoderPopDebugGroupCmd& record,
    RenderBundleEncoderPopDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderPopDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderPopDebugGroupDeserialize(
    RenderBundleEncoderPopDebugGroupCmd* record,
    const volatile RenderBundleEncoderPopDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderPopDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderPopDebugGroupDeserialize);

struct RenderBundleEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t groupLabelStrlen;
};

static_assert(offsetof(RenderBundleEncoderPushDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderPushDebugGroupGetExtraRequiredSize(const RenderBundleEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.groupLabel != nullptr);
    result += Align(std::strlen(record.groupLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderPushDebugGroupSerialize(
    const RenderBundleEncoderPushDebugGroupCmd& record,
    RenderBundleEncoderPushDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderPushDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->groupLabelStrlen = std::strlen(record.groupLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->groupLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.groupLabel, transfer->groupLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderPushDebugGroupDeserialize(
    RenderBundleEncoderPushDebugGroupCmd* record,
    const volatile RenderBundleEncoderPushDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderPushDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->groupLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderPushDebugGroupDeserialize);

struct RenderBundleEncoderSetBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectId group;
    uint64_t dynamicOffsetCount;
};

static_assert(offsetof(RenderBundleEncoderSetBindGroupTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderSetBindGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetBindGroupGetExtraRequiredSize(const RenderBundleEncoderSetBindGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.dynamicOffsetCount;
        auto size = WireAlignSizeofN<uint32_t>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetBindGroupSerialize(
    const RenderBundleEncoderSetBindGroupCmd& record,
    RenderBundleEncoderSetBindGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderSetBindGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->groupIndex = record.groupIndex;
    WIRE_TRY(provider.GetOptionalId(record.group, &transfer->group));
    transfer->dynamicOffsetCount = record.dynamicOffsetCount;
    {
        auto memberLength = record.dynamicOffsetCount;

        uint32_t* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.dynamicOffsets,
            sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetBindGroupSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetBindGroupDeserialize(
    RenderBundleEncoderSetBindGroupCmd* record,
    const volatile RenderBundleEncoderSetBindGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetBindGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->groupIndex) >= sizeof(transfer->groupIndex), "Deserialize assignment may not narrow.");
    record->groupIndex = transfer->groupIndex;
    WIRE_TRY(resolver.GetOptionalFromId(transfer->group, &record->group));
    if (transfer->dynamicOffsetCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->dynamicOffsetCount = checked_cast<size_t>(transfer->dynamicOffsetCount);
    {
        auto memberLength = record->dynamicOffsetCount;
        const volatile uint32_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint32_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dynamicOffsets = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint32_t*>(memberBuffer),
           sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetBindGroupDeserialize);

struct RenderBundleEncoderSetIndexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;
};

static_assert(offsetof(RenderBundleEncoderSetIndexBufferTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderSetIndexBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetIndexBufferGetExtraRequiredSize(const RenderBundleEncoderSetIndexBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetIndexBufferSerialize(
    const RenderBundleEncoderSetIndexBufferCmd& record,
    RenderBundleEncoderSetIndexBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderSetIndexBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.buffer, &transfer->buffer));
    transfer->format = record.format;
    transfer->offset = record.offset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetIndexBufferDeserialize(
    RenderBundleEncoderSetIndexBufferCmd* record,
    const volatile RenderBundleEncoderSetIndexBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetIndexBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetIndexBufferDeserialize);

struct RenderBundleEncoderSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(RenderBundleEncoderSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetLabelGetExtraRequiredSize(const RenderBundleEncoderSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetLabelSerialize(
    const RenderBundleEncoderSetLabelCmd& record,
    RenderBundleEncoderSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetLabelDeserialize(
    RenderBundleEncoderSetLabelCmd* record,
    const volatile RenderBundleEncoderSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetLabelDeserialize);

struct RenderBundleEncoderSetPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId pipeline;
};

static_assert(offsetof(RenderBundleEncoderSetPipelineTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderSetPipelineTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetPipelineGetExtraRequiredSize(const RenderBundleEncoderSetPipelineCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetPipelineSerialize(
    const RenderBundleEncoderSetPipelineCmd& record,
    RenderBundleEncoderSetPipelineTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderSetPipeline;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.pipeline, &transfer->pipeline));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetPipelineSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetPipelineDeserialize(
    RenderBundleEncoderSetPipelineCmd* record,
    const volatile RenderBundleEncoderSetPipelineTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetPipeline);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->pipeline, &record->pipeline));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetPipelineDeserialize);

struct RenderBundleEncoderSetVertexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t slot;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;
};

static_assert(offsetof(RenderBundleEncoderSetVertexBufferTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleEncoderSetVertexBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleEncoderSetVertexBufferGetExtraRequiredSize(const RenderBundleEncoderSetVertexBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleEncoderSetVertexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetVertexBufferSerialize(
    const RenderBundleEncoderSetVertexBufferCmd& record,
    RenderBundleEncoderSetVertexBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleEncoderSetVertexBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->slot = record.slot;
    WIRE_TRY(provider.GetOptionalId(record.buffer, &transfer->buffer));
    transfer->offset = record.offset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetVertexBufferSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleEncoderSetVertexBufferDeserialize(
    RenderBundleEncoderSetVertexBufferCmd* record,
    const volatile RenderBundleEncoderSetVertexBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleEncoderSetVertexBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->slot) >= sizeof(transfer->slot), "Deserialize assignment may not narrow.");
    record->slot = transfer->slot;
    WIRE_TRY(resolver.GetOptionalFromId(transfer->buffer, &record->buffer));
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleEncoderSetVertexBufferDeserialize);

struct RenderBundleSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(RenderBundleSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(RenderBundleSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderBundleSetLabelGetExtraRequiredSize(const RenderBundleSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderBundleSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderBundleSetLabelSerialize(
    const RenderBundleSetLabelCmd& record,
    RenderBundleSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderBundleSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult RenderBundleSetLabelDeserialize(
    RenderBundleSetLabelCmd* record,
    const volatile RenderBundleSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderBundleSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderBundleSetLabelDeserialize);

struct RenderPassEncoderBeginOcclusionQueryTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t queryIndex;
};

static_assert(offsetof(RenderPassEncoderBeginOcclusionQueryTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderBeginOcclusionQueryTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderBeginOcclusionQueryGetExtraRequiredSize(const RenderPassEncoderBeginOcclusionQueryCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderBeginOcclusionQueryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderBeginOcclusionQuerySerialize(
    const RenderPassEncoderBeginOcclusionQueryCmd& record,
    RenderPassEncoderBeginOcclusionQueryTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderBeginOcclusionQuery;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->queryIndex = record.queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderBeginOcclusionQuerySerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderBeginOcclusionQueryDeserialize(
    RenderPassEncoderBeginOcclusionQueryCmd* record,
    const volatile RenderPassEncoderBeginOcclusionQueryTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderBeginOcclusionQuery);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->queryIndex) >= sizeof(transfer->queryIndex), "Deserialize assignment may not narrow.");
    record->queryIndex = transfer->queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderBeginOcclusionQueryDeserialize);

struct RenderPassEncoderDrawTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

static_assert(offsetof(RenderPassEncoderDrawTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderDrawTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawGetExtraRequiredSize(const RenderPassEncoderDrawCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawSerialize(
    const RenderPassEncoderDrawCmd& record,
    RenderPassEncoderDrawTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderDraw;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->vertexCount = record.vertexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstVertex = record.firstVertex;
    transfer->firstInstance = record.firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawDeserialize(
    RenderPassEncoderDrawCmd* record,
    const volatile RenderPassEncoderDrawTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDraw);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->vertexCount) >= sizeof(transfer->vertexCount), "Deserialize assignment may not narrow.");
    record->vertexCount = transfer->vertexCount;
    static_assert(sizeof(record->instanceCount) >= sizeof(transfer->instanceCount), "Deserialize assignment may not narrow.");
    record->instanceCount = transfer->instanceCount;
    static_assert(sizeof(record->firstVertex) >= sizeof(transfer->firstVertex), "Deserialize assignment may not narrow.");
    record->firstVertex = transfer->firstVertex;
    static_assert(sizeof(record->firstInstance) >= sizeof(transfer->firstInstance), "Deserialize assignment may not narrow.");
    record->firstInstance = transfer->firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawDeserialize);

struct RenderPassEncoderDrawIndexedTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t baseVertex;
    uint32_t firstInstance;
};

static_assert(offsetof(RenderPassEncoderDrawIndexedTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderDrawIndexedTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawIndexedGetExtraRequiredSize(const RenderPassEncoderDrawIndexedCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawIndexedSerialize(
    const RenderPassEncoderDrawIndexedCmd& record,
    RenderPassEncoderDrawIndexedTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderDrawIndexed;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->indexCount = record.indexCount;
    transfer->instanceCount = record.instanceCount;
    transfer->firstIndex = record.firstIndex;
    transfer->baseVertex = record.baseVertex;
    transfer->firstInstance = record.firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawIndexedDeserialize(
    RenderPassEncoderDrawIndexedCmd* record,
    const volatile RenderPassEncoderDrawIndexedTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDrawIndexed);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->indexCount) >= sizeof(transfer->indexCount), "Deserialize assignment may not narrow.");
    record->indexCount = transfer->indexCount;
    static_assert(sizeof(record->instanceCount) >= sizeof(transfer->instanceCount), "Deserialize assignment may not narrow.");
    record->instanceCount = transfer->instanceCount;
    static_assert(sizeof(record->firstIndex) >= sizeof(transfer->firstIndex), "Deserialize assignment may not narrow.");
    record->firstIndex = transfer->firstIndex;
    static_assert(sizeof(record->baseVertex) >= sizeof(transfer->baseVertex), "Deserialize assignment may not narrow.");
    record->baseVertex = transfer->baseVertex;
    static_assert(sizeof(record->firstInstance) >= sizeof(transfer->firstInstance), "Deserialize assignment may not narrow.");
    record->firstInstance = transfer->firstInstance;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedDeserialize);

struct RenderPassEncoderDrawIndexedIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;
};

static_assert(offsetof(RenderPassEncoderDrawIndexedIndirectTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderDrawIndexedIndirectTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawIndexedIndirectGetExtraRequiredSize(const RenderPassEncoderDrawIndexedIndirectCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawIndexedIndirectSerialize(
    const RenderPassEncoderDrawIndexedIndirectCmd& record,
    RenderPassEncoderDrawIndexedIndirectTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderDrawIndexedIndirect;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.indirectBuffer, &transfer->indirectBuffer));
    transfer->indirectOffset = record.indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedIndirectSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawIndexedIndirectDeserialize(
    RenderPassEncoderDrawIndexedIndirectCmd* record,
    const volatile RenderPassEncoderDrawIndexedIndirectTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDrawIndexedIndirect);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    static_assert(sizeof(record->indirectOffset) >= sizeof(transfer->indirectOffset), "Deserialize assignment may not narrow.");
    record->indirectOffset = transfer->indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndexedIndirectDeserialize);

struct RenderPassEncoderDrawIndirectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId indirectBuffer;
    uint64_t indirectOffset;
};

static_assert(offsetof(RenderPassEncoderDrawIndirectTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderDrawIndirectTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderDrawIndirectGetExtraRequiredSize(const RenderPassEncoderDrawIndirectCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndirectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawIndirectSerialize(
    const RenderPassEncoderDrawIndirectCmd& record,
    RenderPassEncoderDrawIndirectTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderDrawIndirect;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.indirectBuffer, &transfer->indirectBuffer));
    transfer->indirectOffset = record.indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndirectSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderDrawIndirectDeserialize(
    RenderPassEncoderDrawIndirectCmd* record,
    const volatile RenderPassEncoderDrawIndirectTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderDrawIndirect);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->indirectBuffer, &record->indirectBuffer));
    static_assert(sizeof(record->indirectOffset) >= sizeof(transfer->indirectOffset), "Deserialize assignment may not narrow.");
    record->indirectOffset = transfer->indirectOffset;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderDrawIndirectDeserialize);

struct RenderPassEncoderEndTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(RenderPassEncoderEndTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderEndTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderEndGetExtraRequiredSize(const RenderPassEncoderEndCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderEndGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderEndSerialize(
    const RenderPassEncoderEndCmd& record,
    RenderPassEncoderEndTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderEnd;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderEndSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderEndDeserialize(
    RenderPassEncoderEndCmd* record,
    const volatile RenderPassEncoderEndTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderEnd);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderEndDeserialize);

struct RenderPassEncoderEndOcclusionQueryTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(RenderPassEncoderEndOcclusionQueryTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderEndOcclusionQueryTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderEndOcclusionQueryGetExtraRequiredSize(const RenderPassEncoderEndOcclusionQueryCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderEndOcclusionQueryGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderEndOcclusionQuerySerialize(
    const RenderPassEncoderEndOcclusionQueryCmd& record,
    RenderPassEncoderEndOcclusionQueryTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderEndOcclusionQuery;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderEndOcclusionQuerySerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderEndOcclusionQueryDeserialize(
    RenderPassEncoderEndOcclusionQueryCmd* record,
    const volatile RenderPassEncoderEndOcclusionQueryTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderEndOcclusionQuery);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderEndOcclusionQueryDeserialize);

struct RenderPassEncoderExecuteBundlesTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t bundleCount;
};

static_assert(offsetof(RenderPassEncoderExecuteBundlesTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderExecuteBundlesTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderExecuteBundlesGetExtraRequiredSize(const RenderPassEncoderExecuteBundlesCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.bundleCount;
        auto size = WireAlignSizeofN<ObjectId>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderExecuteBundlesGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderExecuteBundlesSerialize(
    const RenderPassEncoderExecuteBundlesCmd& record,
    RenderPassEncoderExecuteBundlesTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderExecuteBundles;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->bundleCount = record.bundleCount;
    {
        auto memberLength = record.bundleCount;

        ObjectId* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(provider.GetId(record.bundles[i], &memberBuffer[i]));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderExecuteBundlesSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderExecuteBundlesDeserialize(
    RenderPassEncoderExecuteBundlesCmd* record,
    const volatile RenderPassEncoderExecuteBundlesTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderExecuteBundles);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    if (transfer->bundleCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->bundleCount = checked_cast<size_t>(transfer->bundleCount);
    {
        auto memberLength = record->bundleCount;
        const volatile ObjectId* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPURenderBundle* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->bundles = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(resolver.GetFromId(memberBuffer[i], &copiedMembers[i]));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderExecuteBundlesDeserialize);

struct RenderPassEncoderInsertDebugMarkerTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t markerLabelStrlen;
};

static_assert(offsetof(RenderPassEncoderInsertDebugMarkerTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderInsertDebugMarkerTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderInsertDebugMarkerGetExtraRequiredSize(const RenderPassEncoderInsertDebugMarkerCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.markerLabel != nullptr);
    result += Align(std::strlen(record.markerLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderInsertDebugMarkerGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderInsertDebugMarkerSerialize(
    const RenderPassEncoderInsertDebugMarkerCmd& record,
    RenderPassEncoderInsertDebugMarkerTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderInsertDebugMarker;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->markerLabelStrlen = std::strlen(record.markerLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->markerLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.markerLabel, transfer->markerLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderInsertDebugMarkerSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderInsertDebugMarkerDeserialize(
    RenderPassEncoderInsertDebugMarkerCmd* record,
    const volatile RenderPassEncoderInsertDebugMarkerTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderInsertDebugMarker);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->markerLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->markerLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderInsertDebugMarkerDeserialize);

struct RenderPassEncoderPopDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(RenderPassEncoderPopDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderPopDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderPopDebugGroupGetExtraRequiredSize(const RenderPassEncoderPopDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderPopDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderPopDebugGroupSerialize(
    const RenderPassEncoderPopDebugGroupCmd& record,
    RenderPassEncoderPopDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderPopDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderPopDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderPopDebugGroupDeserialize(
    RenderPassEncoderPopDebugGroupCmd* record,
    const volatile RenderPassEncoderPopDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderPopDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderPopDebugGroupDeserialize);

struct RenderPassEncoderPushDebugGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t groupLabelStrlen;
};

static_assert(offsetof(RenderPassEncoderPushDebugGroupTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderPushDebugGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderPushDebugGroupGetExtraRequiredSize(const RenderPassEncoderPushDebugGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.groupLabel != nullptr);
    result += Align(std::strlen(record.groupLabel), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderPushDebugGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderPushDebugGroupSerialize(
    const RenderPassEncoderPushDebugGroupCmd& record,
    RenderPassEncoderPushDebugGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderPushDebugGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->groupLabelStrlen = std::strlen(record.groupLabel);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->groupLabelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.groupLabel, transfer->groupLabelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderPushDebugGroupSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderPushDebugGroupDeserialize(
    RenderPassEncoderPushDebugGroupCmd* record,
    const volatile RenderPassEncoderPushDebugGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderPushDebugGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->groupLabelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->groupLabel = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderPushDebugGroupDeserialize);

struct RenderPassEncoderSetBindGroupTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectId group;
    uint64_t dynamicOffsetCount;
};

static_assert(offsetof(RenderPassEncoderSetBindGroupTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetBindGroupTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetBindGroupGetExtraRequiredSize(const RenderPassEncoderSetBindGroupCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = record.dynamicOffsetCount;
        auto size = WireAlignSizeofN<uint32_t>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetBindGroupGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetBindGroupSerialize(
    const RenderPassEncoderSetBindGroupCmd& record,
    RenderPassEncoderSetBindGroupTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetBindGroup;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->groupIndex = record.groupIndex;
    WIRE_TRY(provider.GetOptionalId(record.group, &transfer->group));
    transfer->dynamicOffsetCount = record.dynamicOffsetCount;
    {
        auto memberLength = record.dynamicOffsetCount;

        uint32_t* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.dynamicOffsets,
            sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBindGroupSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetBindGroupDeserialize(
    RenderPassEncoderSetBindGroupCmd* record,
    const volatile RenderPassEncoderSetBindGroupTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetBindGroup);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->groupIndex) >= sizeof(transfer->groupIndex), "Deserialize assignment may not narrow.");
    record->groupIndex = transfer->groupIndex;
    WIRE_TRY(resolver.GetOptionalFromId(transfer->group, &record->group));
    if (transfer->dynamicOffsetCount > std::numeric_limits<size_t>::max()) return WireResult::FatalError;
    record->dynamicOffsetCount = checked_cast<size_t>(transfer->dynamicOffsetCount);
    {
        auto memberLength = record->dynamicOffsetCount;
        const volatile uint32_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint32_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->dynamicOffsets = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint32_t*>(memberBuffer),
           sizeof(uint32_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBindGroupDeserialize);

struct RenderPassEncoderSetBlendConstantTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(RenderPassEncoderSetBlendConstantTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetBlendConstantTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetBlendConstantGetExtraRequiredSize(const RenderPassEncoderSetBlendConstantCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUColorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUColorGetExtraRequiredSize(record.color[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetBlendConstantGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetBlendConstantSerialize(
    const RenderPassEncoderSetBlendConstantCmd& record,
    RenderPassEncoderSetBlendConstantTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetBlendConstant;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        auto memberLength = 1u;

        WGPUColorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.color,
            sizeof(WGPUColorTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBlendConstantSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetBlendConstantDeserialize(
    RenderPassEncoderSetBlendConstantCmd* record,
    const volatile RenderPassEncoderSetBlendConstantTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetBlendConstant);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        auto memberLength = 1u;
        const volatile WGPUColorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUColor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->color = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUColorTransfer*>(memberBuffer),
           sizeof(WGPUColorTransfer) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetBlendConstantDeserialize);

struct RenderPassEncoderSetIndexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId buffer;
    WGPUIndexFormat format;
    uint64_t offset;
    uint64_t size;
};

static_assert(offsetof(RenderPassEncoderSetIndexBufferTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetIndexBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetIndexBufferGetExtraRequiredSize(const RenderPassEncoderSetIndexBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetIndexBufferSerialize(
    const RenderPassEncoderSetIndexBufferCmd& record,
    RenderPassEncoderSetIndexBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetIndexBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.buffer, &transfer->buffer));
    transfer->format = record.format;
    transfer->offset = record.offset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetIndexBufferDeserialize(
    RenderPassEncoderSetIndexBufferCmd* record,
    const volatile RenderPassEncoderSetIndexBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetIndexBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->buffer, &record->buffer));
    static_assert(sizeof(record->format) >= sizeof(transfer->format), "Deserialize assignment may not narrow.");
    record->format = transfer->format;
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetIndexBufferDeserialize);

struct RenderPassEncoderSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(RenderPassEncoderSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetLabelGetExtraRequiredSize(const RenderPassEncoderSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetLabelSerialize(
    const RenderPassEncoderSetLabelCmd& record,
    RenderPassEncoderSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetLabelDeserialize(
    RenderPassEncoderSetLabelCmd* record,
    const volatile RenderPassEncoderSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetLabelDeserialize);

struct RenderPassEncoderSetPipelineTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId pipeline;
};

static_assert(offsetof(RenderPassEncoderSetPipelineTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetPipelineTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetPipelineGetExtraRequiredSize(const RenderPassEncoderSetPipelineCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetPipelineGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetPipelineSerialize(
    const RenderPassEncoderSetPipelineCmd& record,
    RenderPassEncoderSetPipelineTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetPipeline;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.pipeline, &transfer->pipeline));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetPipelineSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetPipelineDeserialize(
    RenderPassEncoderSetPipelineCmd* record,
    const volatile RenderPassEncoderSetPipelineTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetPipeline);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->pipeline, &record->pipeline));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetPipelineDeserialize);

struct RenderPassEncoderSetScissorRectTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

static_assert(offsetof(RenderPassEncoderSetScissorRectTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetScissorRectTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetScissorRectGetExtraRequiredSize(const RenderPassEncoderSetScissorRectCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetScissorRectGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetScissorRectSerialize(
    const RenderPassEncoderSetScissorRectCmd& record,
    RenderPassEncoderSetScissorRectTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetScissorRect;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->x = record.x;
    transfer->y = record.y;
    transfer->width = record.width;
    transfer->height = record.height;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetScissorRectSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetScissorRectDeserialize(
    RenderPassEncoderSetScissorRectCmd* record,
    const volatile RenderPassEncoderSetScissorRectTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetScissorRect);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->x) >= sizeof(transfer->x), "Deserialize assignment may not narrow.");
    record->x = transfer->x;
    static_assert(sizeof(record->y) >= sizeof(transfer->y), "Deserialize assignment may not narrow.");
    record->y = transfer->y;
    static_assert(sizeof(record->width) >= sizeof(transfer->width), "Deserialize assignment may not narrow.");
    record->width = transfer->width;
    static_assert(sizeof(record->height) >= sizeof(transfer->height), "Deserialize assignment may not narrow.");
    record->height = transfer->height;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetScissorRectDeserialize);

struct RenderPassEncoderSetStencilReferenceTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t reference;
};

static_assert(offsetof(RenderPassEncoderSetStencilReferenceTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetStencilReferenceTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetStencilReferenceGetExtraRequiredSize(const RenderPassEncoderSetStencilReferenceCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetStencilReferenceGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetStencilReferenceSerialize(
    const RenderPassEncoderSetStencilReferenceCmd& record,
    RenderPassEncoderSetStencilReferenceTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetStencilReference;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->reference = record.reference;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetStencilReferenceSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetStencilReferenceDeserialize(
    RenderPassEncoderSetStencilReferenceCmd* record,
    const volatile RenderPassEncoderSetStencilReferenceTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetStencilReference);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->reference) >= sizeof(transfer->reference), "Deserialize assignment may not narrow.");
    record->reference = transfer->reference;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetStencilReferenceDeserialize);

struct RenderPassEncoderSetVertexBufferTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t slot;
    ObjectId buffer;
    uint64_t offset;
    uint64_t size;
};

static_assert(offsetof(RenderPassEncoderSetVertexBufferTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetVertexBufferTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetVertexBufferGetExtraRequiredSize(const RenderPassEncoderSetVertexBufferCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetVertexBufferGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetVertexBufferSerialize(
    const RenderPassEncoderSetVertexBufferCmd& record,
    RenderPassEncoderSetVertexBufferTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetVertexBuffer;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->slot = record.slot;
    WIRE_TRY(provider.GetOptionalId(record.buffer, &transfer->buffer));
    transfer->offset = record.offset;
    transfer->size = record.size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetVertexBufferSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetVertexBufferDeserialize(
    RenderPassEncoderSetVertexBufferCmd* record,
    const volatile RenderPassEncoderSetVertexBufferTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetVertexBuffer);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->slot) >= sizeof(transfer->slot), "Deserialize assignment may not narrow.");
    record->slot = transfer->slot;
    WIRE_TRY(resolver.GetOptionalFromId(transfer->buffer, &record->buffer));
    static_assert(sizeof(record->offset) >= sizeof(transfer->offset), "Deserialize assignment may not narrow.");
    record->offset = transfer->offset;
    static_assert(sizeof(record->size) >= sizeof(transfer->size), "Deserialize assignment may not narrow.");
    record->size = transfer->size;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetVertexBufferDeserialize);

struct RenderPassEncoderSetViewportTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;
};

static_assert(offsetof(RenderPassEncoderSetViewportTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderSetViewportTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderSetViewportGetExtraRequiredSize(const RenderPassEncoderSetViewportCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderSetViewportGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetViewportSerialize(
    const RenderPassEncoderSetViewportCmd& record,
    RenderPassEncoderSetViewportTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderSetViewport;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->x = record.x;
    transfer->y = record.y;
    transfer->width = record.width;
    transfer->height = record.height;
    transfer->minDepth = record.minDepth;
    transfer->maxDepth = record.maxDepth;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetViewportSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderSetViewportDeserialize(
    RenderPassEncoderSetViewportCmd* record,
    const volatile RenderPassEncoderSetViewportTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderSetViewport);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->x) >= sizeof(transfer->x), "Deserialize assignment may not narrow.");
    record->x = transfer->x;
    static_assert(sizeof(record->y) >= sizeof(transfer->y), "Deserialize assignment may not narrow.");
    record->y = transfer->y;
    static_assert(sizeof(record->width) >= sizeof(transfer->width), "Deserialize assignment may not narrow.");
    record->width = transfer->width;
    static_assert(sizeof(record->height) >= sizeof(transfer->height), "Deserialize assignment may not narrow.");
    record->height = transfer->height;
    static_assert(sizeof(record->minDepth) >= sizeof(transfer->minDepth), "Deserialize assignment may not narrow.");
    record->minDepth = transfer->minDepth;
    static_assert(sizeof(record->maxDepth) >= sizeof(transfer->maxDepth), "Deserialize assignment may not narrow.");
    record->maxDepth = transfer->maxDepth;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderSetViewportDeserialize);

struct RenderPassEncoderWriteTimestampTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectId querySet;
    uint32_t queryIndex;
};

static_assert(offsetof(RenderPassEncoderWriteTimestampTransfer, commandSize) == 0);
static_assert(offsetof(RenderPassEncoderWriteTimestampTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPassEncoderWriteTimestampGetExtraRequiredSize(const RenderPassEncoderWriteTimestampCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPassEncoderWriteTimestampGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderWriteTimestampSerialize(
    const RenderPassEncoderWriteTimestampCmd& record,
    RenderPassEncoderWriteTimestampTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPassEncoderWriteTimestamp;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    WIRE_TRY(provider.GetId(record.querySet, &transfer->querySet));
    transfer->queryIndex = record.queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderWriteTimestampSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPassEncoderWriteTimestampDeserialize(
    RenderPassEncoderWriteTimestampCmd* record,
    const volatile RenderPassEncoderWriteTimestampTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPassEncoderWriteTimestamp);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    WIRE_TRY(resolver.GetFromId(transfer->querySet, &record->querySet));
    static_assert(sizeof(record->queryIndex) >= sizeof(transfer->queryIndex), "Deserialize assignment may not narrow.");
    record->queryIndex = transfer->queryIndex;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPassEncoderWriteTimestampDeserialize);

struct RenderPipelineGetBindGroupLayoutTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint32_t groupIndex;
    ObjectHandle result;
};

static_assert(offsetof(RenderPipelineGetBindGroupLayoutTransfer, commandSize) == 0);
static_assert(offsetof(RenderPipelineGetBindGroupLayoutTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPipelineGetBindGroupLayoutGetExtraRequiredSize(const RenderPipelineGetBindGroupLayoutCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPipelineGetBindGroupLayoutGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPipelineGetBindGroupLayoutSerialize(
    const RenderPipelineGetBindGroupLayoutCmd& record,
    RenderPipelineGetBindGroupLayoutTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPipelineGetBindGroupLayout;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->groupIndex = record.groupIndex;
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPipelineGetBindGroupLayoutSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPipelineGetBindGroupLayoutDeserialize(
    RenderPipelineGetBindGroupLayoutCmd* record,
    const volatile RenderPipelineGetBindGroupLayoutTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPipelineGetBindGroupLayout);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->groupIndex) >= sizeof(transfer->groupIndex), "Deserialize assignment may not narrow.");
    record->groupIndex = transfer->groupIndex;
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPipelineGetBindGroupLayoutDeserialize);

struct RenderPipelineSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(RenderPipelineSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(RenderPipelineSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t RenderPipelineSetLabelGetExtraRequiredSize(const RenderPipelineSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(RenderPipelineSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult RenderPipelineSetLabelSerialize(
    const RenderPipelineSetLabelCmd& record,
    RenderPipelineSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::RenderPipelineSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPipelineSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult RenderPipelineSetLabelDeserialize(
    RenderPipelineSetLabelCmd* record,
    const volatile RenderPipelineSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::RenderPipelineSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(RenderPipelineSetLabelDeserialize);

struct SamplerSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(SamplerSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(SamplerSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t SamplerSetLabelGetExtraRequiredSize(const SamplerSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(SamplerSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult SamplerSetLabelSerialize(
    const SamplerSetLabelCmd& record,
    SamplerSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::SamplerSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SamplerSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult SamplerSetLabelDeserialize(
    SamplerSetLabelCmd* record,
    const volatile SamplerSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::SamplerSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SamplerSetLabelDeserialize);

struct ShaderModuleGetCompilationInfoTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId shaderModuleId;
    uint64_t requestSerial;
};

static_assert(offsetof(ShaderModuleGetCompilationInfoTransfer, commandSize) == 0);
static_assert(offsetof(ShaderModuleGetCompilationInfoTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ShaderModuleGetCompilationInfoGetExtraRequiredSize(const ShaderModuleGetCompilationInfoCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ShaderModuleGetCompilationInfoGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ShaderModuleGetCompilationInfoSerialize(
    const ShaderModuleGetCompilationInfoCmd& record,
    ShaderModuleGetCompilationInfoTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ShaderModuleGetCompilationInfo;


    transfer->shaderModuleId = record.shaderModuleId;
    transfer->requestSerial = record.requestSerial;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ShaderModuleGetCompilationInfoSerialize);

DAWN_DECLARE_UNUSED WireResult ShaderModuleGetCompilationInfoDeserialize(
    ShaderModuleGetCompilationInfoCmd* record,
    const volatile ShaderModuleGetCompilationInfoTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ShaderModuleGetCompilationInfo);


    static_assert(sizeof(record->shaderModuleId) >= sizeof(transfer->shaderModuleId), "Deserialize assignment may not narrow.");
    record->shaderModuleId = transfer->shaderModuleId;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ShaderModuleGetCompilationInfoDeserialize);

struct ShaderModuleSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(ShaderModuleSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(ShaderModuleSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ShaderModuleSetLabelGetExtraRequiredSize(const ShaderModuleSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ShaderModuleSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ShaderModuleSetLabelSerialize(
    const ShaderModuleSetLabelCmd& record,
    ShaderModuleSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::ShaderModuleSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ShaderModuleSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult ShaderModuleSetLabelDeserialize(
    ShaderModuleSetLabelCmd* record,
    const volatile ShaderModuleSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::ShaderModuleSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ShaderModuleSetLabelDeserialize);

struct SwapChainGetCurrentTextureTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(SwapChainGetCurrentTextureTransfer, commandSize) == 0);
static_assert(offsetof(SwapChainGetCurrentTextureTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t SwapChainGetCurrentTextureGetExtraRequiredSize(const SwapChainGetCurrentTextureCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult SwapChainGetCurrentTextureSerialize(
    const SwapChainGetCurrentTextureCmd& record,
    SwapChainGetCurrentTextureTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::SwapChainGetCurrentTexture;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureSerialize);

DAWN_DECLARE_UNUSED WireResult SwapChainGetCurrentTextureDeserialize(
    SwapChainGetCurrentTextureCmd* record,
    const volatile SwapChainGetCurrentTextureTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::SwapChainGetCurrentTexture);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureDeserialize);

struct SwapChainGetCurrentTextureViewTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    ObjectHandle result;
};

static_assert(offsetof(SwapChainGetCurrentTextureViewTransfer, commandSize) == 0);
static_assert(offsetof(SwapChainGetCurrentTextureViewTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t SwapChainGetCurrentTextureViewGetExtraRequiredSize(const SwapChainGetCurrentTextureViewCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureViewGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult SwapChainGetCurrentTextureViewSerialize(
    const SwapChainGetCurrentTextureViewCmd& record,
    SwapChainGetCurrentTextureViewTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::SwapChainGetCurrentTextureView;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureViewSerialize);

DAWN_DECLARE_UNUSED WireResult SwapChainGetCurrentTextureViewDeserialize(
    SwapChainGetCurrentTextureViewCmd* record,
    const volatile SwapChainGetCurrentTextureViewTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::SwapChainGetCurrentTextureView);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainGetCurrentTextureViewDeserialize);

struct SwapChainPresentTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(SwapChainPresentTransfer, commandSize) == 0);
static_assert(offsetof(SwapChainPresentTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t SwapChainPresentGetExtraRequiredSize(const SwapChainPresentCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(SwapChainPresentGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult SwapChainPresentSerialize(
    const SwapChainPresentCmd& record,
    SwapChainPresentTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::SwapChainPresent;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainPresentSerialize);

DAWN_DECLARE_UNUSED WireResult SwapChainPresentDeserialize(
    SwapChainPresentCmd* record,
    const volatile SwapChainPresentTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::SwapChainPresent);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(SwapChainPresentDeserialize);

struct TextureCreateViewTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    bool has_descriptor;
    ObjectHandle result;
};

static_assert(offsetof(TextureCreateViewTransfer, commandSize) == 0);
static_assert(offsetof(TextureCreateViewTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t TextureCreateViewGetExtraRequiredSize(const TextureCreateViewCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.descriptor != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUTextureViewDescriptorTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUTextureViewDescriptorGetExtraRequiredSize(record.descriptor[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(TextureCreateViewGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult TextureCreateViewSerialize(
    const TextureCreateViewCmd& record,
    TextureCreateViewTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::TextureCreateView;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    transfer->result = record.result;
    bool has_descriptor = record.descriptor != nullptr;
    transfer->has_descriptor = has_descriptor;
    if (has_descriptor) {
        auto memberLength = 1u;

        WGPUTextureViewDescriptorTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureViewDescriptorSerialize(record.descriptor[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureCreateViewSerialize);

DAWN_DECLARE_UNUSED WireResult TextureCreateViewDeserialize(
    TextureCreateViewCmd* record,
    const volatile TextureCreateViewTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::TextureCreateView);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    static_assert(sizeof(record->result) >= sizeof(transfer->result), "Deserialize assignment may not narrow.");
    record->result = transfer->result;
    bool has_descriptor = transfer->has_descriptor;
    record->descriptor = nullptr;
    if (has_descriptor) {
        auto memberLength = 1u;
        const volatile WGPUTextureViewDescriptorTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUTextureViewDescriptor* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->descriptor = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUTextureViewDescriptorDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureCreateViewDeserialize);

struct TextureDestroyTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
};

static_assert(offsetof(TextureDestroyTransfer, commandSize) == 0);
static_assert(offsetof(TextureDestroyTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t TextureDestroyGetExtraRequiredSize(const TextureDestroyCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(TextureDestroyGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult TextureDestroySerialize(
    const TextureDestroyCmd& record,
    TextureDestroyTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::TextureDestroy;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureDestroySerialize);

DAWN_DECLARE_UNUSED WireResult TextureDestroyDeserialize(
    TextureDestroyCmd* record,
    const volatile TextureDestroyTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::TextureDestroy);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureDestroyDeserialize);

struct TextureSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(TextureSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(TextureSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t TextureSetLabelGetExtraRequiredSize(const TextureSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(TextureSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult TextureSetLabelSerialize(
    const TextureSetLabelCmd& record,
    TextureSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::TextureSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult TextureSetLabelDeserialize(
    TextureSetLabelCmd* record,
    const volatile TextureSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::TextureSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureSetLabelDeserialize);

struct TextureViewSetLabelTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    WireCmd commandId;

    ObjectId self;
    uint64_t labelStrlen;
};

static_assert(offsetof(TextureViewSetLabelTransfer, commandSize) == 0);
static_assert(offsetof(TextureViewSetLabelTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t TextureViewSetLabelGetExtraRequiredSize(const TextureViewSetLabelCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.label != nullptr);
    result += Align(std::strlen(record.label), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(TextureViewSetLabelGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult TextureViewSetLabelSerialize(
    const TextureViewSetLabelCmd& record,
    TextureViewSetLabelTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = WireCmd::TextureViewSetLabel;


    WIRE_TRY(provider.GetId(record.self, &transfer->self));
    {
        transfer->labelStrlen = std::strlen(record.label);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->labelStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.label, transfer->labelStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureViewSetLabelSerialize);

DAWN_DECLARE_UNUSED WireResult TextureViewSetLabelDeserialize(
    TextureViewSetLabelCmd* record,
    const volatile TextureViewSetLabelTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == WireCmd::TextureViewSetLabel);
    record->selfId = transfer->self;


    WIRE_TRY(resolver.GetFromId(transfer->self, &record->self));
    {
        uint64_t stringLength64 = transfer->labelStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->label = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(TextureViewSetLabelDeserialize);


struct ReturnAdapterRequestDeviceCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle adapter;
    uint64_t requestSerial;
    WGPURequestDeviceStatus status;
    uint64_t messageStrlen;
    bool has_message;
    bool has_limits;
    uint32_t featuresCount;
};

static_assert(offsetof(ReturnAdapterRequestDeviceCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnAdapterRequestDeviceCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnAdapterRequestDeviceCallbackGetExtraRequiredSize(const ReturnAdapterRequestDeviceCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.message != nullptr) {
        result += Align(std::strlen(record.message), kWireBufferAlignment);
    }
    if (record.limits != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUSupportedLimitsTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUSupportedLimitsGetExtraRequiredSize(record.limits[i]);
        }
    }
    {
        auto memberLength = record.featuresCount;
        auto size = WireAlignSizeofN<WGPUFeatureName>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnAdapterRequestDeviceCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnAdapterRequestDeviceCallbackSerialize(
    const ReturnAdapterRequestDeviceCallbackCmd& record,
    ReturnAdapterRequestDeviceCallbackTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::AdapterRequestDeviceCallback;


    transfer->adapter = record.adapter;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;
    transfer->featuresCount = record.featuresCount;
    bool has_message = record.message != nullptr;
    transfer->has_message = has_message;
    if (has_message) {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }
    bool has_limits = record.limits != nullptr;
    transfer->has_limits = has_limits;
    if (has_limits) {
        auto memberLength = 1u;

        WGPUSupportedLimitsTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSupportedLimitsSerialize(record.limits[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = record.featuresCount;

        WGPUFeatureName* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.features,
            sizeof(WGPUFeatureName) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnAdapterRequestDeviceCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnAdapterRequestDeviceCallbackDeserialize(
    ReturnAdapterRequestDeviceCallbackCmd* record,
    const volatile ReturnAdapterRequestDeviceCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::AdapterRequestDeviceCallback);


    static_assert(sizeof(record->adapter) >= sizeof(transfer->adapter), "Deserialize assignment may not narrow.");
    record->adapter = transfer->adapter;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->status) >= sizeof(transfer->status), "Deserialize assignment may not narrow.");
    record->status = transfer->status;
    static_assert(sizeof(record->featuresCount) >= sizeof(transfer->featuresCount), "Deserialize assignment may not narrow.");
    record->featuresCount = transfer->featuresCount;
    bool has_message = transfer->has_message;
    record->message = nullptr;
    if (has_message) {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }
    bool has_limits = transfer->has_limits;
    record->limits = nullptr;
    if (has_limits) {
        auto memberLength = 1u;
        const volatile WGPUSupportedLimitsTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUSupportedLimits* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->limits = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSupportedLimitsDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = record->featuresCount;
        const volatile WGPUFeatureName* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUFeatureName* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->features = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUFeatureName*>(memberBuffer),
           sizeof(WGPUFeatureName) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnAdapterRequestDeviceCallbackDeserialize);

struct ReturnBufferMapAsyncCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle buffer;
    uint64_t requestSerial;
    uint32_t status;
    uint64_t readDataUpdateInfoLength;
};

static_assert(offsetof(ReturnBufferMapAsyncCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnBufferMapAsyncCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnBufferMapAsyncCallbackGetExtraRequiredSize(const ReturnBufferMapAsyncCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnBufferMapAsyncCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnBufferMapAsyncCallbackSerialize(
    const ReturnBufferMapAsyncCallbackCmd& record,
    ReturnBufferMapAsyncCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::BufferMapAsyncCallback;


    transfer->buffer = record.buffer;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;
    transfer->readDataUpdateInfoLength = record.readDataUpdateInfoLength;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnBufferMapAsyncCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnBufferMapAsyncCallbackDeserialize(
    ReturnBufferMapAsyncCallbackCmd* record,
    const volatile ReturnBufferMapAsyncCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::BufferMapAsyncCallback);


    static_assert(sizeof(record->buffer) >= sizeof(transfer->buffer), "Deserialize assignment may not narrow.");
    record->buffer = transfer->buffer;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->status) >= sizeof(transfer->status), "Deserialize assignment may not narrow.");
    record->status = transfer->status;
    static_assert(sizeof(record->readDataUpdateInfoLength) >= sizeof(transfer->readDataUpdateInfoLength), "Deserialize assignment may not narrow.");
    record->readDataUpdateInfoLength = transfer->readDataUpdateInfoLength;
    {
        auto memberLength = record->readDataUpdateInfoLength;
        const volatile uint8_t* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        uint8_t* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->readDataUpdateInfo = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const uint8_t*>(memberBuffer),
           sizeof(uint8_t) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnBufferMapAsyncCallbackDeserialize);

struct ReturnDeviceCreateComputePipelineAsyncCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle device;
    uint64_t requestSerial;
    WGPUCreatePipelineAsyncStatus status;
    uint64_t messageStrlen;
};

static_assert(offsetof(ReturnDeviceCreateComputePipelineAsyncCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnDeviceCreateComputePipelineAsyncCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnDeviceCreateComputePipelineAsyncCallbackGetExtraRequiredSize(const ReturnDeviceCreateComputePipelineAsyncCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceCreateComputePipelineAsyncCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceCreateComputePipelineAsyncCallbackSerialize(
    const ReturnDeviceCreateComputePipelineAsyncCallbackCmd& record,
    ReturnDeviceCreateComputePipelineAsyncCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::DeviceCreateComputePipelineAsyncCallback;


    transfer->device = record.device;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceCreateComputePipelineAsyncCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceCreateComputePipelineAsyncCallbackDeserialize(
    ReturnDeviceCreateComputePipelineAsyncCallbackCmd* record,
    const volatile ReturnDeviceCreateComputePipelineAsyncCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceCreateComputePipelineAsyncCallback);


    static_assert(sizeof(record->device) >= sizeof(transfer->device), "Deserialize assignment may not narrow.");
    record->device = transfer->device;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->status) >= sizeof(transfer->status), "Deserialize assignment may not narrow.");
    record->status = transfer->status;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceCreateComputePipelineAsyncCallbackDeserialize);

struct ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle device;
    uint64_t requestSerial;
    WGPUCreatePipelineAsyncStatus status;
    uint64_t messageStrlen;
};

static_assert(offsetof(ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnDeviceCreateRenderPipelineAsyncCallbackGetExtraRequiredSize(const ReturnDeviceCreateRenderPipelineAsyncCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceCreateRenderPipelineAsyncCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceCreateRenderPipelineAsyncCallbackSerialize(
    const ReturnDeviceCreateRenderPipelineAsyncCallbackCmd& record,
    ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::DeviceCreateRenderPipelineAsyncCallback;


    transfer->device = record.device;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceCreateRenderPipelineAsyncCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceCreateRenderPipelineAsyncCallbackDeserialize(
    ReturnDeviceCreateRenderPipelineAsyncCallbackCmd* record,
    const volatile ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceCreateRenderPipelineAsyncCallback);


    static_assert(sizeof(record->device) >= sizeof(transfer->device), "Deserialize assignment may not narrow.");
    record->device = transfer->device;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->status) >= sizeof(transfer->status), "Deserialize assignment may not narrow.");
    record->status = transfer->status;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceCreateRenderPipelineAsyncCallbackDeserialize);

struct ReturnDeviceLoggingCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle device;
    WGPULoggingType type;
    uint64_t messageStrlen;
};

static_assert(offsetof(ReturnDeviceLoggingCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnDeviceLoggingCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnDeviceLoggingCallbackGetExtraRequiredSize(const ReturnDeviceLoggingCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceLoggingCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceLoggingCallbackSerialize(
    const ReturnDeviceLoggingCallbackCmd& record,
    ReturnDeviceLoggingCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::DeviceLoggingCallback;


    transfer->device = record.device;
    transfer->type = record.type;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceLoggingCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceLoggingCallbackDeserialize(
    ReturnDeviceLoggingCallbackCmd* record,
    const volatile ReturnDeviceLoggingCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceLoggingCallback);


    static_assert(sizeof(record->device) >= sizeof(transfer->device), "Deserialize assignment may not narrow.");
    record->device = transfer->device;
    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceLoggingCallbackDeserialize);

struct ReturnDeviceLostCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle device;
    WGPUDeviceLostReason reason;
    uint64_t messageStrlen;
};

static_assert(offsetof(ReturnDeviceLostCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnDeviceLostCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnDeviceLostCallbackGetExtraRequiredSize(const ReturnDeviceLostCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceLostCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceLostCallbackSerialize(
    const ReturnDeviceLostCallbackCmd& record,
    ReturnDeviceLostCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::DeviceLostCallback;


    transfer->device = record.device;
    transfer->reason = record.reason;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceLostCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceLostCallbackDeserialize(
    ReturnDeviceLostCallbackCmd* record,
    const volatile ReturnDeviceLostCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceLostCallback);


    static_assert(sizeof(record->device) >= sizeof(transfer->device), "Deserialize assignment may not narrow.");
    record->device = transfer->device;
    static_assert(sizeof(record->reason) >= sizeof(transfer->reason), "Deserialize assignment may not narrow.");
    record->reason = transfer->reason;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceLostCallbackDeserialize);

struct ReturnDevicePopErrorScopeCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle device;
    uint64_t requestSerial;
    WGPUErrorType type;
    uint64_t messageStrlen;
};

static_assert(offsetof(ReturnDevicePopErrorScopeCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnDevicePopErrorScopeCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnDevicePopErrorScopeCallbackGetExtraRequiredSize(const ReturnDevicePopErrorScopeCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDevicePopErrorScopeCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnDevicePopErrorScopeCallbackSerialize(
    const ReturnDevicePopErrorScopeCallbackCmd& record,
    ReturnDevicePopErrorScopeCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::DevicePopErrorScopeCallback;


    transfer->device = record.device;
    transfer->requestSerial = record.requestSerial;
    transfer->type = record.type;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDevicePopErrorScopeCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnDevicePopErrorScopeCallbackDeserialize(
    ReturnDevicePopErrorScopeCallbackCmd* record,
    const volatile ReturnDevicePopErrorScopeCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::DevicePopErrorScopeCallback);


    static_assert(sizeof(record->device) >= sizeof(transfer->device), "Deserialize assignment may not narrow.");
    record->device = transfer->device;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDevicePopErrorScopeCallbackDeserialize);

struct ReturnDeviceUncapturedErrorCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle device;
    WGPUErrorType type;
    uint64_t messageStrlen;
};

static_assert(offsetof(ReturnDeviceUncapturedErrorCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnDeviceUncapturedErrorCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnDeviceUncapturedErrorCallbackGetExtraRequiredSize(const ReturnDeviceUncapturedErrorCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    ASSERT(record.message != nullptr);
    result += Align(std::strlen(record.message), kWireBufferAlignment);
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnDeviceUncapturedErrorCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceUncapturedErrorCallbackSerialize(
    const ReturnDeviceUncapturedErrorCallbackCmd& record,
    ReturnDeviceUncapturedErrorCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::DeviceUncapturedErrorCallback;


    transfer->device = record.device;
    transfer->type = record.type;
    {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceUncapturedErrorCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnDeviceUncapturedErrorCallbackDeserialize(
    ReturnDeviceUncapturedErrorCallbackCmd* record,
    const volatile ReturnDeviceUncapturedErrorCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::DeviceUncapturedErrorCallback);


    static_assert(sizeof(record->device) >= sizeof(transfer->device), "Deserialize assignment may not narrow.");
    record->device = transfer->device;
    static_assert(sizeof(record->type) >= sizeof(transfer->type), "Deserialize assignment may not narrow.");
    record->type = transfer->type;
    {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnDeviceUncapturedErrorCallbackDeserialize);

struct ReturnInstanceRequestAdapterCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle instance;
    uint64_t requestSerial;
    WGPURequestAdapterStatus status;
    uint64_t messageStrlen;
    bool has_message;
    bool has_properties;
    bool has_limits;
    uint32_t featuresCount;
};

static_assert(offsetof(ReturnInstanceRequestAdapterCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnInstanceRequestAdapterCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnInstanceRequestAdapterCallbackGetExtraRequiredSize(const ReturnInstanceRequestAdapterCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.message != nullptr) {
        result += Align(std::strlen(record.message), kWireBufferAlignment);
    }
    if (record.properties != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUAdapterPropertiesTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUAdapterPropertiesGetExtraRequiredSize(record.properties[i]);
        }
    }
    if (record.limits != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUSupportedLimitsTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUSupportedLimitsGetExtraRequiredSize(record.limits[i]);
        }
    }
    {
        auto memberLength = record.featuresCount;
        auto size = WireAlignSizeofN<WGPUFeatureName>(memberLength);
        ASSERT(size);
        result += *size;
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnInstanceRequestAdapterCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnInstanceRequestAdapterCallbackSerialize(
    const ReturnInstanceRequestAdapterCallbackCmd& record,
    ReturnInstanceRequestAdapterCallbackTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::InstanceRequestAdapterCallback;


    transfer->instance = record.instance;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;
    transfer->featuresCount = record.featuresCount;
    bool has_message = record.message != nullptr;
    transfer->has_message = has_message;
    if (has_message) {
        transfer->messageStrlen = std::strlen(record.message);

        char* stringInBuffer;
        WIRE_TRY(buffer->NextN(transfer->messageStrlen, &stringInBuffer));
        memcpy(stringInBuffer, record.message, transfer->messageStrlen);
    }
    bool has_properties = record.properties != nullptr;
    transfer->has_properties = has_properties;
    if (has_properties) {
        auto memberLength = 1u;

        WGPUAdapterPropertiesTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUAdapterPropertiesSerialize(record.properties[i], &memberBuffer[i], buffer, provider));
        }
    }
    bool has_limits = record.limits != nullptr;
    transfer->has_limits = has_limits;
    if (has_limits) {
        auto memberLength = 1u;

        WGPUSupportedLimitsTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSupportedLimitsSerialize(record.limits[i], &memberBuffer[i], buffer, provider));
        }
    }
    {
        auto memberLength = record.featuresCount;

        WGPUFeatureName* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        memcpy(
            memberBuffer, record.features,
            sizeof(WGPUFeatureName) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnInstanceRequestAdapterCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnInstanceRequestAdapterCallbackDeserialize(
    ReturnInstanceRequestAdapterCallbackCmd* record,
    const volatile ReturnInstanceRequestAdapterCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::InstanceRequestAdapterCallback);


    static_assert(sizeof(record->instance) >= sizeof(transfer->instance), "Deserialize assignment may not narrow.");
    record->instance = transfer->instance;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->status) >= sizeof(transfer->status), "Deserialize assignment may not narrow.");
    record->status = transfer->status;
    static_assert(sizeof(record->featuresCount) >= sizeof(transfer->featuresCount), "Deserialize assignment may not narrow.");
    record->featuresCount = transfer->featuresCount;
    bool has_message = transfer->has_message;
    record->message = nullptr;
    if (has_message) {
        uint64_t stringLength64 = transfer->messageStrlen;
        if (stringLength64 >= std::numeric_limits<size_t>::max()) {
            return WireResult::FatalError;
        }
        size_t stringLength = static_cast<size_t>(stringLength64);

        const volatile char* stringInBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(stringLength, &stringInBuffer));

        char* copiedString;
        WIRE_TRY(GetSpace(allocator, stringLength + 1, &copiedString));
        memcpy(copiedString, const_cast<const char*>(stringInBuffer), stringLength);
        copiedString[stringLength] = '\0';
        record->message = copiedString;
    }
    bool has_properties = transfer->has_properties;
    record->properties = nullptr;
    if (has_properties) {
        auto memberLength = 1u;
        const volatile WGPUAdapterPropertiesTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUAdapterProperties* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->properties = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUAdapterPropertiesDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    bool has_limits = transfer->has_limits;
    record->limits = nullptr;
    if (has_limits) {
        auto memberLength = 1u;
        const volatile WGPUSupportedLimitsTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUSupportedLimits* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->limits = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUSupportedLimitsDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }
    {
        auto memberLength = record->featuresCount;
        const volatile WGPUFeatureName* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUFeatureName* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->features = copiedMembers;

        memcpy(
            copiedMembers,
            const_cast<const WGPUFeatureName*>(memberBuffer),
           sizeof(WGPUFeatureName) * memberLength);
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnInstanceRequestAdapterCallbackDeserialize);

struct ReturnQueueWorkDoneCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle queue;
    uint64_t requestSerial;
    WGPUQueueWorkDoneStatus status;
};

static_assert(offsetof(ReturnQueueWorkDoneCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnQueueWorkDoneCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnQueueWorkDoneCallbackGetExtraRequiredSize(const ReturnQueueWorkDoneCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnQueueWorkDoneCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnQueueWorkDoneCallbackSerialize(
    const ReturnQueueWorkDoneCallbackCmd& record,
    ReturnQueueWorkDoneCallbackTransfer* transfer,
    SerializeBuffer* buffer) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::QueueWorkDoneCallback;


    transfer->queue = record.queue;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnQueueWorkDoneCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnQueueWorkDoneCallbackDeserialize(
    ReturnQueueWorkDoneCallbackCmd* record,
    const volatile ReturnQueueWorkDoneCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::QueueWorkDoneCallback);


    static_assert(sizeof(record->queue) >= sizeof(transfer->queue), "Deserialize assignment may not narrow.");
    record->queue = transfer->queue;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->status) >= sizeof(transfer->status), "Deserialize assignment may not narrow.");
    record->status = transfer->status;

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnQueueWorkDoneCallbackDeserialize);

struct ReturnShaderModuleGetCompilationInfoCallbackTransfer : CmdHeader {
    static_assert(1 <= 1,
                  "Record must be at most one of is_cmd, extensible, and chained.");
    ReturnWireCmd commandId;

    ObjectHandle shaderModule;
    uint64_t requestSerial;
    WGPUCompilationInfoRequestStatus status;
    bool has_info;
};

static_assert(offsetof(ReturnShaderModuleGetCompilationInfoCallbackTransfer, commandSize) == 0);
static_assert(offsetof(ReturnShaderModuleGetCompilationInfoCallbackTransfer, commandId) == sizeof(CmdHeader));

DAWN_DECLARE_UNUSED size_t ReturnShaderModuleGetCompilationInfoCallbackGetExtraRequiredSize(const ReturnShaderModuleGetCompilationInfoCallbackCmd& record) {
    DAWN_UNUSED(record);
    size_t result = 0;

    if (record.info != nullptr) {
        auto memberLength = 1u;
        auto size = WireAlignSizeofN<WGPUCompilationInfoTransfer>(memberLength);
        ASSERT(size);
        result += *size;
        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            result += WGPUCompilationInfoGetExtraRequiredSize(record.info[i]);
        }
    }
    return result;
}
// GetExtraRequiredSize isn't used for structures that are value members of other structures
// because we assume they cannot contain pointers themselves.
DAWN_UNUSED_FUNC(ReturnShaderModuleGetCompilationInfoCallbackGetExtraRequiredSize);

DAWN_DECLARE_UNUSED WireResult ReturnShaderModuleGetCompilationInfoCallbackSerialize(
    const ReturnShaderModuleGetCompilationInfoCallbackCmd& record,
    ReturnShaderModuleGetCompilationInfoCallbackTransfer* transfer,
    SerializeBuffer* buffer, const ObjectIdProvider& provider) {
    DAWN_UNUSED(buffer);
    transfer->commandId = ReturnWireCmd::ShaderModuleGetCompilationInfoCallback;


    transfer->shaderModule = record.shaderModule;
    transfer->requestSerial = record.requestSerial;
    transfer->status = record.status;
    bool has_info = record.info != nullptr;
    transfer->has_info = has_info;
    if (has_info) {
        auto memberLength = 1u;

        WGPUCompilationInfoTransfer* memberBuffer;
        WIRE_TRY(buffer->NextN(memberLength, &memberBuffer));

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCompilationInfoSerialize(record.info[i], &memberBuffer[i], buffer, provider));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnShaderModuleGetCompilationInfoCallbackSerialize);

DAWN_DECLARE_UNUSED WireResult ReturnShaderModuleGetCompilationInfoCallbackDeserialize(
    ReturnShaderModuleGetCompilationInfoCallbackCmd* record,
    const volatile ReturnShaderModuleGetCompilationInfoCallbackTransfer* transfer,
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator, const ObjectIdResolver& resolver) {
    DAWN_UNUSED(allocator);

    ASSERT(transfer->commandId == ReturnWireCmd::ShaderModuleGetCompilationInfoCallback);


    static_assert(sizeof(record->shaderModule) >= sizeof(transfer->shaderModule), "Deserialize assignment may not narrow.");
    record->shaderModule = transfer->shaderModule;
    static_assert(sizeof(record->requestSerial) >= sizeof(transfer->requestSerial), "Deserialize assignment may not narrow.");
    record->requestSerial = transfer->requestSerial;
    static_assert(sizeof(record->status) >= sizeof(transfer->status), "Deserialize assignment may not narrow.");
    record->status = transfer->status;
    bool has_info = transfer->has_info;
    record->info = nullptr;
    if (has_info) {
        auto memberLength = 1u;
        const volatile WGPUCompilationInfoTransfer* memberBuffer;
        WIRE_TRY(deserializeBuffer->ReadN(memberLength, &memberBuffer));

        WGPUCompilationInfo* copiedMembers;
        WIRE_TRY(GetSpace(allocator, memberLength, &copiedMembers));
        record->info = copiedMembers;

        for (decltype(memberLength) i = 0; i < memberLength; ++i) {
            WIRE_TRY(WGPUCompilationInfoDeserialize(&copiedMembers[i], &memberBuffer[i], deserializeBuffer, allocator, resolver));
        }
    }

    return WireResult::Success;
}
DAWN_UNUSED_FUNC(ReturnShaderModuleGetCompilationInfoCallbackDeserialize);

// Implementation of ObjectIdResolver that always errors.
// Used when the generator adds a provider argument because of a chained
// struct, but in practice, a chained struct in that location is invalid.
class ErrorObjectIdResolver final : public ObjectIdResolver {
    public:
  WireResult GetFromId(ObjectId id, WGPUAdapter* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUAdapter* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUBindGroup* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUBindGroup* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUBindGroupLayout* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUBindGroupLayout* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUBuffer* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUBuffer* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUCommandBuffer* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUCommandBuffer* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUCommandEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUCommandEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUComputePassEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUComputePassEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUComputePipeline* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUComputePipeline* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUDevice* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUDevice* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUExternalTexture* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUExternalTexture* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUInstance* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUInstance* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUPipelineLayout* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUPipelineLayout* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUQuerySet* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUQuerySet* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUQueue* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUQueue* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPURenderBundle* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPURenderBundle* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPURenderBundleEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPURenderBundleEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPURenderPassEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPURenderPassEncoder* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPURenderPipeline* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPURenderPipeline* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUSampler* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUSampler* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUShaderModule* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUShaderModule* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUSurface* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUSurface* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUSwapChain* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUSwapChain* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUTexture* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUTexture* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetFromId(ObjectId id, WGPUTextureView* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalFromId(ObjectId id, WGPUTextureView* out) const override {
      return WireResult::FatalError;
  }
};

// Implementation of ObjectIdProvider that always errors.
// Used when the generator adds a provider argument because of a chained
// struct, but in practice, a chained struct in that location is invalid.
class ErrorObjectIdProvider final : public ObjectIdProvider {
    public:
  WireResult GetId(WGPUAdapter object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUAdapter object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUBindGroup object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUBindGroup object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUBindGroupLayout object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUBindGroupLayout object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUBuffer object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUBuffer object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUCommandBuffer object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUCommandBuffer object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUCommandEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUCommandEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUComputePassEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUComputePassEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUComputePipeline object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUComputePipeline object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUDevice object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUDevice object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUExternalTexture object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUExternalTexture object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUInstance object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUInstance object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUPipelineLayout object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUPipelineLayout object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUQuerySet object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUQuerySet object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUQueue object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUQueue object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPURenderBundle object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPURenderBundle object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPURenderBundleEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPURenderBundleEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPURenderPassEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPURenderPassEncoder object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPURenderPipeline object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPURenderPipeline object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUSampler object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUSampler object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUShaderModule object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUShaderModule object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUSurface object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUSurface object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUSwapChain object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUSwapChain object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUTexture object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUTexture object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetId(WGPUTextureView object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
  WireResult GetOptionalId(WGPUTextureView object, ObjectId* out) const override {
      return WireResult::FatalError;
  }
};

}  // anonymous namespace

size_t AdapterGetInstanceCmd::GetRequiredSize() const {
    return WireAlignSizeof<AdapterGetInstanceTransfer>() + AdapterGetInstanceGetExtraRequiredSize(*this);
}

WireResult AdapterGetInstanceCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    AdapterGetInstanceTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (AdapterGetInstanceSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult AdapterGetInstanceCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult AdapterGetInstanceCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile AdapterGetInstanceTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return AdapterGetInstanceDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult AdapterGetInstanceCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t AdapterRequestDeviceCmd::GetRequiredSize() const {
    return WireAlignSizeof<AdapterRequestDeviceTransfer>() + AdapterRequestDeviceGetExtraRequiredSize(*this);
}

WireResult AdapterRequestDeviceCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    AdapterRequestDeviceTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (AdapterRequestDeviceSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult AdapterRequestDeviceCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult AdapterRequestDeviceCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile AdapterRequestDeviceTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return AdapterRequestDeviceDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult AdapterRequestDeviceCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t BindGroupLayoutSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<BindGroupLayoutSetLabelTransfer>() + BindGroupLayoutSetLabelGetExtraRequiredSize(*this);
}

WireResult BindGroupLayoutSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    BindGroupLayoutSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (BindGroupLayoutSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult BindGroupLayoutSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult BindGroupLayoutSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile BindGroupLayoutSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return BindGroupLayoutSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult BindGroupLayoutSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t BindGroupSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<BindGroupSetLabelTransfer>() + BindGroupSetLabelGetExtraRequiredSize(*this);
}

WireResult BindGroupSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    BindGroupSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (BindGroupSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult BindGroupSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult BindGroupSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile BindGroupSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return BindGroupSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult BindGroupSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t BufferDestroyCmd::GetRequiredSize() const {
    return WireAlignSizeof<BufferDestroyTransfer>() + BufferDestroyGetExtraRequiredSize(*this);
}

WireResult BufferDestroyCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    BufferDestroyTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (BufferDestroySerialize(*this, transfer, serializeBuffer, provider));
}
WireResult BufferDestroyCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult BufferDestroyCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile BufferDestroyTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return BufferDestroyDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult BufferDestroyCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t BufferMapAsyncCmd::GetRequiredSize() const {
    return WireAlignSizeof<BufferMapAsyncTransfer>() + BufferMapAsyncGetExtraRequiredSize(*this);
}

WireResult BufferMapAsyncCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    BufferMapAsyncTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (BufferMapAsyncSerialize(*this, transfer, serializeBuffer));
}
WireResult BufferMapAsyncCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult BufferMapAsyncCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile BufferMapAsyncTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return BufferMapAsyncDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult BufferMapAsyncCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t BufferSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<BufferSetLabelTransfer>() + BufferSetLabelGetExtraRequiredSize(*this);
}

WireResult BufferSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    BufferSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (BufferSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult BufferSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult BufferSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile BufferSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return BufferSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult BufferSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t BufferUnmapCmd::GetRequiredSize() const {
    return WireAlignSizeof<BufferUnmapTransfer>() + BufferUnmapGetExtraRequiredSize(*this);
}

WireResult BufferUnmapCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    BufferUnmapTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (BufferUnmapSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult BufferUnmapCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult BufferUnmapCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile BufferUnmapTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return BufferUnmapDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult BufferUnmapCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t BufferUpdateMappedDataCmd::GetRequiredSize() const {
    return WireAlignSizeof<BufferUpdateMappedDataTransfer>() + BufferUpdateMappedDataGetExtraRequiredSize(*this);
}

WireResult BufferUpdateMappedDataCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    BufferUpdateMappedDataTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (BufferUpdateMappedDataSerialize(*this, transfer, serializeBuffer));
}
WireResult BufferUpdateMappedDataCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult BufferUpdateMappedDataCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile BufferUpdateMappedDataTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return BufferUpdateMappedDataDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult BufferUpdateMappedDataCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t CommandBufferSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandBufferSetLabelTransfer>() + CommandBufferSetLabelGetExtraRequiredSize(*this);
}

WireResult CommandBufferSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandBufferSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandBufferSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandBufferSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandBufferSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandBufferSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandBufferSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandBufferSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderBeginComputePassCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderBeginComputePassTransfer>() + CommandEncoderBeginComputePassGetExtraRequiredSize(*this);
}

WireResult CommandEncoderBeginComputePassCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderBeginComputePassTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderBeginComputePassSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderBeginComputePassCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderBeginComputePassCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderBeginComputePassTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderBeginComputePassDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderBeginComputePassCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderBeginRenderPassCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderBeginRenderPassTransfer>() + CommandEncoderBeginRenderPassGetExtraRequiredSize(*this);
}

WireResult CommandEncoderBeginRenderPassCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderBeginRenderPassTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderBeginRenderPassSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderBeginRenderPassCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderBeginRenderPassCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderBeginRenderPassTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderBeginRenderPassDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderBeginRenderPassCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderClearBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderClearBufferTransfer>() + CommandEncoderClearBufferGetExtraRequiredSize(*this);
}

WireResult CommandEncoderClearBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderClearBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderClearBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderClearBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderClearBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderClearBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderClearBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderClearBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderCopyBufferToBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderCopyBufferToBufferTransfer>() + CommandEncoderCopyBufferToBufferGetExtraRequiredSize(*this);
}

WireResult CommandEncoderCopyBufferToBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderCopyBufferToBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderCopyBufferToBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderCopyBufferToBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderCopyBufferToBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyBufferToBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderCopyBufferToBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderCopyBufferToBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderCopyBufferToTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderCopyBufferToTextureTransfer>() + CommandEncoderCopyBufferToTextureGetExtraRequiredSize(*this);
}

WireResult CommandEncoderCopyBufferToTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderCopyBufferToTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderCopyBufferToTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderCopyBufferToTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderCopyBufferToTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyBufferToTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderCopyBufferToTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderCopyBufferToTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderCopyTextureToBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderCopyTextureToBufferTransfer>() + CommandEncoderCopyTextureToBufferGetExtraRequiredSize(*this);
}

WireResult CommandEncoderCopyTextureToBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderCopyTextureToBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderCopyTextureToBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderCopyTextureToBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderCopyTextureToBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyTextureToBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderCopyTextureToBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderCopyTextureToBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderCopyTextureToTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderCopyTextureToTextureTransfer>() + CommandEncoderCopyTextureToTextureGetExtraRequiredSize(*this);
}

WireResult CommandEncoderCopyTextureToTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderCopyTextureToTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderCopyTextureToTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderCopyTextureToTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderCopyTextureToTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyTextureToTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderCopyTextureToTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderCopyTextureToTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderCopyTextureToTextureInternalCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderCopyTextureToTextureInternalTransfer>() + CommandEncoderCopyTextureToTextureInternalGetExtraRequiredSize(*this);
}

WireResult CommandEncoderCopyTextureToTextureInternalCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderCopyTextureToTextureInternalTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderCopyTextureToTextureInternalSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderCopyTextureToTextureInternalCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderCopyTextureToTextureInternalCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderCopyTextureToTextureInternalTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderCopyTextureToTextureInternalDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderCopyTextureToTextureInternalCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderFinishCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderFinishTransfer>() + CommandEncoderFinishGetExtraRequiredSize(*this);
}

WireResult CommandEncoderFinishCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderFinishTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderFinishSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderFinishCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderFinishCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderFinishTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderFinishDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderFinishCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderInjectValidationErrorCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderInjectValidationErrorTransfer>() + CommandEncoderInjectValidationErrorGetExtraRequiredSize(*this);
}

WireResult CommandEncoderInjectValidationErrorCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderInjectValidationErrorTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderInjectValidationErrorSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderInjectValidationErrorCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderInjectValidationErrorCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderInjectValidationErrorTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderInjectValidationErrorDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderInjectValidationErrorCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderInsertDebugMarkerTransfer>() + CommandEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
}

WireResult CommandEncoderInsertDebugMarkerCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderInsertDebugMarkerSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderInsertDebugMarkerCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderInsertDebugMarkerDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderInsertDebugMarkerCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderPopDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderPopDebugGroupTransfer>() + CommandEncoderPopDebugGroupGetExtraRequiredSize(*this);
}

WireResult CommandEncoderPopDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderPopDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderPopDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderPopDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderPopDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderPopDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderPushDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderPushDebugGroupTransfer>() + CommandEncoderPushDebugGroupGetExtraRequiredSize(*this);
}

WireResult CommandEncoderPushDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderPushDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderPushDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderPushDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderPushDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderPushDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderResolveQuerySetCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderResolveQuerySetTransfer>() + CommandEncoderResolveQuerySetGetExtraRequiredSize(*this);
}

WireResult CommandEncoderResolveQuerySetCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderResolveQuerySetTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderResolveQuerySetSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderResolveQuerySetCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderResolveQuerySetCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderResolveQuerySetTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderResolveQuerySetDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderResolveQuerySetCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderSetLabelTransfer>() + CommandEncoderSetLabelGetExtraRequiredSize(*this);
}

WireResult CommandEncoderSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderWriteBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderWriteBufferTransfer>() + CommandEncoderWriteBufferGetExtraRequiredSize(*this);
}

WireResult CommandEncoderWriteBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderWriteBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderWriteBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderWriteBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderWriteBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderWriteBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderWriteBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderWriteBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t CommandEncoderWriteTimestampCmd::GetRequiredSize() const {
    return WireAlignSizeof<CommandEncoderWriteTimestampTransfer>() + CommandEncoderWriteTimestampGetExtraRequiredSize(*this);
}

WireResult CommandEncoderWriteTimestampCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    CommandEncoderWriteTimestampTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (CommandEncoderWriteTimestampSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult CommandEncoderWriteTimestampCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult CommandEncoderWriteTimestampCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile CommandEncoderWriteTimestampTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return CommandEncoderWriteTimestampDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult CommandEncoderWriteTimestampCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderDispatchWorkgroupsCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderDispatchWorkgroupsTransfer>() + ComputePassEncoderDispatchWorkgroupsGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderDispatchWorkgroupsCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderDispatchWorkgroupsTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderDispatchWorkgroupsSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderDispatchWorkgroupsCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderDispatchWorkgroupsCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderDispatchWorkgroupsTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderDispatchWorkgroupsDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderDispatchWorkgroupsCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderDispatchWorkgroupsIndirectCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderDispatchWorkgroupsIndirectTransfer>() + ComputePassEncoderDispatchWorkgroupsIndirectGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderDispatchWorkgroupsIndirectCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderDispatchWorkgroupsIndirectTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderDispatchWorkgroupsIndirectSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderDispatchWorkgroupsIndirectCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderDispatchWorkgroupsIndirectCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderDispatchWorkgroupsIndirectTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderDispatchWorkgroupsIndirectDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderDispatchWorkgroupsIndirectCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderEndCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderEndTransfer>() + ComputePassEncoderEndGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderEndCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderEndTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderEndSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderEndCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderEndCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderEndTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderEndDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderEndCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderInsertDebugMarkerTransfer>() + ComputePassEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderInsertDebugMarkerCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderInsertDebugMarkerSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderInsertDebugMarkerCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderInsertDebugMarkerDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderInsertDebugMarkerCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderPopDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderPopDebugGroupTransfer>() + ComputePassEncoderPopDebugGroupGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderPopDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderPopDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderPopDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderPopDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderPopDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderPopDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderPushDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderPushDebugGroupTransfer>() + ComputePassEncoderPushDebugGroupGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderPushDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderPushDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderPushDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderPushDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderPushDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderPushDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderSetBindGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderSetBindGroupTransfer>() + ComputePassEncoderSetBindGroupGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderSetBindGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderSetBindGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderSetBindGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderSetBindGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderSetBindGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderSetBindGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderSetBindGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderSetBindGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderSetLabelTransfer>() + ComputePassEncoderSetLabelGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderSetPipelineCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderSetPipelineTransfer>() + ComputePassEncoderSetPipelineGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderSetPipelineCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderSetPipelineTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderSetPipelineSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderSetPipelineCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderSetPipelineCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderSetPipelineTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderSetPipelineDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderSetPipelineCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePassEncoderWriteTimestampCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePassEncoderWriteTimestampTransfer>() + ComputePassEncoderWriteTimestampGetExtraRequiredSize(*this);
}

WireResult ComputePassEncoderWriteTimestampCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePassEncoderWriteTimestampTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePassEncoderWriteTimestampSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePassEncoderWriteTimestampCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePassEncoderWriteTimestampCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePassEncoderWriteTimestampTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePassEncoderWriteTimestampDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePassEncoderWriteTimestampCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePipelineGetBindGroupLayoutCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePipelineGetBindGroupLayoutTransfer>() + ComputePipelineGetBindGroupLayoutGetExtraRequiredSize(*this);
}

WireResult ComputePipelineGetBindGroupLayoutCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePipelineGetBindGroupLayoutTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePipelineGetBindGroupLayoutSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePipelineGetBindGroupLayoutCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePipelineGetBindGroupLayoutCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePipelineGetBindGroupLayoutTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePipelineGetBindGroupLayoutDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePipelineGetBindGroupLayoutCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ComputePipelineSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<ComputePipelineSetLabelTransfer>() + ComputePipelineSetLabelGetExtraRequiredSize(*this);
}

WireResult ComputePipelineSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ComputePipelineSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ComputePipelineSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ComputePipelineSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ComputePipelineSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ComputePipelineSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ComputePipelineSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ComputePipelineSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DestroyObjectCmd::GetRequiredSize() const {
    return WireAlignSizeof<DestroyObjectTransfer>() + DestroyObjectGetExtraRequiredSize(*this);
}

WireResult DestroyObjectCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    DestroyObjectTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DestroyObjectSerialize(*this, transfer, serializeBuffer));
}
WireResult DestroyObjectCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult DestroyObjectCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile DestroyObjectTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DestroyObjectDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult DestroyObjectCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t DeviceCreateBindGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateBindGroupTransfer>() + DeviceCreateBindGroupGetExtraRequiredSize(*this);
}

WireResult DeviceCreateBindGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateBindGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateBindGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateBindGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateBindGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateBindGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateBindGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateBindGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateBindGroupLayoutCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateBindGroupLayoutTransfer>() + DeviceCreateBindGroupLayoutGetExtraRequiredSize(*this);
}

WireResult DeviceCreateBindGroupLayoutCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateBindGroupLayoutTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateBindGroupLayoutSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateBindGroupLayoutCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateBindGroupLayoutCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateBindGroupLayoutTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateBindGroupLayoutDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateBindGroupLayoutCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateBufferTransfer>() + DeviceCreateBufferGetExtraRequiredSize(*this);
}

WireResult DeviceCreateBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateCommandEncoderCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateCommandEncoderTransfer>() + DeviceCreateCommandEncoderGetExtraRequiredSize(*this);
}

WireResult DeviceCreateCommandEncoderCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateCommandEncoderTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateCommandEncoderSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateCommandEncoderCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateCommandEncoderCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateCommandEncoderTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateCommandEncoderDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateCommandEncoderCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateComputePipelineCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateComputePipelineTransfer>() + DeviceCreateComputePipelineGetExtraRequiredSize(*this);
}

WireResult DeviceCreateComputePipelineCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateComputePipelineTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateComputePipelineSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateComputePipelineCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateComputePipelineCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateComputePipelineTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateComputePipelineDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateComputePipelineCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateComputePipelineAsyncCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateComputePipelineAsyncTransfer>() + DeviceCreateComputePipelineAsyncGetExtraRequiredSize(*this);
}

WireResult DeviceCreateComputePipelineAsyncCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateComputePipelineAsyncTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateComputePipelineAsyncSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateComputePipelineAsyncCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateComputePipelineAsyncCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateComputePipelineAsyncTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateComputePipelineAsyncDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateComputePipelineAsyncCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateErrorBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateErrorBufferTransfer>() + DeviceCreateErrorBufferGetExtraRequiredSize(*this);
}

WireResult DeviceCreateErrorBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateErrorBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateErrorBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateErrorBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateErrorBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateErrorBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateErrorBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateErrorBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateErrorExternalTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateErrorExternalTextureTransfer>() + DeviceCreateErrorExternalTextureGetExtraRequiredSize(*this);
}

WireResult DeviceCreateErrorExternalTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateErrorExternalTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateErrorExternalTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateErrorExternalTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateErrorExternalTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateErrorExternalTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateErrorExternalTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateErrorExternalTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateErrorShaderModuleCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateErrorShaderModuleTransfer>() + DeviceCreateErrorShaderModuleGetExtraRequiredSize(*this);
}

WireResult DeviceCreateErrorShaderModuleCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateErrorShaderModuleTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateErrorShaderModuleSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateErrorShaderModuleCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateErrorShaderModuleCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateErrorShaderModuleTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateErrorShaderModuleDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateErrorShaderModuleCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateErrorTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateErrorTextureTransfer>() + DeviceCreateErrorTextureGetExtraRequiredSize(*this);
}

WireResult DeviceCreateErrorTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateErrorTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateErrorTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateErrorTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateErrorTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateErrorTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateErrorTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateErrorTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateExternalTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateExternalTextureTransfer>() + DeviceCreateExternalTextureGetExtraRequiredSize(*this);
}

WireResult DeviceCreateExternalTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateExternalTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateExternalTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateExternalTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateExternalTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateExternalTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateExternalTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateExternalTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreatePipelineLayoutCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreatePipelineLayoutTransfer>() + DeviceCreatePipelineLayoutGetExtraRequiredSize(*this);
}

WireResult DeviceCreatePipelineLayoutCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreatePipelineLayoutTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreatePipelineLayoutSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreatePipelineLayoutCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreatePipelineLayoutCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreatePipelineLayoutTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreatePipelineLayoutDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreatePipelineLayoutCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateQuerySetCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateQuerySetTransfer>() + DeviceCreateQuerySetGetExtraRequiredSize(*this);
}

WireResult DeviceCreateQuerySetCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateQuerySetTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateQuerySetSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateQuerySetCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateQuerySetCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateQuerySetTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateQuerySetDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateQuerySetCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateRenderBundleEncoderCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateRenderBundleEncoderTransfer>() + DeviceCreateRenderBundleEncoderGetExtraRequiredSize(*this);
}

WireResult DeviceCreateRenderBundleEncoderCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateRenderBundleEncoderTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateRenderBundleEncoderSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateRenderBundleEncoderCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateRenderBundleEncoderCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateRenderBundleEncoderTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateRenderBundleEncoderDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateRenderBundleEncoderCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateRenderPipelineCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateRenderPipelineTransfer>() + DeviceCreateRenderPipelineGetExtraRequiredSize(*this);
}

WireResult DeviceCreateRenderPipelineCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateRenderPipelineTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateRenderPipelineSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateRenderPipelineCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateRenderPipelineCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateRenderPipelineTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateRenderPipelineDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateRenderPipelineCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateRenderPipelineAsyncCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateRenderPipelineAsyncTransfer>() + DeviceCreateRenderPipelineAsyncGetExtraRequiredSize(*this);
}

WireResult DeviceCreateRenderPipelineAsyncCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateRenderPipelineAsyncTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateRenderPipelineAsyncSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateRenderPipelineAsyncCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateRenderPipelineAsyncCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateRenderPipelineAsyncTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateRenderPipelineAsyncDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateRenderPipelineAsyncCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateSamplerCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateSamplerTransfer>() + DeviceCreateSamplerGetExtraRequiredSize(*this);
}

WireResult DeviceCreateSamplerCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateSamplerTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateSamplerSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateSamplerCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateSamplerCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateSamplerTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateSamplerDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateSamplerCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateShaderModuleCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateShaderModuleTransfer>() + DeviceCreateShaderModuleGetExtraRequiredSize(*this);
}

WireResult DeviceCreateShaderModuleCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateShaderModuleTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateShaderModuleSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateShaderModuleCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateShaderModuleCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateShaderModuleTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateShaderModuleDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateShaderModuleCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateSwapChainCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateSwapChainTransfer>() + DeviceCreateSwapChainGetExtraRequiredSize(*this);
}

WireResult DeviceCreateSwapChainCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateSwapChainTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateSwapChainSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateSwapChainCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateSwapChainCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateSwapChainTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateSwapChainDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateSwapChainCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceCreateTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceCreateTextureTransfer>() + DeviceCreateTextureGetExtraRequiredSize(*this);
}

WireResult DeviceCreateTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceCreateTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceCreateTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceCreateTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceCreateTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceCreateTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceCreateTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceCreateTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceDestroyCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceDestroyTransfer>() + DeviceDestroyGetExtraRequiredSize(*this);
}

WireResult DeviceDestroyCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceDestroyTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceDestroySerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceDestroyCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceDestroyCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceDestroyTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceDestroyDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceDestroyCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceForceLossCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceForceLossTransfer>() + DeviceForceLossGetExtraRequiredSize(*this);
}

WireResult DeviceForceLossCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceForceLossTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceForceLossSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceForceLossCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceForceLossCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceForceLossTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceForceLossDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceForceLossCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceGetAdapterCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceGetAdapterTransfer>() + DeviceGetAdapterGetExtraRequiredSize(*this);
}

WireResult DeviceGetAdapterCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceGetAdapterTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceGetAdapterSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceGetAdapterCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceGetAdapterCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceGetAdapterTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceGetAdapterDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceGetAdapterCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceGetQueueCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceGetQueueTransfer>() + DeviceGetQueueGetExtraRequiredSize(*this);
}

WireResult DeviceGetQueueCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceGetQueueTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceGetQueueSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceGetQueueCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceGetQueueCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceGetQueueTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceGetQueueDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceGetQueueCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceInjectErrorCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceInjectErrorTransfer>() + DeviceInjectErrorGetExtraRequiredSize(*this);
}

WireResult DeviceInjectErrorCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceInjectErrorTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceInjectErrorSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceInjectErrorCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceInjectErrorCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceInjectErrorTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceInjectErrorDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceInjectErrorCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DevicePopErrorScopeCmd::GetRequiredSize() const {
    return WireAlignSizeof<DevicePopErrorScopeTransfer>() + DevicePopErrorScopeGetExtraRequiredSize(*this);
}

WireResult DevicePopErrorScopeCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    DevicePopErrorScopeTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DevicePopErrorScopeSerialize(*this, transfer, serializeBuffer));
}
WireResult DevicePopErrorScopeCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult DevicePopErrorScopeCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile DevicePopErrorScopeTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DevicePopErrorScopeDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult DevicePopErrorScopeCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t DevicePushErrorScopeCmd::GetRequiredSize() const {
    return WireAlignSizeof<DevicePushErrorScopeTransfer>() + DevicePushErrorScopeGetExtraRequiredSize(*this);
}

WireResult DevicePushErrorScopeCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DevicePushErrorScopeTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DevicePushErrorScopeSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DevicePushErrorScopeCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DevicePushErrorScopeCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DevicePushErrorScopeTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DevicePushErrorScopeDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DevicePushErrorScopeCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceSetLabelTransfer>() + DeviceSetLabelGetExtraRequiredSize(*this);
}

WireResult DeviceSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceTickCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceTickTransfer>() + DeviceTickGetExtraRequiredSize(*this);
}

WireResult DeviceTickCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceTickTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceTickSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceTickCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceTickCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceTickTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceTickDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceTickCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t DeviceValidateTextureDescriptorCmd::GetRequiredSize() const {
    return WireAlignSizeof<DeviceValidateTextureDescriptorTransfer>() + DeviceValidateTextureDescriptorGetExtraRequiredSize(*this);
}

WireResult DeviceValidateTextureDescriptorCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    DeviceValidateTextureDescriptorTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (DeviceValidateTextureDescriptorSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult DeviceValidateTextureDescriptorCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult DeviceValidateTextureDescriptorCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile DeviceValidateTextureDescriptorTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return DeviceValidateTextureDescriptorDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult DeviceValidateTextureDescriptorCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ExternalTextureDestroyCmd::GetRequiredSize() const {
    return WireAlignSizeof<ExternalTextureDestroyTransfer>() + ExternalTextureDestroyGetExtraRequiredSize(*this);
}

WireResult ExternalTextureDestroyCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ExternalTextureDestroyTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ExternalTextureDestroySerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ExternalTextureDestroyCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ExternalTextureDestroyCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ExternalTextureDestroyTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ExternalTextureDestroyDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ExternalTextureDestroyCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ExternalTextureExpireCmd::GetRequiredSize() const {
    return WireAlignSizeof<ExternalTextureExpireTransfer>() + ExternalTextureExpireGetExtraRequiredSize(*this);
}

WireResult ExternalTextureExpireCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ExternalTextureExpireTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ExternalTextureExpireSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ExternalTextureExpireCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ExternalTextureExpireCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ExternalTextureExpireTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ExternalTextureExpireDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ExternalTextureExpireCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ExternalTextureRefreshCmd::GetRequiredSize() const {
    return WireAlignSizeof<ExternalTextureRefreshTransfer>() + ExternalTextureRefreshGetExtraRequiredSize(*this);
}

WireResult ExternalTextureRefreshCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ExternalTextureRefreshTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ExternalTextureRefreshSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ExternalTextureRefreshCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ExternalTextureRefreshCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ExternalTextureRefreshTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ExternalTextureRefreshDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ExternalTextureRefreshCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ExternalTextureSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<ExternalTextureSetLabelTransfer>() + ExternalTextureSetLabelGetExtraRequiredSize(*this);
}

WireResult ExternalTextureSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ExternalTextureSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ExternalTextureSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ExternalTextureSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ExternalTextureSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ExternalTextureSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ExternalTextureSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ExternalTextureSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t InstanceCreateSurfaceCmd::GetRequiredSize() const {
    return WireAlignSizeof<InstanceCreateSurfaceTransfer>() + InstanceCreateSurfaceGetExtraRequiredSize(*this);
}

WireResult InstanceCreateSurfaceCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    InstanceCreateSurfaceTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (InstanceCreateSurfaceSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult InstanceCreateSurfaceCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult InstanceCreateSurfaceCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile InstanceCreateSurfaceTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return InstanceCreateSurfaceDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult InstanceCreateSurfaceCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t InstanceProcessEventsCmd::GetRequiredSize() const {
    return WireAlignSizeof<InstanceProcessEventsTransfer>() + InstanceProcessEventsGetExtraRequiredSize(*this);
}

WireResult InstanceProcessEventsCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    InstanceProcessEventsTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (InstanceProcessEventsSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult InstanceProcessEventsCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult InstanceProcessEventsCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile InstanceProcessEventsTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return InstanceProcessEventsDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult InstanceProcessEventsCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t InstanceRequestAdapterCmd::GetRequiredSize() const {
    return WireAlignSizeof<InstanceRequestAdapterTransfer>() + InstanceRequestAdapterGetExtraRequiredSize(*this);
}

WireResult InstanceRequestAdapterCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    InstanceRequestAdapterTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (InstanceRequestAdapterSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult InstanceRequestAdapterCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult InstanceRequestAdapterCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile InstanceRequestAdapterTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return InstanceRequestAdapterDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult InstanceRequestAdapterCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t PipelineLayoutSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<PipelineLayoutSetLabelTransfer>() + PipelineLayoutSetLabelGetExtraRequiredSize(*this);
}

WireResult PipelineLayoutSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    PipelineLayoutSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (PipelineLayoutSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult PipelineLayoutSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult PipelineLayoutSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile PipelineLayoutSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return PipelineLayoutSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult PipelineLayoutSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t QuerySetDestroyCmd::GetRequiredSize() const {
    return WireAlignSizeof<QuerySetDestroyTransfer>() + QuerySetDestroyGetExtraRequiredSize(*this);
}

WireResult QuerySetDestroyCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    QuerySetDestroyTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QuerySetDestroySerialize(*this, transfer, serializeBuffer, provider));
}
WireResult QuerySetDestroyCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult QuerySetDestroyCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile QuerySetDestroyTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QuerySetDestroyDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult QuerySetDestroyCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t QuerySetSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<QuerySetSetLabelTransfer>() + QuerySetSetLabelGetExtraRequiredSize(*this);
}

WireResult QuerySetSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    QuerySetSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QuerySetSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult QuerySetSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult QuerySetSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile QuerySetSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QuerySetSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult QuerySetSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t QueueCopyExternalTextureForBrowserCmd::GetRequiredSize() const {
    return WireAlignSizeof<QueueCopyExternalTextureForBrowserTransfer>() + QueueCopyExternalTextureForBrowserGetExtraRequiredSize(*this);
}

WireResult QueueCopyExternalTextureForBrowserCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    QueueCopyExternalTextureForBrowserTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QueueCopyExternalTextureForBrowserSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult QueueCopyExternalTextureForBrowserCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult QueueCopyExternalTextureForBrowserCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile QueueCopyExternalTextureForBrowserTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QueueCopyExternalTextureForBrowserDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult QueueCopyExternalTextureForBrowserCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t QueueCopyTextureForBrowserCmd::GetRequiredSize() const {
    return WireAlignSizeof<QueueCopyTextureForBrowserTransfer>() + QueueCopyTextureForBrowserGetExtraRequiredSize(*this);
}

WireResult QueueCopyTextureForBrowserCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    QueueCopyTextureForBrowserTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QueueCopyTextureForBrowserSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult QueueCopyTextureForBrowserCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult QueueCopyTextureForBrowserCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile QueueCopyTextureForBrowserTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QueueCopyTextureForBrowserDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult QueueCopyTextureForBrowserCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t QueueOnSubmittedWorkDoneCmd::GetRequiredSize() const {
    return WireAlignSizeof<QueueOnSubmittedWorkDoneTransfer>() + QueueOnSubmittedWorkDoneGetExtraRequiredSize(*this);
}

WireResult QueueOnSubmittedWorkDoneCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    QueueOnSubmittedWorkDoneTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QueueOnSubmittedWorkDoneSerialize(*this, transfer, serializeBuffer));
}
WireResult QueueOnSubmittedWorkDoneCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult QueueOnSubmittedWorkDoneCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile QueueOnSubmittedWorkDoneTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QueueOnSubmittedWorkDoneDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult QueueOnSubmittedWorkDoneCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t QueueSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<QueueSetLabelTransfer>() + QueueSetLabelGetExtraRequiredSize(*this);
}

WireResult QueueSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    QueueSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QueueSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult QueueSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult QueueSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile QueueSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QueueSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult QueueSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t QueueSubmitCmd::GetRequiredSize() const {
    return WireAlignSizeof<QueueSubmitTransfer>() + QueueSubmitGetExtraRequiredSize(*this);
}

WireResult QueueSubmitCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    QueueSubmitTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QueueSubmitSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult QueueSubmitCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult QueueSubmitCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile QueueSubmitTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QueueSubmitDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult QueueSubmitCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t QueueWriteBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<QueueWriteBufferTransfer>() + QueueWriteBufferGetExtraRequiredSize(*this);
}

WireResult QueueWriteBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    QueueWriteBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QueueWriteBufferSerialize(*this, transfer, serializeBuffer));
}
WireResult QueueWriteBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult QueueWriteBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile QueueWriteBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QueueWriteBufferDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult QueueWriteBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t QueueWriteTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<QueueWriteTextureTransfer>() + QueueWriteTextureGetExtraRequiredSize(*this);
}

WireResult QueueWriteTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    QueueWriteTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (QueueWriteTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult QueueWriteTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult QueueWriteTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile QueueWriteTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return QueueWriteTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult QueueWriteTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderDrawCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderDrawTransfer>() + RenderBundleEncoderDrawGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderDrawCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderDrawTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderDrawSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderDrawCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderDrawCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderDrawDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderDrawCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderDrawIndexedCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderDrawIndexedTransfer>() + RenderBundleEncoderDrawIndexedGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderDrawIndexedCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderDrawIndexedTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderDrawIndexedSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderDrawIndexedCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderDrawIndexedCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawIndexedTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderDrawIndexedDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderDrawIndexedCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderDrawIndexedIndirectCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderDrawIndexedIndirectTransfer>() + RenderBundleEncoderDrawIndexedIndirectGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderDrawIndexedIndirectCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderDrawIndexedIndirectTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderDrawIndexedIndirectSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderDrawIndexedIndirectCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderDrawIndexedIndirectCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawIndexedIndirectTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderDrawIndexedIndirectDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderDrawIndexedIndirectCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderDrawIndirectCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderDrawIndirectTransfer>() + RenderBundleEncoderDrawIndirectGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderDrawIndirectCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderDrawIndirectTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderDrawIndirectSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderDrawIndirectCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderDrawIndirectCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderDrawIndirectTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderDrawIndirectDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderDrawIndirectCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderFinishCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderFinishTransfer>() + RenderBundleEncoderFinishGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderFinishCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderFinishTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderFinishSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderFinishCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderFinishCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderFinishTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderFinishDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderFinishCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderInsertDebugMarkerTransfer>() + RenderBundleEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderInsertDebugMarkerCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderInsertDebugMarkerSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderInsertDebugMarkerCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderInsertDebugMarkerDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderInsertDebugMarkerCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderPopDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderPopDebugGroupTransfer>() + RenderBundleEncoderPopDebugGroupGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderPopDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderPopDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderPopDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderPopDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderPopDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderPopDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderPushDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderPushDebugGroupTransfer>() + RenderBundleEncoderPushDebugGroupGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderPushDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderPushDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderPushDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderPushDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderPushDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderPushDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderSetBindGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderSetBindGroupTransfer>() + RenderBundleEncoderSetBindGroupGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderSetBindGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderSetBindGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderSetBindGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderSetBindGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderSetBindGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetBindGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderSetBindGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderSetBindGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderSetIndexBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderSetIndexBufferTransfer>() + RenderBundleEncoderSetIndexBufferGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderSetIndexBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderSetIndexBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderSetIndexBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderSetIndexBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderSetIndexBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetIndexBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderSetIndexBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderSetIndexBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderSetLabelTransfer>() + RenderBundleEncoderSetLabelGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderSetPipelineCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderSetPipelineTransfer>() + RenderBundleEncoderSetPipelineGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderSetPipelineCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderSetPipelineTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderSetPipelineSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderSetPipelineCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderSetPipelineCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetPipelineTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderSetPipelineDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderSetPipelineCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleEncoderSetVertexBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleEncoderSetVertexBufferTransfer>() + RenderBundleEncoderSetVertexBufferGetExtraRequiredSize(*this);
}

WireResult RenderBundleEncoderSetVertexBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleEncoderSetVertexBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleEncoderSetVertexBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleEncoderSetVertexBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleEncoderSetVertexBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleEncoderSetVertexBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleEncoderSetVertexBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleEncoderSetVertexBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderBundleSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderBundleSetLabelTransfer>() + RenderBundleSetLabelGetExtraRequiredSize(*this);
}

WireResult RenderBundleSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderBundleSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderBundleSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderBundleSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderBundleSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderBundleSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderBundleSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderBundleSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderBeginOcclusionQueryCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderBeginOcclusionQueryTransfer>() + RenderPassEncoderBeginOcclusionQueryGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderBeginOcclusionQueryCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderBeginOcclusionQueryTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderBeginOcclusionQuerySerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderBeginOcclusionQueryCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderBeginOcclusionQueryCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderBeginOcclusionQueryTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderBeginOcclusionQueryDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderBeginOcclusionQueryCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderDrawCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderDrawTransfer>() + RenderPassEncoderDrawGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderDrawCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderDrawTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderDrawSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderDrawCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderDrawCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderDrawDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderDrawCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderDrawIndexedCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderDrawIndexedTransfer>() + RenderPassEncoderDrawIndexedGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderDrawIndexedCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderDrawIndexedTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderDrawIndexedSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderDrawIndexedCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderDrawIndexedCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawIndexedTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderDrawIndexedDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderDrawIndexedCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderDrawIndexedIndirectCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderDrawIndexedIndirectTransfer>() + RenderPassEncoderDrawIndexedIndirectGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderDrawIndexedIndirectCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderDrawIndexedIndirectTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderDrawIndexedIndirectSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderDrawIndexedIndirectCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderDrawIndexedIndirectCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawIndexedIndirectTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderDrawIndexedIndirectDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderDrawIndexedIndirectCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderDrawIndirectCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderDrawIndirectTransfer>() + RenderPassEncoderDrawIndirectGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderDrawIndirectCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderDrawIndirectTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderDrawIndirectSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderDrawIndirectCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderDrawIndirectCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderDrawIndirectTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderDrawIndirectDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderDrawIndirectCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderEndCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderEndTransfer>() + RenderPassEncoderEndGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderEndCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderEndTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderEndSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderEndCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderEndCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderEndTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderEndDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderEndCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderEndOcclusionQueryCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderEndOcclusionQueryTransfer>() + RenderPassEncoderEndOcclusionQueryGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderEndOcclusionQueryCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderEndOcclusionQueryTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderEndOcclusionQuerySerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderEndOcclusionQueryCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderEndOcclusionQueryCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderEndOcclusionQueryTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderEndOcclusionQueryDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderEndOcclusionQueryCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderExecuteBundlesCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderExecuteBundlesTransfer>() + RenderPassEncoderExecuteBundlesGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderExecuteBundlesCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderExecuteBundlesTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderExecuteBundlesSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderExecuteBundlesCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderExecuteBundlesCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderExecuteBundlesTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderExecuteBundlesDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderExecuteBundlesCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderInsertDebugMarkerCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderInsertDebugMarkerTransfer>() + RenderPassEncoderInsertDebugMarkerGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderInsertDebugMarkerCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderInsertDebugMarkerSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderInsertDebugMarkerCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderInsertDebugMarkerCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderInsertDebugMarkerTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderInsertDebugMarkerDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderInsertDebugMarkerCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderPopDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderPopDebugGroupTransfer>() + RenderPassEncoderPopDebugGroupGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderPopDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderPopDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderPopDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderPopDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderPopDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderPopDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderPopDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderPushDebugGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderPushDebugGroupTransfer>() + RenderPassEncoderPushDebugGroupGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderPushDebugGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderPushDebugGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderPushDebugGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderPushDebugGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderPushDebugGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderPushDebugGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderPushDebugGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetBindGroupCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetBindGroupTransfer>() + RenderPassEncoderSetBindGroupGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetBindGroupCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetBindGroupTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetBindGroupSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetBindGroupCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetBindGroupCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetBindGroupTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetBindGroupDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetBindGroupCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetBlendConstantCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetBlendConstantTransfer>() + RenderPassEncoderSetBlendConstantGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetBlendConstantCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetBlendConstantTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetBlendConstantSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetBlendConstantCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetBlendConstantCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetBlendConstantTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetBlendConstantDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetBlendConstantCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetIndexBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetIndexBufferTransfer>() + RenderPassEncoderSetIndexBufferGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetIndexBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetIndexBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetIndexBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetIndexBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetIndexBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetIndexBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetIndexBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetIndexBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetLabelTransfer>() + RenderPassEncoderSetLabelGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetPipelineCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetPipelineTransfer>() + RenderPassEncoderSetPipelineGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetPipelineCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetPipelineTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetPipelineSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetPipelineCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetPipelineCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetPipelineTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetPipelineDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetPipelineCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetScissorRectCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetScissorRectTransfer>() + RenderPassEncoderSetScissorRectGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetScissorRectCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetScissorRectTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetScissorRectSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetScissorRectCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetScissorRectCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetScissorRectTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetScissorRectDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetScissorRectCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetStencilReferenceCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetStencilReferenceTransfer>() + RenderPassEncoderSetStencilReferenceGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetStencilReferenceCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetStencilReferenceTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetStencilReferenceSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetStencilReferenceCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetStencilReferenceCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetStencilReferenceTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetStencilReferenceDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetStencilReferenceCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetVertexBufferCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetVertexBufferTransfer>() + RenderPassEncoderSetVertexBufferGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetVertexBufferCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetVertexBufferTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetVertexBufferSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetVertexBufferCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetVertexBufferCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetVertexBufferTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetVertexBufferDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetVertexBufferCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderSetViewportCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderSetViewportTransfer>() + RenderPassEncoderSetViewportGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderSetViewportCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderSetViewportTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderSetViewportSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderSetViewportCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderSetViewportCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderSetViewportTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderSetViewportDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderSetViewportCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPassEncoderWriteTimestampCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPassEncoderWriteTimestampTransfer>() + RenderPassEncoderWriteTimestampGetExtraRequiredSize(*this);
}

WireResult RenderPassEncoderWriteTimestampCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPassEncoderWriteTimestampTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPassEncoderWriteTimestampSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPassEncoderWriteTimestampCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPassEncoderWriteTimestampCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPassEncoderWriteTimestampTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPassEncoderWriteTimestampDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPassEncoderWriteTimestampCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPipelineGetBindGroupLayoutCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPipelineGetBindGroupLayoutTransfer>() + RenderPipelineGetBindGroupLayoutGetExtraRequiredSize(*this);
}

WireResult RenderPipelineGetBindGroupLayoutCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPipelineGetBindGroupLayoutTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPipelineGetBindGroupLayoutSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPipelineGetBindGroupLayoutCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPipelineGetBindGroupLayoutCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPipelineGetBindGroupLayoutTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPipelineGetBindGroupLayoutDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPipelineGetBindGroupLayoutCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t RenderPipelineSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<RenderPipelineSetLabelTransfer>() + RenderPipelineSetLabelGetExtraRequiredSize(*this);
}

WireResult RenderPipelineSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    RenderPipelineSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (RenderPipelineSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult RenderPipelineSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult RenderPipelineSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile RenderPipelineSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return RenderPipelineSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult RenderPipelineSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t SamplerSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<SamplerSetLabelTransfer>() + SamplerSetLabelGetExtraRequiredSize(*this);
}

WireResult SamplerSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    SamplerSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (SamplerSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult SamplerSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult SamplerSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile SamplerSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return SamplerSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult SamplerSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ShaderModuleGetCompilationInfoCmd::GetRequiredSize() const {
    return WireAlignSizeof<ShaderModuleGetCompilationInfoTransfer>() + ShaderModuleGetCompilationInfoGetExtraRequiredSize(*this);
}

WireResult ShaderModuleGetCompilationInfoCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ShaderModuleGetCompilationInfoTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ShaderModuleGetCompilationInfoSerialize(*this, transfer, serializeBuffer));
}
WireResult ShaderModuleGetCompilationInfoCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ShaderModuleGetCompilationInfoCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ShaderModuleGetCompilationInfoTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ShaderModuleGetCompilationInfoDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ShaderModuleGetCompilationInfoCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ShaderModuleSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<ShaderModuleSetLabelTransfer>() + ShaderModuleSetLabelGetExtraRequiredSize(*this);
}

WireResult ShaderModuleSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ShaderModuleSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ShaderModuleSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ShaderModuleSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ShaderModuleSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ShaderModuleSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ShaderModuleSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ShaderModuleSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t SwapChainGetCurrentTextureCmd::GetRequiredSize() const {
    return WireAlignSizeof<SwapChainGetCurrentTextureTransfer>() + SwapChainGetCurrentTextureGetExtraRequiredSize(*this);
}

WireResult SwapChainGetCurrentTextureCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    SwapChainGetCurrentTextureTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (SwapChainGetCurrentTextureSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult SwapChainGetCurrentTextureCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult SwapChainGetCurrentTextureCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile SwapChainGetCurrentTextureTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return SwapChainGetCurrentTextureDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult SwapChainGetCurrentTextureCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t SwapChainGetCurrentTextureViewCmd::GetRequiredSize() const {
    return WireAlignSizeof<SwapChainGetCurrentTextureViewTransfer>() + SwapChainGetCurrentTextureViewGetExtraRequiredSize(*this);
}

WireResult SwapChainGetCurrentTextureViewCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    SwapChainGetCurrentTextureViewTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (SwapChainGetCurrentTextureViewSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult SwapChainGetCurrentTextureViewCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult SwapChainGetCurrentTextureViewCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile SwapChainGetCurrentTextureViewTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return SwapChainGetCurrentTextureViewDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult SwapChainGetCurrentTextureViewCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t SwapChainPresentCmd::GetRequiredSize() const {
    return WireAlignSizeof<SwapChainPresentTransfer>() + SwapChainPresentGetExtraRequiredSize(*this);
}

WireResult SwapChainPresentCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    SwapChainPresentTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (SwapChainPresentSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult SwapChainPresentCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult SwapChainPresentCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile SwapChainPresentTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return SwapChainPresentDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult SwapChainPresentCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t TextureCreateViewCmd::GetRequiredSize() const {
    return WireAlignSizeof<TextureCreateViewTransfer>() + TextureCreateViewGetExtraRequiredSize(*this);
}

WireResult TextureCreateViewCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    TextureCreateViewTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (TextureCreateViewSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult TextureCreateViewCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult TextureCreateViewCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile TextureCreateViewTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return TextureCreateViewDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult TextureCreateViewCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t TextureDestroyCmd::GetRequiredSize() const {
    return WireAlignSizeof<TextureDestroyTransfer>() + TextureDestroyGetExtraRequiredSize(*this);
}

WireResult TextureDestroyCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    TextureDestroyTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (TextureDestroySerialize(*this, transfer, serializeBuffer, provider));
}
WireResult TextureDestroyCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult TextureDestroyCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile TextureDestroyTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return TextureDestroyDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult TextureDestroyCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t TextureSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<TextureSetLabelTransfer>() + TextureSetLabelGetExtraRequiredSize(*this);
}

WireResult TextureSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    TextureSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (TextureSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult TextureSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult TextureSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile TextureSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return TextureSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult TextureSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t TextureViewSetLabelCmd::GetRequiredSize() const {
    return WireAlignSizeof<TextureViewSetLabelTransfer>() + TextureViewSetLabelGetExtraRequiredSize(*this);
}

WireResult TextureViewSetLabelCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    TextureViewSetLabelTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (TextureViewSetLabelSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult TextureViewSetLabelCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult TextureViewSetLabelCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile TextureViewSetLabelTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return TextureViewSetLabelDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult TextureViewSetLabelCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}


size_t ReturnAdapterRequestDeviceCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnAdapterRequestDeviceCallbackTransfer>() + ReturnAdapterRequestDeviceCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnAdapterRequestDeviceCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ReturnAdapterRequestDeviceCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnAdapterRequestDeviceCallbackSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ReturnAdapterRequestDeviceCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ReturnAdapterRequestDeviceCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ReturnAdapterRequestDeviceCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnAdapterRequestDeviceCallbackDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ReturnAdapterRequestDeviceCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ReturnBufferMapAsyncCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnBufferMapAsyncCallbackTransfer>() + ReturnBufferMapAsyncCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnBufferMapAsyncCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnBufferMapAsyncCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnBufferMapAsyncCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnBufferMapAsyncCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnBufferMapAsyncCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnBufferMapAsyncCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnBufferMapAsyncCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnBufferMapAsyncCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnDeviceCreateComputePipelineAsyncCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnDeviceCreateComputePipelineAsyncCallbackTransfer>() + ReturnDeviceCreateComputePipelineAsyncCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnDeviceCreateComputePipelineAsyncCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnDeviceCreateComputePipelineAsyncCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnDeviceCreateComputePipelineAsyncCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnDeviceCreateComputePipelineAsyncCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnDeviceCreateComputePipelineAsyncCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceCreateComputePipelineAsyncCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnDeviceCreateComputePipelineAsyncCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnDeviceCreateComputePipelineAsyncCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnDeviceCreateRenderPipelineAsyncCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer>() + ReturnDeviceCreateRenderPipelineAsyncCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnDeviceCreateRenderPipelineAsyncCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnDeviceCreateRenderPipelineAsyncCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnDeviceCreateRenderPipelineAsyncCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnDeviceCreateRenderPipelineAsyncCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceCreateRenderPipelineAsyncCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnDeviceCreateRenderPipelineAsyncCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnDeviceCreateRenderPipelineAsyncCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnDeviceLoggingCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnDeviceLoggingCallbackTransfer>() + ReturnDeviceLoggingCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnDeviceLoggingCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnDeviceLoggingCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnDeviceLoggingCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnDeviceLoggingCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnDeviceLoggingCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceLoggingCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnDeviceLoggingCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnDeviceLoggingCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnDeviceLostCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnDeviceLostCallbackTransfer>() + ReturnDeviceLostCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnDeviceLostCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnDeviceLostCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnDeviceLostCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnDeviceLostCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnDeviceLostCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceLostCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnDeviceLostCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnDeviceLostCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnDevicePopErrorScopeCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnDevicePopErrorScopeCallbackTransfer>() + ReturnDevicePopErrorScopeCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnDevicePopErrorScopeCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnDevicePopErrorScopeCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnDevicePopErrorScopeCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnDevicePopErrorScopeCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnDevicePopErrorScopeCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnDevicePopErrorScopeCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnDevicePopErrorScopeCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnDevicePopErrorScopeCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnDeviceUncapturedErrorCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnDeviceUncapturedErrorCallbackTransfer>() + ReturnDeviceUncapturedErrorCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnDeviceUncapturedErrorCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnDeviceUncapturedErrorCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnDeviceUncapturedErrorCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnDeviceUncapturedErrorCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnDeviceUncapturedErrorCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnDeviceUncapturedErrorCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnDeviceUncapturedErrorCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnDeviceUncapturedErrorCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnInstanceRequestAdapterCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnInstanceRequestAdapterCallbackTransfer>() + ReturnInstanceRequestAdapterCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnInstanceRequestAdapterCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ReturnInstanceRequestAdapterCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnInstanceRequestAdapterCallbackSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ReturnInstanceRequestAdapterCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ReturnInstanceRequestAdapterCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ReturnInstanceRequestAdapterCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnInstanceRequestAdapterCallbackDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ReturnInstanceRequestAdapterCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}

size_t ReturnQueueWorkDoneCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnQueueWorkDoneCallbackTransfer>() + ReturnQueueWorkDoneCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnQueueWorkDoneCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ReturnQueueWorkDoneCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnQueueWorkDoneCallbackSerialize(*this, transfer, serializeBuffer));
}
WireResult ReturnQueueWorkDoneCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider&) const {
    return Serialize(commandSize, serializeBuffer);
}

WireResult ReturnQueueWorkDoneCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    const volatile ReturnQueueWorkDoneCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnQueueWorkDoneCallbackDeserialize(this, transfer, deserializeBuffer, allocator);
}
WireResult ReturnQueueWorkDoneCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver&) {
    return Deserialize(deserializeBuffer, allocator);
}

size_t ReturnShaderModuleGetCompilationInfoCallbackCmd::GetRequiredSize() const {
    return WireAlignSizeof<ReturnShaderModuleGetCompilationInfoCallbackTransfer>() + ReturnShaderModuleGetCompilationInfoCallbackGetExtraRequiredSize(*this);
}

WireResult ReturnShaderModuleGetCompilationInfoCallbackCmd::Serialize(
    size_t commandSize,
    SerializeBuffer* serializeBuffer,
    const ObjectIdProvider& provider) const {
    ReturnShaderModuleGetCompilationInfoCallbackTransfer* transfer;
    WIRE_TRY(serializeBuffer->Next(&transfer));
    transfer->commandSize = commandSize;
    return (ReturnShaderModuleGetCompilationInfoCallbackSerialize(*this, transfer, serializeBuffer, provider));
}
WireResult ReturnShaderModuleGetCompilationInfoCallbackCmd::Serialize(size_t commandSize, SerializeBuffer* serializeBuffer) const {
    ErrorObjectIdProvider provider;
    return Serialize(commandSize, serializeBuffer, provider);
}

WireResult ReturnShaderModuleGetCompilationInfoCallbackCmd::Deserialize(
    DeserializeBuffer* deserializeBuffer,
    DeserializeAllocator* allocator,
    const ObjectIdResolver& resolver) {
    const volatile ReturnShaderModuleGetCompilationInfoCallbackTransfer* transfer;
    WIRE_TRY(deserializeBuffer->Read(&transfer));
    return ReturnShaderModuleGetCompilationInfoCallbackDeserialize(this, transfer, deserializeBuffer, allocator, resolver);
}
WireResult ReturnShaderModuleGetCompilationInfoCallbackCmd::Deserialize(DeserializeBuffer* deserializeBuffer, DeserializeAllocator* allocator) {
    ErrorObjectIdResolver resolver;
    return Deserialize(deserializeBuffer, allocator, resolver);
}


}  // namespace dawn::wire
