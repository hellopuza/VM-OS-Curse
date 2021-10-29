cmake_minimum_required(VERSION 3.9)
project(StackTest)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(gtest QUIET URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()

file(GLOB_RECURSE STACK_TEST_SOURCES *.cpp)
set(EXEC_NAME stack_test)

add_executable(${EXEC_NAME} ${STACK_TEST_SOURCES})
target_link_libraries(${EXEC_NAME} gtest_main stack)

add_custom_target(run_${EXEC_NAME}
                  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME})
add_dependencies(run_${EXEC_NAME} ${EXEC_NAME})

set_target_properties(${EXEC_NAME} PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")

include(GoogleTest)
gtest_discover_tests(${EXEC_NAME} PROPERTIES LABELS "unit")