# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '72713baf74125413fbe20ffb06a27cff5913c1d0',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '2d3a152081ca6e6bea7093940d0f81088fe4d01c',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '6e09e44cd88a5297433411b2ee52f4cf9f50fa90',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': 'd33bea584707c3509065010c45d9b79c54c8376b',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'cb71b646f1389822409a281252689492a18905b9',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '676e5308394e48cbc0f627f07a595b9488261184',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '17edcc1455855055b8aa5b898aca86f94d35d9d5',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '4bd85410dec98af7f7374a48348dd7239ea2b9a7',
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
