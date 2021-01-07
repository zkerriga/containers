/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:03:02 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/06 16:03:04 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <type_traits>
#include <stdexcept>

#include "vector.hpp"
#include "list.hpp"
#include <vector> /* todo: change types to ft */
#include <list>

#include "deque_iterators.hpp"

namespace ft {

#define _ENABLE_INPUT_ITERATOR_TYPE(type_name) \
			typename std::enable_if< std::__is_input_iterator< type_name >::value,type_name >::type

template < class T, class Alloc = std::allocator<T> >
class deque {

public:
	typedef T										value_type;
	typedef Alloc									allocator_type;
	typedef typename Alloc::reference				reference;
	typedef typename Alloc::const_reference			const_reference;
	typedef typename Alloc::pointer					pointer;
	typedef typename Alloc::const_pointer			const_pointer;
	typedef std::ptrdiff_t							difference_type;
	typedef std::size_t								size_type;
private:
	typedef std::vector<value_type>					vector_type;
	typedef typename vector_type::iterator			vector_iterator;
	typedef typename vector_type::reverse_iterator	vector_reverse_iterator;
public:
	typedef DequeIterator<vector_type,value_type>	iterator;
	/* todo: iterators */
	typedef int										const_iterator;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
	/* todo: iterators */

	/* Initialize */
	explicit deque(const allocator_type & alloc = allocator_type())
		: m_direct(alloc), m_reverse(alloc) {}
	explicit deque(size_type n, const value_type & val = value_type(),
				   const allocator_type & alloc = allocator_type())
		: m_direct(n / 2, val, alloc), m_reverse(n - n / 2, val, alloc) {}
	template <class InputIterator>
	deque(InputIterator first, _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last,
		  const allocator_type & alloc = allocator_type())
		: m_direct(alloc), m_reverse(alloc)
	{
		while (first != last) {
			push_back(*first++);
		}
		_balance();
	}
	deque(const deque & x) : m_direct(x.m_direct), m_reverse(x.m_reverse) {}
	~deque() {}
	deque & operator= (const deque & x) {
		if (this != &x) {
			m_direct	= x.m_direct;
			m_reverse	= x.m_reverse;
		}
		return *this;
	}

	/* Iterators */
	iterator				begin() {
		return iterator(true, &m_direct, &m_reverse,
						m_direct.end(), m_reverse.rbegin());
	}
//	const_iterator			begin() const;
	iterator				end() {
		return iterator(false, &m_direct, &m_reverse,
						m_direct.end(), m_reverse.rend());
	}
//	const_iterator			end() const;
//	reverse_iterator		rbegin();
//	const_reverse_iterator	rbegin() const;
//	reverse_iterator		rend();
//	const_reverse_iterator	rend() const;

	/* Capacity */
	size_type	size() const {
		return (m_direct.size() + m_reverse.size());
	}
//	size_type	max_size() const;
//	void		resize(size_type n, value_type val = value_type());
	bool		empty() const {
		return (size() == 0);
	}

	/* Element access */
//	reference			operator[](size_type n);
//	const_reference		operator[](size_type n) const;
//	reference			at(size_type n);
//	const_reference		at(size_type n) const;
//	reference			front();
//	const_reference		front() const;
//	reference			back();
//	const_reference		back() const;

	/* Modifiers */
//	template <class InputIterator>
//	void		assign(InputIterator first, InputIterator last);
//	void		assign(size_type n, const value_type & val);
	void		push_back(const value_type & val) {
		m_direct.push_back(val);
	}
	void		push_front(const value_type & val) {
		m_reverse.push_back(val);
	}
//	void		pop_back();
//	void		pop_front();
//	iterator	insert(iterator position, const value_type & val);
//	void		insert(iterator position, size_type n, const value_type & val);
//	template <class InputIterator>
//	void		insert(iterator position, InputIterator first, InputIterator last);
//	iterator	erase(iterator position);
//	iterator	erase(iterator first, iterator last);
//	void		swap(deque & x);
//	void		clear();

	/* Allocator */
//	allocator_type	get_allocator() const;

private:
	vector_type				m_direct;	/* The end of the vector is the end   of the deque */
	vector_type				m_reverse;	/* The end of the vector is the begin of the deque */

	void		_balance() {
		static const size_type		fillCoefficient = 3;
		if (m_direct.size() > fillCoefficient * m_reverse.size()) {
			vector_reverse_iterator		rEnd	= m_direct.rend();
			const size_type				offset	= (m_direct.size() / fillCoefficient);
			vector_reverse_iterator		rBegin	= rEnd - offset;

			m_reverse.insert(m_reverse.begin(), rBegin, rEnd);
			m_direct.erase(m_direct.begin(), m_direct.begin() + offset);
		}
	}
}; //class deque

/* todo: operators */
template <class T, class Alloc>
bool operator==(const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator!=(const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator< (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<=(const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator> (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>=(const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);
/* todo: operators */

/* todo: swap */
template <class T, class Alloc>
void swap(deque<T,Alloc> & x, deque<T,Alloc> & y);
/* todo: swap */

#undef _ENABLE_INPUT_ITERATOR_TYPE

} //namespace ft
