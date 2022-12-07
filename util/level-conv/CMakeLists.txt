cmake_minimum_required(VERSION 3.10)
project(level_conv)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(level_conv src/main.cpp lib/json.hpp ${CMAKE_CURRENT_SOURCE_DIR}/../../app/src/main/cpp/LevelFactory.h)