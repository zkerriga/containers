#include "gtest/gtest.h"
#include "list.hpp"
#include <list>

#define INT_VALUE 1232349
#define SIZE_T_VALUE 9000000000
#define SIZE_LITTLE 5
#define SIZE_LONG 34

using sList = std::list<int>;
using mList = std::list<int>;
using sAlloc = std::allocator<int>;

class ListTestClass: public ::testing::Test {
public:
	ListTestClass() {
		// код инициализации
		for (int i = 0; i < 10; ++i) {
			sTenList.push_front(i);
		}
		for (int i = 100; i > 0; --i) {
			sLongList.push_front(i);
		}
		srand(time(nullptr));
		int size = rand() % 100 + 1;
		for (int i = 0; i < size; ++i) {
			sRandomList.push_front(rand());
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

	// сюда можно поместить необходимые вам пользовательские объекты данных
	sList				sEmptyList;
	sList				sTenList;
	sList				sLongList;
	sList				sRandomList;
	sList::iterator		sIt;
	sList::iterator		sIte;
	sAlloc				sAl;
};

void checkListContainsSingleValue(const sList & list, size_t size, const int value) {
	sList::const_iterator	it = list.begin();
	sList::const_iterator	ite = list.end();

	if (size == 0) {
		ASSERT_TRUE(it == ite);
		return;
	}
	while (it != ite) {
		ASSERT_EQ(*it, value);
		++it;
		--size;
	}
	ASSERT_TRUE(size == 0);
}

void assertListEQ(const sList & stdList, const mList & myList) {
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
}

TEST(list, basic_types) {
	sList::value_type				s1 = INT_VALUE;
	sList::allocator_type			s2;
	sList::reference				s3();
	sList::const_reference			s4();
	sList::pointer					s5;
	sList::const_pointer			s6;
	sList::iterator					s7;
	sList::const_iterator			s8;
	sList::reverse_iterator			s9;
	sList::const_reverse_iterator	s10;
	sList::difference_type			s11;
	sList::size_type				s12 = SIZE_T_VALUE;
}

TEST_F(ListTestClass, construct) {
	sList	s1;
	ASSERT_TRUE(s1.empty());

	sList	s2(sAl);
	ASSERT_TRUE(s2.empty());

	sList	s3(SIZE_LITTLE);
	checkListContainsSingleValue(s3, SIZE_LITTLE, int());

	sList	s4(SIZE_LITTLE, INT_VALUE);
	checkListContainsSingleValue(s4, SIZE_LITTLE, INT_VALUE);

	sList	s5(SIZE_LITTLE, INT_VALUE, sAl);
	checkListContainsSingleValue(s5, SIZE_LITTLE, INT_VALUE);

	sList	s6(sTenList.begin(), sTenList.end());
	assertListEQ(sTenList, s6);

	sList	s7(sTenList.begin(), sTenList.end(), sAl);
	assertListEQ(sTenList, s7);

	sList	s8(sRandomList.begin(), sRandomList.end());
	assertListEQ(sRandomList, s8);
}
