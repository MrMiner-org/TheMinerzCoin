file(GLOB LIGHTNING_SOURCES *.cpp)
add_library(lightning STATIC ${LIGHTNING_SOURCES})
target_include_directories(lightning PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(lightning PUBLIC grpc++ grpc)
