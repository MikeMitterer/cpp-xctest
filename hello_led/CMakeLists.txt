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



# Verhindert die komische Fehlermeldung:
#
#     Policy CMP0074 is not set: find_package uses <PackageName>_ROOT variables.
#     Run "cmake --help-policy CMP0074" for policy details.  Use the cmake_policy
#     command to set the policy and suppress this warning.
#
#     Environment variable GPIO_ROOT is set to:
#         /Volumes/DevLocal/DevCPP/Production/libs/gpio
#
#     For compatibility, CMake is ignoring the variable.
#
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
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
