file(GLOB SCRIPT_SOURCES *.cpp)
add_library(script_lib STATIC ${SCRIPT_SOURCES})
target_include_directories(script_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
