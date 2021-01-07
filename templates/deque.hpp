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
	typedef DequeIterator<value_type>				iterator;
	typedef DequeConstIterator<value_type>			const_iterator;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

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
	iterator				begin() _NOEXCEPT {
		if (m_reverse.empty()) {
			return iterator(false, &m_direct, &m_reverse,
							m_direct.begin(), m_reverse.rend());
		}
		vector_reverse_iterator		rIt = m_reverse.rbegin();
		return iterator(true, &m_direct, &m_reverse,
						m_direct.end(), rIt);
	}
	const_iterator			begin() const _NOEXCEPT {
		if (m_reverse.empty()) {
			return iterator(false, &m_direct, &m_reverse,
							m_direct.begin(), m_reverse.rend());
		}
		typename vector_type::const_reverse_iterator	rIt = m_reverse.rbegin();
		return const_iterator(true, &m_direct, &m_reverse,
						m_direct.end(), rIt);
	}
	iterator				end() _NOEXCEPT {
		vector_iterator				it = m_direct.end();
		return iterator(false, &m_direct, &m_reverse,
						it, m_reverse.rend());
	}
	const_iterator			end() const _NOEXCEPT {
		typename vector_type::const_iterator	it = m_direct.end();
		return iterator(false, &m_direct, &m_reverse,
						it, m_reverse.rend());
	}
	reverse_iterator		rbegin() _NOEXCEPT {
		return reverse_iterator(end());
	}
	const_reverse_iterator	rbegin() const _NOEXCEPT {
		return const_reverse_iterator(end());
	}
	reverse_iterator		rend() _NOEXCEPT {
		return reverse_iterator(begin());
	}
	const_reverse_iterator	rend() const _NOEXCEPT {
		return const_reverse_iterator(begin());
	}

	/* Capacity */
	size_type	size() const _NOEXCEPT {
		return (m_direct.size() + m_reverse.size());
	}
	size_type	max_size() const _NOEXCEPT {
		return (static_cast<size_type>(-1) / sizeof(value_type));
	}
	void		resize(size_type n, value_type val = value_type()) {
		m_direct.insert(m_direct.begin(), m_reverse.rbegin(), m_reverse.rend());
		m_reverse.clear();
		m_direct.resize(n, val);
		_balance();
	}
	bool		empty() const _NOEXCEPT {
		return (size() == 0);
	}

	/* Element access */
	reference			operator[](size_type n) _NOEXCEPT {
		if (n < m_reverse.size()) {
			return m_reverse[m_reverse.size() - n - 1];
		}
		return m_direct[n - m_reverse.size()];
	}
	const_reference		operator[](size_type n) const _NOEXCEPT {
		if (n < m_reverse.size()) {
			return m_reverse[m_reverse.size() - n - 1];
		}
		return m_direct[n - m_reverse.size()];
	}
	reference			at(size_type n) {
		if (n >= size()) {
			throw std::out_of_range("Incorrect index!");
		}
		return operator[](n);
	}
	const_reference		at(size_type n) const {
		if (n >= size()) {
			throw std::out_of_range("Incorrect index!");
		}
		return operator[](n);
	}
	reference			front() {
		return (m_reverse.empty() ? m_direct.front() : m_reverse.back());
	}
	const_reference		front() const {
		return (m_reverse.empty() ? m_direct.front() : m_reverse.back());
	}
	reference			back() {
		return m_direct.back();
	}
	const_reference		back() const {
		return m_direct.back();
	}

	/* Modifiers */
	template <class InputIterator>
	void		assign(InputIterator first,
					   _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last) {
		clear();
		m_direct.assign(first, last);
		_balance();
	}
	void		assign(size_type n, const value_type & val) {
		clear();
		m_direct.assign(n / 2, val);
		m_reverse.assign(n - n / 2, val);
	}
	void		push_back(const value_type & val) {
		m_direct.push_back(val);
		_balance();
	}
	void		push_front(const value_type & val) {
		m_reverse.push_back(val);
		_balance();
	}
	void		pop_back() {
		m_direct.pop_back();
		_balance();
	}
	void		pop_front() {
		if (m_reverse.empty()) {
			m_direct.erase(m_direct.begin());
		}
		else {
			m_reverse.pop_back();
		}
		_balance();
	}
	iterator	insert(iterator position, const value_type & val) {
		difference_type		diff = position - begin();

		m_direct.insert(m_direct.begin(), m_reverse.rbegin(), m_reverse.rend());
		m_reverse.clear();
		m_direct.insert(m_direct.begin() + diff, val);
		_balance();
		return begin() + diff;
	}
	void		insert(iterator position, size_type n, const value_type & val) {
		difference_type		diff = position - begin();

		m_direct.insert(m_direct.begin(), m_reverse.rbegin(), m_reverse.rend());
		m_reverse.clear();
		m_direct.insert(m_direct.begin() + diff, n, val);
		_balance();
	}
	template <class InputIterator>
	void		insert(iterator position,
					   _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) first, InputIterator last) {
		difference_type		diff = position - begin();

		m_direct.insert(m_direct.begin(), m_reverse.rbegin(), m_reverse.rend());
		m_reverse.clear();
		m_direct.insert(m_direct.begin() + diff, first, last);
		_balance();
	}
//	iterator	erase(iterator position);
//	iterator	erase(iterator first, iterator last);
//	void		swap(deque & x);
	void		clear() {
		m_reverse.clear();
		m_direct.clear();
	}

	/* Allocator */
	allocator_type	get_allocator() const {
		return m_direct.get_allocator();
	}

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
