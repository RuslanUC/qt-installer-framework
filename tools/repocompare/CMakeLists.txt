include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)

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
target_compile_definitions(repocompare PRIVATE ${IFW_COMPILE_DEFINITIONS})
