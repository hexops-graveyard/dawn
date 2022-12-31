# Mach engine fork of Dawn

This is a (super minimal) fork of Dawn for [Mach engine](https://github.com/hexops/mach).

## Branches

| Branch     | Description                                                                                                        |
|------------|--------------------------------------------------------------------------------------------------------------------|
| `upstream` | Tracks `main` from dawn.googlesource.com, zero changes.                                                            |
| `main`     | `mach/` scripts, and sometimes temporary patches we're upstreaming. `upstream` changes merged into here regularly. |
| `generated-<date>` | `main`, but with all generated sources and third-party dependencies committed.                             |

## Updating Mach to the latest generated branch

Compare the diffs between the new generated branch and the old generated branch to determine if any changes need to be made to the mach/gpu-dawn `build.zig` files. In particular look out for changes to (`BUILD`) `.gn` files, `.gni` files:

```
git diff generated-2022-07-10..generated-2022-08-06 -- '*.gni'
git diff generated-2022-07-10..generated-2022-08-06 -- '*.gn'
git diff generated-2022-07-10..generated-2022-08-06 -- 'BUILD'
```

Then make certain to update `mach/gpu` by reviewing the diff between `webgpu.h` and `dawn.json`:

```
git diff generated-2022-07-10..generated-2022-08-06 -- 'out/Debug/gen/include/dawn/webgpu.h'
git diff generated-2022-07-10..generated-2022-08-06 -- 'dawn.json'
```

Confirm that `zig build run-example` works in `mach/gpu` before updating the hard-coded branch version that `mach/gpu` uses.
