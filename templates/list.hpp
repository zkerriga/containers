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

	class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {};
	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T const> {};
	class reverse_iterator : public iterator {};
	class const_reverse_iterator : public const_iterator {};

protected:

private:

}; //End class list

} //End namespace ft

#endif
