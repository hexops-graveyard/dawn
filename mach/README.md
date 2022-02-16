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
TODO(slimsag)
```
