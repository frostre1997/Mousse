cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

set(CMAKE_CXX_STANDARD 23)

# Geode_DIR must be set via CMake command line
if(NOT Geode_DIR)
    message(FATAL_ERROR "Geode_DIR must be set to the Geode SDK cmake folder")
endif()

message(STATUS "Geode_DIR: ${Geode_DIR}")

# Find the Geode package
find_package(Geode REQUIRED)

# Check if we have hook support
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

# If no source files found, error
list(LENGTH SOURCES SOURCE_COUNT)
if(SOURCE_COUNT EQUAL 0)
    message(FATAL_ERROR "No source files found! Please add at least one .cpp file.")
endif()

# Define the mod
geode_mod(
    NAME "Mouse on Android"
    ID "frostre1997.mouse_on_android"
    VERSION "1.0.0"
    AUTHOR "frostre1997"
    DESCRIPTION "Desktop-style mouse cursor on Android"
    SOURCES ${SOURCES}
    RESOURCES ${RESOURCES}
)
