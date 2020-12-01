#include "gtest/gtest.h"
//#include "list.hpp"
#include <list>
#include <iterator>
#include <limits>

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
			sTenList.push_back(i);
		}
		for (int i = 100; i > 0; --i) {
			sLongList.push_back(i);
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
//	sList::reference				s3;
//	sList::const_reference			s4;
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

	sList	s9(sTenList);
	assertListEQ(sTenList, s9);

	sList	s10(sEmptyList);
	assertListEQ(sEmptyList, s10);

	sList	s11(sRandomList);
	assertListEQ(sRandomList, s11);

//	sList	s12(-1, INT_VALUE);
}

TEST_F(ListTestClass, assignation) {
	sList	s1;
	sList	s2;

	s2 = s1;
	assertListEQ(s2, s1);

	s1 = sTenList;
	assertListEQ(sTenList, s1);

	s1 = sEmptyList;
	assertListEQ(sEmptyList, s1);

	s1 = sRandomList;
	assertListEQ(sRandomList, s1);
}

TEST(list, iterator_types) {
	sList::iterator::value_type					s1;
	sList::iterator::difference_type			s2;
	sList::iterator::pointer					s3;
	sList::iterator::iterator_category			s4;
}

TEST_F(ListTestClass, const_iterators_empty) {
	sList::const_iterator	sIt = sEmptyList.begin();
	sList::const_iterator	sIte = sEmptyList.end();

	ASSERT_TRUE(*sIt == *sIte);
	ASSERT_TRUE(sIt == sIte);
	ASSERT_FALSE(sIt != sIte);

	sList::const_iterator	s3(sIt);
	sList::const_iterator	s4;
	s4 = sIte;

	ASSERT_TRUE(*s3 == *s4);
	ASSERT_TRUE(s3 == s4);
}

TEST_F(ListTestClass, iterators_empty) {
	sList::iterator	sIt = sEmptyList.begin();
	sList::iterator	sIte = sEmptyList.end();

	ASSERT_TRUE(*sIt == *sIte);
	ASSERT_TRUE(sIt == sIte);
	ASSERT_FALSE(sIt != sIte);

	sList::iterator	s3(sIt);
	sList::iterator	s4;
	s4 = sIte;

	ASSERT_TRUE(*s3 == *s4);
	ASSERT_TRUE(s3 == s4);
}

TEST_F(ListTestClass, const_iterator_bi) {
	sList::const_iterator			sIt = sTenList.begin();
	sList::const_iterator			sIte = sTenList.end();

	ASSERT_TRUE(sIt != sIte);

	sList::const_iterator			s3(sIt);
	sList::const_iterator			s4;
	s4 = sIt;

	++sIt;
	--sIt;
	ASSERT_TRUE(sIt == s4);
	ASSERT_TRUE(sIt == s3);

	s3 = sIt++;
	s4 = sIt--;
	ASSERT_EQ(*s3, 0);
	ASSERT_EQ(*s4, 1);

	int counter = 0;
	while (sIt != sIte) {
		ASSERT_EQ(*sIt, counter);
		++counter;
		++sIt;
	}
	ASSERT_EQ(counter, 10);
}

TEST_F(ListTestClass, iterator_bi) {
	sList::iterator			sIt = sTenList.begin();
	sList::iterator			sIte = sTenList.end();

	ASSERT_TRUE(sIt != sIte);

	sList::iterator			s3(sIt);
	sList::iterator			s4;
	s4 = sIt;

	++sIt;
	--sIt;
	ASSERT_TRUE(sIt == s4);
	ASSERT_TRUE(sIt == s3);

	s3 = sIt++;
	s4 = sIt--;
	ASSERT_EQ(*s3, 0);
	ASSERT_EQ(*s4, 1);

	int counter = 0;
	while (sIt != sIte) {
		ASSERT_EQ(*sIt, counter);
		++counter;
		++sIt;
	}
	ASSERT_EQ(counter, 10);

	sIt = sTenList.begin();
	sIte = sTenList.end();
	while (sIt != sIte) {
		*sIt = INT_VALUE;
		++sIt;
	}
	sList	s5(10, INT_VALUE);
	assertListEQ(s5, sTenList);
}

