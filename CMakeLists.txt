cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

# Set default if not provided
if(NOT GEODE_TARGET_PLATFORM)
    set(GEODE_TARGET_PLATFORM "Android64")
endif()

set(CMAKE_CXX_STANDARD 23)

# Find Geode SDK
if(NOT GEODE_SDK_DIR)
    # Try common locations
    set(GEODE_SDK_DIR "$ENV{HOME}/.geode/sdk" CACHE PATH "Geode SDK directory")
endif()

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
