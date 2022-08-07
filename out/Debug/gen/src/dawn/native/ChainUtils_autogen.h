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
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromMetalLayer** out);
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWindowsHWND** out);
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromXlibWindow** out);
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromCanvasHTMLSelector** out);
    void FindInChain(const ChainedStruct* chain, const ShaderModuleSPIRVDescriptor** out);
    void FindInChain(const ChainedStruct* chain, const ShaderModuleWGSLDescriptor** out);
    void FindInChain(const ChainedStruct* chain, const PrimitiveDepthClipControl** out);
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWaylandSurface** out);
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromAndroidNativeWindow** out);
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWindowsCoreWindow** out);
    void FindInChain(const ChainedStruct* chain, const ExternalTextureBindingEntry** out);
    void FindInChain(const ChainedStruct* chain, const ExternalTextureBindingLayout** out);
    void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWindowsSwapChainPanel** out);
    void FindInChain(const ChainedStruct* chain, const RenderPassDescriptorMaxDrawCount** out);
    void FindInChain(const ChainedStruct* chain, const DawnTextureInternalUsageDescriptor** out);
    void FindInChain(const ChainedStruct* chain, const DawnTogglesDeviceDescriptor** out);
    void FindInChain(const ChainedStruct* chain, const DawnEncoderInternalUsageDescriptor** out);
    void FindInChain(const ChainedStruct* chain, const DawnInstanceDescriptor** out);
    void FindInChain(const ChainedStruct* chain, const DawnCacheDeviceDescriptor** out);

    // Verifies that |chain| only contains ChainedStructs of types enumerated in
    // |oneOfConstraints| and contains no duplicate sTypes. Each vector in
    // |oneOfConstraints| defines a set of sTypes that cannot coexist in the same chain.
    // For example:
    //   ValidateSTypes(chain, { { ShaderModuleSPIRVDescriptor, ShaderModuleWGSLDescriptor } }))
    //   ValidateSTypes(chain, { { Extension1 }, { Extension2 } })
    MaybeError ValidateSTypes(const ChainedStruct* chain,
                              std::vector<std::vector<wgpu::SType>> oneOfConstraints);

    template <typename T>
    MaybeError ValidateSingleSTypeInner(const ChainedStruct* chain, T sType) {
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

}  // namespace dawn::native

#endif  // DAWNNATIVE_CHAIN_UTILS_H_
