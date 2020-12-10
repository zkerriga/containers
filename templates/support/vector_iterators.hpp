/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:06:43 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/10 20:06:44 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <stdexcept>

template < typename value_type, typename difference_type >
class _VectorIterator : public std::iterator< std::random_access_iterator_tag,
											  value_type,
											  difference_type,
											  value_type *,
											  value_type & > {
public:
	_VectorIterator();
	_VectorIterator(const _VectorIterator & other);
	~_VectorIterator();
	_VectorIterator& operator = (const _VectorIterator & other);

	value_type &		operator* () const _NOEXCEPT {
		/*todo*/
	}
	value_type *		operator->() const _NOEXCEPT {
		/*todo*/
	}

	_VectorIterator		operator+ (difference_type n) const _NOEXCEPT {
		/*todo*/
	}
	_VectorIterator		operator- (difference_type n) const _NOEXCEPT {
		/*todo*/
	}
	_VectorIterator &	operator-=(difference_type n) _NOEXCEPT {
		/*todo*/
	}
	_VectorIterator &	operator+=(difference_type n) _NOEXCEPT {
		/*todo*/
	}
	value_type &		operator[](difference_type n) const _NOEXCEPT {
		/*todo*/
	}

	bool				operator==(const _VectorIterator & other) const _NOEXCEPT {
		/*todo*/
	}
	bool				operator!=(const _VectorIterator & other) const _NOEXCEPT {
		/*todo*/
	}
	bool				operator< (const _VectorIterator & other) const _NOEXCEPT {
		/*todo*/
	}
	bool				operator> (const _VectorIterator & other) const _NOEXCEPT {
		/*todo*/
	}
	bool				operator>=(const _VectorIterator & other) const _NOEXCEPT {
		/*todo*/
	}
	bool				operator<=(const _VectorIterator & other) const _NOEXCEPT {
		/*todo*/
	}

	_VectorIterator &	operator++() _NOEXCEPT {
		/*todo*/
	}
	_VectorIterator &	operator--() _NOEXCEPT {
		/*todo*/
	}
	_VectorIterator		operator++(int) _NOEXCEPT {
		/*todo*/
	}
	_VectorIterator		operator--(int) _NOEXCEPT {
		/*todo*/
	}


private:

};
