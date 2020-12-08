#include "gtest/gtest.h"
#include "list.hpp"
#include "support/list_node.hpp"
#include <list>
#include <iterator>
#include <limits>

#define INT_VALUE 1232349
#define SIZE_T_VALUE 9000000000
#define SIZE_LITTLE 5
#define SIZE_LONG 34

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sList		= std::list<int>;
using mList		= ft::list<int>;
using sAlloc	= std::allocator<int>;

class ListTestClass: public ::testing::Test {
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
};

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

	mList::value_type				m1 = INT_VALUE;
	mList::allocator_type			m2;
//	mList::reference				m3;
//	mList::const_reference			m4;
	mList::pointer					m5;
	mList::const_pointer			m6;
	mList::iterator					m7;
	mList::const_iterator			m8;
	mList::reverse_iterator			m9;
	mList::const_reverse_iterator	m10;
	mList::difference_type			m11;
	mList::size_type				m12 = SIZE_T_VALUE;
}

TEST(list, _lst) {
	using _lst	= ListNode<int, std::allocator<int> >;

	ASSERT_EQ(sizeof(_lst), 8 * 3);
	sAlloc		sAl;

	_lst *	endNode = _lst::getNewNode(sAl);
	_lst *	newNode = _lst::setDataReturnNode(
			_lst::getNewNode(sAl),
			INT_VALUE,
			sAl
	);
	_lst::insertBetween(newNode, endNode->prev, endNode);

	newNode = _lst::setDataReturnNode(
			_lst::getNewNode(sAl),
			INT_VALUE - 1,
			sAl
	);
	_lst::insertBetween(newNode, endNode->prev, endNode);

	ASSERT_EQ(*(endNode->next->data), INT_VALUE);
	ASSERT_EQ(*(endNode->next->next->data), INT_VALUE - 1);
	ASSERT_EQ(*(endNode->prev->data), INT_VALUE - 1);
	ASSERT_EQ(*(endNode->prev->prev->data), INT_VALUE);

	D( _lst::printList(endNode->next, endNode); )
}

TEST_F(ListTestClass, construct) {
	sList	s1;
	mList	m1;
	ASSERT_TRUE(s1.empty() == m1.empty());

	sList	s2(sAl);
	mList	m2(sAl);
	ASSERT_TRUE(s1.empty() == m1.empty());

	sList	s3(SIZE_LITTLE);
	mList	m3(SIZE_LITTLE);
	assertListEQ(s3, m3);

	sList	s4(SIZE_LITTLE, INT_VALUE);
	mList	m4(SIZE_LITTLE, INT_VALUE);
	assertListEQ(s4, m4);

	sList	s5(SIZE_LITTLE, INT_VALUE, sAl);
	mList	m5(SIZE_LITTLE, INT_VALUE, sAl);
	assertListEQ(s5, m5);

	sList	s6(sTenList.begin(), sTenList.end());
	mList	m6(sTenList.begin(), sTenList.end());
	assertListEQ(s6, m6);

	sList	s7(sTenList.begin(), sTenList.end(), sAl);
	mList	m7(sTenList.begin(), sTenList.end(), sAl);
	assertListEQ(s7, m7);

	sList	s8(sRandomList.begin(), sRandomList.end());
	mList	m8(sRandomList.begin(), sRandomList.end());
	assertListEQ(s8, m8);

	sList	s9(sTenList);
	mList	m9(mTenList);
	assertListEQ(s9, m9);

	sList	s10(sEmptyList);
	mList	m10(mEmptyList);
	assertListEQ(s10, m10);

	sList	s11(sRandomList);
	mList	m11(mRandomList);
	assertListEQ(s11, m11);

//	sList	s12(-1, INT_VALUE);
//	mList	m12(-1, INT_VALUE);
}

TEST_F(ListTestClass, destructor) {
	// For debug mode ;)
	mList	m1(mTenList);
}

TEST_F(ListTestClass, assignation) {
	sList	s1;
	sList	s2;
	mList	m1;
	mList	m2;

	s2 = s1;
	m2 = m1;
	assertListEQ(s2, m2);

	s1 = sTenList;
	m1 = mTenList;
	assertListEQ(sTenList, m1);

	s1 = sEmptyList;
	m1 = mEmptyList;
	assertListEQ(sEmptyList, m1);

	s1 = sRandomList;
	m1 = mRandomList;
	assertListEQ(sRandomList, m1);
}

