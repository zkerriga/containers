#include "gtest/gtest.h"
#include <vector>
#include <iterator>
#include <limits>
#include <iostream>

#include "vector.hpp"
#include "Any.hpp"

#define ANY_INT Any(1232349)
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

void assertVecEQ(const sVec & sV, const mVec & mV) {
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
}

void assertVecEQFromIterators(sVec::const_iterator sIt,
							  sVec::const_iterator sIte,
							  mVec::const_iterator mIt,
							  mVec::const_iterator mIte) {
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}

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
	assertVecEQ(sEmpty, mEmpty);
	assertVecEQ(sTen, mTen);
	assertVecEQ(sRandom, mRandom);
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

TEST_F(VecTest, const_iterators_empty) {
	sVec::const_iterator	sIt		= sEmpty.begin();
	sVec::const_iterator	sIte	= sEmpty.end();
	mVec::const_iterator	mIt		= mEmpty.end();
	mVec::const_iterator	mIte	= mEmpty.end();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sVec::const_iterator	s3(sIt);
	mVec::const_iterator	m3(mIt);
	sVec::const_iterator	s4;
	mVec::const_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, iterators_empty) {
	sVec::iterator	sIt		= sEmpty.begin();
	sVec::iterator	sIte	= sEmpty.end();
	mVec::iterator	mIt		= mEmpty.end();
	mVec::iterator	mIte	= mEmpty.end();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sVec::iterator	s3(sIt);
	mVec::iterator	m3(mIt);
	sVec::iterator	s4;
	mVec::iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, const_iterator_bi) {
	sVec::const_iterator			sIt		= sTen.begin();
	sVec::const_iterator			sIte	= sTen.end();
	mVec::const_iterator			mIt		= mTen.begin();
	mVec::const_iterator			mIte	= mTen.end();

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
		ASSERT_EQ(*sIt, *mIt);
		++counter;
		++sIt; ++mIt;
	}
	ASSERT_EQ(counter, 10);
}

TEST_F(VecTest, iterator_bi) {
	sVec::iterator			sIt = sTen.begin();
	sVec::iterator			sIte = sTen.end();
	mVec::iterator			mIt = mTen.begin();
	mVec::iterator			mIte = mTen.end();
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

	sIt = sTen.begin();
	sIte = sTen.end();
	mIt = mTen.begin();
	mIte = mTen.end();
	while (sIt != sIte) {
		*sIt = ANY_INT; *mIt = ANY_INT;
		++sIt; ++mIt;
	}
	sVec	s5(10, ANY_INT);
	assertVecEQ(s5, mTen);
}

TEST_F(VecTest, iterator_random_access) {
	sVec::iterator			s1		= sTen.begin();
	mVec::iterator			m1		= mTen.begin();

	s1 = (s1 + 2);		m1 = (m1 + 2);
	s1 = (2 + s1);		m1 = (2 + m1);
	s1 = (s1 - 1);		m1 = (m1 - 1);
//	s1 = (1 - s1);		m1 = (1 - m1);

	ASSERT_EQ(*s1, *m1);
	ASSERT_EQ(s1[0], m1[0]);
	ASSERT_EQ(s1[1], m1[1]);
	ASSERT_EQ(s1[3], m1[3]);
	ASSERT_EQ(s1[-1], m1[-1]);
	ASSERT_EQ(s1->getInt(), m1->getInt());

	s1 += 2;		m1 += 2;
	s1 -= 1;		m1 -= 1;
	ASSERT_EQ(*s1, *m1);
}

TEST_F(VecTest, const_iterator_random_access) {
	sVec::const_iterator	s1		= sTen.begin();
	mVec::const_iterator	m1		= mTen.begin();

	s1 = (s1 + 2);		m1 = (m1 + 2);
	s1 = (2 + s1);		m1 = (2 + m1);
	s1 = (s1 - 1);		m1 = (m1 - 1);
//	s1 = (1 - s1);		m1 = (1 - m1);

	ASSERT_EQ(*s1, *m1);
	ASSERT_EQ(s1[0], m1[0]);
	ASSERT_EQ(s1[1], m1[1]);
	ASSERT_EQ(s1[3], m1[3]);
	ASSERT_EQ(s1[-1], m1[-1]);
	ASSERT_EQ(s1->getInt(), m1->getInt());

	s1 += 2;		m1 += 2;
	s1 -= 1;		m1 -= 1;
	ASSERT_EQ(*s1, *m1);
}

