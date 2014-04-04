project(squire CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS -std=c++11)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(${PROJECT_NAME}/ktsuk)
add_subdirectory(examples)
