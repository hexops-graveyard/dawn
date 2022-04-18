#!/usr/bin/env bash
set -exuo pipefail

echo "Note: You should run gclient sync before this script"

# Remove gitmodules, some third_party/ repositories contain these and leaving them around would
# cause any recursive submodule clones to fail because e.g. some reference internal Google
# repositories. We don't want them anyway.
sh -c 'find . | grep .gitmodules | xargs rm'

# Turn subrepositories into regular folders.
sh -c 'find third_party/ -type d | grep .git/ | xargs rm -rf'
rm -rf third_party/vulkan-deps/.gitignore

# Remove files that are not needed.
find third_party | grep /tests/ | xargs -n1 rm -rf || true
find third_party | grep /docs/ | xargs -n1 rm -rf || true
find third_party | grep /samples/ | xargs -n1 rm -rf || true
find third_party | grep CMake | xargs -n1 rm -rf || true
rm -rf third_party/abseil-cpp/.github/
rm -rf third_party/abseil-cpp/ci
rm -rf third_party/abseil-cpp/absl/time/internal/cctz/testdata
rm -rf third_party/googletest/
rm -rf third_party/glfw/
rm -rf third_party/llvm-build/
rm -rf third_party/tint/test/
rm -rf third_party/tint/fuzzers/
rm -rf third_party/tint/tools/
rm -rf third_party/tint/kokoro/
rm -rf third_party/tint/infra/
rm -rf third_party/angle/doc/
rm -rf third_party/angle/extensions/
rm -rf third_party/angle/third_party/logdog/
rm -rf third_party/angle/src/android_system_settings
rm -rf third_party/vulkan-deps/glslang/src/Test
rm -rf third_party/vulkan-deps/spirv-cross
rm -rf third_party/vulkan-deps/spirv-tools/src/test
rm -rf third_party/vulkan-deps/spirv-tools/src/source/fuzz/
rm -rf third_party/vulkan-deps/spirv-tools/src/kokoro/
rm -rf third_party/vulkan-deps/glslang/src/kokoro/
rm -rf third_party/vulkan-deps/glslang/src/gtests/
rm -rf third_party/vulkan-deps/vulkan-tools/src/cube/
rm -rf third_party/vulkan-deps/vulkan-tools/src/scripts/
rm -rf third_party/vulkan-deps/vulkan-tools/src/vulkaninfo/
rm -rf third_party/vulkan-deps/vulkan-tools/src/windows-runtime-installer/
rm -rf third_party/vulkan-deps/vulkan-validation-layers/src/scripts/
rm -rf third_party/vulkan_memory_allocator/build/src/Release/
rm -rf third_party/vulkan_memory_allocator/build/src/VmaReplay/
rm -rf third_party/vulkan_memory_allocator/tools/
rm -rf third_party/zlib/google/test/
rm -rf third_party/webgpu-cts/
rm -rf third_party/benchmark/
rm -rf third_party/gpuweb-cts/
rm -rf third_party/protobuf/
rm -rf third_party/markupsafe/
rm -rf third_party/jinja2/
rm -rf third_party/catapult/

rm -rf third_party/swiftshader/third_party/SPIRV-Tools # already in third_party/vulkan-deps/spirv-tools
rm -rf third_party/swiftshader/third_party/SPIRV-Headers # already in third_party/vulkan-deps/spirv-headers
rm -rf third_party/swiftshader/third_party/llvm-subzero # already in 

git add -f third_party/
echo "you may now 'git commit -s -m 'generated: commit vendored dependencies' if you are happy with the staged changes"