TEST_F(VecTest, reverse_iterators_empty) {
	sVec::reverse_iterator	sIt		= sEmpty.rbegin();
	sVec::reverse_iterator	sIte	= sEmpty.rend();
	mVec::reverse_iterator	mIt		= mEmpty.rend();
	mVec::reverse_iterator	mIte	= mEmpty.rend();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sVec::reverse_iterator	s3(sIt);
	mVec::reverse_iterator	m3(mIt);
	sVec::reverse_iterator	s4;
	mVec::reverse_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, const_reverse_iterators_empty) {
	sVec::const_reverse_iterator	sIt		= sEmpty.rbegin();
	sVec::const_reverse_iterator	sIte	= sEmpty.rend();
	mVec::const_reverse_iterator	mIt		= mEmpty.rend();
	mVec::const_reverse_iterator	mIte	= mEmpty.rend();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sVec::const_reverse_iterator	s3(sIt);
	mVec::const_reverse_iterator	m3(mIt);
	sVec::const_reverse_iterator	s4;
	mVec::const_reverse_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, const_iterator_reverse_bi) {
	sVec::const_reverse_iterator	sRit	= sTen.rbegin();
	sVec::const_reverse_iterator	sRite	= sTen.rend();
	mVec::const_reverse_iterator	mRit	= mTen.rbegin();
	mVec::const_reverse_iterator	mRite	= mTen.rend();

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

	int counter = 10;
	while (mRit != mRite) {
		ASSERT_EQ(*sRit, *mRit);
		--counter;
		++sRit; ++mRit;
	}
	ASSERT_EQ(counter, 0);
}

TEST_F(VecTest, iterator_reverse_bi) {
	sVec::reverse_iterator	sRit	= sTen.rbegin();
	sVec::reverse_iterator	sRite	= sTen.rend();
	mVec::reverse_iterator	mRit	= mTen.rbegin();
	mVec::reverse_iterator	mRite	= mTen.rend();

	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sVec::reverse_iterator	s3(sRit);
	sVec::reverse_iterator	s4;
	s4 = sRit;
	mVec::reverse_iterator	m3(mRit);
	mVec::reverse_iterator	m4;
	m4 = mRit;

	++sRit; ++mRit;
	--sRit; --mRit;
	ASSERT_EQ(sRit == s4, mRit == m4);
	ASSERT_EQ(sRit == s3, mRit == m3);

	s3 = sRit++; m3 = mRit++;
	s4 = sRit--; m4 = mRit--;
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*s4, *m4);

	int counter = 10;
	while (mRit != mRite) {
		ASSERT_EQ(*sRit, *mRit);
		--counter;
		++sRit; ++mRit;
	}
	ASSERT_EQ(counter, 0);
}

TEST_F(VecTest, const_iterators_end) {
	sVec::const_iterator			s1	= sTen.begin();
	sVec::const_reverse_iterator	sr2	= sTen.rend();
	mVec::const_iterator			m1	= mTen.begin();
	mVec::const_reverse_iterator	mr2	= mTen.rend();

	--sr2; --mr2;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);

	s1 = sTen.end();
	sr2 = sTen.rbegin();
	m1 = mTen.end();
	mr2 = mTen.rbegin();
	--s1; --m1;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);
}

