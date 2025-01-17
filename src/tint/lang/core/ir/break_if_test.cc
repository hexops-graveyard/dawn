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

#include "src/tint/lang/core/ir/break_if.h"

#include "gmock/gmock.h"
#include "gtest/gtest-spi.h"
#include "src/tint/lang/core/ir/ir_helper_test.h"

namespace tint::ir {
namespace {

using namespace tint::number_suffixes;  // NOLINT
using IR_BreakIfTest = IRTestHelper;

TEST_F(IR_BreakIfTest, Usage) {
    auto* loop = b.Loop();
    auto* cond = b.Constant(true);
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);

    auto* brk = b.BreakIf(loop, cond, arg1, arg2);

    EXPECT_THAT(cond->Usages(), testing::UnorderedElementsAre(Usage{brk, 0u}));
    EXPECT_THAT(arg1->Usages(), testing::UnorderedElementsAre(Usage{brk, 1u}));
    EXPECT_THAT(arg2->Usages(), testing::UnorderedElementsAre(Usage{brk, 2u}));
}

TEST_F(IR_BreakIfTest, Results) {
    auto* loop = b.Loop();
    auto* cond = b.Constant(true);
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);

    auto* brk = b.BreakIf(loop, cond, arg1, arg2);
    EXPECT_FALSE(brk->HasResults());
    EXPECT_FALSE(brk->HasMultiResults());
}

TEST_F(IR_BreakIfTest, Fail_NullLoop) {
    EXPECT_FATAL_FAILURE(
        {
            Module mod;
            Builder b{mod};
            b.BreakIf(nullptr, true);
        },
        "");
}

}  // namespace
}  // namespace tint::ir
