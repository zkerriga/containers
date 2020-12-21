/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:06:43 by zkerriga          #+#    #+#             */
/*   Updated: 2020/12/10 20:06:44 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template < typename value_type >
class TreeNode {
public:
	value_type *	data;
	TreeNode *		left;
	TreeNode *		right;
	TreeNode *		parent;

	static
	TreeNode *		createNewNode(TreeNode * (*allocateNode)()) {
		TreeNode * const	node = allocateNode();

		rightLink(node, node);
		leftLink(node, node);
	}
	inline static
	void			rightLink(TreeNode * const parent, TreeNode * const right) {
		parent->right = right;
		right->parent = parent;
	}
	inline static
	void			leftLink(TreeNode * const left, TreeNode * const parent) {
		parent->left = left;
		left->parent = parent;
	}
	inline static
	void			setData(TreeNode * const target, value_type * const data) {
		target->data = data;
	}
};