TEST_F(VecTest, reverse_iterator_random_access) {
	sVec::reverse_iterator		s1	= sTen.rbegin();
	mVec::reverse_iterator		m1	= mTen.rbegin();

	s1 = (s1 + 2);		m1 = (m1 + 2);
	s1 = (2 + s1);		m1 = (2 + m1);
	s1 = (s1 - 1);		m1 = (m1 - 1);
//	s1 = (1 - s1);		m1 = (1 - m1);

	ASSERT_EQ(*s1, *m1);
	ASSERT_EQ(s1[0], m1[0]);
	ASSERT_EQ(s1[1], m1[1]);
	ASSERT_EQ(s1[3], m1[3]);
	ASSERT_EQ(s1[-1], m1[-1]);
	ASSERT_EQ(s1->getInt(), m1->getInt());

	s1 += 2;		m1 += 2;
	s1 -= 1;		m1 -= 1;
	ASSERT_EQ(*s1, *m1);
}

TEST_F(VecTest, iterators_end) {
	sVec::iterator			s1 = sTen.begin();
	sVec::reverse_iterator	sr2 = sTen.rend();
	mVec::iterator			m1 = mTen.begin();
	mVec::reverse_iterator	mr2 = mTen.rend();

	--sr2; --mr2;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);

	s1 = sTen.end();
	sr2 = sTen.rbegin();
	m1 = mTen.end();
	mr2 = mTen.rbegin();
	--s1; --m1;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);
}

TEST_F(VecTest, iterators_compare) {
	sVec::const_iterator	sCI	= sTen.begin();
	sVec::iterator			sI	= sTen.begin();
	mVec::const_iterator	mCI	= mTen.begin();
	mVec::iterator			mI	= mTen.begin();

	ASSERT_EQ(sCI == sI, mCI == mI);
	ASSERT_EQ(sCI != sI, mCI != mI);
	ASSERT_EQ(sCI < sI, mCI < mI);
	ASSERT_EQ(sCI > sI, mCI > mI);
	ASSERT_EQ(sCI >= sI, mCI >= mI);
	ASSERT_EQ(sCI <= sI, mCI <= mI);

	ASSERT_EQ(sI == sCI, mI == mCI);
	ASSERT_EQ(sI != sCI, mI != mCI);
	ASSERT_EQ(sI <  sCI, mI <  mCI);
	ASSERT_EQ(sI >  sCI, mI >  mCI);
	ASSERT_EQ(sI >= sCI, mI >= mCI);
	ASSERT_EQ(sI <= sCI, mI <= mCI);
}

TEST_F(VecTest, reverse_iterators_compare) {
	sVec::const_reverse_iterator	sCI	= sTen.rbegin();
	sVec::reverse_iterator			sI	= sTen.rbegin();
	mVec::const_reverse_iterator	mCI	= mTen.rbegin();
	mVec::reverse_iterator			mI	= mTen.rbegin();

	ASSERT_EQ(sCI == sI, mCI == mI);
	ASSERT_EQ(sCI != sI, mCI != mI);
	ASSERT_EQ(sCI < sI, mCI < mI);
	ASSERT_EQ(sCI > sI, mCI > mI);
	ASSERT_EQ(sCI >= sI, mCI >= mI);
	ASSERT_EQ(sCI <= sI, mCI <= mI);

	ASSERT_EQ(sI == sCI, mI == mCI);
	ASSERT_EQ(sI != sCI, mI != mCI);
	ASSERT_EQ(sI <  sCI, mI <  mCI);
	ASSERT_EQ(sI >  sCI, mI >  mCI);
	ASSERT_EQ(sI >= sCI, mI >= mCI);
	ASSERT_EQ(sI <= sCI, mI <= mCI);
}

TEST_F(VecTest, constructors) {
	sVec	s1(0);
	mVec	m1(0);
	assertVecEQ(s1, m1);

	sVec	s2(SIZE_LITTLE);
	mVec	m2(SIZE_LITTLE);
	assertVecEQ(s2, m2);

	sVec	s3(SIZE_LITTLE, ANY_INT);
	mVec	m3(SIZE_LITTLE, ANY_INT);
	assertVecEQ(s3, m3);

	sVec	s4(sTen.begin(), sTen.end());
	mVec	m4(sTen.begin(), sTen.end());
	assertVecEQ(s4, m4);

	sVec	s5(sTen.end(), sTen.end());
	mVec	m5(sTen.end(), sTen.end());
	assertVecEQ(s5, m5);

	sVec	s6(sTen);
	mVec	m6(mTen);
	assertVecEQ(s6, m6);

	s1 = s4;	m1 = m4;
	assertVecEQ(s1, m1);

	s6 = s3;	m6 = m3;
	assertVecEQ(s6, m6);
}

