cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused -Wconversion -O2")

set(LIST_DIR list)

set(TEMPLATE_DIRS
        ${LIST_DIR}
        )

include_directories(${TEMPLATE_DIRS})

set(SRCS
        ${LIST_DIR}/list.hpp
        ${LIST_DIR}/list_initialize.hpp
        ${LIST_DIR}/list_methods_capacity.hpp
        ${LIST_DIR}/list_methods_element_access.hpp
        ${LIST_DIR}/list_methods_iterators.hpp
        ${LIST_DIR}/list_methods_modifiers.hpp
        ${LIST_DIR}/list_methods_observers.hpp
        ${LIST_DIR}/list_methods_operations.hpp
        )

add_executable(containers
        ${SRCS}
        main.cpp
        )

add_library(testlib ${SRCS} main.cpp)
add_subdirectory(unit_tests)