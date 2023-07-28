// Copyright 2022 The Tint Authors.
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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/lang/core/builtin/builtin.h.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#ifndef SRC_TINT_LANG_CORE_BUILTIN_BUILTIN_H_
#define SRC_TINT_LANG_CORE_BUILTIN_BUILTIN_H_

#include "src/tint/utils/text/string_stream.h"

namespace tint::builtin {

/// An enumerator of builtin builtin.
enum class Builtin {
    kUndefined,
    kAtomicCompareExchangeResultI32,
    kAtomicCompareExchangeResultU32,
    kFrexpResultAbstract,
    kFrexpResultF16,
    kFrexpResultF32,
    kFrexpResultVec2Abstract,
    kFrexpResultVec2F16,
    kFrexpResultVec2F32,
    kFrexpResultVec3Abstract,
    kFrexpResultVec3F16,
    kFrexpResultVec3F32,
    kFrexpResultVec4Abstract,
    kFrexpResultVec4F16,
    kFrexpResultVec4F32,
    kModfResultAbstract,
    kModfResultF16,
    kModfResultF32,
    kModfResultVec2Abstract,
    kModfResultVec2F16,
    kModfResultVec2F32,
    kModfResultVec3Abstract,
    kModfResultVec3F16,
    kModfResultVec3F32,
    kModfResultVec4Abstract,
    kModfResultVec4F16,
    kModfResultVec4F32,
    kPackedVec3,
    kArray,
    kAtomic,
    kBool,
    kF16,
    kF32,
    kI32,
    kMat2X2,
    kMat2X2F,
    kMat2X2H,
    kMat2X3,
    kMat2X3F,
    kMat2X3H,
    kMat2X4,
    kMat2X4F,
    kMat2X4H,
    kMat3X2,
    kMat3X2F,
    kMat3X2H,
    kMat3X3,
    kMat3X3F,
    kMat3X3H,
    kMat3X4,
    kMat3X4F,
    kMat3X4H,
    kMat4X2,
    kMat4X2F,
    kMat4X2H,
    kMat4X3,
    kMat4X3F,
    kMat4X3H,
    kMat4X4,
    kMat4X4F,
    kMat4X4H,
    kPtr,
    kSampler,
    kSamplerComparison,
    kTexture1D,
    kTexture2D,
    kTexture2DArray,
    kTexture3D,
    kTextureCube,
    kTextureCubeArray,
    kTextureDepth2D,
    kTextureDepth2DArray,
    kTextureDepthCube,
    kTextureDepthCubeArray,
    kTextureDepthMultisampled2D,
    kTextureExternal,
    kTextureMultisampled2D,
    kTextureStorage1D,
    kTextureStorage2D,
    kTextureStorage2DArray,
    kTextureStorage3D,
    kU32,
    kVec2,
    kVec2F,
    kVec2H,
    kVec2I,
    kVec2U,
    kVec3,
    kVec3F,
    kVec3H,
    kVec3I,
    kVec3U,
    kVec4,
    kVec4F,
    kVec4H,
    kVec4I,
    kVec4U,
};

/// @param out the stream to write to
/// @param value the Builtin
/// @returns `out` so calls can be chained
StringStream& operator<<(StringStream& out, Builtin value);

/// ParseBuiltin parses a Builtin from a string.
/// @param str the string to parse
/// @returns the parsed enum, or Builtin::kUndefined if the string could not be parsed.
Builtin ParseBuiltin(std::string_view str);

constexpr const char* kBuiltinStrings[] = {
    "__atomic_compare_exchange_result_i32",
    "__atomic_compare_exchange_result_u32",
    "__frexp_result_abstract",
    "__frexp_result_f16",
    "__frexp_result_f32",
    "__frexp_result_vec2_abstract",
    "__frexp_result_vec2_f16",
    "__frexp_result_vec2_f32",
    "__frexp_result_vec3_abstract",
    "__frexp_result_vec3_f16",
    "__frexp_result_vec3_f32",
    "__frexp_result_vec4_abstract",
    "__frexp_result_vec4_f16",
    "__frexp_result_vec4_f32",
    "__modf_result_abstract",
    "__modf_result_f16",
    "__modf_result_f32",
    "__modf_result_vec2_abstract",
    "__modf_result_vec2_f16",
    "__modf_result_vec2_f32",
    "__modf_result_vec3_abstract",
    "__modf_result_vec3_f16",
    "__modf_result_vec3_f32",
    "__modf_result_vec4_abstract",
    "__modf_result_vec4_f16",
    "__modf_result_vec4_f32",
    "__packed_vec3",
    "array",
    "atomic",
    "bool",
    "f16",
    "f32",
    "i32",
    "mat2x2",
    "mat2x2f",
    "mat2x2h",
    "mat2x3",
    "mat2x3f",
    "mat2x3h",
    "mat2x4",
    "mat2x4f",
    "mat2x4h",
    "mat3x2",
    "mat3x2f",
    "mat3x2h",
    "mat3x3",
    "mat3x3f",
    "mat3x3h",
    "mat3x4",
    "mat3x4f",
    "mat3x4h",
    "mat4x2",
    "mat4x2f",
    "mat4x2h",
    "mat4x3",
    "mat4x3f",
    "mat4x3h",
    "mat4x4",
    "mat4x4f",
    "mat4x4h",
    "ptr",
    "sampler",
    "sampler_comparison",
    "texture_1d",
    "texture_2d",
    "texture_2d_array",
    "texture_3d",
    "texture_cube",
    "texture_cube_array",
    "texture_depth_2d",
    "texture_depth_2d_array",
    "texture_depth_cube",
    "texture_depth_cube_array",
    "texture_depth_multisampled_2d",
    "texture_external",
    "texture_multisampled_2d",
    "texture_storage_1d",
    "texture_storage_2d",
    "texture_storage_2d_array",
    "texture_storage_3d",
    "u32",
    "vec2",
    "vec2f",
    "vec2h",
    "vec2i",
    "vec2u",
    "vec3",
    "vec3f",
    "vec3h",
    "vec3i",
    "vec3u",
    "vec4",
    "vec4f",
    "vec4h",
    "vec4i",
    "vec4u",
};

}  // namespace tint::builtin

#endif  // SRC_TINT_LANG_CORE_BUILTIN_BUILTIN_H_
