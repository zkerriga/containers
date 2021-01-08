/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:01:53 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/08 22:01:53 by zkerriga         ###   ########.fr       */
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


#define _ENABLE_INPUT_ITERATOR_TYPE(type_name) \
		typename std::enable_if< std::__is_input_iterator< type_name >::value,type_name >::type

template < class T,							// set::key_type/value_type
		   class Compare = std::less<T>,	// set::key_compare/value_compare
		   class Alloc = std::allocator<T>	// set::allocator_type
		   >
class set {
public:
	typedef T											key_type;
	typedef T											value_type;
	typedef Compare										key_compare;
	typedef Compare										value_compare;
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
	explicit set(const key_compare & comp = key_compare(),
				 const allocator_type & alloc = allocator_type())
		: m_end(nullptr), m_size(0), mc_valueCompare(comp),
		  m_valueAlloc(alloc), m_treeAlloc(alloc)
	{
		m_end = _tree::end::create(m_treeAlloc);
	}
	template <class InputIterator>
	set(InputIterator first,
		_ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last,
		const key_compare & comp = key_compare(),
		const allocator_type & alloc = allocator_type())
		: m_end(nullptr), m_size(0), mc_valueCompare(comp),
		  m_valueAlloc(alloc), m_treeAlloc(alloc)
	{
		m_end = _tree::end::create(m_treeAlloc);
		insert(first, last);
	}
	set(const set & x)
		: m_end(nullptr), m_size(0), mc_valueCompare(x.mc_valueCompare),
		  m_valueAlloc(x.m_valueAlloc), m_treeAlloc(x.m_treeAlloc)
	{
		m_end = _tree::end::create(m_treeAlloc);
		insert(x.begin(), x.end());
	}
	~set() {
		clear();
		_tree::end::destroy(m_end, m_treeAlloc);
	}
	set & operator= (const set & x) {
		if (this != &x) {
			clear();
			insert(x.begin(), x.end());
		}
		return *this;
	}

	/* Iterators */
	iterator				begin() _NOEXCEPT {
		return iterator(_tree::end::getFirst(m_end));
	}
	const_iterator			begin() const _NOEXCEPT {
		return const_iterator(_tree::end::getFirst(m_end));
	}
	iterator				end() _NOEXCEPT {
		return iterator(m_end);
	}
	const_iterator			end() const _NOEXCEPT {
		return const_iterator(m_end);
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
	bool			empty() const _NOEXCEPT {
		return (m_size == 0);
	}
	size_type		size() const _NOEXCEPT {
		return m_size;
	}
	size_type		max_size() const _NOEXCEPT {
		return (static_cast<size_type>(-1) / sizeof(*m_end));
	}

	/* Modifiers */
	std::pair<iterator,bool>
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
	template <class InputIterator>
	void			insert(InputIterator first,
						   _ENABLE_INPUT_ITERATOR_TYPE(InputIterator) last) {
		while (first != last) {
			insert(*first++);
		}
	}
	void			erase(iterator position) {
		erase(*position);
	}
	size_type		erase(const value_type & val) {
		if ( m_size == 0 || (find(val) == end()) ) {
			return 0;
		}
		_tree::deleteFromTree(
				_tree::end::getRoot(m_end),
				val,
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
	void			swap(set & x) {
		ft::swap(m_end, x.m_end);
		ft::swap(m_size, x.m_size);
	}
	void			clear() {
		_tree::clearTree(m_end, m_treeAlloc, m_valueAlloc);
		m_size = 0;
	}

	/* Observers */
	key_compare		key_comp() const _NOEXCEPT {
		return mc_valueCompare;
	}
	value_compare	value_comp() const _NOEXCEPT {
		return mc_valueCompare;
	}

	/* Operations */
	iterator		find(const value_type & val) const {
		_tree * const	found = _tree::findOrGetNull(
				_tree::end::getRoot(m_end),
				val,
				mc_valueCompare
		);
		return iterator(found ? found : m_end);
	}
	size_type		count(const value_type & val) const {
		return ( m_size == 0 || (find(val) == end()) ) ? 0 : 1;
	}
	iterator		lower_bound(const value_type & val) const {
		const_iterator	it	= begin();
		const_iterator	ite	= end();

		while (it != ite && mc_valueCompare(*it, val)) {
			++it;
		}
		return iterator(it._getTreePointer());
	}
	iterator		upper_bound(const value_type & val) const {
		const_iterator	it = lower_bound(val);

		if (it != end()
			&& !mc_valueCompare(*it, val) && !mc_valueCompare(val, *it)) {
			++it;
		}
		return iterator(it._getTreePointer());
	}
	std::pair<iterator,iterator>
					equal_range(const value_type & val) const {
		return std::make_pair(lower_bound(val), upper_bound(val));
	}

	/* Allocator */
	allocator_type	get_allocator() const _NOEXCEPT {
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
	const value_compare	mc_valueCompare;
	allocator_type		m_valueAlloc;
	allocator_rebind	m_treeAlloc;

	void	_rootToBlack() const _NOEXCEPT {
		_tree * const	root = _tree::end::getRoot(m_end);

		if (_tree::isRed(root)) {
			_tree::flipColor(root);
		}
	}
}; //class set

#undef _ENABLE_INPUT_ITERATOR_TYPE

} //namespace ft

