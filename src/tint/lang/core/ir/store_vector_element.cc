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

#include "src/tint/lang/core/ir/store_vector_element.h"

TINT_INSTANTIATE_TYPEINFO(tint::ir::StoreVectorElement);

namespace tint::ir {

StoreVectorElement::StoreVectorElement(ir::Value* to, ir::Value* index, ir::Value* value) {
    flags_.Add(Flag::kSequenced);

    AddOperand(StoreVectorElement::kToOperandOffset, to);
    AddOperand(StoreVectorElement::kIndexOperandOffset, index);
    AddOperand(StoreVectorElement::kValueOperandOffset, value);
}

StoreVectorElement::~StoreVectorElement() = default;

}  // namespace tint::ir
