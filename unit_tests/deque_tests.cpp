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
#define LARGE_SIZE 84
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

void	assertDequeEQ(sDec & sM, mDec & mM) {
	ASSERT_EQ(sM.size(), mM.size());
	ASSERT_EQ(sM.empty(), mM.empty());

	sDec::iterator	sIt		= sM.begin();
	sDec::iterator	sIte	= sM.end();
	mDec::iterator	mIt		= mM.begin();
	mDec::iterator	mIte	= mM.end();

	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	++sIt; --sIt;
	++mIt; --mIt;
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}

TEST(deque, construct_basic) {
	sDec		s1;
	mDec		m1;

	sDec		s2(LITTLE_SIZE);
	mDec		m2(LITTLE_SIZE);
	assertDequeEQ(s2, m2);

	sDec		s3(LARGE_SIZE, ANY);
	mDec		m3(LARGE_SIZE, ANY);
	assertDequeEQ(s3, m3);

	Any		ar[] = {Any(1), Any(2), Any(3), Any(4)};

	sDec		s4(ar, ar + 4);
	mDec		m4(ar, ar + 4);
	assertDequeEQ(s4, m4);

	sDec		s5(s4);
	mDec		m5(m4);
	assertDequeEQ(s5, m5);

	s5 = s3;
	m5 = m3;
	assertDequeEQ(s5, m5);
}
