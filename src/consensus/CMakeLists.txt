file(GLOB CONSENSUS_SOURCES *.cpp)
add_library(consensus STATIC ${CONSENSUS_SOURCES})
target_include_directories(consensus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
