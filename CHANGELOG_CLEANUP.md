## Changelog

### Changed Files
- src/base58.cpp
- contrib/devtools/check-doc.py
- .github/workflows/build.yml
- .github/workflows/c-cpp.yml
- .github/workflows/codeql.yml

### Key Improvements
- Replaced C-style memory operations in `base58.cpp` with `std::memcpy` and removed casts for better type safety.
- Updated GitHub Actions to use `actions/checkout@v4` for improved security and features.
- Converted a development tool script to be Python 3 compatible.

### Potential Follow-up Tasks
- Resolve remaining clang-tidy and cppcheck warnings across the code base (~50 sp).
- Modernize other Python scripts and add unit tests for tooling (~20 sp).
- Investigate missing dependencies in the CMake build to allow CI compilation (~30 sp).
