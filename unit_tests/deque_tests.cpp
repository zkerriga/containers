#include "gtest/gtest.h"
#include <iterator>
#include <limits>
#include <deque>

#include "Any.hpp"

//#define DEBUG

#ifdef DEBUG
#define D(x) { x }
#else
#define D(x) {}
#endif //ifdef DEBUG

using sDec		= std::deque<Any>;
using mDec		= std::deque<Any>;

TEST(deque, test) {
	sDec	s1;
}

/*
template <class _ValueType, class _DiffType>
struct __deque_block_size {
  static const _DiffType value = sizeof(_ValueType) < 256 ? 4096 / sizeof(_ValueType) : 16;
};
*/
