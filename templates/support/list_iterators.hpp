/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterators.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:52:47 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/04 14:52:48 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include "list_node.hpp"

template < typename value_type, typename allocator_type >
class _listIterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
private:
	typedef ListNode<value_type,allocator_type>		_lst;

public:
	_listIterator() : m_lst(nullptr) {}
	_listIterator(const _listIterator & other) : m_lst(other.m_lst) {}
	~_listIterator() {}
	_listIterator &	operator=(const _listIterator & other) {
		if (this != &other) {
			m_lst = other.m_lst;
		}
		return *this;
	}

	_listIterator(_lst * p) : m_lst(p) {}

	bool					operator!=(const _listIterator & other) const {
		return (m_lst != other.m_lst);
	}
	bool					operator==(const _listIterator & other) const {
		return (m_lst == other.m_lst);
	}
	value_type &			operator*() const {
		return *(m_lst->data);
	}
	_listIterator &			operator++() {
		_lst::toNext(m_lst);
		return *this;
	}
	_listIterator &			operator--() {
		_lst::toPrev(m_lst);
		return *this;
	}
	const _listIterator		operator--(int) {
		_lst *	tmp = m_lst;

		_lst::toPrev(m_lst);
		return _listIterator(tmp);
	}
	const _listIterator		operator++(int) {
		_lst *	tmp = m_lst;

		_lst::toNext(m_lst);
		return _listIterator(tmp);
	}

private:
	_lst *		m_lst;
};

// ListNode<int, std::__1::allocator<int> > *
// ft::list<int, std::__1::allocator<int> >::const_iterator
// _listIterator<const int, std::__1::allocator<int> >

/*template < typename value_type, typename allocator_type >
class _listConstIterator : public std::iterator<std::bidirectional_iterator_tag, const value_type> {
private:
	typedef ListNode<value_type,allocator_type>		_lst;

public:
	_listConstIterator(const _listConstIterator & other) : m_lst(other.m_lst) {}
	~_listConstIterator() {}
	_listConstIterator &	operator=(const _listConstIterator & other) {
		if (this != &other) {
			m_lst = other.m_lst;
		}
		return *this;
	}

	_listConstIterator(_lst * p) : m_lst(p) {}

	bool						operator!=(const _listConstIterator & other) const {
		return (m_lst != other.m_lst);
	}
	bool						operator==(const _listConstIterator & other) const {
		return (m_lst == other.m_lst);
	}
	const value_type &			operator*() const {
		return *(m_lst->data);
	}
	_listConstIterator &		operator++() {
		_lst::toNext(m_lst);
		return *this;
	}
	_listConstIterator &		operator--() {
		_lst::toPrev(m_lst);
		return *this;
	}
	const _listConstIterator	operator--(int) {
		_lst *	tmp = m_lst;

		_lst::toPrev(m_lst);
		return _listConstIterator(tmp);
	}
	const _listConstIterator	operator++(int) {
		_lst *	tmp = m_lst;

		_lst::toNext(m_lst);
		return _listConstIterator(tmp);
	}

private:
	_listConstIterator() : m_lst(nullptr) {}

	_lst *		m_lst;
};*/
