set(MODULE ktsuk)

file(GLOB HEADER *.hpp)
file(GLOB DETAIL detail/*.hpp)

install(FILES ${HEADER} DESTINATION include/${PROJECT_NAME}/${MODULE})
install(FILES ${DETAIL} DESTINATION include/${PROJECT_NAME}/${MODULE}/detail)
