file(GLOB BENCH_SOURCES *.cpp)
add_library(bench STATIC ${BENCH_SOURCES})
target_include_directories(bench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
