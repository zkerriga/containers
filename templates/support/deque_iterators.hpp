/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_iterators.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:07:51 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/07 15:07:52 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

template <typename value_type>
class DequeConstIterator;

template <typename value_type>
class DequeIterator : public std::iterator<std::random_access_iterator_tag,value_type> {
	typedef std::iterator<std::random_access_iterator_tag,value_type>	_stdIt;
	typedef typename _stdIt::difference_type							_difference_type;
	typedef typename _stdIt::pointer									_pointer;
	typedef typename _stdIt::reference									_reference;
	typedef std::vector<value_type>										vector_type;
	typedef typename vector_type::iterator								_directIt;
	typedef typename vector_type::reverse_iterator						_reverseIt;
public:
	DequeIterator() {}
	DequeIterator(const DequeIterator & x) {
		*this = x;
	}
	virtual ~DequeIterator() {}
	DequeIterator & operator= (const DequeIterator & x) {
		if (this != &x) {
			m_isReverse = x.m_isReverse;
			m_dIt = x.m_dIt;
			m_rIt = x.m_rIt;
			m_direct = x.m_direct;
			m_reverse = x.m_reverse;
		}
		return *this;
	}

	DequeIterator(const bool isReverse, vector_type * direct,
				  vector_type * reverse, _directIt dIt, _reverseIt rIt)
		: m_isReverse(isReverse), m_direct(direct), m_reverse(reverse),
		  m_dIt(dIt), m_rIt(rIt) {}

	_reference			operator* () const {
		return (m_isReverse ? *m_rIt : *m_dIt);
	}
	_pointer			operator->() const {
		return (m_isReverse ? m_rIt.operator->() : m_dIt.operator->());
	}

	_reference			operator[](_difference_type n) const {
		DequeIterator	tmp(*this);
		tmp += n;
		return *tmp;
	}
	DequeIterator		operator+ (_difference_type n) const {
		DequeIterator	it(*this);

		it += n;
		return it;
	}
	DequeIterator		operator- (_difference_type n) const {
		DequeIterator	it(*this);

		it -= n;
		return it;
	}

	DequeIterator &		operator++() {
		if (m_isReverse) {
			++m_rIt;
			if (m_rIt == m_reverse->rend()) {
				m_dIt = m_direct->begin();
				m_isReverse = false;
			}
		}
		else {
			++m_dIt;
		}
		return *this;
	}
	DequeIterator		operator++(int) {
		DequeIterator	save(*this);

		operator++();
		return save;
	}
	DequeIterator &		operator--() {
		if (m_isReverse) {
			--m_rIt;
		}
		else {
			if (m_dIt == m_direct->begin()) {
				m_rIt = m_reverse->rbegin();
				m_isReverse = true;
			}
			else {
				--m_dIt;
			}
		}
		return *this;
	}
	DequeIterator		operator--(int) {
		DequeIterator	save(*this);

		operator--();
		return save;
	}

	DequeIterator &		operator+=(_difference_type n) {
		if (n > 0) {
			if (m_isReverse) {
				const _difference_type	diff1 = m_reverse->rend() - m_rIt;
				if (diff1 > n + 1) {
					m_rIt += n;
				}
				else {
					m_isReverse = false;
					m_dIt = m_direct->begin() + n - diff1;
				}
			}
			else {
				m_dIt += n;
			}
		}
		else {
			if (m_isReverse) {
				m_rIt += n;
			}
			else {
				const _difference_type	diff2 = m_dIt - m_direct->begin();
				if (diff2 > -n) {
					m_dIt += n;
				}
				else {
					m_isReverse = true;
					m_rIt = m_reverse->rbegin() + (diff2 + n);
				}
			}
		}
		return *this;
	}
	DequeIterator &		operator-=(_difference_type n) {
		*this += -n;
		return *this;
	}

	inline bool			operator==(const DequeIterator & other) const {
		return (m_isReverse == other.m_isReverse
			&& (m_isReverse ? m_rIt == other.m_rIt : m_dIt == other.m_dIt));
	}
	inline bool			operator!=(const DequeIterator & other) const {
		return !operator==(other);
	}
	inline bool			operator< (const DequeIterator & other) const {
		if (m_isReverse && !other.m_isReverse) {
			return true;
		}
		if (!m_isReverse && other.m_isReverse) {
			return false;
		}
		if (m_isReverse) {
			return std::operator<(m_rIt, other.m_rIt);
		}
		return std::operator<(m_dIt, other.m_dIt);
	}
	inline bool			operator> (const DequeIterator & other) const {
		return other.operator<(*this);
	}
	inline bool			operator<=(const DequeIterator & other) const {
		return !operator>(other);
	}
	inline bool			operator>=(const DequeIterator & other) const {
		return !operator<(other);
	}

