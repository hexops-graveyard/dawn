const std = @import("std");
const system_sdk = @import("system_sdk");

const Build = std.Build;

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "dawn",
        .target = target,
        .optimize = optimize,
    });

    const opt = (Options{
        .debug = optimize == .Debug,

        .d3d12 = b.option(
            bool,
            "d3d12",
            "Use Direct3D 12",
        ),
        .metal = b.option(
            bool,
            "metal",
            "Use Metal",
        ),
        .vulkan = b.option(
            bool,
            "vulkan",
            "Use Vulkan",
        ),
        .desktop_gl = b.option(
            bool,
            "desktop-gl",
            "Use desktop GL",
        ),
        .opengl_es = b.option(
            bool,
            "opengl-es",
            "Use GLES",
        ),
        .separate_libs = b.option(
            bool,
            "separate-libs",
            "Install parts of Dawn as separate libraries",
        ) orelse false,
    }).detectDefaults(lib.target_info.target);

    lib.linkLibCpp();

    lib.addIncludePath("out/Debug/gen/include");
    lib.addIncludePath("include");
    //lib.addIncludePath("mingw_hacks");

    try buildLibDawnCommon(b, lib, opt);
    try buildLibDawnPlatform(b, lib, opt);
    try buildLibAbseilCpp(b, lib, opt);
    try buildLibDawnNative(b, lib, opt);
    try buildLibDawnWire(b, lib, opt);
    //try buildLibDawnUtils(b, lib, opt);
    try buildLibSPIRVTools(b, lib, opt);
    try buildLibTint(b, lib, opt);
    //if (options.d3d12.?) try buildLibDxcompiler(b, lib_dawn, options);

    lib.install();
}

pub const Options = struct {
    /// Defaults to true on Windows
    d3d12: ?bool = null,

    /// Defaults to true on Darwin
    metal: ?bool = null,

    /// Defaults to true on Linux, Fuchsia
    // TODO(build-system): enable on Windows if we can cross compile Vulkan
    vulkan: ?bool = null,

    /// Defaults to true on Linux
    desktop_gl: ?bool = null,

    /// Defaults to true on Android, Linux, Windows, Emscripten
    // TODO(build-system): not respected at all currently
    opengl_es: ?bool = null,

    /// Whether or not minimal debug symbols should be emitted. This is -g1 in most cases, enough to
    /// produce stack traces but omitting debug symbols for locals. For spirv-tools and tint in
    /// specific, -g0 will be used (no debug symbols at all) to save an additional ~39M.
    debug: bool = false,

    /// Whether or not to produce separate static libraries for each component of Dawn (reduces
    /// iteration times when building from source / testing changes to Dawn source code.)
    separate_libs: bool = false,

    /// Detects the default options to use for the given target.
    fn detectDefaults(self: Options, target: std.Target) Options {
        const tag = target.os.tag;

        var options = self;
        if (options.d3d12 == null) options.d3d12 = tag == .windows;
        if (options.metal == null) options.metal = tag.isDarwin();
        if (options.vulkan == null) options.vulkan = tag == .fuchsia or isLinuxDesktopLike(tag);

        // TODO(build-system): technically Dawn itself defaults desktop_gl to true on Windows.
        if (options.desktop_gl == null) options.desktop_gl = isLinuxDesktopLike(tag);

        // TODO(build-system): OpenGL ES
        options.opengl_es = false;
        // if (options.opengl_es == null) options.opengl_es = tag == .windows or tag == .emscripten or target.isAndroid() or linux_desktop_like;

        return options;
    }
};

fn isLinuxDesktopLike(tag: std.Target.Os.Tag) bool {
    return switch (tag) {
        .linux,
        .freebsd,
        .kfreebsd,
        .openbsd,
        .dragonfly,
        => true,
        else => false,
    };
}

fn appendFlags(
    step: *std.build.CompileStep,
    flags: *std.ArrayList([]const u8),
    debug_symbols: bool,
    is_cpp: bool,
) !void {
    if (debug_symbols) try flags.append("-g1") else try flags.append("-g0");
    if (is_cpp) try flags.append("-std=c++17");
    if (isLinuxDesktopLike(step.target_info.target.os.tag)) {
        try flags.append("-DDAWN_USE_X11");
        try flags.append("-DDAWN_USE_WAYLAND");
    }
}

