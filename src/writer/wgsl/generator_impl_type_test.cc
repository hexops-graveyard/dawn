// Copyright 2020 The Tint Authors.
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

#include "src/ast/struct_block_decoration.h"
#include "src/sem/access_control_type.h"
#include "src/sem/depth_texture_type.h"
#include "src/sem/multisampled_texture_type.h"
#include "src/sem/sampled_texture_type.h"
#include "src/writer/wgsl/test_helper.h"

namespace tint {
namespace writer {
namespace wgsl {
namespace {

using WgslGeneratorImplTest = TestHelper;

TEST_F(WgslGeneratorImplTest, EmitType_Alias) {
  auto* alias = ty.alias("alias", ty.f32());
  AST().AddConstructedType(alias);

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(alias)) << gen.error();
  EXPECT_EQ(gen.result(), "alias");
}

TEST_F(WgslGeneratorImplTest, EmitType_Array) {
  auto* arr = ty.array<bool, 4>();
  AST().AddConstructedType(ty.alias("make_type_reachable", arr));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(arr)) << gen.error();
  EXPECT_EQ(gen.result(), "array<bool, 4>");
}

TEST_F(WgslGeneratorImplTest, EmitType_AccessControl_Read) {
  auto* s = Structure("S", {Member("a", ty.i32())},
                      {create<ast::StructBlockDecoration>()});

  auto* a = ty.access(ast::AccessControl::kReadOnly, s);
  AST().AddConstructedType(ty.alias("make_type_reachable", a));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(a)) << gen.error();
  EXPECT_EQ(gen.result(), "[[access(read)]] S");
}

TEST_F(WgslGeneratorImplTest, EmitType_AccessControl_ReadWrite) {
  auto* s = Structure("S", {Member("a", ty.i32())},
                      {create<ast::StructBlockDecoration>()});

  auto* a = ty.access(ast::AccessControl::kReadWrite, s);
  AST().AddConstructedType(ty.alias("make_type_reachable", a));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(a)) << gen.error();
  EXPECT_EQ(gen.result(), "[[access(read_write)]] S");
}

TEST_F(WgslGeneratorImplTest, EmitType_Array_Decoration) {
  auto* a = create<sem::ArrayType>(ty.bool_(), 4,
                                   ast::DecorationList{
                                       create<ast::StrideDecoration>(16u),
                                   });
  AST().AddConstructedType(ty.alias("make_type_reachable", a));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(a)) << gen.error();
  EXPECT_EQ(gen.result(), "[[stride(16)]] array<bool, 4>");
}

TEST_F(WgslGeneratorImplTest, EmitType_Array_MultipleDecorations) {
  auto* a = create<sem::ArrayType>(ty.bool_(), 4,
                                   ast::DecorationList{
                                       create<ast::StrideDecoration>(16u),
                                       create<ast::StrideDecoration>(32u),
                                   });
  AST().AddConstructedType(ty.alias("make_type_reachable", a));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(a)) << gen.error();
  EXPECT_EQ(gen.result(), "[[stride(16)]] [[stride(32)]] array<bool, 4>");
}

TEST_F(WgslGeneratorImplTest, EmitType_RuntimeArray) {
  auto* a = create<sem::ArrayType>(ty.bool_(), 0, ast::DecorationList{});
  AST().AddConstructedType(ty.alias("make_type_reachable", a));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(a)) << gen.error();
  EXPECT_EQ(gen.result(), "array<bool>");
}

TEST_F(WgslGeneratorImplTest, EmitType_Bool) {
  auto* bool_ = ty.bool_();
  AST().AddConstructedType(ty.alias("make_type_reachable", bool_));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(bool_)) << gen.error();
  EXPECT_EQ(gen.result(), "bool");
}

TEST_F(WgslGeneratorImplTest, EmitType_F32) {
  auto* f32 = ty.f32();
  AST().AddConstructedType(ty.alias("make_type_reachable", f32));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(f32)) << gen.error();
  EXPECT_EQ(gen.result(), "f32");
}

TEST_F(WgslGeneratorImplTest, EmitType_I32) {
  auto* i32 = ty.i32();
  AST().AddConstructedType(ty.alias("make_type_reachable", i32));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(i32)) << gen.error();
  EXPECT_EQ(gen.result(), "i32");
}

