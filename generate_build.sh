#!/usr/bin/env bash
# Generate a CMake build directory.
set -euo pipefail

if [ -d build ]; then
    echo "Using existing build directory" >&2
else
    cmake -S . -B build -DCRC32C_USE_GLOG=OFF "$@"
fi
