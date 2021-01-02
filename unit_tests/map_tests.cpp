#include "gtest/gtest.h"
#include <map>
#include <iterator>
#include <limits>

#include "Any.hpp"
#include "map.hpp"
#include "utils.hpp"

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

using sMap		= std::map<char, Any>;
using mMap		=  ft::map<char, Any>;
using sPair		= std::pair<const char, Any>;
using mTree		= TreeNode<sPair>;
using treePair	= std::pair<mTree*, bool>;
//using sAlloc	= std::allocator<Any>;

char getRandAlpha() {
	return static_cast<char>(random() % ('z' - 'a') + 'a');
}

class MapTest : public ::testing::Test {
public:
	MapTest() {
		// код инициализации
		for (char ch = 'a'; ch < 'm'; ++ch) {
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
	mTree::leftLink(end, node10);
	mTree::rightLink(node10, node15);
	mTree::leftLink(node10, node20);
	mTree::rightLink(node20, node40);
	mTree::leftLink(node30, node40);
	mTree::rightLink(node40, node50);
	mTree::rightLink(node50, end);
	mTree::end::setRoot(end, node20);
	mTree::end::setFirst(end, node10);
	mTree::end::setLast(end, node50);

	printTree::print(end, 5);
	mMap::iterator		it(node10);
	mMap::iterator		ite(end);
	while (it != ite) {
		std::cout << it->first << '-' << it->second << std::endl;
		++it;
	}
	std::cout << std::endl;
	it = mMap::iterator(node50);
	while (it != ite) {
		std::cout << it->first << '-' << it->second << std::endl;
		--it;
	}

	std::cout << "ITE" << std::endl;
	--ite;
	std::cout << ite->first << '-' << ite->second << std::endl;
}

TEST_F(TreeTest, rotateRight1) {
	mTree *	nodeB = mTree::create(sTreeAlloc, sPairAlloc, pairs[1]);
	mTree *	nodeD = mTree::create(sTreeAlloc, sPairAlloc, pairs[3]);

	mTree::leftLink(nodeB, nodeD);

	mTree::end::setRoot(end, nodeD);
	mTree::end::setFirst(end, nodeB);
	mTree::end::setLast(end, nodeD);

	printTree::print(end, 3);
	mTree::rotateRight(mTree::end::getRoot(end));
	printTree::print(end, 3);
}

TEST_F(TreeTest, rotateRight2) {
	mTree *	nodeB = mTree::create(sTreeAlloc, sPairAlloc, pairs[1]);
	mTree *	nodeD = mTree::create(sTreeAlloc, sPairAlloc, pairs[3]);
	mTree *	nodeA = mTree::create(sTreeAlloc, sPairAlloc, pairs[0]);

	mTree::leftLink(nodeB, nodeD);
	mTree::leftLink(nodeA, nodeB);

	mTree::end::setRoot(end, nodeD);
	mTree::end::setFirst(end, nodeA);
	mTree::end::setLast(end, nodeD);

	printTree::print(end, 4);
	mTree::rotateRight(mTree::end::getRoot(end));
	printTree::print(end, 4);
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
	printTree::print(end, 4);

	const treePair	pair2 = mTree::insert(
		mTree::end::getRoot(end),
		pairs[2],
		comp(),
		sTreeAlloc,
		sPairAlloc
	);
	ASSERT_FALSE(pair2.second);
	ASSERT_EQ(mTree::getData(pair2.first), pairs[2]);
	printTree::print(end, 4);

	const treePair	pair3 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[0],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair3.second);
	ASSERT_EQ(mTree::getData(pair3.first), pairs[0]);
	printTree::print(end, 4);
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
	printTree::print(end, 4);
	const treePair	pair5 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[5],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair5.second);
	ASSERT_EQ(mTree::getData(pair5.first), pairs[5]);
	printTree::print(end, 4);
	const treePair	pair6 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[4],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair6.second);
	ASSERT_EQ(mTree::getData(pair6.first), pairs[4]);
	printTree::print(end, 4);
	const treePair	pair7 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[3],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair7.second);
	ASSERT_EQ(mTree::getData(pair7.first), pairs[3]);
	printTree::print(end, 4);
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
	printTree::print(end, 5);

	const treePair	pair1 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[1],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair1.second);
	ASSERT_EQ(mTree::getData(pair1.first), pairs[1]);
	printTree::print(end, 5);
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
	printTree::print(end, 5);
	const treePair	pair3 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[3],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair3.second);
	ASSERT_EQ(mTree::getData(pair3.first), pairs[3]);
	printTree::print(end, 5);
	const treePair	pair4 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[4],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair4.second);
	ASSERT_EQ(mTree::getData(pair4.first), pairs[4]);
	printTree::print(end, 5);
	const treePair	pair5 = mTree::insert(
			mTree::end::getRoot(end),
			pairs[5],
			comp(),
			sTreeAlloc,
			sPairAlloc
	);
	ASSERT_TRUE(pair5.second);
	ASSERT_EQ(mTree::getData(pair5.first), pairs[5]);
	printTree::print(end, 5);}

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

TEST_F(MapTest, crush) {
	for (int i = 0; i < 1000; ++i) {
		createTestsMapsAndStartInserts();
	}
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

TEST_F(MapTest, errase_basic) {
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
}