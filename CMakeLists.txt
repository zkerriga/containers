cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused -Wconversion -O2")

set(LIST_DIR list/)

set(TEMPLATES templates/)
set(SUPPORT ${TEMPLATE_DIR}support/)

include_directories(${TEMPLATES} ${SUPPORT})

set(LIST_SRC
        ${TEMPLATES}list.hpp
        ${TEMPLATES}${SUPPORT}list_node.hpp
        ${TEMPLATES}${SUPPORT}list_iterators.hpp
        )

set(VECTOR_SRC
        ${TEMPLATES}vector.hpp
        )

set(SRCS
        ${TEMPLATES}utils.hpp
#        ${LIST_SRC}
        ${VECTOR_SRC}
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
