file(GLOB CRYPTO_SOURCES *.cpp)

# Build blst library
add_subdirectory(${PROJECT_SOURCE_DIR}/blst_lib ${CMAKE_CURRENT_BINARY_DIR}/blst_lib)

add_library(crypto_lib STATIC ${CRYPTO_SOURCES})
target_include_directories(crypto_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(crypto_lib PRIVATE blst)