TEST_F(WgslGeneratorImplTest, EmitType_Matrix) {
  auto* mat2x3 = ty.mat2x3<f32>();
  AST().AddConstructedType(ty.alias("make_type_reachable", mat2x3));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(mat2x3)) << gen.error();
  EXPECT_EQ(gen.result(), "mat2x3<f32>");
}

TEST_F(WgslGeneratorImplTest, EmitType_Pointer) {
  auto* p = create<sem::Pointer>(ty.f32(), ast::StorageClass::kWorkgroup);
  AST().AddConstructedType(ty.alias("make_type_reachable", p));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(p)) << gen.error();
  EXPECT_EQ(gen.result(), "ptr<workgroup, f32>");
}

TEST_F(WgslGeneratorImplTest, EmitType_Struct) {
  auto* s = Structure("S", {
                               Member("a", ty.i32()),
                               Member("b", ty.f32()),
                           });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(s)) << gen.error();
  EXPECT_EQ(gen.result(), "S");
}

TEST_F(WgslGeneratorImplTest, EmitType_StructOffsetDecl) {
  auto* s = Structure("S", {
                               Member("a", ty.i32(), {MemberOffset(8)}),
                               Member("b", ty.f32(), {MemberOffset(16)}),
                           });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitStructType(s)) << gen.error();
  EXPECT_EQ(gen.result(), R"(struct S {
  [[size(8)]]
  tint_0_padding : u32;
  a : i32;
  [[size(4)]]
  tint_1_padding : u32;
  b : f32;
};
)");
}

TEST_F(WgslGeneratorImplTest, EmitType_StructOffsetDecl_WithSymbolCollisions) {
  auto* s =
      Structure("S", {
                         Member("tint_0_padding", ty.i32(), {MemberOffset(8)}),
                         Member("tint_2_padding", ty.f32(), {MemberOffset(16)}),
                     });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitStructType(s)) << gen.error();
  EXPECT_EQ(gen.result(), R"(struct S {
  [[size(8)]]
  tint_1_padding : u32;
  tint_0_padding : i32;
  [[size(4)]]
  tint_3_padding : u32;
  tint_2_padding : f32;
};
)");
}

TEST_F(WgslGeneratorImplTest, EmitType_StructAlignDecl) {
  auto* s = Structure("S", {
                               Member("a", ty.i32(), {MemberAlign(8)}),
                               Member("b", ty.f32(), {MemberAlign(16)}),
                           });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitStructType(s)) << gen.error();
  EXPECT_EQ(gen.result(), R"(struct S {
  [[align(8)]]
  a : i32;
  [[align(16)]]
  b : f32;
};
)");
}

TEST_F(WgslGeneratorImplTest, EmitType_StructSizeDecl) {
  auto* s = Structure("S", {
                               Member("a", ty.i32(), {MemberSize(16)}),
                               Member("b", ty.f32(), {MemberSize(32)}),
                           });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitStructType(s)) << gen.error();
  EXPECT_EQ(gen.result(), R"(struct S {
  [[size(16)]]
  a : i32;
  [[size(32)]]
  b : f32;
};
)");
}

TEST_F(WgslGeneratorImplTest, EmitType_Struct_WithDecoration) {
  auto* s = Structure("S",
                      {
                          Member("a", ty.i32()),
                          Member("b", ty.f32(), {MemberAlign(8)}),
                      },
                      {create<ast::StructBlockDecoration>()});

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitStructType(s)) << gen.error();
  EXPECT_EQ(gen.result(), R"([[block]]
struct S {
  a : i32;
  [[align(8)]]
  b : f32;
};
)");
}

TEST_F(WgslGeneratorImplTest, EmitType_Struct_WithEntryPointDecorations) {
  ast::DecorationList decos;
  decos.push_back(create<ast::StructBlockDecoration>());

  auto* s = Structure(
      "S",
      ast::StructMemberList{
          Member("a", ty.u32(),
                 {create<ast::BuiltinDecoration>(ast::Builtin::kVertexIndex)}),
          Member("b", ty.f32(), {create<ast::LocationDecoration>(2u)})},
      decos);

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitStructType(s)) << gen.error();
  EXPECT_EQ(gen.result(), R"([[block]]
struct S {
  [[builtin(vertex_index)]]
  a : u32;
  [[location(2)]]
  b : f32;
};
)");
}

