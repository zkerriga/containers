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

template <class chain_iterator_type, typename value_type>
class DequeIterator : public std::iterator<std::random_access_iterator_tag,value_type> {
	typedef std::iterator<std::random_access_iterator_tag,value_type>	_stdIt;
	typedef typename _stdIt::difference_type							_difference_type;
	typedef typename _stdIt::pointer									_pointer;
	typedef typename _stdIt::reference									_reference;
public:
	typedef chain_iterator_type		chain_iterator;
	typedef size_t					size_type;
public:
	DequeIterator()
		: mc_maxBlockSize(0), m_chainIndex(0),
		  m_blockIndex(0), m_chainIterator() {}
	DequeIterator(const DequeIterator & x)
		: mc_maxBlockSize(x.mc_maxBlockSize), m_chainIndex(x.m_chainIndex),
		  m_blockIndex(x.m_blockIndex), m_chainIterator(x.m_chainIterator) {}
	virtual ~DequeIterator() {}
	DequeIterator & operator= (const DequeIterator & x) {
		if (this != &x) {
			m_chainIndex	= x.m_chainIndex;
			m_blockIndex	= x.m_blockIndex;
			m_chainIterator	= x.m_chainIterator;
		}
		return *this;
	}

	DequeIterator(const size_type maxBlockSize, const size_type chainIndex,
				  const size_type blockIndex, const chain_iterator_type & it)
		: mc_maxBlockSize(maxBlockSize), m_chainIndex(chainIndex),
		  m_blockIndex(blockIndex), m_chainIterator(it) {}

	_reference			operator* () const {
		return (*m_chainIterator)[m_blockIndex];
	}
	_pointer			operator->() const {
		return &(*m_chainIterator)[m_blockIndex];
	}

	_reference			operator[](_difference_type n) const {
		/* todo: [] */
		return operator*(); /* todo: delete */
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
		++m_blockIndex;
		if (m_blockIndex == (*m_chainIterator).size()) {
			m_blockIndex = 0;
			++m_chainIndex;
			++m_chainIterator;
		}
		return *this;
	}
	DequeIterator		operator++(int) {
		DequeIterator	save(*this);

		operator++();
		return save;
	}
	DequeIterator &		operator--() {
		if (m_blockIndex == 0) {
			m_blockIndex = mc_maxBlockSize;
			--m_chainIndex;
			--m_chainIterator;
		}
		--m_blockIndex;
		return *this;
	}
	DequeIterator		operator--(int) {
		DequeIterator	save(*this);

		operator--();
		return save;
	}

	DequeIterator &		operator+=(_difference_type n) {
		/* todo: += */
		return *this;
	}
	DequeIterator &		operator-=(_difference_type n) {
		*this += -n;
		return *this;
	}

	bool				operator==(const DequeIterator & other) {
		return (m_chainIndex == other.m_chainIndex && m_blockIndex == other.m_blockIndex);
	}
	bool				operator!=(const DequeIterator & other) {
		return !operator==(other);
	}

private:
	const size_type			mc_maxBlockSize;
	size_type				m_chainIndex;
	size_type				m_blockIndex;
	chain_iterator_type		m_chainIterator;
};
