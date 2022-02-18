#!/usr/bin/env bash
set -exuo pipefail

echo "Note: You should run ./mach/generate.sh before this script"

git add -f out/Debug
git reset HEAD -- **/*.ninja*
git reset HEAD -- out/Debug/args.gn **/*.gn
git reset HEAD -- **/*.runtime_deps
git reset HEAD -- **/*.stamp
git reset HEAD -- **/*.allowed_output_dirs
git reset HEAD -- **/*.expected_outputs
git reset HEAD -- **/*.stale_dirs
git reset HEAD -- **/*.json_tarball.d
git reset HEAD -- out/Debug/gen/third_party/vulkan-deps/vulkan-validation-layers/src/old_vvl_files_are_removed
