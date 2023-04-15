// abseil-cpp now depends on `pthread.h`, it previously didn't. But this appears to
// be a bug in abseil of sorts, because if you have `ABSL_FORCE_THREAD_IDENTITY_MODE` set
// to `ABSL_THREAD_IDENTITY_MODE_USE_CPP11` it doesn't appear to be used/needed.
// 
// [Zig doesn't ship with pthread for the MinGW / `x86_64-windows-gnu` target](ziglang/zig#10989),
// and so the header is missing - but we don't actually need it, so we just add an
// empty file to prevent the missing include error.