TEST(list, iterator_types) {
	sList::iterator::value_type					s1;
	sList::iterator::difference_type			s2;
	sList::iterator::pointer					s3;
	sList::iterator::iterator_category			s4;

	mList::iterator::value_type					m1;
	mList::iterator::difference_type			m2;
	mList::iterator::pointer					m3;
	mList::iterator::iterator_category			m4;
}

TEST_F(ListTestClass, iterators_construct) {
	sList::const_iterator	sc1 = sEmptyList.begin();
	sList::const_iterator	sc2(sc1);
	sList::iterator			s3 = sEmptyList.begin();
	sList::iterator			s4(s3);

	sc2 = s4;
//	s4 = sc2;

	mList::const_iterator	mc1 = mEmptyList.begin();
	mList::const_iterator	mc2(mc1);
	mList::iterator			m3 = mEmptyList.begin();
	mList::iterator			m4(m3);

//	mList::iterator			m5(mc1);	// FALSE
	mList::const_iterator	m6(m4);

	mc2 = m4;
//	m4 = mc2;							// FALSE


	mList::const_iterator	const_Iterator = mEmptyList.begin();
	mList::iterator			iterator = mEmptyList.begin();

	const_Iterator = iterator;			// TRUE
	const_Iterator = const_Iterator;	// TRUE
	iterator = iterator;				// TRUE

/*
	int intValue = 1;
	const_Iterator = nullptr;			// FALSE
	iterator = nullptr;					// FALSE
	iterator = const_Iterator;			// FALSE
	iterator = intValue;				// FALSE
	const_Iterator = intValue;			// FALSE
	iterator = sEmptyList.begin();		// FALSE
	const_Iterator = sEmptyList.begin();// FALSE
*/

	sList::iterator			s = sEmptyList.begin();
	sList::const_iterator	sConst = sEmptyList.begin();
	mList::iterator			m = mEmptyList.begin();
	mList::const_iterator	mConst = mEmptyList.begin();
	ASSERT_EQ(s == sConst, m == mConst);
	ASSERT_EQ(sConst == s, mConst == m);
	ASSERT_EQ(sConst != s, mConst != m);
	ASSERT_EQ(s != sConst, m != mConst);
}

TEST_F(ListTestClass, const_iterators_empty) {
	sList::const_iterator	sIt = sEmptyList.begin();
	sList::const_iterator	sIte = sEmptyList.end();

	mList::const_iterator	mIt = mEmptyList.end();
	mList::const_iterator	mIte = mEmptyList.end();

	ASSERT_EQ(*sIt == *sIte, *mIt == *mIte);
	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sList::const_iterator	s3(sIt);
	mList::const_iterator	m3(mIt);
	sList::const_iterator	s4;
	mList::const_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(ListTestClass, iterators_empty) {
	sList::iterator	sIt = sEmptyList.begin();
	sList::iterator	sIte = sEmptyList.end();

	mList::iterator	mIt		= mEmptyList.begin();
	mList::iterator	mIte	= mEmptyList.end();

	ASSERT_EQ(*sIt == *sIte, *mIt == *mIte);
	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sList::iterator	s3(sIt);
	sList::iterator	s4;
	s4 = sIte;

	mList::iterator	m3(mIt);
	mList::iterator	m4;
	m4 = mIte;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(ListTestClass, const_iterator_bi) {
	sList::const_iterator			sIt = sTenList.begin();
	sList::const_iterator			sIte = sTenList.end();
	mList::const_iterator			mIt = mTenList.begin();
	mList::const_iterator			mIte = mTenList.end();

	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sList::const_iterator			s3(sIt);
	sList::const_iterator			s4;
	s4 = sIt;
	mList::const_iterator			m3(mIt);
	mList::const_iterator			m4;
	m4 = mIt;

	++sIt; ++mIt;
	--sIt; --mIt;
	ASSERT_EQ(sIt == s4, mIt == m4);
	ASSERT_EQ(sIt == s3, mIt == m3);

	s3 = sIt++; m3 = mIt++;
	s4 = sIt--; m4 = mIt--;
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*s4, *m4);

	int counter = 0;
	while (mIt != mIte) {
//		ASSERT_EQ(*sIt, counter);
		ASSERT_EQ(*sIt, *mIt);
		++counter;
		++sIt; ++mIt;
	}
	ASSERT_EQ(counter, 10);
}

TEST_F(ListTestClass, iterator_bi) {
	sList::iterator			sIt = sTenList.begin();
	sList::iterator			sIte = sTenList.end();
	mList::iterator			mIt = mTenList.begin();
	mList::iterator			mIte = mTenList.end();
	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sList::iterator			s3(sIt);
	sList::iterator			s4;
	s4 = sIt;
	mList::iterator			m3(mIt);
	mList::iterator			m4;
	m4 = mIt;

	++sIt; ++mIt;
	--sIt; --mIt;
	ASSERT_EQ(sIt == s4, mIt == m4);
	ASSERT_EQ(sIt == s3, mIt == m3);
	ASSERT_EQ(sIt.operator->() == s3.operator->(),
			  mIt.operator->() == m3.operator->());

	s3 = sIt++; m3 = mIt++;
	s4 = sIt--; m4 = mIt--;
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*s4, *m4);

	int counter = 0;
	while (mIt != mIte) {
		ASSERT_EQ(*sIt, *mIt);
		++counter;
		++sIt; ++mIt;
	}
	ASSERT_EQ(counter, 10);

	sIt = sTenList.begin();
	sIte = sTenList.end();
	mIt = mTenList.begin();
	mIte = mTenList.end();
	while (sIt != sIte) {
		*sIt = INT_VALUE; *mIt = INT_VALUE;
		++sIt; ++mIt;
	}
	sList	s5(10, INT_VALUE);
	assertListEQ(s5, mTenList);
}

