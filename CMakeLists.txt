cmake_minimum_required(VERSION 3.25)
project(TheMinerzCoin VERSION 3.0.0 LANGUAGES C CXX)

find_package(Qt5 COMPONENTS Widgets Gui Network REQUIRED)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_ZK_ROLLUP "Enable zk rollup support" OFF)
if(ENABLE_ZK_ROLLUP)
    add_definitions(-DENABLE_ZK_ROLLUP)
endif()

add_subdirectory(src/leveldb)
add_subdirectory(src/crc32c)
add_subdirectory(src)

# install documentation
install(DIRECTORY doc DESTINATION share/theminerzcoin)

install(TARGETS wallet consensus theminerzcoin-qt
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
