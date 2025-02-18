#include "gtest/gtest.h"
#include <map>
#include <iterator>
#include <limits>

#include "Any.hpp"
#include "map.hpp"
#include "utils.hpp"

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sMap		= std::map<char, Any>;
using mMap		=  ft::map<char, Any>;
using sPair		= std::pair<const char, Any>;
using mTree		= TreeNode<sPair>;
using treePair	= std::pair<mTree*, bool>;

char getRandAlpha() {
	return static_cast<char>(random() % ('z' - 'a') + 'a');
}

class MapTest : public ::testing::Test {
public:
	MapTest() {
		// код инициализации
		for (char ch = 'a'; ch < 'z' + 1; ++ch) {
			sAlpha[ch] = Any(ch);
			mAlpha[ch] = Any(ch);
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
			sRando[randChar] = Any(randChar);
			mRando[randChar] = Any(randChar);
		}
	}
	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}
	~MapTest() {
		// очистка всех ресурсов, вызов исключений не допускается
	}

public:
	sMap		sEmpty;
	sMap		sAlpha;
	sMap		sRando;

	mMap		mEmpty;
	mMap		mAlpha;
	mMap		mRando;
};

void assertMapEQ(const sMap & sM, const mMap & mM) {
	ASSERT_EQ(sM.size(), mM.size());
	ASSERT_EQ(sM.empty(), mM.empty());

	sMap::const_iterator	sIt		= sM.begin();
	sMap::const_iterator	sIte	= sM.end();
	mMap::const_iterator	mIt		= mM.begin();
	mMap::const_iterator	mIte	= mM.end();

	ASSERT_EQ((sIt == sIte), (mIt == mIte));
	while (sIt != sIte && mIt != mIte) {
		EXPECT_EQ(*sIt, *mIt);
		++sIt;
		++mIt;
	}
	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}

TEST(map, types) {
	sMap::key_type					s1;
	sMap::mapped_type				s2;
	sMap::value_type				s3;
	sMap::key_compare				s4;
	sMap::allocator_type			s5;
	sMap::reference					s6 = s3;
	sMap::const_reference			s7 = s3;
	sMap::pointer					s8 = &s3;
	sMap::const_pointer				s9 = &s3;
	sMap::difference_type			s10;
	sMap::size_type					s11;

	mMap::key_type					m1;
	mMap::mapped_type				m2;
	mMap::value_type				m3;
	mMap::key_compare				m4;
	mMap::allocator_type			m5;
	mMap::reference					m6 = m3;
	mMap::const_reference			m7 = m3;
	mMap::pointer					m8 = &m3;
	mMap::const_pointer				m9 = &m3;
	mMap::difference_type			m10;
	mMap::size_type					m11;
}

class TreeTest : public ::testing::Test {
public:
	typedef TreeNode< std::pair<const char, Any> >	_tree;
	TreeTest() {
		// код инициализации
		for (size_t i = 0; i < size; ++i) {
			chArr[i] = static_cast<char>(i + 'a');
		}
		pairs = sPairAlloc.allocate(size);
		for (size_t i = 0; i < size; ++i) {
			sPairAlloc.construct(pairs + i, std::make_pair(chArr[i], Any(chArr[i])));
		}
	}
	virtual void SetUp() {
		// код, который будет выполнен перед началом теста
		end = mTree::end::create(sTreeAlloc);
	}
	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}
	~TreeTest() {
		// очистка всех ресурсов, вызов исключений не допускается
	}

public:
	static const size_t			size = 6;

	std::allocator< mTree >		sTreeAlloc;
	std::allocator< sPair >		sPairAlloc;
	char						chArr[size];
	sPair						*pairs;

	mTree						*end;
};

