#!/usr/bin/env bash
# Simple wrapper to invoke the CMake build from project root.
set -euo pipefail

if [ ! -d build ]; then
    echo "Generating build directory..."
    ./generate_build.sh
fi

cmake --build build "$@"
