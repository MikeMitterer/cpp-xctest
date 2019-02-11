get_parent_name(PARENT_NAME)
project(${PARENT_NAME}_tests)

include_directories(
        ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}
        ${MODULE_INCLUDES}

        _setup
)

add_executable(
        ${PROJECT_NAME}

        ${MODULE_SOURCE}

        # Test-Setup
        _setup/setup.cpp

        basic/rule_of_x_test.cpp
        basic/smart_pointer_test.cpp
        basic/ctor_test.cpp
        basic/var_init.cpp
        basic/strings.cpp
)

target_link_libraries(${PROJECT_NAME} gtest gtest_main)

