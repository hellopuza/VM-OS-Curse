cmake_minimum_required(VERSION 3.9)

project(Stack)

add_subdirectory(Stack)

set(EXEC_NAME main)

add_executable(${EXEC_NAME})
target_link_libraries(${EXEC_NAME} stack)

target_sources(${EXEC_NAME} PRIVATE main.cpp)

set_target_properties(${EXEC_NAME} PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion \
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls -Wsign-conversion -Wnon-virtual-dtor \
    -Wctor-dtor-privacy -Woverloaded-virtual \
")