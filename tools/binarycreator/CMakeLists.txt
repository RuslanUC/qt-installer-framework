include(${PROJECT_SOURCE_DIR}/cmake/definitions.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lto.cmake)

add_executable(binarycreator main.cpp)
target_link_libraries(binarycreator PRIVATE installer)
target_compile_definitions(binarycreator PRIVATE ${IFW_COMPILE_DEFINITIONS})
target_enable_lto(binarycreator)
