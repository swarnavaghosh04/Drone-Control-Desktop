cmake_minimum_required(VERSION 3.10)
project(
    DroneControlDesktop
    LANGUAGES C CXX
    VERSION 0.1.0
    HOMEPAGE_URL https://github.com/swarnavaghosh04/Drone-Control-Desktop
    DESCRIPTION "Application to control motors"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

string(
    APPEND _opts
    "$<IF:$<CXX_COMPILER_ID:MSVC>,"
        "/W4;$<$<CONFIG:RELEASE>:/O2>,"
        "-Wall;-Wextra;"
            "$<$<CONFIG:RELEASE>:-O3>"
    ">"
)
add_compile_options("${_opts}")

include(GNUInstallDirs)
include(FetchContent)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# build dependency libraries

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG)
include(cmake/libserialportConfig.cmake)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY      https://github.com/ocornut/imgui
    GIT_TAG             "origin/docking"
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
)

# Dependency fixes

if(NOT TARGET SDL2::SDL2 OR NOT TARGET SDL2::SDL2-static)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2ConfigBackup.cmake)
endif()

FetchContent_MakeAvailable(imgui)

# build library

add_subdirectory(src)

install(TARGETS DroneControl)
