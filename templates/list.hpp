/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:55:16 by zkerriga          #+#    #+#             */
/*   Updated: 2020/11/26 10:55:18 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <type_traits>
#include <stdexcept>

#include "support/list_node.hpp"
#include "support/list_iterators.hpp"
#include "utils.hpp"

namespace ft {

#define _ENABLE_INPUT_ITERATOR_TYPE(type_name) \
			typename std::enable_if< std::__is_input_iterator<type_name>::value,type_name >::type

/*
 * Double-linked list.
 */
template < class T, class Alloc = std::allocator<T> >
class list {
public:
	typedef T								value_type;
	typedef Alloc							allocator_type;
	typedef typename Alloc::reference		reference;
	typedef typename Alloc::const_reference	const_reference;
	typedef typename Alloc::pointer			pointer;
	typedef typename Alloc::const_pointer	const_pointer;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;
private:
	typedef ListNode< value_type, allocator_type >		_lst;

public:
	/* Initialize */
	explicit list( const allocator_type & alloc = allocator_type() )
		: m_end(nullptr), m_size(0), m_allocator(alloc)
	{
		m_end = _lst::getNewNode(m_allocator);
	}
	explicit list( size_type n, const value_type & val = value_type(),
				const allocator_type & alloc = allocator_type() )
		: m_end(nullptr), m_size(n), m_allocator(alloc)
	{
		m_end = _lst::getNewNode(m_allocator);
		_lst::addBeforeNodeNIdenticalValue(n, m_end, val, m_allocator);
	}
	template < class InputIterator >
	list( InputIterator first,
		  _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last,
		  const allocator_type & alloc = allocator_type())
		: m_end(nullptr), m_size(0), m_allocator(alloc)
	{
		m_end = _lst::getNewNode(m_allocator);
		m_size = _lst::addBeforeNodeFromIterators(
			first,
			last,
			m_end,
			m_allocator
		);
	}
	list( const list & x )
		: m_end(nullptr), m_size(0), m_allocator(x.m_allocator)
	{
		m_end = _lst::getNewNode(m_allocator);
		m_size = _lst::addBeforeNodeFromIterators(
			x.begin(),
			x.end(),
			m_end,
			m_allocator
		);
	}
	~list() {
		_lst::safetyClearFullListWithoutEnd(m_end, m_allocator);
		_lst::destroyNode(m_end, m_allocator);
	}
	list & operator= ( const list& x ) {
		if (this != &x) {
			_lst::safetyClearFullListWithoutEnd(m_end, m_allocator);
			m_size = _lst::addBeforeNodeFromIterators(
				x.begin(),
				x.end(),
				m_end,
				m_allocator
			);
		}
		return *this;
	}

	/* Iterator classes */
	typedef _ListIterator< value_type,
						   allocator_type,
						   typename _lst::stepToNextType,
						   typename _lst::stepToPrevType >			iterator;
	typedef _ListConstIterator< value_type,
								allocator_type,
								typename _lst::stepToNextType,
								typename _lst::stepToPrevType >		const_iterator;
	typedef _ListIterator< value_type,
						   allocator_type,
						   typename _lst::stepToPrevType,
						   typename _lst::stepToNextType >			reverse_iterator;
	typedef _ListConstIterator< value_type,
								allocator_type,
								typename _lst::stepToPrevType,
								typename _lst::stepToNextType >		const_reverse_iterator;

	/* Iterators */
	iterator				begin() {
		return iterator(m_end->next);
	}
	const_iterator			begin() const {
		return const_iterator(m_end->next);
	}
	iterator				end() {
		return iterator(m_end);
	}
	const_iterator			end() const {
		return const_iterator(m_end);
	}
	reverse_iterator		rbegin() {
		return reverse_iterator(m_end->prev);
	}
	const_reverse_iterator	rbegin() const {
		return const_reverse_iterator(m_end->prev);
	}
	reverse_iterator		rend() {
		return reverse_iterator(m_end);
	}
	const_reverse_iterator	rend() const {
		return const_reverse_iterator(m_end);
	}

