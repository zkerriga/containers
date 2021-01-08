#include "gtest/gtest.h"
#include <set>
#include <iterator>
#include <limits>

#include "Any.hpp"
#include "set.hpp"

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sSet		= std::set<Any>;
using mSet		=  ft::set<Any>;
using mTree		= TreeNode<Any>;
using treePair	= std::pair<mTree*, bool>;

char getRandAlphaSet() {
	return static_cast<char>(random() % ('z' - 'a') + 'a');
}

class SetTest : public ::testing::Test {
public:
	SetTest() {
		// код инициализации
		for (char ch = 'a'; ch < 'z' + 1; ++ch) {
			sAlpha.insert(Any(ch));
			mAlpha.insert(Any(ch));
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
			randChar = getRandAlphaSet();
			sRando.insert(Any(randChar));
			mRando.insert(Any(randChar));
		}
	}
	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}
	~SetTest() {
		// очистка всех ресурсов, вызов исключений не допускается
	}

public:
	sSet		sEmpty;
	sSet		sAlpha;
	sSet		sRando;

	mSet		mEmpty;
	mSet		mAlpha;
	mSet		mRando;
};

void assertSetEQ(const sSet & sM, const mSet & mM) {
	ASSERT_EQ(sM.size(), mM.size());
	ASSERT_EQ(sM.empty(), mM.empty());

	sSet::const_iterator	sIt		= sM.begin();
	sSet::const_iterator	sIte	= sM.end();
	mSet::const_iterator	mIt		= mM.begin();
	mSet::const_iterator	mIte	= mM.end();

	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}

TEST(set, types) {
	sSet::key_type					s1;
	sSet::value_type				s3;
	sSet::key_compare				s4;
	sSet::allocator_type			s5;
	sSet::reference					s6 = s3;
	sSet::const_reference			s7 = s3;
	sSet::pointer					s8 = &s3;
	sSet::const_pointer				s9 = &s3;
	sSet::difference_type			s10;
	sSet::size_type					s11;

	mSet::key_type					m1;
	mSet::value_type				m3;
	mSet::key_compare				m4;
	mSet::allocator_type			m5;
	mSet::reference					m6 = m3;
	mSet::const_reference			m7 = m3;
	mSet::pointer					m8 = &m3;
	mSet::const_pointer				m9 = &m3;
	mSet::difference_type			m10;
	mSet::size_type					m11;
}

TEST_F(SetTest, basic_iterators) {
	sSet::iterator					s1 = sAlpha.begin();
	sSet::const_iterator			s2 = s1;
	sSet::reverse_iterator			s3 = sAlpha.rbegin();
	sSet::const_reverse_iterator	s4 = s3;

	mSet::iterator					m1 = mAlpha.begin();
	mSet::const_iterator			m2 = m1;
	mSet::reverse_iterator			m3 = mAlpha.rbegin();
	mSet::const_reverse_iterator	m4 = m3;

	ASSERT_EQ(s1 == s2, m1 == m2);
	ASSERT_EQ(s1 != s2, m1 != m2);
	ASSERT_EQ(s3 == s4, m3 == m4);
	ASSERT_EQ(s3 != s4, m3 != m4);
}

TEST_F(SetTest, test_for_tests) {
	ASSERT_TRUE(true);
	assertSetEQ(sEmpty, mEmpty);
	assertSetEQ(sAlpha, mAlpha);
	assertSetEQ(sRando, mRando);
}

void	insertSet(sSet & sM, mSet & mM) {
	const Any randAny(getRandAlphaSet());

	std::pair< sSet::iterator, bool >	sRet = sM.insert(randAny);
	std::pair< mSet::iterator, bool >	mRet = mM.insert(randAny);
	ASSERT_EQ(*sRet.first, *mRet.first);
	ASSERT_EQ(sRet.second, mRet.second);
}

void	createTestsSetsAndStartInsertsSet() {
	sSet		sM;
	mSet		mM;

	const auto	seed = static_cast<unsigned int>(time(nullptr));
	D(std::cout << "INSERT SEED: " << seed << std::endl;);
	srand(seed);
	for (int i = 0; i < 500; ++i) {
		insertSet(sM, mM);
		assertSetEQ(sM, mM);
	}
}

