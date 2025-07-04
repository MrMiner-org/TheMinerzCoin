file(GLOB WEBSOCKETS_SOURCES *.cpp)
add_library(websockets STATIC ${WEBSOCKETS_SOURCES})
target_include_directories(websockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(websockets PUBLIC websockets)
