#!/usr/bin/env bash
set -ex

# Determined via editor regexp searches for:
#
# action\(.*gen
# dawn_json_generator\(
# dawn_generator\(
# spvtools_language_header\("
#
# Excluding:
#   tint_generate_wgsl_corpus
#   emscripten_bits_gen
#
ninja -C ./out/Debug \
    remove_stale_autogen_files \
    spvtools_generators_inc \
    vulkan_gen_icd_json_file \
    vulkan_gen_json_files \
    dawn_headers_gen \
    dawncpp_headers_gen \
    dawncpp_gen \
    dawn_proc_gen \
    webgpu_headers_gen \
    dawn_native_utils_gen \
    webgpu_dawn_native_proc_gen \
    dawn_wire_gen \
    dawn_native_opengl_loader_gen \
    spvtools_language_header_debuginfo \
    spvtools_language_header_cldebuginfo100 \
    spvtools_language_header_vkdebuginfo100
