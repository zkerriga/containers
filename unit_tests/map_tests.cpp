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