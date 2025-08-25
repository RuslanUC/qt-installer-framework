include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

add_executable(repogen repogen.cpp)
target_link_libraries(repogen PRIVATE installer)
target_compile_definitions(repogen PRIVATE ${IFW_COMPILE_DEFINITIONS})
target_enable_lto(repogen)
