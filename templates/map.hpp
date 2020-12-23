/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
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

#include "utils.hpp"
#include "map_iterators.hpp"
#include "tree_node.hpp"

namespace ft {

template < class Key,
		   class T,
		   class Comapare = std::less< Key >,
		   class Alloc = std::allocator< std::pair< const Key, T > > >
class map {
public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef std::pair< const Key, T >					value_type;
	typedef Comapare									key_compare;
	/* todo */
//	class value_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef std::ptrdiff_t								difference_type;
	typedef std::size_t									size_type;

private:
	typedef TreeNode< value_type >						_tree;

public:
	typedef _MapIterator< value_type >					iterator;
	typedef std::reverse_iterator< iterator >			reverse_iterator;
	typedef _MapConstIterator< value_type >				const_iterator;
	typedef std::reverse_iterator< const_iterator >		const_reverse_iterator;

	/* Initialize */
	explicit map(const key_compare & comp = key_compare(),
				 const allocator_type & alloc = allocator_type())
		: m_end(nullptr), m_size(0), mc_compare(comp), m_valueAlloc(alloc)
	{
		m_end = _tree::end::create(_allocateNode());
	}
//	template < class InputIterator >
//	map(InputIterator first, InputIterator last,
//		const key_compare & comp = key_compare(),
//		const allocator_type & alloc = allocator_type());
//	map(const map & x);
//	~map();
//	map & operator= (const map & x);

	/* Iterators */
	iterator				begin() {
		return iterator(_tree::end::getFirst(m_end));
	}
	const_iterator			begin() const {
		return const_iterator(_tree::end::getFirst(m_end));
	}
	iterator				end() {
		return iterator(m_end);
	}
	const_iterator			end() const {
		return const_iterator(m_end);
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
	bool		empty() const {
		return (m_size == 0);
	}
	size_type	size() const {
		return m_size;
	}
//	size_type	max_size() const;

	/* Element access */
	mapped_type & operator[](const key_type & k) {
		/* todo: Are you sure? */
		return insert(
			std::make_pair(k, mapped_type())
		).first->second;
	}

	/* Modifiers */
	std::pair< iterator, bool >
					insert(const value_type & val) {
		/* todo */
	}
//	iterator		insert(iterator position, const value_type & val);
//	template < class InputIterator >
//	void			insert(InputIterator first, InputIterator last);
//	void			erase(iterator position);
//	size_type		erase(const key_type& k);
//	void			erase(iterator first, iterator last);
//	void			swap(map& x);
//	void			clear();

	/* Observers */
//	key_compare		key_comp() const;
//	value_compare	value_comp() const;

	/* Operations */
//	iterator		find(const key_type & k);
//	const_iterator	find(const key_type & k) const;
//	size_type		count(const key_type & k) const;
//	iterator		lower_bound(const key_type & k);
//	const_iterator	lower_bound(const key_type & k) const;
//	iterator		upper_bound(const key_type & k);
//	const_iterator	upper_bound(const key_type & k) const;
//	std::pair< const_iterator, const_iterator >
//					equal_range(const key_type & k) const;
//	std::pair< iterator, iterator >
//					equal_range(const key_type & k);

	/* Allocator */
//	allocator_type	get_allocator() const;

private:
	typedef
	typename allocator_type::template rebind<_tree>::other	allocator_rebind;
	/*
	 * EXPERIMENTAL:
	 * m_end->data   == nullptr
	 * m_end->parent == root node
	 * m_end->left   == first node (in order)
	 * m_end->right  == last node (in order)
	 */
	_tree *				m_end;
	size_type			m_size;
	const key_compare	mc_compare;
	allocator_type		m_valueAlloc;
	allocator_rebind	m_treeAlloc;

	inline
	_tree *			_allocateNode() {
		return m_treeAlloc.allocate(1);
	}

}; //class map

} //namespace ft