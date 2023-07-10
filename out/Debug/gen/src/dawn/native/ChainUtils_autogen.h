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

    template <typename T>
    inline wgpu::SType STypeFor;

    // Specialize STypeFor to map from native struct types to their SType.
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromMetalLayer> = wgpu::SType::SurfaceDescriptorFromMetalLayer;
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromWindowsHWND> = wgpu::SType::SurfaceDescriptorFromWindowsHWND;
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromXlibWindow> = wgpu::SType::SurfaceDescriptorFromXlibWindow;
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromCanvasHTMLSelector> = wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector;
    template <>
    inline wgpu::SType STypeFor<ShaderModuleSPIRVDescriptor> = wgpu::SType::ShaderModuleSPIRVDescriptor;
    template <>
    inline wgpu::SType STypeFor<ShaderModuleWGSLDescriptor> = wgpu::SType::ShaderModuleWGSLDescriptor;
    template <>
    inline wgpu::SType STypeFor<PrimitiveDepthClipControl> = wgpu::SType::PrimitiveDepthClipControl;
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromWaylandSurface> = wgpu::SType::SurfaceDescriptorFromWaylandSurface;
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromAndroidNativeWindow> = wgpu::SType::SurfaceDescriptorFromAndroidNativeWindow;
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromWindowsCoreWindow> = wgpu::SType::SurfaceDescriptorFromWindowsCoreWindow;
    template <>
    inline wgpu::SType STypeFor<ExternalTextureBindingEntry> = wgpu::SType::ExternalTextureBindingEntry;
    template <>
    inline wgpu::SType STypeFor<ExternalTextureBindingLayout> = wgpu::SType::ExternalTextureBindingLayout;
    template <>
    inline wgpu::SType STypeFor<SurfaceDescriptorFromWindowsSwapChainPanel> = wgpu::SType::SurfaceDescriptorFromWindowsSwapChainPanel;
    template <>
    inline wgpu::SType STypeFor<RenderPassDescriptorMaxDrawCount> = wgpu::SType::RenderPassDescriptorMaxDrawCount;
    template <>
    inline wgpu::SType STypeFor<DawnTextureInternalUsageDescriptor> = wgpu::SType::DawnTextureInternalUsageDescriptor;
    template <>
    inline wgpu::SType STypeFor<DawnEncoderInternalUsageDescriptor> = wgpu::SType::DawnEncoderInternalUsageDescriptor;
    template <>
    inline wgpu::SType STypeFor<DawnCacheDeviceDescriptor> = wgpu::SType::DawnCacheDeviceDescriptor;
    template <>
    inline wgpu::SType STypeFor<DawnAdapterPropertiesPowerPreference> = wgpu::SType::DawnAdapterPropertiesPowerPreference;
    template <>
    inline wgpu::SType STypeFor<DawnBufferDescriptorErrorInfoFromWireClient> = wgpu::SType::DawnBufferDescriptorErrorInfoFromWireClient;
    template <>
    inline wgpu::SType STypeFor<DawnTogglesDescriptor> = wgpu::SType::DawnTogglesDescriptor;
    template <>
    inline wgpu::SType STypeFor<DawnShaderModuleSPIRVOptionsDescriptor> = wgpu::SType::DawnShaderModuleSPIRVOptionsDescriptor;
    template <>
    inline wgpu::SType STypeFor<DawnMultisampleStateRenderToSingleSampled> = wgpu::SType::DawnMultisampleStateRenderToSingleSampled;
    template <>
    inline wgpu::SType STypeFor<DawnRenderPassColorAttachmentRenderToSingleSampled> = wgpu::SType::DawnRenderPassColorAttachmentRenderToSingleSampled;

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
