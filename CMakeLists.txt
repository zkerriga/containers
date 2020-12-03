cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused -Wconversion -O2")

set(LIST_DIR list)

set(TEMPLATE_DIR templates)

include_directories(${TEMPLATE_DIR})

add_executable(containers
        main.cpp
        )

add_library(testlib ${SRCS} main.cpp)
add_subdirectory(unit_tests)