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
  'spirv_cross_revision': 'd26c233e1c2629fec1ae1b6fdf538958e5d52bff',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '1feaf4414eb2b353764d01d88f8aa4bcc67b60db',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '9743701ed5e497805a5ab8bb9c8fb3843b200e8c',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '65ad768d8603671fc1085fe115019e72a595ced8',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '22407d7804f111fbc0e31fa0db592d658e19ae8b',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'a7bc1fe90ff58bebf95470ebcb8670ea22907795',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '6ab6adca3ee58d86f62461ae420d179ecba72513',
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
