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

using sDeq		= std::deque<Any>;
using mDeq		= ft::deque<Any>;

TEST(deque, basic_types) {
	Any	a;

	mDeq::value_type				s1 = a;
	mDeq::allocator_type			s2;
	mDeq::reference					s3 = a;
	mDeq::const_reference			s4 = a;
	mDeq::pointer					s5;
	mDeq::const_pointer				s6;
	mDeq::iterator					s7;
	mDeq::const_iterator			s8;
//	mDeq::reverse_iterator			s9; /* todo: iterators */
//	mDeq::const_reverse_iterator	s10; /* todo iterators */
	mDeq::difference_type			s11;
	mDeq::size_type					s12;
}

void	assertDequeEQ(sDeq & sM, mDeq & mM) {
	ASSERT_EQ(sM.size(), mM.size());
	ASSERT_EQ(sM.empty(), mM.empty());

	sDeq::iterator	sIt		= sM.begin();
	sDeq::iterator	sIte	= sM.end();
	mDeq::iterator	mIt		= mM.begin();
	mDeq::iterator	mIte	= mM.end();

	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	++sIt; --sIt;
	++mIt; --mIt;
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(sIt->getInt(), mIt->getInt());
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}

TEST(deque, construct_basic) {
	sDeq		s1;
	mDeq		m1;

	sDeq		s2(LITTLE_SIZE);
	mDeq		m2(LITTLE_SIZE);
	assertDequeEQ(s2, m2);

	sDeq		s3(LARGE_SIZE, ANY);
	mDeq		m3(LARGE_SIZE, ANY);
	assertDequeEQ(s3, m3);

	Any		ar[] = {Any(1), Any(2), Any(3), Any(4)};

	sDeq		s4(ar, ar + 4);
	mDeq		m4(ar, ar + 4);
	assertDequeEQ(s4, m4);

	sDeq		s5(s4);
	mDeq		m5(m4);
	assertDequeEQ(s5, m5);

	s5 = s3;
	m5 = m3;
	assertDequeEQ(s5, m5);
}

char getRandAlpha() {
	return static_cast<char>(random() % ('z' - 'a') + 'a');
}

class DeqTest : public ::testing::Test {
public:
	DeqTest() {
		// код инициализации
		for (char ch = 'a'; ch < 'z' + 1; ++ch) {
			sAlpha.push_back(Any(ch));
			mAlpha.push_back(Any(ch));
		}
	}
	virtual void SetUp() {
		// код, который будет выполнен перед началом теста
		const int	seed = static_cast<int>(time(nullptr));
		std::srand(seed);
		const int	size = std::rand() % 50 + 1;
		char		randChar;
		D(std::cout << "Seed = " << seed << std::endl;);
		for (int i = 0; i < size; ++i) {
			randChar = getRandAlpha();
			sRando.push_back(Any(randChar));
			mRando.push_back(Any(randChar));
		}
	}
	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}
	~DeqTest() {
		// очистка всех ресурсов, вызов исключений не допускается
	}

public:
	sDeq		sEmpty;
	sDeq		sAlpha;
	sDeq		sRando;

	mDeq		mEmpty;
	mDeq		mAlpha;
	mDeq		mRando;
};

TEST_F(DeqTest, iterators_f) {
	sDeq::iterator			s1 = sAlpha.begin();
	sDeq::iterator			s2 = sAlpha.end();
	sDeq::reverse_iterator	s3 = sAlpha.rbegin();
	sDeq::reverse_iterator	s4 = sAlpha.rend();

	mDeq::iterator			m1 = mAlpha.begin();
	mDeq::iterator			m2 = mAlpha.end();
	mDeq::reverse_iterator	m3 = mAlpha.rbegin();
	mDeq::reverse_iterator	m4 = mAlpha.rend();

	ASSERT_EQ(*s1, *m1);
	ASSERT_EQ(*(--s2), *(--m2));
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*(--s4), *(--m4));
}

TEST(deque, iterator_types) {
	sDeq::iterator::value_type					s1;
	sDeq::iterator::difference_type				s2;
	sDeq::iterator::pointer						s3;
	sDeq::iterator::iterator_category			s4;

	mDeq::iterator::value_type					m1;
	mDeq::iterator::difference_type				m2;
	mDeq::iterator::pointer						m3;
	mDeq::iterator::iterator_category			m4;
}

