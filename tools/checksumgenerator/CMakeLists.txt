include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)

add_executable(checksumgenerator main.cpp)
target_link_libraries(checksumgenerator PRIVATE installer)
target_compile_definitions(checksumgenerator PRIVATE ${IFW_COMPILE_DEFINITIONS})