	/* Capacity */
	bool		empty() const _NOEXCEPT {
		return (m_size == 0);
	}
	size_type	size() const _NOEXCEPT {
		return m_size;
	}
	size_type	max_size() const _NOEXCEPT {
		return (static_cast<size_type>(-1) / sizeof(*m_end));
	}

	/* Element access */
	reference		front() _NOEXCEPT {
		return _lst::getDataReference(m_end->next);
	}
	const_reference	front() const _NOEXCEPT {
		return _lst::getDataReference(m_end->next);
	}
	reference		back() _NOEXCEPT {
		return _lst::getDataReference(m_end->prev);
	}
	const_reference	back() const _NOEXCEPT {
		return _lst::getDataReference(m_end->prev);
	}

	/* Modifiers */
	template < class InputIterator >
	void assign( InputIterator first,
				 _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last ) throw(std::bad_alloc) {
		_lst::safetyClearFullListWithoutEnd(m_end, m_allocator);
		m_size = _lst::addBeforeNodeFromIterators(
			first,
			last,
			m_end,
			m_allocator
		);
	}
	void assign( size_type n, const value_type & val ) throw(std::bad_alloc) {
		_lst::safetyClearFullListWithoutEnd(m_end, m_allocator);
		_lst::addBeforeNodeNIdenticalValue(n, m_end, val, m_allocator);
		m_size = n;
	}
	void push_front( const value_type & val ) throw(std::bad_alloc) {
		_lst::createAndInsertBetween(
			val,
			m_allocator,
			m_end,
			m_end->next
		);
		++m_size;
	}
	void pop_front() _NOEXCEPT {
		_lst * const	frontNode = _lst::drawNodeFromList(m_end->next);

		_lst::destroyNode(frontNode, m_allocator);
		--m_size;
	}
	void push_back( const value_type & val ) throw(std::bad_alloc) {
		_lst::createAndInsertBetween(
			val,
			m_allocator,
			m_end->prev,
			m_end
		);
		++m_size;
	}
	void pop_back() _NOEXCEPT {
		_lst * const	backNode = _lst::drawNodeFromList(m_end->prev);

		_lst::destroyNode(backNode, m_allocator);
		--m_size;
	}
	iterator insert( iterator position, const value_type & val ) {
		_lst * const	lastNode = position._getListNode();
		_lst::createAndInsertBetween(
			val,
			m_allocator,
			lastNode->prev,
			lastNode
		);
		++m_size;
		return iterator(lastNode->prev);
	}
	void insert( iterator position, size_type n, const value_type & val ) {
		_lst * const	lastNode = position._getListNode();

		_lst::addBeforeNodeNIdenticalValue(n, lastNode, val, m_allocator);
		m_size += n;
	}
	template < class InputIterator >
	void insert( iterator position, InputIterator first,
				 _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last ) {
		_lst * const	lastNode = position._getListNode();

		m_size += _lst::addBeforeNodeFromIterators(
			first,
			last,
			lastNode,
			m_allocator
		);
	}
	iterator erase( iterator position ) _NOEXCEPT {
		_lst * const	toDeleteNode = position._getListNode();
		_lst * const	nextNode = toDeleteNode->next;

		_lst::drawNodeFromList(toDeleteNode);
		_lst::destroyNode(toDeleteNode, m_allocator);
		--m_size;
		return iterator(nextNode);
	}
	iterator erase( iterator first, iterator last) _NOEXCEPT {
		_lst * const	itNode = first._getListNode();
		_lst * const	iteNode = last._getListNode();

		m_size -= _lst::safetyClearRangeBetweenNodes(
			itNode,
			iteNode,
			m_allocator
		);
		return last;
	}
	void swap( list & x ) _NOEXCEPT {
		ft::swap(m_allocator, x.m_allocator);
		ft::swap(m_end, x.m_end);
		ft::swap(m_size, x.m_size);
	}
	void resize( size_type n, value_type val = value_type() ) {
		if (n == m_size) {
			return;
		}
		else if (n < m_size) {
			_lst::safetyClearNLastNodes(m_size - n, m_end, m_allocator);
		}
		else {
			_lst::addBeforeNodeNIdenticalValue(
				n - m_size,
				m_end,
				val,
				m_allocator
			);
		}
		m_size = n;
	}
	void clear() _NOEXCEPT {
		_lst::safetyClearFullListWithoutEnd(m_end, m_allocator);
	}

