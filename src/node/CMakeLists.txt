file(GLOB NODE_SOURCES *.cpp)
add_library(node STATIC ${NODE_SOURCES})
target_include_directories(node PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
