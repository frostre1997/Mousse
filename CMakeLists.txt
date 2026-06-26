cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

# Set default if not provided
if(NOT GEODE_TARGET_PLATFORM)
    set(GEODE_TARGET_PLATFORM "Android64")
endif()

set(CMAKE_CXX_STANDARD 23)

# Find Geode SDK - check environment variable FIRST
if(NOT GEODE_SDK_DIR)
    # First, check if the action set the GEODE_SDK environment variable
    if(DEFINED ENV{GEODE_SDK})
        set(GEODE_SDK_DIR "$ENV{GEODE_SDK}")
        message(STATUS "Using GEODE_SDK from environment: ${GEODE_SDK_DIR}")
    # Then try the default install location
    elseif(EXISTS "$ENV{HOME}/.geode/sdk")
        set(GEODE_SDK_DIR "$ENV{HOME}/.geode/sdk")
        message(STATUS "Using GEODE_SDK from default location: ${GEODE_SDK_DIR}")
    else()
        message(FATAL_ERROR "GEODE_SDK_DIR not found! Please set GEODE_SDK_DIR to the Geode SDK path.")
    endif()
endif()

# Add Geode's CMake module path and find the package
list(APPEND CMAKE_MODULE_PATH "${GEODE_SDK_DIR}/cmake")
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
