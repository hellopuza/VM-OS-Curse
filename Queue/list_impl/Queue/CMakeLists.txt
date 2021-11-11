cmake_minimum_required(VERSION 3.9)
project(QueueLib VERSION 1.0.0 DESCRIPTION "Queue library")

file(GLOB_RECURSE QUEUE_HEADERS *.h)

set(QUEUE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (ADD_TESTING)
    add_subdirectory(test)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion \
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls -Wsign-conversion -Wnon-virtual-dtor \
    -Wctor-dtor-privacy -Woverloaded-virtual -Wno-float-equal"
)