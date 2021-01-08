/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:27:54 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/08 14:27:55 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>

namespace ft {

/*
 * The underlying container may be any of the standard container class templates
 * or some other specifically designed container class.
 * The container shall support the following operations:
 * + empty
 * + size
 * + back
 * + push_back
 * + pop_back
*/

template <class T, class Container = std::deque<T> >
class stack {
public:
	typedef T				value_type;
	typedef Container		container_type;
	typedef std::size_t		size_type;

	explicit stack(const container_type & ctnr = container_type())
		: m_container(ctnr) {}

	bool				empty() const {
		return m_container.empty();
	}
	size_type			size() const {
		return m_container.size();
	}
	value_type &		top() {
		return m_container.back();
	}
	const value_type &	top() const {
		return m_container.back();
	}
	void				push(const value_type & val) {
		m_container.push_back(val);
	}
	void				pop() {
		m_container.pop_back();
	}

private:
	container_type		m_container;

}; //class stack

/* todo: non-member */
template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
/* todo: non-member */

} //namespace ft