TEST_F(TreeTest, iterator_basic) {
	mTree *		node20 = mTree::create(sTreeAlloc, sPairAlloc, pairs[2]);
	mTree *		node10 = mTree::create(sTreeAlloc, sPairAlloc, pairs[0]);
	mTree *		node15 = mTree::create(sTreeAlloc, sPairAlloc, pairs[1]);
	mTree *		node40 = mTree::create(sTreeAlloc, sPairAlloc, pairs[4]);
	mTree *		node30 = mTree::create(sTreeAlloc, sPairAlloc, pairs[3]);
	mTree *		node50 = mTree::create(sTreeAlloc, sPairAlloc, pairs[5]);
	mTree::linkLeft(node10, end);
	mTree::linkRight(node10, node15);
	mTree::linkLeft(node20, node10);
	mTree::linkRight(node20, node40);
	mTree::linkLeft(node40, node30);
	mTree::linkRight(node40, node50);
	mTree::linkRight(node50, end);
	mTree::end::setRoot(end, node20);
	mTree::end::setFirst(end, node10);
	mTree::end::setLast(end, node50);

	D(printTree::print(end, 5));
	mMap::iterator		it(node10);
	mMap::iterator		ite(end);
	while (it != ite) {
		D(std::cout << it->first << '-' << it->second << std::endl);
		++it;
	}
	D(std::cout << std::endl);
	it = mMap::iterator(node50);
	while (it != ite) {
		D(std::cout << it->first << '-' << it->second << std::endl);
		--it;
	}

	D(std::cout << "ITE" << std::endl);
	--ite;
	D(std::cout << ite->first << '-' << ite->second << std::endl);
}

class comp : public mMap::value_compare {
public:
	comp() : value_compare(std::less<mMap::key_type>()) {}
	~comp() {}
};

TEST_F(TreeTest, insert) {
	const treePair	pair = mTree::insert(mTree::end::getRoot(end), pairs[2], comp(), sTreeAlloc, sPairAlloc);
	ASSERT_TRUE(pair.second);
	ASSERT_EQ(mTree::getData(pair.first), pairs[2]);

	if (true) {
		mTree::end::setRoot(end, pair.first);
		mTree::end::setFirst(end, pair.first);
		mTree::end::setLast(end, pair.first);
		mTree::flipColor(pair.first);
	}
	D(printTree::print(end, 4));

	const treePair	pair2 = mTree::insert(
		mTree::end::getRoot(end),
		pairs[2],
		comp(),
		sTreeAlloc,
		sPairAlloc
	);
	ASSERT_FALSE(pair2.second);
	ASSERT_EQ(mTree::getData(pair2.first), pairs[2]);
	D(printTree::print(end, 4));

	const treePair	pair3 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[0],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair3.second);
	ASSERT_EQ(mTree::getData(pair3.first), pairs[0]);
	D(printTree::print(end, 4));
	const treePair	pair4 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[1],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair4.second);
	ASSERT_EQ(mTree::getData(pair4.first), pairs[1]);
	mTree::flipColor(mTree::end::getRoot(end));
	D(printTree::print(end, 4));
	const treePair	pair5 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[5],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair5.second);
	ASSERT_EQ(mTree::getData(pair5.first), pairs[5]);
	D(printTree::print(end, 4));
	const treePair	pair6 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[4],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair6.second);
	ASSERT_EQ(mTree::getData(pair6.first), pairs[4]);
	D(printTree::print(end, 4));
	const treePair	pair7 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[3],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair7.second);
	ASSERT_EQ(mTree::getData(pair7.first), pairs[3]);
	D(printTree::print(end, 4));
}

