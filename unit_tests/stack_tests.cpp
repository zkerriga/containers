#include "gtest/gtest.h"
#include <iterator>
#include <limits>
#include <stack>
#include <vector>
#include <list>
#include <deque>

#include "Any.hpp"
#include "utils.hpp"

#define ANY Any(42)

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

TEST(stack, construct) {
	sStack			s1;
	mStack			m1;
	sStack			s2(std::vector<Any>());
	mStack			m2(std::vector<Any>());
	sStack			s3(std::list<Any>());
	mStack			m3(std::list<Any>());
}

TEST(stack, empty) {
	sStack		s1;
	sStack		s2;
	s2.push(ANY);

	mStack		m1;
	mStack		m2;
	m2.push(ANY);

	ASSERT_EQ(s1.empty(), m1.empty());
	ASSERT_EQ(s2.empty(), m2.empty());
}

TEST(stack, size) {
	sStack		s1;
	mStack		m1;
	s1.push(ANY);		m1.push(ANY);
	ASSERT_EQ(s1.size(), m1.size());
	s1.push(Any());		m1.push(Any());
	ASSERT_EQ(s1.size(), m1.size());
	s1.push(Any(1));		m1.push(Any(1));
	ASSERT_EQ(s1.size(), m1.size());
}

TEST(stack, top_push_pop) {
	sStack		s1;
	mStack		m1;
	s1.push(ANY);			m1.push(ANY);
	s1.push(ANY);			m1.push(ANY);
	ASSERT_EQ(s1.top(), m1.top());
	s1.push(Any(1));		m1.push(Any(1));
	ASSERT_EQ(s1.top(), m1.top());
	s1.push(Any(2));		m1.push(Any(2));
	ASSERT_EQ(s1.top(), m1.top());
	s1.pop();				m1.pop();
	ASSERT_EQ(s1.top(), m1.top());
	s1.pop();				m1.pop();
	ASSERT_EQ(s1.top(), m1.top());
	s1.pop();				m1.pop();
	ASSERT_EQ(s1.top(), m1.top());
}
