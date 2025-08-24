find_package(Qt6 REQUIRED COMPONENTS Core)

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
        aboutapplicationdialog.cpp)
target_link_libraries(installerbase PUBLIC
    Qt6::Core
    installer)

# TODO: installerbase.rc if windows
