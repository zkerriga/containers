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

void assertListEQFromIterators(sList::const_iterator sIt, sList::const_iterator sIte,
							   mList::const_iterator mIt, mList::const_iterator mIte) {
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}

void assertListEQFromListAndIterators(sList stdList,
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
}

void assertListEQFromListAndRIterators(sList stdList,
									  mList::const_reverse_iterator mIt,
									  mList::const_reverse_iterator mIte) {
	sList::const_iterator	sIt = stdList.begin();
	sList::const_iterator	sIte = stdList.end();

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
	EXPECT_EQ(sTenList.max_size(), static_cast<size_t>(-1) / structureSize);

	std::list<float>	s1(3);
	EXPECT_EQ(s1.max_size(), static_cast<size_t>(-1) / structureSize);
}

TEST_F(ListTestClass, front) {
	ASSERT_EQ(sTenList.front(), 0);

	sTenList.front() = INT_VALUE;
	ASSERT_EQ(sTenList.front(), INT_VALUE);

//	ASSERT_EQ(sEmptyList.front(), int());
//
//	sEmptyList.front() = INT_VALUE;
//	ASSERT_EQ(sEmptyList.front(), INT_VALUE);
}

TEST_F(ListTestClass, back) {
	ASSERT_EQ(sTenList.back(), 9);

	sTenList.back() = INT_VALUE;
	ASSERT_EQ(sTenList.back(), INT_VALUE);

//	ASSERT_EQ(sEmptyList.back(), int());
//
//	sEmptyList.back() = INT_VALUE;
//	ASSERT_EQ(sEmptyList.back(), INT_VALUE);
}

TEST_F(ListTestClass, assign) {
	sEmptyList.assign(SIZE_LITTLE, INT_VALUE);
	sList		s1(SIZE_LITTLE, INT_VALUE);
	assertListEQ(s1, sEmptyList);

	sEmptyList.assign(0, INT_VALUE);
	ASSERT_TRUE(sEmptyList.empty());

	sEmptyList.assign(++sTenList.begin(), sTenList.end());
	ASSERT_EQ(sEmptyList.size(), sTenList.size() - 1);

	sEmptyList.assign(sTenList.end(), sTenList.end());
	ASSERT_TRUE(sEmptyList.empty());
}

TEST_F(ListTestClass, push_front) {
	sList			s1(sEmptyList);

	s1.push_front(INT_VALUE);
	ASSERT_EQ(s1.size(), 1);
	ASSERT_EQ(s1.front(), INT_VALUE);

	s1.push_front(INT_VALUE - 1);
	ASSERT_EQ(s1.size(), 2);
	ASSERT_EQ(s1.front(), INT_VALUE - 1);
	ASSERT_EQ(s1.back(), INT_VALUE);

	sList			s2(sEmptyList);
	for (int i = 9; i > -1; --i) {
		s2.push_front(i);
	}
	assertListEQ(sTenList, s2);

	sList					s3(sTenList);
	sList::const_iterator	it = s3.begin();
	sList::const_iterator	ite = s3.end();
	s3.push_front(INT_VALUE);
	assertListEQFromListAndIterators(sTenList, it, ite);
	it = s3.begin();
	assertListEQFromListAndIterators(sTenList, ++it, ite);
}

TEST_F(ListTestClass, pop_front) {
	sList		s1(sTenList);

	s1.pop_front();
	ASSERT_EQ(s1.size(), sTenList.size() - 1);
	assertListEQFromIterators(++sTenList.begin(), sTenList.end(), s1.begin(), s1.end());

	for (int i = 1; i < 10; ++i) {
		ASSERT_EQ(s1.front(), i);
		s1.pop_front();
	}
	assertListEQ(sEmptyList, s1);

//	s1.pop_front();
//	ASSERT_EQ(s1.size(), 0);

	sList					s2(sTenList);
	sList::const_iterator	it1 = s2.begin();
	ASSERT_EQ(*it1, 0);
	s2.pop_front();
	sList::const_iterator	it2 = s2.begin();
	ASSERT_TRUE(it1 != it2);
}

