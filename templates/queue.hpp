/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:54:13 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/08 18:54:14 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>

namespace ft {

/*
 * The underlying container may be one of the standard container class template
 * or some other specifically designed container class.
 * This underlying container shall support at least the following operations:
 * + empty
 * + size
 * + front
 * + back
 * + push_back
 * + pop_front
 */

template <class T, class Container = std::deque<T> >
class queue {
public:
	typedef T				value_type;
	typedef Container		container_type;
	typedef std::size_t		size_type;

	explicit queue(const container_type& ctnr = container_type())
		: m_container(ctnr) {}

	bool				empty() const {
		return m_container.empty();
	}
	size_type			size() const {
		return m_container.size();
	}
	value_type &		front() {
		return m_container.front();
	}
	const value_type &	front() const {
		return m_container.front();
	}
	value_type &		back() {
		return m_container.back();
	}
	const value_type &	back() const {
		return m_container.back();
	}
	void				push(const value_type & val) {
		m_container.push_back(val);
	}
	void				pop() {
		m_container.pop_front();
	}

	friend bool			operator==(const queue & lhs, const queue & rhs) {
		return (lhs.m_container == rhs.m_container);
	}
	friend bool			operator< (const queue & lhs, const queue & rhs) {
		return (lhs.m_container < rhs.m_container);
	}

private:
	container_type		m_container;

}; //class queue

template <class T, class Container>
bool operator!=(const queue<T,Container> & lhs, const queue<T,Container> & rhs) {
	return !operator==(lhs, rhs);
}

template <class T, class Container>
bool operator<=(const queue<T,Container> & lhs, const queue<T,Container> & rhs) {
	return !operator<(rhs, lhs);
}

template <class T, class Container>
bool operator> (const queue<T,Container> & lhs, const queue<T,Container> & rhs) {
	return operator<(rhs, lhs);
}

template <class T, class Container>
bool operator>=(const queue<T,Container> & lhs, const queue<T,Container> & rhs) {
	return !operator<(lhs, rhs);
}

} //namespace ft
