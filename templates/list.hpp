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

#pragma once

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class list {
public:
	using value_type		= T;
	using allocator_type	= Alloc;
	using reference			= typename Alloc::reference;
	using const_reference	= typename Alloc::const_reference;
	using pointer			= typename Alloc::pointer;
	using const_pointer		= typename Alloc::const_pointer;
	using difference_type	= std::ptrdiff_t;
	using size_type			= std::size_t;

	explicit list(const allocator_type & alloc = allocator_type());
	explicit list(size_type n, const value_type & val = value_type(),
				const allocator_type & alloc = allocator_type());
	template < class InputIterator >
	list(InputIterator first, InputIterator last,
			const allocator_type & alloc = allocator_type());
	list(const list & x);
	~list();
	list& operator= (const list& x);

	class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {};
	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T const> {};
	class reverse_iterator : public iterator {};
	class const_reverse_iterator : public const_iterator {};

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	bool empty() const;
	size_type size() const;
	size_type max_size() const;

	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last);
	void assign (size_type n, const value_type& val);
	void push_front (const value_type& val);
	void pop_front();
	void push_back (const value_type & val);
	void pop_back();
	iterator insert (iterator position, const value_type& val);
	void insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last);
	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);
	void swap (list & x);
	void resize (size_type n, value_type val = value_type());
	void clear();

	void splice (iterator position, list& x);
	void splice (iterator position, list& x, iterator i);
	void splice (iterator position, list& x, iterator first, iterator last);

private:
	struct t_list
	{
		value_type	data;
		t_list		*next;
		t_list		*prev;
	};
	t_list *		_list;
	size_type		_size;
}; //class list

} //namespace ft
