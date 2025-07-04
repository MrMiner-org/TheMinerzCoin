file(GLOB NEUTRINO_SOURCES *.cpp)
add_library(neutrino STATIC ${NEUTRINO_SOURCES})
target_include_directories(neutrino PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
