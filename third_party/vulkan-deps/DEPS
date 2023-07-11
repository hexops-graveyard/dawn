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
  'spirv_cross_revision': 'b8e742c91ba47eb3238c939ee11ec9ba2ba247bf',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '3469b164e25cee24435029a569933cb42578db5d',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '870fd1e17aff8ede9aa12e647754780067306fe6',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'ad5f8ee9750e99c5397d44c075ae5d8a38271de4',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '9d38cccf33e02502534081f050bae5dee08ed7db',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '39090f9152287903b8fc82877f19366d2f9addaa',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '2221fe60db89d0442ad26b1f50f00f976414df4b',
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
