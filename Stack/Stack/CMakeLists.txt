project(StackLib)

set(SOURCES Stack-bool.cpp)
set(HEADERS Stack.h Stack-impl.h)

add_library(stack_lib ${SOURCES} ${HEADERS})
target_include_directories(stack_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})