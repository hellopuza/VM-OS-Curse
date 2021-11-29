cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)

file(GLOB_RECURSE QUEUE_BENCHMARK_SOURCES *.cpp)

string(REPLACE " " ";" IMPLEMENTATIONS ${ADD_BENCHMARK})

foreach(IMPL IN LISTS IMPLEMENTATIONS)
    set(EXEC_NAME queue_${IMPL}_benchmark)
    string(TOUPPER ${IMPL} UPPER_IMPL)
    
    add_executable(${EXEC_NAME} ${QUEUE_BENCHMARK_SOURCES} ${QUEUE_${UPPER_IMPL}_SOURCES})
    target_include_directories(${EXEC_NAME} PUBLIC ${QUEUE_${UPPER_IMPL}_INCLUDE})

    add_custom_target(run_${EXEC_NAME}
                    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME})
    add_dependencies(run_${EXEC_NAME} ${EXEC_NAME})

    if(ADD_SANITIZERS)
        target_compile_options(${EXEC_NAME} PUBLIC -fsanitize=address -g)
        set_target_properties(${EXEC_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address")
    endif()
    
    target_link_libraries(${EXEC_NAME} benchmark::benchmark)
endforeach()