#pragma once
#if __cpp_lib_simd >= 202207L
  #include <simd>
  namespace tmc = std;
#else
  #include <experimental/simd>
  namespace tmc = std::experimental;
#endif
