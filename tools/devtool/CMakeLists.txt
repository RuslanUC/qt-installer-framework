add_executable(devtool
        main.cpp
        binaryreplace.cpp
        operationrunner.cpp)
target_link_libraries(devtool PRIVATE installer)
