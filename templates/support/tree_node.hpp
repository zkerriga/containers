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
//	bool			isRed() const {
//		return (color == red);
//	}
	bool			isEndNode() const {
		return (data == nullptr);
	}

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
		if (node->isEndNode())
			return antiStep(node);
		return step(node)
				? getLastNodeByStep(step(node), antiStep)
				: getFirstStepParent(node, step);
	}
	static
	TreeNode *		getFirstStepParent(TreeNode * const node,
									   typename step::type step) {
		return node->isStepChild(step)
				? getFirstStepParent(node->parent, step)
				: node->parent;
	}
	static
	TreeNode *		getLastNodeByStep(TreeNode * const root,
									  typename step::type step) {
		return (root->isEndNode() || !step(root))
				? root
				: getLastNodeByStep(step(root), step);
	}

}; //class TreeNode