TEST_F(VecTest, max_size) {
	ASSERT_EQ(sEmpty.max_size(), mEmpty.max_size());
	ASSERT_EQ(sTen.max_size(), mTen.max_size());
}

TEST_F(VecTest, resize) {
	sEmpty.resize(0);
	mEmpty.resize(0);
	assertVecEQ(sEmpty, mEmpty);

	sVec	s1(sEmpty);
	mVec	m1(mEmpty);

	s1.resize(SIZE_LITTLE);
	m1.resize(SIZE_LITTLE);
	assertVecEQ(s1, m1);

	s1.resize(SIZE_LITTLE + 1, ANY_INT);
	m1.resize(SIZE_LITTLE + 1, ANY_INT);
	assertVecEQ(s1, m1);

	s1.resize(SIZE_LONG);
	m1.resize(SIZE_LONG);
	assertVecEQ(s1, m1);

	s1.resize(SIZE_LITTLE);
	m1.resize(SIZE_LITTLE);
	assertVecEQ(s1, m1);

	ASSERT_EQ(s1.capacity(), m1.capacity());
}

TEST_F(VecTest, capacity) {
	ASSERT_EQ(sTen.capacity(), mTen.capacity());
	ASSERT_EQ(mRandom.capacity(), mRandom.capacity());

	sTen.push_back(ANY_INT);	mTen.push_back(ANY_INT);
	sTen.push_back(ANY_INT);	mTen.push_back(ANY_INT);
	sTen.push_back(ANY_INT);	mTen.push_back(ANY_INT);
	ASSERT_EQ(sTen.capacity(), mTen.capacity());

	sRandom.push_back(ANY_INT);	mRandom.push_back(ANY_INT);
	sRandom.push_back(ANY_INT);	mRandom.push_back(ANY_INT);
	sRandom.push_back(ANY_INT);	mRandom.push_back(ANY_INT);
	ASSERT_EQ(mRandom.capacity(), mRandom.capacity());
}

TEST_F(VecTest, empty) {
	ASSERT_EQ(sEmpty.empty(), mEmpty.empty());
	ASSERT_EQ(sTen.empty(), mTen.empty());
}

TEST_F(VecTest, operator_access) {
	ASSERT_EQ(sTen[0], mTen[0]);
	ASSERT_EQ(sTen[3], mTen[3]);
	ASSERT_EQ(sTen[9], mTen[9]);

	sVec	s1(sTen);
	mVec	m1(mTen);
	s1[3] = Any();
	m1[3] = Any();
	assertVecEQ(s1, m1);
	s1[0] = Any();
	m1[0] = Any();
	assertVecEQ(s1, m1);
	s1[9] = Any();
	m1[9] = Any();
	assertVecEQ(s1, m1);
}

TEST_F(VecTest, operator_at) {
	ASSERT_EQ(sTen.at(0), mTen.at(0));
	ASSERT_EQ(sTen.at(3), mTen.at(3));
	ASSERT_EQ(sTen.at(9), mTen.at(9));

	sVec	s1(sTen);
	mVec	m1(mTen);
	s1.at(3) = Any();
	m1.at(3) = Any();
	assertVecEQ(s1, m1);
	s1.at(0) = Any();
	m1.at(0) = Any();
	assertVecEQ(s1, m1);
	s1.at(9) = Any();
	m1.at(9) = Any();
	assertVecEQ(s1, m1);

	try {
		m1.at(-1);
		ASSERT_TRUE(false);
	}
	catch (std::out_of_range &) {
		ASSERT_TRUE(true);
	}
	try {
		m1.at(10);
		ASSERT_TRUE(false);
	}
	catch (std::out_of_range &) {
		ASSERT_TRUE(true);
	}
}

