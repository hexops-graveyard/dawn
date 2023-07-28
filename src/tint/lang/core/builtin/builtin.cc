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
//   src/tint/lang/core/builtin/builtin.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/lang/core/builtin/builtin.h"

namespace tint::builtin {

/// ParseBuiltin parses a Builtin from a string.
/// @param str the string to parse
/// @returns the parsed enum, or Builtin::kUndefined if the string could not be parsed.
Builtin ParseBuiltin(std::string_view str) {
    if (str == "__atomic_compare_exchange_result_i32") {
        return Builtin::kAtomicCompareExchangeResultI32;
    }
    if (str == "__atomic_compare_exchange_result_u32") {
        return Builtin::kAtomicCompareExchangeResultU32;
    }
    if (str == "__frexp_result_abstract") {
        return Builtin::kFrexpResultAbstract;
    }
    if (str == "__frexp_result_f16") {
        return Builtin::kFrexpResultF16;
    }
    if (str == "__frexp_result_f32") {
        return Builtin::kFrexpResultF32;
    }
    if (str == "__frexp_result_vec2_abstract") {
        return Builtin::kFrexpResultVec2Abstract;
    }
    if (str == "__frexp_result_vec2_f16") {
        return Builtin::kFrexpResultVec2F16;
    }
    if (str == "__frexp_result_vec2_f32") {
        return Builtin::kFrexpResultVec2F32;
    }
    if (str == "__frexp_result_vec3_abstract") {
        return Builtin::kFrexpResultVec3Abstract;
    }
    if (str == "__frexp_result_vec3_f16") {
        return Builtin::kFrexpResultVec3F16;
    }
    if (str == "__frexp_result_vec3_f32") {
        return Builtin::kFrexpResultVec3F32;
    }
    if (str == "__frexp_result_vec4_abstract") {
        return Builtin::kFrexpResultVec4Abstract;
    }
    if (str == "__frexp_result_vec4_f16") {
        return Builtin::kFrexpResultVec4F16;
    }
    if (str == "__frexp_result_vec4_f32") {
        return Builtin::kFrexpResultVec4F32;
    }
    if (str == "__modf_result_abstract") {
        return Builtin::kModfResultAbstract;
    }
    if (str == "__modf_result_f16") {
        return Builtin::kModfResultF16;
    }
    if (str == "__modf_result_f32") {
        return Builtin::kModfResultF32;
    }
    if (str == "__modf_result_vec2_abstract") {
        return Builtin::kModfResultVec2Abstract;
    }
    if (str == "__modf_result_vec2_f16") {
        return Builtin::kModfResultVec2F16;
    }
    if (str == "__modf_result_vec2_f32") {
        return Builtin::kModfResultVec2F32;
    }
    if (str == "__modf_result_vec3_abstract") {
        return Builtin::kModfResultVec3Abstract;
    }
    if (str == "__modf_result_vec3_f16") {
        return Builtin::kModfResultVec3F16;
    }
    if (str == "__modf_result_vec3_f32") {
        return Builtin::kModfResultVec3F32;
    }
    if (str == "__modf_result_vec4_abstract") {
        return Builtin::kModfResultVec4Abstract;
    }
    if (str == "__modf_result_vec4_f16") {
        return Builtin::kModfResultVec4F16;
    }
    if (str == "__modf_result_vec4_f32") {
        return Builtin::kModfResultVec4F32;
    }
    if (str == "__packed_vec3") {
        return Builtin::kPackedVec3;
    }
    if (str == "array") {
        return Builtin::kArray;
    }
    if (str == "atomic") {
        return Builtin::kAtomic;
    }
    if (str == "bool") {
        return Builtin::kBool;
    }
    if (str == "f16") {
        return Builtin::kF16;
    }
    if (str == "f32") {
        return Builtin::kF32;
    }
    if (str == "i32") {
        return Builtin::kI32;
    }
    if (str == "mat2x2") {
        return Builtin::kMat2X2;
    }
    if (str == "mat2x2f") {
        return Builtin::kMat2X2F;
    }
    if (str == "mat2x2h") {
        return Builtin::kMat2X2H;
    }
    if (str == "mat2x3") {
        return Builtin::kMat2X3;
    }
    if (str == "mat2x3f") {
        return Builtin::kMat2X3F;
    }
    if (str == "mat2x3h") {
        return Builtin::kMat2X3H;
    }
    if (str == "mat2x4") {
        return Builtin::kMat2X4;
    }
    if (str == "mat2x4f") {
        return Builtin::kMat2X4F;
    }
    if (str == "mat2x4h") {
        return Builtin::kMat2X4H;
    }
    if (str == "mat3x2") {
        return Builtin::kMat3X2;
    }
    if (str == "mat3x2f") {
        return Builtin::kMat3X2F;
    }
    if (str == "mat3x2h") {
        return Builtin::kMat3X2H;
    }
    if (str == "mat3x3") {
        return Builtin::kMat3X3;
    }
    if (str == "mat3x3f") {
        return Builtin::kMat3X3F;
    }
    if (str == "mat3x3h") {
        return Builtin::kMat3X3H;
    }
    if (str == "mat3x4") {
        return Builtin::kMat3X4;
    }
    if (str == "mat3x4f") {
        return Builtin::kMat3X4F;
    }
    if (str == "mat3x4h") {
        return Builtin::kMat3X4H;
    }
    if (str == "mat4x2") {
        return Builtin::kMat4X2;
    }
    if (str == "mat4x2f") {
        return Builtin::kMat4X2F;
    }
    if (str == "mat4x2h") {
        return Builtin::kMat4X2H;
    }
    if (str == "mat4x3") {
        return Builtin::kMat4X3;
    }
    if (str == "mat4x3f") {
        return Builtin::kMat4X3F;
    }
    if (str == "mat4x3h") {
        return Builtin::kMat4X3H;
    }
    if (str == "mat4x4") {
        return Builtin::kMat4X4;
    }
    if (str == "mat4x4f") {
        return Builtin::kMat4X4F;
    }
    if (str == "mat4x4h") {
        return Builtin::kMat4X4H;
    }
    if (str == "ptr") {
        return Builtin::kPtr;
    }
    if (str == "sampler") {
        return Builtin::kSampler;
    }
    if (str == "sampler_comparison") {
        return Builtin::kSamplerComparison;
    }
    if (str == "texture_1d") {
        return Builtin::kTexture1D;
    }
    if (str == "texture_2d") {
        return Builtin::kTexture2D;
    }
    if (str == "texture_2d_array") {
        return Builtin::kTexture2DArray;
    }
    if (str == "texture_3d") {
        return Builtin::kTexture3D;
    }
    if (str == "texture_cube") {
        return Builtin::kTextureCube;
    }
    if (str == "texture_cube_array") {
        return Builtin::kTextureCubeArray;
    }
    if (str == "texture_depth_2d") {
        return Builtin::kTextureDepth2D;
    }
    if (str == "texture_depth_2d_array") {
        return Builtin::kTextureDepth2DArray;
    }
    if (str == "texture_depth_cube") {
        return Builtin::kTextureDepthCube;
    }
    if (str == "texture_depth_cube_array") {
        return Builtin::kTextureDepthCubeArray;
    }
    if (str == "texture_depth_multisampled_2d") {
        return Builtin::kTextureDepthMultisampled2D;
    }
    if (str == "texture_external") {
        return Builtin::kTextureExternal;
    }
    if (str == "texture_multisampled_2d") {
        return Builtin::kTextureMultisampled2D;
    }
    if (str == "texture_storage_1d") {
        return Builtin::kTextureStorage1D;
    }
    if (str == "texture_storage_2d") {
        return Builtin::kTextureStorage2D;
    }
    if (str == "texture_storage_2d_array") {
        return Builtin::kTextureStorage2DArray;
    }
    if (str == "texture_storage_3d") {
        return Builtin::kTextureStorage3D;
    }
    if (str == "u32") {
        return Builtin::kU32;
    }
    if (str == "vec2") {
        return Builtin::kVec2;
    }
    if (str == "vec2f") {
        return Builtin::kVec2F;
    }
    if (str == "vec2h") {
        return Builtin::kVec2H;
    }
    if (str == "vec2i") {
        return Builtin::kVec2I;
    }
    if (str == "vec2u") {
        return Builtin::kVec2U;
    }
    if (str == "vec3") {
        return Builtin::kVec3;
    }
    if (str == "vec3f") {
        return Builtin::kVec3F;
    }
    if (str == "vec3h") {
        return Builtin::kVec3H;
    }
    if (str == "vec3i") {
        return Builtin::kVec3I;
    }
    if (str == "vec3u") {
        return Builtin::kVec3U;
    }
    if (str == "vec4") {
        return Builtin::kVec4;
    }
    if (str == "vec4f") {
        return Builtin::kVec4F;
    }
    if (str == "vec4h") {
        return Builtin::kVec4H;
    }
    if (str == "vec4i") {
        return Builtin::kVec4I;
    }
    if (str == "vec4u") {
        return Builtin::kVec4U;
    }
    return Builtin::kUndefined;
}

StringStream& operator<<(StringStream& out, Builtin value) {
    switch (value) {
        case Builtin::kUndefined:
            return out << "undefined";
        case Builtin::kAtomicCompareExchangeResultI32:
            return out << "__atomic_compare_exchange_result_i32";
        case Builtin::kAtomicCompareExchangeResultU32:
            return out << "__atomic_compare_exchange_result_u32";
        case Builtin::kFrexpResultAbstract:
            return out << "__frexp_result_abstract";
        case Builtin::kFrexpResultF16:
            return out << "__frexp_result_f16";
        case Builtin::kFrexpResultF32:
            return out << "__frexp_result_f32";
        case Builtin::kFrexpResultVec2Abstract:
            return out << "__frexp_result_vec2_abstract";
        case Builtin::kFrexpResultVec2F16:
            return out << "__frexp_result_vec2_f16";
        case Builtin::kFrexpResultVec2F32:
            return out << "__frexp_result_vec2_f32";
        case Builtin::kFrexpResultVec3Abstract:
            return out << "__frexp_result_vec3_abstract";
        case Builtin::kFrexpResultVec3F16:
            return out << "__frexp_result_vec3_f16";
        case Builtin::kFrexpResultVec3F32:
            return out << "__frexp_result_vec3_f32";
        case Builtin::kFrexpResultVec4Abstract:
            return out << "__frexp_result_vec4_abstract";
        case Builtin::kFrexpResultVec4F16:
            return out << "__frexp_result_vec4_f16";
        case Builtin::kFrexpResultVec4F32:
            return out << "__frexp_result_vec4_f32";
        case Builtin::kModfResultAbstract:
            return out << "__modf_result_abstract";
        case Builtin::kModfResultF16:
            return out << "__modf_result_f16";
        case Builtin::kModfResultF32:
            return out << "__modf_result_f32";
        case Builtin::kModfResultVec2Abstract:
            return out << "__modf_result_vec2_abstract";
        case Builtin::kModfResultVec2F16:
            return out << "__modf_result_vec2_f16";
        case Builtin::kModfResultVec2F32:
            return out << "__modf_result_vec2_f32";
        case Builtin::kModfResultVec3Abstract:
            return out << "__modf_result_vec3_abstract";
        case Builtin::kModfResultVec3F16:
            return out << "__modf_result_vec3_f16";
        case Builtin::kModfResultVec3F32:
            return out << "__modf_result_vec3_f32";
        case Builtin::kModfResultVec4Abstract:
            return out << "__modf_result_vec4_abstract";
        case Builtin::kModfResultVec4F16:
            return out << "__modf_result_vec4_f16";
        case Builtin::kModfResultVec4F32:
            return out << "__modf_result_vec4_f32";
        case Builtin::kPackedVec3:
            return out << "__packed_vec3";
        case Builtin::kArray:
            return out << "array";
        case Builtin::kAtomic:
            return out << "atomic";
        case Builtin::kBool:
            return out << "bool";
        case Builtin::kF16:
            return out << "f16";
        case Builtin::kF32:
            return out << "f32";
        case Builtin::kI32:
            return out << "i32";
        case Builtin::kMat2X2:
            return out << "mat2x2";
        case Builtin::kMat2X2F:
            return out << "mat2x2f";
        case Builtin::kMat2X2H:
            return out << "mat2x2h";
        case Builtin::kMat2X3:
            return out << "mat2x3";
        case Builtin::kMat2X3F:
            return out << "mat2x3f";
        case Builtin::kMat2X3H:
            return out << "mat2x3h";
        case Builtin::kMat2X4:
            return out << "mat2x4";
        case Builtin::kMat2X4F:
            return out << "mat2x4f";
        case Builtin::kMat2X4H:
            return out << "mat2x4h";
        case Builtin::kMat3X2:
            return out << "mat3x2";
        case Builtin::kMat3X2F:
            return out << "mat3x2f";
        case Builtin::kMat3X2H:
            return out << "mat3x2h";
        case Builtin::kMat3X3:
            return out << "mat3x3";
        case Builtin::kMat3X3F:
            return out << "mat3x3f";
        case Builtin::kMat3X3H:
            return out << "mat3x3h";
        case Builtin::kMat3X4:
            return out << "mat3x4";
        case Builtin::kMat3X4F:
            return out << "mat3x4f";
        case Builtin::kMat3X4H:
            return out << "mat3x4h";
        case Builtin::kMat4X2:
            return out << "mat4x2";
        case Builtin::kMat4X2F:
            return out << "mat4x2f";
        case Builtin::kMat4X2H:
            return out << "mat4x2h";
        case Builtin::kMat4X3:
            return out << "mat4x3";
        case Builtin::kMat4X3F:
            return out << "mat4x3f";
        case Builtin::kMat4X3H:
            return out << "mat4x3h";
        case Builtin::kMat4X4:
            return out << "mat4x4";
        case Builtin::kMat4X4F:
            return out << "mat4x4f";
        case Builtin::kMat4X4H:
            return out << "mat4x4h";
        case Builtin::kPtr:
            return out << "ptr";
        case Builtin::kSampler:
            return out << "sampler";
        case Builtin::kSamplerComparison:
            return out << "sampler_comparison";
        case Builtin::kTexture1D:
            return out << "texture_1d";
        case Builtin::kTexture2D:
            return out << "texture_2d";
        case Builtin::kTexture2DArray:
            return out << "texture_2d_array";
        case Builtin::kTexture3D:
            return out << "texture_3d";
        case Builtin::kTextureCube:
            return out << "texture_cube";
        case Builtin::kTextureCubeArray:
            return out << "texture_cube_array";
        case Builtin::kTextureDepth2D:
            return out << "texture_depth_2d";
        case Builtin::kTextureDepth2DArray:
            return out << "texture_depth_2d_array";
        case Builtin::kTextureDepthCube:
            return out << "texture_depth_cube";
        case Builtin::kTextureDepthCubeArray:
            return out << "texture_depth_cube_array";
        case Builtin::kTextureDepthMultisampled2D:
            return out << "texture_depth_multisampled_2d";
        case Builtin::kTextureExternal:
            return out << "texture_external";
        case Builtin::kTextureMultisampled2D:
            return out << "texture_multisampled_2d";
        case Builtin::kTextureStorage1D:
            return out << "texture_storage_1d";
        case Builtin::kTextureStorage2D:
            return out << "texture_storage_2d";
        case Builtin::kTextureStorage2DArray:
            return out << "texture_storage_2d_array";
        case Builtin::kTextureStorage3D:
            return out << "texture_storage_3d";
        case Builtin::kU32:
            return out << "u32";
        case Builtin::kVec2:
            return out << "vec2";
        case Builtin::kVec2F:
            return out << "vec2f";
        case Builtin::kVec2H:
            return out << "vec2h";
        case Builtin::kVec2I:
            return out << "vec2i";
        case Builtin::kVec2U:
            return out << "vec2u";
        case Builtin::kVec3:
            return out << "vec3";
        case Builtin::kVec3F:
            return out << "vec3f";
        case Builtin::kVec3H:
            return out << "vec3h";
        case Builtin::kVec3I:
            return out << "vec3i";
        case Builtin::kVec3U:
            return out << "vec3u";
        case Builtin::kVec4:
            return out << "vec4";
        case Builtin::kVec4F:
            return out << "vec4f";
        case Builtin::kVec4H:
            return out << "vec4h";
        case Builtin::kVec4I:
            return out << "vec4i";
        case Builtin::kVec4U:
            return out << "vec4u";
    }
    return out << "<unknown>";
}

}  // namespace tint::builtin
