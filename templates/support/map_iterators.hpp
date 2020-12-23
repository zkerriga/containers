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
		m_p = _tree::iterateNode(m_p, _tree::step::right, _tree::step::left);
		return *this;
	}
	_MapIterator &		operator--() noexcept {
		m_p = _tree::iterateNode(m_p, _tree::step::left, _tree::step::right);
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

	/* Bad practice */
	_tree *		_getTreePointer() const {
		return m_p;
	}
private:
	_tree *		m_p;
}; //class _MapIterator


template < typename value_type >
class _MapConstIterator : public std::iterator< std::bidirectional_iterator_tag,
		value_type > {
	typedef std::iterator< std::bidirectional_iterator_tag,
			value_type >						_stdIt;
	typedef typename _stdIt::pointer						_pointer;
	typedef typename _stdIt::reference						_reference;
	typedef TreeNode< value_type >							_tree;
public:
	_MapConstIterator() : m_p(nullptr) {}
	_MapConstIterator(const _MapConstIterator & other) {
		*this = other;
	}
	_MapConstIterator(const _MapIterator<value_type> & other) {
		*this = other;
	}
	virtual ~_MapConstIterator() {}
	_MapConstIterator &	operator= (const _MapConstIterator & other) {
		if (this != &other) {
			m_p = other.m_p;
		}
		return *this;
	}
	_MapConstIterator &	operator= (const _MapIterator<value_type> & other) {
		m_p = other._getTreePointer();
		return *this;
	}

	explicit _MapConstIterator(_tree * p) : m_p(p) {}

	_reference			operator* () const noexcept {
		return *(m_p->data);
	}
	_pointer			operator->() const noexcept {
		return m_p->data;
	}

	_MapConstIterator &	operator++() noexcept {
		m_p = _tree::iterateNode(m_p, _tree::step::right, _tree::step::left);
		return *this;
	}
	_MapConstIterator &	operator--() noexcept {
		m_p = _tree::iterateNode(m_p, _tree::step::left, _tree::step::right);
		return *this;
	}
	_MapConstIterator	operator++(int) noexcept {
		_pointer		tmp = m_p;
		operator++();
		return _MapConstIterator(tmp);
	}
	_MapConstIterator	operator--(int) noexcept {
		_pointer		tmp = m_p;
		operator--();
		return _MapConstIterator(tmp);
	}

	/* Bad practice */
	_tree *		_getTreePointer() const {
		return m_p;
	}
private:
	_tree *		m_p;
}; //class _MapConstIterator


template < class LeftIterator, class RightIterator >
typename std::enable_if<
		(std::is_same< LeftIterator, _MapIterator< typename LeftIterator::value_type > >::value
		 || std::is_same< LeftIterator, _MapConstIterator< typename LeftIterator::value_type > >::value)
		&& (std::is_same< RightIterator, _MapIterator< typename RightIterator::value_type > >::value
			|| std::is_same< RightIterator, _MapConstIterator< typename RightIterator::value_type > >::value),
		bool >::type
operator==(const LeftIterator & lhs, const RightIterator & rhs) noexcept {
	return (lhs._getTreePointer() == rhs._getTreePointer());
}

template < class LeftIterator, class RightIterator >
typename std::enable_if<
		(std::is_same< LeftIterator, _MapIterator< typename LeftIterator::value_type > >::value
		 || std::is_same< LeftIterator, _MapConstIterator< typename LeftIterator::value_type > >::value)
		&& (std::is_same< RightIterator, _MapIterator< typename RightIterator::value_type > >::value
			|| std::is_same< RightIterator, _MapConstIterator< typename RightIterator::value_type > >::value),
		bool >::type
operator!=(const LeftIterator & lhs, const RightIterator & rhs) noexcept {
	return !operator==(lhs, rhs);
}
