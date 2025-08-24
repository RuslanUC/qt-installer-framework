include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)

add_executable(devtool
        main.cpp
        binaryreplace.cpp
        operationrunner.cpp)
target_link_libraries(devtool PRIVATE installer)
target_compile_definitions(devtool PRIVATE ${IFW_COMPILE_DEFINITIONS})