	friend class DequeConstIterator<value_type>;
	friend
	DequeIterator		operator+(_difference_type n, const DequeIterator & it) {
		return it + n;
	}
	friend
	_difference_type		operator-(const DequeIterator & x, const DequeIterator & y) {
		if (x.m_isReverse == y.m_isReverse) {
			return (x.m_isReverse ? (x.m_rIt - y.m_rIt) : (x.m_dIt - y.m_dIt));
		}
		if (x.m_isReverse) {
			return -((x.m_reverse->rend() - x.m_rIt) + (y.m_dIt - y.m_direct->begin()));
		}
		return (x.m_dIt - x.m_direct->begin()) + (y.m_reverse->rend() - y.m_rIt);
	}

private:
	bool			m_isReverse;
	_directIt		m_dIt;
	_reverseIt		m_rIt;
	vector_type *	m_direct;
	vector_type *	m_reverse;
};

template <typename value_type>
class DequeConstIterator : public std::iterator<std::random_access_iterator_tag,const value_type> {
	typedef std::iterator<std::random_access_iterator_tag,const value_type>	_stdIt;
	typedef typename _stdIt::difference_type								_difference_type;
	typedef typename _stdIt::pointer										_pointer;
	typedef typename _stdIt::reference										_reference;
	typedef std::vector<value_type>											vector_type;
	typedef typename vector_type::const_iterator							_directIt;
	typedef typename vector_type::const_reverse_iterator					_reverseIt;
public:
	DequeConstIterator() {}
	DequeConstIterator(const DequeConstIterator & x) {
		*this = x;
	}
	virtual ~DequeConstIterator() {}
	DequeConstIterator & operator= (const DequeConstIterator & x) {
		if (this != &x) {
			m_isReverse = x.m_isReverse;
			m_dIt = x.m_dIt;
			m_rIt = x.m_rIt;
			m_direct = x.m_direct;
			m_reverse = x.m_reverse;
		}
		return *this;
	}

	DequeConstIterator(const DequeIterator<value_type> & x) {
		*this = x;
	}
	DequeConstIterator & operator= (const DequeIterator<value_type> & x) {
		m_isReverse = x.m_isReverse;
		m_dIt = x.m_dIt;
		m_rIt = x.m_rIt;
		m_direct = x.m_direct;
		m_reverse = x.m_reverse;
		return *this;
	}

	DequeConstIterator(const bool isReverse, const vector_type * direct,
					   const vector_type * reverse, _directIt dIt, _reverseIt rIt)
		: m_isReverse(isReverse), m_direct(direct), m_reverse(reverse),
		  m_dIt(dIt), m_rIt(rIt) {}

	_reference				operator* () const {
		return (m_isReverse ? *m_rIt : *m_dIt);
	}
	_pointer				operator->() const {
		return (m_isReverse ? m_rIt.operator->() : m_dIt.operator->());
	}

	_reference				operator[](_difference_type n) const {
		DequeConstIterator	tmp(*this);
		tmp += n;
		return *tmp;
	}
	DequeConstIterator		operator+ (_difference_type n) const {
		DequeConstIterator	it(*this);

		it += n;
		return it;
	}
	DequeConstIterator		operator- (_difference_type n) const {
		DequeConstIterator	it(*this);

		it -= n;
		return it;
	}

	DequeConstIterator &	operator++() {
		if (m_isReverse) {
			++m_rIt;
			if (m_rIt == m_reverse->rend()) {
				m_dIt = m_direct->begin();
				m_isReverse = false;
			}
		}
		else {
			++m_dIt;
		}
		return *this;
	}
	DequeConstIterator		operator++(int) {
		DequeConstIterator	save(*this);

		operator++();
		return save;
	}
	DequeConstIterator &	operator--() {
		if (m_isReverse) {
			--m_rIt;
		}
		else {
			if (m_dIt == m_direct->begin()) {
				m_rIt = m_reverse->rbegin();
				m_isReverse = true;
			}
			else {
				--m_dIt;
			}
		}
		return *this;
	}
	DequeConstIterator		operator--(int) {
		DequeConstIterator	save(*this);

		operator--();
		return save;
	}

