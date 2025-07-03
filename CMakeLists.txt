cmake_minimum_required(VERSION 3.16)
project(TheMinerzCoin VERSION 3.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/leveldb)
add_subdirectory(src/crc32c)

# install documentation
install(DIRECTORY doc DESTINATION share/theminerzcoin)
