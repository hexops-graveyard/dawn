# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True
git_dependencies = 'SYNC'

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'bfd96d3044e1e2b0522a71166203ed4ddcf8d6e5',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'bccaa94db814af33d8ef05c153e7c34d8bd4d685',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': 'f14a663c84e8da4776bd615ac19450aa4d03cd71',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '1d14d84f291805ce845a0e5b9775e5e0ab11995b',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'a3b683653e6a498514ef8a1865594810e91c594c',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '5bc25766b0fa8cd17d4f1f112a5c58828997cf81',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'b8f2f1406ef3e7b9a2e01edaaaf62d82eef1eb00',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '63fbea2af66e44d4bf3a31a2599dc42644a7473d',
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
