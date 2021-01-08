#include "gtest/gtest.h"
#include <vector>
#include <list>
#include <deque>
#include <queue>

#include "Any.hpp"

#define ANY Any(42)

#include "queue.hpp"

using sQu	= std::queue<Any>;
using mQu	=  ft::queue<Any>;

TEST(queue, types) {
	Any	a;

	sQu::value_type		s1 = a;
	sQu::container_type	s2;
	sQu::size_type		s3 = 1;

	mQu::value_type		m1 = a;
	mQu::container_type	m2;
	mQu::size_type		m3 = 1;
}

TEST(queue, construct) {
	using sVec	= std::vector<Any>;
	using sList	= std::list<Any>;

	std::queue<Any>			s1;
	ft::queue<Any>			m1;
	std::queue<Any,sVec>	s2;
	ft::queue<Any,sVec>	m2;
	std::queue<Any,sList>	s3;
	ft::queue<Any,sList>	m3;
}

TEST(queue, empty) {
	sQu		s1;
	sQu		s2;
	s2.push(ANY);

	mQu		m1;
	mQu		m2;
	m2.push(ANY);

	ASSERT_EQ(s1.empty(), m1.empty());
	ASSERT_EQ(s2.empty(), m2.empty());
}

TEST(queue, size) {
	sQu		s1;
	mQu		m1;
	s1.push(ANY);		m1.push(ANY);
	ASSERT_EQ(s1.size(), m1.size());
	s1.push(Any());		m1.push(Any());
	ASSERT_EQ(s1.size(), m1.size());
	s1.push(Any(1));		m1.push(Any(1));
	ASSERT_EQ(s1.size(), m1.size());
}

TEST(queue, push_pop_front_back) {
	sQu		s1;
	mQu		m1;
	s1.push(ANY);			m1.push(ANY);
	s1.push(ANY);			m1.push(ANY);
	ASSERT_EQ(s1.front(), m1.front());
	ASSERT_EQ(s1.back(), m1.back());
	s1.push(Any(1));		m1.push(Any(1));
	ASSERT_EQ(s1.back(), m1.back());
	ASSERT_EQ(s1.front(), m1.front());
	s1.push(Any(2));		m1.push(Any(2));
	ASSERT_EQ(s1.back(), m1.back());
	ASSERT_EQ(s1.front(), m1.front());
	s1.pop();				m1.pop();
	ASSERT_EQ(s1.back(), m1.back());
	ASSERT_EQ(s1.front(), m1.front());
	s1.pop();				m1.pop();
	ASSERT_EQ(s1.back(), m1.back());
	ASSERT_EQ(s1.front(), m1.front());
	s1.pop();				m1.pop();
	ASSERT_EQ(s1.back(), m1.back());
	ASSERT_EQ(s1.front(), m1.front());
}

TEST(queue, operators) {
	sQu		s1;
	s1.push(ANY);
	sQu		s2;
	s2.push(Any(1));
	s2.push(Any(100));

	mQu		m1;
	m1.push(ANY);
	mQu		m2;
	m2.push(Any(1));
	m2.push(Any(100));

	ASSERT_EQ(s1 == s2, m1 == m2);
	ASSERT_EQ(s1 != s2, m1 != m2);
	ASSERT_EQ(s1 < s2, m1 < m2);
	ASSERT_EQ(s1 <= s2, m1 <= m2);
	ASSERT_EQ(s1 > s2, m1 > m2);
	ASSERT_EQ(s1 >= s2, m1 >= m2);
}

#undef ANY