TEST_F(WgslGeneratorImplTest, EmitType_U32) {
  auto* u32 = ty.u32();
  AST().AddConstructedType(ty.alias("make_type_reachable", u32));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(u32)) << gen.error();
  EXPECT_EQ(gen.result(), "u32");
}

TEST_F(WgslGeneratorImplTest, EmitType_Vector) {
  auto* vec3 = ty.vec3<f32>();
  AST().AddConstructedType(ty.alias("make_type_reachable", vec3));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(vec3)) << gen.error();
  EXPECT_EQ(gen.result(), "vec3<f32>");
}

struct TextureData {
  sem::TextureDimension dim;
  const char* name;
};
inline std::ostream& operator<<(std::ostream& out, TextureData data) {
  out << data.name;
  return out;
}
using WgslGenerator_DepthTextureTest = TestParamHelper<TextureData>;

TEST_P(WgslGenerator_DepthTextureTest, EmitType_DepthTexture) {
  auto param = GetParam();

  auto* d = create<sem::DepthTexture>(param.dim);
  AST().AddConstructedType(ty.alias("make_type_reachable", d));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(d)) << gen.error();
  EXPECT_EQ(gen.result(), param.name);
}
INSTANTIATE_TEST_SUITE_P(
    WgslGeneratorImplTest,
    WgslGenerator_DepthTextureTest,
    testing::Values(
        TextureData{sem::TextureDimension::k2d, "texture_depth_2d"},
        TextureData{sem::TextureDimension::k2dArray, "texture_depth_2d_array"},
        TextureData{sem::TextureDimension::kCube, "texture_depth_cube"},
        TextureData{sem::TextureDimension::kCubeArray,
                    "texture_depth_cube_array"}));

using WgslGenerator_SampledTextureTest = TestParamHelper<TextureData>;
TEST_P(WgslGenerator_SampledTextureTest, EmitType_SampledTexture_F32) {
  auto param = GetParam();

  auto* t = create<sem::SampledTexture>(param.dim, ty.f32());
  AST().AddConstructedType(ty.alias("make_type_reachable", t));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(t)) << gen.error();
  EXPECT_EQ(gen.result(), std::string(param.name) + "<f32>");
}

TEST_P(WgslGenerator_SampledTextureTest, EmitType_SampledTexture_I32) {
  auto param = GetParam();

  auto* t = create<sem::SampledTexture>(param.dim, ty.i32());
  AST().AddConstructedType(ty.alias("make_type_reachable", t));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(t)) << gen.error();
  EXPECT_EQ(gen.result(), std::string(param.name) + "<i32>");
}

TEST_P(WgslGenerator_SampledTextureTest, EmitType_SampledTexture_U32) {
  auto param = GetParam();

  auto* t = create<sem::SampledTexture>(param.dim, ty.u32());
  AST().AddConstructedType(ty.alias("make_type_reachable", t));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(t)) << gen.error();
  EXPECT_EQ(gen.result(), std::string(param.name) + "<u32>");
}
INSTANTIATE_TEST_SUITE_P(
    WgslGeneratorImplTest,
    WgslGenerator_SampledTextureTest,
    testing::Values(
        TextureData{sem::TextureDimension::k1d, "texture_1d"},
        TextureData{sem::TextureDimension::k2d, "texture_2d"},
        TextureData{sem::TextureDimension::k2dArray, "texture_2d_array"},
        TextureData{sem::TextureDimension::k3d, "texture_3d"},
        TextureData{sem::TextureDimension::kCube, "texture_cube"},
        TextureData{sem::TextureDimension::kCubeArray, "texture_cube_array"}));

using WgslGenerator_MultiampledTextureTest = TestParamHelper<TextureData>;
TEST_P(WgslGenerator_MultiampledTextureTest, EmitType_MultisampledTexture_F32) {
  auto param = GetParam();

  auto* t = create<sem::MultisampledTexture>(param.dim, ty.f32());
  AST().AddConstructedType(ty.alias("make_type_reachable", t));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(t)) << gen.error();
  EXPECT_EQ(gen.result(), std::string(param.name) + "<f32>");
}

