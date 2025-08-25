include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

add_executable(archivegen archive.cpp)
target_link_libraries(archivegen PRIVATE installer)
target_compile_definitions(archivegen PRIVATE ${IFW_COMPILE_DEFINITIONS})
target_enable_lto(archivegen)
