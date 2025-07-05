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
add_subdirectory(node)
add_subdirectory(support)
add_subdirectory(hw_wallet)
add_subdirectory(compat)
add_subdirectory(bench)
add_subdirectory(zmq)
add_subdirectory(websockets)
add_subdirectory(grpc)
if(WITH_GUI)
    add_subdirectory(qt)
endif()
add_subdirectory(p2p)
add_subdirectory(neutrino)
add_subdirectory(univalue)
add_subdirectory(secp256k1)

option(WITH_LIGHTNING "Build with Lightning support" OFF)
if(WITH_LIGHTNING)
    add_subdirectory(lightning)
endif()

if(ENABLE_ZK_ROLLUP)
    add_subdirectory(rollup)
endif()

add_subdirectory(test)
