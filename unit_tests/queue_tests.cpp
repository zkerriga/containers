#include "gtest/gtest.h"
#include <vector>
#include <list>
#include <deque>
#include <queue>

#include "Any.hpp"

#define ANY Any(42)

#include "queue.hpp"

using sQu	= std::queue<Any>;
using mQu	=  ft::queue<Any>;

TEST(queue, test) {
	SUCCEED();
}

#undef ANY