TEST_F(ListTestClass, const_iterator_reverse_empty) {
	sList::const_reverse_iterator	sRit = sEmptyList.rbegin();
	sList::const_reverse_iterator	sRite = sEmptyList.rend();

	ASSERT_TRUE(*sRit == *sRite);
	ASSERT_TRUE(sRit == sRite);
	ASSERT_FALSE(sRit != sRite);

	sList::const_reverse_iterator	s3(sRit);
	sList::const_reverse_iterator	s4;
	s4 = sRite;

	ASSERT_TRUE(*s3 == *s4);
	ASSERT_TRUE(s3 == s4);
}

TEST_F(ListTestClass, iterator_reverse_empty) {
	sList::reverse_iterator	sRit = sEmptyList.rbegin();
	sList::reverse_iterator	sRite = sEmptyList.rend();

	ASSERT_TRUE(*sRit == *sRite);
	ASSERT_TRUE(sRit == sRite);
	ASSERT_FALSE(sRit != sRite);

	sList::reverse_iterator	s3(sRit);
	sList::reverse_iterator	s4;
	s4 = sRite;

	ASSERT_TRUE(*s3 == *s4);
	ASSERT_TRUE(s3 == s4);
}

TEST_F(ListTestClass, const_iterator_reverse_bi) {
	sList::const_reverse_iterator			sRit = sTenList.rbegin();
	sList::const_reverse_iterator			sRite = sTenList.rend();

	ASSERT_TRUE(sRit != sRite);

	sList::const_reverse_iterator			s3(sRit);
	sList::const_reverse_iterator			s4;
	s4 = sRit;

	++sRit;
	--sRit;
	ASSERT_TRUE(sRit == s4);
	ASSERT_TRUE(sRit == s3);

	s3 = sRit++;
	s4 = sRit--;
	ASSERT_EQ(*s3, 9);
	ASSERT_EQ(*s4, 8);

	int counter = 9;
	while (sRit != sRite) {
		ASSERT_EQ(*sRit, counter);
		--counter;
		++sRit;
	}
	ASSERT_EQ(counter, -1);
}

TEST_F(ListTestClass, iterator_reverse_bi) {
	sList::reverse_iterator			sRit = sTenList.rbegin();
	sList::reverse_iterator			sRite = sTenList.rend();

	ASSERT_TRUE(sRit != sRite);

	sList::reverse_iterator			s3(sRit);
	sList::reverse_iterator			s4;
	s4 = sRit;

	++sRit;
	--sRit;
	ASSERT_TRUE(sRit == s4);
	ASSERT_TRUE(sRit == s3);

	s3 = sRit++;
	s4 = sRit--;
	ASSERT_EQ(*s3, 9);
	ASSERT_EQ(*s4, 8);

	int counter = 9;
	while (sRit != sRite) {
		ASSERT_EQ(*sRit, counter);
		--counter;
		++sRit;
	}
	ASSERT_EQ(counter, -1);

	sRit = sTenList.rbegin();
	sRite = sTenList.rend();
	while (sRit != sRite) {
		*sRit = INT_VALUE;
		++sRit;
	}
	sList	s5(10, INT_VALUE);
	assertListEQ(s5, sTenList);
}

TEST_F(ListTestClass, const_iterators_end) {
	sList::const_iterator			s1 = sTenList.begin();
	sList::const_reverse_iterator	sr2 = sTenList.rend();

	--sr2;
	ASSERT_EQ(*s1, *sr2);

	s1 = sTenList.end();
	sr2 = sTenList.rbegin();
	--s1;
	ASSERT_EQ(*s1, *sr2);
}

TEST_F(ListTestClass, iterators_end) {
	sList::iterator			s1 = sTenList.begin();
	sList::reverse_iterator	sr2 = sTenList.rend();

	--sr2;
	ASSERT_EQ(*s1, *sr2);

	s1 = sTenList.end();
	sr2 = sTenList.rbegin();
	--s1;
	ASSERT_EQ(*s1, *sr2);
}

TEST_F(ListTestClass, empty) {
	EXPECT_TRUE(sEmptyList.empty());
	EXPECT_FALSE(sTenList.empty());
}

TEST_F(ListTestClass, size) {
	EXPECT_EQ(sEmptyList.size(), 0);
	EXPECT_EQ(sTenList.size(), 10);
	EXPECT_EQ(sLongList.size(), 100);
}

TEST_F(ListTestClass, max_size) {
	const int	nPointersInStructure = 3;
	const int	structureSize = nPointersInStructure * sizeof(void *);

	EXPECT_EQ(sEmptyList.max_size(), static_cast<size_t>(-1) / structureSize);
}
