file(GLOB POLICY_SOURCES *.cpp)
add_library(policy STATIC ${POLICY_SOURCES})
target_include_directories(policy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