TEST(set, insert_crush) {
	for (int i = 0; i < 1000; ++i) {
		createTestsSetsAndStartInsertsSet();
	}
	SUCCEED();
}

TEST_F(SetTest, empty) {
	ASSERT_EQ(sEmpty.empty(), mEmpty.empty());
	ASSERT_EQ(sAlpha.empty(), mAlpha.empty());
	ASSERT_EQ(sRando.empty(), mRando.empty());
}

TEST_F(SetTest, size) {
	ASSERT_EQ(sEmpty.size(), mEmpty.size());
	ASSERT_EQ(sAlpha.size(), mAlpha.size());
	ASSERT_EQ(sRando.size(), mRando.size());
}

TEST_F(SetTest, construct) {
	sSet	s1(sAlpha.begin(), sAlpha.end());
	mSet	m1(sAlpha.begin(), sAlpha.end());
	assertSetEQ(s1, m1);

	sSet	s2(sRando.begin(), sRando.end());
	mSet	m2(sRando.begin(), sRando.end());
	assertSetEQ(s2, m2);

	sSet	s3(sRando.begin(), sRando.begin());
	mSet	m3(sRando.begin(), sRando.begin());
	assertSetEQ(s3, m3);

	sSet	s4(s1);
	mSet	m4(m1);
	assertSetEQ(s4, m4);

	sSet	s5(s2);
	mSet	m5(m2);
	assertSetEQ(s5, m5);
}

TEST_F(SetTest, clear) {
	sEmpty.clear();
	mEmpty.clear();
	assertSetEQ(sEmpty, mEmpty);

	sRando.clear();
	mRando.clear();
	assertSetEQ(sRando, mRando);

	sRando.insert(sAlpha.begin(), sAlpha.end());
	mRando.insert(sAlpha.begin(), sAlpha.end());
	assertSetEQ(sRando, mRando);
}

TEST_F(SetTest, assigment) {
	sSet	s1;
	mSet	m1;

	s1 = sRando;
	m1 = mRando;
	assertSetEQ(s1, m1);

	sSet	s2;
	mSet	m2;

	s2 = sAlpha;
	m2 = mAlpha;
	assertSetEQ(s2, m2);
}

TEST_F(SetTest, max_size) {
	size_t	maxBytes = static_cast<size_t>(-1);
	ASSERT_GE(maxBytes / sEmpty.max_size(), maxBytes / mEmpty.max_size());
	ASSERT_GE(maxBytes / sAlpha.max_size(), maxBytes / mAlpha.max_size());
}

TEST_F(SetTest, get_allocator) {
	Any		*sAnys;
	sAnys = sEmpty.get_allocator().allocate(12);
	sEmpty.get_allocator().deallocate(sAnys, 12);

	Any		*mAnys;
	mAnys = mEmpty.get_allocator().allocate(12);
	mEmpty.get_allocator().deallocate(mAnys, 12);
}

TEST_F(SetTest, insert_position) {
	sSet		s1;
	mSet		m1;

	s1.insert(Any(1));
	s1.insert(Any(1));
	s1.insert(Any(1));
	m1.insert(Any(1));
	m1.insert(Any(1));
	m1.insert(Any(1));

	ASSERT_EQ(
		*s1.insert(s1.begin(), Any()),
		*m1.insert(m1.begin(), Any())
	);
	assertSetEQ(s1, m1);
	ASSERT_EQ(
		*s1.insert(s1.begin(), Any(3)),
		*m1.insert(m1.begin(), Any(3))
	);
	assertSetEQ(s1, m1);
}

TEST_F(SetTest, swap) {
	sSet	s1(sAlpha);
	mSet	m1(mAlpha);
	sSet	s2(sRando);
	mSet	m2(mRando);

	s1.swap(s2);
	m1.swap(m2);
	assertSetEQ(s1, m1);
	assertSetEQ(s2, m2);

	s2.swap(s2);
	m2.swap(m2);
	s1.swap(s2);
	m1.swap(m2);
	s1.swap(s2);
	m1.swap(m2);
	assertSetEQ(s1, m1);
	assertSetEQ(s2, m2);
}