TEST_F(ListTestClass, const_iterator_reverse_empty) {
	sList::const_reverse_iterator	sRit = sEmptyList.rbegin();
	sList::const_reverse_iterator	sRite = sEmptyList.rend();
	mList::const_reverse_iterator	mRit = mEmptyList.rbegin();
	mList::const_reverse_iterator	mRite = mEmptyList.rend();

	ASSERT_EQ(*sRit == *sRite, *mRit == *mRite);
	ASSERT_EQ(sRit == sRite, mRit == mRite);
	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sList::const_reverse_iterator	s3(sRit);
	sList::const_reverse_iterator	s4;
	s4 = sRite;
	mList::const_reverse_iterator	m3(mRit);
	mList::const_reverse_iterator	m4;
	m4 = mRite;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(ListTestClass, iterator_reverse_empty) {
	sList::reverse_iterator	sRit = sEmptyList.rbegin();
	sList::reverse_iterator	sRite = sEmptyList.rend();
	mList::reverse_iterator	mRit = mEmptyList.rbegin();
	mList::reverse_iterator	mRite = mEmptyList.rend();

	ASSERT_EQ(*sRit == *sRite, *mRit == *mRite);
	ASSERT_EQ(sRit == sRite, mRit == mRite);
	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sList::reverse_iterator	s3(sRit);
	sList::reverse_iterator	s4;
	s4 = sRite;
	mList::reverse_iterator	m3(mRit);
	mList::reverse_iterator	m4;
	m4 = mRite;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(ListTestClass, const_iterator_reverse_bi) {
	sList::const_reverse_iterator	sRit = sTenList.rbegin();
	sList::const_reverse_iterator	sRite = sTenList.rend();
	mList::const_reverse_iterator	mRit = mTenList.rbegin();
	mList::const_reverse_iterator	mRite = mTenList.rend();

	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sList::const_reverse_iterator	s3(sRit);
	sList::const_reverse_iterator	s4;
	s4 = sRit;
	mList::const_reverse_iterator	m3(mRit);
	mList::const_reverse_iterator	m4;
	m4 = mRit;

	++sRit; ++mRit;
	--sRit; --mRit;
	ASSERT_EQ(sRit == s4, mRit == m4);
	ASSERT_EQ(sRit == s3, mRit == m3);

	s3 = sRit++; m3 = mRit++;
	s4 = sRit--; m4 = mRit--;
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*s4, *m4);

	int counter = 9;
	while (mRit != mRite) {
//		ASSERT_EQ(*sRit, counter);
		ASSERT_EQ(*sRit, *mRit);
		--counter;
		++sRit; ++mRit;
	}
	ASSERT_EQ(counter, -1);
}

TEST_F(ListTestClass, iterator_reverse_bi) {
	sList::reverse_iterator			sRit = sTenList.rbegin();
	sList::reverse_iterator			sRite = sTenList.rend();
	mList::reverse_iterator			mRit = mTenList.rbegin();
	mList::reverse_iterator			mRite = mTenList.rend();

	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sList::reverse_iterator			s3(sRit);
	sList::reverse_iterator			s4;
	s4 = sRit;
	mList::reverse_iterator			m3(mRit);
	mList::reverse_iterator			m4;
	m4 = mRit;

	++sRit; ++mRit;
	--sRit; --mRit;
	ASSERT_EQ(sRit == s4, mRit == m4);
	ASSERT_EQ(sRit == s3, mRit == m3);

	s3 = sRit++; m3 = mRit++;
	s4 = sRit--; m4 = mRit--;
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*s4, *m4);

	int counter = 9;
	while (mRit != mRite) {
		ASSERT_EQ(*sRit, *mRit);
		--counter;
		++sRit; ++mRit;
	}
	ASSERT_EQ(counter, -1);

	sRit = sTenList.rbegin();
	sRite = sTenList.rend();
	mRit = mTenList.rbegin();
	mRite = mTenList.rend();
	while (mRit != mRite) {
		*sRit = INT_VALUE; *mRit = INT_VALUE;
		++sRit; ++mRit;
	}
	sList	s5(10, INT_VALUE);
	assertListEQ(s5, mTenList);
}

