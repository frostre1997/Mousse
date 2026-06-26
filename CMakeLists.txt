cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

# Set default platform if not provided
if(NOT GEODE_TARGET_PLATFORM)
    set(GEODE_TARGET_PLATFORM "Android64")
endif()

set(CMAKE_CXX_STANDARD 23)

# Locate the Geode SDK
if(NOT GEODE_SDK_DIR)
    # 1. Use the environment variable set by the GitHub Action
    if(DEFINED ENV{GEODE_SDK})
        set(GEODE_SDK_DIR "$ENV{GEODE_SDK}")
        message(STATUS "Using GEODE_SDK from environment: ${GEODE_SDK_DIR}")
    # 2. Fallback to the default installation path
    elseif(EXISTS "$ENV{HOME}/.geode/sdk")
        set(GEODE_SDK_DIR "$ENV{HOME}/.geode/sdk")
        message(STATUS "Using GEODE_SDK from default location: ${GEODE_SDK_DIR}")
    else()
        message(FATAL_ERROR "GEODE_SDK_DIR not found! Please set GEODE_SDK_DIR to the Geode SDK path.")
    endif()
endif()

# Tell CMake where to find GeodeConfig.cmake
set(Geode_DIR "${GEODE_SDK_DIR}/cmake" CACHE PATH "Path to Geode CMake config")
message(STATUS "Geode_DIR set to: ${Geode_DIR}")

# Find the Geode package (will use Geode_DIR)
find_package(Geode REQUIRED)

geode_require_hook_support()

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp" "src/*.h")
file(GLOB_RECURSE RESOURCES "resources/*")

geode_mod(
    NAME "Mouse on Android"
    ID "frostre1997.mouse_on_android"
    VERSION "1.0.0"
    AUTHOR "frostre1997"
    DESCRIPTION "Desktop-style mouse cursor on Android"
    SOURCES ${SOURCES}
    RESOURCES ${RESOURCES}
)
