include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)

add_executable(archivegen archive.cpp)
target_link_libraries(archivegen PRIVATE installer)
target_compile_definitions(archivegen PRIVATE ${IFW_COMPILE_DEFINITIONS})
