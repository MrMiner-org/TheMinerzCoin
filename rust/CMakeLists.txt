add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/target/release/libtheminerz_rust.a
    COMMAND ${CMAKE_COMMAND} -E env CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR}/target cargo build --release
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building Rust secp256k1 primitives"
)

add_custom_target(themz_rust ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/target/release/libtheminerz_rust.a)

add_library(secp256k1rs STATIC IMPORTED GLOBAL)
set_target_properties(secp256k1rs PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/target/release/libtheminerz_rust.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/src/rust_bindings
)
add_dependencies(secp256k1rs themz_rust)
