include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

add_executable(devtool
        main.cpp
        binaryreplace.cpp
        operationrunner.cpp)
target_link_libraries(devtool PRIVATE installer)
target_compile_definitions(devtool PRIVATE ${IFW_COMPILE_DEFINITIONS})
target_enable_lto(devtool)
