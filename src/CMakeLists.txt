# Core library
file(GLOB CORE_SOURCES
    "*.cpp"
)
# Remove the standalone executables from the core library sources
list(REMOVE_ITEM CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/bitcoind.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bitcoin-cli.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bitcoin-tx.cpp
)
add_library(core STATIC ${CORE_SOURCES})
target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/univalue/include
    ${CMAKE_CURRENT_SOURCE_DIR}/leveldb/include
    ${CMAKE_CURRENT_SOURCE_DIR}/leveldb/helpers/memenv
    ${CMAKE_CURRENT_SOURCE_DIR}/secp256k1/include
    ${boost_SOURCE_DIR}
)
target_link_libraries(core PUBLIC Boost::filesystem Boost::system)

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
if(WITH_GRPC)
    add_subdirectory(grpc)
endif()
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

# Daemon executable
add_executable(theminerzcoind bitcoind.cpp)
target_link_libraries(theminerzcoind PRIVATE
    core wallet consensus crypto policy primitives rpc script_lib node support
    hw_wallet compat bench zmq_lib websockets p2p neutrino
    univalue secp256k1
)
if(WITH_GRPC)
    target_link_libraries(theminerzcoind PRIVATE grpc_services)
endif()
