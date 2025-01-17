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

#include "src/tint/lang/core/ir/access.h"

#include <utility>

TINT_INSTANTIATE_TYPEINFO(tint::ir::Access);

namespace tint::ir {

//! @cond Doxygen_Suppress
Access::Access(InstructionResult* result, Value* object, VectorRef<Value*> indices) {
    AddOperand(Access::kObjectOperandOffset, object);
    AddOperands(Access::kIndicesOperandOffset, std::move(indices));
    AddResult(result);
}

Access::~Access() = default;
//! @endcond

}  // namespace tint::ir
