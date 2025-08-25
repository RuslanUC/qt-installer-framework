cmake_minimum_required(VERSION 3.22)
project(installerfw LANGUAGES C CXX)

if(CMAKE_CROSSCOMPILING)
    return()
endif()

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_LINK_SEARCH_START_STATIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent Gui Network Qml Test UiTools Widgets Xml Core5Compat)

add_subdirectory(src)
add_subdirectory(tools)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


