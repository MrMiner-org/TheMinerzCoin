file(GLOB RPC_SOURCES *.cpp)
add_library(rpc STATIC ${RPC_SOURCES})
target_include_directories(rpc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
