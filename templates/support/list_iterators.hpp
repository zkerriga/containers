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

template < typename value_type, typename stored_type >
class _BaseIterator {
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

	virtual bool					operator!=(const _BaseIterator & other) const {
		return (m_p != other.m_p);
	}
	virtual bool					operator==(const _BaseIterator & other) const {
		return (m_p == other.m_p);
	}
	virtual _BaseIterator &			operator++() {
		mc_incrementFunction(m_p);
		return *this;
	}
	virtual _BaseIterator &			operator--() {
		mc_decrementFunction(m_p);
		return *this;
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


#define STD_ITERATOR_FOR_LIST(return_value_type) \
			std::iterator< std::bidirectional_iterator_tag, \
						   value_type, \
						   std::size_t, \
						   return_value_type *, \
						   return_value_type & >

#define BASE_CLASS_FOR_LIST \
			_BaseIterator< value_type, \
						   ListNode< value_type, allocator_type > >

#define GET_SHIFT_FUNCS _lst::getShiftFunction(IncrementType()), \
						_lst::getShiftFunction(DecrementType())

template < typename value_type,
		typename allocator_type,
		typename IncrementType,
		typename DecrementType >
class _ListConstIterator;


template < typename value_type,
		   typename allocator_type,
		   typename IncrementType,
		   typename DecrementType >
class _ListIterator : public STD_ITERATOR_FOR_LIST(value_type),
					  public BASE_CLASS_FOR_LIST {
private:
	typedef BASE_CLASS_FOR_LIST					_base;
	typedef typename _base::StoredType			_lst;
	typedef _ListConstIterator< value_type,
								allocator_type,
								IncrementType,
								DecrementType >	_ConstIterator;
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

	value_type &			operator*() const {
		return *(_base::m_p->data);
	}
	value_type *			operator->() const {
		return _base::m_p->data;
	}

	bool					operator!=(const _ListIterator & other) const {
		return (_base::operator!=(other));
	}
	bool					operator==(const _ListIterator & other) const {
		return (_base::operator==(other));
	}
	bool					operator==(const _ConstIterator & other) const {
		return (_base::operator==(other));
	}
	bool					operator!=(const _ConstIterator & other) const {
		return (_base::operator!=(other));
	}
	_ListIterator &			operator++() {
		_base::operator++();
		return *this;
	}
	_ListIterator &			operator--() {
		_base::operator--();
		return *this;
	}
	const _ListIterator		operator--(int) {
		_lst *	tmp = _base::m_p;

		_base::operator--();
		return _ListIterator(tmp);
	}
	const _ListIterator		operator++(int) {
		_lst *	tmp = _base::m_p;

		_base::operator++();
		return _ListIterator(tmp);
	}
}; //class _ListIterator


template < typename value_type,
		   typename allocator_type,
		   typename IncrementType,
		   typename DecrementType >
class _ListConstIterator : public STD_ITERATOR_FOR_LIST(const value_type),
						   public BASE_CLASS_FOR_LIST {
private:
	typedef BASE_CLASS_FOR_LIST				_base;
	typedef typename _base::StoredType		_lst;
	typedef _ListIterator< value_type,
						   allocator_type,
						   IncrementType,
						   DecrementType >	_ListMutableIterator;
public:
	_ListConstIterator() : _base( GET_SHIFT_FUNCS ) {}
	_ListConstIterator(const _ListConstIterator & other) : _base( GET_SHIFT_FUNCS ) {
		_base::operator=(other);
	}
	_ListConstIterator(const _ListMutableIterator & other) : _base( GET_SHIFT_FUNCS ) {
		_base::operator=(other);
	}
	~_ListConstIterator() {}
	_ListConstIterator & operator=(const _ListConstIterator & other) {
		_base::operator=(other);
		return *this;
	}
	_ListConstIterator & operator=(const _ListMutableIterator & other) {
		_base::operator=(other);
		return *this;
	}
	explicit _ListConstIterator(_lst * p) : _base( p, GET_SHIFT_FUNCS ) {}

	const value_type &			operator*() const {
		return *(_base::m_p->data);
	}
	const value_type *			operator->() const {
		return _base::m_p->data;
	}

	bool						operator!=(const _ListConstIterator & other) const {
		return (_base::operator!=(other));
	}
	bool						operator==(const _ListConstIterator & other) const {
		return (_base::operator==(other));
	}
	_ListConstIterator &		operator++() {
		_base::operator++();
		return *this;
	}
	_ListConstIterator &		operator--() {
		_base::operator--();
		return *this;
	}
	const _ListConstIterator	operator--(int) {
		_lst *	tmp = _base::m_p;

		_base::operator--();
		return _ListConstIterator(tmp);
	}
	const _ListConstIterator	operator++(int) {
		_lst *	tmp = _base::m_p;

		_base::operator++();
		return _ListConstIterator(tmp);
	}
}; //class _ListConstIterator


#undef STD_ITERATOR_FOR_LIST
#undef GET_SHIFT_FUNCS
#undef BASE_CLASS_FOR_LIST
