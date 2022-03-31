cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)

file(GLOB_RECURSE DICT_BENCHMARK_SOURCES *.cpp)

set(EXEC_NAME dict_benchmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread")

add_executable(${EXEC_NAME} ${DICT_BENCHMARK_SOURCES} ${DICT_SOURCES})
target_include_directories(${EXEC_NAME} PUBLIC ${DICT_INCLUDE})

if(ADD_SANITIZERS)
    target_compile_options(${EXEC_NAME} PUBLIC -fsanitize=address -g)
    set_target_properties(${EXEC_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()

add_custom_target(bench
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} ${CMAKE_BINARY_DIR}/
)
add_dependencies(bench ${EXEC_NAME})

target_link_libraries(${EXEC_NAME} benchmark::benchmark)