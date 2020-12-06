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
		   typename stored_type >
class _BaseIterator
	: public std::iterator< iterator_category,
							value_type,
							std::size_t,
							return_value_type *,
							return_value_type & > {
private:
	typedef void (*shiftPointerFunction)(stored_type * &);

public:
	_BaseIterator(shiftPointerFunction inc, shiftPointerFunction dec)
		: m_p(nullptr), mc_incrementFunction(inc), mc_decrementFunction(dec) {}
	_BaseIterator(const _BaseIterator & other)
		: m_p(nullptr),
		  mc_incrementFunction(other.mc_incrementFunction),
		  mc_decrementFunction(other.mc_decrementFunction)
	{
		*this = other;
	}
	virtual ~_BaseIterator() {}
	_BaseIterator & operator = (const _BaseIterator & other) {
		if (this != &other) {
			m_p = other.m_p;
		}
		return *this;
	}
	_BaseIterator(stored_type * pointer,
				  shiftPointerFunction inc, shiftPointerFunction dec)
		: m_p(pointer), mc_incrementFunction(inc), mc_decrementFunction(dec) {}

	bool					operator!=(const _BaseIterator & other) const {
		return (m_p != other.m_p);
	}
	bool					operator==(const _BaseIterator & other) const {
		return (m_p == other.m_p);
	}
	_BaseIterator &			operator++() {
		mc_incrementFunction(m_p);
		return *this;
	}
	_BaseIterator &			operator--() {
		mc_decrementFunction(m_p);
		return *this;
	}
	const _BaseIterator		operator--(int) {
		stored_type *	tmp = m_p;

		_BaseIterator::operator--();
		return _BaseIterator(tmp);
	}
	const _BaseIterator		operator++(int) {
		stored_type *	tmp = m_p;

		_BaseIterator::operator++();
		return _BaseIterator(tmp);
	}

protected:
	typedef stored_type		StoredType;

	stored_type *	m_p;

private:
	_BaseIterator()
		: m_p(nullptr),
		  mc_incrementFunction(nullptr), mc_decrementFunction(nullptr) {}

	const shiftPointerFunction mc_incrementFunction;
	const shiftPointerFunction mc_decrementFunction;

}; //class _BaseIterator

#define BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR(return_value_type) \
			_BaseIterator< std::bidirectional_iterator_tag, \
						   value_type, \
						   return_value_type, \
						   ListNode< value_type, allocator_type > >

#define GET_SHIFT_FUNCS _lst::getShiftFunction(IncrementType()), \
						_lst::getShiftFunction(DecrementType())

template < typename value_type,
		   typename allocator_type,
		   typename IncrementType,
		   typename DecrementType >
class _ListIterator : public BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR(value_type) {
private:
	typedef BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR(value_type)	_base;
	typedef typename _base::StoredType							_lst;

public:
	_ListIterator() : _base( GET_SHIFT_FUNCS ) {}
	_ListIterator(const _ListIterator & other) : _base( GET_SHIFT_FUNCS ) {
		_base::operator=(other);
	}
	~_ListIterator() {}
	_ListIterator & operator=(const _ListIterator & other) {
		_base::operator=(other);
		return *this;
	}
	explicit _ListIterator(_lst * p) : _base( p, GET_SHIFT_FUNCS ) {}

	value_type &		operator*() const {
		return *(_base::m_p->data);
	}
	value_type *		operator->() const {
		return _base::m_p->data;
	}
}; //class _ListIterator

template < typename value_type,
		   typename return_value_type,
		   typename allocator_type,
		   typename IncrementType,
		   typename DecrementType >
class _ListConstIterator
		: public BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR(return_value_type) {
private:
	typedef BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR(return_value_type)	_base;
	typedef typename _base::StoredType									_lst;
	typedef _ListIterator< value_type, allocator_type,
						   IncrementType, DecrementType >				_MutableListIterator;
public:
	_ListConstIterator() : _base( GET_SHIFT_FUNCS ) {}
	_ListConstIterator(const _ListConstIterator & other) : _base( GET_SHIFT_FUNCS ) {
		_base::operator=(other);
	}
	_ListConstIterator(const _MutableListIterator & other) : _base( GET_SHIFT_FUNCS ) {
		_base::operator=(other);
	}
	~_ListConstIterator() {}
	_ListConstIterator & operator=(const _ListConstIterator & other) {
		_base::operator=(other);
		return *this;
	}
	_ListConstIterator & operator=(const _MutableListIterator & other) {
		_base::operator=(other);
		return *this;
	}
	explicit _ListConstIterator(_lst * p) : _base( p, GET_SHIFT_FUNCS ) {}

	value_type &		operator*() const {
		return *(_base::m_p->data);
	}
	value_type *		operator->() const {
		return _base::m_p->data;
	}
}; //class _ListConstIterator

#undef BASE_CLASS_TEMPLATE_FOR_LIST_ITERATOR
#undef GET_SHIFT_FUNCS




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