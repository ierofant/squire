function(squire_add_test TEST SOURCE)
    add_executable(${TEST} ${SOURCE})
    target_link_libraries(${TEST} ${PROJECT_NAME} ${Boost_LIBRARIES})

    add_test(${TEST} ${PROJECT_BINARY_DIR}/test/${TEST})
endfunction()

find_package(Boost COMPONENTS unit_test_framework)
if(Boost_UNIT_TEST_FRAMEWORK_FOUND)
    include_directories(${Boost_INCLUDE_DIR})

    squire_add_test(ts_position ts_position.cpp)
    squire_add_test(ts_channel ts_channel.cpp)
    squire_add_test(ts ts.cpp)
endif()
