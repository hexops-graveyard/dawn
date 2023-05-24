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

#include "src/tint/ir/test_helper.h"

#include "gmock/gmock.h"
#include "src/tint/ast/case_selector.h"
#include "src/tint/ast/int_literal_expression.h"
#include "src/tint/constant/scalar.h"

namespace tint::ir {
namespace {

using namespace tint::number_suffixes;  // NOLINT

using IR_BuilderImplTest = TestHelper;

TEST_F(IR_BuilderImplTest, Emit_GlobalVar_NoInit) {
    GlobalVar("a", ty.u32(), builtin::AddressSpace::kPrivate);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(# Root block
%fn1 = block {
  %a:ptr<private, u32, read_write> = var
  br %fn2  # root_end
}

%fn2 = root_terminator

)");
}

TEST_F(IR_BuilderImplTest, Emit_GlobalVar_Init) {
    auto* expr = Expr(2_u);
    GlobalVar("a", ty.u32(), builtin::AddressSpace::kPrivate, expr);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()), R"(# Root block
%fn1 = block {
  %a:ptr<private, u32, read_write> = var, 2u
  br %fn2  # root_end
}

%fn2 = root_terminator

)");
}

TEST_F(IR_BuilderImplTest, Emit_Var_NoInit) {
    auto* a = Var("a", ty.u32(), builtin::AddressSpace::kFunction);
    WrapInFunction(a);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()),
              R"(%1 = func test_function():void [@compute @workgroup_size(1, 1, 1)] -> %fn1 {
  %fn1 = block {
    %a:ptr<function, u32, read_write> = var
    br %fn2  # return
  }
  %fn2 = func_terminator
}
)");
}

TEST_F(IR_BuilderImplTest, Emit_Var_Init) {
    auto* expr = Expr(2_u);
    auto* a = Var("a", ty.u32(), builtin::AddressSpace::kFunction, expr);
    WrapInFunction(a);

    auto m = Build();
    ASSERT_TRUE(m) << (!m ? m.Failure() : "");

    EXPECT_EQ(Disassemble(m.Get()),
              R"(%1 = func test_function():void [@compute @workgroup_size(1, 1, 1)] -> %fn1 {
  %fn1 = block {
    %a:ptr<function, u32, read_write> = var, 2u
    br %fn2  # return
  }
  %fn2 = func_terminator
}
)");
}
}  // namespace
}  // namespace tint::ir