TEST_F(ListTestClass, const_iterators_end) {
	sList::const_iterator			s1 = sTenList.begin();
	sList::const_reverse_iterator	sr2 = sTenList.rend();
	mList::const_iterator			m1 = mTenList.begin();
	mList::const_reverse_iterator	mr2 = mTenList.rend();

	--sr2; --mr2;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);

	s1 = sTenList.end();
	sr2 = sTenList.rbegin();
	m1 = mTenList.end();
	mr2 = mTenList.rbegin();
	--s1; --m1;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);
}

TEST_F(ListTestClass, iterators_end) {
	sList::iterator			s1 = sTenList.begin();
	sList::reverse_iterator	sr2 = sTenList.rend();
	mList::iterator			m1 = mTenList.begin();
	mList::reverse_iterator	mr2 = mTenList.rend();

	--sr2; --mr2;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);

	s1 = sTenList.end();
	sr2 = sTenList.rbegin();
	m1 = mTenList.end();
	mr2 = mTenList.rbegin();
	--s1; --m1;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);
}

TEST_F(ListTestClass, empty) {
	ASSERT_EQ(sEmptyList.empty(), mEmptyList.empty());
	ASSERT_EQ(sTenList.empty(), mTenList.empty());
}

TEST_F(ListTestClass, size) {
	EXPECT_EQ(sEmptyList.size(), mEmptyList.size());
	EXPECT_EQ(sTenList.size(), mTenList.size());
	EXPECT_EQ(sLongList.size(), mLongList.size());
}

TEST_F(ListTestClass, max_size) {
	const int		nPointersInStructure = 3;
	const int		structureSize = nPointersInStructure * sizeof(void *);
	const size_t	maxSize = static_cast<size_t>(-1) / structureSize;

	EXPECT_EQ(sEmptyList.max_size(), mEmptyList.max_size());
	EXPECT_EQ(sTenList.max_size(), mTenList.max_size());

	std::list<float>	s1(3);
	ft::list<float>		m1(3);
	EXPECT_EQ(s1.max_size(), maxSize);
	EXPECT_EQ(m1.max_size(), maxSize);
}

TEST_F(ListTestClass, front) {
	ASSERT_EQ(sTenList.front(), mTenList.front());

	sTenList.front() = INT_VALUE;
	mTenList.front() = INT_VALUE;
	ASSERT_EQ(sTenList.front(), mTenList.front());

//	ASSERT_EQ(sEmptyList.front(), int());
//
//	sEmptyList.front() = INT_VALUE;
//	ASSERT_EQ(sEmptyList.front(), INT_VALUE);
}

TEST_F(ListTestClass, back) {
	ASSERT_EQ(sTenList.back(), mTenList.back());

	sTenList.back() = INT_VALUE;
	mTenList.back() = INT_VALUE;
	ASSERT_EQ(sTenList.back(), mTenList.back());

//	ASSERT_EQ(sEmptyList.back(), int());
//
//	sEmptyList.back() = INT_VALUE;
//	ASSERT_EQ(sEmptyList.back(), INT_VALUE);
}

