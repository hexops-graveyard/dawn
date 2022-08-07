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

#include "dawn/native/ChainUtils_autogen.h"

#include <unordered_set>

namespace dawn::native {

void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromMetalLayer** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromMetalLayer) {
            *out = static_cast<const SurfaceDescriptorFromMetalLayer*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWindowsHWND** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromWindowsHWND) {
            *out = static_cast<const SurfaceDescriptorFromWindowsHWND*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromXlibWindow** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromXlibWindow) {
            *out = static_cast<const SurfaceDescriptorFromXlibWindow*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromCanvasHTMLSelector** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromCanvasHTMLSelector) {
            *out = static_cast<const SurfaceDescriptorFromCanvasHTMLSelector*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const ShaderModuleSPIRVDescriptor** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::ShaderModuleSPIRVDescriptor) {
            *out = static_cast<const ShaderModuleSPIRVDescriptor*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const ShaderModuleWGSLDescriptor** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::ShaderModuleWGSLDescriptor) {
            *out = static_cast<const ShaderModuleWGSLDescriptor*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const PrimitiveDepthClipControl** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::PrimitiveDepthClipControl) {
            *out = static_cast<const PrimitiveDepthClipControl*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWaylandSurface** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromWaylandSurface) {
            *out = static_cast<const SurfaceDescriptorFromWaylandSurface*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromAndroidNativeWindow** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromAndroidNativeWindow) {
            *out = static_cast<const SurfaceDescriptorFromAndroidNativeWindow*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWindowsCoreWindow** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromWindowsCoreWindow) {
            *out = static_cast<const SurfaceDescriptorFromWindowsCoreWindow*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const ExternalTextureBindingEntry** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::ExternalTextureBindingEntry) {
            *out = static_cast<const ExternalTextureBindingEntry*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const ExternalTextureBindingLayout** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::ExternalTextureBindingLayout) {
            *out = static_cast<const ExternalTextureBindingLayout*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const SurfaceDescriptorFromWindowsSwapChainPanel** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::SurfaceDescriptorFromWindowsSwapChainPanel) {
            *out = static_cast<const SurfaceDescriptorFromWindowsSwapChainPanel*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const RenderPassDescriptorMaxDrawCount** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::RenderPassDescriptorMaxDrawCount) {
            *out = static_cast<const RenderPassDescriptorMaxDrawCount*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const DawnTextureInternalUsageDescriptor** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::DawnTextureInternalUsageDescriptor) {
            *out = static_cast<const DawnTextureInternalUsageDescriptor*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const DawnTogglesDeviceDescriptor** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::DawnTogglesDeviceDescriptor) {
            *out = static_cast<const DawnTogglesDeviceDescriptor*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const DawnEncoderInternalUsageDescriptor** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::DawnEncoderInternalUsageDescriptor) {
            *out = static_cast<const DawnEncoderInternalUsageDescriptor*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const DawnInstanceDescriptor** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::DawnInstanceDescriptor) {
            *out = static_cast<const DawnInstanceDescriptor*>(chain);
            break;
        }
    }
}
void FindInChain(const ChainedStruct* chain, const DawnCacheDeviceDescriptor** out) {
    for (; chain; chain = chain->nextInChain) {
        if (chain->sType == wgpu::SType::DawnCacheDeviceDescriptor) {
            *out = static_cast<const DawnCacheDeviceDescriptor*>(chain);
            break;
        }
    }
}

MaybeError ValidateSTypes(const ChainedStruct* chain,
                          std::vector<std::vector<wgpu::SType>> oneOfConstraints) {
    std::unordered_set<wgpu::SType> allSTypes;
    for (; chain; chain = chain->nextInChain) {
        if (allSTypes.find(chain->sType) != allSTypes.end()) {
            return DAWN_VALIDATION_ERROR("Chain cannot have duplicate sTypes");
        }
        allSTypes.insert(chain->sType);
    }
    for (const auto& oneOfConstraint : oneOfConstraints) {
        bool satisfied = false;
        for (wgpu::SType oneOfSType : oneOfConstraint) {
            if (allSTypes.find(oneOfSType) != allSTypes.end()) {
                if (satisfied) {
                    return DAWN_VALIDATION_ERROR("Unsupported sType combination");
                }
                satisfied = true;
                allSTypes.erase(oneOfSType);
            }
        }
    }
    if (!allSTypes.empty()) {
        return DAWN_VALIDATION_ERROR("Unsupported sType");
    }
    return {};
}

}  // namespace dawn::native