// Builds common sources; derived from src/common/BUILD.gn
fn buildLibDawnCommon(
    b: *Build,
    step: *std.build.CompileStep,
    options: Options,
) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "dawn-common",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(&.{
        "-Isrc",
        "-Iout/Debug/gen/include",
        "-Iout/Debug/gen/src",
    });
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/dawn/common/",
            "out/Debug/gen/src/dawn/common/",
        },
        .flags = flags.items,
        .excluding_contains = &.{
            "test",
            "benchmark",
            "mock",
            "WindowsUtils.cpp",
        },
    });

    var cpp_sources = std.ArrayList([]const u8).init(b.allocator);
    if (step.target_info.target.os.tag == .macos) {
        // TODO(build-system): pass system SDK options through
        system_sdk.include(b, lib, .{});
        lib.linkFramework("Foundation");
        try cpp_sources.append("src/dawn/common/SystemUtils_mac.mm");
    } else if (step.target_info.target.os.tag == .windows) {
        try cpp_sources.append("src/dawn/common/WindowsUtils.cpp");
    }

    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try cpp_flags.appendSlice(flags.items);
    try appendFlags(step, &cpp_flags, options.debug, true);
    lib.addCSourceFiles(cpp_sources.items, cpp_flags.items);
}

// Build dawn platform sources; derived from src/dawn/platform/BUILD.gn
fn buildLibDawnPlatform(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "dawn-platform",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };

    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try appendFlags(step, &cpp_flags, options.debug, true);
    try cpp_flags.appendSlice(&.{
        "-Isrc",
        "-Iinclude",
        "-Iout/Debug/gen/include",
    });

    var cpp_sources = std.ArrayList([]const u8).init(b.allocator);
    try cpp_sources.appendSlice(&.{
        "src/dawn/platform/DawnPlatform.cpp",
        "src/dawn/platform/WorkerThread.cpp",
        "src/dawn/platform/tracing/EventTracer.cpp",
    });

    lib.addCSourceFiles(cpp_sources.items, cpp_flags.items);
}

fn appendDawnEnableBackendTypeFlags(flags: *std.ArrayList([]const u8), options: Options) !void {
    const d3d12 = "-DDAWN_ENABLE_BACKEND_D3D12";
    const metal = "-DDAWN_ENABLE_BACKEND_METAL";
    const vulkan = "-DDAWN_ENABLE_BACKEND_VULKAN";
    const opengl = "-DDAWN_ENABLE_BACKEND_OPENGL";
    const desktop_gl = "-DDAWN_ENABLE_BACKEND_DESKTOP_GL";
    const opengl_es = "-DDAWN_ENABLE_BACKEND_OPENGLES";
    const backend_null = "-DDAWN_ENABLE_BACKEND_NULL";

    try flags.append(backend_null);
    if (options.d3d12.?) try flags.append(d3d12);
    if (options.metal.?) try flags.append(metal);
    if (options.vulkan.?) try flags.append(vulkan);
    if (options.desktop_gl.?) try flags.appendSlice(&.{ opengl, desktop_gl });
    if (options.opengl_es.?) try flags.appendSlice(&.{ opengl, opengl_es });
}

const dawn_d3d12_flags = &[_][]const u8{
    "-DDAWN_NO_WINDOWS_UI",
    "-D__EMULATE_UUID=1",
    "-Wno-nonportable-include-path",
    "-Wno-extern-c-compat",
    "-Wno-invalid-noreturn",
    "-Wno-pragma-pack",
    "-Wno-microsoft-template-shadow",
    "-Wno-unused-command-line-argument",
    "-Wno-microsoft-exception-spec",
    "-Wno-implicit-exception-spec-mismatch",
    "-Wno-unknown-attributes",
    "-Wno-c++20-extensions",
    "-D_CRT_SECURE_NO_WARNINGS",
    "-DWIN32_LEAN_AND_MEAN",
    "-DD3D10_ARBITRARY_HEADER_ORDERING",
    "-DNOMINMAX",
};

