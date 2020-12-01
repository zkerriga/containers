#include "gtest/gtest.h"
#include "list.hpp"
#include <list>
#include <vector>

#define INT_VALUE 1232349
#define SIZE_T_VALUE 9000000000
#define FLOAT_VALUE 128.512f
#define STRING_VALUE "Super string!"

using sList = std::list<int>;

class ListTestClass: public ::testing::Test {
public:
	ListTestClass() {
		// код инициализации
		for (int i = 0; i < 10; ++i) {
			sTenList.push_front(i);
		}
		for (int i = 100; i > 0; --i) {
			sLongList.push_front(i);
		}
		srand(time(nullptr));
		int size = rand() % 100 + 1;
		for (int i = 0; i < size; ++i) {
			sRandomList.push_front(rand());
		}
	}

	virtual void SetUp() {
		// код, который будет выполнен перед началом теста
	}

	virtual void TearDown() {
		// код, который будет выполнен сразу по завершении теста
		// при необходимости здесь можно вызывать исключения
	}

	~ListTestClass()  {
		// очистка всех ресурсов, вызов исключений не допускается
		sEmptyList.clear();
		sTenList.clear();
		sLongList.clear();
		sRandomList.clear();
	}

	// сюда можно поместить необходимые вам пользовательские объекты данных
	sList				sEmptyList;
	sList				sTenList;
	sList				sLongList;
	sList				sRandomList;
	sList::iterator		sIt;
	sList::iterator		sIte;
};

TEST_F(ListTestClass, basic) {

}







/*
TEST(list, basic_creation_list) {
	std::list<int>			l1;
	ft::list<int>			my1;

	std::list<std::string>	l2;
	ft::list<std::string>	my2;

	std::list<float>		l3;
	ft::list<float>			my3;
}

TEST(list, types) {

	std::list<int>::value_type		s1 = INT_VALUE;
	std::cout << s1 << std::endl;
	ft::list<int>::value_type		m1 = INT_VALUE;
	std::cout << m1 << std::endl;

	std::list<float>::value_type	s2 = FLOAT_VALUE;
	std::cout << s2 << std::endl;
	ft::list<float>::value_type		m2 = FLOAT_VALUE;
	std::cout << m2 << std::endl;

	std::list<int>::allocator_type			s3;
	std::list<int>::reference				s4();
	std::list<int>::const_reference			s5();
	std::list<int>::pointer					s6;
	std::list<int>::const_pointer			s7;
	std::list<int>::iterator				s8;
	std::list<int>::const_iterator			s9;
	std::list<int>::reverse_iterator		s10;
	std::list<int>::const_reverse_iterator	s11;
	std::list<int>::difference_type			s12;
	std::list<int>::size_type				s13 = SIZE_T_VALUE;
	std::cout << s13 << std::endl;

	ft::list<int>::allocator_type			m3;
	ft::list<int>::reference				m4();
	ft::list<int>::const_reference			m5();
	ft::list<int>::pointer					m6;
	ft::list<int>::const_pointer			m7;
	ft::list<int>::iterator					m8;
	ft::list<int>::const_iterator			m9;
	ft::list<int>::reverse_iterator			m10;
	ft::list<int>::const_reverse_iterator	m11;
	ft::list<int>::difference_type			m12;
	ft::list<int>::size_type				m13 = SIZE_T_VALUE;
	std::cout << m13 << std::endl;
}

std::vector<int> const	g_vec(10, INT_VALUE);

TEST(list, construct_basic) {
	std::list<int>	s1(std::allocator<int>);
	std::list<int>	s2(10);
	std::list<int>	s3(10, INT_VALUE);
	std::list<int>	s4(10, INT_VALUE, std::allocator<int>());
	std::list<int>	s5(g_vec.begin(), g_vec.end());
	std::list<int>	s6(g_vec.begin(), g_vec.end(), std::allocator<int>());
	std::list<int>	s7(s2);

	ft::list<int>	m1(std::allocator<int>);
	ft::list<int>	m2(10);
	ft::list<int>	m3(10, INT_VALUE);
	ft::list<int>	m4(10, INT_VALUE, std::allocator<int>());
	ft::list<int>	m5(g_vec.begin(), g_vec.end());
	ft::list<int>	m6(g_vec.begin(), g_vec.end(), std::allocator<int>());
	ft::list<int>	m7(m2);
	ASSERT_EQ(1,3);
}

//using list_containter = std::list<int>;

TEST(list, destructor_basic) {
	std::list<int> *	s1 = new std::list<int>(10, INT_VALUE);
	delete s1;

	ft::list<int> *		m1 = new ft::list<int>(10, INT_VALUE);
	delete m1;
}

TEST(list, assigment_basic) {
	std::list<int>		s1(10, INT_VALUE);
	std::list<int>		s2;
	s2 = s1;

	ft::list<int>		m1(10, INT_VALUE);
	ft::list<int>		m2;
	m2 = m1;
}

TEST(list, push_front_basic) {
	std::list<int>	s1;

	s1.push_front(INT_VALUE);
	s1.push_front(INT_VALUE + 1);

	ft::list<int>	m1;

	m1.push_front(INT_VALUE);
	m1.push_front(INT_VALUE + 1);
}
*/