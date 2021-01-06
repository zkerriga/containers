/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_chain.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:23:41 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/06 17:23:42 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <list>
#include <iterator>

template <class chain_iterator_type, class block_iterator_type, typename size_type, typename value_type>
class DequeIterator : public std::iterator<std::random_access_iterator_tag,value_type> {
	typedef std::iterator<std::random_access_iterator_tag,value_type>	_stdIt;
	typedef typename _stdIt::difference_type							_difference_type;
	typedef typename _stdIt::pointer									_pointer;
	typedef typename _stdIt::reference									_reference;
public:
	DequeIterator() {}
	DequeIterator(const DequeIterator & x)
		: m_chainIterator(x.m_chainIterator), m_blockIterator(x.m_blockIterator) {}
	virtual ~DequeIterator() {}
	DequeIterator & operator= (const DequeIterator & x) {
		if (this != &x) {
			m_chainIterator = x.m_chainIterator;
			m_blockIterator = x.m_blockIterator;
		}
		return *this;
	}

	DequeIterator(chain_iterator_type chainIt, block_iterator_type blockIt)
		: m_chainIterator(chainIt), m_blockIterator(blockIt) {}

	_reference			operator* () const {
		return *m_blockIterator;
	}
	_pointer			operator->() const {
		return m_blockIterator.operator->();
	}

	_reference			operator[](_difference_type n) const;

	DequeIterator		operator+ (_difference_type n) const;
	DequeIterator		operator- (_difference_type n) const;

	DequeIterator &		operator++();
	DequeIterator		operator++(int);
	DequeIterator &		operator--();
	DequeIterator		operator--(int);

	DequeIterator &		operator+=(_difference_type n);
	DequeIterator &		operator-=(_difference_type n);

private:
	chain_iterator_type		m_chainIterator;
	block_iterator_type		m_blockIterator;
};