TEST_F(TreeTest, insert2) {
	const treePair	pair0 = mTree::insert(mTree::end::getRoot(end), pairs[0], comp(), sTreeAlloc, sPairAlloc);
	ASSERT_TRUE(pair0.second);
	ASSERT_EQ(mTree::getData(pair0.first), pairs[0]);

	if (true) {
		mTree::end::setRoot(end, pair0.first);
		mTree::end::setFirst(end, pair0.first);
		mTree::end::setLast(end, pair0.first);
		mTree::flipColor(pair0.first);
	}
	D(printTree::print(end, 5));

	const treePair	pair1 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[1],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair1.second);
	ASSERT_EQ(mTree::getData(pair1.first), pairs[1]);
	D(printTree::print(end, 5));
	const treePair	pair2 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[2],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair2.second);
	ASSERT_EQ(mTree::getData(pair2.first), pairs[2]);
	mTree::flipColor(mTree::end::getRoot(end));
	D(printTree::print(end, 5));
	const treePair	pair3 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[3],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair3.second);
	ASSERT_EQ(mTree::getData(pair3.first), pairs[3]);
	D(printTree::print(end, 5));
	const treePair	pair4 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[4],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair4.second);
	ASSERT_EQ(mTree::getData(pair4.first), pairs[4]);
	D(printTree::print(end, 5));
	const treePair	pair5 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[5],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair5.second);
	ASSERT_EQ(mTree::getData(pair5.first), pairs[5]);
	D(printTree::print(end, 5));
}

TEST_F(MapTest, basic_iterators) {
	sMap::iterator					s1 = sAlpha.begin();
	sMap::const_iterator			s2 = s1;
	sMap::reverse_iterator			s3 = sAlpha.rbegin();
	sMap::const_reverse_iterator	s4 = s3;

	mMap::iterator					m1 = mAlpha.begin();
	mMap::const_iterator			m2 = m1;
	mMap::reverse_iterator			m3 = mAlpha.rbegin();
	mMap::const_reverse_iterator	m4 = m3;

	ASSERT_EQ(s1 == s2, m1 == m2);
	ASSERT_EQ(s1 != s2, m1 != m2);
	ASSERT_EQ(s3 == s4, m3 == m4);
	ASSERT_EQ(s3 != s4, m3 != m4);
}

TEST_F(MapTest, test_for_tests) {
	ASSERT_TRUE(true);
	assertMapEQ(sEmpty, mEmpty);
	assertMapEQ(sAlpha, mAlpha);
	assertMapEQ(sRando, mRando);
}

inline
sPair	createRandPair() {
	return std::make_pair(getRandAlpha(), Any(getRandAlpha()));
}

void	insert(sMap & sM, mMap & mM) {
	const sPair randPair = createRandPair();

	std::pair< sMap::iterator, bool >	sRet = sM.insert(randPair);
	std::pair< mMap::iterator, bool >	mRet = mM.insert(randPair);
	ASSERT_EQ((*sRet.first).first, (*mRet.first).first);
	ASSERT_EQ((*sRet.first).second, (*mRet.first).second);
	ASSERT_EQ(sRet.second, mRet.second);
}

void	createTestsMapsAndStartInserts() {
	sMap		sM;
	mMap		mM;

	const auto	seed = static_cast<unsigned int>(time(nullptr));
	D(std::cout << "INSERT SEED: " << seed << std::endl;);
	srand(seed);
	for (int i = 0; i < 500; ++i) {
		insert(sM, mM);
		assertMapEQ(sM, mM);
	}
}

TEST(map, insert_crush) {
	for (int i = 0; i < 1000; ++i) {
		createTestsMapsAndStartInserts();
	}
	SUCCEED();
}

TEST_F(MapTest, empty) {
	ASSERT_EQ(sEmpty.empty(), mEmpty.empty());
	ASSERT_EQ(sAlpha.empty(), mAlpha.empty());
	ASSERT_EQ(sRando.empty(), mRando.empty());
}

TEST_F(MapTest, size) {
	ASSERT_EQ(sEmpty.size(), mEmpty.size());
	ASSERT_EQ(sAlpha.size(), mAlpha.size());
	ASSERT_EQ(sRando.size(), mRando.size());
}

TEST_F(MapTest, construct) {
	sMap	s1(sAlpha.begin(), sAlpha.end());
	mMap	m1(sAlpha.begin(), sAlpha.end());
	assertMapEQ(s1, m1);

	sMap	s2(sRando.begin(), sRando.end());
	mMap	m2(sRando.begin(), sRando.end());
	assertMapEQ(s2, m2);

	sMap	s3(sRando.begin(), sRando.begin());
	mMap	m3(sRando.begin(), sRando.begin());
	assertMapEQ(s3, m3);

	sMap	s4(s1);
	mMap	m4(m1);
	assertMapEQ(s4, m4);

	sMap	s5(s2);
	mMap	m5(m2);
	assertMapEQ(s5, m5);
}

