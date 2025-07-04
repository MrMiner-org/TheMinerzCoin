add_executable(tx_deser_fuzz transaction_deserialize.cpp)
target_include_directories(tx_deser_fuzz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../)

add_executable(block_deser_fuzz block_deserialize.cpp)
target_include_directories(block_deser_fuzz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../)

add_executable(script_interpreter_fuzz script_interpreter.cpp)
target_include_directories(script_interpreter_fuzz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
