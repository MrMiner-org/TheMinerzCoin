#!/bin/sh
# Generate a CMake build directory.
set -euo pipefail

cmake -S . -B build -DCRC32C_USE_GLOG=OFF "$@"
