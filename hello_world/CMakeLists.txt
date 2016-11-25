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

# ┌──────────────────────────────────────────────────────────────────┐
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘

find_package(args)
find_package(spdlog)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Tests                                                           │
# │     Sample: add_subdirectory (tests)                             │
# └──────────────────────────────────────────────────────────────────┘

include_directories(include)
include_directories(src)

set(SOURCE_FILES
        src/hello_world.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})