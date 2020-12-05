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

	static stepFunction	getStepFunction(stepToNextType) {
		return toNext;
	}
	static stepFunction	getStepFunction(stepToPrevType) {
		return toPrev;
	}

	static ListNode *	getNewNode(allocator_type & alloc) throw(std::bad_alloc) {
		ListNode *	node = static_cast<ListNode*>(operator new(1));

		node->data = alloc.allocate(1);
		setPrevNext(node, node, node);
		return node;
	}
	inline static void	setData(ListNode * targetNode, const value_type & value, allocator_type & alloc) {
		alloc.construct(targetNode->data, value);
	}
	inline static void	setPrevNext(ListNode * targetNode, ListNode * prevNode, ListNode * nextNode) {
		targetNode->prev = prevNode;
		targetNode->next = nextNode;
	}
	static ListNode *	setDataReturnNode(ListNode * targetNode, const value_type & value, allocator_type & alloc) {
		setData(targetNode, value, alloc);
		return targetNode;
	}
	inline static void	insertBetween(ListNode * insertingNode, ListNode * prevNode, ListNode * nextNode) {
		insertingNode->next = nextNode;
		insertingNode->prev = prevNode;
		prevNode->next = insertingNode;
		nextNode->prev = insertingNode;
	}
	static void			createAndInsertBetween(const value_type & value, allocator_type & alloc, ListNode * prevNode, ListNode * nextNode) {
		insertBetween(
			setDataReturnNode(
				getNewNode(alloc),
				value,
				alloc
			),
			prevNode,
			nextNode
		);
	}
	static void			addNIdenticalValue(const size_type n, ListNode * endNode, const value_type & value, allocator_type & alloc) {
		if (n == 0) {
			return;
		}
		createAndInsertBetween(
			value,
			alloc,
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
	inline static void	destroyNode(ListNode * node, allocator_type & alloc) {
		alloc.destroy(node->data);
		alloc.deallocate(node->data, 1);
		operator delete (node);
	}
	static ListNode *	destroyNodeAndGetNext(ListNode * node, allocator_type & alloc) {
		ListNode *	nextNode = node->next;

		destroyNode(node, alloc);
		return nextNode;
	}

private:
	inline static void	_clearListFromNode(ListNode * itNode, const ListNode * endNode,
												allocator_type & alloc) {
		if (itNode == endNode) {
			return;
		}
		_clearListFromNode(
			destroyNodeAndGetNext(itNode, alloc),
			endNode,
			alloc
		);
	}
public:
	static void			clearListWithoutEnd(ListNode * endNode, allocator_type & alloc) {
		_clearListFromNode(endNode->next, endNode, alloc);
		setPrevNext(endNode, endNode, endNode);
	}

private:
	template < class InputIterator >
	static size_type	_addBeforeNodeFromItWithAccumulator(const size_type n,
									InputIterator & it, const InputIterator & ite,
									ListNode * endNode, allocator_type & alloc) {
		if (it == ite) {
			return n;
		}
		createAndInsertBetween(
			*it++,
			alloc,
			endNode->prev,
			endNode
		);
		return _addBeforeNodeFromItWithAccumulator(n + 1, it, ite, endNode, alloc);
	}
public:
	/* Returns the number of added values */
	template < class InputIterator >
	static size_type	addBeforeNodeFromIterators(InputIterator it,
									const InputIterator ite, ListNode * endNode,
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
