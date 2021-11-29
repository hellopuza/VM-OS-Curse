cmake_minimum_required(VERSION 3.16.3)

find_package(benchmark REQUIRED)

set(EXEC_NAME bench_factor)

file(GLOB_RECURSE STACK_BENCH_SOURCES *.cpp)

add_executable(${EXEC_NAME} ${STACK_BENCH_SOURCES})
target_include_directories(${EXEC_NAME} PUBLIC ${STACK_INCLUDE})

add_custom_target(run_${EXEC_NAME}
                  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME})
add_dependencies(run_${EXEC_NAME} ${EXEC_NAME})

target_link_libraries(${EXEC_NAME} benchmark::benchmark)