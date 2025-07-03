file(GLOB UNIVALUE_SOURCES lib/*.cpp)
add_library(univalue STATIC ${UNIVALUE_SOURCES})
target_include_directories(univalue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
