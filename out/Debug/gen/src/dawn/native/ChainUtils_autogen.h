// Copyright 2021 The Dawn Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DAWNNATIVE_CHAIN_UTILS_H_
#define DAWNNATIVE_CHAIN_UTILS_H_

#include "dawn/native/dawn_platform.h"
#include "dawn/native/Error.h"

namespace dawn::native {
namespace detail {
    // Mapping from native types to the expected STypes is implemented as template specializations.
    template <typename T>
    struct STypeForImpl;
    template <>
    struct STypeForImpl<SurfaceDescriptorFromMetalLayer> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromMetalLayer;
    };
    template <>
    struct STypeForImpl<SurfaceDescriptorFromWindowsHWND> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromWindowsHWND;
    };
    template <>
    struct STypeForImpl<SurfaceDescriptorFromXlibWindow> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromXlibWindow;
    };
    template <>
    struct STypeForImpl<SurfaceDescriptorFromCanvasHTMLSelector> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector;
    };
    template <>
    struct STypeForImpl<ShaderModuleSPIRVDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::ShaderModuleSPIRVDescriptor;
    };
    template <>
    struct STypeForImpl<ShaderModuleWGSLDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::ShaderModuleWGSLDescriptor;
    };
    template <>
    struct STypeForImpl<PrimitiveDepthClipControl> {
        static constexpr wgpu::SType value = wgpu::SType::PrimitiveDepthClipControl;
    };
    template <>
    struct STypeForImpl<SurfaceDescriptorFromWaylandSurface> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromWaylandSurface;
    };
    template <>
    struct STypeForImpl<SurfaceDescriptorFromAndroidNativeWindow> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromAndroidNativeWindow;
    };
    template <>
    struct STypeForImpl<SurfaceDescriptorFromWindowsCoreWindow> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromWindowsCoreWindow;
    };
    template <>
    struct STypeForImpl<ExternalTextureBindingEntry> {
        static constexpr wgpu::SType value = wgpu::SType::ExternalTextureBindingEntry;
    };
    template <>
    struct STypeForImpl<ExternalTextureBindingLayout> {
        static constexpr wgpu::SType value = wgpu::SType::ExternalTextureBindingLayout;
    };
    template <>
    struct STypeForImpl<SurfaceDescriptorFromWindowsSwapChainPanel> {
        static constexpr wgpu::SType value = wgpu::SType::SurfaceDescriptorFromWindowsSwapChainPanel;
    };
    template <>
    struct STypeForImpl<RenderPassDescriptorMaxDrawCount> {
        static constexpr wgpu::SType value = wgpu::SType::RenderPassDescriptorMaxDrawCount;
    };
    template <>
    struct STypeForImpl<DawnTextureInternalUsageDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::DawnTextureInternalUsageDescriptor;
    };
    template <>
    struct STypeForImpl<DawnEncoderInternalUsageDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::DawnEncoderInternalUsageDescriptor;
    };
    template <>
    struct STypeForImpl<DawnCacheDeviceDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::DawnCacheDeviceDescriptor;
    };
    template <>
    struct STypeForImpl<DawnAdapterPropertiesPowerPreference> {
        static constexpr wgpu::SType value = wgpu::SType::DawnAdapterPropertiesPowerPreference;
    };
    template <>
    struct STypeForImpl<DawnBufferDescriptorErrorInfoFromWireClient> {
        static constexpr wgpu::SType value = wgpu::SType::DawnBufferDescriptorErrorInfoFromWireClient;
    };
    template <>
    struct STypeForImpl<DawnTogglesDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::DawnTogglesDescriptor;
    };
    template <>
    struct STypeForImpl<DawnShaderModuleSPIRVOptionsDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::DawnShaderModuleSPIRVOptionsDescriptor;
    };
    template <>
    struct STypeForImpl<DawnInstanceDescriptor> {
        static constexpr wgpu::SType value = wgpu::SType::DawnInstanceDescriptor;
    };
}  // namespace detail

    template <typename T>
    constexpr wgpu::SType STypeFor = detail::STypeForImpl<T>::value;
    template <typename T>
    void FindInChain(const ChainedStruct* chain, const T** out) {
        for (; chain; chain = chain->nextInChain) {
            if (chain->sType == STypeFor<T>) {
                *out = static_cast<const T*>(chain);
                break;
            }
        }
    }
    template <typename T>
    void FindInChain(ChainedStructOut* chain, T** out) {
        for (; chain; chain = chain->nextInChain) {
            if (chain->sType == STypeFor<T>) {
                *out = static_cast<T*>(chain);
                break;
            }
        }
    }

    // Verifies that |chain| only contains ChainedStructs of types enumerated in
    // |oneOfConstraints| and contains no duplicate sTypes. Each vector in
    // |oneOfConstraints| defines a set of sTypes that cannot coexist in the same chain.
    // For example:
    //   ValidateSTypes(chain, { { ShaderModuleSPIRVDescriptor, ShaderModuleWGSLDescriptor } }))
    //   ValidateSTypes(chain, { { Extension1 }, { Extension2 } })
    MaybeError ValidateSTypes(const ChainedStruct* chain,
                              std::vector<std::vector<wgpu::SType>> oneOfConstraints);
    MaybeError ValidateSTypes(const ChainedStructOut* chain,
                              std::vector<std::vector<wgpu::SType>> oneOfConstraints);

    template <typename T>
    MaybeError ValidateSingleSTypeInner(const ChainedStruct* chain, T sType) {
        DAWN_INVALID_IF(chain->sType != sType,
            "Unsupported sType (%s). Expected (%s)", chain->sType, sType);
        return {};
    }
    template <typename T>
    MaybeError ValidateSingleSTypeInner(const ChainedStructOut* chain, T sType) {
        DAWN_INVALID_IF(chain->sType != sType,
            "Unsupported sType (%s). Expected (%s)", chain->sType, sType);
        return {};
    }

    template <typename T, typename... Args>
    MaybeError ValidateSingleSTypeInner(const ChainedStruct* chain, T sType, Args... sTypes) {
        if (chain->sType == sType) {
            return {};
        }
        return ValidateSingleSTypeInner(chain, sTypes...);
    }
    template <typename T, typename... Args>
    MaybeError ValidateSingleSTypeInner(const ChainedStructOut* chain, T sType, Args... sTypes) {
        if (chain->sType == sType) {
            return {};
        }
        return ValidateSingleSTypeInner(chain, sTypes...);
    }

    // Verifies that |chain| contains a single ChainedStruct of type |sType| or no ChainedStructs
    // at all.
    template <typename T>
    MaybeError ValidateSingleSType(const ChainedStruct* chain, T sType) {
        if (chain == nullptr) {
            return {};
        }
        DAWN_INVALID_IF(chain->nextInChain != nullptr,
            "Chain can only contain a single chained struct.");
        return ValidateSingleSTypeInner(chain, sType);
    }
    template <typename T>
    MaybeError ValidateSingleSType(const ChainedStructOut* chain, T sType) {
        if (chain == nullptr) {
            return {};
        }
        DAWN_INVALID_IF(chain->nextInChain != nullptr,
            "Chain can only contain a single chained struct.");
        return ValidateSingleSTypeInner(chain, sType);
    }

    // Verifies that |chain| contains a single ChainedStruct with a type enumerated in the
    // parameter pack or no ChainedStructs at all.
    template <typename T, typename... Args>
    MaybeError ValidateSingleSType(const ChainedStruct* chain, T sType, Args... sTypes) {
        if (chain == nullptr) {
            return {};
        }
        DAWN_INVALID_IF(chain->nextInChain != nullptr,
            "Chain can only contain a single chained struct.");
        return ValidateSingleSTypeInner(chain, sType, sTypes...);
    }
    template <typename T, typename... Args>
    MaybeError ValidateSingleSType(const ChainedStructOut* chain, T sType, Args... sTypes) {
        if (chain == nullptr) {
            return {};
        }
        DAWN_INVALID_IF(chain->nextInChain != nullptr,
            "Chain can only contain a single chained struct.");
        return ValidateSingleSTypeInner(chain, sType, sTypes...);
    }

}  // namespace dawn::native

#endif  // DAWNNATIVE_CHAIN_UTILS_H_
