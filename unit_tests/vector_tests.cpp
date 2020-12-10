#include "gtest/gtest.h"
#include <vector>
#include <iterator>
#include <limits>
#include <iostream>

#include "vector.hpp"
#include "Any.hpp"

#define INT_VAL 1232349
#define SIZE_LITTLE 5
#define SIZE_LONG 34

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sVec		= std::vector<Any>;
using mVec		= ft::vector<Any>;
using sAlloc	= std::allocator<Any>;

class VecTest : public ::testing::Test {
public:
	VecTest() {
		// код инициализации
		sTen.reserve(10);
		mTen.reserve(10);
		for (int i = 1; i < 11; ++i) {
			sTen.push_back(Any(i));
			mTen.push_back(Any(i));
		}

		srand(time(nullptr));
		const int size = rand() % 100 + 1;
		sRandom.reserve(size);
		mRandom.reserve(size);
		int randomInt = 0;
		for (int i = 0; i < size; ++i) {
			randomInt = rand();
			sRandom.push_back(Any(randomInt));
			mRandom.push_back(Any(randomInt));
		}
	}
	virtual void SetUp() {
		// код, который будет выполнен перед началом теста
	}
	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}
	~VecTest() {
		// очистка всех ресурсов, вызов исключений не допускается
	}

public:
	sVec		sEmpty;
	sVec		sTen;
	sVec		sRandom;

	mVec		mEmpty;
	mVec		mTen;
	mVec		mRandom;

	sAlloc		sAl;
};

/*void assertVecEQ(const sVec & sV, const mVec & mV) {
	ASSERT_EQ(sV.size(), mV.size());
	sVec::const_iterator	sIt		= sV.begin();
	sVec::const_iterator	sIte	= sV.end();
	mVec::const_iterator	mIt		= mV.begin();
	mVec::const_iterator	mIte	= mV.end();

	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}*/

/*void assertListEQFromIterators(sList::const_iterator sIt, sList::const_iterator sIte,
							   mList::const_iterator mIt, mList::const_iterator mIte) {
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}*/
/*void assertListEQFromListAndIterators(sList stdList,
									  mList::const_iterator mIt, mList::const_iterator mIte) {
	sList::const_iterator	sIt = stdList.begin();
	sList::const_iterator	sIte = stdList.end();

	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}*/

TEST(vector, basic_types) {
	Any	a;

	mVec::value_type				s1 = a;
	mVec::allocator_type			s2;
	mVec::reference					s3 = a;
	mVec::const_reference			s4 = a;
	mVec::pointer					s5;
	mVec::const_pointer				s6;
	mVec::iterator					s7;
	mVec::const_iterator			s8;
	mVec::reverse_iterator			s9;
	mVec::const_reverse_iterator	s10;
	mVec::difference_type			s11;
	mVec::size_type					s12;
}

TEST(vector, create) {
	sVec	s1;
	mVec	m1;

	s1.push_back(Any(1));	m1.push_back(Any(1));
	s1.push_back(Any(2));	m1.push_back(Any(2));
	s1.push_back(Any(3));	m1.push_back(Any(3));

	ASSERT_EQ(s1.size(), m1.size());
	EXPECT_EQ(s1.capacity(), m1.capacity());
}

TEST_F(VecTest, basic_construct) {
//	assertVecEQ(sEmpty, mEmpty);
//	assertVecEQ(sTen, mTen);
//	assertVecEQ(sRandom, mRandom);
}

TEST_F(VecTest, iterator) {
	sVec::iterator	sIt = sTen.begin();

	sIt.opera
}


#undef DEBUG
