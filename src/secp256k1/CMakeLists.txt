file(GLOB SECP_SOURCES src/secp256k1.c)
add_library(secp256k1 STATIC ${SECP_SOURCES})
target_include_directories(secp256k1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
