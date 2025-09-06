include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core)

if (WIN32)
    enable_language(RC)
    set(WIN32_RESOURCES installerbase.rc)
else()
    set(WIN32_RESOURCES "")
endif()

add_executable(installerbase
        settingsdialog.ui

        tabcontroller.h
        installerbasecommons.h
        settingsdialog.h
        sdkapp.h
        commandlineinterface.h
        installerbase.h
        aboutapplicationdialog.h

        main.cpp
        installerbase.cpp
        tabcontroller.cpp
        installerbasecommons.cpp
        settingsdialog.cpp
        commandlineinterface.cpp
        aboutapplicationdialog.cpp

        ${WIN32_RESOURCES})
target_link_libraries(installerbase PUBLIC
        Qt6::Core
        installer)
target_compile_definitions(installerbase PUBLIC ${IFW_COMPILE_DEFINITIONS})
target_enable_lto(installerbase)
if (WIN32)
    target_link_options(installerbase PRIVATE "/MANIFEST:NO")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
        target_link_options(installerbase PUBLIC "/Os")
    else()
        target_link_options(installerbase PUBLIC -s -Os)
    endif()
endif()
