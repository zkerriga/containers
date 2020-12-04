cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused -Wconversion -O2")

set(LIST_DIR list/)

set(TEMPLATES templates/)
set(SUPPORT ${TEMPLATE_DIR}support/)

include_directories(${TEMPLATES} ${SUPPORT})

set(SRCS
        ${TEMPLATES}list.hpp
        ${TEMPLATES}${SUPPORT}list_node.hpp
        ${TEMPLATES}${SUPPORT}list_iterators.hpp
        )

add_executable(containers
        ${SRCS}
        main.cpp
        )

add_executable(feature
        feature.cpp
        templates/support/list_node.hpp
        )

add_library(testlib ${SRCS} main.cpp)
add_subdirectory(unit_tests)