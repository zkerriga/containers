#include "gtest/gtest.h"
#include <map>
#include <iterator>
#include <limits>
#include "Any.hpp"

#define INT_VALUE 1232349
#define SIZE_T_VALUE 9000000000
#define SIZE_LITTLE 5
#define SIZE_LONG 34

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sMap		= std::map<char, Any>;
using mMap		= std::map<char, Any>;
//using sAlloc	= std::allocator<Any>;

TEST(map, test_for_tests) {
    ASSERT_TRUE(true);
}