TEST_F(MapTest, clear) {
	sEmpty.clear();
	mEmpty.clear();
	assertMapEQ(sEmpty, mEmpty);

	sRando.clear();
	mRando.clear();
	assertMapEQ(sRando, mRando);

	sRando.insert(sAlpha.begin(), sAlpha.end());
	mRando.insert(sAlpha.begin(), sAlpha.end());
	assertMapEQ(sRando, mRando);
}

TEST_F(MapTest, assigment) {
	sMap	s1;
	mMap	m1;

	s1 = sRando;
	m1 = mRando;
	assertMapEQ(s1, m1);

	sMap	s2;
	mMap	m2;

	s2 = sAlpha;
	m2 = mAlpha;
	assertMapEQ(s2, m2);
}

TEST_F(MapTest, max_size) {
	size_t	maxBytes = static_cast<size_t>(-1);
	ASSERT_GE(maxBytes / sEmpty.max_size(), maxBytes / mEmpty.max_size());
	ASSERT_GE(maxBytes / sAlpha.max_size(), maxBytes / mAlpha.max_size());
}

TEST_F(MapTest, get_allocator) {
	sPair	*sPairs;
	sPairs = sEmpty.get_allocator().allocate(12);
	sEmpty.get_allocator().deallocate(sPairs, 12);

	sPair	*mPairs;
	mPairs = mEmpty.get_allocator().allocate(12);
	mEmpty.get_allocator().deallocate(mPairs, 12);
}

TEST_F(MapTest, insert_position) {
	sMap		s1;
	mMap		m1;

	s1.insert(std::make_pair('c', Any(1)));
	s1.insert(std::make_pair('m', Any(1)));
	s1.insert(std::make_pair('p', Any(1)));
	m1.insert(std::make_pair('c', Any(1)));
	m1.insert(std::make_pair('m', Any(1)));
	m1.insert(std::make_pair('p', Any(1)));

	ASSERT_EQ(
		*s1.insert(s1.begin(), std::make_pair('a', Any())),
		*m1.insert(m1.begin(), std::make_pair('a', Any()))
	);
	assertMapEQ(s1, m1);
	ASSERT_EQ(
		*s1.insert(s1.begin(), std::make_pair('z', Any(3))),
		*m1.insert(m1.begin(), std::make_pair('z', Any(3)))
	);
	assertMapEQ(s1, m1);
}

TEST_F(MapTest, swap) {
	sMap	s1(sAlpha);
	mMap	m1(mAlpha);
	sMap	s2(sRando);
	mMap	m2(mRando);

	s1.swap(s2);
	m1.swap(m2);
	assertMapEQ(s1, m1);
	assertMapEQ(s2, m2);

	s2.swap(s2);
	m2.swap(m2);
	s1.swap(s2);
	m1.swap(m2);
	s1.swap(s2);
	m1.swap(m2);
	assertMapEQ(s1, m1);
	assertMapEQ(s2, m2);
}

TEST_F(MapTest, erase_basic) {
	sMap	s1(sAlpha);
	mMap	m1(mAlpha);

	EXPECT_EQ(
		s1.erase('b'),
		m1.erase('b')
	);
	assertMapEQ(s1, m1);
	EXPECT_EQ(
		s1.erase('h'),
		m1.erase('h')
	);
	assertMapEQ(s1, m1);
	EXPECT_EQ(
		s1.erase('z'),
		m1.erase('z')
	);
	assertMapEQ(s1, m1);
	EXPECT_EQ(
		s1.erase('c'),
		m1.erase('c')
	);
	assertMapEQ(s1, m1);
	EXPECT_EQ(
		s1.erase('p'),
		m1.erase('p')
	);
	assertMapEQ(s1, m1);
}

