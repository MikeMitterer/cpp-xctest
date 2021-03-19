# --------------------------------------------------------------------------------------------------
# Common-Vars:
#       https://cgold.readthedocs.io/en/latest/tutorials/cmake-sources/common.html
#
# get_filename_component:
#       https://cmake.org/cmake/help/latest/command/get_filename_component.html
#

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(PARENT_NAME ${PARENT_DIR} NAME)

project(HelloQT_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME}

        basic_tests/basic_check_ma.cpp
        basic_tests/next_check.cpp

        ext_tests/ext_check_ma.cpp
        ext_tests/ext_next_check.cpp
        )

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

