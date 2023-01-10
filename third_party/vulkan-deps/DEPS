# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '06a7078ce74ab5c7801a165b8145859678831fb8',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'cded61dde3f78a8d2a563a99501ac855b2e4ffab',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': 'd13b52222c39a7e9a401b44646f0ca3a640fbd47',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': 'f62e121b0df5374d1f043d1fbda98467406af0b1',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '5eeb2c4c570ce92f5f48bf667e39e9d4da2ef13a',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'b0ab61b46700bb0806f0e8996d793bfb4b7b1a7c',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '7b798e3e47824c94ffc6c8e75b0440bb78d2b7e2',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '38be3b2ccec796ef814eff46e94ff829142a7798',
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
