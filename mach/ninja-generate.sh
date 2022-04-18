#!/usr/bin/env bash
set -ex

# Determined via editor regexp searches for the following:
# (make sure your editor is searching all files / not respecting .gitignore)
# excluding files: *fuzzer*,*catapult*,*webgpu-cts*
#
# action\(".*gen
# dawn_json_generator\(
# dawn_generator\(
#
# Excluding:
#   spvtools_generators_inc
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
    opengl_loader_gen