TEST_F(ListTestClass, assign) {
	sEmptyList.assign(SIZE_LITTLE, INT_VALUE);
	mEmptyList.assign(SIZE_LITTLE, INT_VALUE);
//	sList		s1(SIZE_LITTLE, INT_VALUE);
//	assertListEQ(s1, sEmptyList);
	assertListEQ(sEmptyList, mEmptyList);

	sEmptyList.assign(0, INT_VALUE);
	mEmptyList.assign(0, INT_VALUE);
	ASSERT_EQ(sEmptyList.empty(), mEmptyList.empty());

	sEmptyList.assign(++sTenList.begin(), sTenList.end());
	mEmptyList.assign(++sTenList.begin(), sTenList.end());
	ASSERT_EQ(sEmptyList.size(), mEmptyList.size());
	assertListEQ(sEmptyList, mEmptyList);

	sEmptyList.assign(sTenList.end(), sTenList.end());
	mEmptyList.assign(sTenList.end(), sTenList.end());
	ASSERT_EQ(sEmptyList.empty(), mEmptyList.empty());
}

TEST_F(ListTestClass, push_front) {
	sList			s1(sEmptyList);
	mList			m1(mEmptyList);

	s1.push_front(INT_VALUE);
	m1.push_front(INT_VALUE);
	ASSERT_EQ(s1.size(), m1.size());
	ASSERT_EQ(s1.front(), m1.front());

	s1.push_front(INT_VALUE - 1);
	m1.push_front(INT_VALUE - 1);
	ASSERT_EQ(s1.size(), m1.size());
	ASSERT_EQ(s1.front(), m1.front());
	ASSERT_EQ(s1.back(), m1.back());

	sList			s2(sEmptyList);
	mList			m2(mEmptyList);
	for (int i = 9; i > -1; --i) {
		s2.push_front(i);
		m2.push_front(i);
	}
	assertListEQ(s2, m2);

	mList					m3(mTenList);
	mList::const_iterator	mIt = m3.begin();
	mList::const_iterator	mIte = m3.end();
	m3.push_front(INT_VALUE);
	assertListEQFromListAndIterators(sTenList, mIt, mIte);
	mIt = m3.begin();
	assertListEQFromListAndIterators(sTenList, ++mIt, mIte);
}

TEST_F(ListTestClass, pop_front) {
	sList		s1(sTenList);
	mList		m1(mTenList);

	s1.pop_front();
	m1.pop_front();
	ASSERT_EQ(s1.size(), m1.size());
	assertListEQ(s1, m1);

	for (int i = 1; i < 10; ++i) {
		ASSERT_EQ(s1.front(), m1.front());
		s1.pop_front(); m1.pop_front();
	}
	assertListEQ(s1, m1);

//	s1.pop_front();
//	ASSERT_EQ(s1.size(), 0);

	sList					s2(sTenList);
	sList::const_iterator	sIt1 = s2.begin();
	ASSERT_EQ(*sIt1, 0);
	s2.pop_front();
	sList::const_iterator	sIt2 = s2.begin();
	ASSERT_TRUE(sIt1 != sIt2);

	mList					m2(mTenList);
	mList::const_iterator	mIt1 = m2.begin();
	ASSERT_EQ(*mIt1, 0);
	m2.pop_front();
	mList::const_iterator	mIt2 = m2.begin();
	ASSERT_TRUE(mIt1 != mIt2);
}

TEST_F(ListTestClass, push_back) {
	sList	s1(sEmptyList);
	mList	m1(mEmptyList);

	s1.push_back(INT_VALUE);
	m1.push_back(INT_VALUE);
	ASSERT_EQ(s1.size(), m1.size());
	ASSERT_EQ(s1.back(), m1.back());

	s1.push_back(INT_VALUE - 1);
	m1.push_back(INT_VALUE - 1);
	ASSERT_EQ(s1.size(), m1.size());
	ASSERT_EQ(s1.back(), m1.back());
	ASSERT_EQ(s1.front(), m1.front());

	sList	s2(sEmptyList);
	mList	m2(mEmptyList);
	for (int i = 0; i < 10; ++i) {
		s2.push_back(i);
		m2.push_back(i);
	}
	assertListEQ(s2, m2);

	sList::const_iterator	sIt = s2.begin();
	sList::const_iterator	sIte = s2.end();
	mList::const_iterator	mIt = m2.begin();
	mList::const_iterator	mIte = m2.end();

	s2.push_back(INT_VALUE - 3);
	m2.push_back(INT_VALUE - 3);
	ASSERT_EQ(s2.back(), m2.back());
	assertListEQFromListAndIterators(sTenList, mIt, --mIte);
}

