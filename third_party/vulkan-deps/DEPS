# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'cd2082e0584d4e39d11e3f401184e0d558ab304f',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '7512345f61e5f9b543ebb87df678f3fe7735587b',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '1feaf4414eb2b353764d01d88f8aa4bcc67b60db',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '42267721e1d67ccc9fada23899357bb9b25ace23',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'a3dd2655a3a68c2a67c55a0f8b77dcb8b166ada2',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'e4895e86f7da0226b92fcc29d53bbf4e0bb55d1f',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '5bcfa1605e110150710170bfe199aa60e7f048fe',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'e894873f2245b3142f615b4e938a665ab8f8977e',
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
