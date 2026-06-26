cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

set(CMAKE_CXX_STANDARD 23)

# The action sets GEODE_SDK environment variable automatically
if(DEFINED ENV{GEODE_SDK})
    set(GEODE_SDK_DIR "$ENV{GEODE_SDK}")
    message(STATUS "Using GEODE_SDK from environment: ${GEODE_SDK_DIR}")
else()
    set(GEODE_SDK_DIR "$ENV{HOME}/.geode/sdk")
endif()

# Tell CMake where to find GeodeConfig.cmake
set(Geode_DIR "${GEODE_SDK_DIR}/cmake" CACHE PATH "Geode config directory")
message(STATUS "Geode_DIR set to: ${Geode_DIR}")

find_package(Geode REQUIRED)

geode_require_hook_support()

# Find source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp" "src/*.h")
if(NOT SOURCES)
    file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp" "*.h")
endif()

# Find resources if they exist
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources")
    file(GLOB_RECURSE RESOURCES "resources/*")
else()
    set(RESOURCES "")
endif()

geode_mod(
    NAME "Mouse on Android"
    ID "frostre1997.mouse_on_android"
    VERSION "1.0.0"
    AUTHOR "frostre1997"
    DESCRIPTION "Desktop-style mouse cursor on Android"
    SOURCES ${SOURCES}
    RESOURCES ${RESOURCES}
)