TEST_F(ListTestClass, pop_back) {
	sList		s1(sTenList);
	mList		m1(mTenList);

	s1.pop_back();
	m1.pop_back();
	ASSERT_EQ(s1.size(), m1.size());
	assertListEQ(s1, m1);

	for (int i = 8; i > -1; --i) {
		ASSERT_EQ(s1.back(), m1.back());
		s1.pop_back();
		m1.pop_back();
	}
	assertListEQ(s1, m1);

//	s1.pop_back();
//	ASSERT_EQ(s1.size(), 0);

	sList					s2(sTenList);
	sList::const_iterator	sIte = s2.end();
	s2.pop_back();
	mList					m2(mTenList);
	mList::const_iterator	mIte = m2.end();
	m2.pop_back();
	assertListEQFromIterators(s2.begin(), sIte, m2.begin(), mIte);
}

void printList(sList list) {
	sList::const_iterator	sIt = list.begin();
	sList::const_iterator	ite = list.end();

	std::cout << "List = ";
	while (sIt != ite) {
		std::cout << *sIt++ << ", ";
	}
	std::cout << ";" << std::endl;
}

TEST_F(ListTestClass, insert) {
	sList		s1(sEmptyList);
	mList		m1(mEmptyList);

	ASSERT_EQ(*s1.insert(s1.begin(), INT_VALUE), *m1.insert(m1.begin(), INT_VALUE));
	ASSERT_EQ(s1.size(), m1.size());
	ASSERT_EQ(s1.front(), m1.front());
	s1.pop_front(); m1.pop_front();

	ASSERT_EQ(*s1.insert(s1.end(), INT_VALUE - 1), *m1.insert(m1.end(), INT_VALUE - 1));
	ASSERT_EQ(s1.size(), m1.size());
	ASSERT_EQ(s1.front(), m1.front());
	s1.pop_front();
	m1.pop_front();

	s1.push_front(0); m1.push_front(0);
	s1.push_back(9); m1.push_back(9);
	s1.insert(++s1.begin(), ++sTenList.begin(), --sTenList.end());
	m1.insert(++m1.begin(), ++sTenList.begin(), --sTenList.end());
	assertListEQ(s1, m1);

	sList		s2(sEmptyList);
	mList		m2(mEmptyList);
	s2.push_front(INT_VALUE - 2); m2.push_front(INT_VALUE - 2);
	s2.insert(s2.begin(), SIZE_LONG, INT_VALUE - 2);
	m2.insert(m2.begin(), SIZE_LONG, INT_VALUE - 2);
	assertListEQ(s2, m2);

	sList				s3(sTenList);
	sList::iterator		sIt = s3.begin();
	mList				m3(mTenList);
	mList::iterator		mIt = m3.begin();

	++sIt, ++sIt, ++sIt;
	++mIt, ++mIt, ++mIt;
	s3.insert(sIt, SIZE_LITTLE, INT_VALUE);
	m3.insert(mIt, SIZE_LITTLE, INT_VALUE);
	ASSERT_EQ(*sIt, *mIt);
	sIt = s3.begin();
	mIt = m3.begin();
	bool flag = true;
	for (int i = 0; i < 10; ++i) {
		if (i == 3 && flag) {
			for (int j = 0; j < SIZE_LITTLE; ++j) {
				EXPECT_EQ(*sIt++, *mIt++);
			}
			--i;
			flag = false;
			continue;
		}
		EXPECT_EQ(*sIt++, *mIt++);
	}
}

