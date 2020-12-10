/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:28:15 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/10 13:28:16 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <type_traits>
#include <stdexcept>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector {
public:
	typedef T								value_type;
	typedef Alloc							allocator_type;
	typedef typename Alloc::reference		reference;
	typedef typename Alloc::const_reference	const_reference;
	typedef typename Alloc::pointer			pointer;
	typedef typename Alloc::const_pointer	const_pointer;
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;

	/* todo */
	class iterator {};
	class const_iterator {};
	class reverse_iterator {};
	class const_reverse_iterator {};
	/* todo */
};

} //namespace ft
