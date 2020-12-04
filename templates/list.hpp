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
#include "support/list_node.hpp"
#include "support/list_iterators.hpp"

namespace ft {

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
	typedef ListNode<value_type,allocator_type>		_lst;

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
		_lst::addNIdenticalValue(n, m_end, val, m_allocator);
	}
	template < class InputIterator >
	list( InputIterator first,
		  typename std::enable_if< std::__is_input_iterator<InputIterator>::value,InputIterator >::type last,
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

	}
//	list& operator= ( const list& x );

	/* Iterator classes */
	typedef _listIterator< value_type, value_type, allocator_type,
						   typename _lst::stepToNextType,
						   typename _lst::stepToPrevType >			iterator;
	typedef _listIterator< value_type, const value_type, allocator_type,
						   typename _lst::stepToNextType,
						   typename _lst::stepToPrevType >			const_iterator;
	/* todo */
	class reverse_iterator {};
	class const_reverse_iterator {};
	/* todo */

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
//	reverse_iterator		rbegin();
//	const_reverse_iterator	rbegin() const;
//	reverse_iterator		rend();
//	const_reverse_iterator	rend() const;

	/* Capacity */
	bool		empty() const {
		return (m_size == 0);
	}
	size_type	size() const {
		return m_size;
	}
//	size_type	max_size() const;
//
//	 Element access
//	reference		front();
//	const_reference	front() const;
//	reference		back();
//	const_reference	back() const;

	/* Modifiers */
//	template <class InputIterator>
//	void assign( InputIterator first, InputIterator last );
//	void assign( size_type n, const value_type & val );
	void push_front( const value_type & val ) {
		_lst::createAndInsertBetween(
			val,
			m_allocator,
			m_end,
			m_end->next
		);
	}
//	void pop_front();
	void push_back( const value_type & val ) {
		_lst::createAndInsertBetween(
			val,
			m_allocator,
			m_end->prev,
			m_end
		);
	}
//	void pop_back();
//	iterator insert( iterator position, const value_type & val );
//	void insert( iterator position, size_type n, const value_type & val );
//	template <class InputIterator>
//	void insert( iterator position, InputIterator first, InputIterator last );
//	iterator erase( iterator position );
//	iterator erase( iterator first, iterator last);
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
