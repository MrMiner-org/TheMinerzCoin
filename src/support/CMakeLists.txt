file(GLOB SUPPORT_SOURCES *.cpp)
add_library(support STATIC ${SUPPORT_SOURCES})
target_include_directories(support PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
