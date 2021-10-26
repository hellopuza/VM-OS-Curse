cmake_minimum_required(VERSION 3.9)
project(StackTest)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(gtest QUIET URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()

set(STACK_TEST_SOURCES main.cpp)
set(EXEC_NAME stack_test)

add_executable(${EXEC_NAME} ${STACK_TEST_SOURCES})
target_link_libraries(${EXEC_NAME} gtest_main stack)

add_custom_target(run_${EXEC_NAME}
                  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME})
add_dependencies(run_${EXEC_NAME} ${EXEC_NAME})

include(GoogleTest)
gtest_discover_tests(stack_test PROPERTIES LABELS "unit")