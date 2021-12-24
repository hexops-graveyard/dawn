## Updating

Process for updating Dawn:

1. `git remote add upstream https://dawn.googlesource.com/dawn`
2. `git checkout main && git checkout -B update-nov-30` (replace date with current date)
3. `git fetch upstream && git merge upstream/main`
4. Send PR to merge `update-nov-30` into `main` of hexops/dawn
5. Review that PR and make GitHub review notes of: any changes to (`BUILD`) `.gn` files, `.gni` files
6. (optional) `gn args out/Debug` (set `use_system_xcode=true`) and `ninja -C out/Debug` to build Dawn. Confirm your build works.
7. `rm -rf out/ third_party/ build/ && git checkout upstream/main -- third_party/ out/`
8. `gclient sync` At this point there will be quite a large diff as many `third_party/` dependencies we commit will have changed.
9.  Stage and review the changes to the `third_party/` directory by running `./mach/add-dependencies.sh`. Alter the script to include/exclude files as needed, commit the result. Make sure test files, documentation, `.gitmodules`, etc. are not included.
10. Run `./mach/generate.sh` and Ensure any header updates in `out/Debug` are committed.
11. Address all the previous GitHub review notes you created by updating https://github.com/hexops/mach/blob/main/gpu/build_dawn.zig - send a PR for that and link to the hexops/dawn one.
12. Confirm that `zig build run-dawn-example` works in `mach/gpu`
