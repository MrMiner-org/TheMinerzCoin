#!/usr/bin/env bash
# Install build artifacts from the CMake build directory.
set -euo pipefail

if [ ! -d build ]; then
    echo "Build directory missing; run ./generate_build.sh first" >&2
    exit 1
fi

cmake --install build "$@"
