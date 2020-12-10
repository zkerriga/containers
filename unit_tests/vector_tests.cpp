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
	VecTest() {
		// код инициализации
		sTen.reserve(10);
		for (int i = 1; i < 11; ++i) {
			sTen.push_back(Any(i));
		}

		srand(time(nullptr));
		const int size = rand() % 100 + 1;
		sRandom.reserve(size);
		int randomInt = 0;
		for (int i = 0; i < size; ++i) {
			randomInt = rand();
			sRandom.push_back(Any(randomInt));
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

	sAlloc		sAl;
};

/*void assertListEQ(const sList & stdList, const mList & myList) {
	ASSERT_EQ(stdList.size(), myList.size());

	sList::const_iterator	sIt = stdList.begin();
	sList::const_iterator	sIte = stdList.end();
	mList::const_iterator	mIt = myList.begin();
	mList::const_iterator	mIte = myList.end();

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



#undef DEBUG
