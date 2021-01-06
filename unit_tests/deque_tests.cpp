#include "gtest/gtest.h"
#include <iterator>
#include <deque>

#include "deque.hpp"

#include "Any.hpp"

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

#define LITTLE_SIZE 5
#define LARGE_SIZE 2167
#define ANY Any(42)

using sDec		= std::deque<Any>;
using mDec		= ft::deque<Any>;

TEST(deque, basic_types) {
	Any	a;

	mDec::value_type				s1 = a;
	mDec::allocator_type			s2;
	mDec::reference					s3 = a;
	mDec::const_reference			s4 = a;
	mDec::pointer					s5;
	mDec::const_pointer				s6;
	mDec::iterator					s7;
	mDec::const_iterator			s8;
//	mDec::reverse_iterator			s9; /* todo: iterators */
//	mDec::const_reverse_iterator	s10; /* todo iterators */
	mDec::difference_type			s11;
	mDec::size_type					s12;
}

TEST(deque, construct_basic) {
	sDec		s1;
	mDec		m1;

	sDec		s2(LITTLE_SIZE);
	mDec		m2(LITTLE_SIZE);

	sDec		s3(LARGE_SIZE, ANY);
	mDec		m3(LARGE_SIZE, ANY);
}