TEST_P(WgslGenerator_MultiampledTextureTest, EmitType_MultisampledTexture_I32) {
  auto param = GetParam();

  auto* t = create<sem::MultisampledTexture>(param.dim, ty.i32());
  AST().AddConstructedType(ty.alias("make_type_reachable", t));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(t)) << gen.error();
  EXPECT_EQ(gen.result(), std::string(param.name) + "<i32>");
}

TEST_P(WgslGenerator_MultiampledTextureTest, EmitType_MultisampledTexture_U32) {
  auto param = GetParam();

  auto* t = create<sem::MultisampledTexture>(param.dim, ty.u32());
  AST().AddConstructedType(ty.alias("make_type_reachable", t));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(t)) << gen.error();
  EXPECT_EQ(gen.result(), std::string(param.name) + "<u32>");
}
INSTANTIATE_TEST_SUITE_P(WgslGeneratorImplTest,
                         WgslGenerator_MultiampledTextureTest,
                         testing::Values(TextureData{
                             sem::TextureDimension::k2d,
                             "texture_multisampled_2d"}));

struct StorageTextureData {
  sem::ImageFormat fmt;
  sem::TextureDimension dim;
  ast::AccessControl::Access access;
  const char* name;
};
inline std::ostream& operator<<(std::ostream& out, StorageTextureData data) {
  out << data.name;
  return out;
}
using WgslGenerator_StorageTextureTest = TestParamHelper<StorageTextureData>;
TEST_P(WgslGenerator_StorageTextureTest, EmitType_StorageTexture) {
  auto param = GetParam();

  auto* subtype = sem::StorageTexture::SubtypeFor(param.fmt, Types());
  auto* t = create<sem::StorageTexture>(param.dim, param.fmt, subtype);
  auto* ac = ty.access(param.access, t);

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(ac)) << gen.error();
  EXPECT_EQ(gen.result(), param.name);
}
INSTANTIATE_TEST_SUITE_P(
    WgslGeneratorImplTest,
    WgslGenerator_StorageTextureTest,
    testing::Values(
        StorageTextureData{sem::ImageFormat::kR8Unorm,
                           sem::TextureDimension::k1d,
                           ast::AccessControl::kReadOnly,
                           "[[access(read)]] texture_storage_1d<r8unorm>"},
        StorageTextureData{sem::ImageFormat::kR8Unorm,
                           sem::TextureDimension::k2d,
                           ast::AccessControl::kReadOnly,
                           "[[access(read)]] texture_storage_2d<r8unorm>"},
        StorageTextureData{
            sem::ImageFormat::kR8Unorm, sem::TextureDimension::k2dArray,
            ast::AccessControl::kReadOnly,
            "[[access(read)]] texture_storage_2d_array<r8unorm>"},
        StorageTextureData{sem::ImageFormat::kR8Unorm,
                           sem::TextureDimension::k3d,
                           ast::AccessControl::kReadOnly,
                           "[[access(read)]] texture_storage_3d<r8unorm>"},
        StorageTextureData{sem::ImageFormat::kR8Unorm,
                           sem::TextureDimension::k1d,
                           ast::AccessControl::kWriteOnly,
                           "[[access(write)]] texture_storage_1d<r8unorm>"},
        StorageTextureData{sem::ImageFormat::kR8Unorm,
                           sem::TextureDimension::k2d,
                           ast::AccessControl::kWriteOnly,
                           "[[access(write)]] texture_storage_2d<r8unorm>"},
        StorageTextureData{
            sem::ImageFormat::kR8Unorm, sem::TextureDimension::k2dArray,
            ast::AccessControl::kWriteOnly,
            "[[access(write)]] texture_storage_2d_array<r8unorm>"},
        StorageTextureData{sem::ImageFormat::kR8Unorm,
                           sem::TextureDimension::k3d,
                           ast::AccessControl::kWriteOnly,
                           "[[access(write)]] texture_storage_3d<r8unorm>"}));

struct ImageFormatData {
  sem::ImageFormat fmt;
  const char* name;
};
inline std::ostream& operator<<(std::ostream& out, ImageFormatData data) {
  out << data.name;
  return out;
}
using WgslGenerator_ImageFormatTest = TestParamHelper<ImageFormatData>;
TEST_P(WgslGenerator_ImageFormatTest, EmitType_StorageTexture_ImageFormat) {
  auto param = GetParam();

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitImageFormat(param.fmt)) << gen.error();
  EXPECT_EQ(gen.result(), param.name);
}

