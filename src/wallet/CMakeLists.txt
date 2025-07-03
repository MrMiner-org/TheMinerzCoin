file(GLOB WALLET_SOURCES *.cpp)
add_library(wallet STATIC ${WALLET_SOURCES})
target_include_directories(wallet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
