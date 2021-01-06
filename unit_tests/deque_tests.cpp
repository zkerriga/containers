#include "gtest/gtest.h"
#include <iterator>
#include <limits>
#include <deque>

#include "Any.hpp"

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sDec		= std::deque<Any>;
using mDec		= std::deque<Any>;

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
	mDec::reverse_iterator			s9;
	mDec::const_reverse_iterator	s10;
	mDec::difference_type			s11;
	mDec::size_type					s12;
}

TEST(deque, construct_basic) {
	sDec		s1;
	mDec		m1;
}
