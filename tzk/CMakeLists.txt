set(SQUIRE_LIBRARY tzk)
project(squire_${SQUIRE_LIBRARY})
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS -std=c++11)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB HEADER squire/${SQUIRE_LIBRARY}/*.hpp)
file(GLOB SOURCE squire/${SQUIRE_LIBRARY}/*.cpp)

add_library(${PROJECT_NAME} ${SOURCE})
install(FILES ${HEADER} DESTINATION include/squire/${SQUIRE_LIBRARY})

enable_testing()
add_subdirectory(test)
