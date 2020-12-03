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

	/* Initialize */
	explicit list( const allocator_type & alloc = allocator_type() )
		: m_end(_listNode::_createEmptyNode()), m_size(0), m_allocator(alloc)
	{
		_listNode::_createEmptyNode(m_allocator);
		_fillEndNode();
	}
	explicit list( size_type n, const value_type & val = value_type(),
				const allocator_type & alloc = allocator_type() )
		: m_end(_createEmptyNode()), m_size(n), m_allocator(alloc)
	{
		_fillEndNode();

		t_list *	node;
		for (size_type i = 0; i < n; ++i) {
			node = _createEmptyNode();
		}
	}
//	template < class InputIterator >
//	list( InputIterator first, InputIterator last,
//			const allocator_type & alloc = allocator_type() );
//	list( const list & x );
//	~list();
//	list& operator= ( const list& x );

	/* todo */
	/* Iterator classes */
	class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {};
	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T const> {};
	class reverse_iterator : public iterator {};
	class const_reverse_iterator : public const_iterator {};
	/* todo */

	/* Iterators */
//	iterator				begin();
//	const_iterator			begin() const;
//	iterator				end();
//	const_iterator			end() const;
//	reverse_iterator		rbegin();
//	const_reverse_iterator	rbegin() const;
//	reverse_iterator		rend();
//	const_reverse_iterator	rend() const;

	/* Capacity */
	bool		empty() const {
		return (m_size == 0);
	}
//	size_type	size() const;
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
//	void push_front( const value_type & val );
//	void pop_front();
//	void push_back( const value_type & val );
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
	struct t_list
	{
		value_type *	data;
		t_list *		next;
		t_list *		prev;
	};
	t_list *		m_end;
	size_type		m_size;
	allocator_type	m_allocator;

	class _listNode {
	public:
		value_type *	data;
		_listNode *			next;
		_listNode *			prev;

		static _listNode *	_createEmptyNode(allocator_type & alloc) {
			_listNode *	node = new _listNode;

			node->data = alloc.allocate(1);
			return node;
		}
	}; //class _listNode

	_listNode *		m_End;

	/*t_list *	_createEmptyNode() {
		t_list *	node = new t_list;

		node->data = m_allocator.allocate(1);
		return node;
	}*/
	void		_fillEndNode() {
		m_end->prev = m_end;
		m_end->next = m_end;
	}
	t_list *	_fillNode(t_list * targetNode, t_list * nextNode, t_list * prevNode, value_type const & value) {
		targetNode->data = value;
		targetNode->next = nextNode;
		targetNode->prev = prevNode;
	}
	t_list *	_nodePushBack(t_list *node) {}
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