TEST_F(ListTestClass, push_back) {
	sList s1(sEmptyList);

	s1.push_back(INT_VALUE);
	ASSERT_EQ(s1.size(), 1);
	ASSERT_EQ(s1.back(), INT_VALUE);

	s1.push_back(INT_VALUE - 1);
	ASSERT_EQ(s1.size(), 2);
	ASSERT_EQ(s1.back(), INT_VALUE - 1);
	ASSERT_EQ(s1.front(), INT_VALUE);

	sList s2(sEmptyList);
	for (int i = 0; i < 10; ++i) {
		s2.push_back(i);
	}
	assertListEQ(sTenList, s2);

	sList::const_iterator	it = s2.begin();
	sList::const_iterator	ite = s2.end();
	s2.push_back(INT_VALUE - 3);
	ASSERT_EQ(s2.back(), INT_VALUE - 3);
	assertListEQFromListAndIterators(sTenList, it, --ite);
}

TEST_F(ListTestClass, pop_back) {
	sList		s1(sTenList);

	s1.pop_back();
	ASSERT_EQ(s1.size(), sTenList.size() - 1);
	assertListEQFromIterators(sTenList.begin(), --sTenList.end(), s1.begin(), s1.end());

	for (int i = 8; i > -1; --i) {
		ASSERT_EQ(s1.back(), i);
		s1.pop_back();
	}
	assertListEQ(sEmptyList, s1);

//	s1.pop_back();
//	ASSERT_EQ(s1.size(), 0);

	sList					s2(sTenList);
	sList::const_iterator	ite = s2.end();
	s2.pop_back();
	assertListEQFromIterators(sTenList.begin(), --sTenList.end(), s2.begin(), ite);
}

void printList(sList list) {
	sList::const_iterator	it = list.begin();
	sList::const_iterator	ite = list.end();

	std::cout << "List = ";
	while (it != ite) {
		std::cout << *it++ << ", ";
	}
	std::cout << ";" << std::endl;
}

TEST_F(ListTestClass, insert) {
	sList		s1(sEmptyList);

	s1.insert(s1.begin(), INT_VALUE);
	ASSERT_EQ(s1.size(), 1);
	ASSERT_EQ(s1.front(), INT_VALUE);
	s1.pop_front();

	s1.insert(s1.end(), INT_VALUE - 1);
	ASSERT_EQ(s1.size(), 1);
	ASSERT_EQ(s1.front(), INT_VALUE - 1);
	s1.pop_front();

	s1.push_front(0);
	s1.push_back(9);
	s1.insert(++s1.begin(), ++sTenList.begin(), --sTenList.end());
	assertListEQ(sTenList, s1);

	sList		s2(sEmptyList);
	s2.push_front(INT_VALUE - 2);
	s2.insert(s2.begin(), SIZE_LONG, INT_VALUE - 2);
	checkListContainsSingleValue(s2, SIZE_LONG + 1, INT_VALUE - 2);

	sList				s3(sTenList);
	sList::iterator		it = s3.begin();

	++it, ++it, ++it;
	s3.insert(it, SIZE_LITTLE, INT_VALUE);
	ASSERT_EQ(*it, 3);
	it = s3.begin();
	bool flag = true;
	for (int i = 0; i < 10; ++i) {
		if (i == 3 && flag) {
			for (int j = 0; j < SIZE_LITTLE; ++j) {
				EXPECT_EQ(*it++, INT_VALUE);
			}
			--i;
			flag = false;
			continue;
		}
		EXPECT_EQ(*it++, i);
	}
}

TEST_F(ListTestClass, erase) {
//	sEmptyList.erase(sEmptyList.begin());
//	ASSERT_TRUE(sEmptyList.empty());

	sEmptyList.push_front(INT_VALUE);
	sEmptyList.erase(sEmptyList.begin());
	ASSERT_TRUE(sEmptyList.empty());

	sList					s1(sTenList);
	sList::const_iterator	it = s1.begin();
	s1.push_back(INT_VALUE);
	s1.erase(--s1.end());
	assertListEQFromListAndIterators(sTenList, it, s1.end());

	sList			s2(sTenList);
	sList::iterator	it2 = s2.begin();
	++it2, ++it2, ++it2;

	s2.insert(it2, SIZE_LITTLE, INT_VALUE);
	it2 = s2.begin();
	++it2, ++it2, ++it2;
	sList::iterator	ite2(it2);

	for (int i = 0; i < SIZE_LITTLE; ++i)
		++ite2;
	s2.erase(it2, ite2);
	ASSERT_EQ(s2.size(), 10);
	assertListEQ(sTenList, s2);
}

TEST_F(ListTestClass, swap) {
	sList		s1(sEmptyList);
	sList		s2(sTenList);

	s1.swap(s2);
	assertListEQ(sEmptyList, s2);
	assertListEQ(sTenList, s1);

	sList					s3(sRandomList);
	sList					s4(sTenList);

	s3.swap(s4);
	assertListEQ(sTenList, s3);
	assertListEQ(sRandomList, s4);
}

