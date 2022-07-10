#!/usr/bin/env bash
set -ex

# Determined via editor regexp searches for the following:
# (make sure your editor is searching all files / not respecting gitignore)
#
# action\(".*gen
# dawn_json_generator\(
# dawn_generator\(
# spvtools_language_header\("
# spvtools_core_tables\("
# spvtools_core_enums\("
# spvtools_glsl_tables\("
# spvtools_opencl_tables\("
# spvtools_vendor_tables = 
#
# Excluding:
#   generate_v8_inspector_fuzzer_corpus
#   gen_javascript_parser_proto
#   generate_about_tracing
#   tint_generate_wgsl_corpus
#   emscripten_bits_gen
#
ninja -C ./out/Debug \
    remove_stale_autogen_files \
    vulkan_gen_icd_json_file \
    vulkan_gen_json_files \
    headers_gen \
    cpp_headers_gen \
    cpp_gen \
    proc_gen \
    webgpu_headers_gen \
    utils_gen \
    webgpu_dawn_native_proc_gen \
    mock_webgpu_gen \
    gen \
    dawn_version_gen \
    dawn_gpu_info_gen \
    opengl_loader_gen \
    third_party/vulkan-deps/spirv-tools/src:spvtools_language_header_debuginfo \
    third_party/vulkan-deps/spirv-tools/src:spvtools_language_header_cldebuginfo100 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_language_header_vkdebuginfo100 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_core_tables_unified1 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_core_enums_unified1 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_glsl_tables_glsl1-0 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_opencl_tables_opencl1-0 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_spv-amd-shader-explicit-vertex-parameter \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_spv-amd-shader-trinary-minmax \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_spv-amd-gcn-shader \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_spv-amd-shader-ballot \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_debuginfo \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_opencl.debuginfo.100 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_nonsemantic.clspvreflection \
    third_party/vulkan-deps/spirv-tools/src:spvtools_vendor_tables_nonsemantic.shader.debuginfo.100 \
    third_party/vulkan-deps/spirv-tools/src:spvtools_generators_inc \
    third_party/vulkan-deps/spirv-tools/src:spvtools_build_version