// Builds dawn native sources; derived from src/dawn/native/BUILD.gn
fn buildLibDawnNative(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "dawn-native",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };
    system_sdk.include(b, lib, .{});

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try appendDawnEnableBackendTypeFlags(&flags, options);
    try flags.appendSlice(&.{
        "-I.",
        "-Isrc",
        "-Iinclude",
        "-Ithird_party/vulkan-deps/spirv-tools/src/include",
        "-Ithird_party/abseil-cpp",
        "-Ithird_party/khronos",

        // TODO(build-system): make these optional
        "-DTINT_BUILD_SPV_READER=1",
        "-DTINT_BUILD_SPV_WRITER=1",
        "-DTINT_BUILD_WGSL_READER=1",
        "-DTINT_BUILD_WGSL_WRITER=1",
        "-DTINT_BUILD_MSL_WRITER=1",
        "-DTINT_BUILD_HLSL_WRITER=1",
        "-DTINT_BUILD_GLSL_WRITER=1",

        "-Iinclude/tint",
        "-Ithird_party/vulkan-deps/vulkan-tools/src/",

        "-Iout/Debug/gen/include",
        "-Iout/Debug/gen/src",

        "-Wno-deprecated-declarations",
    });
    if (options.d3d12.?) try flags.appendSlice(dawn_d3d12_flags);

    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "out/Debug/gen/src/dawn/",
            "src/dawn/native/",
            "src/dawn/native/utils/",
            "src/dawn/native/stream/",
        },
        .flags = flags.items,
        .excluding_contains = &.{
            "test",
            "benchmark",
            "mock",
            "SpirvValidation.cpp",
            "XlibXcbFunctions.cpp",
            "dawn_proc.c",
        },
    });

    // dawn_native_gen
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "out/Debug/gen/src/dawn/native/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark", "mock", "webgpu_dawn_native_proc.cpp" },
    });

    // TODO(build-system): could allow enable_vulkan_validation_layers here. See src/dawn/native/BUILD.gn
    // TODO(build-system): allow use_angle here. See src/dawn/native/BUILD.gn
    // TODO(build-system): could allow use_swiftshader here. See src/dawn/native/BUILD.gn

    var cpp_sources = std.ArrayList([]const u8).init(b.allocator);
    if (options.d3d12.?) {
        lib.linkSystemLibraryName("dxgi");
        lib.linkSystemLibraryName("dxguid");

        try cpp_sources.append("src/dawn/mingw_helpers.cpp");

        try appendLangScannedSources(b, lib, .{
            .rel_dirs = &.{
                "src/dawn/native/d3d12/",
            },
            .flags = flags.items,
            .excluding_contains = &.{ "test", "benchmark", "mock" },
        });
    }
    if (options.metal.?) {
        lib.linkFramework("Metal");
        lib.linkFramework("CoreGraphics");
        lib.linkFramework("Foundation");
        lib.linkFramework("IOKit");
        lib.linkFramework("IOSurface");
        lib.linkFramework("QuartzCore");

        try appendLangScannedSources(b, lib, .{
            .objc = true,
            .rel_dirs = &.{
                "src/dawn/native/metal/",
                "src/dawn/native/",
            },
            .flags = flags.items,
            .excluding_contains = &.{ "test", "benchmark", "mock" },
        });
    }

    const tag = step.target_info.target.os.tag;
    if (isLinuxDesktopLike(tag)) {
        lib.linkSystemLibraryName("X11");
        try cpp_sources.append("src/dawn/native/XlibXcbFunctions.cpp");
    }

    try cpp_sources.append("src/dawn/native/null/DeviceNull.cpp");

    if (options.desktop_gl.? or options.vulkan.?) {
        try cpp_sources.append("src/dawn/native/SpirvValidation.cpp");
    }

    if (options.desktop_gl.?) {
        try appendLangScannedSources(b, lib, .{
            .rel_dirs = &.{
                "out/Debug/gen/src/dawn/native/opengl/",
                "src/dawn/native/opengl/",
            },
            .flags = flags.items,
            .excluding_contains = &.{ "test", "benchmark", "mock" },
        });
    }

    if (options.vulkan.?) {
        try appendLangScannedSources(b, lib, .{
            .rel_dirs = &.{
                "src/dawn/native/vulkan/",
            },
            .flags = flags.items,
            .excluding_contains = &.{ "test", "benchmark", "mock" },
        });
        try cpp_sources.append("src/dawn/native/vulkan/external_memory/MemoryService.cpp");

        if (isLinuxDesktopLike(tag)) {
            try cpp_sources.appendSlice(&.{
                "src/dawn/native/vulkan/external_memory/MemoryServiceImplementationOpaqueFD.cpp",
                "src/dawn/native/vulkan/external_semaphore/SemaphoreServiceImplementationFD.cpp",
            });
        } else if (tag == .fuchsia) {
            try cpp_sources.appendSlice(&.{
                "src/dawn/native/vulkan/external_memory/MemoryServiceImplementationZirconHandle.cpp",
                "src/dawn/native/vulkan/external_semaphore/SemaphoreServiceImplementationZirconHandle.cpp",
            });
        } else if (step.target_info.target.isAndroid()) {
            try cpp_sources.appendSlice(&.{
                "src/dawn/native/vulkan/external_memory/MemoryServiceImplementationAHardwareBuffer.cpp",
                "src/dawn/native/vulkan/external_semaphore/SemaphoreServiceImplementationFD.cpp",
            });
            try cpp_sources.append("-DDAWN_USE_SYNC_FDS");
        } else {
            try cpp_sources.appendSlice(&.{
                "src/dawn/native/vulkan/external_memory/MemoryServiceImplementationNull.cpp",
                "src/dawn/native/vulkan/external_semaphore/SemaphoreServiceImplementationNull.cpp",
            });
        }
    }

    // TODO(build-system): fuchsia: add is_fuchsia here from upstream source file

    if (options.vulkan.?) {
        // TODO(build-system): vulkan
        //     if (enable_vulkan_validation_layers) {
        //       defines += [
        //         "DAWN_ENABLE_VULKAN_VALIDATION_LAYERS",
        //         "DAWN_VK_DATA_DIR=\"$vulkan_data_subdir\"",
        //       ]
        //     }
        //     if (enable_vulkan_loader) {
        //       data_deps += [ "${dawn_vulkan_loader_dir}:libvulkan" ]
        //       defines += [ "DAWN_ENABLE_VULKAN_LOADER" ]
        //     }
    }
    // TODO(build-system): swiftshader
    //     if (use_swiftshader) {
    //       data_deps += [
    //         "${dawn_swiftshader_dir}/src/Vulkan:icd_file",
    //         "${dawn_swiftshader_dir}/src/Vulkan:swiftshader_libvulkan",
    //       ]
    //       defines += [
    //         "DAWN_ENABLE_SWIFTSHADER",
    //         "DAWN_SWIFTSHADER_VK_ICD_JSON=\"${swiftshader_icd_file_name}\"",
    //       ]
    //     }
    //   }

    if (options.opengl_es.?) {
        // TODO(build-system): gles
        //   if (use_angle) {
        //     data_deps += [
        //       "${dawn_angle_dir}:libEGL",
        //       "${dawn_angle_dir}:libGLESv2",
        //     ]
        //   }
        // }
    }

    try cpp_sources.append("src/dawn/native/null/NullBackend.cpp");

    if (options.d3d12.?) {
        try cpp_sources.append("src/dawn/native/d3d12/D3D12Backend.cpp");
    }

    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try cpp_flags.appendSlice(flags.items);
    try appendFlags(step, &cpp_flags, options.debug, true);
    lib.addCSourceFiles(cpp_sources.items, cpp_flags.items);
}