TEST_F(SetTest, erase_basic) {
	sSet	s1(sAlpha);
	mSet	m1(mAlpha);

	EXPECT_EQ(
		s1.erase(Any('b')),
		m1.erase(Any('b'))
	);
	assertSetEQ(s1, m1);
	EXPECT_EQ(
		s1.erase(Any('h')),
		m1.erase(Any('h'))
	);
	assertSetEQ(s1, m1);
	EXPECT_EQ(
		s1.erase(Any('z')),
		m1.erase(Any('z'))
	);
	assertSetEQ(s1, m1);
	EXPECT_EQ(
		s1.erase(Any('c')),
		m1.erase(Any('c'))
	);
	assertSetEQ(s1, m1);
	EXPECT_EQ(
		s1.erase(Any('p')),
		m1.erase(Any('p'))
	);
	assertSetEQ(s1, m1);
}

void	eraseSet(sSet & sM, mSet & mM) {
	const Any	randKey(getRandAlphaSet());
	D(std::cout << "To delete: " << randKey << std::endl);
	const size_t	sRet	= sM.erase(randKey);
	const size_t	mRet	= mM.erase(randKey);

	ASSERT_EQ(sRet, mRet);
}

void	createAndEraseMapsSet() {
	sSet		sM;
	mSet		mM;

	const auto	seed = static_cast<unsigned int>(time(nullptr));
	D(std::cout << "ERRASE SEED: " << seed << std::endl;);
	srand(seed);
	const auto	insertN = rand() % 400 + 4;
	for (int i = 0; i < insertN; ++i) {
		insertSet(sM, mM);
	}
	for (int i = 0; i < 200; ++i) {
		eraseSet(sM, mM);
		assertSetEQ(sM, mM);
		if (sM.empty() && mM.empty()) {
			eraseSet(sM, mM);
			assertSetEQ(sM, mM);
			break;
		}
	}
}

TEST(set, erase_crush) {
	for (int i = 0; i < 8000; ++i) {
		createAndEraseMapsSet();
	}
	SUCCEED();
}

TEST_F(SetTest, erase) {
	sSet	s1(sAlpha);
	mSet	m1(mAlpha);

	s1.erase(++s1.begin());
	m1.erase(++m1.begin());
	assertSetEQ(s1, m1);
	s1.erase(--s1.end());
	m1.erase(--m1.end());
	assertSetEQ(s1, m1);

	sSet	s2(sEmpty);
	mSet	m2(mEmpty);

	s2.erase(s2.begin(), s2.end());
	m2.erase(m2.begin(), m2.end());
	assertSetEQ(s2, m2);

	sSet	s3(sAlpha);
	mSet	m3(mAlpha);

	s3.erase(++s3.begin(), --s3.end());
	m3.erase(++m3.begin(), --m3.end());
	assertSetEQ(s3, m3);

	sSet	s4(sRando);
	mSet	m4(mRando);

	s4.erase(s4.begin(), s4.end());
	m4.erase(m4.begin(), m4.end());
	assertSetEQ(s4, m4);
}

void	foundAssertSet(sSet & sM, mSet & mM, sSet::const_iterator sIt, mSet::const_iterator mIt) {
	ASSERT_EQ(sM.end() == sIt, mM.end() == mIt);
	if (sM.end() != sIt) {
		ASSERT_EQ(*sIt, *mIt);
	}
}

TEST_F(SetTest, find) {
	foundAssertSet(sEmpty, mEmpty, sEmpty.find(Any('a')), mEmpty.find(Any('a')));

	for (char i = 0; i < 127; ++i) {
		foundAssertSet(sAlpha, mAlpha, sAlpha.find(Any(i)), mAlpha.find(Any(i)));
	}
	for (char i = 0; i < 127; ++i) {
		foundAssertSet(sRando, mRando, sRando.find(Any(i)), mRando.find(Any(i)));
	}
}

