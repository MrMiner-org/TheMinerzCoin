cmake_minimum_required(VERSION 3.0)
project(blst C)

add_library(blst STATIC
    src/server.c
    build/assembly.S
)

target_include_directories(blst PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/bindings
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/build
)

target_compile_options(blst PRIVATE -O2 -fno-builtin -fPIC -Wall -Wextra -D__ADX__)
set_target_properties(blst PROPERTIES POSITION_INDEPENDENT_CODE ON)