TEST_F(VecTest, front) {
	ASSERT_EQ(sTen.front(), mTen.front());
	ASSERT_EQ(sRandom.front(), mRandom.front());

	sTen.resize(SIZE_LITTLE);
	mTen.resize(SIZE_LITTLE);
	ASSERT_EQ(sTen.front(), mTen.front());
}

TEST_F(VecTest, back) {
	ASSERT_EQ(sTen.back(), mTen.back());
	ASSERT_EQ(sRandom.back(), mRandom.back());

	sTen.resize(SIZE_LITTLE);
	mTen.resize(SIZE_LITTLE);
	ASSERT_EQ(sTen.back(), mTen.back());
}

TEST_F(VecTest, assign) {
	sVec		s1(sEmpty);
	mVec		m1(mEmpty);

	s1.assign(sTen.begin(), sTen.end());
	m1.assign(mTen.begin(), mTen.end());
	assertVecEQ(s1, m1);

	s1.assign(SIZE_LONG, ANY_INT);
	m1.assign(SIZE_LONG, ANY_INT);
	assertVecEQ(s1, m1);

	s1.assign(SIZE_LITTLE, Any());
	m1.assign(SIZE_LITTLE, Any());
	assertVecEQ(s1, m1);
}

TEST_F(VecTest, pop_back) {
	sTen.pop_back();
	mTen.pop_back();
	assertVecEQ(sTen, mTen);

	for (size_t i = sRandom.size(); i > 0; --i) {
		sRandom.pop_back();
		mRandom.pop_back();
	}
	assertVecEQ(sRandom, mRandom);
}

template < class Vec >
void printVec(const Vec vec) {
	typename Vec::const_iterator	it	= vec.begin();
	typename Vec::const_iterator	ite	= vec.end();

	std::cout << "Size " << vec.size() << ": ";
	while (it != ite) {
		std::cout << *it++ << ',';
	}
	std::cout << ';' << std::endl;
}

TEST_F(VecTest, iterator_difference) {
	ASSERT_EQ(sEmpty.end() - sEmpty.begin(), mEmpty.end() - mEmpty.begin());
	ASSERT_EQ(sTen.end() - sTen.begin(), mTen.end() - mTen.begin());
	ASSERT_EQ(sTen.end() - sTen.end(), mTen.end() - mTen.end());
	ASSERT_EQ(sTen.begin() - sTen.end(), mTen.begin() - mTen.end());

	ASSERT_EQ(sTen.rend() - sTen.rbegin(), mTen.rend() - mTen.rbegin());
}

TEST_F(VecTest, insert) {
	sVec	s1(sEmpty);
	mVec	m1(mEmpty);

	ASSERT_EQ(*s1.insert(s1.begin(), Any(1)), *m1.insert(m1.begin(), Any(1)));
	ASSERT_EQ(*s1.insert(s1.begin(), Any(2)), *m1.insert(m1.begin(), Any(2)));
	ASSERT_EQ(*s1.insert(s1.begin(), Any(3)), *m1.insert(m1.begin(), Any(3)));
	ASSERT_EQ(*s1.insert(++s1.begin(), Any(4)), *m1.insert(++m1.begin(), Any(4)));
	assertVecEQ(s1, m1);

	s1.insert(s1.begin() + 1, SIZE_LITTLE, ANY_INT);
	m1.insert(m1.begin() + 1, SIZE_LITTLE, ANY_INT);
	assertVecEQ(s1, m1);

	s1.insert(s1.begin(), SIZE_LITTLE, Any());
	m1.insert(m1.begin(), SIZE_LITTLE, Any());
	assertVecEQ(s1, m1);
	s1.insert(s1.end() - 1, SIZE_LITTLE, Any(123));
	m1.insert(m1.end() - 1, SIZE_LITTLE, Any(123));
	assertVecEQ(s1, m1);

	sVec	s2(sEmpty);
	mVec	m2(mEmpty);

	s2.insert(s2.begin(), sTen.begin(), sTen.end());
	m2.insert(m2.begin(), sTen.begin(), sTen.end());
	assertVecEQ(s2, m2);

	s2.insert(s2.begin() + 5, sTen.begin(), sTen.end());
	m2.insert(m2.begin() + 5, sTen.begin(), sTen.end());
	assertVecEQ(s2, m2);
}