void	erase(sMap & sM, mMap & mM) {
	const char		randKey	= getRandAlpha();
	D(std::cout << "To delete: " << randKey << std::endl);
	const size_t	sRet	= sM.erase(randKey);
	const size_t	mRet	= mM.erase(randKey);

	ASSERT_EQ(sRet, mRet);
}

void	createAndEraseMaps() {
	sMap		sM;
	mMap		mM;

	const auto	seed = static_cast<unsigned int>(time(nullptr));
	D(std::cout << "ERRASE SEED: " << seed << std::endl;);
	srand(seed);
	const auto	insertN = rand() % 400 + 4;
	for (int i = 0; i < insertN; ++i) {
		insert(sM, mM);
	}
	for (int i = 0; i < 200; ++i) {
		erase(sM, mM);
		assertMapEQ(sM, mM);
		if (sM.empty() && mM.empty()) {
			erase(sM, mM);
			assertMapEQ(sM, mM);
			break;
		}
	}
}

TEST(map, erase_crush) {
	for (int i = 0; i < 8000; ++i) {
		createAndEraseMaps();
	}
	SUCCEED();
}

TEST_F(MapTest, erase) {
	sMap	s1(sAlpha);
	mMap	m1(mAlpha);

	s1.erase(++s1.begin());
	m1.erase(++m1.begin());
	assertMapEQ(s1, m1);
	s1.erase(--s1.end());
	m1.erase(--m1.end());
	assertMapEQ(s1, m1);

	sMap	s2(sEmpty);
	mMap	m2(mEmpty);

	s2.erase(s2.begin(), s2.end());
	m2.erase(m2.begin(), m2.end());
	assertMapEQ(s2, m2);

	sMap	s3(sAlpha);
	mMap	m3(mAlpha);

	s3.erase(++s3.begin(), --s3.end());
	m3.erase(++m3.begin(), --m3.end());
	assertMapEQ(s3, m3);

	sMap	s4(sRando);
	mMap	m4(mRando);

	s4.erase(s4.begin(), s4.end());
	m4.erase(m4.begin(), m4.end());
	assertMapEQ(s4, m4);
}

void	foundAssert(sMap & sM, mMap & mM, sMap::const_iterator sIt, mMap::const_iterator mIt) {
	ASSERT_EQ(sM.end() == sIt, mM.end() == mIt);
	if (sM.end() != sIt) {
		ASSERT_EQ(*sIt, *mIt);
	}
}

TEST_F(MapTest, find) {
	foundAssert(sEmpty, mEmpty, sEmpty.find('a'), mEmpty.find('a'));

	for (char i = 0; i < 127; ++i) {
		foundAssert(sAlpha, mAlpha, sAlpha.find(i), mAlpha.find(i));
	}
	for (char i = 0; i < 127; ++i) {
		foundAssert(sRando, mRando, sRando.find(i), mRando.find(i));
	}
}

TEST_F(MapTest, key_value_comp) {
	sMap::key_compare	sKeyComp = sEmpty.key_comp();
	mMap::key_compare	mKeyComp = mEmpty.key_comp();

	ASSERT_EQ(
		sKeyComp('a', 'a'),
		mKeyComp('a', 'a')
	);
	ASSERT_EQ(
		sKeyComp('m', 'a'),
		mKeyComp('m', 'a')
	);
	ASSERT_EQ(
		sKeyComp('m', 'z'),
		mKeyComp('m', 'z')
	);

	sMap::value_compare		sValComp = sEmpty.value_comp();
	mMap::value_compare		mValComp = mEmpty.value_comp();

	ASSERT_EQ(
		sValComp(std::make_pair('m', Any(1)), std::make_pair('m', Any(1))),
		mValComp(std::make_pair('m', Any(1)), std::make_pair('m', Any(1)))
	);
	ASSERT_EQ(
		sValComp(std::make_pair('m', Any(1)), std::make_pair('m', Any(2))),
		mValComp(std::make_pair('m', Any(1)), std::make_pair('m', Any(2)))
	);
	ASSERT_EQ(
		sValComp(std::make_pair('m', Any()), std::make_pair('a', Any())),
		mValComp(std::make_pair('m', Any()), std::make_pair('a', Any()))
	);
	ASSERT_EQ(
		sValComp(std::make_pair('m', Any()), std::make_pair('z', Any())),
		mValComp(std::make_pair('m', Any()), std::make_pair('z', Any()))
	);
}

