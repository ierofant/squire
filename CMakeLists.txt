project(squire CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS -std=c++11)

include_directories(${PROJECT_SOURCE_DIR})

enable_testing()
add_subdirectory(ktsuk)
add_subdirectory(tzk)
