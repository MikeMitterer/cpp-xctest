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

project(XCTest)

# Output bin, c++11 usw
include(Config)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Google-Test                                                     │
# └──────────────────────────────────────────────────────────────────┘

find_package(GTest)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Sub-Projects                                                    │
# └──────────────────────────────────────────────────────────────────┘

add_subdirectory(hello_world)
add_subdirectory(hello_lib)
add_subdirectory(hello_thread)

# Scheint nur mit clang zu funktionieren - nicht mit gcc-5
#add_subdirectory(hello_poco)

add_subdirectory(hello_qt)
#add_subdirectory(hello_led)
add_subdirectory(hello_ncurses)
#add_subdirectory(hello_dart)
