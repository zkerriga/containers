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

/* todo: edd NOEXCEPT */

#define _ENABLE_INPUT_ITERATOR_TYPE(type_name) \
		typename std::enable_if< std::__is_input_iterator< type_name >::value,type_name >::type

template < class Key,
		   class T,
		   class Compare = std::less< Key >,
		   class Alloc = std::allocator< std::pair< const Key, T > > >
class map {
public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef std::pair< const Key, T >					value_type;
	typedef Compare										key_compare;
	class value_compare;
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
		: m_end(nullptr), m_size(0), mc_keyCompare(comp),
		  mc_valueCompare(comp), m_valueAlloc(alloc)
	{
		m_end = _tree::end::create(m_treeAlloc);
	}
	template < class InputIterator >
	map(InputIterator first,
		_ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last,
		const key_compare & comp = key_compare(),
		const allocator_type & alloc = allocator_type())
		: m_end(nullptr), m_size(0), mc_keyCompare(comp),
		  mc_valueCompare(comp), m_valueAlloc(alloc)
	{
		m_end = _tree::end::create(m_treeAlloc);
		insert(first, last);
	}
	map(const map & x)
		: m_end(nullptr), m_size(0), mc_keyCompare(x.mc_keyCompare),
		  mc_valueCompare(x.mc_valueCompare), m_valueAlloc(x.m_valueAlloc)
	{
		m_end = _tree::end::create(m_treeAlloc);
		insert(x.begin(), x.end());
	}
	~map() {
		clear();
		_tree::end::destroy(m_end, m_treeAlloc);
	}
	map & operator= (const map & x) {
		if (this != &x) {
			clear();
			insert(x.begin(), x.end());
		}
		return *this;
	}

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
	size_type	max_size() const {
		return (static_cast<size_type>(-1) / sizeof(*m_end));
	}

	/* Element access */
	mapped_type & operator[](const key_type & k) {
		return insert(
			std::make_pair(k, mapped_type())
		).first->second;
	}

	/* Modifiers */
	std::pair< iterator, bool >
					insert(const value_type & val) {
		const std::pair< _tree*, bool >	ret = _tree::insert(
				_tree::end::getRoot(m_end),
				val,
				mc_valueCompare,
				m_treeAlloc,
				m_valueAlloc
		);
		if (m_size == 0) {
			_tree::end::setRoot(m_end, ret.first);
			_tree::end::setFirst(m_end, ret.first);
			_tree::end::setLast(m_end, ret.first);
		}
		if (ret.second) {
			++m_size;
			_rootToBlack();
		}
		return std::make_pair(iterator(ret.first), ret.second);
	}
	iterator		insert(iterator, const value_type & val) {
		return insert(val).first;
	}
	template < class InputIterator >
	void			insert(InputIterator first,
						   _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last) {
		while (first != last) {
			insert(*first++);
		}
	}
	void			erase(iterator position) {
		erase(position->first);
	}
	size_type		erase(const key_type & k) {
		if ( m_size == 0 || (find(k) == end()) ) {
			return 0;
		}
		_tree::deleteFromTree(
			_tree::end::getRoot(m_end),
			std::make_pair(k, mapped_type()),
			mc_valueCompare,
			m_treeAlloc,
			m_valueAlloc
		);
		--m_size;
		if (m_size == 0) {
			_tree::end::roundOff(m_end);
		}
		else {
			_rootToBlack();
		}
		return 1;
	}
	void			erase(iterator first, iterator last) {
		while (first != last) {
			erase(first++);
		}
	}
	void			swap(map & x) {
		ft::swap(m_end, x.m_end);
		ft::swap(m_size, x.m_size);
	}
	void			clear() {
		_tree::clearTree(m_end, m_treeAlloc, m_valueAlloc);
		m_size = 0;
	}

	/* Observers */
	key_compare		key_comp() const {
		return mc_keyCompare;
	}
	value_compare	value_comp() const {
		return mc_valueCompare;
	}

	/* Operations */
	iterator		find(const key_type & k) {
		_tree * const	found = _tree::findOrGetNull(
			_tree::end::getRoot(m_end),
			std::make_pair(k, mapped_type()),
			mc_valueCompare
		);
		return iterator(found ? found : m_end);
	}
	const_iterator	find(const key_type & k) const {
		_tree * const	found = _tree::findOrGetNull(
				_tree::end::getRoot(m_end),
				std::make_pair(k, mapped_type()),
				mc_valueCompare
		);
		return const_iterator(found ? found : m_end);
	}
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
	allocator_type	get_allocator() const {
		return m_valueAlloc;
	}

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
	const key_compare	mc_keyCompare;
	const value_compare	mc_valueCompare;
	allocator_type		m_valueAlloc;
	allocator_rebind	m_treeAlloc;

	void	_rootToBlack() const {
		_tree * const	root = _tree::end::getRoot(m_end);

		if (_tree::isRed(root)) {
			_tree::flipColor(root);
		}
	}
}; //class map

#undef _ENABLE_INPUT_ITERATOR_TYPE

template <class Key, class T, class Compare, class Alloc>
class map< Key, T, Compare, Alloc >::value_compare
		: public std::binary_function< value_type, value_type, bool > {
public:
	typedef bool		result_type;
	typedef value_type	first_argument_type;
	typedef value_type	second_argument_type;

	value_compare(Compare c) : comp(c) {} /* todo: move to protected */

	bool operator()(const value_type & x, const value_type & y) const {
		return comp(x.first, y.first);
	}
protected:
	Compare	comp;
};

} //namespace ft
