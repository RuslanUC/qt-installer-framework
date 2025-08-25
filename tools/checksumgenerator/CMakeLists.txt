include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

add_executable(checksumgenerator main.cpp)
target_link_libraries(checksumgenerator PRIVATE installer)
target_compile_definitions(checksumgenerator PRIVATE ${IFW_COMPILE_DEFINITIONS})
target_enable_lto(checksumgenerator)
