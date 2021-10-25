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

add_executable(stack_test ${STACK_TEST_SOURCES})
target_link_libraries(stack_test gtest_main stack)

include(GoogleTest)
gtest_discover_tests(stack_test PROPERTIES LABELS "unit")