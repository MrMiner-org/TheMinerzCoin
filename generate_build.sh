#!/bin/sh
set -e
cmake -S . -B build -DCRC32C_USE_GLOG=OFF "$@"
