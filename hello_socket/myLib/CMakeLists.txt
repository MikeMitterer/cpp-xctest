# ┌──────────────────────────────────────────────────────────────────┐
# │  Basis für CMAKE                                                 │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.0)

# ENV ist im .bashrc definiert
#   (Am Mac auf /Volumes/Daten/DevLocal/DevCPP/cmake )
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

project(mySocketLib)

# Output bin, c++11 usw
include(Config)

#if(NOT DEFINED LIBRARY_OUTPUT_DIRECTORY)
#    set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
#endif()
#
#message( "Library ouput path: ${LIBRARY_OUTPUT_DIRECTORY}")
#
## Set the output directory for library
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY} )
#
## Add this lib to the projects SEARCH-Path for LIBs
#list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories("${PROJECT_SOURCE_DIR}/include")

#include_directories(include)
include_directories(src)

set(SOURCE_FILES
        src/NewCppClass.cpp
        )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Library (entry points)                                          │
# └──────────────────────────────────────────────────────────────────┘

add_library (${PROJECT_NAME} SHARED ${SOURCE_FILES})
#add_library (${PROJECT_NAME} STATIC ${SOURCE_FILES})

