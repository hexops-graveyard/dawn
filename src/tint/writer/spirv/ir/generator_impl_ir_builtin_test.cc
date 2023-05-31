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

#include "src/tint/writer/spirv/ir/test_helper_ir.h"

#include "gmock/gmock.h"
#include "src/tint/builtin/function.h"

using namespace tint::number_suffixes;  // NOLINT

namespace tint::writer::spirv {
namespace {

/// A parameterized builtin function test case.
struct BuiltinTestCase {
    /// The element type to test.
    TestElementType type;
    /// The builtin function.
    enum builtin::Function function;
    /// The expected SPIR-V instruction string.
    std::string spirv_inst;
};

// Tests for builtins with the signature: T = func(T)
using Builtin_1arg = SpvGeneratorImplTestWithParam<BuiltinTestCase>;
TEST_P(Builtin_1arg, Scalar) {
    auto params = GetParam();

    auto* func = b.CreateFunction("foo", mod.Types().void_());
    func->StartTarget()->SetInstructions(
        utils::Vector{b.Builtin(MakeScalarType(params.type), params.function,
                                utils::Vector{MakeScalarValue(params.type)}),
                      b.Return(func)});

    generator_.EmitFunction(func);
    EXPECT_THAT(DumpModule(generator_.Module()), ::testing::HasSubstr(params.spirv_inst));
}
TEST_P(Builtin_1arg, Vector) {
    auto params = GetParam();

    auto* func = b.CreateFunction("foo", mod.Types().void_());
    func->StartTarget()->SetInstructions(
        utils::Vector{b.Builtin(MakeVectorType(params.type), params.function,
                                utils::Vector{MakeVectorValue(params.type)}),

                      b.Return(func)});

    generator_.EmitFunction(func);
    EXPECT_THAT(DumpModule(generator_.Module()), ::testing::HasSubstr(params.spirv_inst));
}
INSTANTIATE_TEST_SUITE_P(SpvGeneratorImplTest,
                         Builtin_1arg,
                         testing::Values(BuiltinTestCase{kI32, builtin::Function::kAbs, "SAbs"},
                                         BuiltinTestCase{kF32, builtin::Function::kAbs, "FAbs"}));

// Test that abs of an unsigned value just folds away.
TEST_F(SpvGeneratorImplTest, Builtin_Abs_u32) {
    auto* result = b.Builtin(MakeScalarType(kU32), builtin::Function::kAbs,
                             utils::Vector{MakeScalarValue(kU32)});
    auto* func = b.CreateFunction("foo", MakeScalarType(kU32));
    func->StartTarget()->SetInstructions(
        utils::Vector{result, b.Return(func, utils::Vector{result})});

    generator_.EmitFunction(func);
    EXPECT_EQ(DumpModule(generator_.Module()), R"(OpName %1 "foo"
%2 = OpTypeInt 32 0
%3 = OpTypeFunction %2
%6 = OpConstant %2 1
%1 = OpFunction %2 None %3
%4 = OpLabel
OpReturnValue %6
OpFunctionEnd
)");
}
TEST_F(SpvGeneratorImplTest, Builtin_Abs_vec2u) {
    auto* result = b.Builtin(MakeVectorType(kU32), builtin::Function::kAbs,
                             utils::Vector{MakeVectorValue(kU32)});
    auto* func = b.CreateFunction("foo", MakeVectorType(kU32));
    func->StartTarget()->SetInstructions(
        utils::Vector{result, b.Return(func, utils::Vector{result})});

    generator_.EmitFunction(func);
    EXPECT_EQ(DumpModule(generator_.Module()), R"(OpName %1 "foo"
%3 = OpTypeInt 32 0
%2 = OpTypeVector %3 2
%4 = OpTypeFunction %2
%8 = OpConstant %3 42
%9 = OpConstant %3 10
%7 = OpConstantComposite %2 %8 %9
%1 = OpFunction %2 None %4
%5 = OpLabel
OpReturnValue %7
OpFunctionEnd
)");
}

// Tests for builtins with the signature: T = func(T, T)
using Builtin_2arg = SpvGeneratorImplTestWithParam<BuiltinTestCase>;
TEST_P(Builtin_2arg, Scalar) {
    auto params = GetParam();

    auto* func = b.CreateFunction("foo", mod.Types().void_());
    func->StartTarget()->SetInstructions(utils::Vector{
        b.Builtin(MakeScalarType(params.type), params.function,
                  utils::Vector{MakeScalarValue(params.type), MakeScalarValue(params.type)}),
        b.Return(func)});

    generator_.EmitFunction(func);
    EXPECT_THAT(DumpModule(generator_.Module()), ::testing::HasSubstr(params.spirv_inst));
}
TEST_P(Builtin_2arg, Vector) {
    auto params = GetParam();

    auto* func = b.CreateFunction("foo", mod.Types().void_());
    func->StartTarget()->SetInstructions(utils::Vector{
        b.Builtin(MakeVectorType(params.type), params.function,
                  utils::Vector{MakeVectorValue(params.type), MakeVectorValue(params.type)}),

        b.Return(func)});

    generator_.EmitFunction(func);
    EXPECT_THAT(DumpModule(generator_.Module()), ::testing::HasSubstr(params.spirv_inst));
}
INSTANTIATE_TEST_SUITE_P(SpvGeneratorImplTest,
                         Builtin_2arg,
                         testing::Values(BuiltinTestCase{kF32, builtin::Function::kMax, "FMax"},
                                         BuiltinTestCase{kI32, builtin::Function::kMax, "SMax"},
                                         BuiltinTestCase{kU32, builtin::Function::kMax, "UMax"},
                                         BuiltinTestCase{kF32, builtin::Function::kMin, "FMin"},
                                         BuiltinTestCase{kI32, builtin::Function::kMin, "SMin"},
                                         BuiltinTestCase{kU32, builtin::Function::kMin, "UMin"}));

}  // namespace
}  // namespace tint::writer::spirv