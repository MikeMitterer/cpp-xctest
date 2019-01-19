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

project(ModernCPP)

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
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘

find_package(Args)
find_package(Spdlog)
find_package(Fmt)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Modul-Source                                                    │
# └──────────────────────────────────────────────────────────────────┘

set(MODULE_INCLUDES
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        )

set(MODULE_main ${PROJECT_SOURCE_DIR}/src/modern.cpp)

set(MODULE_SOURCE
        ${PROJECT_SOURCE_DIR}/src/config.h
        ${PROJECT_SOURCE_DIR}/src/rule_of_x.cpp
        )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Google-Test (BasisProjekt: find_package(GTest)                  │
# └──────────────────────────────────────────────────────────────────┘

find_package(GTest)
add_subdirectory(tests)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Applikation                                                     │
# └──────────────────────────────────────────────────────────────────┘

include_directories(MODULE_INCLUDES)

add_executable(
        ${PROJECT_NAME}

        ${MODULE_main}
        ${MODULE_SOURCE}

        ${CONAN_LIBS}
)