// Builds tint sources; derived from src/tint/BUILD.gn
fn buildLibTint(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "tint",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(&.{
        // TODO(build-system): make these optional
        "-DTINT_BUILD_SPV_READER=1",
        "-DTINT_BUILD_SPV_WRITER=1",
        "-DTINT_BUILD_WGSL_READER=1",
        "-DTINT_BUILD_WGSL_WRITER=1",
        "-DTINT_BUILD_MSL_WRITER=1",
        "-DTINT_BUILD_HLSL_WRITER=1",
        "-DTINT_BUILD_GLSL_WRITER=1",

        "-I.",
        "-Iinclude/tint",

        // Required for TINT_BUILD_SPV_READER=1 and TINT_BUILD_SPV_WRITER=1, if specified
        "-Ithird_party/vulkan-deps",
        "-Ithird_party/vulkan-deps/spirv-tools/src",
        "-Ithird_party/vulkan-deps/spirv-tools/src/include",
        "-Ithird_party/vulkan-deps/spirv-headers/src/include",
        "-Iout/Debug/gen/third_party/vulkan-deps/spirv-tools/src",
        "-Iout/Debug/gen/third_party/vulkan-deps/spirv-tools/src/include",
        "-Iinclude",
    });

    // libtint_core_all_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint",
            "src/tint/constant/",
            "src/tint/diagnostic/",
            "src/tint/inspector/",
            "src/tint/reader/",
            "src/tint/resolver/",
            "src/tint/utils/",
            "src/tint/text/",
            "src/tint/type/",
            "src/tint/transform/",
            "src/tint/transform/utils",
            "src/tint/writer/",
            "src/tint/ast/",
            "src/tint/val/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "bench", "printer_windows", "printer_posix", "printer_other", "glsl.cc" },
    });

    var cpp_sources = std.ArrayList([]const u8).init(b.allocator);

    const tag = step.target_info.target.os.tag;
    if (tag == .windows) {
        try cpp_sources.append("src/tint/diagnostic/printer_windows.cc");
    } else if (tag.isDarwin() or isLinuxDesktopLike(tag)) {
        try cpp_sources.append("src/tint/diagnostic/printer_posix.cc");
    } else {
        try cpp_sources.append("src/tint/diagnostic/printer_other.cc");
    }

    // libtint_sem_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/sem/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark" },
    });

    // libtint_spv_reader_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/reader/spirv/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark" },
    });

    // libtint_spv_writer_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/writer/spirv/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "bench" },
    });

    // TODO(build-system): make optional
    // libtint_wgsl_reader_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/reader/wgsl/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "bench" },
    });

    // TODO(build-system): make optional
    // libtint_wgsl_writer_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/writer/wgsl/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "bench" },
    });

    // TODO(build-system): make optional
    // libtint_msl_writer_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/writer/msl/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "bench" },
    });

    // TODO(build-system): make optional
    // libtint_hlsl_writer_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/writer/hlsl/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "bench" },
    });

    // TODO(build-system): make optional
    // libtint_glsl_writer_src
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "src/tint/writer/glsl/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "bench" },
    });

    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try cpp_flags.appendSlice(flags.items);
    try appendFlags(step, &cpp_flags, options.debug, true);
    lib.addCSourceFiles(cpp_sources.items, cpp_flags.items);
}

