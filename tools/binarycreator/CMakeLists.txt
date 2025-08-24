include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)

add_executable(binarycreator main.cpp)
target_link_libraries(binarycreator PRIVATE installer)
target_compile_definitions(binarycreator PRIVATE ${IFW_COMPILE_DEFINITIONS})
