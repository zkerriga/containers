/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_chain.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:23:41 by zkerriga          #+#    #+#             */
/*   Updated: 2021/01/06 17:23:42 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "list.hpp"
#include "vector.hpp"

template <typename value_type, typename allocator_type>
struct BlockChain {
	typedef ft::list<ft::vector<value_type, allocator_type>, allocator_type> type;
	static const size_t		blockSize = sizeof(value_type) < 256
											? 4096 / sizeof(value_type)
											: 16;
};
