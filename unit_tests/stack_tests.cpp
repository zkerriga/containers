#include "gtest/gtest.h"
#include <iterator>
#include <limits>
#include <stack>

#include "Any.hpp"
#include "utils.hpp"

#include "stack.hpp"

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sStack	= std::stack<Any>;
using mStack	=  ft::stack<Any>;

TEST(stack, basic_types) {
	Any	a;

	sStack::value_type		s1 = a;
	sStack::container_type	s2;
	sStack::size_type		s3 = 1;

	mStack::value_type		m1 = a;
	mStack::container_type	m2;
	mStack::size_type		m3 = 1;
}
