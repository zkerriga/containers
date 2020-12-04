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

template < typename value_type, typename return_value_type,
		   typename allocator_type,
		   typename PlusPlusType, typename MinusMinusType >
class _listIterator : public std::iterator<std::bidirectional_iterator_tag, return_value_type> {
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
	return_value_type &		operator*() const {
		return *(m_lst->data);
	}
	return_value_type *		operator->() const {
		return m_lst->data;
	}
	_listIterator &			operator++() {
		_lst::getStepFunction(PlusPlusType())(m_lst);
//		_lst::toNext(m_lst);
		return *this;
	}
	_listIterator &			operator--() {
		_lst::getStepFunction(MinusMinusType())(m_lst);
//		_lst::toPrev(m_lst);
		return *this;
	}
	const _listIterator		operator--(int) {
		_lst *	tmp = m_lst;

		this->operator--();
		return _listIterator(tmp);
	}
	const _listIterator		operator++(int) {
		_lst *	tmp = m_lst;

		this->operator++();
		return _listIterator(tmp);
	}

private:
	_lst *		m_lst;
};