TEST_F(MapTest, count) {
	ASSERT_EQ(sEmpty.count('a'), mEmpty.count('a'));
	for (char i = 0; i < 126; ++i) {
		ASSERT_EQ(sAlpha.count('a'), mAlpha.count('a'));
	}
}

TEST_F(MapTest, lower_bound) {
	sMap::iterator	s1 = sEmpty.lower_bound('a');
	mMap::iterator	m1 = mEmpty.lower_bound('a');
	ASSERT_EQ(s1 == sEmpty.end(), m1 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s1 = sAlpha.lower_bound(i);
		m1 = mAlpha.lower_bound(i);

		EXPECT_EQ(s1 == sAlpha.end(), m1 == mAlpha.end());
		if (s1 != sAlpha.end()) {
			ASSERT_EQ(s1->first, m1->first);
		}
	}

	sMap::const_iterator	s2 = sEmpty.lower_bound('a');
	mMap::const_iterator	m2 = mEmpty.lower_bound('a');
	ASSERT_EQ(s2 == sEmpty.end(), m2 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s2 = sAlpha.lower_bound(i);
		m2 = mAlpha.lower_bound(i);

		EXPECT_EQ(s2 == sAlpha.end(), m2 == mAlpha.end());
		if (s2 != sAlpha.end()) {
			ASSERT_EQ(s2->first, m2->first);
		}
	}
}

TEST_F(MapTest, upper_bound) {
	sMap::iterator	s1 = sEmpty.upper_bound('a');
	mMap::iterator	m1 = mEmpty.upper_bound('a');
	ASSERT_EQ(s1 == sEmpty.end(), m1 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s1 = sAlpha.upper_bound(i);
		m1 = mAlpha.upper_bound(i);

		EXPECT_EQ(s1 == sAlpha.end(), m1 == mAlpha.end());
		if (s1 != sAlpha.end()) {
			EXPECT_EQ(s1->first, m1->first);
		}
	}

	sMap::const_iterator	s2 = sEmpty.upper_bound('a');
	mMap::const_iterator	m2 = mEmpty.upper_bound('a');
	ASSERT_EQ(s2 == sEmpty.end(), m2 == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		s2 = sAlpha.upper_bound(i);
		m2 = mAlpha.upper_bound(i);

		EXPECT_EQ(s2 == sAlpha.end(), m2 == mAlpha.end());
		if (s2 != sAlpha.end()) {
			EXPECT_EQ(s2->first, m2->first);
		}
	}
}

TEST_F(MapTest, equal_range) {
	auto	s1 = sEmpty.equal_range('m');
	auto	m1 = mEmpty.equal_range('m');
	ASSERT_EQ(s1.first == sEmpty.end(), m1.first == mEmpty.end());
	ASSERT_EQ(s1.second == sEmpty.end(), m1.second == mEmpty.end());

	for (char i = 0; i < 126; ++i) {
		auto s2 = sAlpha.equal_range(i);
		auto m2 = mAlpha.equal_range(i);
		ASSERT_EQ(s2.first == sAlpha.end(), m2.first == mAlpha.end());
		ASSERT_EQ(s2.second == sAlpha.end(), m2.second == mAlpha.end());
		if (s2.first != sAlpha.end() && s2.second != sAlpha.end()) {
			ASSERT_EQ(s2.first->first, m2.first->first);
			ASSERT_EQ(s2.first->second, m2.first->second);
		}
	}
}
