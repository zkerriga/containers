cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused -Wconversion -O2")

set(LIST_DIR list/)

set(TEMPLATE_DIR templates/)
set(SUPPORT ${TEMPLATE_DIR}support/)

include_directories(${TEMPLATE_DIR} ${SUPPORT})

set(LIST_SRC
        ${TEMPLATE_DIR}list.hpp
        ${SUPPORT}list_node.hpp
        ${SUPPORT}list_iterators.hpp
        )

set(VECTOR_SRC
        ${TEMPLATE_DIR}vector.hpp
        ${SUPPORT}vector_mem_worker.hpp
        ${SUPPORT}vector_iterators.hpp
        )

set(MAP_SRC
        ${TEMPLATE_DIR}map.hpp
        ${SUPPORT}map_iterators.hpp
        ${SUPPORT}tree_node.hpp
        )

set(DEQUE_SRC
        ${TEMPLATE_DIR}deque.hpp
        ${SUPPORT}block_chain.hpp
        )

set(SRCS
        ${TEMPLATE_DIR}utils.hpp
        ${LIST_SRC}
        ${VECTOR_SRC}
        ${MAP_SRC}
        ${DEQUE_SRC}
        )

add_executable(containers
        ${SRCS}
        main.cpp
        )

add_executable(feature
        feature.cpp
        )

add_library(testlib ${SRCS} main.cpp)
add_subdirectory(unit_tests)
