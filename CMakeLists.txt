cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

set(CMAKE_CXX_STANDARD 23)

# Set default platform if not specified
if(NOT GEODE_TARGET_PLATFORM)
    set(GEODE_TARGET_PLATFORM "Android64")
endif()

# Find Geode SDK
if(NOT GEODE_SDK_DIR)
    # Try common locations
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../geode-sdk")
        set(GEODE_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../geode-sdk")
    elseif(EXISTS "$ENV{HOME}/.geode/sdk")
        set(GEODE_SDK_DIR "$ENV{HOME}/.geode/sdk")
    else()
        message(FATAL_ERROR "GEODE_SDK_DIR not found! Please set GEODE_SDK_DIR to the Geode SDK path.")
    endif()
endif()

message(STATUS "Using Geode SDK at: ${GEODE_SDK_DIR}")

# Add Geode's CMake module path
list(APPEND CMAKE_MODULE_PATH "${GEODE_SDK_DIR}/cmake")

# Find Geode package
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
