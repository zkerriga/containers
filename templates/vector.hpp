/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:28:15 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/10 13:28:16 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <type_traits>
#include <stdexcept>

#include "vector_mem_worker.hpp"

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector {
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
	typedef MemoryWorker< value_type,
						  allocator_type,
						  size_type >		_MemWorker;
public:
	/* todo */
	class iterator {};
	class const_iterator {};
	class reverse_iterator {};
	class const_reverse_iterator {};
	/* todo */

	/* Initialize */
	explicit vector(const allocator_type & alloc = allocator_type())
		: m_array(nullptr), m_size(0),
		  m_capacity(mc_startCapacity), m_allocator(alloc)
	{
		m_array = m_allocator.allocate(m_capacity);
	}
//	explicit vector(size_type n, const value_type & val = value_type(),
//					const allocator_type & alloc = allocator_type());
//	template < class InputIterator >
//	vector(InputIterator first, InputIterator last,
//		   const allocator_type & alloc = allocator_type());
//	vector(const vector & x);

	/* Member functions */
//	~vector();
//	vector& operator=(const vector & x);

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
	size_type		size() const {
		return m_size;
	}
//	size_type		max_size() const;
//	void			resize(size_type n, value_type val = value_type());
	size_type		capacity() const {
		return m_capacity;
	}
//	bool			empty() const;
	void			reserve(size_type n) {
		if (n > m_capacity) {
			m_array = _MemWorker::reallocate(
				m_array, m_size, m_capacity, n, m_allocator
			);
			m_capacity = n;
		}
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
//	template < class InputIterator >
//	void		assign(InputIterator first, InputIterator last);
//	void		assign(size_type n, const value_type & val);
	void		push_back(const value_type & val) {
		if (m_size == m_capacity) {
			reserve(m_capacity * 2);
		}
		m_allocator.construct(m_array + m_size, val);
		++m_size;
	}
//	void		pop_back();
//	iterator	insert(iterator position, const value_type & val);
//	void		insert(iterator position, size_type n, const value_type & val);
//	template < class InputIterator >
//	void		insert(iterator position, InputIterator first, InputIterator last);
//	iterator	erase(iterator position);
//	iterator	erase(iterator first, iterator last);
//	void		swap(vector & x);
//	void		clear();

	/* Allocator */
//	allocator_type	get_allocator() const;

private:
	value_type *			m_array;
	size_type				m_size;
	size_type				m_capacity;
	allocator_type			m_allocator;

	static const size_type	mc_startCapacity = 1;

}; //class vector

/* todo */
/* Non-member function overloads */
template < class T, class Alloc >
bool operator == (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs);

template < class T, class Alloc >
bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs);

template < class T, class Alloc >
bool operator <  (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs);

template < class T, class Alloc >
bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs);

template < class T, class Alloc >
bool operator >  (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs);

template < class T, class Alloc >
bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs);
/* todo */

template < class T, class Alloc >
void swap(vector<T,Alloc>& x, vector<T,Alloc> & y);

/* todo: vector<bool> ???? */

} //namespace ft