TEST_F(ListTestClass , resize) {
	sEmptyList.resize(0);
	ASSERT_TRUE(sEmptyList.empty());

	sList		s1(sTenList);
	s1.resize(SIZE_LITTLE);
	s1.resize(SIZE_LITTLE, INT_VALUE);
	s1.resize(SIZE_LONG, INT_VALUE - 1);

	sList::const_iterator	it = s1.begin();
	sList::const_iterator	ite = s1.end();
	for (int i = 0; i < SIZE_LITTLE; ++i) {
		ASSERT_EQ(*it++, i);
	}
	for (int i = 0; i < SIZE_LONG - SIZE_LITTLE; ++i) {
		ASSERT_EQ(*it++, INT_VALUE - 1);
	}
	ASSERT_TRUE(it == ite);
}

TEST_F(ListTestClass, clear) {
	sEmptyList.clear();
	ASSERT_EQ(sEmptyList.size(), 0);
	ASSERT_TRUE(sEmptyList.empty());

	sTenList.clear();
	ASSERT_EQ(sTenList.size(), 0);
	ASSERT_TRUE(sTenList.empty());

	sRandomList.clear();
	ASSERT_EQ(sRandomList.size(), 0);
	ASSERT_TRUE(sRandomList.empty());

	sEmptyList.push_back(INT_VALUE);
	ASSERT_EQ(sEmptyList.front(), INT_VALUE);
}

TEST_F(ListTestClass, splice) {
	sList		s1(sEmptyList);
	sList		s2(sTenList);

	s1.splice(s1.begin(), s2);
	assertListEQ(sTenList, s1);
	assertListEQ(sEmptyList, s2);

	sList		s3(sTenList);
	sList		s4(sRandomList);

	s4.splice(s4.begin(), s3, ++s3.begin());
	sList::const_iterator	it = s4.begin();
	ASSERT_EQ(*it++, 1);
	assertListEQFromListAndIterators(sRandomList, it, s4.end());
	ASSERT_EQ(s3.size(), sTenList.size() - 1);

	sList		s5(sTenList);
	sList		s6(sRandomList);

	s6.splice(++s6.begin(), s5, s5.begin(), --s5.end());
	it = s6.begin();
	ASSERT_EQ(*it++, sRandomList.front());
	for (int i = 0; i < 9; ++i) {
		ASSERT_EQ(*it++, i);
	}
	assertListEQFromIterators(++sRandomList.begin(), sRandomList.end(), it, s6.end());
	ASSERT_EQ(s5.size(), 1);
	ASSERT_EQ(s5.front(), sTenList.back());
}

TEST_F(ListTestClass, remove) {
	sEmptyList.remove(INT_VALUE);
	ASSERT_TRUE(sEmptyList.empty());

	sList		s1(SIZE_LONG, INT_VALUE);

	s1.remove(INT_VALUE);
	ASSERT_TRUE(s1.empty());

	sList		s2(sTenList);
	sList		s3(sTenList);
	sList		s4(sTenList);

	s2.remove(0);
	s3.remove(5);
	s4.remove(9);
	ASSERT_EQ(s2.size(), 9);
	ASSERT_EQ(s3.size(), 9);
	ASSERT_EQ(s4.size(), 9);

	sList::const_iterator	it = s2.begin();
	for (int i = 1; i < 10; ++i) {
		ASSERT_EQ(*it++, i);
	}
	it = s3.begin();
	for (int i = 0; i < 10; ++i) {
		if (i == 5)
			continue;
		ASSERT_EQ(*it++, i);
	}
	it = s4.begin();
	for (int i = 0; i < 9; ++i) {
		ASSERT_EQ(*it++, i);
	}
}

static bool allTrue(int val) {
	return true;
}

static bool allFalse(int val) {
	return false;
}

static bool check(int val) {
	return (val % 2 == 0);
}

TEST_F(ListTestClass, remove_if) {
	sEmptyList.remove_if(allTrue);
	sEmptyList.remove_if(allFalse);
	ASSERT_TRUE(sEmptyList.empty());

	sList		s1(sTenList);
	s1.remove_if(allFalse);
	ASSERT_EQ(s1.size(), sTenList.size());
	s1.remove_if(check);
	ASSERT_EQ(s1.size(), 5);
	sList::const_iterator		it = s1.begin();
	for (int i = 1; i < 10; i += 2) {
		ASSERT_EQ(*it++, i);
	}
	s1.remove_if(allTrue);
	ASSERT_TRUE(s1.empty());
}

