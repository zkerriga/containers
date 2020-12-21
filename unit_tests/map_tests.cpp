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

TEST_F(MapTest, basic_iterators) {
	sMap::iterator					s1 = sAlpha.begin();
	sMap::const_iterator			s2 = s1;
	sMap::reverse_iterator			s3 = sAlpha.rbegin();
	sMap::const_reverse_iterator	s4 = s3;

	mMap::iterator					m1 = mAlpha.begin();
	mMap::const_iterator			m2 = m1;
	mMap::reverse_iterator			m3 = mAlpha.rbegin();
	mMap::const_reverse_iterator	m4 = m3;
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