	/* Operations */
	void splice( iterator position, list & x ) {
		splice(position, x, x.begin(), x.end());
	}
	void splice( iterator position, list & x, iterator i ) _NOEXCEPT {
		_lst * const	positionNode = position._getListNode();
		_lst * const	drawnNode = _lst::drawNodeFromList(i._getListNode());
		--x.m_size;

		_lst::insertBetween(
			drawnNode,
			positionNode->prev,
			positionNode
		);
		++m_size;
	}
	void splice( iterator position, list & x, iterator first, iterator last ) _NOEXCEPT {
		_lst * const	positionNode = position._getListNode();
		const size_type	movedSize = _lst::moveBeforeNodeFromNodesRange(
			positionNode,
			first._getListNode(),
			last._getListNode()
		);
		x.m_size -= movedSize;
		m_size += movedSize;
	}
	void remove( const value_type & val ) _NOEXCEPT {
		m_size -= _lst::deleteNodesFromListByEquate(
			val,
			m_end,
			m_allocator
		);
	}
	template < class Predicate >
	void remove_if( Predicate pred ) {
		m_size -= _lst::deleteNodesFromListByPredicate(
			pred,
			m_end,
			m_allocator
		);
	}
	void unique() {
		unique(_uniqueBinaryPredicate);
	}
	template < class BinaryPredicate >
	void unique( BinaryPredicate binary_pred ) {
		m_size -= _lst::deleteNodesFromListByBinaryPredicate(
			binary_pred,
			m_end,
			m_allocator
		);
	}
	/*void merge( list & x ) {
		if (this != &x) {
			merge(x, _defaultCompare);
		}
	}
	template < class Compare >
	void merge( list & x, Compare comp ) {
		if (this != &x) {

			m_size += x.m_size;
			x.m_size = 0;
		}
	}*/
//	void sort();
//	template <class Compare>
//	void sort( Compare comp );
	void reverse() {
		_lst::reverseFullList(m_end);
	}

	/* Observers */
	allocator_type get_allocator() const {
		return m_allocator;
	}

private:
	_lst *			m_end;
	size_type		m_size;
	allocator_type	m_allocator;

	static bool	_uniqueBinaryPredicate(const value_type & prev,
									   const value_type & curr) _NOEXCEPT {
		return (curr == prev);
	}
	static bool	_defaultCompare(const value_type & val1,
								const value_type & val2) _NOEXCEPT {
		return (val1 < val2);
	}
}; //class list

#undef _ENABLE_INPUT_ITERATOR_TYPE

/* todo */
template <class T, class Alloc>
bool operator == ( const list<T,Alloc> & lhs, const list<T,Alloc> & rhs );

template <class T, class Alloc>
bool operator != ( const list<T,Alloc> & lhs, const list<T,Alloc> & rhs );

template <class T, class Alloc>
bool operator <  ( const list<T,Alloc> & lhs, const list<T,Alloc> & rhs );

template <class T, class Alloc>
bool operator <= ( const list<T,Alloc> & lhs, const list<T,Alloc> & rhs );

template <class T, class Alloc>
bool operator >  ( const list<T,Alloc> & lhs, const list<T,Alloc> & rhs );

template <class T, class Alloc>
bool operator >= ( const list<T,Alloc> & lhs, const list<T,Alloc> & rhs );

template <class T, class Alloc>
void swap( list<T,Alloc> & x, list<T,Alloc> & y );
/* todo */

} //namespace ft
