#!/bin/sh
# Install build artifacts from the CMake build directory.
set -euo pipefail

cmake --install build "$@"
