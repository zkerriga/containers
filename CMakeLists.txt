cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused -Wconversion")

set(T_DIR templates)
include_directories(${T_DIR})

set(SRCS
        ${T_DIR}/list.hpp
        )

add_executable(containers
        ${SRCS}
        main.cpp
        )

add_library(testlib ${SRCS} main.cpp)
add_subdirectory(unit_tests)