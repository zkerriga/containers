/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:06:43 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/10 20:06:44 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <stdexcept>
#include <type_traits>

template < typename value_type >
class _VectorIterator : public std::iterator< std::random_access_iterator_tag,
											  value_type > {
	typedef std::iterator< std::random_access_iterator_tag,
						   value_type >						_stdIt;
	typedef typename _stdIt::difference_type				_difference_type;
	typedef typename _stdIt::pointer						_pointer;
	typedef typename _stdIt::reference						_reference;
public:
	_VectorIterator() : m_p(nullptr) {}
	_VectorIterator(const _VectorIterator & other) {
		*this = other;
	}
	~_VectorIterator() {}
	_VectorIterator&	operator= (const _VectorIterator & other) {
		if (this != &other) {
			m_p = other.m_p;
		}
		return *this;
	}

	explicit _VectorIterator(value_type * p) : m_p(p) {}

	_reference			operator* () const _NOEXCEPT {
		return *m_p;
	}
	_pointer				operator->() const _NOEXCEPT {
		return m_p;
	}

	_VectorIterator		operator+ (_difference_type n) const _NOEXCEPT {
		_VectorIterator		it(*this);

		it += n;
		return it;
	}
	_VectorIterator		operator- (_difference_type n) const _NOEXCEPT {
		return (*this + (-n));
	}
	_VectorIterator &	operator-=(_difference_type n) _NOEXCEPT {
		*this += -n;
		return *this;
	}
	_VectorIterator &	operator+=(_difference_type n) _NOEXCEPT {
		m_p += n;
		return *this;
	}
	_reference			operator[](_difference_type n) const _NOEXCEPT {
		return m_p[n];
	}

	bool				operator==(const _VectorIterator & other) const _NOEXCEPT {
		return (m_p == other.m_p);
	}
	bool				operator!=(const _VectorIterator & other) const _NOEXCEPT {
		return (m_p != other.m_p);
	}
	bool				operator< (const _VectorIterator & other) const _NOEXCEPT {
		return (m_p < other.m_p);
	}
	bool				operator> (const _VectorIterator & other) const _NOEXCEPT {
		return (m_p > other.m_p);
	}
	bool				operator>=(const _VectorIterator & other) const _NOEXCEPT {
		return (m_p >= other.m_p);
	}
	bool				operator<=(const _VectorIterator & other) const _NOEXCEPT {
		return (m_p <= other.m_p);
	}

	_VectorIterator &	operator++() _NOEXCEPT {
		++m_p;
		return *this;
	}
	_VectorIterator &	operator--() _NOEXCEPT {
		--m_p;
		return *this;
	}
	_VectorIterator		operator++(int) _NOEXCEPT {
		_pointer		tmp = m_p;
		operator++();
		return _VectorIterator(tmp);
	}
	_VectorIterator		operator--(int) _NOEXCEPT {
		_pointer		tmp = m_p;
		operator--();
		return _VectorIterator(tmp);
	}

private:
	_pointer		m_p;
}; //class _VectorIterator

template < typename value_type >
class _VectorConstIterator : public std::iterator< std::random_access_iterator_tag,
		value_type > {
	typedef std::iterator< std::random_access_iterator_tag,
						   value_type >						_stdIt;
	typedef typename _stdIt::difference_type				_difference_type;
	typedef typename _stdIt::pointer						_pointer;
	typedef typename _stdIt::reference						_reference;
	typedef _VectorIterator< value_type >					_MutableIterator;
public:
	_VectorConstIterator() : m_p(nullptr) {}
	_VectorConstIterator(const _VectorConstIterator & other) {
		*this = other;
	}
	~_VectorConstIterator() {}
	_VectorConstIterator&	operator= (const _VectorConstIterator & other) {
		if (this != &other) {
			m_p = other.m_p;
		}
		return *this;
	}

	explicit _VectorConstIterator(value_type * p) : m_p(p) {}

	_VectorConstIterator(const _MutableIterator & other) {
		*this = other;
	}
	_VectorConstIterator&	operator= (const _MutableIterator & other) {
		m_p = other.operator->();
		return *this;
	}

	_reference				operator* () const _NOEXCEPT {
		return *m_p;
	}
	_pointer				operator->() const _NOEXCEPT {
		return m_p;
	}

	_VectorConstIterator	operator+ (_difference_type n) const _NOEXCEPT {
		_VectorConstIterator		it(*this);

		it += n;
		return it;
	}
	_VectorConstIterator	operator- (_difference_type n) const _NOEXCEPT {
		return (*this + (-n));
	}
	_VectorConstIterator &	operator-=(_difference_type n) _NOEXCEPT {
		*this += -n;
		return *this;
	}
	_VectorConstIterator &	operator+=(_difference_type n) _NOEXCEPT {
		m_p += n;
		return *this;
	}
	_reference				operator[](_difference_type n) const _NOEXCEPT {
		return m_p[n];
	}

	bool					operator==(const _VectorConstIterator & other) const _NOEXCEPT {
		return (m_p == other.m_p);
	}
	bool					operator!=(const _VectorConstIterator & other) const _NOEXCEPT {
		return (m_p != other.m_p);
	}
	bool					operator< (const _VectorConstIterator & other) const _NOEXCEPT {
		return (m_p < other.m_p);
	}
	bool					operator> (const _VectorConstIterator & other) const _NOEXCEPT {
		return (m_p > other.m_p);
	}
	bool					operator>=(const _VectorConstIterator & other) const _NOEXCEPT {
		return (m_p >= other.m_p);
	}
	bool					operator<=(const _VectorConstIterator & other) const _NOEXCEPT {
		return (m_p <= other.m_p);
	}

	_VectorConstIterator &	operator++() _NOEXCEPT {
		++m_p;
		return *this;
	}
	_VectorConstIterator &	operator--() _NOEXCEPT {
		--m_p;
		return *this;
	}
	_VectorConstIterator	operator++(int) _NOEXCEPT {
		_pointer		tmp = m_p;
		operator++();
		return _VectorConstIterator(tmp);
	}
	_VectorConstIterator	operator--(int) _NOEXCEPT {
		_pointer		tmp = m_p;
		operator--();
		return _VectorConstIterator(tmp);
	}

private:
	_pointer		m_p;
}; //class _VectorConstIterator

template < class Iterator >
inline
typename std::enable_if<
	std::is_same<Iterator, _VectorIterator<typename Iterator::value_type> >::value
	|| std::is_same<Iterator, _VectorConstIterator<typename Iterator::value_type> >::value,
	Iterator>::type
operator+(typename Iterator::difference_type n, Iterator it) {
	it += n;
	return it;
}
