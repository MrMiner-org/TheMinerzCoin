file(GLOB PRIMITIVES_SOURCES *.cpp)
add_library(primitives STATIC ${PRIMITIVES_SOURCES})
target_include_directories(primitives PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
