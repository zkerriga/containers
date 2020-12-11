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
#include "vector_iterators.hpp"
#include "utils.hpp"

namespace ft {

#define _ENABLE_INPUT_ITERATOR_TYPE(type_name) \
			typename std::enable_if< std::__is_input_iterator< type_name >::value,type_name >::type

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
	typedef _VectorIterator< value_type >			iterator;
	typedef _VectorConstIterator< value_type >		const_iterator;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	/* Initialize */
	explicit vector(const allocator_type & alloc = allocator_type())
		: m_array(nullptr), m_size(0),
		  m_capacity(mc_startCapacity), m_allocator(alloc)
	{
		m_array = m_allocator.allocate(m_capacity);
	}
	explicit vector(size_type n, const value_type & val = value_type(),
					const allocator_type & alloc = allocator_type())
		: m_array(nullptr), m_size(n),
		  m_capacity(n ? n : mc_startCapacity), m_allocator(alloc)
	{
		m_array = m_allocator.allocate(m_capacity);
		for (size_type i = 0; i < n; ++i) {
			m_allocator.construct(m_array + i, val);
		}
	}
	template < class InputIterator >
	vector(InputIterator first,
		   _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last,
		   const allocator_type & alloc = allocator_type())
		: m_array(nullptr), m_size(0),
		  m_capacity(mc_startCapacity), m_allocator(alloc)
	{
		m_array = m_allocator.allocate(m_capacity);
		while (first != last) {
			push_back(*first);
			++first;
		}
	}
	vector(const vector & x) : m_array(nullptr) {
		*this = x;
	}

	/* Member functions */
	~vector() {
		_MemWorker::fullDestruct(m_array, m_size, m_capacity, m_allocator);
	}
	vector & operator=(const vector & x) {
		if (this != &x) {
			if (m_array) {
				_MemWorker::fullDestruct(m_array, m_size, m_capacity, m_allocator);
			}
			m_allocator = x.m_allocator;
			m_capacity = x.m_capacity;
			m_size = x.m_size;
			m_array = m_allocator.allocate(m_capacity);
			for (size_type i = 0; i < m_size; ++i) {
				m_allocator.construct(m_array + i, *(x.m_array + i));
			}
		}
		return *this;
	}

	/* Iterators */
	iterator				begin() {
		return iterator(m_array);
	}
	const_iterator			begin() const {
		return const_iterator(m_array);
	}
	iterator				end() {
		return iterator(m_array + m_size);
	}
	const_iterator			end() const {
		return const_iterator(m_array + m_size);
	}
	reverse_iterator		rbegin() {
		return reverse_iterator(end());
	}
	const_reverse_iterator	rbegin() const {
		return const_reverse_iterator(end());
	}
	reverse_iterator		rend() {
		return reverse_iterator(begin());
	}
	const_reverse_iterator	rend() const {
		return const_reverse_iterator(begin());
	}

	/* Capacity */
	size_type		size() const _NOEXCEPT {
		return m_size;
	}
	size_type		max_size() const _NOEXCEPT {
		return (static_cast<size_type>(-1) / sizeof(value_type));
	}
	void			resize(size_type n, value_type val = value_type()) {
		if (n == m_size) {
			return;
		}
		if (n < m_size) {
			_MemWorker::destructElements(m_array + n, m_array + m_size, m_allocator);
		}
		else {
			if (n > m_capacity) {
				reserve(n);
			}
			for (size_type i = m_size; i < n; ++i) {
				push_back(val);
			}
		}
		m_size = n;
	}
	size_type		capacity() const _NOEXCEPT {
		return m_capacity;
	}
	bool			empty() const _NOEXCEPT {
		return (m_size == 0);
	}
	void			reserve(size_type n) {
		if (n > m_capacity) {
			m_array = _MemWorker::reallocate(
				m_array, m_size, m_capacity, n, m_allocator
			);
			m_capacity = n;
		}
	}

