file(GLOB WALLET_SOURCES *.cpp)
add_library(wallet STATIC ${WALLET_SOURCES})
target_include_directories(wallet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

if(WITH_LIGHTNING)
    target_link_libraries(wallet PUBLIC lightning)
    target_compile_definitions(wallet PUBLIC ENABLE_LIGHTNING)
endif()