// Builds third_party/vulkan-deps/spirv-tools sources; derived from third_party/vulkan-deps/spirv-tools/src/BUILD.gn
fn buildLibSPIRVTools(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "spirv-tools",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(&.{
        "-I.",
        "-Ithird_party/vulkan-deps/spirv-tools/src",
        "-Ithird_party/vulkan-deps/spirv-tools/src/include",
        "-Ithird_party/vulkan-deps/spirv-headers/src/include",
        "-Iout/Debug/gen/third_party/vulkan-deps/spirv-tools/src",
        "-Iout/Debug/gen/third_party/vulkan-deps/spirv-tools/src/include",
        "-Ithird_party/vulkan-deps/spirv-headers/src/include/spirv/unified1",
    });

    // spvtools
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "third_party/vulkan-deps/spirv-tools/src/source/",
            "third_party/vulkan-deps/spirv-tools/src/source/util/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark" },
    });

    // spvtools_val
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "third_party/vulkan-deps/spirv-tools/src/source/val/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark" },
    });

    // spvtools_opt
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "third_party/vulkan-deps/spirv-tools/src/source/opt/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark" },
    });

    // spvtools_link
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "third_party/vulkan-deps/spirv-tools/src/source/link/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark" },
    });
}

// Builds third_party/abseil sources; derived from:
//
// ```
// $ find third_party/abseil-cpp/absl | grep '\.cc' | grep -v 'test' | grep -v 'benchmark' | grep -v gaussian_distribution_gentables | grep -v print_hash_of | grep -v chi_square
// ```
//
fn buildLibAbseilCpp(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "abseil-cpp-common",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };
    system_sdk.include(b, lib, .{});

    const target = step.target_info.target;
    if (target.os.tag == .macos) lib.linkFramework("CoreFoundation");
    if (target.os.tag == .windows) lib.linkSystemLibraryName("bcrypt");

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(&.{
        "-Ithird_party/abseil-cpp",
        "-Wno-deprecated-declarations",
    });
    if (target.os.tag == .windows) try flags.appendSlice(&.{
        "-DABSL_FORCE_THREAD_IDENTITY_MODE=2",
        "-DWIN32_LEAN_AND_MEAN",
        "-DD3D10_ARBITRARY_HEADER_ORDERING",
        "-D_CRT_SECURE_NO_WARNINGS",
        "-DNOMINMAX",
        "-Imingw_hacks",
    });

    // absl
    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "third_party/abseil-cpp/absl/strings/",
            "third_party/abseil-cpp/absl/strings/internal/",
            "third_party/abseil-cpp/absl/strings/internal/str_format/",
            "third_party/abseil-cpp/absl/types/",
            "third_party/abseil-cpp/absl/flags/internal/",
            "third_party/abseil-cpp/absl/flags/",
            "third_party/abseil-cpp/absl/synchronization/",
            "third_party/abseil-cpp/absl/synchronization/internal/",
            "third_party/abseil-cpp/absl/hash/internal/",
            "third_party/abseil-cpp/absl/debugging/",
            "third_party/abseil-cpp/absl/debugging/internal/",
            "third_party/abseil-cpp/absl/status/",
            "third_party/abseil-cpp/absl/time/internal/cctz/src/",
            "third_party/abseil-cpp/absl/time/",
            "third_party/abseil-cpp/absl/container/internal/",
            "third_party/abseil-cpp/absl/numeric/",
            "third_party/abseil-cpp/absl/random/",
            "third_party/abseil-cpp/absl/random/internal/",
            "third_party/abseil-cpp/absl/base/internal/",
            "third_party/abseil-cpp/absl/base/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "_test", "_testing", "benchmark", "print_hash_of.cc", "gaussian_distribution_gentables.cc" },
    });
}

