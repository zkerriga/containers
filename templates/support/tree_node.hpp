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
struct TreeNode {
	static const bool	black	= false;
	static const bool	red		= true;

	value_type *	data;
	TreeNode *		left;
	TreeNode *		right;
	TreeNode *		parent;
	bool			color;

	static
	TreeNode *		createEndNode(TreeNode * const allocatedNodeMemory) {
		TreeNode * const	node = allocatedNodeMemory;

		node->data = nullptr;
		rightLink(node, node);
		leftLink(node, node);
		node->color = black;
		return node;
	}
	static
	TreeNode *		createNode(TreeNode * const allocatedNodeMemory,
							   const value_type & constructedValue) {
		TreeNode * const	node = allocatedNodeMemory;

		node->data = &constructedValue;
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;
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
	inline
	bool			isEndNode() const {
		return (data == nullptr);
	}
	inline
	bool			isLeftChild() const {
		return (this == this->parent->left);
	}
//	bool			isRed() const {
//		return (color == red);
//	}
	static
	TreeNode *		getPrevNode(const TreeNode * const node) noexcept {
		if (node->left) {
			return getMaximalNode(node->left);
		}
		return getFirstLeftParent(node);
	}
	static
	TreeNode *		getNextNode(const TreeNode * const node) noexcept {
		if (node->right) {
			return getMinimalNode(node->right);
		}
		return getFirstRightParent(node);
	}
	static
	TreeNode *		getFirstLeftParent(const TreeNode * const node) noexcept {
		if (!node->isLeftChild()) {
			return node->parent;
		}
		return getFirstLeftParent(node->parent);
	}
	static
	TreeNode *		getFirstRightParent(const TreeNode * const node) noexcept {
		if (node->isLeftChild()) {
			return node->parent;
		}
		return getFirstRightParent(node->parent);
	}
	static
	TreeNode *		getMinimalNode(const TreeNode * const root) noexcept {
		if (root->isEndNode() || !root->left) {
			return root;
		}
		return getMinimalNode(root->left);
	}
	static
	TreeNode *		getMaximalNode(const TreeNode * const root) noexcept {
		if (root->isEndNode() || !root->right) {
			return root;
		}
		return getMaximalNode(root->right);
	}
}; //class TreeNode
