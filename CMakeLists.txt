cmake_minimum_required(VERSION 3.18)
project(TheMinerzCoin LANGUAGES C CXX)

option(WITH_GUI "Build GUI" ON)
option(WITH_RUST "Build Rust components" OFF)
option(STRICT "Treat warnings as errors" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCXXSourceCompiles)
check_cxx_source_compiles(
"#include \"${CMAKE_SOURCE_DIR}/src/simd_fallback.h\"
using floatv = tmc::native_simd<float>;
int main(){floatv v(1.0f); return v.size();}"
HAVE_STD_SIMD)
if(HAVE_STD_SIMD)
    add_compile_definitions(HAVE_STD_SIMD)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(STRICT)
    add_compile_options(-Werror)
endif()

include(FetchContent)

FetchContent_Declare(
  boost
  URL https://boostorg.jfrog.io/artifactory/main/release/1.85.0/source/boost_1_85_0.tar.gz
)
FetchContent_MakeAvailable(boost)

FetchContent_Declare(
  openssl
  URL https://www.openssl.org/source/openssl-3.3.0.tar.gz
)
FetchContent_MakeAvailable(openssl)

FetchContent_Declare(
  miniupnpc
  URL https://miniupnp.tuxfamily.org/files/miniupnpc-2.2.6.tar.gz
)
FetchContent_MakeAvailable(miniupnpc)

FetchContent_Declare(
  blst
  GIT_REPOSITORY https://github.com/supranational/blst.git
  GIT_TAG v0.3.10
)
FetchContent_MakeAvailable(blst)

if(WITH_GUI)
  find_package(Qt5 COMPONENTS Widgets Gui Network REQUIRED)
endif()

add_subdirectory(src/leveldb)
add_subdirectory(src/crc32c)
if(WITH_RUST)
  add_subdirectory(rust)
endif()
add_subdirectory(src)

include(GNUInstallDirs)
install(DIRECTORY doc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/theminerzcoin)
install(TARGETS theminerzcoind theminerzcoin-qt libbitcoinconsensus
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(CPACK_GENERATOR "TGZ;NSIS;DragNDrop")
include(CPack)