	/* Element access */
	reference			operator[](size_type n) _NOEXCEPT {
		return *(m_array + n);
	}
	const_reference		operator[](size_type n) const _NOEXCEPT {
		return *(m_array + n);
	}
	reference			at(size_type n) throw(std::out_of_range) {
		if (n >= m_size) {
			throw std::out_of_range("vector: incorrect index!");
		}
		return operator[](n);
	}
	const_reference		at(size_type n) const throw(std::out_of_range) {
		if (n >= m_size) {
			throw std::out_of_range("vector: incorrect index!");
		}
		return operator[](n);
	}
	reference			front() _NOEXCEPT {
		return *m_array;
	}
	const_reference		front() const _NOEXCEPT {
		return *m_array;
	}
	reference			back() _NOEXCEPT {
		return *(m_array + m_size - 1);
	}
	const_reference		back() const _NOEXCEPT {
		return *(m_array + m_size - 1);
	}

	/* Modifiers */
	template < class InputIterator >
	void		assign(InputIterator first,
					   _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last) {
		clear();
		while (first != last) {
			push_back(*first);
			++first;
		}
	}
	void		assign(size_type n, const value_type & val) {
		clear();
		reserve(n);
		for (size_type i = 0; i < n; ++i) {
			push_back(val);
		}
	}
	void		push_back(const value_type & val) {
		if (m_size == m_capacity) {
			reserve(m_capacity * 2);
		}
		m_allocator.construct(m_array + m_size, val);
		++m_size;
	}
	void		pop_back() {
		m_allocator.destroy(m_array + m_size - 1);
		--m_size;
	}
//	iterator	insert(iterator position, const value_type & val);
//	void		insert(iterator position, size_type n, const value_type & val);
//	template < class InputIterator >
//	void		insert(iterator position, InputIterator first, InputIterator last);
//	iterator	erase(iterator position);
//	iterator	erase(iterator first, iterator last);
	void		swap(vector & x) {
		ft::swap(m_allocator, x.m_allocator);
		ft::swap(m_capacity, x.m_capacity);
		ft::swap(m_size, x.m_size);
		ft::swap(m_array, x.m_array);
	}
	void		clear() _NOEXCEPT {
		_MemWorker::destructElements(m_array, m_array + m_size, m_allocator);
		m_size = 0;
	}

	/* Allocator */
	allocator_type	get_allocator() const {
		return m_allocator;
	}

private:
	value_type *			m_array;
	size_type				m_size;
	size_type				m_capacity;
	allocator_type			m_allocator;

	static const size_type	mc_startCapacity = 1;

}; //class vector


/* Non-member function overloads */
template < class T, class Alloc >
bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs) {
	typedef typename vector<T, Alloc>::const_iterator _iter;

	if (lhs.size() != rhs.size()) {
		return false;
	}
	_iter	lIt		= lhs.begin();
	_iter	lIte	= lhs.end();
	_iter	rIt		= rhs.begin();
	_iter	rIte	= rhs.end();
	while (lIt != lIte && rIt != rIte) {
		if (!(*lIt == *rIt)) {
			return false;
		}
		++rIt;
		++lIt;
	}
	return (lIt == lIte && rIt == rIte);
}

template < class T, class Alloc >
bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs) {
	return !operator==(lhs, rhs);
}

template < class T, class Alloc >
bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs) {
	typedef typename vector<T, Alloc>::const_iterator _iter;

	_iter	lIt		= lhs.begin();
	_iter	lIte	= lhs.end();
	_iter	rIt		= rhs.begin();
	_iter	rIte	= rhs.end();

	while (lIt != lIte && rIt != rIte) {
		if (*lIt < *rIt) {
			return true;
		}
		if (*rIt < *lIt) {
			return false;
		}
		++lIt;
		++rIt;
	}
	return (lIt == lIte && rIt != rIte);
}

template < class T, class Alloc >
bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs) {
	return (!operator<(rhs, lhs));
}

template < class T, class Alloc >
bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs) {
	return operator<(rhs, lhs);
}

template < class T, class Alloc >
bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc> & rhs) {
	return (!operator<(lhs, rhs));
}

template < class T, class Alloc >
void swap(vector<T,Alloc>& x, vector<T,Alloc> & y) {
	x.swap(y);
}

} //namespace ft
