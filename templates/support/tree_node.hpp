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
	value_type *		data;
private:
	TreeNode *			m_left;
	TreeNode *			m_right;
	TreeNode *			m_parent;
	bool				m_color;

	static const bool	mc_black	= false;
	static const bool	mc_red		= true;

public:
	static
	TreeNode *		create(TreeNode * const allocatedNodeMemory,
						   value_type & constructedValue) {
		TreeNode * const	node = allocatedNodeMemory;

		node->data = &constructedValue;
		node->m_left = nullptr;
		node->m_right = nullptr;
		node->m_parent = nullptr;
		return node;
	}
	static
	void			rightLink(TreeNode * const parent, TreeNode * const right) {
		parent->m_right = right;
		if (right) {
			right->m_parent = parent;
		}
	}
	static
	void			leftLink(TreeNode * const left, TreeNode * const parent) {
		parent->m_left = left;
		if (left) {
			left->m_parent = parent;
		}
	}
	inline static
	bool			isRed(const TreeNode * const node) {
		return (node)
				? node->m_color == mc_red
				: false;
	}

	struct step {
		typedef TreeNode * (*type)(const TreeNode *);

		inline static
		TreeNode *	left(const TreeNode * const node) {
			return node->m_left;
		}
		inline static
		TreeNode *	right(const TreeNode * const node) {
			return node->m_right;
		}
	}; // subclass step

	inline static
	bool			isStepChild(const TreeNode * const node, typename step::type step) {
		return (node == step(node->m_parent));
	}
	static
	TreeNode *		iterateNode(const TreeNode * const node,
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
	TreeNode *		getFirstStepParent(const TreeNode * const node,
									   typename step::type step) {
		return isStepChild(node, step)
				? getFirstStepParent(node->m_parent, step)
				: node->m_parent;
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
			node->m_color = mc_black;
			return node;
		}
		inline static
		bool		isEndNode(const TreeNode * const node) {
			return !(node->data);
		}
		inline static
		TreeNode *	getRoot(const TreeNode * const endNode) {
			return endNode->m_parent;
		}
		inline static
		TreeNode *	getFirst(const TreeNode * const endNode) {
			return endNode->m_left;
		}
		inline static
		TreeNode *	getLast(const TreeNode * const endNode) {
			return endNode->m_right;
		}
		inline static
		void		setRoot(TreeNode * const endNode, TreeNode * const root) {
			endNode->m_parent = root;
		}
		inline static
		void		setFirst(TreeNode * const endNode, TreeNode * const firstNode) {
			endNode->m_left = firstNode;
		}
		inline static
		void		setLast(TreeNode * const endNode, TreeNode * const lastNode) {
			endNode->m_right = lastNode;
		}
	}; // subclass end

	static
	void			linkWithNewChild(TreeNode * const parent,
									 TreeNode * const oldChild,
									 TreeNode * const newChild) {
		if (end::isEndNode(parent)) {
			end::setRoot(parent, newChild);
			newChild->m_parent = parent;
			return;
		}
		(parent->m_right == oldChild)
			? rightLink(parent, newChild)
			: leftLink(newChild, parent);
	}

	static
	TreeNode *		rotateLeft(TreeNode * const head) {
		TreeNode * const	x = head->m_right;

		linkWithNewChild(head->m_parent, head, x);
		rightLink(head, x->m_left);
		leftLink(head, x);

		x->m_color		= head->m_color;
		head->m_color	= mc_red;
		return x;
	}
	static
	TreeNode *		rotateRight(TreeNode * const head) {
		TreeNode * const	x = head->m_left;

		linkWithNewChild(head->m_parent, head, x);
		leftLink(x->m_right, head);
		rightLink(x, head);

		x->m_color		= head->m_color;
		head->m_color	= mc_red;
		return x;
	}
}; //class TreeNode
#pragma pack(pop)
