# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '1aefd184a602c3efe414cf0208ab36a720d19e95',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '3327924addfcffe8f1a4119cb09c1ad353fe1190',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '29ba2493125effc581532518add689613cebfec7',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': 'dd03c1fca45df87755b75526438dfd2f5b374865',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '63af1cf1ee906ba4dcd5a324bdd0201d4f4bfd12',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '50df6bc578c851ddc7ec1f3b9f631918a4071b03',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '4ad4313da0a8d374efc61d744e7132c38b2a2dbd',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '8b2cdce023e021e0ac4cb2817bf510cd4e6fb529',
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
