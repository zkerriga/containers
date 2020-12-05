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
	_baseIterator(_lst * p) : m_lst(p) {}

protected:
	_lst *		m_lst;

}; //class _baseIterator


template < typename value_type, typename return_value_type,
		   typename allocator_type,
		   typename PlusPlusType, typename MinusMinusType >
class _listIterator : public std::iterator< std::bidirectional_iterator_tag, return_value_type >,
					  public _baseIterator< value_type, allocator_type > {
private:
	typedef ListNode< value_type,allocator_type >			_lst;
	typedef _baseIterator< value_type,allocator_type >		_base;
	typedef _listIterator< value_type, value_type,
						   allocator_type, PlusPlusType,
						   MinusMinusType >					_nonConstantIterator;

public:
	_listIterator() : _base() {}
	_listIterator(const _nonConstantIterator & other) {
		*this = other;
	}
	~_listIterator() {}
	_listIterator &	operator=(const _nonConstantIterator & other) {
		_base::operator=(other);
		return *this;
	}

	_listIterator(_lst * p) : _base(p) {}

	template < typename InputIterator,
			bool Enable = std::is_same<InputIterator, _listIterator>::value
						  || std::is_same<InputIterator, _nonConstantIterator>::value,
			typename = typename std::enable_if< Enable >::type >
	void construct(const InputIterator & other) {
		std::cout << "COMPLETE! ptr = " << &other <<  std::endl;
	}

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
		_lst::getStepFunction(PlusPlusType())(_base::m_lst);
		return *this;
	}
	_listIterator &			operator--() {
		_lst::getStepFunction(MinusMinusType())(_base::m_lst);
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
