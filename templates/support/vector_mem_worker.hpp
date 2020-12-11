/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mem_worker.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 19:20:49 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/10 19:20:50 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <memory>

template < typename value_type,
		   typename allocator_type,
		   typename size_type >
class MemoryWorker {
	static
	void			_destructElements(value_type * const current,
									  const value_type * const end,
									  allocator_type & alloc) _NOEXCEPT {
		if (current == end) {
			return;
		}
		alloc.destroy(current);
		_destructElements(current + 1, end, alloc);
	}
public:
	static
	value_type *	reallocate(value_type * const sourceArray,
							   const size_type realSize,
							   const size_type prevCapacity,
							   const size_type newCapacity,
							   allocator_type & alloc) throw(std::bad_alloc) {
		value_type * const newMemory = alloc.allocate(newCapacity);
		std::memmove(newMemory, sourceArray, realSize * sizeof(value_type));
		alloc.deallocate(sourceArray, prevCapacity);
		return newMemory;
	}
	inline static
	void			fullDestruct(value_type * const sourceArray,
								 const size_type realSize,
								 const size_type capacity,
								 allocator_type & alloc) _NOEXCEPT {
		_destructElements(sourceArray, sourceArray + realSize, alloc);
		alloc.deallocate(sourceArray, capacity);
	}
}; //class MemWorker
