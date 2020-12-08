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
		_lst::clearFullListWithoutEnd(m_end, m_allocator);
		_lst::destroyNode(m_end, m_allocator);
	}
	list & operator= ( const list& x ) {
		if (this != &x) {
			_lst::clearFullListWithoutEnd(m_end, m_allocator);
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
		_lst::clearFullListWithoutEnd(m_end, m_allocator);
		m_size = _lst::addBeforeNodeFromIterators(
			first,
			last,
			m_end,
			m_allocator
		);
	}
	void assign( size_type n, const value_type & val ) throw(std::bad_alloc) {
		_lst::clearFullListWithoutEnd(m_end, m_allocator);
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
//	void swap( list & x );
//	void resize( size_type n, value_type val = value_type() );
//	void clear();

	/* Operations */
//	void splice( iterator position, list & x );
//	void splice( iterator position, list & x, iterator i );
//	void splice( iterator position, list & x, iterator first, iterator last );
//	void remove( const value_type & val );
//	template <class Predicate>
//	void remove_if( Predicate pred );
//	void unique();
//	template <class BinaryPredicate>
//	void unique( BinaryPredicate binary_pred );
//	void merge( list & x );
//	template <class Compare>
//	void merge( list & x, Compare comp );
//	void sort();
//	template <class Compare>
//	void sort( Compare comp );
//	void reverse();

	/* Observers */
//	allocator_type get_allocator() const;

private:
	_lst *			m_end;
	size_type		m_size;
	allocator_type	m_allocator;

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
