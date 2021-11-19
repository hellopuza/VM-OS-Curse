cmake_minimum_required(VERSION 3.16.3)
project(Queue-list_impl VERSION 1.0.0 DESCRIPTION "Queue library with list implementation")

set(QUEUE_LIST_IMPL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion \
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls -Wsign-conversion -Wnon-virtual-dtor \
    -Wctor-dtor-privacy -Woverloaded-virtual -Wno-float-equal"
)