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

private:
	typedef ListNode		_NodesRange;
public:
	typedef void (*shiftFunction)(ListNode * &);
	typedef int stepToNextType;
	typedef char stepToPrevType;

	inline static
	shiftFunction	getShiftFunction(stepToNextType) _NOEXCEPT {
		return toNext;
	}
	inline static
	shiftFunction	getShiftFunction(stepToPrevType) _NOEXCEPT {
		return toPrev;
	}

	static
	ListNode *		getNewNode(allocator_type & alloc) throw(std::bad_alloc) {
		ListNode * const	node = static_cast<ListNode*>(operator new(1));

		node->data = alloc.allocate(1);
		setPrevNext(node, node, node);
		return node;
	}
	inline static
	void			setData(ListNode * const targetNode,
							const value_type & value,
							allocator_type & alloc) _NOEXCEPT {
		alloc.construct(targetNode->data, value);
	}
	inline static
	value_type &	getDataReference(ListNode * const node) _NOEXCEPT {
		return *(node->data);
	}
	inline static
	void			setPrevNext(ListNode * const targetNode,
								ListNode * const prevNode,
								ListNode * const nextNode) _NOEXCEPT {
		targetNode->prev = prevNode;
		targetNode->next = nextNode;
	}
	static
	ListNode *		setDataReturnNode(ListNode * const targetNode,
									  const value_type & value,
									  allocator_type & alloc) _NOEXCEPT {
		setData(targetNode, value, alloc);
		return targetNode;
	}
	inline static
	void			insertBetween(ListNode * const insertingNode,
								  ListNode * const prevNode,
								  ListNode * const nextNode) _NOEXCEPT {
		insertingNode->next = nextNode;
		insertingNode->prev = prevNode;
		prevNode->next = insertingNode;
		nextNode->prev = insertingNode;
	}
	static
	ListNode *		drawNodeFromList(ListNode * const drawingNode) _NOEXCEPT {
		ListNode * const	prevNode = drawingNode->prev;
		ListNode * const	nextNode = drawingNode->next;

		linkNodes(prevNode, nextNode);
		return drawingNode;
	}
	/*
	 * The function returns a pointer to the beginning of the drawn list
	 * with its end in prev.
	 */
	static
	_NodesRange *		drawNodesRangeFromList(ListNode * const startNode,
											   ListNode * const endNode) _NOEXCEPT {
		ListNode * const	beforeStartNode = startNode->prev;
		ListNode * const	lastRangeNode = endNode->prev;

		linkNodes(beforeStartNode, endNode);
		linkNodes(lastRangeNode, startNode);
		return startNode;
	}
	static
	void			createAndInsertBetween(const value_type & value,
										   allocator_type & alloc,
										   ListNode * const prevNode,
										   ListNode * const nextNode) throw(std::bad_alloc) {
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
	static
	void			addBeforeNodeNIdenticalValue(const size_type n,
												 ListNode * const endNode,
												 const value_type & value,
												 allocator_type & alloc) throw(std::bad_alloc) {
		if (n == 0) {
			return;
		}
		createAndInsertBetween(
			value,
			alloc,
			endNode->prev,
			endNode
		);
		addBeforeNodeNIdenticalValue(n - 1, endNode, value, alloc);
	}
	inline static
	void			toPrev(ListNode * & node) _NOEXCEPT {
		node = node->prev;
	};
	inline static
	void			toNext(ListNode * & node) _NOEXCEPT {
		node = node->next;
	};
	inline static
	void			destroyNode(ListNode * const node,
								allocator_type & alloc) _NOEXCEPT {
		alloc.destroy(node->data);
		alloc.deallocate(node->data, 1);
		operator delete (node);
	}
	static
	ListNode *		destroyNodeAndGetNext(ListNode * const node,
										  allocator_type & alloc) _NOEXCEPT {
		ListNode * const	nextNode = node->next;

		destroyNode(node, alloc);
		return nextNode;
	}
	static
	ListNode *		destroyNodeAndGetPrev(ListNode * const node,
										  allocator_type & alloc) _NOEXCEPT {
		ListNode * const	prevNode = node->prev;

		destroyNode(node, alloc);
		return prevNode;
	}
	inline static
	void			linkNodes(ListNode * const prevNode,
							  ListNode * const nextNode) {
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	}
	/* todo: make inline all single-string-functions */
	static
	size_type		getListSize(const ListNode * const endNode) {
		return _getListSizeWithAccumulator(0, endNode->next, endNode);
	}
private:
	static
	size_type		_getListSizeWithAccumulator(const size_type n,
												const ListNode * const startNode,
												const ListNode * const endNode) _NOEXCEPT {
		if (startNode == endNode) {
			return n;
		}
		return _getListSizeWithAccumulator(
			n + 1,
			startNode->next,
			endNode
		);
	}
	static
	size_type		_getNodesRangeSize(const _NodesRange * range) _NOEXCEPT {
		return _getListSizeWithAccumulator(1, range, range->prev);
	}
	static
	size_type		_clearListBetweenNodes(const size_type accumulator,
										   ListNode * const itNode,
										   const ListNode * const endNode,
										   allocator_type & alloc) _NOEXCEPT {
		if (itNode == endNode) {
			return accumulator;
		}
		return _clearListBetweenNodes(
				accumulator + 1,
				destroyNodeAndGetNext(itNode, alloc),
				endNode,
				alloc
		);
	}
	static
	ListNode *		_clearNPrevNodesAndGetLast(const size_type n,
											   ListNode * const currentNode,
											   allocator_type & alloc
											   ) _NOEXCEPT {
		if (n == 0) {
			return currentNode;
		}
		return _clearNPrevNodesAndGetLast(
			n - 1,
			destroyNodeAndGetPrev(currentNode, alloc),
			alloc
		);
	}

public:
	static
	size_type		moveBeforeNodeFromNodesRange(ListNode * const nodeToInsert,
												 ListNode * const startNode,
												 ListNode * const endNode) _NOEXCEPT {
		_NodesRange * const	drawnRange = drawNodesRangeFromList(
			startNode,
			endNode
		);
		const size_type		rangeSize = _getNodesRangeSize(drawnRange);
		ListNode * const	rangeStart = drawnRange;
		ListNode * const	rangeEnd = drawnRange->prev;

		linkNodes(nodeToInsert->prev, rangeStart);
		linkNodes(rangeEnd, nodeToInsert);
		return rangeSize;
	}

	static
	void			safetyClearNLastNodes(const size_type n,
										  ListNode * const endNode,
										  allocator_type & alloc) _NOEXCEPT {
		ListNode * const	lastAliveNode = _clearNPrevNodesAndGetLast(
			n,
			endNode->prev,
			alloc
		);
		linkNodes(lastAliveNode, endNode);
	}
	/* EndNode will not be deleted! */
	static
	size_type		safetyClearRangeBetweenNodes(ListNode * const startNode,
												 ListNode * const endNode,
												 allocator_type & alloc) _NOEXCEPT {
		ListNode * const	prevNode = startNode->prev;
		const size_type		deleteSize = _clearListBetweenNodes(
			0,
			startNode,
			endNode,
			alloc
		);
		linkNodes(prevNode, endNode);
		return deleteSize;
	}
	static
	void			safetyClearFullListWithoutEnd(ListNode * const endNode,
												  allocator_type & alloc) _NOEXCEPT {
		_clearListBetweenNodes(0, endNode->next, endNode, alloc);
		setPrevNext(endNode, endNode, endNode);
	}

private:
	template < class InputIterator >
	static
	size_type		_addBeforeNodeFromItWithAccumulator(const size_type n,
									InputIterator & it,
									const InputIterator & ite,
									ListNode * const endNode,
									allocator_type & alloc) throw(std::bad_alloc) {
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
	static
	size_type		addBeforeNodeFromIterators(InputIterator it,
											   const InputIterator ite,
											   ListNode * const endNode,
											   allocator_type & alloc) throw(std::bad_alloc) {
		return _addBeforeNodeFromItWithAccumulator(0, it, ite, endNode, alloc);
	}

#ifdef DEBUG
	inline static
	void			printNodeData(const ListNode * const node) _NOEXCEPT {
		std::cout << *(node->data) << ", ";
	}
	static
	void			printList(const ListNode * const itNode,
							  const ListNode * const endNode) _NOEXCEPT {
		if (itNode == endNode) {
			std::cout << "end" << std::endl;
			return;
		}
		printNodeData(itNode);
		return printList(itNode->next, endNode);
	}
#endif //DEBUG

private:
	void* operator new (std::size_t) throw(std::bad_alloc) {
		return ::operator new(sizeof(ListNode));
	}
};

std::ostream & operator<<(std::ostream & o,
						  const ListNode< int, std::allocator<int> > nodePtr) _NOEXCEPT {
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
