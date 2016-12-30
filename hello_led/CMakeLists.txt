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

project(HelloLed)

# Output bin, c++11 usw
include(Config)
#include(configGPIO)

# RealLife
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")

    # Wichtig - sonst funktioniert's auf dem Raspi nicht
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Simulation
else()


endif()

find_package(GPIO)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘

#include_directories(${gpio_SOURCE_DIR}/include )

#find_package(Curses REQUIRED)

# RealLife
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")

# Simulation
else()


endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source                                                          │
# └──────────────────────────────────────────────────────────────────┘

include_directories(include)
include_directories(src)


set(SOURCE_FILES ${SOURCE_FILES}
        src/hello_led.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        gpio
        ${CURSES_LIBRARIES}
        )