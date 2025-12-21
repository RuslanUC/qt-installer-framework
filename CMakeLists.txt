cmake_minimum_required(VERSION 3.22)
project(installerfw LANGUAGES C CXX)

if(CMAKE_CROSSCOMPILING)
    return()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)
#set(CMAKE_LINK_SEARCH_START_STATIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent Gui Widgets Xml)

add_subdirectory(src)
add_subdirectory(tools)

install(TARGETS installer ARCHIVE LIBRARY RUNTIME PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/ifw")
install(TARGETS installerbase RUNTIME)
install(TARGETS binarycreator RUNTIME)
install(TARGETS repogen RUNTIME)
