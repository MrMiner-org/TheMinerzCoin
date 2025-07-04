file(GLOB ROLLUP_SOURCES *.cpp)
add_library(rollup STATIC ${ROLLUP_SOURCES})
target_include_directories(rollup PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
