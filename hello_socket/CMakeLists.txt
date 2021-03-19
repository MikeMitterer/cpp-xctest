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

project(HelloSocket)

# Output bin, c++11 usw
include(Config)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘

add_subdirectory (myLib)
include_directories(myLib/include)

set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl" )
find_package(OpenSSL REQUIRED)

find_package(LibUV REQUIRED)
find_package(ZLIB REQUIRED)
find_package(uws REQUIRED)
find_package(json REQUIRED)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Tests                                                           │
# │     Sample: add_subdirectory (tests)                             │
# └──────────────────────────────────────────────────────────────────┘

include_directories(include)
include_directories(src)
include_directories(${OPENSSL_INCLUDE_DIR} )

set(SOURCE_FILES
        src/hello_socket.cpp
        )

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${uws_SRCFILES}
        )

target_link_libraries(${PROJECT_NAME} myLib
        ${OPENSSL_LIBRARIES}
        ${crypto_LIB}
        ${LIBUV_LIBRARIES}
        ${ZLIB_LIBRARIES}
        )