TEST_F(ListTestClass, erase) {
//	sEmptyList.erase(sEmptyList.begin());
//	ASSERT_TRUE(sEmptyList.empty());

	sEmptyList.push_front(INT_VALUE);
	mEmptyList.push_front(INT_VALUE);
	sEmptyList.erase(sEmptyList.begin());
	mEmptyList.erase(mEmptyList.begin());
	ASSERT_EQ(sEmptyList.empty(), mEmptyList.empty());

	sList					s1(sTenList);
	sList::const_iterator	sIt = s1.begin();
	s1.push_back(INT_VALUE);
	mList					m1(mTenList);
	mList::const_iterator	mIt = m1.begin();
	m1.push_back(INT_VALUE);
	ASSERT_EQ(s1.erase(--s1.end()) == s1.end(), m1.erase(--m1.end()) == m1.end());
	assertListEQFromIterators(sIt, s1.end(), mIt, m1.end());

	sList			s2(sTenList);
	sList::iterator	sIt2 = s2.begin();
	mList			m2(mTenList);
	mList::iterator	mIt2 = m2.begin();
	++sIt2, ++sIt2, ++sIt2;
	++mIt2, ++mIt2, ++mIt2;

	s2.insert(sIt2, SIZE_LITTLE, INT_VALUE);
	m2.insert(mIt2, SIZE_LITTLE, INT_VALUE);
	sIt2 = s2.begin();
	mIt2 = m2.begin();
	++sIt2, ++sIt2, ++sIt2;
	++mIt2, ++mIt2, ++mIt2;
	sList::iterator	sIte2(sIt2);
	mList::iterator	mIte2(mIt2);

	for (int i = 0; i < SIZE_LITTLE; ++i) {
		++sIte2; ++mIte2;
	}
	ASSERT_EQ(*s2.erase(sIt2, sIte2), *m2.erase(mIt2, mIte2));
	ASSERT_EQ(s2.size(), m2.size());
	assertListEQ(s2, m2);
}

/*
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

	sList::const_iterator	sIt = s1.begin();
	sList::const_iterator	ite = s1.end();
	for (int i = 0; i < SIZE_LITTLE; ++i) {
		ASSERT_EQ(*sIt++, i);
	}
	for (int i = 0; i < SIZE_LONG - SIZE_LITTLE; ++i) {
		ASSERT_EQ(*sIt++, INT_VALUE - 1);
	}
	ASSERT_TRUE(sIt == ite);
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
	sList::const_iterator	sIt = s4.begin();
	ASSERT_EQ(*sIt++, 1);
	assertListEQFromListAndIterators(sRandomList, sIt, s4.end());
	ASSERT_EQ(s3.size(), sTenList.size() - 1);

	sList		s5(sTenList);
	sList		s6(sRandomList);

	s6.splice(++s6.begin(), s5, s5.begin(), --s5.end());
	sIt = s6.begin();
	ASSERT_EQ(*sIt++, sRandomList.front());
	for (int i = 0; i < 9; ++i) {
		ASSERT_EQ(*sIt++, i);
	}
	assertListEQFromIterators(++sRandomList.begin(), sRandomList.end(), sIt, s6.end());
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

	sList::const_iterator	sIt = s2.begin();
	for (int i = 1; i < 10; ++i) {
		ASSERT_EQ(*sIt++, i);
	}
	sIt = s3.begin();
	for (int i = 0; i < 10; ++i) {
		if (i == 5)
			continue;
		ASSERT_EQ(*sIt++, i);
	}
	sIt = s4.begin();
	for (int i = 0; i < 9; ++i) {
		ASSERT_EQ(*sIt++, i);
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
	sList::const_iterator		sIt = s1.begin();
	for (int i = 1; i < 10; i += 2) {
		ASSERT_EQ(*sIt++, i);
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

TEST_F(ListTestClass, non_member_operators) {
	sList	s1(sEmptyList);

	ASSERT_TRUE(s1 == sEmptyList);
	ASSERT_TRUE(s1 < sTenList);
	ASSERT_FALSE(s1 > sTenList);
	ASSERT_TRUE(s1 != sTenList);

	sList	s2(sTenList);
	ASSERT_TRUE(s2 <= sTenList);
	ASSERT_TRUE(s2 >= sTenList);
}

TEST_F(ListTestClass, non_member_swap) {
	sList		s1(sEmptyList);
	sList		s2(sTenList);

	std::swap(s1, s2);
	assertListEQ(sEmptyList, s2);
	assertListEQ(sTenList, s1);

	sList		s3(sRandomList);
	sList		s4(sTenList);

	std::swap(s3, s4);
	assertListEQ(sTenList, s3);
	assertListEQ(sRandomList, s4);
}
*/
#undef DEBUG
