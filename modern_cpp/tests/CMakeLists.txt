# --------------------------------------------------------------------------------------------------
# Common-Vars:
#       https://cgold.readthedocs.io/en/latest/tutorials/cmake-sources/common.html
#
# get_filename_component:
#       https://cmake.org/cmake/help/latest/command/get_filename_component.html
#

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(PARENT_NAME ${PARENT_DIR} NAME)

project(ModernCPP_tests)

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

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

