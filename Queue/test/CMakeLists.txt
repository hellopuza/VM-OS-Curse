cmake_minimum_required(VERSION 3.16.3)
project(QueueTest)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(gtest QUIET URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()

file(GLOB_RECURSE QUEUE_TEST_SOURCES *.cpp)

string(REPLACE " " ";" IMPLEMENTATIONS ${ADD_TESTING})

foreach (IMPL IN LISTS IMPLEMENTATIONS)
    set(EXEC_NAME queue_${IMPL}_test)

    string(TOUPPER ${IMPL} UPPER_IMPL)
    
    add_executable(${EXEC_NAME} ${QUEUE_TEST_SOURCES} ${QUEUE_${UPPER_IMPL}_SOURCES})
    target_include_directories(${EXEC_NAME} PUBLIC ${QUEUE_${UPPER_IMPL}_INCLUDE})

    add_custom_target(run_${EXEC_NAME}
                    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME})
    add_dependencies(run_${EXEC_NAME} ${EXEC_NAME})

    if(ADD_SANITIZERS)
        target_compile_options(${EXEC_NAME} PUBLIC -fsanitize=address -g)
        set_target_properties(${EXEC_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address")
    endif()
    
    target_link_libraries(${EXEC_NAME} gtest_main)
    
    include(GoogleTest)
    gtest_discover_tests(${EXEC_NAME} PROPERTIES LABELS "unit")
endforeach()