cmake_minimum_required(VERSION 3.0)

project(Stack)

add_subdirectory(Stack)

set(MAIN_PROJECT_SRC_LIST main)
add_executable(main ${MAIN_PROJECT_SRC_LIST})
target_link_libraries(main stack_lib)