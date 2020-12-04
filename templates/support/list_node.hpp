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

#define DEBUG

#include <stdexcept>

template < typename value_type, typename allocator_type >
class ListNode {
public:
	value_type *	data;
	ListNode *		next;
	ListNode *		prev;

public:
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
	void* operator new (std::size_t size) throw (std::bad_alloc) {
		return ::operator new(size * sizeof(ListNode));
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
