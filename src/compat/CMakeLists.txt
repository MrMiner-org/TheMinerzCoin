file(GLOB COMPAT_SOURCES *.cpp)
add_library(compat STATIC ${COMPAT_SOURCES})
target_include_directories(compat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