INSTANTIATE_TEST_SUITE_P(
    WgslGeneratorImplTest,
    WgslGenerator_ImageFormatTest,
    testing::Values(
        ImageFormatData{sem::ImageFormat::kR8Unorm, "r8unorm"},
        ImageFormatData{sem::ImageFormat::kR8Snorm, "r8snorm"},
        ImageFormatData{sem::ImageFormat::kR8Uint, "r8uint"},
        ImageFormatData{sem::ImageFormat::kR8Sint, "r8sint"},
        ImageFormatData{sem::ImageFormat::kR16Uint, "r16uint"},
        ImageFormatData{sem::ImageFormat::kR16Sint, "r16sint"},
        ImageFormatData{sem::ImageFormat::kR16Float, "r16float"},
        ImageFormatData{sem::ImageFormat::kRg8Unorm, "rg8unorm"},
        ImageFormatData{sem::ImageFormat::kRg8Snorm, "rg8snorm"},
        ImageFormatData{sem::ImageFormat::kRg8Uint, "rg8uint"},
        ImageFormatData{sem::ImageFormat::kRg8Sint, "rg8sint"},
        ImageFormatData{sem::ImageFormat::kR32Uint, "r32uint"},
        ImageFormatData{sem::ImageFormat::kR32Sint, "r32sint"},
        ImageFormatData{sem::ImageFormat::kR32Float, "r32float"},
        ImageFormatData{sem::ImageFormat::kRg16Uint, "rg16uint"},
        ImageFormatData{sem::ImageFormat::kRg16Sint, "rg16sint"},
        ImageFormatData{sem::ImageFormat::kRg16Float, "rg16float"},
        ImageFormatData{sem::ImageFormat::kRgba8Unorm, "rgba8unorm"},
        ImageFormatData{sem::ImageFormat::kRgba8UnormSrgb, "rgba8unorm_srgb"},
        ImageFormatData{sem::ImageFormat::kRgba8Snorm, "rgba8snorm"},
        ImageFormatData{sem::ImageFormat::kRgba8Uint, "rgba8uint"},
        ImageFormatData{sem::ImageFormat::kRgba8Sint, "rgba8sint"},
        ImageFormatData{sem::ImageFormat::kBgra8Unorm, "bgra8unorm"},
        ImageFormatData{sem::ImageFormat::kBgra8UnormSrgb, "bgra8unorm_srgb"},
        ImageFormatData{sem::ImageFormat::kRgb10A2Unorm, "rgb10a2unorm"},
        ImageFormatData{sem::ImageFormat::kRg11B10Float, "rg11b10float"},
        ImageFormatData{sem::ImageFormat::kRg32Uint, "rg32uint"},
        ImageFormatData{sem::ImageFormat::kRg32Sint, "rg32sint"},
        ImageFormatData{sem::ImageFormat::kRg32Float, "rg32float"},
        ImageFormatData{sem::ImageFormat::kRgba16Uint, "rgba16uint"},
        ImageFormatData{sem::ImageFormat::kRgba16Sint, "rgba16sint"},
        ImageFormatData{sem::ImageFormat::kRgba16Float, "rgba16float"},
        ImageFormatData{sem::ImageFormat::kRgba32Uint, "rgba32uint"},
        ImageFormatData{sem::ImageFormat::kRgba32Sint, "rgba32sint"},
        ImageFormatData{sem::ImageFormat::kRgba32Float, "rgba32float"}));

TEST_F(WgslGeneratorImplTest, EmitType_Sampler) {
  auto* sampler = create<sem::Sampler>(sem::SamplerKind::kSampler);
  AST().AddConstructedType(ty.alias("make_type_reachable", sampler));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(sampler)) << gen.error();
  EXPECT_EQ(gen.result(), "sampler");
}

TEST_F(WgslGeneratorImplTest, EmitType_SamplerComparison) {
  auto* sampler = create<sem::Sampler>(sem::SamplerKind::kComparisonSampler);
  AST().AddConstructedType(ty.alias("make_type_reachable", sampler));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitType(sampler)) << gen.error();
  EXPECT_EQ(gen.result(), "sampler_comparison");
}

}  // namespace
}  // namespace wgsl
}  // namespace writer
}  // namespace tint
