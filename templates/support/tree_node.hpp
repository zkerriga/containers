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

#pragma pack(push,1)
template < typename value_type >
struct TreeNode {
	value_type *	data;
private:
	TreeNode *		left;
	TreeNode *		right;
	TreeNode *		parent;
	bool			color;

	static const bool	black	= false;
	static const bool	red		= true;

public:
	static
	TreeNode *		create(TreeNode * const allocatedNodeMemory,
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
	inline static
	bool			isRed(const TreeNode * const node) {
		return node->color;
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
	}; // subclass step

	inline static
	bool			isStepChild(const TreeNode * const node, typename step::type step) {
		return (node == step(node->parent));
	}
	static
	TreeNode *		iterateNode(TreeNode * const node,
								typename step::type step,
								typename step::type antiStep) {
		if (end::isEndNode(node)) {
			return antiStep(node);
		}
		return step(node)
				? getLastNodeByStep(step(node), antiStep)
				: getFirstStepParent(node, step);
	}
	static
	TreeNode *		getFirstStepParent(TreeNode * const node,
									   typename step::type step) {
		return isStepChild(node, step)
				? getFirstStepParent(node->parent, step)
				: node->parent;
	}
	static
	TreeNode *		getLastNodeByStep(TreeNode * const root,
									  typename step::type step) {
		return (end::isEndNode(root) || !step(root))
				? root
				: getLastNodeByStep(step(root), step);
	}

	inline static
	const value_type &	getData(const TreeNode * const node) {
		return *(node->data);
	}

	struct end {
		static
		TreeNode *	create(TreeNode * const allocatedNodeMemory) {
			TreeNode * const	node = allocatedNodeMemory;

			node->data = nullptr;
			rightLink(node, node);
			leftLink(node, node);
			node->color = black;
			return node;
		}
		inline static
		bool		isEndNode(const TreeNode * const node) {
			return !(node->data);
		}
		inline static
		TreeNode *	getRoot(const TreeNode * const endNode) {
			return endNode->parent;
		}
		inline static
		TreeNode *	getFirst(const TreeNode * const endNode) {
			return endNode->left;
		}
		inline static
		TreeNode *	getLast(const TreeNode * const endNode) {
			return endNode->right;
		}
		inline static
		void		setRoot(TreeNode * const endNode, TreeNode * const root) {
			endNode->parent = root;
		}
		inline static
		void		setFirst(TreeNode * const endNode, TreeNode * const firstNode) {
			endNode->left = firstNode;
		}
		inline static
		void		setLast(TreeNode * const endNode, TreeNode * const lastNode) {
			endNode->right = lastNode;
		}
	}; // subclass end

}; //class TreeNode
#pragma pack(pop)
