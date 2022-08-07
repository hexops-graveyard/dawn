
#include "dawn/native/wgpu_structs_autogen.h"

#include <tuple>

#ifdef __GNUC__
// error: 'offsetof' within non-standard-layout type 'wgpu::XXX' is conditionally-supported
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

namespace dawn::native {

    static_assert(sizeof(ChainedStruct) == sizeof(WGPUChainedStruct),
            "sizeof mismatch for ChainedStruct");
    static_assert(alignof(ChainedStruct) == alignof(WGPUChainedStruct),
            "alignof mismatch for ChainedStruct");
    static_assert(offsetof(ChainedStruct, nextInChain) == offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ChainedStruct::nextInChain");
    static_assert(offsetof(ChainedStruct, sType) == offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ChainedStruct::sType");


    static_assert(sizeof(AdapterProperties) == sizeof(WGPUAdapterProperties), "sizeof mismatch for AdapterProperties");
    static_assert(alignof(AdapterProperties) == alignof(WGPUAdapterProperties), "alignof mismatch for AdapterProperties");

    static_assert(offsetof(AdapterProperties, nextInChain) == offsetof(WGPUAdapterProperties, nextInChain),
            "offsetof mismatch for AdapterProperties::nextInChain");
    static_assert(offsetof(AdapterProperties, vendorID) == offsetof(WGPUAdapterProperties, vendorID),
            "offsetof mismatch for AdapterProperties::vendorID");
    static_assert(offsetof(AdapterProperties, vendorName) == offsetof(WGPUAdapterProperties, vendorName),
            "offsetof mismatch for AdapterProperties::vendorName");
    static_assert(offsetof(AdapterProperties, architecture) == offsetof(WGPUAdapterProperties, architecture),
            "offsetof mismatch for AdapterProperties::architecture");
    static_assert(offsetof(AdapterProperties, deviceID) == offsetof(WGPUAdapterProperties, deviceID),
            "offsetof mismatch for AdapterProperties::deviceID");
    static_assert(offsetof(AdapterProperties, name) == offsetof(WGPUAdapterProperties, name),
            "offsetof mismatch for AdapterProperties::name");
    static_assert(offsetof(AdapterProperties, driverDescription) == offsetof(WGPUAdapterProperties, driverDescription),
            "offsetof mismatch for AdapterProperties::driverDescription");
    static_assert(offsetof(AdapterProperties, adapterType) == offsetof(WGPUAdapterProperties, adapterType),
            "offsetof mismatch for AdapterProperties::adapterType");
    static_assert(offsetof(AdapterProperties, backendType) == offsetof(WGPUAdapterProperties, backendType),
            "offsetof mismatch for AdapterProperties::backendType");

    bool AdapterProperties::operator==(const AdapterProperties& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            vendorID,
            vendorName,
            architecture,
            deviceID,
            name,
            driverDescription,
            adapterType,
            backendType
        ) == std::tie(
            rhs.vendorID,
            rhs.vendorName,
            rhs.architecture,
            rhs.deviceID,
            rhs.name,
            rhs.driverDescription,
            rhs.adapterType,
            rhs.backendType
        );
    }


    static_assert(sizeof(BindGroupEntry) == sizeof(WGPUBindGroupEntry), "sizeof mismatch for BindGroupEntry");
    static_assert(alignof(BindGroupEntry) == alignof(WGPUBindGroupEntry), "alignof mismatch for BindGroupEntry");

    static_assert(offsetof(BindGroupEntry, nextInChain) == offsetof(WGPUBindGroupEntry, nextInChain),
            "offsetof mismatch for BindGroupEntry::nextInChain");
    static_assert(offsetof(BindGroupEntry, binding) == offsetof(WGPUBindGroupEntry, binding),
            "offsetof mismatch for BindGroupEntry::binding");
    static_assert(offsetof(BindGroupEntry, buffer) == offsetof(WGPUBindGroupEntry, buffer),
            "offsetof mismatch for BindGroupEntry::buffer");
    static_assert(offsetof(BindGroupEntry, offset) == offsetof(WGPUBindGroupEntry, offset),
            "offsetof mismatch for BindGroupEntry::offset");
    static_assert(offsetof(BindGroupEntry, size) == offsetof(WGPUBindGroupEntry, size),
            "offsetof mismatch for BindGroupEntry::size");
    static_assert(offsetof(BindGroupEntry, sampler) == offsetof(WGPUBindGroupEntry, sampler),
            "offsetof mismatch for BindGroupEntry::sampler");
    static_assert(offsetof(BindGroupEntry, textureView) == offsetof(WGPUBindGroupEntry, textureView),
            "offsetof mismatch for BindGroupEntry::textureView");

    bool BindGroupEntry::operator==(const BindGroupEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            binding,
            buffer,
            offset,
            size,
            sampler,
            textureView
        ) == std::tie(
            rhs.binding,
            rhs.buffer,
            rhs.offset,
            rhs.size,
            rhs.sampler,
            rhs.textureView
        );
    }


    static_assert(sizeof(BlendComponent) == sizeof(WGPUBlendComponent), "sizeof mismatch for BlendComponent");
    static_assert(alignof(BlendComponent) == alignof(WGPUBlendComponent), "alignof mismatch for BlendComponent");

    static_assert(offsetof(BlendComponent, operation) == offsetof(WGPUBlendComponent, operation),
            "offsetof mismatch for BlendComponent::operation");
    static_assert(offsetof(BlendComponent, srcFactor) == offsetof(WGPUBlendComponent, srcFactor),
            "offsetof mismatch for BlendComponent::srcFactor");
    static_assert(offsetof(BlendComponent, dstFactor) == offsetof(WGPUBlendComponent, dstFactor),
            "offsetof mismatch for BlendComponent::dstFactor");

    bool BlendComponent::operator==(const BlendComponent& rhs) const {
        return  std::tie(
            operation,
            srcFactor,
            dstFactor
        ) == std::tie(
            rhs.operation,
            rhs.srcFactor,
            rhs.dstFactor
        );
    }


    static_assert(sizeof(BufferBindingLayout) == sizeof(WGPUBufferBindingLayout), "sizeof mismatch for BufferBindingLayout");
    static_assert(alignof(BufferBindingLayout) == alignof(WGPUBufferBindingLayout), "alignof mismatch for BufferBindingLayout");

    static_assert(offsetof(BufferBindingLayout, nextInChain) == offsetof(WGPUBufferBindingLayout, nextInChain),
            "offsetof mismatch for BufferBindingLayout::nextInChain");
    static_assert(offsetof(BufferBindingLayout, type) == offsetof(WGPUBufferBindingLayout, type),
            "offsetof mismatch for BufferBindingLayout::type");
    static_assert(offsetof(BufferBindingLayout, hasDynamicOffset) == offsetof(WGPUBufferBindingLayout, hasDynamicOffset),
            "offsetof mismatch for BufferBindingLayout::hasDynamicOffset");
    static_assert(offsetof(BufferBindingLayout, minBindingSize) == offsetof(WGPUBufferBindingLayout, minBindingSize),
            "offsetof mismatch for BufferBindingLayout::minBindingSize");

