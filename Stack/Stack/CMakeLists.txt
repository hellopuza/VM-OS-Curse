cmake_minimum_required(VERSION 3.9)
project(StackLib VERSION 1.0.0 DESCRIPTION "Stack library")

file(GLOB_RECURSE STACK_SOURCES *.cpp)
set(STACK_SOURCES ${STACK_SOURCES} PARENT_SCOPE)

set(STACK_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion \
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls -Wsign-conversion -Wnon-virtual-dtor \
    -Wctor-dtor-privacy -Woverloaded-virtual -Wno-float-equal"
)