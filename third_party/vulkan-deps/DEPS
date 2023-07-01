# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '3ebb72cc7429f0ab8218104dc3687c659c0f364d',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'aafcc207ea82308722124db2575aa95f42cb99c9',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '3469b164e25cee24435029a569933cb42578db5d',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': 'd3b0a522cec6cec4f241a6d1a7650096768cc43a',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'ad5f8ee9750e99c5397d44c075ae5d8a38271de4',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'dce85674e249f7b6956842dd6df067b70060c483',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '2e5260d44c662d31357e0cd3e430957cddcf1a6e',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '4400858043f909ea86076b6f47a61b51ec8d58f9',
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
