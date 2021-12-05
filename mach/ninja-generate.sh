#!/usr/bin/env bash
set -ex

# Determined via editor regexp searches for:
#
# action\(.*gen
# dawn_json_generator\(
# dawn_generator\(
#
# Excluding:
#   tint_generate_wgsl_corpus
#   webgpu_headers_gen
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
    dawn_native_utils_gen \
    dawn_wire_gen \
    dawn_native_opengl_loader_gen
