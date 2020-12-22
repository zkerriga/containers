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
							   value_type & constructedValue) {
		TreeNode * const	node = allocatedNodeMemory;

		node->data = &constructedValue;
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;
		return node;
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
//	bool			isRed() const {
//		return (color == red);
//	}
	struct step {
		typedef TreeNode * (*type)(const TreeNode *);

		inline static
		TreeNode *	left(const TreeNode * const node) {
			return node->left;
		}
		inline static
		TreeNode *	right(const TreeNode * const node) {
			return node->right;
		}
	};

	bool			isStepChild(typename step::type step) const {
		return (this == step(this->parent));
	}
	static
	TreeNode *		iterateNode(TreeNode * const node,
								typename step::type step,
								typename step::type antiStep) {
		if (step(node)) {
			return getLastNodeByStep(step(node), antiStep);
		}
		return getFirstStepParent(node, step);
	}
	static
	TreeNode *		getFirstStepParent(TreeNode * const node,
									   typename step::type step) {
		if (!node->isStepChild(step)) {
			return node->parent;
		}
		return getFirstStepParent(node->parent, step);
	}
	static
	TreeNode *		getLastNodeByStep(TreeNode * const root,
									  typename step::type step) {
		if (root->isEndNode() || !step(root)) {
			return root;
		}
		return getLastNodeByStep(step(root), step);
	}

//	inline
//	bool			isLeftChild() const {
//		return (this == this->parent->left);
//	}

//	static
//	TreeNode *		getFirstLeftParent(const TreeNode * const node) noexcept {
//		if (!node->isLeftChild()) {
//			return node->parent;
//		}
//		return getFirstLeftParent(node->parent);
//	}
//	static
//	TreeNode *		getFirstRightParent(const TreeNode * const node) noexcept {
//		if (node->isLeftChild()) {
//			return node->parent;
//		}
//		return getFirstRightParent(node->parent);
//	}

//	static
//	TreeNode *		getPrevNode(const TreeNode * const node) noexcept {
//		if (node->left) {
//			return getMaximalNode(node->left);
//		}
//		return getFirstLeftParent(node);
//	}
//	static
//	TreeNode *		getNextNode(const TreeNode * const node) noexcept {
//		if (node->right) {
//			return getMinimalNode(node->right);
//		}
//		return getFirstRightParent(node);
//	}
//	static
//	TreeNode *		getMinimalNode(const TreeNode * const root) noexcept {
//		if (root->isEndNode() || !root->left) {
//			return root;
//		}
//		return getMinimalNode(root->left);
//	}
//	static
//	TreeNode *		getMaximalNode(const TreeNode * const root) noexcept {
//		if (root->isEndNode() || !root->right) {
//			return root;
//		}
//		return getMaximalNode(root->right);
//	}

}; //class TreeNode
