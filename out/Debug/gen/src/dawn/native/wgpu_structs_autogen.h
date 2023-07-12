
#ifndef DAWNNATIVE_WGPU_STRUCTS_H_
#define DAWNNATIVE_WGPU_STRUCTS_H_

#include "dawn/webgpu_cpp.h"
#include "dawn/native/Forward.h"
#include <cmath>

namespace dawn::native {


    using wgpu::ChainedStruct;
    using wgpu::ChainedStructOut;

    struct AdapterProperties {
        ChainedStructOut * nextInChain = nullptr;
        uint32_t vendorID;
        char const * vendorName;
        char const * architecture;
        uint32_t deviceID;
        char const * name;
        char const * driverDescription;
        wgpu::AdapterType adapterType;
        wgpu::BackendType backendType;
        bool compatibilityMode = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterProperties& rhs) const;
    };

    struct BindGroupEntry {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t binding;
        BufferBase* buffer = nullptr;
        uint64_t offset = 0;
        uint64_t size = WGPU_WHOLE_SIZE;
        SamplerBase* sampler = nullptr;
        TextureViewBase* textureView = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupEntry& rhs) const;
    };

    struct BlendComponent {
        wgpu::BlendOperation operation = wgpu::BlendOperation::Add;
        wgpu::BlendFactor srcFactor = wgpu::BlendFactor::One;
        wgpu::BlendFactor dstFactor = wgpu::BlendFactor::Zero;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BlendComponent& rhs) const;
    };

    struct BufferBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::BufferBindingType type = wgpu::BufferBindingType::Undefined;
        bool hasDynamicOffset = false;
        uint64_t minBindingSize = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BufferBindingLayout& rhs) const;
    };

    struct BufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::BufferUsage usage;
        uint64_t size;
        bool mappedAtCreation = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BufferDescriptor& rhs) const;
    };

    struct Color {
        double r;
        double g;
        double b;
        double a;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Color& rhs) const;
    };

    struct CommandBufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CommandBufferDescriptor& rhs) const;
    };

    struct CommandEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CommandEncoderDescriptor& rhs) const;
    };

    struct CompilationMessage {
        ChainedStruct const * nextInChain = nullptr;
        char const * message = nullptr;
        wgpu::CompilationMessageType type;
        uint64_t lineNum;
        uint64_t linePos;
        uint64_t offset;
        uint64_t length;
        uint64_t utf16LinePos;
        uint64_t utf16Offset;
        uint64_t utf16Length;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CompilationMessage& rhs) const;
    };

    struct ComputePassTimestampWrite {
        QuerySetBase* querySet;
        uint32_t queryIndex;
        wgpu::ComputePassTimestampLocation location;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ComputePassTimestampWrite& rhs) const;
    };

    struct ConstantEntry {
        ChainedStruct const * nextInChain = nullptr;
        char const * key;
        double value;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ConstantEntry& rhs) const;
    };

    struct CopyTextureForBrowserOptions {
        ChainedStruct const * nextInChain = nullptr;
        bool flipY = false;
        bool needsColorSpaceConversion = false;
        wgpu::AlphaMode srcAlphaMode = wgpu::AlphaMode::Unpremultiplied;
        float const * srcTransferFunctionParameters = nullptr;
        float const * conversionMatrix = nullptr;
        float const * dstTransferFunctionParameters = nullptr;
        wgpu::AlphaMode dstAlphaMode = wgpu::AlphaMode::Unpremultiplied;
        bool internalUsage = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CopyTextureForBrowserOptions& rhs) const;
    };

    struct DawnAdapterPropertiesPowerPreference : ChainedStructOut {
        DawnAdapterPropertiesPowerPreference() {
            sType = wgpu::SType::DawnAdapterPropertiesPowerPreference;
        }
        alignas(wgpu::DawnAdapterPropertiesPowerPreference::kFirstMemberAlignment) wgpu::PowerPreference powerPreference = wgpu::PowerPreference::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnAdapterPropertiesPowerPreference& rhs) const;
    };

    struct DawnBufferDescriptorErrorInfoFromWireClient : ChainedStruct {
        DawnBufferDescriptorErrorInfoFromWireClient() {
            sType = wgpu::SType::DawnBufferDescriptorErrorInfoFromWireClient;
        }
        alignas(wgpu::DawnBufferDescriptorErrorInfoFromWireClient::kFirstMemberAlignment) bool outOfMemory = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnBufferDescriptorErrorInfoFromWireClient& rhs) const;
    };

    struct DawnCacheDeviceDescriptor : ChainedStruct {
        DawnCacheDeviceDescriptor() {
            sType = wgpu::SType::DawnCacheDeviceDescriptor;
        }
        alignas(wgpu::DawnCacheDeviceDescriptor::kFirstMemberAlignment) char const * isolationKey = "";

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnCacheDeviceDescriptor& rhs) const;
    };

    struct DawnEncoderInternalUsageDescriptor : ChainedStruct {
        DawnEncoderInternalUsageDescriptor() {
            sType = wgpu::SType::DawnEncoderInternalUsageDescriptor;
        }
        alignas(wgpu::DawnEncoderInternalUsageDescriptor::kFirstMemberAlignment) bool useInternalUsages = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnEncoderInternalUsageDescriptor& rhs) const;
    };

    struct DawnMultisampleStateRenderToSingleSampled : ChainedStruct {
        DawnMultisampleStateRenderToSingleSampled() {
            sType = wgpu::SType::DawnMultisampleStateRenderToSingleSampled;
        }
        alignas(wgpu::DawnMultisampleStateRenderToSingleSampled::kFirstMemberAlignment) bool enabled = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnMultisampleStateRenderToSingleSampled& rhs) const;
    };

    struct DawnRenderPassColorAttachmentRenderToSingleSampled : ChainedStruct {
        DawnRenderPassColorAttachmentRenderToSingleSampled() {
            sType = wgpu::SType::DawnRenderPassColorAttachmentRenderToSingleSampled;
        }
        alignas(wgpu::DawnRenderPassColorAttachmentRenderToSingleSampled::kFirstMemberAlignment) uint32_t implicitSampleCount = 1;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnRenderPassColorAttachmentRenderToSingleSampled& rhs) const;
    };

    struct DawnShaderModuleSPIRVOptionsDescriptor : ChainedStruct {
        DawnShaderModuleSPIRVOptionsDescriptor() {
            sType = wgpu::SType::DawnShaderModuleSPIRVOptionsDescriptor;
        }
        alignas(wgpu::DawnShaderModuleSPIRVOptionsDescriptor::kFirstMemberAlignment) bool allowNonUniformDerivatives = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnShaderModuleSPIRVOptionsDescriptor& rhs) const;
    };

    struct DawnTextureInternalUsageDescriptor : ChainedStruct {
        DawnTextureInternalUsageDescriptor() {
            sType = wgpu::SType::DawnTextureInternalUsageDescriptor;
        }
        alignas(wgpu::DawnTextureInternalUsageDescriptor::kFirstMemberAlignment) wgpu::TextureUsage internalUsage = wgpu::TextureUsage::None;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnTextureInternalUsageDescriptor& rhs) const;
    };

    struct DawnTogglesDescriptor : ChainedStruct {
        DawnTogglesDescriptor() {
            sType = wgpu::SType::DawnTogglesDescriptor;
        }
        alignas(wgpu::DawnTogglesDescriptor::kFirstMemberAlignment) size_t enabledTogglesCount = 0;
        const char* const * enabledToggles;
        size_t disabledTogglesCount = 0;
        const char* const * disabledToggles;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnTogglesDescriptor& rhs) const;
    };

    struct Extent2D {
        uint32_t width = 0;
        uint32_t height = 1;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Extent2D& rhs) const;
    };

    struct Extent3D {
        uint32_t width;
        uint32_t height = 1;
        uint32_t depthOrArrayLayers = 1;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Extent3D& rhs) const;
    };

    struct ExternalTextureBindingEntry : ChainedStruct {
        ExternalTextureBindingEntry() {
            sType = wgpu::SType::ExternalTextureBindingEntry;
        }
        alignas(wgpu::ExternalTextureBindingEntry::kFirstMemberAlignment) ExternalTextureBase* externalTexture;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ExternalTextureBindingEntry& rhs) const;
    };

    struct ExternalTextureBindingLayout : ChainedStruct {
        ExternalTextureBindingLayout() {
            sType = wgpu::SType::ExternalTextureBindingLayout;
        }

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ExternalTextureBindingLayout& rhs) const;
    };

    struct InstanceDescriptor {
        ChainedStruct const * nextInChain = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const InstanceDescriptor& rhs) const;
    };

    struct Limits {
        uint32_t maxTextureDimension1D = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxTextureDimension2D = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxTextureDimension3D = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxTextureArrayLayers = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxBindGroups = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxBindGroupsPlusVertexBuffers = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxBindingsPerBindGroup = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxDynamicUniformBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxDynamicStorageBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxSampledTexturesPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxSamplersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxStorageBuffersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxStorageTexturesPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxUniformBuffersPerShaderStage = WGPU_LIMIT_U32_UNDEFINED;
        uint64_t maxUniformBufferBindingSize = WGPU_LIMIT_U64_UNDEFINED;
        uint64_t maxStorageBufferBindingSize = WGPU_LIMIT_U64_UNDEFINED;
        uint32_t minUniformBufferOffsetAlignment = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t minStorageBufferOffsetAlignment = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxVertexBuffers = WGPU_LIMIT_U32_UNDEFINED;
        uint64_t maxBufferSize = WGPU_LIMIT_U64_UNDEFINED;
        uint32_t maxVertexAttributes = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxVertexBufferArrayStride = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxInterStageShaderComponents = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxInterStageShaderVariables = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxColorAttachments = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxColorAttachmentBytesPerSample = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupStorageSize = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeInvocationsPerWorkgroup = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupSizeX = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupSizeY = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupSizeZ = WGPU_LIMIT_U32_UNDEFINED;
        uint32_t maxComputeWorkgroupsPerDimension = WGPU_LIMIT_U32_UNDEFINED;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Limits& rhs) const;
    };

    struct MultisampleState {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t count = 1;
        uint32_t mask = 0xFFFFFFFF;
        bool alphaToCoverageEnabled = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const MultisampleState& rhs) const;
    };

    struct Origin2D {
        uint32_t x = 0;
        uint32_t y = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Origin2D& rhs) const;
    };

    struct Origin3D {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t z = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Origin3D& rhs) const;
    };

    struct PipelineLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t bindGroupLayoutCount;
        BindGroupLayoutBase* const * bindGroupLayouts;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PipelineLayoutDescriptor& rhs) const;
    };

    struct PrimitiveDepthClipControl : ChainedStruct {
        PrimitiveDepthClipControl() {
            sType = wgpu::SType::PrimitiveDepthClipControl;
        }
        alignas(wgpu::PrimitiveDepthClipControl::kFirstMemberAlignment) bool unclippedDepth = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PrimitiveDepthClipControl& rhs) const;
    };

    struct PrimitiveState {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::PrimitiveTopology topology = wgpu::PrimitiveTopology::TriangleList;
        wgpu::IndexFormat stripIndexFormat = wgpu::IndexFormat::Undefined;
        wgpu::FrontFace frontFace = wgpu::FrontFace::CCW;
        wgpu::CullMode cullMode = wgpu::CullMode::None;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PrimitiveState& rhs) const;
    };

    struct QuerySetDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::QueryType type;
        uint32_t count;
        wgpu::PipelineStatisticName const * pipelineStatistics;
        size_t pipelineStatisticsCount = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const QuerySetDescriptor& rhs) const;
    };

    struct QueueDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const QueueDescriptor& rhs) const;
    };

    struct RenderBundleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderBundleDescriptor& rhs) const;
    };

    struct RenderBundleEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t colorFormatsCount;
        wgpu::TextureFormat const * colorFormats;
        wgpu::TextureFormat depthStencilFormat = wgpu::TextureFormat::Undefined;
        uint32_t sampleCount = 1;
        bool depthReadOnly = false;
        bool stencilReadOnly = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderBundleEncoderDescriptor& rhs) const;
    };

    struct RenderPassDepthStencilAttachment {
        TextureViewBase* view;
        wgpu::LoadOp depthLoadOp = wgpu::LoadOp::Undefined;
        wgpu::StoreOp depthStoreOp = wgpu::StoreOp::Undefined;
        float depthClearValue = NAN;
        bool depthReadOnly = false;
        wgpu::LoadOp stencilLoadOp = wgpu::LoadOp::Undefined;
        wgpu::StoreOp stencilStoreOp = wgpu::StoreOp::Undefined;
        uint32_t stencilClearValue = 0;
        bool stencilReadOnly = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassDepthStencilAttachment& rhs) const;
    };

    struct RenderPassDescriptorMaxDrawCount : ChainedStruct {
        RenderPassDescriptorMaxDrawCount() {
            sType = wgpu::SType::RenderPassDescriptorMaxDrawCount;
        }
        alignas(wgpu::RenderPassDescriptorMaxDrawCount::kFirstMemberAlignment) uint64_t maxDrawCount = 50000000;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassDescriptorMaxDrawCount& rhs) const;
    };

    struct RenderPassTimestampWrite {
        QuerySetBase* querySet;
        uint32_t queryIndex;
        wgpu::RenderPassTimestampLocation location;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassTimestampWrite& rhs) const;
    };

    struct RequestAdapterOptions {
        ChainedStruct const * nextInChain = nullptr;
        SurfaceBase* compatibleSurface = nullptr;
        wgpu::PowerPreference powerPreference = wgpu::PowerPreference::Undefined;
        wgpu::BackendType backendType = wgpu::BackendType::Undefined;
        bool forceFallbackAdapter = false;
        bool compatibilityMode = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RequestAdapterOptions& rhs) const;
    };

    struct SamplerBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::SamplerBindingType type = wgpu::SamplerBindingType::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SamplerBindingLayout& rhs) const;
    };

    struct SamplerDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::AddressMode addressModeU = wgpu::AddressMode::ClampToEdge;
        wgpu::AddressMode addressModeV = wgpu::AddressMode::ClampToEdge;
        wgpu::AddressMode addressModeW = wgpu::AddressMode::ClampToEdge;
        wgpu::FilterMode magFilter = wgpu::FilterMode::Nearest;
        wgpu::FilterMode minFilter = wgpu::FilterMode::Nearest;
        wgpu::MipmapFilterMode mipmapFilter = wgpu::MipmapFilterMode::Nearest;
        float lodMinClamp = 0.0f;
        float lodMaxClamp = 32.0f;
        wgpu::CompareFunction compare = wgpu::CompareFunction::Undefined;
        uint16_t maxAnisotropy = 1;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SamplerDescriptor& rhs) const;
    };

    struct ShaderModuleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ShaderModuleDescriptor& rhs) const;
    };

    struct ShaderModuleSPIRVDescriptor : ChainedStruct {
        ShaderModuleSPIRVDescriptor() {
            sType = wgpu::SType::ShaderModuleSPIRVDescriptor;
        }
        alignas(wgpu::ShaderModuleSPIRVDescriptor::kFirstMemberAlignment) uint32_t codeSize;
        uint32_t const * code;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ShaderModuleSPIRVDescriptor& rhs) const;
    };

    struct ShaderModuleWGSLDescriptor : ChainedStruct {
        ShaderModuleWGSLDescriptor() {
            sType = wgpu::SType::ShaderModuleWGSLDescriptor;
        }
        alignas(wgpu::ShaderModuleWGSLDescriptor::kFirstMemberAlignment) char const * code;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ShaderModuleWGSLDescriptor& rhs) const;
    };

    struct StencilFaceState {
        wgpu::CompareFunction compare = wgpu::CompareFunction::Always;
        wgpu::StencilOperation failOp = wgpu::StencilOperation::Keep;
        wgpu::StencilOperation depthFailOp = wgpu::StencilOperation::Keep;
        wgpu::StencilOperation passOp = wgpu::StencilOperation::Keep;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const StencilFaceState& rhs) const;
    };

    struct StorageTextureBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::StorageTextureAccess access = wgpu::StorageTextureAccess::Undefined;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        wgpu::TextureViewDimension viewDimension = wgpu::TextureViewDimension::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const StorageTextureBindingLayout& rhs) const;
    };

    struct SurfaceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptor& rhs) const;
    };

    struct SurfaceDescriptorFromAndroidNativeWindow : ChainedStruct {
        SurfaceDescriptorFromAndroidNativeWindow() {
            sType = wgpu::SType::SurfaceDescriptorFromAndroidNativeWindow;
        }
        alignas(wgpu::SurfaceDescriptorFromAndroidNativeWindow::kFirstMemberAlignment) void * window;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromAndroidNativeWindow& rhs) const;
    };

    struct SurfaceDescriptorFromCanvasHTMLSelector : ChainedStruct {
        SurfaceDescriptorFromCanvasHTMLSelector() {
            sType = wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector;
        }
        alignas(wgpu::SurfaceDescriptorFromCanvasHTMLSelector::kFirstMemberAlignment) char const * selector;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromCanvasHTMLSelector& rhs) const;
    };

    struct SurfaceDescriptorFromMetalLayer : ChainedStruct {
        SurfaceDescriptorFromMetalLayer() {
            sType = wgpu::SType::SurfaceDescriptorFromMetalLayer;
        }
        alignas(wgpu::SurfaceDescriptorFromMetalLayer::kFirstMemberAlignment) void * layer;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromMetalLayer& rhs) const;
    };

    struct SurfaceDescriptorFromWaylandSurface : ChainedStruct {
        SurfaceDescriptorFromWaylandSurface() {
            sType = wgpu::SType::SurfaceDescriptorFromWaylandSurface;
        }
        alignas(wgpu::SurfaceDescriptorFromWaylandSurface::kFirstMemberAlignment) void * display;
        void * surface;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromWaylandSurface& rhs) const;
    };

    struct SurfaceDescriptorFromWindowsCoreWindow : ChainedStruct {
        SurfaceDescriptorFromWindowsCoreWindow() {
            sType = wgpu::SType::SurfaceDescriptorFromWindowsCoreWindow;
        }
        alignas(wgpu::SurfaceDescriptorFromWindowsCoreWindow::kFirstMemberAlignment) void * coreWindow;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromWindowsCoreWindow& rhs) const;
    };

    struct SurfaceDescriptorFromWindowsHWND : ChainedStruct {
        SurfaceDescriptorFromWindowsHWND() {
            sType = wgpu::SType::SurfaceDescriptorFromWindowsHWND;
        }
        alignas(wgpu::SurfaceDescriptorFromWindowsHWND::kFirstMemberAlignment) void * hinstance;
        void * hwnd;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromWindowsHWND& rhs) const;
    };

    struct SurfaceDescriptorFromWindowsSwapChainPanel : ChainedStruct {
        SurfaceDescriptorFromWindowsSwapChainPanel() {
            sType = wgpu::SType::SurfaceDescriptorFromWindowsSwapChainPanel;
        }
        alignas(wgpu::SurfaceDescriptorFromWindowsSwapChainPanel::kFirstMemberAlignment) void * swapChainPanel;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromWindowsSwapChainPanel& rhs) const;
    };

    struct SurfaceDescriptorFromXlibWindow : ChainedStruct {
        SurfaceDescriptorFromXlibWindow() {
            sType = wgpu::SType::SurfaceDescriptorFromXlibWindow;
        }
        alignas(wgpu::SurfaceDescriptorFromXlibWindow::kFirstMemberAlignment) void * display;
        uint32_t window;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromXlibWindow& rhs) const;
    };

    struct SwapChainDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::TextureUsage usage;
        wgpu::TextureFormat format;
        uint32_t width;
        uint32_t height;
        wgpu::PresentMode presentMode;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SwapChainDescriptor& rhs) const;
    };

    struct TextureBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureSampleType sampleType = wgpu::TextureSampleType::Undefined;
        wgpu::TextureViewDimension viewDimension = wgpu::TextureViewDimension::Undefined;
        bool multisampled = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureBindingLayout& rhs) const;
    };

    struct TextureDataLayout {
        ChainedStruct const * nextInChain = nullptr;
        uint64_t offset = 0;
        uint32_t bytesPerRow = WGPU_COPY_STRIDE_UNDEFINED;
        uint32_t rowsPerImage = WGPU_COPY_STRIDE_UNDEFINED;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureDataLayout& rhs) const;
    };

    struct TextureViewDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        wgpu::TextureViewDimension dimension = wgpu::TextureViewDimension::Undefined;
        uint32_t baseMipLevel = 0;
        uint32_t mipLevelCount = WGPU_MIP_LEVEL_COUNT_UNDEFINED;
        uint32_t baseArrayLayer = 0;
        uint32_t arrayLayerCount = WGPU_ARRAY_LAYER_COUNT_UNDEFINED;
        wgpu::TextureAspect aspect = wgpu::TextureAspect::All;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureViewDescriptor& rhs) const;
    };

    struct VertexAttribute {
        wgpu::VertexFormat format;
        uint64_t offset;
        uint32_t shaderLocation;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const VertexAttribute& rhs) const;
    };

    struct BindGroupDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        BindGroupLayoutBase* layout;
        size_t entryCount;
        BindGroupEntry const * entries;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupDescriptor& rhs) const;
    };

    struct BindGroupLayoutEntry {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t binding;
        wgpu::ShaderStage visibility;
        BufferBindingLayout buffer;
        SamplerBindingLayout sampler;
        TextureBindingLayout texture;
        StorageTextureBindingLayout storageTexture;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupLayoutEntry& rhs) const;
    };

    struct BlendState {
        BlendComponent color;
        BlendComponent alpha;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BlendState& rhs) const;
    };

    struct CompilationInfo {
        ChainedStruct const * nextInChain = nullptr;
        size_t messageCount;
        CompilationMessage const * messages;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CompilationInfo& rhs) const;
    };

    struct ComputePassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t timestampWriteCount = 0;
        ComputePassTimestampWrite const * timestampWrites;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ComputePassDescriptor& rhs) const;
    };

    struct DepthStencilState {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureFormat format;
        bool depthWriteEnabled;
        wgpu::CompareFunction depthCompare;
        StencilFaceState stencilFront;
        StencilFaceState stencilBack;
        uint32_t stencilReadMask = 0xFFFFFFFF;
        uint32_t stencilWriteMask = 0xFFFFFFFF;
        int32_t depthBias = 0;
        float depthBiasSlopeScale = 0.0f;
        float depthBiasClamp = 0.0f;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DepthStencilState& rhs) const;
    };

    struct ExternalTextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        TextureViewBase* plane0;
        TextureViewBase* plane1 = nullptr;
        Origin2D visibleOrigin;
        Extent2D visibleSize;
        bool doYuvToRgbConversionOnly = false;
        float const * yuvToRgbConversionMatrix = nullptr;
        float const * srcTransferFunctionParameters;
        float const * dstTransferFunctionParameters;
        float const * gamutConversionMatrix;
        bool flipY = false;
        wgpu::ExternalTextureRotation rotation = wgpu::ExternalTextureRotation::Rotate0Degrees;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ExternalTextureDescriptor& rhs) const;
    };

    struct ImageCopyBuffer {
        ChainedStruct const * nextInChain = nullptr;
        TextureDataLayout layout;
        BufferBase* buffer;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ImageCopyBuffer& rhs) const;
    };

    struct ImageCopyExternalTexture {
        ChainedStruct const * nextInChain = nullptr;
        ExternalTextureBase* externalTexture;
        Origin3D origin;
        Extent2D naturalSize;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ImageCopyExternalTexture& rhs) const;
    };

    struct ImageCopyTexture {
        ChainedStruct const * nextInChain = nullptr;
        TextureBase* texture;
        uint32_t mipLevel = 0;
        Origin3D origin;
        wgpu::TextureAspect aspect = wgpu::TextureAspect::All;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ImageCopyTexture& rhs) const;
    };

    struct ProgrammableStageDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModuleBase* module;
        char const * entryPoint;
        size_t constantCount = 0;
        ConstantEntry const * constants;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ProgrammableStageDescriptor& rhs) const;
    };

    struct RenderPassColorAttachment {
        ChainedStruct const * nextInChain = nullptr;
        TextureViewBase* view = nullptr;
        TextureViewBase* resolveTarget = nullptr;
        wgpu::LoadOp loadOp;
        wgpu::StoreOp storeOp;
        Color clearValue;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassColorAttachment& rhs) const;
    };

    struct RequiredLimits {
        ChainedStruct const * nextInChain = nullptr;
        Limits limits;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RequiredLimits& rhs) const;
    };

    struct SupportedLimits {
        ChainedStructOut * nextInChain = nullptr;
        Limits limits;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SupportedLimits& rhs) const;
    };

    struct TextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        wgpu::TextureUsage usage;
        wgpu::TextureDimension dimension = wgpu::TextureDimension::e2D;
        Extent3D size;
        wgpu::TextureFormat format;
        uint32_t mipLevelCount = 1;
        uint32_t sampleCount = 1;
        size_t viewFormatCount = 0;
        wgpu::TextureFormat const * viewFormats;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureDescriptor& rhs) const;
    };

    struct VertexBufferLayout {
        uint64_t arrayStride;
        wgpu::VertexStepMode stepMode = wgpu::VertexStepMode::Vertex;
        size_t attributeCount;
        VertexAttribute const * attributes;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const VertexBufferLayout& rhs) const;
    };

    struct BindGroupLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t entryCount;
        BindGroupLayoutEntry const * entries;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupLayoutDescriptor& rhs) const;
    };

    struct ColorTargetState {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureFormat format;
        BlendState const * blend = nullptr;
        wgpu::ColorWriteMask writeMask = wgpu::ColorWriteMask::All;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ColorTargetState& rhs) const;
    };

    struct ComputePipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayoutBase* layout = nullptr;
        ProgrammableStageDescriptor compute;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ComputePipelineDescriptor& rhs) const;
    };

    struct DeviceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t requiredFeaturesCount = 0;
        wgpu::FeatureName const * requiredFeatures = nullptr;
        RequiredLimits const * requiredLimits = nullptr;
        QueueDescriptor defaultQueue;
        WGPUDeviceLostCallback deviceLostCallback = nullptr;
        void * deviceLostUserdata = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DeviceDescriptor& rhs) const;
    };

    struct RenderPassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        size_t colorAttachmentCount;
        RenderPassColorAttachment const * colorAttachments;
        RenderPassDepthStencilAttachment const * depthStencilAttachment = nullptr;
        QuerySetBase* occlusionQuerySet = nullptr;
        size_t timestampWriteCount = 0;
        RenderPassTimestampWrite const * timestampWrites;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassDescriptor& rhs) const;
    };

    struct VertexState {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModuleBase* module;
        char const * entryPoint;
        size_t constantCount = 0;
        ConstantEntry const * constants;
        size_t bufferCount = 0;
        VertexBufferLayout const * buffers;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const VertexState& rhs) const;
    };

    struct FragmentState {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModuleBase* module;
        char const * entryPoint;
        size_t constantCount = 0;
        ConstantEntry const * constants;
        size_t targetCount;
        ColorTargetState const * targets;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const FragmentState& rhs) const;
    };

    struct RenderPipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        char const * label = nullptr;
        PipelineLayoutBase* layout = nullptr;
        VertexState vertex;
        PrimitiveState primitive;
        DepthStencilState const * depthStencil = nullptr;
        MultisampleState multisample;
        FragmentState const * fragment = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPipelineDescriptor& rhs) const;
    };



} // namespace dawn::native

#endif  // DAWNNATIVE_WGPU_STRUCTS_H_
