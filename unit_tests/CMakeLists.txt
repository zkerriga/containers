project(Google_tests)

set(CMAKE_CXX_FLAGS "-Wno-unused")

add_subdirectory(lib)
include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)

set(TEST_FILES
#        list_tests.cpp
#        vector_tests.cpp
#        map_tests.cpp
#        deque_tests.cpp
        stack_tests.cpp
        utils.hpp
)

add_executable(Google_Tests_run
        ${TEST_FILES}
        Any.cpp
        Any.hpp
)

target_link_libraries(Google_Tests_run gtest gtest_main testlib)
