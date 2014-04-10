set(SQUIRE_LIBRARY ktsuk)
project(squire_${SQUIRE_LIBRARY})
cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB HEADER squire/${SQUIRE_LIBRARY}/*.hpp)
file(GLOB DETAIL squire/${SQUIRE_LIBRARY}/detail*.hpp)

install(FILES ${HEADER} DESTINATION include/squire/${SQUIRE_LIBRARY})
install(FILES ${DETAIL} DESTINATION include/squire/${SQUIRE_LIBRARY}/detail)

add_subdirectory(examples)
