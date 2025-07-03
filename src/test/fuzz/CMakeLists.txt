add_executable(tx_deser_fuzz transaction_deserialize.cpp)
target_include_directories(tx_deser_fuzz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