// Buids dawn wire sources; derived from src/dawn/wire/BUILD.gn
fn buildLibDawnWire(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "dawn-wire",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(&.{
        "-I.",
        "-Isrc",
        "-Iinclude",
        "-Iout/Debug/gen/include",
        "-Iout/Debug/gen/src",
    });

    try appendLangScannedSources(b, lib, .{
        .rel_dirs = &.{
            "out/Debug/gen/src/dawn/wire/",
            "out/Debug/gen/src/dawn/wire/client/",
            "out/Debug/gen/src/dawn/wire/server/",
            "src/dawn/wire/",
            "src/dawn/wire/client/",
            "src/dawn/wire/server/",
        },
        .flags = flags.items,
        .excluding_contains = &.{ "test", "benchmark", "mock" },
    });
}

// Builds dawn utils sources; derived from src/dawn/utils/BUILD.gn
fn buildLibDawnUtils(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const lib = if (!options.separate_libs) step else blk: {
        const separate_lib = b.addStaticLibrary(.{
            .name = "dawn-utils",
            .target = step.target,
            .optimize = if (options.debug) .Debug else .ReleaseFast,
        });
        separate_lib.linkLibCpp();
        separate_lib.install();
        step.linkLibrary(separate_lib);
        break :blk separate_lib;
    };

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try appendDawnEnableBackendTypeFlags(&flags, options);
    try flags.appendSlice(&.{
        //"-I" ++ deps.glfw_include_dir,
        "-Isrc",
        "-Iinclude",
        "-Iout/Debug/gen/include",
    });

    var cpp_sources = std.ArrayList([]const u8).init(b.allocator);
    try cpp_sources.appendSlice(&.{
        "src/dawn/utils/BackendBinding.cpp",
        "src/dawn/utils/NullBinding.cpp",
    });

    if (options.d3d12.?) {
        try cpp_sources.append("src/dawn/utils/D3D12Binding.cpp");
        try flags.appendSlice(dawn_d3d12_flags);
    }
    if (options.metal.?) {
        try cpp_sources.append("src/dawn/utils/MetalBinding.mm");
    }

    if (options.desktop_gl.?) {
        try cpp_sources.append("src/dawn/utils/OpenGLBinding.cpp");
    }

    if (options.vulkan.?) {
        try cpp_sources.append("src/dawn/utils/VulkanBinding.cpp");
    }

    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try cpp_flags.appendSlice(flags.items);
    try appendFlags(step, &cpp_flags, options.debug, true);
    lib.addCSourceFiles(cpp_sources.items, cpp_flags.items);
}

