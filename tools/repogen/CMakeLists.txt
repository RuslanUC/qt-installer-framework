include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)

add_executable(repogen repogen.cpp)
target_link_libraries(repogen PRIVATE installer)
target_compile_definitions(repogen PRIVATE ${IFW_COMPILE_DEFINITIONS})
