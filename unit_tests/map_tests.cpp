#include "gtest/gtest.h"
#include <map>
#include <iterator>
#include <limits>
#include <algorithm>

#include "Any.hpp"
#include "map.hpp"

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
//using sAlloc	= std::allocator<Any>;

class MapTest : public ::testing::Test {
public:
	MapTest() {
		// код инициализации
		for (char ch = 'a'; ch < 'm'; ++ch) {
			sAlpha[ch] = Any(ch);
//			mAlpha[ch] = Any(ch);
		}
	}
	virtual void SetUp() {
		// код, который будет выполнен перед началом теста
		const int	seed = static_cast<int>(time(nullptr));
		std::srand(seed);
		const int	size = std::rand() % 50 + 1;
		char		randChar;
		std::cout << "Seed = " << seed << std::endl;
		for (int i = 0; i < size; ++i) {
			randChar = getRandPrintable();
			sRando[randChar] = Any(randChar);
//			mRando[randChar] = Any(randChar);
		}
	}
	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}
	~MapTest() {
		// очистка всех ресурсов, вызов исключений не допускается
	}
	inline static char	getRandPrintable() {
		return static_cast<char>(rand() % ('z' - 'a') + 'a');
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
//	mMap::const_iterator	mIt		= mM.begin();
//	mMap::const_iterator	mIte	= mM.end();

//	ASSERT_EQ((sIt == sIte), (mIt == mIte));
//	while (sIt != sIte && mIt != mIte) {
//		EXPECT_EQ(*sIt, *mIt);
//		++sIt;
//		++mIt;
//	}
//	ASSERT_EQ((sIt == sIte), (mIt == mIte));
}

bool cmp(const sMap::value_type &, const sMap::value_type &) {
	return true;
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

TEST(map, tree_steps) {
	typedef TreeNode< int >		_tree;
	std::allocator<_tree>		sAl;
	int n20 = 20;
	int n10 = 10;
	int n15 = 15;
	int n40 = 40;
	int n30 = 30;
	int n50 = 50;

	_tree *		end = _tree::createEndNode(sAl.allocate(1));
	_tree *		node20 = _tree::createNode(sAl.allocate(1), n20);
	_tree *		node10 = _tree::createNode(sAl.allocate(1), n10);
	_tree *		node15 = _tree::createNode(sAl.allocate(1), n15);
	_tree *		node40 = _tree::createNode(sAl.allocate(1), n40);
	_tree *		node30 = _tree::createNode(sAl.allocate(1), n30);
	_tree *		node50 = _tree::createNode(sAl.allocate(1), n50);

	_tree::leftLink(end, node10);
	_tree::rightLink(node10, node15);
	_tree::leftLink(node10, node20);

	_tree::rightLink(node20, node40);
	_tree::leftLink(node30, node40);
	_tree::rightLink(node40, node50);

	_tree::rightLink(node50, end);
	end->parent = node20;

	_tree *		next = node10;
	while (next != end) {
		std::cout << *next->data << std::endl;
		next = _tree::iterateNode(next, _tree::step::right, _tree::step::left);
	}
	std::cout << std::endl;
	_tree *		prev = node50;
	while (prev != end) {
		std::cout << *prev->data << std::endl;
		prev = _tree::iterateNode(prev, _tree::step::left, _tree::step::right);
	}
}

TEST(map, iterator_basic) {
	typedef TreeNode< std::pair<const char, Any> >	_tree;
	std::allocator<_tree>						sAl;
	const char	chArr[]		= {'a', 'b', 'c', 'd', 'e', 'f'};
	Any		anyArr[]	= {Any(chArr[0]), Any(chArr[1]), Any(chArr[2]),
						   Any(chArr[3]), Any(chArr[4]), Any(chArr[5])};

	std::pair< const char, Any >	pairs[] = {
			std::make_pair(chArr[0], anyArr[0]),
			std::make_pair(chArr[1], anyArr[1]),
			std::make_pair(chArr[2], anyArr[2]),
			std::make_pair(chArr[3], anyArr[3]),
			std::make_pair(chArr[4], anyArr[4]),
			std::make_pair(chArr[5], anyArr[5])
	};

	_tree *		end = _tree::createEndNode(sAl.allocate(1));
	_tree *		node20 = _tree::createNode(sAl.allocate(1), pairs[2]);
	_tree *		node10 = _tree::createNode(sAl.allocate(1), pairs[0]);
	_tree *		node15 = _tree::createNode(sAl.allocate(1), pairs[1]);
	_tree *		node40 = _tree::createNode(sAl.allocate(1), pairs[4]);
	_tree *		node30 = _tree::createNode(sAl.allocate(1), pairs[3]);
	_tree *		node50 = _tree::createNode(sAl.allocate(1), pairs[5]);
	_tree::leftLink(end, node10);
	_tree::rightLink(node10, node15);
	_tree::leftLink(node10, node20);
	_tree::rightLink(node20, node40);
	_tree::leftLink(node30, node40);
	_tree::rightLink(node40, node50);
	_tree::rightLink(node50, end);
	end->parent = node20;
	end->left = node10;
	end->right = node50;

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
//	assertMapEQ(sAlpha, mAlpha);
//	assertMapEQ(sRando, mRando);
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