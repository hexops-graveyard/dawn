#!/usr/bin/env bash
set -ex

# Mac
cp mach/args-linux.gn out/Debug/args.gn
gn gen out/Debug
./mach/ninja-generate.sh

# Linux
cp mach/args-linux.gn out/Debug/args.gn
gn gen out/Debug
./mach/ninja-generate.sh

# Windows
echo "print 'vs_path = \"\"'" > ./build/vs_toolchain.py 
echo "print 'sdk_path = \"\"'" >> ./build/vs_toolchain.py 
echo "print 'vs_version = \"\"'" >> ./build/vs_toolchain.py 
echo "print 'wdk_dir = \"\"'" >> ./build/vs_toolchain.py 
echo "print 'runtime_dirs = \"\"'" >> ./build/vs_toolchain.py 

echo "print 'include_flags_imsvc = \"\"'" > ./build/toolchain/win/setup_toolchain.py
echo "print 'libpath_flags = \"\"'" >> ./build/toolchain/win/setup_toolchain.py
echo "print 'vc_lib_path = \"tmp\"'" >> ./build/toolchain/win/setup_toolchain.py
echo "print 'vc_lib_um_path = \"tmp\"'" >> ./build/toolchain/win/setup_toolchain.py

cp mach/args-win.gn out/Debug/args.gn
gn gen out/Debug
./mach/ninja-generate.sh
