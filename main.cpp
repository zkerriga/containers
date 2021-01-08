/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:52:02 by zkerriga          #+#    #+#             */
/*   Updated: 2020/11/26 10:52:04 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "vector.hpp"
#include "map.hpp"
#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"

#include "deque.hpp"
#include "set.hpp"

int main() {
	ft::list<int>					myList;
	ft::vector<int>					myVector;
	ft::map<char, int>				myMap;
	ft::stack< ft::vector<int> >	myStack;
	ft::queue< ft::vector<int> >	myQueue;

	ft::deque< int >				myDeque;
	ft::set<int>					mySet;

	std::cout << "\033[32m";
	std::cout << "All container constructors have been compiled!" << std::endl;
	std::cout << "Check the unit-tests to make sure they work ;)" << std::endl;
	std::cout << "\033[0m";
	return 0;
}
