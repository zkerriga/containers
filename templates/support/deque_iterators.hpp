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

template <class vector_type, typename value_type>
class DequeIterator : public std::iterator<std::random_access_iterator_tag,value_type> {
	typedef std::iterator<std::random_access_iterator_tag,value_type>	_stdIt;
	typedef typename _stdIt::difference_type							_difference_type;
	typedef typename _stdIt::pointer									_pointer;
	typedef typename _stdIt::reference									_reference;
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

	_reference			operator[](_difference_type n) const;
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

	DequeIterator &		operator+=(_difference_type n);
	DequeIterator &		operator-=(_difference_type n) {
		*this += -n;
		return *this;
	}

	bool				operator==(const DequeIterator & other) const {
		return (m_isReverse == other.m_isReverse
			&& (m_isReverse ? m_rIt == other.m_rIt : m_dIt == other.m_dIt));
	}
	bool				operator!=(const DequeIterator & other) const {
		return !operator==(other);
	}

private:
	bool			m_isReverse;
	_directIt		m_dIt;
	_reverseIt		m_rIt;
	vector_type *	m_direct;
	vector_type *	m_reverse;
};


