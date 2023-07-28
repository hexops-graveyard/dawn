// Copyright 2023 The Tint Authors.
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

#ifndef SRC_TINT_LANG_CORE_IR_TRANSFORM_BUILTIN_POLYFILL_SPIRV_H_
#define SRC_TINT_LANG_CORE_IR_TRANSFORM_BUILTIN_POLYFILL_SPIRV_H_

#include <string>

#include "src/tint/lang/core/ir/constant.h"
#include "src/tint/lang/core/ir/transform/transform.h"
#include "src/tint/lang/core/type/type.h"

// Forward declarations
namespace tint::type {
class Texture;
}  // namespace tint::type

namespace tint::ir::transform {

/// BuiltinPolyfillSpirv is a transform that replaces calls to builtins with polyfills and calls to
/// SPIR-V backend intrinsic functions.
class BuiltinPolyfillSpirv final : public Castable<BuiltinPolyfillSpirv, Transform> {
  public:
    /// Constructor
    BuiltinPolyfillSpirv();
    /// Destructor
    ~BuiltinPolyfillSpirv() override;

    /// @copydoc Transform::Run
    void Run(ir::Module* module) const override;

    /// LiteralOperand is a type of constant value that is intended to be emitted as a literal in
    /// the SPIR-V instruction stream.
    class LiteralOperand final : public Castable<LiteralOperand, ir::Constant> {
      public:
        /// Constructor
        /// @param value the operand value
        explicit LiteralOperand(const constant::Value* value);
        /// Destructor
        ~LiteralOperand() override;
    };

    /// SampledImage represents an OpTypeSampledImage in SPIR-V.
    class SampledImage final : public Castable<SampledImage, type::Type> {
      public:
        /// Constructor
        /// @param image the image type
        explicit SampledImage(const type::Type* image);

        /// @param other the other node to compare against
        /// @returns true if the this type is equal to @p other
        bool Equals(const UniqueNode& other) const override {
            return &other.TypeInfo() == &TypeInfo();
        }

        /// @returns the friendly name for this type
        std::string FriendlyName() const override { return "spirv.sampled_image"; }

        /// @param ctx the clone context
        /// @returns a clone of this type
        SampledImage* Clone(type::CloneContext& ctx) const override;

        /// @returns the image type
        const type::Type* Image() const { return image_; }

      private:
        const type::Type* image_;
    };

  private:
    struct State;
};

}  // namespace tint::ir::transform

#endif  // SRC_TINT_LANG_CORE_IR_TRANSFORM_BUILTIN_POLYFILL_SPIRV_H_