/* todo */

TEST_F(VecTest, swap) {
	sVec	s1(sTen);
	sVec	s2(sRandom);

	mVec	m1(mTen);
	mVec	m2(mRandom);

	sVec::const_iterator	sIt		= s1.begin();
	mVec::const_iterator	mIt		= m1.begin();
	sVec::const_iterator	sIte	= s1.end();
	mVec::const_iterator	mIte	= m1.end();

	s1.swap(s2);
	m1.swap(m2);
	assertVecEQFromIterators(sIt, sIte, mIt, mIte);
	assertVecEQ(s2, m2);

	s1.swap(s2);
	m1.swap(m2);
	assertVecEQ(s1, m1);
	assertVecEQ(s2, m2);
}

TEST_F(VecTest, clear) {
	sEmpty.clear();
	mEmpty.clear();
	assertVecEQ(sEmpty, mEmpty);
	sTen.clear();
	mTen.clear();
	assertVecEQ(sTen, mTen);
	sRandom.clear();
	mRandom.clear();
	sRandom.clear();
	mRandom.clear();
	assertVecEQ(sRandom, mRandom);
}

TEST_F(VecTest, get_allocator) {
	sVec	s1(sAl);
	mVec	m1(sAl);
	Any *	sP;
	Any *	mP;

	sP = s1.get_allocator().allocate(10);
	mP = m1.get_allocator().allocate(10);

	for (int i = 0; i < 10; ++i) {
		sP[i] = Any(i);
		mP[i] = Any(i);
	}

	sVec	s2(sP, sP + 10);
	mVec	m2(mP, mP + 10);
	assertVecEQ(s2, m2);

	s1.get_allocator().deallocate(sP, 10);
	m1.get_allocator().deallocate(mP, 10);
}

TEST_F(VecTest, non_member_operators) {
	sVec	s1(sEmpty);
	mVec	m1(mEmpty);

	ASSERT_EQ(s1 == sEmpty, m1 == mEmpty);
	ASSERT_EQ(s1 < sTen, m1 < mTen);
	ASSERT_EQ(s1 > sTen, m1 > mTen);
	ASSERT_EQ(s1 != sTen, m1 != mTen);

	sVec	s2(sTen);
	mVec	m2(mTen);
	ASSERT_EQ(s2 <= sTen, m2 <= mTen);
	ASSERT_EQ(s2 >= sTen, m2 >= mTen);

	sVec	s3(sEmpty);
	sVec	s4(sEmpty);
	mVec	m3(mEmpty);
	mVec	m4(mEmpty);

	s3.push_back(Any(1));	s4.push_back(Any(1));
	s3.push_back(Any(2));	s4.push_back(Any(2));
	s3.push_back(Any(3));
	m3.push_back(Any(1));	m4.push_back(Any(1));
	m3.push_back(Any(2));	m4.push_back(Any(2));
	m3.push_back(Any(3));
	ASSERT_EQ(s3 < s4, m3 < m4);
	ASSERT_EQ(s3 > s4, m3 > m4);
	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(VecTest, non_member_swap) {
	sVec		s1(sEmpty);
	sVec		s2(sTen);
	mVec		m1(mEmpty);
	mVec		m2(mTen);

	std::swap(s1, s2);
	std::swap(m1, m2);
	assertVecEQ(s2, m2);
	assertVecEQ(s1, m1);

	sVec		s3(sRandom);
	sVec		s4(sTen);
	mVec		m3(mRandom);
	mVec		m4(mTen);

	std::swap(s3, s4);
	std::swap(m3, m4);
	assertVecEQ(s3, m3);
	assertVecEQ(s4, m4);
}

#undef DEBUG
