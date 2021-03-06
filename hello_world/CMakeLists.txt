# ┌──────────────────────────────────────────────────────────────────┐
# │  Basis für CMAKE                                                 │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.6)

# ENV ist im .bashrc definiert
#   (Am Mac auf /Volumes/Daten/DevLocal/DevCPP/cmake )
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

project(HelloWorld)

# Output bin, c++11 usw
include(Config)

# Password for this project
include(.config/passwords.cmake)

# The version number.
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 4)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/.config/config.h.in"
        "${PROJECT_SOURCE_DIR}/src/config.h"
        @ONLY
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Precompiled headers                                             │
# └──────────────────────────────────────────────────────────────────┘

add_library(${PROJECT_NAME}_pch
        ${PROJECT_SOURCE_DIR}/src/stdafx.cpp ${PROJECT_SOURCE_DIR}/src/stdafx.h)

set_source_files_properties(${PROJECT_SOURCE_DIR}/src/stdafx.cpp
        PROPERTIES
        COMPILE_FLAGS "-include ${PROJECT_SOURCE_DIR}/src/stdafx.h")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Google-Test (BasisProjekt: find_package(GTest)                  │
# └──────────────────────────────────────────────────────────────────┘

# find_package(GTest)
add_subdirectory(tests)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘

find_package(args)
find_package(spdlog)
find_package(fmt)


# ┌──────────────────────────────────────────────────────────────────┐
# │  Tests                                                           │
# │     Sample: add_subdirectory (tests)                             │
# └──────────────────────────────────────────────────────────────────┘

include_directories(include)
include_directories(src)

set(SOURCE_FILES
        src/hello_world.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${CONAN_LIBS})
