get_parent_name(PARENT_NAME)
project(${PARENT_NAME}_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME}

        basic_tests/basic_check_ma.cpp
        basic_tests/next_check.cpp

        ext_tests/ext_check_ma.cpp
        ext_tests/ext_next_check.cpp
        )

target_link_libraries(${PROJECT_NAME} gtest gtest_main)

