#!/usr/bin/env bash
set -exuo pipefail

echo "Note: You should run gclient sync before this script"

# Remove gitmodules, some third_party/ repositories contain these and leaving them around would
# cause any recursive submodule clones to fail because e.g. some reference internal Google
# repositories. We don't want them anyway.
sh -c 'find . | grep .gitmodules | xargs rm'

# Turn subrepositories into regular folders.
rm -rf third_party/abseil-cpp/.git
rm -rf third_party/angle/.git
rm -rf third_party/swiftshader/.git
rm -rf third_party/tint/.git
rm -rf third_party/vulkan_memory_allocator/.git
rm -rf third_party/zlib/.git
rm -rf third_party/vulkan-deps/.git
rm -rf third_party/vulkan-deps/glslang/src/.git
rm -rf third_party/vulkan-deps/spirv-cross/src/.git
rm -rf third_party/vulkan-deps/spirv-headers/src/.git
rm -rf third_party/vulkan-deps/spirv-tools/src/.git
rm -rf third_party/vulkan-deps/vulkan-headers/src/.git
rm -rf third_party/vulkan-deps/vulkan-loader/src/.git
rm -rf third_party/vulkan-deps/vulkan-tools/src/.git
rm -rf third_party/vulkan-deps/vulkan-validation-layers/src/.git

git add third_party/
git commit -s -m 'update dependencies'