TEST_F(SetTest, key_value_comp) {
	sSet::key_compare	sKeyComp = sEmpty.key_comp();
	mSet::key_compare	mKeyComp = mEmpty.key_comp();

	ASSERT_EQ(
		sKeyComp(Any('a'), Any('a')),
		mKeyComp(Any('a'), Any('a'))
	);
	ASSERT_EQ(
		sKeyComp(Any('m'), Any('a')),
		mKeyComp(Any('m'), Any('a'))
	);
	ASSERT_EQ(
		sKeyComp(Any('m'), Any('z')),
		mKeyComp(Any('m'), Any('z'))
	);

	sSet::value_compare		sValComp = sEmpty.value_comp();
	mSet::value_compare		mValComp = mEmpty.value_comp();

	ASSERT_EQ(
		sValComp(Any(1), Any(1)),
		mValComp(Any(1), Any(1))
	);
	ASSERT_EQ(
		sValComp(Any(1), Any(2)),
		mValComp(Any(1), Any(2))
	);
	ASSERT_EQ(
		sValComp(Any(), Any()),
		mValComp(Any(), Any())
	);
	ASSERT_EQ(
		sValComp(Any(), Any()),
		mValComp(Any(), Any())
	);
}

TEST_F(SetTest, count) {
	ASSERT_EQ(sEmpty.count(Any('a')), mEmpty.count(Any('a')));
	for (char i = 0; i < 126; ++i) {
		ASSERT_EQ(sAlpha.count(Any(i)), mAlpha.count(Any(i)));
	}
}

TEST_F(SetTest, lower_bound) {
	sSet::iterator	s1 = sEmpty.lower_bound(Any('a'));
	mSet::iterator	m1 = mEmpty.lower_bound(Any('a'));
	ASSERT_EQ(s1 == sEmpty.end(), m1 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s1 = sAlpha.lower_bound(Any(i));
		m1 = mAlpha.lower_bound(Any(i));

		EXPECT_EQ(s1 == sAlpha.end(), m1 == mAlpha.end());
		if (s1 != sAlpha.end()) {
			ASSERT_EQ(*s1, *m1);
		}
	}

	sSet::const_iterator	s2 = sEmpty.lower_bound(Any('a'));
	mSet::const_iterator	m2 = mEmpty.lower_bound(Any('a'));
	ASSERT_EQ(s2 == sEmpty.end(), m2 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s2 = sAlpha.lower_bound(Any(i));
		m2 = mAlpha.lower_bound(Any(i));

		EXPECT_EQ(s2 == sAlpha.end(), m2 == mAlpha.end());
		if (s2 != sAlpha.end()) {
			ASSERT_EQ(*s2, *m2);
		}
	}
}

TEST_F(SetTest, upper_bound) {
	sSet::iterator	s1 = sEmpty.upper_bound(Any('a'));
	mSet::iterator	m1 = mEmpty.upper_bound(Any('a'));
	ASSERT_EQ(s1 == sEmpty.end(), m1 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s1 = sAlpha.upper_bound(Any(i));
		m1 = mAlpha.upper_bound(Any(i));

		EXPECT_EQ(s1 == sAlpha.end(), m1 == mAlpha.end());
		if (s1 != sAlpha.end()) {
			EXPECT_EQ(*s1, *m1);
		}
	}

	sSet::const_iterator	s2 = sEmpty.upper_bound(Any('a'));
	mSet::const_iterator	m2 = mEmpty.upper_bound(Any('a'));
	ASSERT_EQ(s2 == sEmpty.end(), m2 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s2 = sAlpha.upper_bound(Any(i));
		m2 = mAlpha.upper_bound(Any(i));

		EXPECT_EQ(s2 == sAlpha.end(), m2 == mAlpha.end());
		if (s2 != sAlpha.end()) {
			EXPECT_EQ(*s2, *m2);
		}
	}
}

TEST_F(SetTest, equal_range) {
	auto	s1 = sEmpty.equal_range(Any('m'));
	auto	m1 = mEmpty.equal_range(Any('m'));
	ASSERT_EQ(s1.first == sEmpty.end(), m1.first == mEmpty.end());
	ASSERT_EQ(s1.second == sEmpty.end(), m1.second == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		auto s2 = sAlpha.equal_range(Any(i));
		auto m2 = mAlpha.equal_range(Any(i));
		ASSERT_EQ(s2.first == sAlpha.end(), m2.first == mAlpha.end());
		ASSERT_EQ(s2.second == sAlpha.end(), m2.second == mAlpha.end());
		if (s2.first != sAlpha.end() && s2.second != sAlpha.end()) {
			ASSERT_EQ(*s2.first, *m2.first);
			ASSERT_EQ(*s2.first, *m2.first);
		}
	}
}
