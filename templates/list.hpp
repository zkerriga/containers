/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:55:16 by zkerriga          #+#    #+#             */
/*   Updated: 2020/11/26 10:55:18 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class list {
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t size_type;

	explicit list(const allocator_type & alloc = allocator_type()) {
		//TODO;
	}
	explicit list(size_type n, const value_type & val = value_type(),
				const allocator_type & alloc = allocator_type()) {
		//TODO;
	}
	template < class InputIterator >
	list(InputIterator first, InputIterator last,
			const allocator_type & alloc = allocator_type()) {
		//TODO;
	}
	list(const list & x) {
		//TODO;
	}
	~list() {}
	list& operator= (const list& x) {
		//TODO;
	}

	class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {};
	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T const> {};
	class reverse_iterator : public iterator {};
	class const_reverse_iterator : public const_iterator {};

public:
	void push_front (const value_type & val) {
		//TODO:
//		throw std::bad_alloc();
	}
/*
	splice
	remove
	remove_if
	unique
	merge
	sort
	reverse
	get_allocator
	insert
	erase
	swap
	resize
	clear
	push_back
	pop_back
			push_front
	pop_front
	assign
	front
	back
	empty
	size
	max_size
	begin
	end
	rbegin
	rend
*/

private:
	struct t_list
	{
		value_type	data;
		t_list		*next;
		t_list		*prev;
	};
	t_list *		_list;
	size_type		_size;
}; //End class list
} //End namespace ft

#endif