// TODO: libdxcompiler
// Buids dxcompiler sources; derived from libs/DirectXShaderCompiler/CMakeLists.txt
//fn buildLibDxcompiler(b: *Build, step: *std.build.CompileStep, options: Options) !*std.build.CompileStep {
//    const lib = if (!options.separate_libs) step else blk: {
//        const separate_lib = b.addStaticLibrary(.{
//            .name = "dxcompiler",
//            .target = step.target,
//            .optimize = if (options.debug) .Debug else .ReleaseFast,
//        });
//        separate_lib.linkLibCpp();
//            separate_lib.install();
//        break :blk separate_lib;
//    };
//    system_sdk.include(b, lib, .{});
//
//    lib.linkSystemLibraryName("oleaut32");
//    lib.linkSystemLibraryName("ole32");
//    lib.linkSystemLibraryName("dbghelp");
//    lib.linkSystemLibraryName("dxguid");
//    lib.linkLibCpp();
//
//    var flags = std.ArrayList([]const u8).init(b.allocator);
//    try flags.appendSlice(&.{
//        "-Ilibs/",
//        "-Ilibs/DirectXShaderCompiler/include/llvm/llvm_assert",
//        "-Ilibs/DirectXShaderCompiler/include",
//        "-Ilibs/DirectXShaderCompiler/build/include",
//        "-Ilibs/DirectXShaderCompiler/build/lib/HLSL",
//        "-Ilibs/DirectXShaderCompiler/build/lib/DxilPIXPasses",
//        "-Ilibs/DirectXShaderCompiler/build/include",
//        "-DUNREFERENCED_PARAMETER(x)=",
//        "-Wno-inconsistent-missing-override",
//        "-Wno-missing-exception-spec",
//        "-Wno-switch",
//        "-Wno-deprecated-declarations",
//        "-Wno-macro-redefined", // regex2.h and regcomp.c requires this for OUT redefinition
//        "-DMSFT_SUPPORTS_CHILD_PROCESSES=1",
//        "-DHAVE_LIBPSAPI=1",
//        "-DHAVE_LIBSHELL32=1",
//        "-DLLVM_ON_WIN32=1",
//    });
//
//    try appendLangScannedSources(b, lib, .{
//        .debug_symbols = false,
//        .rel_dirs = &.{
//            "libs/DirectXShaderCompiler/lib/Analysis/IPA",
//            "libs/DirectXShaderCompiler/lib/Analysis",
//            "libs/DirectXShaderCompiler/lib/AsmParser",
//            "libs/DirectXShaderCompiler/lib/Bitcode/Writer",
//            "libs/DirectXShaderCompiler/lib/DxcBindingTable",
//            "libs/DirectXShaderCompiler/lib/DxcSupport",
//            "libs/DirectXShaderCompiler/lib/DxilContainer",
//            "libs/DirectXShaderCompiler/lib/DxilPIXPasses",
//            "libs/DirectXShaderCompiler/lib/DxilRootSignature",
//            "libs/DirectXShaderCompiler/lib/DXIL",
//            "libs/DirectXShaderCompiler/lib/DxrFallback",
//            "libs/DirectXShaderCompiler/lib/HLSL",
//            "libs/DirectXShaderCompiler/lib/IRReader",
//            "libs/DirectXShaderCompiler/lib/IR",
//            "libs/DirectXShaderCompiler/lib/Linker",
//            "libs/DirectXShaderCompiler/lib/Miniz",
//            "libs/DirectXShaderCompiler/lib/Option",
//            "libs/DirectXShaderCompiler/lib/PassPrinters",
//            "libs/DirectXShaderCompiler/lib/Passes",
//            "libs/DirectXShaderCompiler/lib/ProfileData",
//            "libs/DirectXShaderCompiler/lib/Target",
//            "libs/DirectXShaderCompiler/lib/Transforms/InstCombine",
//            "libs/DirectXShaderCompiler/lib/Transforms/IPO",
//            "libs/DirectXShaderCompiler/lib/Transforms/Scalar",
//            "libs/DirectXShaderCompiler/lib/Transforms/Utils",
//            "libs/DirectXShaderCompiler/lib/Transforms/Vectorize",
//        },
//        .flags = flags.items,
//    });
//
//    try appendLangScannedSources(b, lib, .{
//        .debug_symbols = false,
//        .rel_dirs = &.{
//            "libs/DirectXShaderCompiler/lib/Support",
//        },
//        .flags = flags.items,
//        .excluding_contains = &.{
//            "DynamicLibrary.cpp", // ignore, HLSL_IGNORE_SOURCES
//            "PluginLoader.cpp", // ignore, HLSL_IGNORE_SOURCES
//            "Path.cpp", // ignore, LLVM_INCLUDE_TESTS
//            "DynamicLibrary.cpp", // ignore
//        },
//    });
//
//    try appendLangScannedSources(b, lib, .{
//        .debug_symbols = false,
//        .rel_dirs = &.{
//            "libs/DirectXShaderCompiler/lib/Bitcode/Reader",
//        },
//        .flags = flags.items,
//        .excluding_contains = &.{
//            "BitReader.cpp", // ignore
//        },
//    });
//}

