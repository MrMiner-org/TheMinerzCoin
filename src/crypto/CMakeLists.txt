file(GLOB CRYPTO_SOURCES *.cpp)

# Provide a minimal blst interface library to avoid fetching and building the
# actual dependency during configuration.
add_library(blst INTERFACE)
target_include_directories(blst INTERFACE ${PROJECT_SOURCE_DIR}/blst_lib/bindings)

add_library(crypto_lib STATIC ${CRYPTO_SOURCES})
target_include_directories(crypto_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(crypto_lib PRIVATE blst)
