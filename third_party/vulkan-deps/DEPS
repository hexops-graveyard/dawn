# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'ca8d07d0bc1c6390b83915700439fa7719de6a2a',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '4be568c0047163d61859c0be2411b48d29672ba7',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': 'aa331ab0ffcb3a67021caa1a0c1c9017712f2f31',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': 'c51e2afe001f4c8380c096e4416f3511798d859a',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '78448eda6ed5911c6828d5305ae750e3aab65d15',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '125b4f665cf4cd192ac216e1e85fc6918a3fff0c',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '80e16af0fd8f1f03374e4cc4eea4822520967e08',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '947366e2ce15e18a31b55367109a59be77c14bb5',
}

deps = {
  'glslang/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/glslang@{glslang_revision}',
  },

  'spirv-cross/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/SPIRV-Cross@{spirv_cross_revision}',
  },

  'spirv-headers/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/SPIRV-Headers@{spirv_headers_revision}',
  },

  'spirv-tools/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/SPIRV-Tools@{spirv_tools_revision}',
  },

  'vulkan-headers/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-Headers@{vulkan_headers_revision}',
  },

  'vulkan-loader/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-Loader@{vulkan_loader_revision}',
  },

  'vulkan-tools/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-Tools@{vulkan_tools_revision}',
  },

  'vulkan-validation-layers/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-ValidationLayers@{vulkan_validation_revision}',
  },
}
