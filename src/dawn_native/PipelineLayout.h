// Copyright 2017 The Dawn Authors
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

#ifndef DAWNNATIVE_PIPELINELAYOUT_H_
#define DAWNNATIVE_PIPELINELAYOUT_H_

#include "common/Constants.h"
#include "common/ityp_array.h"
#include "common/ityp_bitset.h"
#include "dawn_native/BindingInfo.h"
#include "dawn_native/CachedObject.h"
#include "dawn_native/Error.h"
#include "dawn_native/Forward.h"
#include "dawn_native/ObjectBase.h"

#include "dawn_native/dawn_platform.h"

#include <array>
#include <bitset>

namespace dawn::native {

    MaybeError ValidatePipelineLayoutDescriptor(
        DeviceBase*,
        const PipelineLayoutDescriptor* descriptor,
        PipelineCompatibilityToken pipelineCompatibilityToken = PipelineCompatibilityToken(0));

    using BindGroupLayoutArray =
        ityp::array<BindGroupIndex, Ref<BindGroupLayoutBase>, kMaxBindGroups>;
    using BindGroupLayoutMask = ityp::bitset<BindGroupIndex, kMaxBindGroups>;

    struct StageAndDescriptor {
        SingleShaderStage shaderStage;
        ShaderModuleBase* module;
        std::string entryPoint;
        uint32_t constantCount = 0u;
        ConstantEntry const* constants = nullptr;
    };

    class PipelineLayoutBase : public ApiObjectBase, public CachedObject {
      public:
        PipelineLayoutBase(DeviceBase* device,
                           const PipelineLayoutDescriptor* descriptor,
                           ApiObjectBase::UntrackedByDeviceTag tag);
        PipelineLayoutBase(DeviceBase* device, const PipelineLayoutDescriptor* descriptor);
        ~PipelineLayoutBase() override;

        static PipelineLayoutBase* MakeError(DeviceBase* device);
        static ResultOrError<Ref<PipelineLayoutBase>> CreateDefault(
            DeviceBase* device,
            std::vector<StageAndDescriptor> stages);

        ObjectType GetType() const override;

        const BindGroupLayoutBase* GetBindGroupLayout(BindGroupIndex group) const;
        BindGroupLayoutBase* GetBindGroupLayout(BindGroupIndex group);
        const BindGroupLayoutMask& GetBindGroupLayoutsMask() const;

        // Utility functions to compute inherited bind groups.
        // Returns the inherited bind groups as a mask.
        BindGroupLayoutMask InheritedGroupsMask(const PipelineLayoutBase* other) const;

        // Returns the index of the first incompatible bind group in the range
        // [0, kMaxBindGroups]
        BindGroupIndex GroupsInheritUpTo(const PipelineLayoutBase* other) const;

        // Functions necessary for the unordered_set<PipelineLayoutBase*>-based cache.
        size_t ComputeContentHash() override;

        struct EqualityFunc {
            bool operator()(const PipelineLayoutBase* a, const PipelineLayoutBase* b) const;
        };

      protected:
        // Constructor used only for mocking and testing.
        PipelineLayoutBase(DeviceBase* device);
        PipelineLayoutBase(DeviceBase* device, ObjectBase::ErrorTag tag);
        void DestroyImpl() override;

        BindGroupLayoutArray mBindGroupLayouts;
        BindGroupLayoutMask mMask;
    };

}  // namespace dawn::native

#endif  // DAWNNATIVE_PIPELINELAYOUT_H_
