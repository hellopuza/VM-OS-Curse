cmake_minimum_required(VERSION 3.9)

project(StackLib VERSION 1.0.0 DESCRIPTION "Stack library")

set(SOURCES src/Stack-bool.cpp)
set(HEADERS include/Stack.h include/Stack-impl.h)

add_library(stack SHARED ${SOURCES} ${HEADERS})
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES ${SOURCES} ${HEADERS})

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
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES ${SOURCES} ${HEADERS})

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