fn appendLangScannedSources(
    b: *Build,
    step: *std.build.CompileStep,
    args: struct {
        debug_symbols: bool = false,
        flags: []const []const u8,
        rel_dirs: []const []const u8 = &.{},
        objc: bool = false,
        excluding: []const []const u8 = &.{},
        excluding_contains: []const []const u8 = &.{},
    },
) !void {
    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try cpp_flags.appendSlice(args.flags);
    try appendFlags(step, &cpp_flags, args.debug_symbols, true);
    const cpp_extensions: []const []const u8 = if (args.objc) &.{".mm"} else &.{ ".cpp", ".cc" };
    try appendScannedSources(b, step, .{
        .flags = cpp_flags.items,
        .rel_dirs = args.rel_dirs,
        .extensions = cpp_extensions,
        .excluding = args.excluding,
        .excluding_contains = args.excluding_contains,
    });

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(args.flags);
    try appendFlags(step, &flags, args.debug_symbols, false);
    const c_extensions: []const []const u8 = if (args.objc) &.{".m"} else &.{".c"};
    try appendScannedSources(b, step, .{
        .flags = flags.items,
        .rel_dirs = args.rel_dirs,
        .extensions = c_extensions,
        .excluding = args.excluding,
        .excluding_contains = args.excluding_contains,
    });
}

fn appendScannedSources(b: *Build, step: *std.build.CompileStep, args: struct {
    flags: []const []const u8,
    rel_dirs: []const []const u8 = &.{},
    extensions: []const []const u8,
    excluding: []const []const u8 = &.{},
    excluding_contains: []const []const u8 = &.{},
}) !void {
    var sources = std.ArrayList([]const u8).init(b.allocator);
    for (args.rel_dirs) |rel_dir| {
        try scanSources(b, &sources, rel_dir, args.extensions, args.excluding, args.excluding_contains);
    }
    step.addCSourceFiles(sources.items, args.flags);
}

/// Scans rel_dir for sources ending with one of the provided extensions, excluding relative paths
/// listed in the excluded list.
/// Results are appended to the dst ArrayList.
fn scanSources(
    b: *Build,
    dst: *std.ArrayList([]const u8),
    rel_dir: []const u8,
    extensions: []const []const u8,
    excluding: []const []const u8,
    excluding_contains: []const []const u8,
) !void {
    var dir = try std.fs.cwd().openIterableDir(rel_dir, .{});
    defer dir.close();
    var dir_it = dir.iterate();
    while (try dir_it.next()) |entry| {
        if (entry.kind != .File) continue;
        var abs_path = try std.fs.path.join(b.allocator, &.{ rel_dir, entry.name });
        abs_path = try std.fs.realpathAlloc(b.allocator, abs_path);

        const allowed_extension = blk: {
            const ours = std.fs.path.extension(entry.name);
            for (extensions) |ext| {
                if (std.mem.eql(u8, ours, ext)) break :blk true;
            }
            break :blk false;
        };
        if (!allowed_extension) continue;

        const excluded = blk: {
            for (excluding) |excluded| {
                if (std.mem.eql(u8, entry.name, excluded)) break :blk true;
            }
            break :blk false;
        };
        if (excluded) continue;

        const excluded_contains = blk: {
            for (excluding_contains) |contains| {
                if (std.mem.containsAtLeast(u8, entry.name, 1, contains)) break :blk true;
            }
            break :blk false;
        };
        if (excluded_contains) continue;

        try dst.append(abs_path);
    }
}
