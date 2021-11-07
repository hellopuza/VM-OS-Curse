cmake_minimum_required(VERSION 3.9)
project(QueueLib VERSION 1.0.0 DESCRIPTION "Queue library")

add_subdirectory(test)
add_subdirectory(lib/Stack)

file(GLOB_RECURSE QUEUE_SOURCES *.cpp)
file(GLOB_RECURSE QUEUE_HEADERS *.h)

add_library(queue STATIC ${QUEUE_SOURCES} ${QUEUE_HEADERS})
target_link_libraries(queue stack)

set(QUEUE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(queue
    PUBLIC ${QUEUE_INCLUDE}
    PUBLIC ${STACK_INCLUDE}
)

set_target_properties(queue PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion \
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls -Wsign-conversion -Wnon-virtual-dtor \
    -Wctor-dtor-privacy -Woverloaded-virtual -Wno-float-equal"
)