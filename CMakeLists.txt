cmake_minimum_required(VERSION 3.27)
project(MouseOnAndroid)

set(CMAKE_CXX_STANDARD 23)

# The action sets GEODE_SDK environment variable
if(DEFINED ENV{GEODE_SDK})
    set(GEODE_SDK_DIR "$ENV{GEODE_SDK}")
else()
    set(GEODE_SDK_DIR "$ENV{HOME}/.geode/sdk")
endif()

list(APPEND CMAKE_MODULE_PATH "${GEODE_SDK_DIR}/cmake")
find_package(Geode REQUIRED)

geode_require_hook_support()
...