	DequeConstIterator &	operator+=(_difference_type n) {
		if (n > 0) {
			if (m_isReverse) {
				const _difference_type	diff1 = m_reverse->rend() - m_rIt;
				if (diff1 > n + 1) {
					m_rIt += n;
				}
				else {
					m_isReverse = false;
					m_dIt = m_direct->begin() + n - diff1;
				}
			}
			else {
				m_dIt += n;
			}
		}
		else {
			if (m_isReverse) {
				m_rIt += n;
			}
			else {
				const _difference_type	diff2 = m_dIt - m_direct->begin();
				if (diff2 > -n) {
					m_dIt += n;
				}
				else {
					m_isReverse = true;
					m_rIt = m_reverse->rbegin() + (diff2 + n);
				}
			}
		}
		return *this;
	}
	DequeConstIterator &	operator-=(_difference_type n) {
		*this += -n;
		return *this;
	}

	inline bool				operator==(const DequeConstIterator & other) const {
		return (m_isReverse == other.m_isReverse
				&& (m_isReverse ? m_rIt == other.m_rIt : m_dIt == other.m_dIt));
	}
	inline bool				operator!=(const DequeConstIterator & other) const {
		return !operator==(other);
	}
	inline bool				operator< (const DequeConstIterator & other) const {
		if (m_isReverse && !other.m_isReverse) {
			return true;
		}
		if (!m_isReverse && other.m_isReverse) {
			return false;
		}
		if (m_isReverse) {
			return std::operator<(m_rIt, other.m_rIt);
		}
		return std::operator<(m_dIt, other.m_dIt);
	}
	inline bool				operator> (const DequeConstIterator & other) const {
		return other.operator<(*this);
	}
	inline bool				operator<=(const DequeConstIterator & other) const {
		return !operator>(other);
	}
	inline bool				operator>=(const DequeConstIterator & other) const {
		return !operator<(other);
	}

	friend
	DequeConstIterator		operator+(_difference_type n, const DequeConstIterator & it) {
		return it + n;
	}
	friend bool				operator==(const DequeIterator<value_type> & x, const DequeConstIterator & y) {
		return (x.m_isReverse == y.m_isReverse
				&& (x.m_isReverse ? x.m_rIt == y.m_rIt : x.m_dIt == y.m_dIt));
	}
	friend bool				operator!=(const DequeIterator<value_type> & x, const DequeConstIterator & y) {
		return !y.operator==(x);
	}
	friend bool				operator< (const DequeIterator<value_type> & x, const DequeConstIterator & y) {
		if (x.m_isReverse && !y.m_isReverse) {
			return true;
		}
		if (!x.m_isReverse && y.m_isReverse) {
			return false;
		}
		if (x.m_isReverse) {
			return std::operator<(x.m_rIt, y.m_rIt);
		}
		return std::operator<(x.m_dIt, y.m_dIt);
	}
	friend bool				operator> (const DequeIterator<value_type> & x, const DequeConstIterator & y) {
		return y.operator<(x);
	}
	friend bool				operator<=(const DequeIterator<value_type> & x, const DequeConstIterator & y) {
		return y.operator<=(x);
	}
	friend bool				operator>=(const DequeIterator<value_type> & x, const DequeConstIterator & y) {
		return y.operator>=(x);
	}
	friend
	_difference_type		operator-(const DequeConstIterator & x, const DequeConstIterator & y) {
		if (x.m_isReverse == y.m_isReverse) {
			return (x.m_isReverse ? (x.m_rIt - y.m_rIt) : (x.m_dIt - y.m_dIt));
		}
		if (x.m_isReverse) {
			return -((x.m_reverse->rend() - x.m_rIt) + (y.m_dIt - y.m_direct->begin()));
		}
		return (x.m_dIt - x.m_direct->begin()) + (y.m_reverse->rend() - y.m_rIt);
	}

private:
	bool					m_isReverse;
	_directIt				m_dIt;
	_reverseIt				m_rIt;
	const vector_type *		m_direct;
	const vector_type *		m_reverse;
};