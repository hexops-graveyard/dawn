# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '06ac14141222bc059f48609b9a4a68fdb6fc4814',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'd7cae5e7cd326ca0ebfb2a7ac4e634a63ecfe19f',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '46b7918218d02b678b9405da538928a0f2c286bb',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '671f6e633f4233a6e02e66a0b4d54ee1e67fa045',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '76f00ef6cbb1886eb1162d1fa39bee8b51e22ee8',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '71bd6240afaef2c199b47f26d715091fa6fdf4f8',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'ef20059aea7ec24d0842edca2f75255eaa33a7b0',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'd3be3175c287da3b82fc50d8544417dd85d4eb9b',
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
