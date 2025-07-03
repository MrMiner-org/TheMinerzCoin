# Core library
file(GLOB CORE_SOURCES
    "*.cpp"
)
add_library(core STATIC ${CORE_SOURCES})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Modules
add_subdirectory(consensus)
add_subdirectory(wallet)
add_subdirectory(crypto)
add_subdirectory(policy)
add_subdirectory(primitives)
add_subdirectory(rpc)
add_subdirectory(script)
add_subdirectory(support)
add_subdirectory(compat)
add_subdirectory(bench)
add_subdirectory(zmq)
add_subdirectory(qt)
add_subdirectory(univalue)
add_subdirectory(secp256k1)

