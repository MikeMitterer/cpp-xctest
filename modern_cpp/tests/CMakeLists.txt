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

# Evtl. könnte auch GLOB_RECURSE eine Variante sein!
file(GLOB BASIC_TESTS basic/*.h basic/*.cpp)
file(GLOB CLASS_TESTS basic/class/*.h basic/class/*.cpp basic/class/tdd)
file(GLOB TEMPLATE_TESTS basic/templates/*.h basic/templates/*.cpp)

add_executable(
        ${PROJECT_NAME}

        ${MODULE_SOURCE}

        # Test-Setup
        _setup/setup.cpp

        _setup/utils.h
        _setup/utils.cpp

        ${BASIC_TESTS}
        ${CLASS_TESTS}
        ${TEMPLATE_TESTS}

#        basic/conditions_test.cpp
#        basic/const_test.cpp
#        basic/constexpr_test.cpp
#        basic/loops_test.cpp
#        basic/smart_pointer_test.cpp
#        basic/string_test.cpp
#        basic/var_init.cpp
#
#        basic/class/rule_of_x_test.cpp
#        basic/class/ctor_test.cpp
#
#        basic/templates/ToJson.h
#        basic/templates/ToJson.cpp
#        basic/templates/NameEvent.h
#        basic/templates/class_template.h
#        basic/templates/function_template.h
#        basic/templates/template_test.cpp

)

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

