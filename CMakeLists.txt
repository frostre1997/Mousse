cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

if(NOT GEODE_TARGET_PLATFORM)
    set(GEODE_TARGET_PLATFORM "Android64")
endif()

set(CMAKE_CXX_STANDARD 23)

# Locate the Geode SDK
if(NOT GEODE_SDK_DIR)
    if(DEFINED ENV{GEODE_SDK})
        set(GEODE_SDK_DIR "$ENV{GEODE_SDK}")
        message(STATUS "Using GEODE_SDK from environment: ${GEODE_SDK_DIR}")
    elseif(EXISTS "$ENV{HOME}/.geode/sdk")
        set(GEODE_SDK_DIR "$ENV{HOME}/.geode/sdk")
        message(STATUS "Using GEODE_SDK from default location: ${GEODE_SDK_DIR}")
    else()
        message(FATAL_ERROR "GEODE_SDK_DIR not found! Please set GEODE_SDK_DIR to the Geode SDK path.")
    endif()
endif()

# Add the SDK's cmake directory to the module path (as a fallback)
list(APPEND CMAKE_MODULE_PATH "${GEODE_SDK_DIR}/cmake")

# Do NOT set Geode_DIR here – the build action will pass it via -DGeode_DIR
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
