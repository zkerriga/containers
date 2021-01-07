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

#include "block_chain_iterators.hpp"

namespace ft {

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
	typedef std::vector<value_type, allocator_type>				block_type;
	typedef typename allocator_type::template rebind<block_type>::other
																allocator_rebind;
	typedef std::list<block_type, allocator_rebind>				chain_type;
public:
	typedef DequeIterator<typename chain_type::iterator,value_type>		iterator;
	/* todo: iterators */
	typedef int										const_iterator;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
	/* todo: iterators */

	/* Initialize */
	explicit deque(const allocator_type & alloc = allocator_type())
		: m_size(0), m_capacity(0),
		  m_allocValue(alloc), m_allocBlock(alloc),
		  m_blockChain(chain_type()) {}
	explicit deque(size_type n, const value_type & val = value_type(),
				   const allocator_type & alloc = allocator_type())
		: m_size(n), m_capacity(0),
		  m_allocValue(alloc), m_allocBlock(alloc),
		  m_blockChain(chain_type(alloc))
	{
		const size_type		numberOfFullBlocks = n / mc_blockSize;
		const size_type		sizeOfNotFullBlock = n % mc_blockSize;

		m_capacity = (numberOfFullBlocks + (sizeOfNotFullBlock ? 1 : 0)) * mc_blockSize;
		if (numberOfFullBlocks) {
			const block_type	defaultBlock(mc_blockSize, val, m_allocValue);
			m_blockChain = chain_type(numberOfFullBlocks, defaultBlock, m_allocBlock);
		}
		if (sizeOfNotFullBlock) {
			block_type	block = _getEmptyBlock();
			for (size_type i = 0; i < sizeOfNotFullBlock; ++i) {
				block.push_back(val);
			}
			m_blockChain.push_back(block);
		}
	}
//	template <class InputIterator>
//	deque(InputIterator first, InputIterator last,
//		  const allocator_type & alloc = allocator_type());
//	deque(const deque & x);
//	~deque();
//	deque & operator= (const deque & x);

	/* Iterators */
	iterator				begin() {
		static const size_type	firstIndex = 0; /* todo: не ноль, можно добавить неполную ноду */
		return iterator(mc_blockSize, firstIndex, firstIndex, m_blockChain.begin());
	}
//	const_iterator			begin() const;
	iterator				end() {
		static const size_type	blockIndex = 0;
		const size_type			lastChainIndex = m_blockChain.size();
		return iterator(mc_blockSize, lastChainIndex, blockIndex, m_blockChain.end());
	}
//	const_iterator			end() const;
//	reverse_iterator		rbegin();
//	const_reverse_iterator	rbegin() const;
//	reverse_iterator		rend();
//	const_reverse_iterator	rend() const;

	/* Capacity */
	size_type	size() const {
		return m_size;
	}
//	size_type	max_size() const;
//	void		resize(size_type n, value_type val = value_type());
	bool		empty() const {
		return (m_size == 0);
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
//	void		push_back(const value_type & val);
//	void		push_front(const value_type & val);
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
	static const size_type	mc_blockSize = sizeof(value_type) < 256
											? 4096 / sizeof(value_type)
											: 16;

	size_type				m_size;
	size_type				m_capacity;
	allocator_type			m_allocValue;
	allocator_rebind		m_allocBlock;
	chain_type				m_blockChain;

private:
	block_type				_getEmptyBlock() {
		block_type	block(m_allocValue);
		block.reserve(mc_blockSize);
		return block;
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

} //namespace ft
