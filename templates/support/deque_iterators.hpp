/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_iterators.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:07:51 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/07 15:07:52 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <type_traits>

template <typename value_type>
class DequeIterator : public std::iterator<std::random_access_iterator_tag,value_type> {
	typedef std::iterator<std::random_access_iterator_tag,value_type>	_stdIt;
	typedef typename _stdIt::difference_type							_difference_type;
	typedef typename _stdIt::pointer									_pointer;
	typedef typename _stdIt::reference									_reference;
public:
public:
	DequeIterator();
	DequeIterator(const DequeIterator & x);
	virtual ~DequeIterator();
	DequeIterator & operator= (const DequeIterator & x);
	_reference			operator* () const;
	_pointer			operator->() const;

	_reference			operator[](_difference_type n) const;
	DequeIterator		operator+ (_difference_type n) const {
		DequeIterator	it(*this);

		it += n;
		return it;
	}
	DequeIterator		operator- (_difference_type n) const {
		DequeIterator	it(*this);

		it -= n;
		return it;
	}

	DequeIterator &		operator++();
	DequeIterator		operator++(int) {
		DequeIterator	save(*this);

		operator++();
		return save;
	}
	DequeIterator &		operator--();
	DequeIterator		operator--(int) {
		DequeIterator	save(*this);

		operator--();
		return save;
	}

	DequeIterator &		operator+=(_difference_type n);
	DequeIterator &		operator-=(_difference_type n) {
		*this += -n;
		return *this;
	}

	bool				operator==(const DequeIterator & other) const;
	bool				operator!=(const DequeIterator & other) const {
		return !operator==(other);
	}

private:

};


