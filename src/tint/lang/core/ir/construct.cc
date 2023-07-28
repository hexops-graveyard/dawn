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

#include "src/tint/lang/core/ir/construct.h"

#include <utility>

#include "src/tint/utils/debug/debug.h"

TINT_INSTANTIATE_TYPEINFO(tint::ir::Construct);

namespace tint::ir {

Construct::Construct(InstructionResult* result, VectorRef<Value*> arguments) {
    AddOperands(Construct::kArgsOperandOffset, std::move(arguments));
    AddResult(result);
}

Construct::~Construct() = default;

}  // namespace tint::ir
