file(GLOB CRYPTO_SOURCES *.cpp)
add_library(crypto_lib STATIC ${CRYPTO_SOURCES})
target_include_directories(crypto_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
