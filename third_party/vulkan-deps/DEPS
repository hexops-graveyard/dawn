# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '7ca4dfa06158b923a122922a268c80d9d2e32a3f',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'bab4e5911b1bfa5a86bc80006b7301ae48363844',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '449bc986ba6f4c5e10e32828783f9daef2a77644',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '926ff6d1bab0f6982838ac8ec212151563b1a42d',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'c5b7a2fa18750e435e91e06a50cdc5451c5b9abd',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '90fd66f60fa7de10c91030f8c88b2a5c7c377784',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '58051062663477240484c8904459762ad544ba18',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'cefa7fd82e226e4ecb5c982003149749e02ec376',
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
