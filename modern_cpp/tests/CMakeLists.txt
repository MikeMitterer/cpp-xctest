get_parent_name(PARENT_NAME)
project(${PARENT_NAME}_tests)

include_directories(
        ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}
        ${MODULE_INCLUDES}
)

add_executable(
        ${PROJECT_NAME}

        ${MODULE_SOURCE}

        basic/rule_of_x_test.cpp
        basic/smart_pointer_test.cpp
        )

target_link_libraries(${PROJECT_NAME} gtest gtest_main)

