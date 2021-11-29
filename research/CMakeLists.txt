cmake_minimum_required(VERSION 3.16.3)
project(Bench)

set(CMAKE_CXX_STANDARD 14)

find_package(benchmark REQUIRED)

if (ADD_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        --format-style=file;
        --header-filter=*.h;
    )
endif()

SET(CMAKE_CXX_FLAGS_RELEASE "-O0")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0")

string(REPLACE " " ";" BENCHMARK ${BENCHMARK})

foreach(EXEC_NAME IN LISTS BENCHMARK)
    add_executable(${EXEC_NAME} ${EXEC_NAME}.cpp)

    add_custom_target(run_${EXEC_NAME}
                    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME})
    add_dependencies(run_${EXEC_NAME} ${EXEC_NAME})

    target_link_libraries(${EXEC_NAME} benchmark::benchmark)
endforeach()