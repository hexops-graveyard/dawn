# Mach engine fork of Dawn

This is a (super minimal) fork of Dawn for [Mach engine](https://github.com/hexops/mach).

## Branches

| Branch     | Description                                                                                                        |
|------------|--------------------------------------------------------------------------------------------------------------------|
| `upstream` | Tracks `main` from dawn.googlesource.com, zero changes.                                                            |
| `main`     | `mach/` scripts, and sometimes temporary patches we're upstreaming. `upstream` changes merged into here regularly. |
| `generated-<date>` | `main`, but with all generated sources and third-party dependencies committed.                             |

## Updating

Periodically, we do the following.

### Update `upstream` branch

```sh
git remote add upstream https://dawn.googlesource.com/dawn
git fetch upstream
git push origin refs/remotes/upstream/main:refs/heads/upstream
```

### Update `main` branch

```sh
git checkout main
git merge upstream
git push
```

### Create a new `generated-<date>` branch

```sh
git checkout main
git checkout -B generated-2022-02-16
```

Compare the diff between this generated branch and the prior generated branch to determine if any changes need to be made to the mach/gpu-dawn `build.zig` files. In particular look out for changes to (`BUILD`) `.gn` files, `.gni` files.

(optional) Run `gn args out/Debug` (set `use_system_xcode=true`) and `ninja -C out/Debug` to build Dawn & confirm your build works.

```sh
rm -rf build/ 
gclient sync
```

At this point there will be quite a large diff to add all of the `third_party/` dependencies we will commit.

Stage and review the changes:

```sh
./mach/add-dependencies.sh
```

Alter the above script as needed to include/exclude files. Make sure test files, documentation, `.gitmodules`, etc. are not included. Commit the result:

```sh
git commit -s -m 'generated: add dependencies'
```

Perform code generation:

```sh
./mach/generate.sh
```

Commit the generated code, e.g. headers in `out/Debug`.

```sh
git commit -s -m 'generated: commit generated code'
```

Confirm that `zig build run-dawn-example` works in `mach/gpu`
