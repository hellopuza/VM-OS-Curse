cmake_minimum_required(VERSION 3.16.3)
project(Queue)

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.h)

find_program(CLANG_FORMAT "clang-format")
add_custom_target(
    format
    COMMAND clang-format-12
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
)

if (ADD_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        --format-style=file;
        --header-filter=*.h;
    )
endif()

add_subdirectory(list_impl)
add_subdirectory(stack_impl)

if (ADD_TESTING)
    add_subdirectory(test)
endif()

if (ADD_BENCHMARK)
    add_subdirectory(benchmark)
endif()