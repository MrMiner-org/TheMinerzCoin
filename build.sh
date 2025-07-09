#!/bin/sh
# Simple wrapper to invoke the CMake build from project root.
set -euo pipefail

cmake --build build "$@"
