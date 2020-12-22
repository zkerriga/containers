/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:06:43 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/10 20:06:44 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <type_traits>
#include <stdexcept>

#include "tree_node.hpp"

template < typename value_type >
class _MapIterator : public std::iterator< std::bidirectional_iterator_tag,
										   value_type > {
	typedef std::iterator< std::bidirectional_iterator_tag,
						   value_type >						_stdIt;
	typedef typename _stdIt::pointer						_pointer;
	typedef typename _stdIt::reference						_reference;
	typedef TreeNode< value_type >							_tree;
public:
	_MapIterator() : m_p(nullptr) {}
	_MapIterator(const _MapIterator & other) {
		*this = other;
	}
	virtual ~_MapIterator() {}
	_MapIterator &	operator= (const _MapIterator & other) {
		if (this != &other) {
			m_p = other.m_p;
		}
		return *this;
	}

	explicit _MapIterator(_tree * p) : m_p(p) {}

	_reference			operator* () const noexcept {
		return *(m_p->data);
	}
	_pointer			operator->() const noexcept {
		return m_p->data;
	}

	_MapIterator &		operator++() noexcept {
		/* todo */
		return *this;
	}
	_MapIterator &		operator--() noexcept {
		/* todo */
		return *this;
	}
	_MapIterator		operator++(int) noexcept {
		_pointer		tmp = m_p;
		operator++();
		return _MapIterator(tmp);
	}
	_MapIterator		operator--(int) noexcept {
		_pointer		tmp = m_p;
		operator--();
		return _MapIterator(tmp);
	}

private:
	_tree *		m_p;
};
