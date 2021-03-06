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

project(HelloQTSocket)

# Output bin, c++11 usw
include(Config)
set(CMAKE_VERBOSE_MAKEFILE ON)

#include(configGTest)
#add_subdirectory(../.dependencies/googletest test_HelloQT)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Qt (e.g. /usr/local/QT5.3/5.3/clang_64                          │
# │      Weitere Infos: http://doc.qt.io/qt-5/cmake-manual.html      │
# └──────────────────────────────────────────────────────────────────┘

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON) # moc
set(CMAKE_AUTORCC ON) # rcc

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

#if(XCTARGET STREQUAL "rpi1")
#if(XCTARGET MATCHES "^rpi.*")
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(CMAKE_PREFIX_PATH "${PIROOT}/usr/lib/arm-linux-gnueabihf/cmake" ${CMAKE_PREFIX_PATH})

    # Wichtig - sonst funktioniert's auf dem Raspi nicht
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

else()

    # Ist in der .bashrc definiert
    # set(CMAKE_PREFIX_PATH $ENV{QT5DIR} ${CMAKE_PREFIX_PATH})

    # set(CMAKE_MODULE_PATH $ENV{QT5DIR}/lib/cmake/Qt5 ${CMAKE_MODULE_PATH})

endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl" )
find_package(OpenSSL REQUIRED)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS WebSockets REQUIRED)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘



# ┌──────────────────────────────────────────────────────────────────┐
# │  Tests                                                           │
# │     Sample: add_subdirectory (tests)                             │
# └──────────────────────────────────────────────────────────────────┘

add_subdirectory (tests)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

include_directories(include)
include_directories(src)

set(SOURCE_FILES
        src/hello_qt_socket.cpp
        src/echoserver.h
        src/echoserver.cpp
        )

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
        )

#target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::WebSockets)
qt5_use_modules(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::WebSockets)
