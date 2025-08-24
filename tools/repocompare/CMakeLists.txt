find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

add_executable(repocompare
        mainwindow.ui

        main.cpp
        mainwindow.cpp
        repositorymanager.cpp)
target_link_libraries(repocompare PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
Qt6::Network)
