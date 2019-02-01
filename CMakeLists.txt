# ┌──────────────────────────────────────────────────────────────────┐
# │  Basis für CMAKE                                                 │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.6)

# ENV ist im .bashrc definiert
#   (Am Mac auf /Volumes/DevLocal/DevCPP/cmake )
#set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

#list(APPEND CMAKE_MODULE_PATH "$ENV{QT5DIR}/lib/cmake")
#message(WARNING "MP ${CMAKE_MODULE_PATH}")

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

project(XCTest)

# Triggert den Debugger an - scheint aber nicht immer notwendig zu sein...
# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

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
add_subdirectory(hello_socket)
add_subdirectory(hello_thread)

# Scheint nur mit clang zu funktionieren - nicht mit gcc-5
add_subdirectory(hello_poco)

add_subdirectory(hello_qt)
add_subdirectory(hello_qt_socket)

add_subdirectory(hello_led)
add_subdirectory(hello_ncurses)
add_subdirectory(hello_dart)

add_subdirectory(modern_cpp)