static bool binaryAllTrue(int prev, int cur) {
	return true;
}

static bool binaryAllFalse(int prev, int cur) {
	return false;
}

static bool binaryCheck(int cur, int prev) {
	return (prev > cur);
}

TEST_F(ListTestClass, unique) {
	sEmptyList.unique();
	ASSERT_TRUE(sEmptyList.empty());

	sList		s1(sTenList);
	s1.unique();
	assertListEQ(sTenList, s1);

	sList		s2(SIZE_LONG, INT_VALUE);
	s2.unique();
	ASSERT_EQ(s2.size(), 1);
	ASSERT_EQ(s2.front(), INT_VALUE);

	sList		s3(sTenList);
	s3.insert(++s3.begin(), 1);
	s3.insert(++s3.begin(), 1);

	s3.unique();
	assertListEQ(sTenList, s3);

	sList		s4(sTenList);
	s4.push_back(9);
	s4.unique();
	assertListEQ(sTenList, s4);

	sEmptyList.unique(binaryAllFalse);
	sEmptyList.unique(binaryAllTrue);
	ASSERT_TRUE(sEmptyList.empty());

	sList		s5(sTenList);
	s5.unique(binaryAllFalse);
	ASSERT_FALSE(s5.empty());
	s5.unique(binaryCheck);
	ASSERT_EQ(s5.size(), 1);
	ASSERT_EQ(s5.front(), 0);

	sList		s6(sTenList);
	s6.push_front(INT_VALUE);
	s6.unique(binaryCheck);
	ASSERT_EQ(s6.size(), 2);
	ASSERT_EQ(s6.front(), INT_VALUE);
	ASSERT_EQ(*(++s6.begin()), 0);
}

bool myCompare (int first, int second) {
	return ( (first / 10) < (second / 10) );
}

bool except (int first, int second) {
	throw std::exception();
}

TEST_F(ListTestClass, merge) {
	sList		s1;
	s1.push_back(22);
	s1.push_back(29);
	s1.push_back(31);

	sList		s2;
	s2.push_back(14);
	s2.push_back(37);
	s2.push_back(71);

	s1.merge(s2);
	ASSERT_TRUE(s2.empty());

	s2.push_back(21);
	s1.merge(s2, myCompare);

	int		result[] = {14, 22, 29, 21, 31, 37, 71};
	sList	sResult(result, result + 7);

	assertListEQ(sResult, s1);
	ASSERT_TRUE(s2.empty());

	try {
		s1.merge(sTenList, except);
	}
	catch (std::exception &) {}
	assertListEQ(sResult, s1);
}

bool compareAllFalse(int first, int second) {
	return false;
}

bool compareAllTrue(int first, int second) {
	return true;
}

bool compareNormal(int first, int second) {
	return (first < second);
}

bool compareStupid(int first, int second) {
	return (first == 2);
}

TEST_F(ListTestClass, sort) {
	sEmptyList.sort();
	ASSERT_TRUE(sEmptyList.empty());

	sList		s1(sTenList);
	s1.sort();
	assertListEQ(sTenList, s1);

	s1.sort(compareAllFalse);
	assertListEQ(sTenList, s1);

	s1.sort(compareAllTrue);
	assertListEQFromListAndRIterators(sTenList, s1.rbegin(), s1.rend());

	s1.sort(compareNormal);
	assertListEQ(sTenList, s1);

	s1.sort(compareStupid);
	int		result[] = {2, 0, 1, 3, 4, 5, 6, 7, 8, 9};
	sList	sResult(result, result + 10);
	assertListEQ(sResult, s1);
}

TEST_F(ListTestClass, reverse) {
	sEmptyList.reverse();
	ASSERT_TRUE(sEmptyList.empty());

	sList		s1(sTenList);
	s1.reverse();
	assertListEQFromListAndRIterators(sTenList, s1.rbegin(), s1.rend());

	sList		s2(sRandomList);

	s2.reverse();
	s2.reverse();
	assertListEQ(sRandomList, s2);
}

TEST_F(ListTestClass, get_allocator) {
	sList	s1(sAl);
	int *	p;

	p = s1.get_allocator().allocate(10);

	for (int i = 0; i < 10; ++i)
		p[i] = i;

	sList	s2(p, p + 10);
	assertListEQ(sTenList, s2);

	s1.get_allocator().deallocate(p,10);
}