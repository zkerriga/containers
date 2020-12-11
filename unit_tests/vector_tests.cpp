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

/*void assertListEQFromIterators(sVec::const_iterator sIt, sVec::const_iterator sIte,
							   mVec::const_iterator mIt, mVec::const_iterator mIte) {
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}*/
/*void assertListEQFromListAndIterators(sVec stdList,
									  mVec::const_iterator mIt, mVec::const_iterator mIte) {
	sVec::const_iterator	sIt = stdList.begin();
	sVec::const_iterator	sIte = stdList.end();

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

TEST(vector, iterator_types) {
	sVec::iterator::value_type					s1;
	sVec::iterator::difference_type				s2;
	sVec::iterator::pointer						s3;
	sVec::iterator::iterator_category			s4;

	mVec::iterator::value_type					m1;
	mVec::iterator::difference_type				m2;
	mVec::iterator::pointer						m3;
	mVec::iterator::iterator_category			m4;
}
TEST_F(VecTest, iterators_construct) {
	mVec::const_iterator	mc1 = mEmpty.begin();
	mVec::const_iterator	mc2(mc1);
	mVec::iterator			m3 = mEmpty.begin();
	mVec::iterator			m4(m3);

//	mVec::iterator			m5(mc1);	// FALSE
	mVec::const_iterator	m6(m4);

	mc2 = m4;
//	m4 = mc2;							// FALSE

	mVec::const_iterator	const_Iterator = mEmpty.begin();
	mVec::iterator			iterator = mEmpty.begin();

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
	iterator = sEmpty.begin();			// FALSE
	const_Iterator = sEmpty.begin();	// FALSE
*/
}

/*
TEST_F(VecTest, const_iterators_empty) {
	sVec::const_iterator	sIt = sEmpty.begin();
	sVec::const_iterator	sIte = sEmpty.end();

	mVec::const_iterator	mIt = mEmpty.end();
	mVec::const_iterator	mIte = mEmpty.end();

	ASSERT_EQ(*sIt == *sIte, *mIt == *mIte);
	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sVec::const_iterator	s3(sIt);
	mVec::const_iterator	m3(mIt);
	sVec::const_iterator	s4;
	mVec::const_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, iterators_empty) {
	sVec::iterator	sIt = sEmpty.begin();
	sVec::iterator	sIte = sEmpty.end();

	mVec::iterator	mIt		= mEmpty.begin();
	mVec::iterator	mIte	= mEmpty.end();

	ASSERT_EQ(*sIt == *sIte, *mIt == *mIte);
	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sVec::iterator	s3(sIt);
	sVec::iterator	s4;
	s4 = sIte;

	mVec::iterator	m3(mIt);
	mVec::iterator	m4;
	m4 = mIte;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, const_iterator_bi) {
	sVec::const_iterator			sIt = sTenList.begin();
	sVec::const_iterator			sIte = sTenList.end();
	mVec::const_iterator			mIt = mTenList.begin();
	mVec::const_iterator			mIte = mTenList.end();

	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sVec::const_iterator			s3(sIt);
	sVec::const_iterator			s4;
	s4 = sIt;
	mVec::const_iterator			m3(mIt);
	mVec::const_iterator			m4;
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

TEST_F(VecTest, iterator_bi) {
	sVec::iterator			sIt = sTenList.begin();
	sVec::iterator			sIte = sTenList.end();
	mVec::iterator			mIt = mTenList.begin();
	mVec::iterator			mIte = mTenList.end();
	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sVec::iterator			s3(sIt);
	sVec::iterator			s4;
	s4 = sIt;
	mVec::iterator			m3(mIt);
	mVec::iterator			m4;
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
	sVec	s5(10, INT_VALUE);
	assertListEQ(s5, mTenList);
}

TEST_F(VecTest, const_iterator_reverse_empty) {
	sVec::const_reverse_iterator	sRit = sEmpty.rbegin();
	sVec::const_reverse_iterator	sRite = sEmpty.rend();
	mVec::const_reverse_iterator	mRit = mEmpty.rbegin();
	mVec::const_reverse_iterator	mRite = mEmpty.rend();

	ASSERT_EQ(*sRit == *sRite, *mRit == *mRite);
	ASSERT_EQ(sRit == sRite, mRit == mRite);
	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sVec::const_reverse_iterator	s3(sRit);
	sVec::const_reverse_iterator	s4;
	s4 = sRite;
	mVec::const_reverse_iterator	m3(mRit);
	mVec::const_reverse_iterator	m4;
	m4 = mRite;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, iterator_reverse_empty) {
	sVec::reverse_iterator	sRit = sEmpty.rbegin();
	sVec::reverse_iterator	sRite = sEmpty.rend();
	mVec::reverse_iterator	mRit = mEmpty.rbegin();
	mVec::reverse_iterator	mRite = mEmpty.rend();

	ASSERT_EQ(*sRit == *sRite, *mRit == *mRite);
	ASSERT_EQ(sRit == sRite, mRit == mRite);
	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sVec::reverse_iterator	s3(sRit);
	sVec::reverse_iterator	s4;
	s4 = sRite;
	mVec::reverse_iterator	m3(mRit);
	mVec::reverse_iterator	m4;
	m4 = mRite;

	ASSERT_EQ(*s3 == *s4, *m3 == *m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, const_iterator_reverse_bi) {
	sVec::const_reverse_iterator	sRit = sTenList.rbegin();
	sVec::const_reverse_iterator	sRite = sTenList.rend();
	mVec::const_reverse_iterator	mRit = mTenList.rbegin();
	mVec::const_reverse_iterator	mRite = mTenList.rend();

	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sVec::const_reverse_iterator	s3(sRit);
	sVec::const_reverse_iterator	s4;
	s4 = sRit;
	mVec::const_reverse_iterator	m3(mRit);
	mVec::const_reverse_iterator	m4;
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

TEST_F(VecTest, iterator_reverse_bi) {
	sVec::reverse_iterator			sRit = sTenList.rbegin();
	sVec::reverse_iterator			sRite = sTenList.rend();
	mVec::reverse_iterator			mRit = mTenList.rbegin();
	mVec::reverse_iterator			mRite = mTenList.rend();

	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sVec::reverse_iterator			s3(sRit);
	sVec::reverse_iterator			s4;
	s4 = sRit;
	mVec::reverse_iterator			m3(mRit);
	mVec::reverse_iterator			m4;
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
	sVec	s5(10, INT_VALUE);
	assertListEQ(s5, mTenList);
}

TEST_F(VecTest, const_iterators_end) {
	sVec::const_iterator			s1 = sTenList.begin();
	sVec::const_reverse_iterator	sr2 = sTenList.rend();
	mVec::const_iterator			m1 = mTenList.begin();
	mVec::const_reverse_iterator	mr2 = mTenList.rend();

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

TEST_F(VecTest, iterators_end) {
	sVec::iterator			s1 = sTenList.begin();
	sVec::reverse_iterator	sr2 = sTenList.rend();
	mVec::iterator			m1 = mTenList.begin();
	mVec::reverse_iterator	mr2 = mTenList.rend();

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
}*/

#undef DEBUG
