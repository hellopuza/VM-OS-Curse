cmake_minimum_required(VERSION 3.9)
project(StackLib VERSION 1.0.0 DESCRIPTION "Stack library")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.h)

find_program(CLANG_FORMAT "clang-format")
add_custom_target(
    format
    COMMAND clang-format-12
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --format-style=file;
    --header-filter=*.h;
)

add_subdirectory(Stack)

if (ADD_TESTING)
    add_subdirectory(test)
endif()

if (ADD_BENCHMARK)
    add_subdirectory(benchmark)
endif()