TEST_F(DeqTest, iterators_construct) {
	mDeq::const_iterator	mc1 = mEmpty.begin();
	mDeq::const_iterator	mc2(mc1);
	mDeq::iterator			m3 = mEmpty.begin();
	mDeq::iterator			m4(m3);

//	mDeq::iterator			m5(mc1);	// FALSE
	mDeq::const_iterator	m6(m4);

	mc2 = m4;
//	m4 = mc2;							// FALSE

	mDeq::const_iterator	const_Iterator = mEmpty.begin();
	mDeq::iterator			iterator = mEmpty.begin();

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

TEST_F(DeqTest, const_iterators_empty) {
	sDeq::const_iterator	sIt		= sEmpty.begin();
	sDeq::const_iterator	sIte	= sEmpty.end();
	mDeq::const_iterator	mIt		= mEmpty.end();
	mDeq::const_iterator	mIte	= mEmpty.end();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sDeq::const_iterator	s3(sIt);
	mDeq::const_iterator	m3(mIt);
	sDeq::const_iterator	s4;
	mDeq::const_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(DeqTest, iterators_empty) {
	sDeq::iterator	sIt		= sEmpty.begin();
	sDeq::iterator	sIte	= sEmpty.end();
	mDeq::iterator	mIt		= mEmpty.end();
	mDeq::iterator	mIte	= mEmpty.end();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sDeq::iterator	s3(sIt);
	mDeq::iterator	m3(mIt);
	sDeq::iterator	s4;
	mDeq::iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(DeqTest, const_iterator_bi) {
	sDeq::const_iterator			sIt		= sAlpha.begin();
	sDeq::const_iterator			sIte	= sAlpha.end();
	mDeq::const_iterator			mIt		= mAlpha.begin();
	mDeq::const_iterator			mIte	= mAlpha.end();

	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sDeq::const_iterator			s3(sIt);
	sDeq::const_iterator			s4;
	s4 = sIt;
	mDeq::const_iterator			m3(mIt);
	mDeq::const_iterator			m4;
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
	ASSERT_EQ(counter, 26);
}

TEST_F(DeqTest, iterator_bi) {
	sDeq::iterator			sIt = sAlpha.begin();
	sDeq::iterator			sIte = sAlpha.end();
	mDeq::iterator			mIt = mAlpha.begin();
	mDeq::iterator			mIte = mAlpha.end();
	ASSERT_EQ(sIt != sIte, mIt != mIte);

	sDeq::iterator			s3(sIt);
	sDeq::iterator			s4;
	s4 = sIt;
	mDeq::iterator			m3(mIt);
	mDeq::iterator			m4;
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
	ASSERT_EQ(counter, 26);

	sIt = sAlpha.begin();
	sIte = sAlpha.end();
	mIt = mAlpha.begin();
	mIte = mAlpha.end();
	while (sIt != sIte) {
		*sIt = ANY; *mIt = ANY;
		++sIt; ++mIt;
	}
	sDeq	s5(26, ANY);
	assertDequeEQ(s5, mAlpha);
}

TEST_F(DeqTest, iterator_random_access) {
	sDeq::iterator			s1		= sAlpha.begin();
	mDeq::iterator			m1		= mAlpha.begin();

	s1 = (s1 + 2);		m1 = (m1 + 2);
	s1 = (2 + s1);		m1 = (2 + m1);
	s1 = (s1 - 1);		m1 = (m1 - 1);
//	s1 = (1 - s1);		m1 = (1 - m1);

	ASSERT_EQ(*s1, *m1);
	ASSERT_EQ(s1[0], m1[0]);
	ASSERT_EQ(s1[1], m1[1]);
	ASSERT_EQ(s1[3], m1[3]);
	ASSERT_EQ(s1[10].getInt(), m1[10].getInt());
	ASSERT_EQ(s1[-1], m1[-1]);
	ASSERT_EQ(s1->getInt(), m1->getInt());

	s1 += 2;		m1 += 2;
	s1 -= 1;		m1 -= 1;
	ASSERT_EQ(*s1, *m1);
}

TEST_F(DeqTest, const_iterator_random_access) {
	sDeq::const_iterator	s1		= sAlpha.begin();
	mDeq::const_iterator	m1		= mAlpha.begin();

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

TEST_F(DeqTest, reverse_iterators_empty) {
	sDeq::reverse_iterator	sIt		= sEmpty.rbegin();
	sDeq::reverse_iterator	sIte	= sEmpty.rend();
	mDeq::reverse_iterator	mIt		= mEmpty.rend();
	mDeq::reverse_iterator	mIte	= mEmpty.rend();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sDeq::reverse_iterator	s3(sIt);
	mDeq::reverse_iterator	m3(mIt);
	sDeq::reverse_iterator	s4;
	mDeq::reverse_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(DeqTest, const_reverse_iterators_empty) {
	sDeq::const_reverse_iterator	sIt		= sEmpty.rbegin();
	sDeq::const_reverse_iterator	sIte	= sEmpty.rend();
	mDeq::const_reverse_iterator	mIt		= mEmpty.rend();
	mDeq::const_reverse_iterator	mIte	= mEmpty.rend();

	ASSERT_EQ(sIt == sIte, mIt == mIte);
	ASSERT_EQ(sIt != sIte, mIt != mIte);
	ASSERT_EQ(sIt < sIte, mIt < mIte);
	ASSERT_EQ(sIt > sIte, mIt > mIte);
	ASSERT_EQ(sIt <= sIte, mIt <= mIte);
	ASSERT_EQ(sIt >= sIte, mIt >= mIte);

	sDeq::const_reverse_iterator	s3(sIt);
	mDeq::const_reverse_iterator	m3(mIt);
	sDeq::const_reverse_iterator	s4;
	mDeq::const_reverse_iterator	m4;
	s4 = sIte;
	m4 = mIte;

	ASSERT_EQ(s3 == s4, m3 == m4);
}

TEST_F(DeqTest, const_iterator_reverse_bi) {
	sDeq::const_reverse_iterator	sRit	= sAlpha.rbegin();
	sDeq::const_reverse_iterator	sRite	= sAlpha.rend();
	mDeq::const_reverse_iterator	mRit	= mAlpha.rbegin();
	mDeq::const_reverse_iterator	mRite	= mAlpha.rend();

	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sDeq::const_reverse_iterator	s3(sRit);
	sDeq::const_reverse_iterator	s4;
	s4 = sRit;
	mDeq::const_reverse_iterator	m3(mRit);
	mDeq::const_reverse_iterator	m4;
	m4 = mRit;

	++sRit; ++mRit;
	--sRit; --mRit;
	ASSERT_EQ(sRit == s4, mRit == m4);
	ASSERT_EQ(sRit == s3, mRit == m3);

	s3 = sRit++; m3 = mRit++;
	s4 = sRit--; m4 = mRit--;
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*s4, *m4);
}

TEST_F(DeqTest, iterator_reverse_bi) {
	sDeq::reverse_iterator	sRit	= sAlpha.rbegin();
	sDeq::reverse_iterator	sRite	= sAlpha.rend();
	mDeq::reverse_iterator	mRit	= mAlpha.rbegin();
	mDeq::reverse_iterator	mRite	= mAlpha.rend();

	ASSERT_EQ(sRit != sRite, mRit != mRite);

	sDeq::reverse_iterator	s3(sRit);
	sDeq::reverse_iterator	s4;
	s4 = sRit;
	mDeq::reverse_iterator	m3(mRit);
	mDeq::reverse_iterator	m4;
	m4 = mRit;

	++sRit; ++mRit;
	--sRit; --mRit;
	ASSERT_EQ(sRit == s4, mRit == m4);
	ASSERT_EQ(sRit == s3, mRit == m3);

	s3 = sRit++; m3 = mRit++;
	s4 = sRit--; m4 = mRit--;
	ASSERT_EQ(*s3, *m3);
	ASSERT_EQ(*s4, *m4);
}

TEST_F(DeqTest, const_iterators_end) {
	sDeq::const_iterator			s1	= sAlpha.begin();
	sDeq::const_reverse_iterator	sr2	= sAlpha.rend();
	mDeq::const_iterator			m1	= mAlpha.begin();
	mDeq::const_reverse_iterator	mr2	= mAlpha.rend();

	--sr2; --mr2;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);

	s1 = sAlpha.end();
	sr2 = sAlpha.rbegin();
	m1 = mAlpha.end();
	mr2 = mAlpha.rbegin();
	--s1; --m1;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);
}

TEST_F(DeqTest, reverse_iterator_random_access) {
	sDeq::reverse_iterator		s1	= sAlpha.rbegin();
	mDeq::reverse_iterator		m1	= mAlpha.rbegin();

	s1 = (s1 + 2);		m1 = (m1 + 2);
	s1 = (2 + s1);		m1 = (2 + m1);
	s1 = (s1 - 1);		m1 = (m1 - 1);
//	s1 = (1 - s1);		m1 = (1 - m1);

	ASSERT_EQ(*s1, *m1);
	ASSERT_EQ(s1[0], m1[0]);
	ASSERT_EQ(s1[1], m1[1]);
	ASSERT_EQ(s1[3], m1[3]);
	ASSERT_EQ(s1[10], m1[10]);
	ASSERT_EQ(s1[-1], m1[-1]);
	ASSERT_EQ(s1->getInt(), m1->getInt());

	s1 += 2;		m1 += 2;
	s1 -= 1;		m1 -= 1;
	ASSERT_EQ(*s1, *m1);
}

TEST_F(DeqTest, iterators_end) {
	sDeq::iterator			s1 = sAlpha.begin();
	sDeq::reverse_iterator	sr2 = sAlpha.rend();
	mDeq::iterator			m1 = mAlpha.begin();
	mDeq::reverse_iterator	mr2 = mAlpha.rend();

	--sr2; --mr2;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);

	s1 = sAlpha.end();
	sr2 = sAlpha.rbegin();
	m1 = mAlpha.end();
	mr2 = mAlpha.rbegin();
	--s1; --m1;
	ASSERT_EQ(*s1, *sr2);
	ASSERT_EQ(*m1, *mr2);
}

TEST_F(DeqTest, iterators_compare) {
	sDeq::const_iterator	sCI	= sAlpha.begin();
	sDeq::iterator			sI	= sAlpha.begin();
	mDeq::const_iterator	mCI	= mAlpha.begin();
	mDeq::iterator			mI	= mAlpha.begin();

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

TEST_F(DeqTest, reverse_iterators_compare) {
	sDeq::const_reverse_iterator	sCI	= sAlpha.rbegin();
	sDeq::reverse_iterator			sI	= sAlpha.rbegin();
	mDeq::const_reverse_iterator	mCI	= mAlpha.rbegin();
	mDeq::reverse_iterator			mI	= mAlpha.rbegin();

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

TEST_F(DeqTest, size) {
	ASSERT_EQ(sEmpty.size(), mEmpty.size());
	ASSERT_EQ(sAlpha.size(), mAlpha.size());
	ASSERT_EQ(sRando.size(), mRando.size());
}

TEST_F(DeqTest, max_size) {
	ASSERT_EQ(sEmpty.max_size(), mEmpty.max_size());
	ASSERT_EQ(sAlpha.max_size(), mAlpha.max_size());
}

TEST_F(DeqTest, empty) {
	ASSERT_EQ(sEmpty.empty(), mEmpty.empty());
	ASSERT_EQ(sAlpha.empty(), mAlpha.empty());
	ASSERT_EQ(sRando.empty(), mRando.empty());
}

TEST_F(DeqTest, resize) {
	sDeq		s1(sAlpha);
	mDeq		m1(mAlpha);

	s1.resize(LARGE_SIZE);
	m1.resize(LARGE_SIZE);
	assertDequeEQ(s1, m1);

	s1.resize(2 * LARGE_SIZE, ANY);
	m1.resize(2 * LARGE_SIZE, ANY);
	assertDequeEQ(s1, m1);

	s1.resize(1);
	m1.resize(1);
	assertDequeEQ(s1, m1);
}

TEST_F(DeqTest, operator_at) {
	ASSERT_EQ(sAlpha[10].getInt(), mAlpha[10].getInt());
	ASSERT_EQ(sAlpha[1].getInt(), mAlpha[1].getInt());
	ASSERT_EQ(sAlpha[0].getInt(), mAlpha[0].getInt());
	ASSERT_EQ(sAlpha[sAlpha.size() - 1].getInt(), mAlpha[mAlpha.size() - 1].getInt());
	for (size_t i = 0; i < sRando.size(); ++i) {
		ASSERT_EQ(sRando[i], mRando[i]);
	}
}

TEST_F(DeqTest, at) {
	try {
		mAlpha.at(100);
		FAIL();
	}
	catch (std::out_of_range &) {
		SUCCEED();
	}
	catch (...) {
		FAIL();
	}
	try {
		mAlpha.at(27);
		FAIL();
	}
	catch (std::out_of_range &) {
		SUCCEED();
	}
	catch (...) {
		FAIL();
	}
	for (size_t i = 0; i < sRando.size(); ++i) {
		ASSERT_EQ(sRando.at(i), mRando.at(i));
	}
}

TEST_F(DeqTest, front_and_back) {
	ASSERT_EQ(sAlpha.front(), mAlpha.front());
	ASSERT_EQ(sRando.front(), mRando.front());
	ASSERT_EQ(sRando.back(), mRando.back());
	ASSERT_EQ(sAlpha.back(), mAlpha.back());

	sAlpha.resize(LARGE_SIZE, ANY);
	mAlpha.resize(LARGE_SIZE, ANY);
	ASSERT_EQ(sAlpha.front(), mAlpha.front());
	ASSERT_EQ(sAlpha.back(), mAlpha.back());
}

TEST_F(DeqTest, assign) {
	sAlpha.assign(LARGE_SIZE, ANY);
	mAlpha.assign(LARGE_SIZE, ANY);
	assertDequeEQ(sAlpha, mAlpha);

	sAlpha.assign(sRando.begin(), sRando.end());
	mAlpha.assign(sRando.begin(), sRando.end());
	assertDequeEQ(sAlpha, mAlpha);
}

TEST_F(DeqTest, clear) {
	sRando.clear();
	mRando.clear();
	sAlpha.clear();
	mAlpha.clear();
	sEmpty.clear();
	mEmpty.clear();
	ASSERT_EQ(sEmpty.empty(), mEmpty.empty());
	ASSERT_EQ(sAlpha.empty(), mAlpha.empty());
	ASSERT_EQ(sRando.empty(), mRando.empty());
}

TEST_F(DeqTest, push) {
	sDeq		s1(sEmpty);
	mDeq		m1(mEmpty);

	s1.push_back(ANY);			m1.push_back(ANY);
	assertDequeEQ(s1, m1);
	s1.push_back(Any());		m1.push_back(Any());
	assertDequeEQ(s1, m1);
	s1.push_front(Any(1));		m1.push_front(Any(1));
	assertDequeEQ(s1, m1);
	s1.push_front(Any(2));		m1.push_front(Any(2));
	assertDequeEQ(s1, m1);
	s1.push_back(Any(3));		m1.push_back(Any(3));
	assertDequeEQ(s1, m1);
	s1.push_front(Any(4));		m1.push_front(Any(4));
	assertDequeEQ(s1, m1);
	s1.push_back(Any(5));		m1.push_back(Any(5));
	assertDequeEQ(s1, m1);
}

TEST_F(DeqTest, pop) {
	sDeq		s1(sAlpha);
	mDeq		m1(mAlpha);

	s1.pop_back();		m1.pop_back();
	assertDequeEQ(s1, m1);
	s1.pop_back();		m1.pop_back();
	assertDequeEQ(s1, m1);
	s1.pop_back();		m1.pop_back();
	assertDequeEQ(s1, m1);
	s1.pop_front();		m1.pop_front();
	assertDequeEQ(s1, m1);
	s1.pop_front();		m1.pop_front();
	assertDequeEQ(s1, m1);
	s1.pop_front();		m1.pop_front();
	assertDequeEQ(s1, m1);
	s1.pop_front();		m1.pop_front();
	assertDequeEQ(s1, m1);
	s1.pop_back();		m1.pop_back();
	assertDequeEQ(s1, m1);
	s1.pop_front();		m1.pop_front();
	assertDequeEQ(s1, m1);
	s1.pop_back();		m1.pop_back();
	assertDequeEQ(s1, m1);
	s1.pop_back();		m1.pop_back();
	assertDequeEQ(s1, m1);

	s1.clear();				m1.clear();
	s1.push_back(ANY);		m1.push_back(ANY);
	s1.push_back(Any());	m1.push_back(Any());
	s1.pop_front();			m1.pop_front();
	assertDequeEQ(s1, m1);
}

TEST_F(DeqTest, insert) {
	sDeq		s1(sAlpha);
	mDeq		m1(mAlpha);

	s1.insert(++s1.begin(), ANY);
	m1.insert(++m1.begin(), ANY);
	assertDequeEQ(s1, m1);

	s1.insert(s1.begin(), LARGE_SIZE, Any());
	m1.insert(m1.begin(), LARGE_SIZE, Any());
	assertDequeEQ(s1, m1);

	s1.insert(--s1.end(), sRando.begin(), sRando.end());
	m1.insert(--m1.end(), sRando.begin(), sRando.end());
	assertDequeEQ(s1, m1);
}
