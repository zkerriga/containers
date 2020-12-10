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

/*class ListTestClass: public ::testing::Test {
public:
	ListTestClass() {
		// код инициализации
		for (int i = 0; i < 10; ++i) {
			sTenList.push_back(i);
			mTenList.push_back(i);
		}
		for (int i = 100; i > 0; --i) {
			sLongList.push_back(i);
			mLongList.push_back(i);
		}
		srand(time(nullptr));
		int size = rand() % 100 + 1;
		int randomInt = 0;
		for (int i = 0; i < size; ++i) {
			randomInt = rand();
			sRandomList.push_front(randomInt);
			mRandomList.push_front(randomInt);
		}
	}

	virtual void SetUp() {
		// код, который будет выполнен перед началом теста
	}

	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}

	~ListTestClass()  {
		// очистка всех ресурсов, вызов исключений не допускается
		sEmptyList.clear();
		sTenList.clear();
		sLongList.clear();
		sRandomList.clear();
	}

public:
	// сюда можно поместить необходимые вам пользовательские объекты данных
	sList				sEmptyList;
	mList				mEmptyList;

	sList				sTenList;
	mList				mTenList;

	sList				sLongList;
	mList				mLongList;

	sList				sRandomList;
	mList				mRandomList;

	sAlloc				sAl;
};*/

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

#undef DEBUG
