/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:22:16 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/04 10:22:18 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//#define DEBUG

#include <stdexcept>
#include <list>
template < typename value_type, typename allocator_type >
class ListNode {
public:
	typedef std::size_t		size_type;

	value_type *	data;
	ListNode *		next;
	ListNode *		prev;

public:
	typedef void (*stepFunction)(ListNode * &);
	typedef int stepToNextType;
	typedef char stepToPrevType;

	static ListNode *	getNewNode(allocator_type & alloc) throw(std::bad_alloc) {
		ListNode *	node = static_cast<ListNode*>(operator new(1));

		node->data = alloc.allocate(1);
		node->prev = node;
		node->next = node;
		return node;
	}
	inline static void	setData(ListNode * targetNode, const value_type & value) {
		*(targetNode->data) = value;
	}
	static ListNode *	setDataReturnNode(ListNode * targetNode, const value_type & value) {
		setData(targetNode, value);
		return targetNode;
	}
	inline static void	insertBetween(ListNode * insertingNode, ListNode * prevNode, ListNode * nextNode) {
		insertingNode->next = nextNode;
		insertingNode->prev = prevNode;
		prevNode->next = insertingNode;
		nextNode->prev = insertingNode;
	}
	static void			addNIdenticalValue(const size_type n, ListNode * endNode, const value_type & value, allocator_type & alloc) throw(std::bad_alloc) {
		if (n == 0) {
			return;
		}
		insertBetween(
			setDataReturnNode(
				getNewNode(alloc),
				value
			),
			endNode,
			endNode->next
		);
		addNIdenticalValue(n - 1, endNode, value, alloc);
	}
	inline static void	toPrev(ListNode * & node) {
		node = node->prev;
	};
	inline static void	toNext(ListNode * & node) {
		node = node->next;
	};
	static stepFunction	getStepFunction(stepToNextType) {
		return toNext;
	}
	static stepFunction	getStepFunction(stepToPrevType) {
		return toPrev;
	}

private:
	template < class InputIterator >
	static size_type	_addBeforeNodeFromItWithAccumulator(const size_type n,
									InputIterator & it, const InputIterator & ite,
									ListNode * endNode, allocator_type & alloc) {
		if (it == ite) {
			return 0;
		}
		insertBetween(
			setDataReturnNode(
				getNewNode(alloc),
				*it++
			),
			endNode->prev,
			endNode
		);
		return _addBeforeNodeFromItWithAccumulator(n + 1, it, ite, endNode, alloc);
	}
public:
	/* Returns the number of added values */
	template < class InputIterator >
	static size_type	addBeforeNodeFromIterators(InputIterator & it,
									const InputIterator & ite, ListNode * endNode,
									allocator_type & alloc) {
		return _addBeforeNodeFromItWithAccumulator(0, it, ite, endNode, alloc);
	}

#ifdef DEBUG
	inline static void	printNodeData(const ListNode *node) {
		std::cout << *(node->data) << ", ";
	}
	static void			printList(const ListNode * itNode, const ListNode * endNode) {
		if (itNode == endNode) {
			std::cout << "end" << std::endl;
			return;
		}
		printNodeData(itNode);
		return printList(itNode->next, endNode);
	}
#endif //DEBUG

private:
	void* operator new (std::size_t) throw (std::bad_alloc) {
		return ::operator new(sizeof(ListNode));
	}
};

std::ostream & operator<<(std::ostream & o, ListNode< int, std::allocator<int> > nodePtr) {
	o << "Node {" << std::endl;
	o << "	data = ";
	(nodePtr.data)
		? o << *nodePtr.data
		: o << nodePtr.data;
	o << std::endl;
	o << "	prev = " << nodePtr.prev << std::endl;
	o << "	next = " << nodePtr.next << std::endl;
	o << "}";
	return o;
}

#undef DEBUG
