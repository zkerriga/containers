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
#include <type_traits>

#include "list_node.hpp"

template < typename iterator_category,
		   typename value_type,
		   typename return_value_type,
		   typename stored_pointer_type >
class _BaseIterator
	: public std::iterator< iterator_category,
							value_type,
							std::size_t,
							return_value_type *,
							return_value_type & >
{
private:
	typedef void (*shiftPointerFunction)(stored_pointer_type &);

public:
	_BaseIterator() : m_p(nullptr) {}
	_BaseIterator(const _BaseIterator &other) {
		*this = other;
	}
	virtual ~_BaseIterator() {}
	_BaseIterator & operator = (const _BaseIterator &other) {
		if (this != &other) {
			m_p = other.m_p;
		}
		return *this;
	}
	_BaseIterator(stored_pointer_type pointer) : m_p(pointer) {}

	bool	operator!=(const _BaseIterator & other) const {
		return (m_p != other.m_p);
	}
	bool	operator==(const _BaseIterator & other) const {
		return (m_p == other.m_p);
	}

protected:
	stored_pointer_type	m_p;
	typedef stored_pointer_type StoredPointer;

private:
	const shiftPointerFunction mc_incrementFunction;
	const shiftPointerFunction mc_decrementFunction;

}; //class _BaseIterator

#define BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR \
			_BaseIterator< std::bidirectional_iterator_tag, \
						   value_type, \
						   return_value_type, \
						   ListNode< value_type, allocator_type >* >

template < typename value_type,
		   typename return_value_type,
		   typename allocator_type >
class _ListIterator : public BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR {
private:
	typedef BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR	_base;
	typedef typename _base::StoredPointer			_lstPtr;

public:
	_ListIterator() : _base() {}
	_ListIterator(const _ListIterator &other) : _base() {
		_base::operator=(other);
	}
	~_ListIterator() {}
	_ListIterator & operator = (const _ListIterator &other) {
		_base::operator=(other);
		return *this;
	}
	explicit _ListIterator(_lstPtr p) : _base(p) {}

	return_value_type &		operator*() const {
		return *(_base::m_p->data);
	}
	return_value_type *		operator->() const {
		return _base::m_p->data;
	}
	_ListIterator &			operator++() {
		//TODO:
//		_lst::getStepFunction(IncrementType())(_base::m_lst);
//		return *this;
	}
	_ListIterator &			operator--() {
		//TODO:
	}
	const _ListIterator		operator--(int) {
		_lstPtr		tmp = _base::m_p;

		this->operator--();
		return _ListIterator(tmp);
	}
	const _ListIterator		operator++(int) {
		_lstPtr		tmp = _base::m_p;

		this->operator++();
		return _ListIterator(tmp);
	}
}; //class _ListIterator

#undef BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR





/*
template < typename value_type, typename allocator_type >
class _baseIterator {
private:
	typedef ListNode<value_type,allocator_type>		_lst;

public:
	_baseIterator() : m_lst(nullptr) {}
	_baseIterator(const _baseIterator & other) {
		*this = other;
	}
	virtual ~_baseIterator() {}
	_baseIterator & operator = (const _baseIterator & other) {
		if (this != &other) {
			m_lst = other.m_lst;
		}
		return *this;
	}
	explicit _baseIterator(_lst * p) : m_lst(p) {}

protected:
	_lst *		m_lst;

}; //class _baseIterator


template < typename value_type, typename return_value_type,
		   typename allocator_type,
		   typename IncrementType, typename DecrementType >
class _listIterator : public std::iterator< std::bidirectional_iterator_tag, return_value_type >,
					  public _baseIterator< value_type, allocator_type > {
private:
	typedef ListNode< value_type,allocator_type >			_lst;
	typedef _baseIterator< value_type,allocator_type >		_base;
	typedef _listIterator< value_type, value_type,
						   allocator_type, IncrementType,
						   DecrementType >					_nonConstIterator;

public:
	_listIterator() : _base() {}
	_listIterator(const _nonConstIterator & other) : _base() {
		*this = other;
	}
	~_listIterator() {}
	_listIterator &	operator=(const _nonConstIterator & other) {
		_base::operator=(other);
		return *this;
	}
	explicit _listIterator(_lst * p) : _base(p) {}

	bool					operator!=(const _listIterator & other) const {
		return (_base::m_lst != other.m_lst);
	}
	bool					operator==(const _listIterator & other) const {
		return (_base::m_lst == other.m_lst);
	}
	return_value_type &		operator*() const {
		return *(_base::m_lst->data);
	}
	return_value_type *		operator->() const {
		return _base::m_lst->data;
	}
	_listIterator &			operator++() {
		_lst::getStepFunction(IncrementType())(_base::m_lst);
		return *this;
	}
	_listIterator &			operator--() {
		_lst::getStepFunction(DecrementType())(_base::m_lst);
		return *this;
	}
	const _listIterator		operator--(int) {
		_lst *	tmp = _base::m_lst;

		this->operator--();
		return _listIterator(tmp);
	}
	const _listIterator		operator++(int) {
		_lst *	tmp = _base::m_lst;

		this->operator++();
		return _listIterator(tmp);
	}
}; //class _listIterator
*/