    bool BufferBindingLayout::operator==(const BufferBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            type,
            hasDynamicOffset,
            minBindingSize
        ) == std::tie(
            rhs.type,
            rhs.hasDynamicOffset,
            rhs.minBindingSize
        );
    }


    static_assert(sizeof(BufferDescriptor) == sizeof(WGPUBufferDescriptor), "sizeof mismatch for BufferDescriptor");
    static_assert(alignof(BufferDescriptor) == alignof(WGPUBufferDescriptor), "alignof mismatch for BufferDescriptor");

    static_assert(offsetof(BufferDescriptor, nextInChain) == offsetof(WGPUBufferDescriptor, nextInChain),
            "offsetof mismatch for BufferDescriptor::nextInChain");
    static_assert(offsetof(BufferDescriptor, label) == offsetof(WGPUBufferDescriptor, label),
            "offsetof mismatch for BufferDescriptor::label");
    static_assert(offsetof(BufferDescriptor, usage) == offsetof(WGPUBufferDescriptor, usage),
            "offsetof mismatch for BufferDescriptor::usage");
    static_assert(offsetof(BufferDescriptor, size) == offsetof(WGPUBufferDescriptor, size),
            "offsetof mismatch for BufferDescriptor::size");
    static_assert(offsetof(BufferDescriptor, mappedAtCreation) == offsetof(WGPUBufferDescriptor, mappedAtCreation),
            "offsetof mismatch for BufferDescriptor::mappedAtCreation");

    bool BufferDescriptor::operator==(const BufferDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            usage,
            size,
            mappedAtCreation
        ) == std::tie(
            rhs.label,
            rhs.usage,
            rhs.size,
            rhs.mappedAtCreation
        );
    }


    static_assert(sizeof(Color) == sizeof(WGPUColor), "sizeof mismatch for Color");
    static_assert(alignof(Color) == alignof(WGPUColor), "alignof mismatch for Color");

    static_assert(offsetof(Color, r) == offsetof(WGPUColor, r),
            "offsetof mismatch for Color::r");
    static_assert(offsetof(Color, g) == offsetof(WGPUColor, g),
            "offsetof mismatch for Color::g");
    static_assert(offsetof(Color, b) == offsetof(WGPUColor, b),
            "offsetof mismatch for Color::b");
    static_assert(offsetof(Color, a) == offsetof(WGPUColor, a),
            "offsetof mismatch for Color::a");

    bool Color::operator==(const Color& rhs) const {
        return  std::tie(
            r,
            g,
            b,
            a
        ) == std::tie(
            rhs.r,
            rhs.g,
            rhs.b,
            rhs.a
        );
    }


    static_assert(sizeof(CommandBufferDescriptor) == sizeof(WGPUCommandBufferDescriptor), "sizeof mismatch for CommandBufferDescriptor");
    static_assert(alignof(CommandBufferDescriptor) == alignof(WGPUCommandBufferDescriptor), "alignof mismatch for CommandBufferDescriptor");

    static_assert(offsetof(CommandBufferDescriptor, nextInChain) == offsetof(WGPUCommandBufferDescriptor, nextInChain),
            "offsetof mismatch for CommandBufferDescriptor::nextInChain");
    static_assert(offsetof(CommandBufferDescriptor, label) == offsetof(WGPUCommandBufferDescriptor, label),
            "offsetof mismatch for CommandBufferDescriptor::label");

    bool CommandBufferDescriptor::operator==(const CommandBufferDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(CommandEncoderDescriptor) == sizeof(WGPUCommandEncoderDescriptor), "sizeof mismatch for CommandEncoderDescriptor");
    static_assert(alignof(CommandEncoderDescriptor) == alignof(WGPUCommandEncoderDescriptor), "alignof mismatch for CommandEncoderDescriptor");

    static_assert(offsetof(CommandEncoderDescriptor, nextInChain) == offsetof(WGPUCommandEncoderDescriptor, nextInChain),
            "offsetof mismatch for CommandEncoderDescriptor::nextInChain");
    static_assert(offsetof(CommandEncoderDescriptor, label) == offsetof(WGPUCommandEncoderDescriptor, label),
            "offsetof mismatch for CommandEncoderDescriptor::label");

    bool CommandEncoderDescriptor::operator==(const CommandEncoderDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(CompilationMessage) == sizeof(WGPUCompilationMessage), "sizeof mismatch for CompilationMessage");
    static_assert(alignof(CompilationMessage) == alignof(WGPUCompilationMessage), "alignof mismatch for CompilationMessage");

    static_assert(offsetof(CompilationMessage, nextInChain) == offsetof(WGPUCompilationMessage, nextInChain),
            "offsetof mismatch for CompilationMessage::nextInChain");
    static_assert(offsetof(CompilationMessage, message) == offsetof(WGPUCompilationMessage, message),
            "offsetof mismatch for CompilationMessage::message");
    static_assert(offsetof(CompilationMessage, type) == offsetof(WGPUCompilationMessage, type),
            "offsetof mismatch for CompilationMessage::type");
    static_assert(offsetof(CompilationMessage, lineNum) == offsetof(WGPUCompilationMessage, lineNum),
            "offsetof mismatch for CompilationMessage::lineNum");
    static_assert(offsetof(CompilationMessage, linePos) == offsetof(WGPUCompilationMessage, linePos),
            "offsetof mismatch for CompilationMessage::linePos");
    static_assert(offsetof(CompilationMessage, offset) == offsetof(WGPUCompilationMessage, offset),
            "offsetof mismatch for CompilationMessage::offset");
    static_assert(offsetof(CompilationMessage, length) == offsetof(WGPUCompilationMessage, length),
            "offsetof mismatch for CompilationMessage::length");

    bool CompilationMessage::operator==(const CompilationMessage& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            message,
            type,
            lineNum,
            linePos,
            offset,
            length
        ) == std::tie(
            rhs.message,
            rhs.type,
            rhs.lineNum,
            rhs.linePos,
            rhs.offset,
            rhs.length
        );
    }


    static_assert(sizeof(ComputePassTimestampWrite) == sizeof(WGPUComputePassTimestampWrite), "sizeof mismatch for ComputePassTimestampWrite");
    static_assert(alignof(ComputePassTimestampWrite) == alignof(WGPUComputePassTimestampWrite), "alignof mismatch for ComputePassTimestampWrite");

    static_assert(offsetof(ComputePassTimestampWrite, querySet) == offsetof(WGPUComputePassTimestampWrite, querySet),
            "offsetof mismatch for ComputePassTimestampWrite::querySet");
    static_assert(offsetof(ComputePassTimestampWrite, queryIndex) == offsetof(WGPUComputePassTimestampWrite, queryIndex),
            "offsetof mismatch for ComputePassTimestampWrite::queryIndex");
    static_assert(offsetof(ComputePassTimestampWrite, location) == offsetof(WGPUComputePassTimestampWrite, location),
            "offsetof mismatch for ComputePassTimestampWrite::location");

    bool ComputePassTimestampWrite::operator==(const ComputePassTimestampWrite& rhs) const {
        return  std::tie(
            querySet,
            queryIndex,
            location
        ) == std::tie(
            rhs.querySet,
            rhs.queryIndex,
            rhs.location
        );
    }


    static_assert(sizeof(ConstantEntry) == sizeof(WGPUConstantEntry), "sizeof mismatch for ConstantEntry");
    static_assert(alignof(ConstantEntry) == alignof(WGPUConstantEntry), "alignof mismatch for ConstantEntry");

    static_assert(offsetof(ConstantEntry, nextInChain) == offsetof(WGPUConstantEntry, nextInChain),
            "offsetof mismatch for ConstantEntry::nextInChain");
    static_assert(offsetof(ConstantEntry, key) == offsetof(WGPUConstantEntry, key),
            "offsetof mismatch for ConstantEntry::key");
    static_assert(offsetof(ConstantEntry, value) == offsetof(WGPUConstantEntry, value),
            "offsetof mismatch for ConstantEntry::value");

    bool ConstantEntry::operator==(const ConstantEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            key,
            value
        ) == std::tie(
            rhs.key,
            rhs.value
        );
    }


    static_assert(sizeof(CopyTextureForBrowserOptions) == sizeof(WGPUCopyTextureForBrowserOptions), "sizeof mismatch for CopyTextureForBrowserOptions");
    static_assert(alignof(CopyTextureForBrowserOptions) == alignof(WGPUCopyTextureForBrowserOptions), "alignof mismatch for CopyTextureForBrowserOptions");

    static_assert(offsetof(CopyTextureForBrowserOptions, nextInChain) == offsetof(WGPUCopyTextureForBrowserOptions, nextInChain),
            "offsetof mismatch for CopyTextureForBrowserOptions::nextInChain");
    static_assert(offsetof(CopyTextureForBrowserOptions, flipY) == offsetof(WGPUCopyTextureForBrowserOptions, flipY),
            "offsetof mismatch for CopyTextureForBrowserOptions::flipY");
    static_assert(offsetof(CopyTextureForBrowserOptions, needsColorSpaceConversion) == offsetof(WGPUCopyTextureForBrowserOptions, needsColorSpaceConversion),
            "offsetof mismatch for CopyTextureForBrowserOptions::needsColorSpaceConversion");
    static_assert(offsetof(CopyTextureForBrowserOptions, srcAlphaMode) == offsetof(WGPUCopyTextureForBrowserOptions, srcAlphaMode),
            "offsetof mismatch for CopyTextureForBrowserOptions::srcAlphaMode");
    static_assert(offsetof(CopyTextureForBrowserOptions, srcTransferFunctionParameters) == offsetof(WGPUCopyTextureForBrowserOptions, srcTransferFunctionParameters),
            "offsetof mismatch for CopyTextureForBrowserOptions::srcTransferFunctionParameters");
    static_assert(offsetof(CopyTextureForBrowserOptions, conversionMatrix) == offsetof(WGPUCopyTextureForBrowserOptions, conversionMatrix),
            "offsetof mismatch for CopyTextureForBrowserOptions::conversionMatrix");
    static_assert(offsetof(CopyTextureForBrowserOptions, dstTransferFunctionParameters) == offsetof(WGPUCopyTextureForBrowserOptions, dstTransferFunctionParameters),
            "offsetof mismatch for CopyTextureForBrowserOptions::dstTransferFunctionParameters");
    static_assert(offsetof(CopyTextureForBrowserOptions, dstAlphaMode) == offsetof(WGPUCopyTextureForBrowserOptions, dstAlphaMode),
            "offsetof mismatch for CopyTextureForBrowserOptions::dstAlphaMode");
    static_assert(offsetof(CopyTextureForBrowserOptions, internalUsage) == offsetof(WGPUCopyTextureForBrowserOptions, internalUsage),
            "offsetof mismatch for CopyTextureForBrowserOptions::internalUsage");

    bool CopyTextureForBrowserOptions::operator==(const CopyTextureForBrowserOptions& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            flipY,
            needsColorSpaceConversion,
            srcAlphaMode,
            srcTransferFunctionParameters,
            conversionMatrix,
            dstTransferFunctionParameters,
            dstAlphaMode,
            internalUsage
        ) == std::tie(
            rhs.flipY,
            rhs.needsColorSpaceConversion,
            rhs.srcAlphaMode,
            rhs.srcTransferFunctionParameters,
            rhs.conversionMatrix,
            rhs.dstTransferFunctionParameters,
            rhs.dstAlphaMode,
            rhs.internalUsage
        );
    }


    static_assert(sizeof(DawnCacheDeviceDescriptor) == sizeof(WGPUDawnCacheDeviceDescriptor), "sizeof mismatch for DawnCacheDeviceDescriptor");
    static_assert(alignof(DawnCacheDeviceDescriptor) == alignof(WGPUDawnCacheDeviceDescriptor), "alignof mismatch for DawnCacheDeviceDescriptor");

    static_assert(offsetof(DawnCacheDeviceDescriptor, isolationKey) == offsetof(WGPUDawnCacheDeviceDescriptor, isolationKey),
            "offsetof mismatch for DawnCacheDeviceDescriptor::isolationKey");

    bool DawnCacheDeviceDescriptor::operator==(const DawnCacheDeviceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            isolationKey
        ) == std::tie(
            rhs.isolationKey
        );
    }


    static_assert(sizeof(DawnEncoderInternalUsageDescriptor) == sizeof(WGPUDawnEncoderInternalUsageDescriptor), "sizeof mismatch for DawnEncoderInternalUsageDescriptor");
    static_assert(alignof(DawnEncoderInternalUsageDescriptor) == alignof(WGPUDawnEncoderInternalUsageDescriptor), "alignof mismatch for DawnEncoderInternalUsageDescriptor");

    static_assert(offsetof(DawnEncoderInternalUsageDescriptor, useInternalUsages) == offsetof(WGPUDawnEncoderInternalUsageDescriptor, useInternalUsages),
            "offsetof mismatch for DawnEncoderInternalUsageDescriptor::useInternalUsages");

    bool DawnEncoderInternalUsageDescriptor::operator==(const DawnEncoderInternalUsageDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            useInternalUsages
        ) == std::tie(
            rhs.useInternalUsages
        );
    }


    static_assert(sizeof(DawnInstanceDescriptor) == sizeof(WGPUDawnInstanceDescriptor), "sizeof mismatch for DawnInstanceDescriptor");
    static_assert(alignof(DawnInstanceDescriptor) == alignof(WGPUDawnInstanceDescriptor), "alignof mismatch for DawnInstanceDescriptor");

    static_assert(offsetof(DawnInstanceDescriptor, additionalRuntimeSearchPathsCount) == offsetof(WGPUDawnInstanceDescriptor, additionalRuntimeSearchPathsCount),
            "offsetof mismatch for DawnInstanceDescriptor::additionalRuntimeSearchPathsCount");
    static_assert(offsetof(DawnInstanceDescriptor, additionalRuntimeSearchPaths) == offsetof(WGPUDawnInstanceDescriptor, additionalRuntimeSearchPaths),
            "offsetof mismatch for DawnInstanceDescriptor::additionalRuntimeSearchPaths");

    bool DawnInstanceDescriptor::operator==(const DawnInstanceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            additionalRuntimeSearchPathsCount,
            additionalRuntimeSearchPaths
        ) == std::tie(
            rhs.additionalRuntimeSearchPathsCount,
            rhs.additionalRuntimeSearchPaths
        );
    }


    static_assert(sizeof(DawnTextureInternalUsageDescriptor) == sizeof(WGPUDawnTextureInternalUsageDescriptor), "sizeof mismatch for DawnTextureInternalUsageDescriptor");
    static_assert(alignof(DawnTextureInternalUsageDescriptor) == alignof(WGPUDawnTextureInternalUsageDescriptor), "alignof mismatch for DawnTextureInternalUsageDescriptor");

    static_assert(offsetof(DawnTextureInternalUsageDescriptor, internalUsage) == offsetof(WGPUDawnTextureInternalUsageDescriptor, internalUsage),
            "offsetof mismatch for DawnTextureInternalUsageDescriptor::internalUsage");

    bool DawnTextureInternalUsageDescriptor::operator==(const DawnTextureInternalUsageDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            internalUsage
        ) == std::tie(
            rhs.internalUsage
        );
    }


    static_assert(sizeof(DawnTogglesDeviceDescriptor) == sizeof(WGPUDawnTogglesDeviceDescriptor), "sizeof mismatch for DawnTogglesDeviceDescriptor");
    static_assert(alignof(DawnTogglesDeviceDescriptor) == alignof(WGPUDawnTogglesDeviceDescriptor), "alignof mismatch for DawnTogglesDeviceDescriptor");

    static_assert(offsetof(DawnTogglesDeviceDescriptor, forceEnabledTogglesCount) == offsetof(WGPUDawnTogglesDeviceDescriptor, forceEnabledTogglesCount),
            "offsetof mismatch for DawnTogglesDeviceDescriptor::forceEnabledTogglesCount");
    static_assert(offsetof(DawnTogglesDeviceDescriptor, forceEnabledToggles) == offsetof(WGPUDawnTogglesDeviceDescriptor, forceEnabledToggles),
            "offsetof mismatch for DawnTogglesDeviceDescriptor::forceEnabledToggles");
    static_assert(offsetof(DawnTogglesDeviceDescriptor, forceDisabledTogglesCount) == offsetof(WGPUDawnTogglesDeviceDescriptor, forceDisabledTogglesCount),
            "offsetof mismatch for DawnTogglesDeviceDescriptor::forceDisabledTogglesCount");
    static_assert(offsetof(DawnTogglesDeviceDescriptor, forceDisabledToggles) == offsetof(WGPUDawnTogglesDeviceDescriptor, forceDisabledToggles),
            "offsetof mismatch for DawnTogglesDeviceDescriptor::forceDisabledToggles");

    bool DawnTogglesDeviceDescriptor::operator==(const DawnTogglesDeviceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            forceEnabledTogglesCount,
            forceEnabledToggles,
            forceDisabledTogglesCount,
            forceDisabledToggles
        ) == std::tie(
            rhs.forceEnabledTogglesCount,
            rhs.forceEnabledToggles,
            rhs.forceDisabledTogglesCount,
            rhs.forceDisabledToggles
        );
    }


    static_assert(sizeof(Extent3D) == sizeof(WGPUExtent3D), "sizeof mismatch for Extent3D");
    static_assert(alignof(Extent3D) == alignof(WGPUExtent3D), "alignof mismatch for Extent3D");

    static_assert(offsetof(Extent3D, width) == offsetof(WGPUExtent3D, width),
            "offsetof mismatch for Extent3D::width");
    static_assert(offsetof(Extent3D, height) == offsetof(WGPUExtent3D, height),
            "offsetof mismatch for Extent3D::height");
    static_assert(offsetof(Extent3D, depthOrArrayLayers) == offsetof(WGPUExtent3D, depthOrArrayLayers),
            "offsetof mismatch for Extent3D::depthOrArrayLayers");

    bool Extent3D::operator==(const Extent3D& rhs) const {
        return  std::tie(
            width,
            height,
            depthOrArrayLayers
        ) == std::tie(
            rhs.width,
            rhs.height,
            rhs.depthOrArrayLayers
        );
    }


    static_assert(sizeof(ExternalTextureBindingEntry) == sizeof(WGPUExternalTextureBindingEntry), "sizeof mismatch for ExternalTextureBindingEntry");
    static_assert(alignof(ExternalTextureBindingEntry) == alignof(WGPUExternalTextureBindingEntry), "alignof mismatch for ExternalTextureBindingEntry");

    static_assert(offsetof(ExternalTextureBindingEntry, externalTexture) == offsetof(WGPUExternalTextureBindingEntry, externalTexture),
            "offsetof mismatch for ExternalTextureBindingEntry::externalTexture");

    bool ExternalTextureBindingEntry::operator==(const ExternalTextureBindingEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            externalTexture
        ) == std::tie(
            rhs.externalTexture
        );
    }


    static_assert(sizeof(ExternalTextureBindingLayout) == sizeof(WGPUExternalTextureBindingLayout), "sizeof mismatch for ExternalTextureBindingLayout");
    static_assert(alignof(ExternalTextureBindingLayout) == alignof(WGPUExternalTextureBindingLayout), "alignof mismatch for ExternalTextureBindingLayout");


    bool ExternalTextureBindingLayout::operator==(const ExternalTextureBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
        ) == std::tie(
        );
    }


    static_assert(sizeof(ExternalTextureDescriptor) == sizeof(WGPUExternalTextureDescriptor), "sizeof mismatch for ExternalTextureDescriptor");
    static_assert(alignof(ExternalTextureDescriptor) == alignof(WGPUExternalTextureDescriptor), "alignof mismatch for ExternalTextureDescriptor");

    static_assert(offsetof(ExternalTextureDescriptor, nextInChain) == offsetof(WGPUExternalTextureDescriptor, nextInChain),
            "offsetof mismatch for ExternalTextureDescriptor::nextInChain");
    static_assert(offsetof(ExternalTextureDescriptor, label) == offsetof(WGPUExternalTextureDescriptor, label),
            "offsetof mismatch for ExternalTextureDescriptor::label");
    static_assert(offsetof(ExternalTextureDescriptor, plane0) == offsetof(WGPUExternalTextureDescriptor, plane0),
            "offsetof mismatch for ExternalTextureDescriptor::plane0");
    static_assert(offsetof(ExternalTextureDescriptor, plane1) == offsetof(WGPUExternalTextureDescriptor, plane1),
            "offsetof mismatch for ExternalTextureDescriptor::plane1");
    static_assert(offsetof(ExternalTextureDescriptor, doYuvToRgbConversionOnly) == offsetof(WGPUExternalTextureDescriptor, doYuvToRgbConversionOnly),
            "offsetof mismatch for ExternalTextureDescriptor::doYuvToRgbConversionOnly");
    static_assert(offsetof(ExternalTextureDescriptor, yuvToRgbConversionMatrix) == offsetof(WGPUExternalTextureDescriptor, yuvToRgbConversionMatrix),
            "offsetof mismatch for ExternalTextureDescriptor::yuvToRgbConversionMatrix");
    static_assert(offsetof(ExternalTextureDescriptor, srcTransferFunctionParameters) == offsetof(WGPUExternalTextureDescriptor, srcTransferFunctionParameters),
            "offsetof mismatch for ExternalTextureDescriptor::srcTransferFunctionParameters");
    static_assert(offsetof(ExternalTextureDescriptor, dstTransferFunctionParameters) == offsetof(WGPUExternalTextureDescriptor, dstTransferFunctionParameters),
            "offsetof mismatch for ExternalTextureDescriptor::dstTransferFunctionParameters");
    static_assert(offsetof(ExternalTextureDescriptor, gamutConversionMatrix) == offsetof(WGPUExternalTextureDescriptor, gamutConversionMatrix),
            "offsetof mismatch for ExternalTextureDescriptor::gamutConversionMatrix");

    bool ExternalTextureDescriptor::operator==(const ExternalTextureDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            plane0,
            plane1,
            doYuvToRgbConversionOnly,
            yuvToRgbConversionMatrix,
            srcTransferFunctionParameters,
            dstTransferFunctionParameters,
            gamutConversionMatrix
        ) == std::tie(
            rhs.label,
            rhs.plane0,
            rhs.plane1,
            rhs.doYuvToRgbConversionOnly,
            rhs.yuvToRgbConversionMatrix,
            rhs.srcTransferFunctionParameters,
            rhs.dstTransferFunctionParameters,
            rhs.gamutConversionMatrix
        );
    }


    static_assert(sizeof(InstanceDescriptor) == sizeof(WGPUInstanceDescriptor), "sizeof mismatch for InstanceDescriptor");
    static_assert(alignof(InstanceDescriptor) == alignof(WGPUInstanceDescriptor), "alignof mismatch for InstanceDescriptor");

    static_assert(offsetof(InstanceDescriptor, nextInChain) == offsetof(WGPUInstanceDescriptor, nextInChain),
            "offsetof mismatch for InstanceDescriptor::nextInChain");

    bool InstanceDescriptor::operator==(const InstanceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
        ) == std::tie(
        );
    }


    static_assert(sizeof(Limits) == sizeof(WGPULimits), "sizeof mismatch for Limits");
    static_assert(alignof(Limits) == alignof(WGPULimits), "alignof mismatch for Limits");

    static_assert(offsetof(Limits, maxTextureDimension1D) == offsetof(WGPULimits, maxTextureDimension1D),
            "offsetof mismatch for Limits::maxTextureDimension1D");
    static_assert(offsetof(Limits, maxTextureDimension2D) == offsetof(WGPULimits, maxTextureDimension2D),
            "offsetof mismatch for Limits::maxTextureDimension2D");
    static_assert(offsetof(Limits, maxTextureDimension3D) == offsetof(WGPULimits, maxTextureDimension3D),
            "offsetof mismatch for Limits::maxTextureDimension3D");
    static_assert(offsetof(Limits, maxTextureArrayLayers) == offsetof(WGPULimits, maxTextureArrayLayers),
            "offsetof mismatch for Limits::maxTextureArrayLayers");
    static_assert(offsetof(Limits, maxBindGroups) == offsetof(WGPULimits, maxBindGroups),
            "offsetof mismatch for Limits::maxBindGroups");
    static_assert(offsetof(Limits, maxDynamicUniformBuffersPerPipelineLayout) == offsetof(WGPULimits, maxDynamicUniformBuffersPerPipelineLayout),
            "offsetof mismatch for Limits::maxDynamicUniformBuffersPerPipelineLayout");
    static_assert(offsetof(Limits, maxDynamicStorageBuffersPerPipelineLayout) == offsetof(WGPULimits, maxDynamicStorageBuffersPerPipelineLayout),
            "offsetof mismatch for Limits::maxDynamicStorageBuffersPerPipelineLayout");
    static_assert(offsetof(Limits, maxSampledTexturesPerShaderStage) == offsetof(WGPULimits, maxSampledTexturesPerShaderStage),
            "offsetof mismatch for Limits::maxSampledTexturesPerShaderStage");
    static_assert(offsetof(Limits, maxSamplersPerShaderStage) == offsetof(WGPULimits, maxSamplersPerShaderStage),
            "offsetof mismatch for Limits::maxSamplersPerShaderStage");
    static_assert(offsetof(Limits, maxStorageBuffersPerShaderStage) == offsetof(WGPULimits, maxStorageBuffersPerShaderStage),
            "offsetof mismatch for Limits::maxStorageBuffersPerShaderStage");
    static_assert(offsetof(Limits, maxStorageTexturesPerShaderStage) == offsetof(WGPULimits, maxStorageTexturesPerShaderStage),
            "offsetof mismatch for Limits::maxStorageTexturesPerShaderStage");
    static_assert(offsetof(Limits, maxUniformBuffersPerShaderStage) == offsetof(WGPULimits, maxUniformBuffersPerShaderStage),
            "offsetof mismatch for Limits::maxUniformBuffersPerShaderStage");
    static_assert(offsetof(Limits, maxUniformBufferBindingSize) == offsetof(WGPULimits, maxUniformBufferBindingSize),
            "offsetof mismatch for Limits::maxUniformBufferBindingSize");
    static_assert(offsetof(Limits, maxStorageBufferBindingSize) == offsetof(WGPULimits, maxStorageBufferBindingSize),
            "offsetof mismatch for Limits::maxStorageBufferBindingSize");
    static_assert(offsetof(Limits, minUniformBufferOffsetAlignment) == offsetof(WGPULimits, minUniformBufferOffsetAlignment),
            "offsetof mismatch for Limits::minUniformBufferOffsetAlignment");
    static_assert(offsetof(Limits, minStorageBufferOffsetAlignment) == offsetof(WGPULimits, minStorageBufferOffsetAlignment),
            "offsetof mismatch for Limits::minStorageBufferOffsetAlignment");
    static_assert(offsetof(Limits, maxVertexBuffers) == offsetof(WGPULimits, maxVertexBuffers),
            "offsetof mismatch for Limits::maxVertexBuffers");
    static_assert(offsetof(Limits, maxVertexAttributes) == offsetof(WGPULimits, maxVertexAttributes),
            "offsetof mismatch for Limits::maxVertexAttributes");
    static_assert(offsetof(Limits, maxVertexBufferArrayStride) == offsetof(WGPULimits, maxVertexBufferArrayStride),
            "offsetof mismatch for Limits::maxVertexBufferArrayStride");
    static_assert(offsetof(Limits, maxInterStageShaderComponents) == offsetof(WGPULimits, maxInterStageShaderComponents),
            "offsetof mismatch for Limits::maxInterStageShaderComponents");
    static_assert(offsetof(Limits, maxInterStageShaderVariables) == offsetof(WGPULimits, maxInterStageShaderVariables),
            "offsetof mismatch for Limits::maxInterStageShaderVariables");
    static_assert(offsetof(Limits, maxColorAttachments) == offsetof(WGPULimits, maxColorAttachments),
            "offsetof mismatch for Limits::maxColorAttachments");
    static_assert(offsetof(Limits, maxComputeWorkgroupStorageSize) == offsetof(WGPULimits, maxComputeWorkgroupStorageSize),
            "offsetof mismatch for Limits::maxComputeWorkgroupStorageSize");
    static_assert(offsetof(Limits, maxComputeInvocationsPerWorkgroup) == offsetof(WGPULimits, maxComputeInvocationsPerWorkgroup),
            "offsetof mismatch for Limits::maxComputeInvocationsPerWorkgroup");
    static_assert(offsetof(Limits, maxComputeWorkgroupSizeX) == offsetof(WGPULimits, maxComputeWorkgroupSizeX),
            "offsetof mismatch for Limits::maxComputeWorkgroupSizeX");
    static_assert(offsetof(Limits, maxComputeWorkgroupSizeY) == offsetof(WGPULimits, maxComputeWorkgroupSizeY),
            "offsetof mismatch for Limits::maxComputeWorkgroupSizeY");
    static_assert(offsetof(Limits, maxComputeWorkgroupSizeZ) == offsetof(WGPULimits, maxComputeWorkgroupSizeZ),
            "offsetof mismatch for Limits::maxComputeWorkgroupSizeZ");
    static_assert(offsetof(Limits, maxComputeWorkgroupsPerDimension) == offsetof(WGPULimits, maxComputeWorkgroupsPerDimension),
            "offsetof mismatch for Limits::maxComputeWorkgroupsPerDimension");

    bool Limits::operator==(const Limits& rhs) const {
        return  std::tie(
            maxTextureDimension1D,
            maxTextureDimension2D,
            maxTextureDimension3D,
            maxTextureArrayLayers,
            maxBindGroups,
            maxDynamicUniformBuffersPerPipelineLayout,
            maxDynamicStorageBuffersPerPipelineLayout,
            maxSampledTexturesPerShaderStage,
            maxSamplersPerShaderStage,
            maxStorageBuffersPerShaderStage,
            maxStorageTexturesPerShaderStage,
            maxUniformBuffersPerShaderStage,
            maxUniformBufferBindingSize,
            maxStorageBufferBindingSize,
            minUniformBufferOffsetAlignment,
            minStorageBufferOffsetAlignment,
            maxVertexBuffers,
            maxVertexAttributes,
            maxVertexBufferArrayStride,
            maxInterStageShaderComponents,
            maxInterStageShaderVariables,
            maxColorAttachments,
            maxComputeWorkgroupStorageSize,
            maxComputeInvocationsPerWorkgroup,
            maxComputeWorkgroupSizeX,
            maxComputeWorkgroupSizeY,
            maxComputeWorkgroupSizeZ,
            maxComputeWorkgroupsPerDimension
        ) == std::tie(
            rhs.maxTextureDimension1D,
            rhs.maxTextureDimension2D,
            rhs.maxTextureDimension3D,
            rhs.maxTextureArrayLayers,
            rhs.maxBindGroups,
            rhs.maxDynamicUniformBuffersPerPipelineLayout,
            rhs.maxDynamicStorageBuffersPerPipelineLayout,
            rhs.maxSampledTexturesPerShaderStage,
            rhs.maxSamplersPerShaderStage,
            rhs.maxStorageBuffersPerShaderStage,
            rhs.maxStorageTexturesPerShaderStage,
            rhs.maxUniformBuffersPerShaderStage,
            rhs.maxUniformBufferBindingSize,
            rhs.maxStorageBufferBindingSize,
            rhs.minUniformBufferOffsetAlignment,
            rhs.minStorageBufferOffsetAlignment,
            rhs.maxVertexBuffers,
            rhs.maxVertexAttributes,
            rhs.maxVertexBufferArrayStride,
            rhs.maxInterStageShaderComponents,
            rhs.maxInterStageShaderVariables,
            rhs.maxColorAttachments,
            rhs.maxComputeWorkgroupStorageSize,
            rhs.maxComputeInvocationsPerWorkgroup,
            rhs.maxComputeWorkgroupSizeX,
            rhs.maxComputeWorkgroupSizeY,
            rhs.maxComputeWorkgroupSizeZ,
            rhs.maxComputeWorkgroupsPerDimension
        );
    }


    static_assert(sizeof(MultisampleState) == sizeof(WGPUMultisampleState), "sizeof mismatch for MultisampleState");
    static_assert(alignof(MultisampleState) == alignof(WGPUMultisampleState), "alignof mismatch for MultisampleState");

    static_assert(offsetof(MultisampleState, nextInChain) == offsetof(WGPUMultisampleState, nextInChain),
            "offsetof mismatch for MultisampleState::nextInChain");
    static_assert(offsetof(MultisampleState, count) == offsetof(WGPUMultisampleState, count),
            "offsetof mismatch for MultisampleState::count");
    static_assert(offsetof(MultisampleState, mask) == offsetof(WGPUMultisampleState, mask),
            "offsetof mismatch for MultisampleState::mask");
    static_assert(offsetof(MultisampleState, alphaToCoverageEnabled) == offsetof(WGPUMultisampleState, alphaToCoverageEnabled),
            "offsetof mismatch for MultisampleState::alphaToCoverageEnabled");

    bool MultisampleState::operator==(const MultisampleState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            count,
            mask,
            alphaToCoverageEnabled
        ) == std::tie(
            rhs.count,
            rhs.mask,
            rhs.alphaToCoverageEnabled
        );
    }


    static_assert(sizeof(Origin3D) == sizeof(WGPUOrigin3D), "sizeof mismatch for Origin3D");
    static_assert(alignof(Origin3D) == alignof(WGPUOrigin3D), "alignof mismatch for Origin3D");

    static_assert(offsetof(Origin3D, x) == offsetof(WGPUOrigin3D, x),
            "offsetof mismatch for Origin3D::x");
    static_assert(offsetof(Origin3D, y) == offsetof(WGPUOrigin3D, y),
            "offsetof mismatch for Origin3D::y");
    static_assert(offsetof(Origin3D, z) == offsetof(WGPUOrigin3D, z),
            "offsetof mismatch for Origin3D::z");

    bool Origin3D::operator==(const Origin3D& rhs) const {
        return  std::tie(
            x,
            y,
            z
        ) == std::tie(
            rhs.x,
            rhs.y,
            rhs.z
        );
    }


    static_assert(sizeof(PipelineLayoutDescriptor) == sizeof(WGPUPipelineLayoutDescriptor), "sizeof mismatch for PipelineLayoutDescriptor");
    static_assert(alignof(PipelineLayoutDescriptor) == alignof(WGPUPipelineLayoutDescriptor), "alignof mismatch for PipelineLayoutDescriptor");

    static_assert(offsetof(PipelineLayoutDescriptor, nextInChain) == offsetof(WGPUPipelineLayoutDescriptor, nextInChain),
            "offsetof mismatch for PipelineLayoutDescriptor::nextInChain");
    static_assert(offsetof(PipelineLayoutDescriptor, label) == offsetof(WGPUPipelineLayoutDescriptor, label),
            "offsetof mismatch for PipelineLayoutDescriptor::label");
    static_assert(offsetof(PipelineLayoutDescriptor, bindGroupLayoutCount) == offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayoutCount),
            "offsetof mismatch for PipelineLayoutDescriptor::bindGroupLayoutCount");
    static_assert(offsetof(PipelineLayoutDescriptor, bindGroupLayouts) == offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayouts),
            "offsetof mismatch for PipelineLayoutDescriptor::bindGroupLayouts");

    bool PipelineLayoutDescriptor::operator==(const PipelineLayoutDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            bindGroupLayoutCount,
            bindGroupLayouts
        ) == std::tie(
            rhs.label,
            rhs.bindGroupLayoutCount,
            rhs.bindGroupLayouts
        );
    }


    static_assert(sizeof(PrimitiveDepthClipControl) == sizeof(WGPUPrimitiveDepthClipControl), "sizeof mismatch for PrimitiveDepthClipControl");
    static_assert(alignof(PrimitiveDepthClipControl) == alignof(WGPUPrimitiveDepthClipControl), "alignof mismatch for PrimitiveDepthClipControl");

    static_assert(offsetof(PrimitiveDepthClipControl, unclippedDepth) == offsetof(WGPUPrimitiveDepthClipControl, unclippedDepth),
            "offsetof mismatch for PrimitiveDepthClipControl::unclippedDepth");

    bool PrimitiveDepthClipControl::operator==(const PrimitiveDepthClipControl& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            unclippedDepth
        ) == std::tie(
            rhs.unclippedDepth
        );
    }


    static_assert(sizeof(PrimitiveState) == sizeof(WGPUPrimitiveState), "sizeof mismatch for PrimitiveState");
    static_assert(alignof(PrimitiveState) == alignof(WGPUPrimitiveState), "alignof mismatch for PrimitiveState");

    static_assert(offsetof(PrimitiveState, nextInChain) == offsetof(WGPUPrimitiveState, nextInChain),
            "offsetof mismatch for PrimitiveState::nextInChain");
    static_assert(offsetof(PrimitiveState, topology) == offsetof(WGPUPrimitiveState, topology),
            "offsetof mismatch for PrimitiveState::topology");
    static_assert(offsetof(PrimitiveState, stripIndexFormat) == offsetof(WGPUPrimitiveState, stripIndexFormat),
            "offsetof mismatch for PrimitiveState::stripIndexFormat");
    static_assert(offsetof(PrimitiveState, frontFace) == offsetof(WGPUPrimitiveState, frontFace),
            "offsetof mismatch for PrimitiveState::frontFace");
    static_assert(offsetof(PrimitiveState, cullMode) == offsetof(WGPUPrimitiveState, cullMode),
            "offsetof mismatch for PrimitiveState::cullMode");

    bool PrimitiveState::operator==(const PrimitiveState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            topology,
            stripIndexFormat,
            frontFace,
            cullMode
        ) == std::tie(
            rhs.topology,
            rhs.stripIndexFormat,
            rhs.frontFace,
            rhs.cullMode
        );
    }


    static_assert(sizeof(QuerySetDescriptor) == sizeof(WGPUQuerySetDescriptor), "sizeof mismatch for QuerySetDescriptor");
    static_assert(alignof(QuerySetDescriptor) == alignof(WGPUQuerySetDescriptor), "alignof mismatch for QuerySetDescriptor");

    static_assert(offsetof(QuerySetDescriptor, nextInChain) == offsetof(WGPUQuerySetDescriptor, nextInChain),
            "offsetof mismatch for QuerySetDescriptor::nextInChain");
    static_assert(offsetof(QuerySetDescriptor, label) == offsetof(WGPUQuerySetDescriptor, label),
            "offsetof mismatch for QuerySetDescriptor::label");
    static_assert(offsetof(QuerySetDescriptor, type) == offsetof(WGPUQuerySetDescriptor, type),
            "offsetof mismatch for QuerySetDescriptor::type");
    static_assert(offsetof(QuerySetDescriptor, count) == offsetof(WGPUQuerySetDescriptor, count),
            "offsetof mismatch for QuerySetDescriptor::count");
    static_assert(offsetof(QuerySetDescriptor, pipelineStatistics) == offsetof(WGPUQuerySetDescriptor, pipelineStatistics),
            "offsetof mismatch for QuerySetDescriptor::pipelineStatistics");
    static_assert(offsetof(QuerySetDescriptor, pipelineStatisticsCount) == offsetof(WGPUQuerySetDescriptor, pipelineStatisticsCount),
            "offsetof mismatch for QuerySetDescriptor::pipelineStatisticsCount");

    bool QuerySetDescriptor::operator==(const QuerySetDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            type,
            count,
            pipelineStatistics,
            pipelineStatisticsCount
        ) == std::tie(
            rhs.label,
            rhs.type,
            rhs.count,
            rhs.pipelineStatistics,
            rhs.pipelineStatisticsCount
        );
    }


    static_assert(sizeof(QueueDescriptor) == sizeof(WGPUQueueDescriptor), "sizeof mismatch for QueueDescriptor");
    static_assert(alignof(QueueDescriptor) == alignof(WGPUQueueDescriptor), "alignof mismatch for QueueDescriptor");

    static_assert(offsetof(QueueDescriptor, nextInChain) == offsetof(WGPUQueueDescriptor, nextInChain),
            "offsetof mismatch for QueueDescriptor::nextInChain");
    static_assert(offsetof(QueueDescriptor, label) == offsetof(WGPUQueueDescriptor, label),
            "offsetof mismatch for QueueDescriptor::label");

    bool QueueDescriptor::operator==(const QueueDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(RenderBundleDescriptor) == sizeof(WGPURenderBundleDescriptor), "sizeof mismatch for RenderBundleDescriptor");
    static_assert(alignof(RenderBundleDescriptor) == alignof(WGPURenderBundleDescriptor), "alignof mismatch for RenderBundleDescriptor");

    static_assert(offsetof(RenderBundleDescriptor, nextInChain) == offsetof(WGPURenderBundleDescriptor, nextInChain),
            "offsetof mismatch for RenderBundleDescriptor::nextInChain");
    static_assert(offsetof(RenderBundleDescriptor, label) == offsetof(WGPURenderBundleDescriptor, label),
            "offsetof mismatch for RenderBundleDescriptor::label");

    bool RenderBundleDescriptor::operator==(const RenderBundleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(RenderBundleEncoderDescriptor) == sizeof(WGPURenderBundleEncoderDescriptor), "sizeof mismatch for RenderBundleEncoderDescriptor");
    static_assert(alignof(RenderBundleEncoderDescriptor) == alignof(WGPURenderBundleEncoderDescriptor), "alignof mismatch for RenderBundleEncoderDescriptor");

    static_assert(offsetof(RenderBundleEncoderDescriptor, nextInChain) == offsetof(WGPURenderBundleEncoderDescriptor, nextInChain),
            "offsetof mismatch for RenderBundleEncoderDescriptor::nextInChain");
    static_assert(offsetof(RenderBundleEncoderDescriptor, label) == offsetof(WGPURenderBundleEncoderDescriptor, label),
            "offsetof mismatch for RenderBundleEncoderDescriptor::label");
    static_assert(offsetof(RenderBundleEncoderDescriptor, colorFormatsCount) == offsetof(WGPURenderBundleEncoderDescriptor, colorFormatsCount),
            "offsetof mismatch for RenderBundleEncoderDescriptor::colorFormatsCount");
    static_assert(offsetof(RenderBundleEncoderDescriptor, colorFormats) == offsetof(WGPURenderBundleEncoderDescriptor, colorFormats),
            "offsetof mismatch for RenderBundleEncoderDescriptor::colorFormats");
    static_assert(offsetof(RenderBundleEncoderDescriptor, depthStencilFormat) == offsetof(WGPURenderBundleEncoderDescriptor, depthStencilFormat),
            "offsetof mismatch for RenderBundleEncoderDescriptor::depthStencilFormat");
    static_assert(offsetof(RenderBundleEncoderDescriptor, sampleCount) == offsetof(WGPURenderBundleEncoderDescriptor, sampleCount),
            "offsetof mismatch for RenderBundleEncoderDescriptor::sampleCount");
    static_assert(offsetof(RenderBundleEncoderDescriptor, depthReadOnly) == offsetof(WGPURenderBundleEncoderDescriptor, depthReadOnly),
            "offsetof mismatch for RenderBundleEncoderDescriptor::depthReadOnly");
    static_assert(offsetof(RenderBundleEncoderDescriptor, stencilReadOnly) == offsetof(WGPURenderBundleEncoderDescriptor, stencilReadOnly),
            "offsetof mismatch for RenderBundleEncoderDescriptor::stencilReadOnly");

    bool RenderBundleEncoderDescriptor::operator==(const RenderBundleEncoderDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            colorFormatsCount,
            colorFormats,
            depthStencilFormat,
            sampleCount,
            depthReadOnly,
            stencilReadOnly
        ) == std::tie(
            rhs.label,
            rhs.colorFormatsCount,
            rhs.colorFormats,
            rhs.depthStencilFormat,
            rhs.sampleCount,
            rhs.depthReadOnly,
            rhs.stencilReadOnly
        );
    }


    static_assert(sizeof(RenderPassDepthStencilAttachment) == sizeof(WGPURenderPassDepthStencilAttachment), "sizeof mismatch for RenderPassDepthStencilAttachment");
    static_assert(alignof(RenderPassDepthStencilAttachment) == alignof(WGPURenderPassDepthStencilAttachment), "alignof mismatch for RenderPassDepthStencilAttachment");

    static_assert(offsetof(RenderPassDepthStencilAttachment, view) == offsetof(WGPURenderPassDepthStencilAttachment, view),
            "offsetof mismatch for RenderPassDepthStencilAttachment::view");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthLoadOp) == offsetof(WGPURenderPassDepthStencilAttachment, depthLoadOp),
            "offsetof mismatch for RenderPassDepthStencilAttachment::depthLoadOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthStoreOp) == offsetof(WGPURenderPassDepthStencilAttachment, depthStoreOp),
            "offsetof mismatch for RenderPassDepthStencilAttachment::depthStoreOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, clearDepth) == offsetof(WGPURenderPassDepthStencilAttachment, clearDepth),
            "offsetof mismatch for RenderPassDepthStencilAttachment::clearDepth");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthClearValue) == offsetof(WGPURenderPassDepthStencilAttachment, depthClearValue),
            "offsetof mismatch for RenderPassDepthStencilAttachment::depthClearValue");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthReadOnly) == offsetof(WGPURenderPassDepthStencilAttachment, depthReadOnly),
            "offsetof mismatch for RenderPassDepthStencilAttachment::depthReadOnly");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilLoadOp) == offsetof(WGPURenderPassDepthStencilAttachment, stencilLoadOp),
            "offsetof mismatch for RenderPassDepthStencilAttachment::stencilLoadOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilStoreOp) == offsetof(WGPURenderPassDepthStencilAttachment, stencilStoreOp),
            "offsetof mismatch for RenderPassDepthStencilAttachment::stencilStoreOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, clearStencil) == offsetof(WGPURenderPassDepthStencilAttachment, clearStencil),
            "offsetof mismatch for RenderPassDepthStencilAttachment::clearStencil");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilClearValue) == offsetof(WGPURenderPassDepthStencilAttachment, stencilClearValue),
            "offsetof mismatch for RenderPassDepthStencilAttachment::stencilClearValue");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilReadOnly) == offsetof(WGPURenderPassDepthStencilAttachment, stencilReadOnly),
            "offsetof mismatch for RenderPassDepthStencilAttachment::stencilReadOnly");

    bool RenderPassDepthStencilAttachment::operator==(const RenderPassDepthStencilAttachment& rhs) const {
        return  std::tie(
            view,
            depthLoadOp,
            depthStoreOp,
            clearDepth,
            depthClearValue,
            depthReadOnly,
            stencilLoadOp,
            stencilStoreOp,
            clearStencil,
            stencilClearValue,
            stencilReadOnly
        ) == std::tie(
            rhs.view,
            rhs.depthLoadOp,
            rhs.depthStoreOp,
            rhs.clearDepth,
            rhs.depthClearValue,
            rhs.depthReadOnly,
            rhs.stencilLoadOp,
            rhs.stencilStoreOp,
            rhs.clearStencil,
            rhs.stencilClearValue,
            rhs.stencilReadOnly
        );
    }


    static_assert(sizeof(RenderPassDescriptorMaxDrawCount) == sizeof(WGPURenderPassDescriptorMaxDrawCount), "sizeof mismatch for RenderPassDescriptorMaxDrawCount");
    static_assert(alignof(RenderPassDescriptorMaxDrawCount) == alignof(WGPURenderPassDescriptorMaxDrawCount), "alignof mismatch for RenderPassDescriptorMaxDrawCount");

    static_assert(offsetof(RenderPassDescriptorMaxDrawCount, maxDrawCount) == offsetof(WGPURenderPassDescriptorMaxDrawCount, maxDrawCount),
            "offsetof mismatch for RenderPassDescriptorMaxDrawCount::maxDrawCount");

    bool RenderPassDescriptorMaxDrawCount::operator==(const RenderPassDescriptorMaxDrawCount& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            maxDrawCount
        ) == std::tie(
            rhs.maxDrawCount
        );
    }


    static_assert(sizeof(RenderPassTimestampWrite) == sizeof(WGPURenderPassTimestampWrite), "sizeof mismatch for RenderPassTimestampWrite");
    static_assert(alignof(RenderPassTimestampWrite) == alignof(WGPURenderPassTimestampWrite), "alignof mismatch for RenderPassTimestampWrite");

    static_assert(offsetof(RenderPassTimestampWrite, querySet) == offsetof(WGPURenderPassTimestampWrite, querySet),
            "offsetof mismatch for RenderPassTimestampWrite::querySet");
    static_assert(offsetof(RenderPassTimestampWrite, queryIndex) == offsetof(WGPURenderPassTimestampWrite, queryIndex),
            "offsetof mismatch for RenderPassTimestampWrite::queryIndex");
    static_assert(offsetof(RenderPassTimestampWrite, location) == offsetof(WGPURenderPassTimestampWrite, location),
            "offsetof mismatch for RenderPassTimestampWrite::location");

    bool RenderPassTimestampWrite::operator==(const RenderPassTimestampWrite& rhs) const {
        return  std::tie(
            querySet,
            queryIndex,
            location
        ) == std::tie(
            rhs.querySet,
            rhs.queryIndex,
            rhs.location
        );
    }


    static_assert(sizeof(RequestAdapterOptions) == sizeof(WGPURequestAdapterOptions), "sizeof mismatch for RequestAdapterOptions");
    static_assert(alignof(RequestAdapterOptions) == alignof(WGPURequestAdapterOptions), "alignof mismatch for RequestAdapterOptions");

    static_assert(offsetof(RequestAdapterOptions, nextInChain) == offsetof(WGPURequestAdapterOptions, nextInChain),
            "offsetof mismatch for RequestAdapterOptions::nextInChain");
    static_assert(offsetof(RequestAdapterOptions, compatibleSurface) == offsetof(WGPURequestAdapterOptions, compatibleSurface),
            "offsetof mismatch for RequestAdapterOptions::compatibleSurface");
    static_assert(offsetof(RequestAdapterOptions, powerPreference) == offsetof(WGPURequestAdapterOptions, powerPreference),
            "offsetof mismatch for RequestAdapterOptions::powerPreference");
    static_assert(offsetof(RequestAdapterOptions, forceFallbackAdapter) == offsetof(WGPURequestAdapterOptions, forceFallbackAdapter),
            "offsetof mismatch for RequestAdapterOptions::forceFallbackAdapter");

    bool RequestAdapterOptions::operator==(const RequestAdapterOptions& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            compatibleSurface,
            powerPreference,
            forceFallbackAdapter
        ) == std::tie(
            rhs.compatibleSurface,
            rhs.powerPreference,
            rhs.forceFallbackAdapter
        );
    }


    static_assert(sizeof(SamplerBindingLayout) == sizeof(WGPUSamplerBindingLayout), "sizeof mismatch for SamplerBindingLayout");
    static_assert(alignof(SamplerBindingLayout) == alignof(WGPUSamplerBindingLayout), "alignof mismatch for SamplerBindingLayout");

    static_assert(offsetof(SamplerBindingLayout, nextInChain) == offsetof(WGPUSamplerBindingLayout, nextInChain),
            "offsetof mismatch for SamplerBindingLayout::nextInChain");
    static_assert(offsetof(SamplerBindingLayout, type) == offsetof(WGPUSamplerBindingLayout, type),
            "offsetof mismatch for SamplerBindingLayout::type");

    bool SamplerBindingLayout::operator==(const SamplerBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            type
        ) == std::tie(
            rhs.type
        );
    }


    static_assert(sizeof(SamplerDescriptor) == sizeof(WGPUSamplerDescriptor), "sizeof mismatch for SamplerDescriptor");
    static_assert(alignof(SamplerDescriptor) == alignof(WGPUSamplerDescriptor), "alignof mismatch for SamplerDescriptor");

    static_assert(offsetof(SamplerDescriptor, nextInChain) == offsetof(WGPUSamplerDescriptor, nextInChain),
            "offsetof mismatch for SamplerDescriptor::nextInChain");
    static_assert(offsetof(SamplerDescriptor, label) == offsetof(WGPUSamplerDescriptor, label),
            "offsetof mismatch for SamplerDescriptor::label");
    static_assert(offsetof(SamplerDescriptor, addressModeU) == offsetof(WGPUSamplerDescriptor, addressModeU),
            "offsetof mismatch for SamplerDescriptor::addressModeU");
    static_assert(offsetof(SamplerDescriptor, addressModeV) == offsetof(WGPUSamplerDescriptor, addressModeV),
            "offsetof mismatch for SamplerDescriptor::addressModeV");
    static_assert(offsetof(SamplerDescriptor, addressModeW) == offsetof(WGPUSamplerDescriptor, addressModeW),
            "offsetof mismatch for SamplerDescriptor::addressModeW");
    static_assert(offsetof(SamplerDescriptor, magFilter) == offsetof(WGPUSamplerDescriptor, magFilter),
            "offsetof mismatch for SamplerDescriptor::magFilter");
    static_assert(offsetof(SamplerDescriptor, minFilter) == offsetof(WGPUSamplerDescriptor, minFilter),
            "offsetof mismatch for SamplerDescriptor::minFilter");
    static_assert(offsetof(SamplerDescriptor, mipmapFilter) == offsetof(WGPUSamplerDescriptor, mipmapFilter),
            "offsetof mismatch for SamplerDescriptor::mipmapFilter");
    static_assert(offsetof(SamplerDescriptor, lodMinClamp) == offsetof(WGPUSamplerDescriptor, lodMinClamp),
            "offsetof mismatch for SamplerDescriptor::lodMinClamp");
    static_assert(offsetof(SamplerDescriptor, lodMaxClamp) == offsetof(WGPUSamplerDescriptor, lodMaxClamp),
            "offsetof mismatch for SamplerDescriptor::lodMaxClamp");
    static_assert(offsetof(SamplerDescriptor, compare) == offsetof(WGPUSamplerDescriptor, compare),
            "offsetof mismatch for SamplerDescriptor::compare");
    static_assert(offsetof(SamplerDescriptor, maxAnisotropy) == offsetof(WGPUSamplerDescriptor, maxAnisotropy),
            "offsetof mismatch for SamplerDescriptor::maxAnisotropy");

    bool SamplerDescriptor::operator==(const SamplerDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            addressModeU,
            addressModeV,
            addressModeW,
            magFilter,
            minFilter,
            mipmapFilter,
            lodMinClamp,
            lodMaxClamp,
            compare,
            maxAnisotropy
        ) == std::tie(
            rhs.label,
            rhs.addressModeU,
            rhs.addressModeV,
            rhs.addressModeW,
            rhs.magFilter,
            rhs.minFilter,
            rhs.mipmapFilter,
            rhs.lodMinClamp,
            rhs.lodMaxClamp,
            rhs.compare,
            rhs.maxAnisotropy
        );
    }


    static_assert(sizeof(ShaderModuleDescriptor) == sizeof(WGPUShaderModuleDescriptor), "sizeof mismatch for ShaderModuleDescriptor");
    static_assert(alignof(ShaderModuleDescriptor) == alignof(WGPUShaderModuleDescriptor), "alignof mismatch for ShaderModuleDescriptor");

    static_assert(offsetof(ShaderModuleDescriptor, nextInChain) == offsetof(WGPUShaderModuleDescriptor, nextInChain),
            "offsetof mismatch for ShaderModuleDescriptor::nextInChain");
    static_assert(offsetof(ShaderModuleDescriptor, label) == offsetof(WGPUShaderModuleDescriptor, label),
            "offsetof mismatch for ShaderModuleDescriptor::label");

    bool ShaderModuleDescriptor::operator==(const ShaderModuleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(ShaderModuleSPIRVDescriptor) == sizeof(WGPUShaderModuleSPIRVDescriptor), "sizeof mismatch for ShaderModuleSPIRVDescriptor");
    static_assert(alignof(ShaderModuleSPIRVDescriptor) == alignof(WGPUShaderModuleSPIRVDescriptor), "alignof mismatch for ShaderModuleSPIRVDescriptor");

    static_assert(offsetof(ShaderModuleSPIRVDescriptor, codeSize) == offsetof(WGPUShaderModuleSPIRVDescriptor, codeSize),
            "offsetof mismatch for ShaderModuleSPIRVDescriptor::codeSize");
    static_assert(offsetof(ShaderModuleSPIRVDescriptor, code) == offsetof(WGPUShaderModuleSPIRVDescriptor, code),
            "offsetof mismatch for ShaderModuleSPIRVDescriptor::code");

    bool ShaderModuleSPIRVDescriptor::operator==(const ShaderModuleSPIRVDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            codeSize,
            code
        ) == std::tie(
            rhs.codeSize,
            rhs.code
        );
    }


    static_assert(sizeof(ShaderModuleWGSLDescriptor) == sizeof(WGPUShaderModuleWGSLDescriptor), "sizeof mismatch for ShaderModuleWGSLDescriptor");
    static_assert(alignof(ShaderModuleWGSLDescriptor) == alignof(WGPUShaderModuleWGSLDescriptor), "alignof mismatch for ShaderModuleWGSLDescriptor");

    static_assert(offsetof(ShaderModuleWGSLDescriptor, source) == offsetof(WGPUShaderModuleWGSLDescriptor, source),
            "offsetof mismatch for ShaderModuleWGSLDescriptor::source");

    bool ShaderModuleWGSLDescriptor::operator==(const ShaderModuleWGSLDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            source
        ) == std::tie(
            rhs.source
        );
    }


    static_assert(sizeof(StencilFaceState) == sizeof(WGPUStencilFaceState), "sizeof mismatch for StencilFaceState");
    static_assert(alignof(StencilFaceState) == alignof(WGPUStencilFaceState), "alignof mismatch for StencilFaceState");

    static_assert(offsetof(StencilFaceState, compare) == offsetof(WGPUStencilFaceState, compare),
            "offsetof mismatch for StencilFaceState::compare");
    static_assert(offsetof(StencilFaceState, failOp) == offsetof(WGPUStencilFaceState, failOp),
            "offsetof mismatch for StencilFaceState::failOp");
    static_assert(offsetof(StencilFaceState, depthFailOp) == offsetof(WGPUStencilFaceState, depthFailOp),
            "offsetof mismatch for StencilFaceState::depthFailOp");
    static_assert(offsetof(StencilFaceState, passOp) == offsetof(WGPUStencilFaceState, passOp),
            "offsetof mismatch for StencilFaceState::passOp");

    bool StencilFaceState::operator==(const StencilFaceState& rhs) const {
        return  std::tie(
            compare,
            failOp,
            depthFailOp,
            passOp
        ) == std::tie(
            rhs.compare,
            rhs.failOp,
            rhs.depthFailOp,
            rhs.passOp
        );
    }


    static_assert(sizeof(StorageTextureBindingLayout) == sizeof(WGPUStorageTextureBindingLayout), "sizeof mismatch for StorageTextureBindingLayout");
    static_assert(alignof(StorageTextureBindingLayout) == alignof(WGPUStorageTextureBindingLayout), "alignof mismatch for StorageTextureBindingLayout");

    static_assert(offsetof(StorageTextureBindingLayout, nextInChain) == offsetof(WGPUStorageTextureBindingLayout, nextInChain),
            "offsetof mismatch for StorageTextureBindingLayout::nextInChain");
    static_assert(offsetof(StorageTextureBindingLayout, access) == offsetof(WGPUStorageTextureBindingLayout, access),
            "offsetof mismatch for StorageTextureBindingLayout::access");
    static_assert(offsetof(StorageTextureBindingLayout, format) == offsetof(WGPUStorageTextureBindingLayout, format),
            "offsetof mismatch for StorageTextureBindingLayout::format");
    static_assert(offsetof(StorageTextureBindingLayout, viewDimension) == offsetof(WGPUStorageTextureBindingLayout, viewDimension),
            "offsetof mismatch for StorageTextureBindingLayout::viewDimension");

    bool StorageTextureBindingLayout::operator==(const StorageTextureBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            access,
            format,
            viewDimension
        ) == std::tie(
            rhs.access,
            rhs.format,
            rhs.viewDimension
        );
    }


    static_assert(sizeof(SurfaceDescriptor) == sizeof(WGPUSurfaceDescriptor), "sizeof mismatch for SurfaceDescriptor");
    static_assert(alignof(SurfaceDescriptor) == alignof(WGPUSurfaceDescriptor), "alignof mismatch for SurfaceDescriptor");

    static_assert(offsetof(SurfaceDescriptor, nextInChain) == offsetof(WGPUSurfaceDescriptor, nextInChain),
            "offsetof mismatch for SurfaceDescriptor::nextInChain");
    static_assert(offsetof(SurfaceDescriptor, label) == offsetof(WGPUSurfaceDescriptor, label),
            "offsetof mismatch for SurfaceDescriptor::label");

    bool SurfaceDescriptor::operator==(const SurfaceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromAndroidNativeWindow) == sizeof(WGPUSurfaceDescriptorFromAndroidNativeWindow), "sizeof mismatch for SurfaceDescriptorFromAndroidNativeWindow");
    static_assert(alignof(SurfaceDescriptorFromAndroidNativeWindow) == alignof(WGPUSurfaceDescriptorFromAndroidNativeWindow), "alignof mismatch for SurfaceDescriptorFromAndroidNativeWindow");

    static_assert(offsetof(SurfaceDescriptorFromAndroidNativeWindow, window) == offsetof(WGPUSurfaceDescriptorFromAndroidNativeWindow, window),
            "offsetof mismatch for SurfaceDescriptorFromAndroidNativeWindow::window");

    bool SurfaceDescriptorFromAndroidNativeWindow::operator==(const SurfaceDescriptorFromAndroidNativeWindow& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            window
        ) == std::tie(
            rhs.window
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromCanvasHTMLSelector) == sizeof(WGPUSurfaceDescriptorFromCanvasHTMLSelector), "sizeof mismatch for SurfaceDescriptorFromCanvasHTMLSelector");
    static_assert(alignof(SurfaceDescriptorFromCanvasHTMLSelector) == alignof(WGPUSurfaceDescriptorFromCanvasHTMLSelector), "alignof mismatch for SurfaceDescriptorFromCanvasHTMLSelector");

    static_assert(offsetof(SurfaceDescriptorFromCanvasHTMLSelector, selector) == offsetof(WGPUSurfaceDescriptorFromCanvasHTMLSelector, selector),
            "offsetof mismatch for SurfaceDescriptorFromCanvasHTMLSelector::selector");

    bool SurfaceDescriptorFromCanvasHTMLSelector::operator==(const SurfaceDescriptorFromCanvasHTMLSelector& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            selector
        ) == std::tie(
            rhs.selector
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromMetalLayer) == sizeof(WGPUSurfaceDescriptorFromMetalLayer), "sizeof mismatch for SurfaceDescriptorFromMetalLayer");
    static_assert(alignof(SurfaceDescriptorFromMetalLayer) == alignof(WGPUSurfaceDescriptorFromMetalLayer), "alignof mismatch for SurfaceDescriptorFromMetalLayer");

    static_assert(offsetof(SurfaceDescriptorFromMetalLayer, layer) == offsetof(WGPUSurfaceDescriptorFromMetalLayer, layer),
            "offsetof mismatch for SurfaceDescriptorFromMetalLayer::layer");

    bool SurfaceDescriptorFromMetalLayer::operator==(const SurfaceDescriptorFromMetalLayer& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            layer
        ) == std::tie(
            rhs.layer
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromWaylandSurface) == sizeof(WGPUSurfaceDescriptorFromWaylandSurface), "sizeof mismatch for SurfaceDescriptorFromWaylandSurface");
    static_assert(alignof(SurfaceDescriptorFromWaylandSurface) == alignof(WGPUSurfaceDescriptorFromWaylandSurface), "alignof mismatch for SurfaceDescriptorFromWaylandSurface");

    static_assert(offsetof(SurfaceDescriptorFromWaylandSurface, display) == offsetof(WGPUSurfaceDescriptorFromWaylandSurface, display),
            "offsetof mismatch for SurfaceDescriptorFromWaylandSurface::display");
    static_assert(offsetof(SurfaceDescriptorFromWaylandSurface, surface) == offsetof(WGPUSurfaceDescriptorFromWaylandSurface, surface),
            "offsetof mismatch for SurfaceDescriptorFromWaylandSurface::surface");

    bool SurfaceDescriptorFromWaylandSurface::operator==(const SurfaceDescriptorFromWaylandSurface& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            display,
            surface
        ) == std::tie(
            rhs.display,
            rhs.surface
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromWindowsCoreWindow) == sizeof(WGPUSurfaceDescriptorFromWindowsCoreWindow), "sizeof mismatch for SurfaceDescriptorFromWindowsCoreWindow");
    static_assert(alignof(SurfaceDescriptorFromWindowsCoreWindow) == alignof(WGPUSurfaceDescriptorFromWindowsCoreWindow), "alignof mismatch for SurfaceDescriptorFromWindowsCoreWindow");

    static_assert(offsetof(SurfaceDescriptorFromWindowsCoreWindow, coreWindow) == offsetof(WGPUSurfaceDescriptorFromWindowsCoreWindow, coreWindow),
            "offsetof mismatch for SurfaceDescriptorFromWindowsCoreWindow::coreWindow");

    bool SurfaceDescriptorFromWindowsCoreWindow::operator==(const SurfaceDescriptorFromWindowsCoreWindow& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            coreWindow
        ) == std::tie(
            rhs.coreWindow
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromWindowsHWND) == sizeof(WGPUSurfaceDescriptorFromWindowsHWND), "sizeof mismatch for SurfaceDescriptorFromWindowsHWND");
    static_assert(alignof(SurfaceDescriptorFromWindowsHWND) == alignof(WGPUSurfaceDescriptorFromWindowsHWND), "alignof mismatch for SurfaceDescriptorFromWindowsHWND");

    static_assert(offsetof(SurfaceDescriptorFromWindowsHWND, hinstance) == offsetof(WGPUSurfaceDescriptorFromWindowsHWND, hinstance),
            "offsetof mismatch for SurfaceDescriptorFromWindowsHWND::hinstance");
    static_assert(offsetof(SurfaceDescriptorFromWindowsHWND, hwnd) == offsetof(WGPUSurfaceDescriptorFromWindowsHWND, hwnd),
            "offsetof mismatch for SurfaceDescriptorFromWindowsHWND::hwnd");

    bool SurfaceDescriptorFromWindowsHWND::operator==(const SurfaceDescriptorFromWindowsHWND& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            hinstance,
            hwnd
        ) == std::tie(
            rhs.hinstance,
            rhs.hwnd
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromWindowsSwapChainPanel) == sizeof(WGPUSurfaceDescriptorFromWindowsSwapChainPanel), "sizeof mismatch for SurfaceDescriptorFromWindowsSwapChainPanel");
    static_assert(alignof(SurfaceDescriptorFromWindowsSwapChainPanel) == alignof(WGPUSurfaceDescriptorFromWindowsSwapChainPanel), "alignof mismatch for SurfaceDescriptorFromWindowsSwapChainPanel");

    static_assert(offsetof(SurfaceDescriptorFromWindowsSwapChainPanel, swapChainPanel) == offsetof(WGPUSurfaceDescriptorFromWindowsSwapChainPanel, swapChainPanel),
            "offsetof mismatch for SurfaceDescriptorFromWindowsSwapChainPanel::swapChainPanel");

    bool SurfaceDescriptorFromWindowsSwapChainPanel::operator==(const SurfaceDescriptorFromWindowsSwapChainPanel& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            swapChainPanel
        ) == std::tie(
            rhs.swapChainPanel
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromXlibWindow) == sizeof(WGPUSurfaceDescriptorFromXlibWindow), "sizeof mismatch for SurfaceDescriptorFromXlibWindow");
    static_assert(alignof(SurfaceDescriptorFromXlibWindow) == alignof(WGPUSurfaceDescriptorFromXlibWindow), "alignof mismatch for SurfaceDescriptorFromXlibWindow");

    static_assert(offsetof(SurfaceDescriptorFromXlibWindow, display) == offsetof(WGPUSurfaceDescriptorFromXlibWindow, display),
            "offsetof mismatch for SurfaceDescriptorFromXlibWindow::display");
    static_assert(offsetof(SurfaceDescriptorFromXlibWindow, window) == offsetof(WGPUSurfaceDescriptorFromXlibWindow, window),
            "offsetof mismatch for SurfaceDescriptorFromXlibWindow::window");

    bool SurfaceDescriptorFromXlibWindow::operator==(const SurfaceDescriptorFromXlibWindow& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            display,
            window
        ) == std::tie(
            rhs.display,
            rhs.window
        );
    }


    static_assert(sizeof(SwapChainDescriptor) == sizeof(WGPUSwapChainDescriptor), "sizeof mismatch for SwapChainDescriptor");
    static_assert(alignof(SwapChainDescriptor) == alignof(WGPUSwapChainDescriptor), "alignof mismatch for SwapChainDescriptor");

    static_assert(offsetof(SwapChainDescriptor, nextInChain) == offsetof(WGPUSwapChainDescriptor, nextInChain),
            "offsetof mismatch for SwapChainDescriptor::nextInChain");
    static_assert(offsetof(SwapChainDescriptor, label) == offsetof(WGPUSwapChainDescriptor, label),
            "offsetof mismatch for SwapChainDescriptor::label");
    static_assert(offsetof(SwapChainDescriptor, usage) == offsetof(WGPUSwapChainDescriptor, usage),
            "offsetof mismatch for SwapChainDescriptor::usage");
    static_assert(offsetof(SwapChainDescriptor, format) == offsetof(WGPUSwapChainDescriptor, format),
            "offsetof mismatch for SwapChainDescriptor::format");
    static_assert(offsetof(SwapChainDescriptor, width) == offsetof(WGPUSwapChainDescriptor, width),
            "offsetof mismatch for SwapChainDescriptor::width");
    static_assert(offsetof(SwapChainDescriptor, height) == offsetof(WGPUSwapChainDescriptor, height),
            "offsetof mismatch for SwapChainDescriptor::height");
    static_assert(offsetof(SwapChainDescriptor, presentMode) == offsetof(WGPUSwapChainDescriptor, presentMode),
            "offsetof mismatch for SwapChainDescriptor::presentMode");
    static_assert(offsetof(SwapChainDescriptor, implementation) == offsetof(WGPUSwapChainDescriptor, implementation),
            "offsetof mismatch for SwapChainDescriptor::implementation");

    bool SwapChainDescriptor::operator==(const SwapChainDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            usage,
            format,
            width,
            height,
            presentMode,
            implementation
        ) == std::tie(
            rhs.label,
            rhs.usage,
            rhs.format,
            rhs.width,
            rhs.height,
            rhs.presentMode,
            rhs.implementation
        );
    }


    static_assert(sizeof(TextureBindingLayout) == sizeof(WGPUTextureBindingLayout), "sizeof mismatch for TextureBindingLayout");
    static_assert(alignof(TextureBindingLayout) == alignof(WGPUTextureBindingLayout), "alignof mismatch for TextureBindingLayout");

    static_assert(offsetof(TextureBindingLayout, nextInChain) == offsetof(WGPUTextureBindingLayout, nextInChain),
            "offsetof mismatch for TextureBindingLayout::nextInChain");
    static_assert(offsetof(TextureBindingLayout, sampleType) == offsetof(WGPUTextureBindingLayout, sampleType),
            "offsetof mismatch for TextureBindingLayout::sampleType");
    static_assert(offsetof(TextureBindingLayout, viewDimension) == offsetof(WGPUTextureBindingLayout, viewDimension),
            "offsetof mismatch for TextureBindingLayout::viewDimension");
    static_assert(offsetof(TextureBindingLayout, multisampled) == offsetof(WGPUTextureBindingLayout, multisampled),
            "offsetof mismatch for TextureBindingLayout::multisampled");

    bool TextureBindingLayout::operator==(const TextureBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sampleType,
            viewDimension,
            multisampled
        ) == std::tie(
            rhs.sampleType,
            rhs.viewDimension,
            rhs.multisampled
        );
    }


    static_assert(sizeof(TextureDataLayout) == sizeof(WGPUTextureDataLayout), "sizeof mismatch for TextureDataLayout");
    static_assert(alignof(TextureDataLayout) == alignof(WGPUTextureDataLayout), "alignof mismatch for TextureDataLayout");

    static_assert(offsetof(TextureDataLayout, nextInChain) == offsetof(WGPUTextureDataLayout, nextInChain),
            "offsetof mismatch for TextureDataLayout::nextInChain");
    static_assert(offsetof(TextureDataLayout, offset) == offsetof(WGPUTextureDataLayout, offset),
            "offsetof mismatch for TextureDataLayout::offset");
    static_assert(offsetof(TextureDataLayout, bytesPerRow) == offsetof(WGPUTextureDataLayout, bytesPerRow),
            "offsetof mismatch for TextureDataLayout::bytesPerRow");
    static_assert(offsetof(TextureDataLayout, rowsPerImage) == offsetof(WGPUTextureDataLayout, rowsPerImage),
            "offsetof mismatch for TextureDataLayout::rowsPerImage");

    bool TextureDataLayout::operator==(const TextureDataLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            offset,
            bytesPerRow,
            rowsPerImage
        ) == std::tie(
            rhs.offset,
            rhs.bytesPerRow,
            rhs.rowsPerImage
        );
    }


    static_assert(sizeof(TextureViewDescriptor) == sizeof(WGPUTextureViewDescriptor), "sizeof mismatch for TextureViewDescriptor");
    static_assert(alignof(TextureViewDescriptor) == alignof(WGPUTextureViewDescriptor), "alignof mismatch for TextureViewDescriptor");

    static_assert(offsetof(TextureViewDescriptor, nextInChain) == offsetof(WGPUTextureViewDescriptor, nextInChain),
            "offsetof mismatch for TextureViewDescriptor::nextInChain");
    static_assert(offsetof(TextureViewDescriptor, label) == offsetof(WGPUTextureViewDescriptor, label),
            "offsetof mismatch for TextureViewDescriptor::label");
    static_assert(offsetof(TextureViewDescriptor, format) == offsetof(WGPUTextureViewDescriptor, format),
            "offsetof mismatch for TextureViewDescriptor::format");
    static_assert(offsetof(TextureViewDescriptor, dimension) == offsetof(WGPUTextureViewDescriptor, dimension),
            "offsetof mismatch for TextureViewDescriptor::dimension");
    static_assert(offsetof(TextureViewDescriptor, baseMipLevel) == offsetof(WGPUTextureViewDescriptor, baseMipLevel),
            "offsetof mismatch for TextureViewDescriptor::baseMipLevel");
    static_assert(offsetof(TextureViewDescriptor, mipLevelCount) == offsetof(WGPUTextureViewDescriptor, mipLevelCount),
            "offsetof mismatch for TextureViewDescriptor::mipLevelCount");
    static_assert(offsetof(TextureViewDescriptor, baseArrayLayer) == offsetof(WGPUTextureViewDescriptor, baseArrayLayer),
            "offsetof mismatch for TextureViewDescriptor::baseArrayLayer");
    static_assert(offsetof(TextureViewDescriptor, arrayLayerCount) == offsetof(WGPUTextureViewDescriptor, arrayLayerCount),
            "offsetof mismatch for TextureViewDescriptor::arrayLayerCount");
    static_assert(offsetof(TextureViewDescriptor, aspect) == offsetof(WGPUTextureViewDescriptor, aspect),
            "offsetof mismatch for TextureViewDescriptor::aspect");

    bool TextureViewDescriptor::operator==(const TextureViewDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            format,
            dimension,
            baseMipLevel,
            mipLevelCount,
            baseArrayLayer,
            arrayLayerCount,
            aspect
        ) == std::tie(
            rhs.label,
            rhs.format,
            rhs.dimension,
            rhs.baseMipLevel,
            rhs.mipLevelCount,
            rhs.baseArrayLayer,
            rhs.arrayLayerCount,
            rhs.aspect
        );
    }


    static_assert(sizeof(VertexAttribute) == sizeof(WGPUVertexAttribute), "sizeof mismatch for VertexAttribute");
    static_assert(alignof(VertexAttribute) == alignof(WGPUVertexAttribute), "alignof mismatch for VertexAttribute");

    static_assert(offsetof(VertexAttribute, format) == offsetof(WGPUVertexAttribute, format),
            "offsetof mismatch for VertexAttribute::format");
    static_assert(offsetof(VertexAttribute, offset) == offsetof(WGPUVertexAttribute, offset),
            "offsetof mismatch for VertexAttribute::offset");
    static_assert(offsetof(VertexAttribute, shaderLocation) == offsetof(WGPUVertexAttribute, shaderLocation),
            "offsetof mismatch for VertexAttribute::shaderLocation");

    bool VertexAttribute::operator==(const VertexAttribute& rhs) const {
        return  std::tie(
            format,
            offset,
            shaderLocation
        ) == std::tie(
            rhs.format,
            rhs.offset,
            rhs.shaderLocation
        );
    }


    static_assert(sizeof(BindGroupDescriptor) == sizeof(WGPUBindGroupDescriptor), "sizeof mismatch for BindGroupDescriptor");
    static_assert(alignof(BindGroupDescriptor) == alignof(WGPUBindGroupDescriptor), "alignof mismatch for BindGroupDescriptor");

    static_assert(offsetof(BindGroupDescriptor, nextInChain) == offsetof(WGPUBindGroupDescriptor, nextInChain),
            "offsetof mismatch for BindGroupDescriptor::nextInChain");
    static_assert(offsetof(BindGroupDescriptor, label) == offsetof(WGPUBindGroupDescriptor, label),
            "offsetof mismatch for BindGroupDescriptor::label");
    static_assert(offsetof(BindGroupDescriptor, layout) == offsetof(WGPUBindGroupDescriptor, layout),
            "offsetof mismatch for BindGroupDescriptor::layout");
    static_assert(offsetof(BindGroupDescriptor, entryCount) == offsetof(WGPUBindGroupDescriptor, entryCount),
            "offsetof mismatch for BindGroupDescriptor::entryCount");
    static_assert(offsetof(BindGroupDescriptor, entries) == offsetof(WGPUBindGroupDescriptor, entries),
            "offsetof mismatch for BindGroupDescriptor::entries");

    bool BindGroupDescriptor::operator==(const BindGroupDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            layout,
            entryCount,
            entries
        ) == std::tie(
            rhs.label,
            rhs.layout,
            rhs.entryCount,
            rhs.entries
        );
    }


    static_assert(sizeof(BindGroupLayoutEntry) == sizeof(WGPUBindGroupLayoutEntry), "sizeof mismatch for BindGroupLayoutEntry");
    static_assert(alignof(BindGroupLayoutEntry) == alignof(WGPUBindGroupLayoutEntry), "alignof mismatch for BindGroupLayoutEntry");

    static_assert(offsetof(BindGroupLayoutEntry, nextInChain) == offsetof(WGPUBindGroupLayoutEntry, nextInChain),
            "offsetof mismatch for BindGroupLayoutEntry::nextInChain");
    static_assert(offsetof(BindGroupLayoutEntry, binding) == offsetof(WGPUBindGroupLayoutEntry, binding),
            "offsetof mismatch for BindGroupLayoutEntry::binding");
    static_assert(offsetof(BindGroupLayoutEntry, visibility) == offsetof(WGPUBindGroupLayoutEntry, visibility),
            "offsetof mismatch for BindGroupLayoutEntry::visibility");
    static_assert(offsetof(BindGroupLayoutEntry, buffer) == offsetof(WGPUBindGroupLayoutEntry, buffer),
            "offsetof mismatch for BindGroupLayoutEntry::buffer");
    static_assert(offsetof(BindGroupLayoutEntry, sampler) == offsetof(WGPUBindGroupLayoutEntry, sampler),
            "offsetof mismatch for BindGroupLayoutEntry::sampler");
    static_assert(offsetof(BindGroupLayoutEntry, texture) == offsetof(WGPUBindGroupLayoutEntry, texture),
            "offsetof mismatch for BindGroupLayoutEntry::texture");
    static_assert(offsetof(BindGroupLayoutEntry, storageTexture) == offsetof(WGPUBindGroupLayoutEntry, storageTexture),
            "offsetof mismatch for BindGroupLayoutEntry::storageTexture");

    bool BindGroupLayoutEntry::operator==(const BindGroupLayoutEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            binding,
            visibility,
            buffer,
            sampler,
            texture,
            storageTexture
        ) == std::tie(
            rhs.binding,
            rhs.visibility,
            rhs.buffer,
            rhs.sampler,
            rhs.texture,
            rhs.storageTexture
        );
    }


    static_assert(sizeof(BlendState) == sizeof(WGPUBlendState), "sizeof mismatch for BlendState");
    static_assert(alignof(BlendState) == alignof(WGPUBlendState), "alignof mismatch for BlendState");

    static_assert(offsetof(BlendState, color) == offsetof(WGPUBlendState, color),
            "offsetof mismatch for BlendState::color");
    static_assert(offsetof(BlendState, alpha) == offsetof(WGPUBlendState, alpha),
            "offsetof mismatch for BlendState::alpha");

    bool BlendState::operator==(const BlendState& rhs) const {
        return  std::tie(
            color,
            alpha
        ) == std::tie(
            rhs.color,
            rhs.alpha
        );
    }


    static_assert(sizeof(CompilationInfo) == sizeof(WGPUCompilationInfo), "sizeof mismatch for CompilationInfo");
    static_assert(alignof(CompilationInfo) == alignof(WGPUCompilationInfo), "alignof mismatch for CompilationInfo");

    static_assert(offsetof(CompilationInfo, nextInChain) == offsetof(WGPUCompilationInfo, nextInChain),
            "offsetof mismatch for CompilationInfo::nextInChain");
    static_assert(offsetof(CompilationInfo, messageCount) == offsetof(WGPUCompilationInfo, messageCount),
            "offsetof mismatch for CompilationInfo::messageCount");
    static_assert(offsetof(CompilationInfo, messages) == offsetof(WGPUCompilationInfo, messages),
            "offsetof mismatch for CompilationInfo::messages");

    bool CompilationInfo::operator==(const CompilationInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            messageCount,
            messages
        ) == std::tie(
            rhs.messageCount,
            rhs.messages
        );
    }


    static_assert(sizeof(ComputePassDescriptor) == sizeof(WGPUComputePassDescriptor), "sizeof mismatch for ComputePassDescriptor");
    static_assert(alignof(ComputePassDescriptor) == alignof(WGPUComputePassDescriptor), "alignof mismatch for ComputePassDescriptor");

    static_assert(offsetof(ComputePassDescriptor, nextInChain) == offsetof(WGPUComputePassDescriptor, nextInChain),
            "offsetof mismatch for ComputePassDescriptor::nextInChain");
    static_assert(offsetof(ComputePassDescriptor, label) == offsetof(WGPUComputePassDescriptor, label),
            "offsetof mismatch for ComputePassDescriptor::label");
    static_assert(offsetof(ComputePassDescriptor, timestampWriteCount) == offsetof(WGPUComputePassDescriptor, timestampWriteCount),
            "offsetof mismatch for ComputePassDescriptor::timestampWriteCount");
    static_assert(offsetof(ComputePassDescriptor, timestampWrites) == offsetof(WGPUComputePassDescriptor, timestampWrites),
            "offsetof mismatch for ComputePassDescriptor::timestampWrites");

    bool ComputePassDescriptor::operator==(const ComputePassDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            timestampWriteCount,
            timestampWrites
        ) == std::tie(
            rhs.label,
            rhs.timestampWriteCount,
            rhs.timestampWrites
        );
    }


    static_assert(sizeof(DepthStencilState) == sizeof(WGPUDepthStencilState), "sizeof mismatch for DepthStencilState");
    static_assert(alignof(DepthStencilState) == alignof(WGPUDepthStencilState), "alignof mismatch for DepthStencilState");

    static_assert(offsetof(DepthStencilState, nextInChain) == offsetof(WGPUDepthStencilState, nextInChain),
            "offsetof mismatch for DepthStencilState::nextInChain");
    static_assert(offsetof(DepthStencilState, format) == offsetof(WGPUDepthStencilState, format),
            "offsetof mismatch for DepthStencilState::format");
    static_assert(offsetof(DepthStencilState, depthWriteEnabled) == offsetof(WGPUDepthStencilState, depthWriteEnabled),
            "offsetof mismatch for DepthStencilState::depthWriteEnabled");
    static_assert(offsetof(DepthStencilState, depthCompare) == offsetof(WGPUDepthStencilState, depthCompare),
            "offsetof mismatch for DepthStencilState::depthCompare");
    static_assert(offsetof(DepthStencilState, stencilFront) == offsetof(WGPUDepthStencilState, stencilFront),
            "offsetof mismatch for DepthStencilState::stencilFront");
    static_assert(offsetof(DepthStencilState, stencilBack) == offsetof(WGPUDepthStencilState, stencilBack),
            "offsetof mismatch for DepthStencilState::stencilBack");
    static_assert(offsetof(DepthStencilState, stencilReadMask) == offsetof(WGPUDepthStencilState, stencilReadMask),
            "offsetof mismatch for DepthStencilState::stencilReadMask");
    static_assert(offsetof(DepthStencilState, stencilWriteMask) == offsetof(WGPUDepthStencilState, stencilWriteMask),
            "offsetof mismatch for DepthStencilState::stencilWriteMask");
    static_assert(offsetof(DepthStencilState, depthBias) == offsetof(WGPUDepthStencilState, depthBias),
            "offsetof mismatch for DepthStencilState::depthBias");
    static_assert(offsetof(DepthStencilState, depthBiasSlopeScale) == offsetof(WGPUDepthStencilState, depthBiasSlopeScale),
            "offsetof mismatch for DepthStencilState::depthBiasSlopeScale");
    static_assert(offsetof(DepthStencilState, depthBiasClamp) == offsetof(WGPUDepthStencilState, depthBiasClamp),
            "offsetof mismatch for DepthStencilState::depthBiasClamp");

    bool DepthStencilState::operator==(const DepthStencilState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            format,
            depthWriteEnabled,
            depthCompare,
            stencilFront,
            stencilBack,
            stencilReadMask,
            stencilWriteMask,
            depthBias,
            depthBiasSlopeScale,
            depthBiasClamp
        ) == std::tie(
            rhs.format,
            rhs.depthWriteEnabled,
            rhs.depthCompare,
            rhs.stencilFront,
            rhs.stencilBack,
            rhs.stencilReadMask,
            rhs.stencilWriteMask,
            rhs.depthBias,
            rhs.depthBiasSlopeScale,
            rhs.depthBiasClamp
        );
    }


    static_assert(sizeof(ImageCopyBuffer) == sizeof(WGPUImageCopyBuffer), "sizeof mismatch for ImageCopyBuffer");
    static_assert(alignof(ImageCopyBuffer) == alignof(WGPUImageCopyBuffer), "alignof mismatch for ImageCopyBuffer");

    static_assert(offsetof(ImageCopyBuffer, nextInChain) == offsetof(WGPUImageCopyBuffer, nextInChain),
            "offsetof mismatch for ImageCopyBuffer::nextInChain");
    static_assert(offsetof(ImageCopyBuffer, layout) == offsetof(WGPUImageCopyBuffer, layout),
            "offsetof mismatch for ImageCopyBuffer::layout");
    static_assert(offsetof(ImageCopyBuffer, buffer) == offsetof(WGPUImageCopyBuffer, buffer),
            "offsetof mismatch for ImageCopyBuffer::buffer");

    bool ImageCopyBuffer::operator==(const ImageCopyBuffer& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            layout,
            buffer
        ) == std::tie(
            rhs.layout,
            rhs.buffer
        );
    }


    static_assert(sizeof(ImageCopyTexture) == sizeof(WGPUImageCopyTexture), "sizeof mismatch for ImageCopyTexture");
    static_assert(alignof(ImageCopyTexture) == alignof(WGPUImageCopyTexture), "alignof mismatch for ImageCopyTexture");

    static_assert(offsetof(ImageCopyTexture, nextInChain) == offsetof(WGPUImageCopyTexture, nextInChain),
            "offsetof mismatch for ImageCopyTexture::nextInChain");
    static_assert(offsetof(ImageCopyTexture, texture) == offsetof(WGPUImageCopyTexture, texture),
            "offsetof mismatch for ImageCopyTexture::texture");
    static_assert(offsetof(ImageCopyTexture, mipLevel) == offsetof(WGPUImageCopyTexture, mipLevel),
            "offsetof mismatch for ImageCopyTexture::mipLevel");
    static_assert(offsetof(ImageCopyTexture, origin) == offsetof(WGPUImageCopyTexture, origin),
            "offsetof mismatch for ImageCopyTexture::origin");
    static_assert(offsetof(ImageCopyTexture, aspect) == offsetof(WGPUImageCopyTexture, aspect),
            "offsetof mismatch for ImageCopyTexture::aspect");

    bool ImageCopyTexture::operator==(const ImageCopyTexture& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            texture,
            mipLevel,
            origin,
            aspect
        ) == std::tie(
            rhs.texture,
            rhs.mipLevel,
            rhs.origin,
            rhs.aspect
        );
    }


    static_assert(sizeof(ProgrammableStageDescriptor) == sizeof(WGPUProgrammableStageDescriptor), "sizeof mismatch for ProgrammableStageDescriptor");
    static_assert(alignof(ProgrammableStageDescriptor) == alignof(WGPUProgrammableStageDescriptor), "alignof mismatch for ProgrammableStageDescriptor");

    static_assert(offsetof(ProgrammableStageDescriptor, nextInChain) == offsetof(WGPUProgrammableStageDescriptor, nextInChain),
            "offsetof mismatch for ProgrammableStageDescriptor::nextInChain");
    static_assert(offsetof(ProgrammableStageDescriptor, module) == offsetof(WGPUProgrammableStageDescriptor, module),
            "offsetof mismatch for ProgrammableStageDescriptor::module");
    static_assert(offsetof(ProgrammableStageDescriptor, entryPoint) == offsetof(WGPUProgrammableStageDescriptor, entryPoint),
            "offsetof mismatch for ProgrammableStageDescriptor::entryPoint");
    static_assert(offsetof(ProgrammableStageDescriptor, constantCount) == offsetof(WGPUProgrammableStageDescriptor, constantCount),
            "offsetof mismatch for ProgrammableStageDescriptor::constantCount");
    static_assert(offsetof(ProgrammableStageDescriptor, constants) == offsetof(WGPUProgrammableStageDescriptor, constants),
            "offsetof mismatch for ProgrammableStageDescriptor::constants");

    bool ProgrammableStageDescriptor::operator==(const ProgrammableStageDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            module,
            entryPoint,
            constantCount,
            constants
        ) == std::tie(
            rhs.module,
            rhs.entryPoint,
            rhs.constantCount,
            rhs.constants
        );
    }


    static_assert(sizeof(RenderPassColorAttachment) == sizeof(WGPURenderPassColorAttachment), "sizeof mismatch for RenderPassColorAttachment");
    static_assert(alignof(RenderPassColorAttachment) == alignof(WGPURenderPassColorAttachment), "alignof mismatch for RenderPassColorAttachment");

    static_assert(offsetof(RenderPassColorAttachment, view) == offsetof(WGPURenderPassColorAttachment, view),
            "offsetof mismatch for RenderPassColorAttachment::view");
    static_assert(offsetof(RenderPassColorAttachment, resolveTarget) == offsetof(WGPURenderPassColorAttachment, resolveTarget),
            "offsetof mismatch for RenderPassColorAttachment::resolveTarget");
    static_assert(offsetof(RenderPassColorAttachment, loadOp) == offsetof(WGPURenderPassColorAttachment, loadOp),
            "offsetof mismatch for RenderPassColorAttachment::loadOp");
    static_assert(offsetof(RenderPassColorAttachment, storeOp) == offsetof(WGPURenderPassColorAttachment, storeOp),
            "offsetof mismatch for RenderPassColorAttachment::storeOp");
    static_assert(offsetof(RenderPassColorAttachment, clearColor) == offsetof(WGPURenderPassColorAttachment, clearColor),
            "offsetof mismatch for RenderPassColorAttachment::clearColor");
    static_assert(offsetof(RenderPassColorAttachment, clearValue) == offsetof(WGPURenderPassColorAttachment, clearValue),
            "offsetof mismatch for RenderPassColorAttachment::clearValue");

    bool RenderPassColorAttachment::operator==(const RenderPassColorAttachment& rhs) const {
        return  std::tie(
            view,
            resolveTarget,
            loadOp,
            storeOp,
            clearColor,
            clearValue
        ) == std::tie(
            rhs.view,
            rhs.resolveTarget,
            rhs.loadOp,
            rhs.storeOp,
            rhs.clearColor,
            rhs.clearValue
        );
    }


    static_assert(sizeof(RequiredLimits) == sizeof(WGPURequiredLimits), "sizeof mismatch for RequiredLimits");
    static_assert(alignof(RequiredLimits) == alignof(WGPURequiredLimits), "alignof mismatch for RequiredLimits");

    static_assert(offsetof(RequiredLimits, nextInChain) == offsetof(WGPURequiredLimits, nextInChain),
            "offsetof mismatch for RequiredLimits::nextInChain");
    static_assert(offsetof(RequiredLimits, limits) == offsetof(WGPURequiredLimits, limits),
            "offsetof mismatch for RequiredLimits::limits");

    bool RequiredLimits::operator==(const RequiredLimits& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            limits
        ) == std::tie(
            rhs.limits
        );
    }


    static_assert(sizeof(SupportedLimits) == sizeof(WGPUSupportedLimits), "sizeof mismatch for SupportedLimits");
    static_assert(alignof(SupportedLimits) == alignof(WGPUSupportedLimits), "alignof mismatch for SupportedLimits");

    static_assert(offsetof(SupportedLimits, nextInChain) == offsetof(WGPUSupportedLimits, nextInChain),
            "offsetof mismatch for SupportedLimits::nextInChain");
    static_assert(offsetof(SupportedLimits, limits) == offsetof(WGPUSupportedLimits, limits),
            "offsetof mismatch for SupportedLimits::limits");

    bool SupportedLimits::operator==(const SupportedLimits& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            limits
        ) == std::tie(
            rhs.limits
        );
    }


    static_assert(sizeof(TextureDescriptor) == sizeof(WGPUTextureDescriptor), "sizeof mismatch for TextureDescriptor");
    static_assert(alignof(TextureDescriptor) == alignof(WGPUTextureDescriptor), "alignof mismatch for TextureDescriptor");

    static_assert(offsetof(TextureDescriptor, nextInChain) == offsetof(WGPUTextureDescriptor, nextInChain),
            "offsetof mismatch for TextureDescriptor::nextInChain");
    static_assert(offsetof(TextureDescriptor, label) == offsetof(WGPUTextureDescriptor, label),
            "offsetof mismatch for TextureDescriptor::label");
    static_assert(offsetof(TextureDescriptor, usage) == offsetof(WGPUTextureDescriptor, usage),
            "offsetof mismatch for TextureDescriptor::usage");
    static_assert(offsetof(TextureDescriptor, dimension) == offsetof(WGPUTextureDescriptor, dimension),
            "offsetof mismatch for TextureDescriptor::dimension");
    static_assert(offsetof(TextureDescriptor, size) == offsetof(WGPUTextureDescriptor, size),
            "offsetof mismatch for TextureDescriptor::size");
    static_assert(offsetof(TextureDescriptor, format) == offsetof(WGPUTextureDescriptor, format),
            "offsetof mismatch for TextureDescriptor::format");
    static_assert(offsetof(TextureDescriptor, mipLevelCount) == offsetof(WGPUTextureDescriptor, mipLevelCount),
            "offsetof mismatch for TextureDescriptor::mipLevelCount");
    static_assert(offsetof(TextureDescriptor, sampleCount) == offsetof(WGPUTextureDescriptor, sampleCount),
            "offsetof mismatch for TextureDescriptor::sampleCount");
    static_assert(offsetof(TextureDescriptor, viewFormatCount) == offsetof(WGPUTextureDescriptor, viewFormatCount),
            "offsetof mismatch for TextureDescriptor::viewFormatCount");
    static_assert(offsetof(TextureDescriptor, viewFormats) == offsetof(WGPUTextureDescriptor, viewFormats),
            "offsetof mismatch for TextureDescriptor::viewFormats");

    bool TextureDescriptor::operator==(const TextureDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            usage,
            dimension,
            size,
            format,
            mipLevelCount,
            sampleCount,
            viewFormatCount,
            viewFormats
        ) == std::tie(
            rhs.label,
            rhs.usage,
            rhs.dimension,
            rhs.size,
            rhs.format,
            rhs.mipLevelCount,
            rhs.sampleCount,
            rhs.viewFormatCount,
            rhs.viewFormats
        );
    }


    static_assert(sizeof(VertexBufferLayout) == sizeof(WGPUVertexBufferLayout), "sizeof mismatch for VertexBufferLayout");
    static_assert(alignof(VertexBufferLayout) == alignof(WGPUVertexBufferLayout), "alignof mismatch for VertexBufferLayout");

    static_assert(offsetof(VertexBufferLayout, arrayStride) == offsetof(WGPUVertexBufferLayout, arrayStride),
            "offsetof mismatch for VertexBufferLayout::arrayStride");
    static_assert(offsetof(VertexBufferLayout, stepMode) == offsetof(WGPUVertexBufferLayout, stepMode),
            "offsetof mismatch for VertexBufferLayout::stepMode");
    static_assert(offsetof(VertexBufferLayout, attributeCount) == offsetof(WGPUVertexBufferLayout, attributeCount),
            "offsetof mismatch for VertexBufferLayout::attributeCount");
    static_assert(offsetof(VertexBufferLayout, attributes) == offsetof(WGPUVertexBufferLayout, attributes),
            "offsetof mismatch for VertexBufferLayout::attributes");

    bool VertexBufferLayout::operator==(const VertexBufferLayout& rhs) const {
        return  std::tie(
            arrayStride,
            stepMode,
            attributeCount,
            attributes
        ) == std::tie(
            rhs.arrayStride,
            rhs.stepMode,
            rhs.attributeCount,
            rhs.attributes
        );
    }


    static_assert(sizeof(BindGroupLayoutDescriptor) == sizeof(WGPUBindGroupLayoutDescriptor), "sizeof mismatch for BindGroupLayoutDescriptor");
    static_assert(alignof(BindGroupLayoutDescriptor) == alignof(WGPUBindGroupLayoutDescriptor), "alignof mismatch for BindGroupLayoutDescriptor");

    static_assert(offsetof(BindGroupLayoutDescriptor, nextInChain) == offsetof(WGPUBindGroupLayoutDescriptor, nextInChain),
            "offsetof mismatch for BindGroupLayoutDescriptor::nextInChain");
    static_assert(offsetof(BindGroupLayoutDescriptor, label) == offsetof(WGPUBindGroupLayoutDescriptor, label),
            "offsetof mismatch for BindGroupLayoutDescriptor::label");
    static_assert(offsetof(BindGroupLayoutDescriptor, entryCount) == offsetof(WGPUBindGroupLayoutDescriptor, entryCount),
            "offsetof mismatch for BindGroupLayoutDescriptor::entryCount");
    static_assert(offsetof(BindGroupLayoutDescriptor, entries) == offsetof(WGPUBindGroupLayoutDescriptor, entries),
            "offsetof mismatch for BindGroupLayoutDescriptor::entries");

    bool BindGroupLayoutDescriptor::operator==(const BindGroupLayoutDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            entryCount,
            entries
        ) == std::tie(
            rhs.label,
            rhs.entryCount,
            rhs.entries
        );
    }


    static_assert(sizeof(ColorTargetState) == sizeof(WGPUColorTargetState), "sizeof mismatch for ColorTargetState");
    static_assert(alignof(ColorTargetState) == alignof(WGPUColorTargetState), "alignof mismatch for ColorTargetState");

    static_assert(offsetof(ColorTargetState, nextInChain) == offsetof(WGPUColorTargetState, nextInChain),
            "offsetof mismatch for ColorTargetState::nextInChain");
    static_assert(offsetof(ColorTargetState, format) == offsetof(WGPUColorTargetState, format),
            "offsetof mismatch for ColorTargetState::format");
    static_assert(offsetof(ColorTargetState, blend) == offsetof(WGPUColorTargetState, blend),
            "offsetof mismatch for ColorTargetState::blend");
    static_assert(offsetof(ColorTargetState, writeMask) == offsetof(WGPUColorTargetState, writeMask),
            "offsetof mismatch for ColorTargetState::writeMask");

    bool ColorTargetState::operator==(const ColorTargetState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            format,
            blend,
            writeMask
        ) == std::tie(
            rhs.format,
            rhs.blend,
            rhs.writeMask
        );
    }


    static_assert(sizeof(ComputePipelineDescriptor) == sizeof(WGPUComputePipelineDescriptor), "sizeof mismatch for ComputePipelineDescriptor");
    static_assert(alignof(ComputePipelineDescriptor) == alignof(WGPUComputePipelineDescriptor), "alignof mismatch for ComputePipelineDescriptor");

    static_assert(offsetof(ComputePipelineDescriptor, nextInChain) == offsetof(WGPUComputePipelineDescriptor, nextInChain),
            "offsetof mismatch for ComputePipelineDescriptor::nextInChain");
    static_assert(offsetof(ComputePipelineDescriptor, label) == offsetof(WGPUComputePipelineDescriptor, label),
            "offsetof mismatch for ComputePipelineDescriptor::label");
    static_assert(offsetof(ComputePipelineDescriptor, layout) == offsetof(WGPUComputePipelineDescriptor, layout),
            "offsetof mismatch for ComputePipelineDescriptor::layout");
    static_assert(offsetof(ComputePipelineDescriptor, compute) == offsetof(WGPUComputePipelineDescriptor, compute),
            "offsetof mismatch for ComputePipelineDescriptor::compute");

    bool ComputePipelineDescriptor::operator==(const ComputePipelineDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            layout,
            compute
        ) == std::tie(
            rhs.label,
            rhs.layout,
            rhs.compute
        );
    }


    static_assert(sizeof(DeviceDescriptor) == sizeof(WGPUDeviceDescriptor), "sizeof mismatch for DeviceDescriptor");
    static_assert(alignof(DeviceDescriptor) == alignof(WGPUDeviceDescriptor), "alignof mismatch for DeviceDescriptor");

    static_assert(offsetof(DeviceDescriptor, nextInChain) == offsetof(WGPUDeviceDescriptor, nextInChain),
            "offsetof mismatch for DeviceDescriptor::nextInChain");
    static_assert(offsetof(DeviceDescriptor, label) == offsetof(WGPUDeviceDescriptor, label),
            "offsetof mismatch for DeviceDescriptor::label");
    static_assert(offsetof(DeviceDescriptor, requiredFeaturesCount) == offsetof(WGPUDeviceDescriptor, requiredFeaturesCount),
            "offsetof mismatch for DeviceDescriptor::requiredFeaturesCount");
    static_assert(offsetof(DeviceDescriptor, requiredFeatures) == offsetof(WGPUDeviceDescriptor, requiredFeatures),
            "offsetof mismatch for DeviceDescriptor::requiredFeatures");
    static_assert(offsetof(DeviceDescriptor, requiredLimits) == offsetof(WGPUDeviceDescriptor, requiredLimits),
            "offsetof mismatch for DeviceDescriptor::requiredLimits");
    static_assert(offsetof(DeviceDescriptor, defaultQueue) == offsetof(WGPUDeviceDescriptor, defaultQueue),
            "offsetof mismatch for DeviceDescriptor::defaultQueue");

    bool DeviceDescriptor::operator==(const DeviceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            requiredFeaturesCount,
            requiredFeatures,
            requiredLimits,
            defaultQueue
        ) == std::tie(
            rhs.label,
            rhs.requiredFeaturesCount,
            rhs.requiredFeatures,
            rhs.requiredLimits,
            rhs.defaultQueue
        );
    }


    static_assert(sizeof(RenderPassDescriptor) == sizeof(WGPURenderPassDescriptor), "sizeof mismatch for RenderPassDescriptor");
    static_assert(alignof(RenderPassDescriptor) == alignof(WGPURenderPassDescriptor), "alignof mismatch for RenderPassDescriptor");

    static_assert(offsetof(RenderPassDescriptor, nextInChain) == offsetof(WGPURenderPassDescriptor, nextInChain),
            "offsetof mismatch for RenderPassDescriptor::nextInChain");
    static_assert(offsetof(RenderPassDescriptor, label) == offsetof(WGPURenderPassDescriptor, label),
            "offsetof mismatch for RenderPassDescriptor::label");
    static_assert(offsetof(RenderPassDescriptor, colorAttachmentCount) == offsetof(WGPURenderPassDescriptor, colorAttachmentCount),
            "offsetof mismatch for RenderPassDescriptor::colorAttachmentCount");
    static_assert(offsetof(RenderPassDescriptor, colorAttachments) == offsetof(WGPURenderPassDescriptor, colorAttachments),
            "offsetof mismatch for RenderPassDescriptor::colorAttachments");
    static_assert(offsetof(RenderPassDescriptor, depthStencilAttachment) == offsetof(WGPURenderPassDescriptor, depthStencilAttachment),
            "offsetof mismatch for RenderPassDescriptor::depthStencilAttachment");
    static_assert(offsetof(RenderPassDescriptor, occlusionQuerySet) == offsetof(WGPURenderPassDescriptor, occlusionQuerySet),
            "offsetof mismatch for RenderPassDescriptor::occlusionQuerySet");
    static_assert(offsetof(RenderPassDescriptor, timestampWriteCount) == offsetof(WGPURenderPassDescriptor, timestampWriteCount),
            "offsetof mismatch for RenderPassDescriptor::timestampWriteCount");
    static_assert(offsetof(RenderPassDescriptor, timestampWrites) == offsetof(WGPURenderPassDescriptor, timestampWrites),
            "offsetof mismatch for RenderPassDescriptor::timestampWrites");

    bool RenderPassDescriptor::operator==(const RenderPassDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            colorAttachmentCount,
            colorAttachments,
            depthStencilAttachment,
            occlusionQuerySet,
            timestampWriteCount,
            timestampWrites
        ) == std::tie(
            rhs.label,
            rhs.colorAttachmentCount,
            rhs.colorAttachments,
            rhs.depthStencilAttachment,
            rhs.occlusionQuerySet,
            rhs.timestampWriteCount,
            rhs.timestampWrites
        );
    }


    static_assert(sizeof(VertexState) == sizeof(WGPUVertexState), "sizeof mismatch for VertexState");
    static_assert(alignof(VertexState) == alignof(WGPUVertexState), "alignof mismatch for VertexState");

    static_assert(offsetof(VertexState, nextInChain) == offsetof(WGPUVertexState, nextInChain),
            "offsetof mismatch for VertexState::nextInChain");
    static_assert(offsetof(VertexState, module) == offsetof(WGPUVertexState, module),
            "offsetof mismatch for VertexState::module");
    static_assert(offsetof(VertexState, entryPoint) == offsetof(WGPUVertexState, entryPoint),
            "offsetof mismatch for VertexState::entryPoint");
    static_assert(offsetof(VertexState, constantCount) == offsetof(WGPUVertexState, constantCount),
            "offsetof mismatch for VertexState::constantCount");
    static_assert(offsetof(VertexState, constants) == offsetof(WGPUVertexState, constants),
            "offsetof mismatch for VertexState::constants");
    static_assert(offsetof(VertexState, bufferCount) == offsetof(WGPUVertexState, bufferCount),
            "offsetof mismatch for VertexState::bufferCount");
    static_assert(offsetof(VertexState, buffers) == offsetof(WGPUVertexState, buffers),
            "offsetof mismatch for VertexState::buffers");

    bool VertexState::operator==(const VertexState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            module,
            entryPoint,
            constantCount,
            constants,
            bufferCount,
            buffers
        ) == std::tie(
            rhs.module,
            rhs.entryPoint,
            rhs.constantCount,
            rhs.constants,
            rhs.bufferCount,
            rhs.buffers
        );
    }


    static_assert(sizeof(FragmentState) == sizeof(WGPUFragmentState), "sizeof mismatch for FragmentState");
    static_assert(alignof(FragmentState) == alignof(WGPUFragmentState), "alignof mismatch for FragmentState");

    static_assert(offsetof(FragmentState, nextInChain) == offsetof(WGPUFragmentState, nextInChain),
            "offsetof mismatch for FragmentState::nextInChain");
    static_assert(offsetof(FragmentState, module) == offsetof(WGPUFragmentState, module),
            "offsetof mismatch for FragmentState::module");
    static_assert(offsetof(FragmentState, entryPoint) == offsetof(WGPUFragmentState, entryPoint),
            "offsetof mismatch for FragmentState::entryPoint");
    static_assert(offsetof(FragmentState, constantCount) == offsetof(WGPUFragmentState, constantCount),
            "offsetof mismatch for FragmentState::constantCount");
    static_assert(offsetof(FragmentState, constants) == offsetof(WGPUFragmentState, constants),
            "offsetof mismatch for FragmentState::constants");
    static_assert(offsetof(FragmentState, targetCount) == offsetof(WGPUFragmentState, targetCount),
            "offsetof mismatch for FragmentState::targetCount");
    static_assert(offsetof(FragmentState, targets) == offsetof(WGPUFragmentState, targets),
            "offsetof mismatch for FragmentState::targets");

    bool FragmentState::operator==(const FragmentState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            module,
            entryPoint,
            constantCount,
            constants,
            targetCount,
            targets
        ) == std::tie(
            rhs.module,
            rhs.entryPoint,
            rhs.constantCount,
            rhs.constants,
            rhs.targetCount,
            rhs.targets
        );
    }


    static_assert(sizeof(RenderPipelineDescriptor) == sizeof(WGPURenderPipelineDescriptor), "sizeof mismatch for RenderPipelineDescriptor");
    static_assert(alignof(RenderPipelineDescriptor) == alignof(WGPURenderPipelineDescriptor), "alignof mismatch for RenderPipelineDescriptor");

    static_assert(offsetof(RenderPipelineDescriptor, nextInChain) == offsetof(WGPURenderPipelineDescriptor, nextInChain),
            "offsetof mismatch for RenderPipelineDescriptor::nextInChain");
    static_assert(offsetof(RenderPipelineDescriptor, label) == offsetof(WGPURenderPipelineDescriptor, label),
            "offsetof mismatch for RenderPipelineDescriptor::label");
    static_assert(offsetof(RenderPipelineDescriptor, layout) == offsetof(WGPURenderPipelineDescriptor, layout),
            "offsetof mismatch for RenderPipelineDescriptor::layout");
    static_assert(offsetof(RenderPipelineDescriptor, vertex) == offsetof(WGPURenderPipelineDescriptor, vertex),
            "offsetof mismatch for RenderPipelineDescriptor::vertex");
    static_assert(offsetof(RenderPipelineDescriptor, primitive) == offsetof(WGPURenderPipelineDescriptor, primitive),
            "offsetof mismatch for RenderPipelineDescriptor::primitive");
    static_assert(offsetof(RenderPipelineDescriptor, depthStencil) == offsetof(WGPURenderPipelineDescriptor, depthStencil),
            "offsetof mismatch for RenderPipelineDescriptor::depthStencil");
    static_assert(offsetof(RenderPipelineDescriptor, multisample) == offsetof(WGPURenderPipelineDescriptor, multisample),
            "offsetof mismatch for RenderPipelineDescriptor::multisample");
    static_assert(offsetof(RenderPipelineDescriptor, fragment) == offsetof(WGPURenderPipelineDescriptor, fragment),
            "offsetof mismatch for RenderPipelineDescriptor::fragment");

    bool RenderPipelineDescriptor::operator==(const RenderPipelineDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            layout,
            vertex,
            primitive,
            depthStencil,
            multisample,
            fragment
        ) == std::tie(
            rhs.label,
            rhs.layout,
            rhs.vertex,
            rhs.primitive,
            rhs.depthStencil,
            rhs.multisample,
            rhs.fragment
        );
    }

} // namespace dawn::native
