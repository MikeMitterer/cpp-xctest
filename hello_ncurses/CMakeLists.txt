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

project(HelloNCurses)

# Output bin, c++11 usw
include(Config)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Wichtig - sonst funktioniert's auf dem Raspi nicht
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘

find_package(args)
find_package(spdlog)
find_package(fmt)

set(ADDITIONAL_LIBRARIES menu)
find_package(curses REQUIRED)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Tests                                                           │
# │     Sample: add_subdirectory (tests)                             │
# └──────────────────────────────────────────────────────────────────┘

include_directories(include)
include_directories(src)
#include_directories(${CURSES_INCLUDE_DIRS})

#file(GLOB_RECURSE HEADER_SOURCES src/*.h)
set(HEADER_SOURCES
        src/main/data_types.h
        src/main/LayoutManager.h
        src/main/Screen.h
        src/main/Window.h
)

include_directories(src/main)

set(SOURCE_FILES
        src/hello_ncurses.cpp

        src/main/LayoutManager.cpp
        src/main/Screen.cpp
        src/main/Window.cpp
        src/main/XCurses.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(
        ${PROJECT_NAME}
        menu
        ${curses_LIBRARY}

        # Solves: undefined reference to symbol 'curs_set'
        # More: https://goo.gl/9dtJsO
        # tinfo
)
