cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

set(GEODE_TARGET_PLATFORM "Android64")
set(CMAKE_CXX_STANDARD 23)

find_package(Geode REQUIRED)

geode_require_hook_support()

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp" "src/*.h")
file(GLOB_RECURSE RESOURCES "resources/*")

geode_mod(
    NAME "Mouse on Android"
    ID "dev.usr.mouse_on_android"
    VERSION "1.0.0"
    AUTHOR "usr"
    DESCRIPTION "Desktop-style mouse cursor on Android"
    SOURCES ${SOURCES}
    RESOURCES ${RESOURCES}
)
