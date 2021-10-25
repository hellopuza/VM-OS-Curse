cmake_minimum_required(VERSION 3.9)
project(StackLib VERSION 1.0.0 DESCRIPTION "Stack library")

set(STACK_SOURCES src/Stack-bool.cpp)
set(STACK_HEADERS include/Stack.h include/Stack-impl.h)

add_library(stack SHARED ${STACK_SOURCES} ${STACK_HEADERS})
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(stack PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES ${STACK_SOURCES} ${STACK_HEADERS})

    add_custom_target(
        format
        COMMAND clang-format-12
        -i
        -style=file
        ${ALL_CXX_SOURCE_FILES}
    )
endif()

find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES ${STACK_SOURCES} ${STACK_HEADERS})

    add_custom_target(
        tidy
        COMMAND clang-tidy
        ${ALL_CXX_SOURCE_FILES}
        -format-style=file
        --
        -std=c++11
        -I${PROJECT_ROOT_DIR}/include
    )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion \
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls -Wsign-conversion -Wnon-virtual-dtor \
    -Wctor-dtor-privacy -Woverloaded-virtual \
")