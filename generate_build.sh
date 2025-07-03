#!/bin/sh
set -e
cmake -S . -B build "$@"
