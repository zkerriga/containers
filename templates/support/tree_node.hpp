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
	template < typename node_allocator_type, typename value_allocator_type >
	static
	TreeNode *		create(node_allocator_type & nodeAlloc,
						   value_allocator_type & valAlloc,
						   const value_type & value) {
		TreeNode * const	node = nodeAlloc.allocate(1);

		node->data = valAlloc.allocate(1);
		valAlloc.construct(node->data, value);
		node->m_left = nullptr;
		node->m_right = nullptr;
		node->m_parent = nullptr;
		node->m_color = mc_red;
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
		if (end::isEnd(node)) {
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
		return (end::isEnd(root) || !step(root))
				? root
				: getLastNodeByStep(step(root), step);
	}

	inline static
	const value_type &	getData(const TreeNode * const node) {
		return *(node->data);
	}

	struct end {
		template < typename node_allocator_type >
		static
		TreeNode *	create(node_allocator_type & alloc) {
			TreeNode * const	node = alloc.allocate(1);

			node->data = nullptr;
			rightLink(node, node);
			leftLink(node, node);
			node->m_color = mc_black;
			return node;
		}
		inline static
		bool		isEnd(const TreeNode * const node) {
			return node
					? !(node->data)
					: false;
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
			root->m_parent = endNode;
		}
		inline static
		void		setFirst(TreeNode * const endNode, TreeNode * const firstNode) {
			endNode->m_left = firstNode;
			firstNode->m_left = endNode;
		}
		inline static
		void		setLast(TreeNode * const endNode, TreeNode * const lastNode) {
			endNode->m_right = lastNode;
			lastNode->m_right = endNode;
		}
	}; // subclass end

	static
	void			linkWithNewChild(TreeNode * const parent,
									 TreeNode * const oldChild,
									 TreeNode * const newChild) {
		if (end::isEnd(parent)) {
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

		linkWithNewChild(head->m_parent, head, x); /* todo: возможно, это не нужно */
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
	inline static
	void			flipColor(TreeNode * const node) {
		if (node && !end::isEnd(node)) {
			node->m_color = !node->m_color;
		}
	}
	static
	TreeNode *		flipColors(TreeNode * const head) {
		flipColor(head);
		flipColor(head->m_left);
		flipColor(head->m_right);
		return head;
	}

	template < class Compare,
			   typename node_allocator_type,
			   typename value_allocator_type >
	static
	const std::pair< TreeNode*, bool >
					insert(TreeNode * const head,
						   const value_type & value,
						   const Compare comp,
						   node_allocator_type & nodeAlloc,
						   value_allocator_type & valAlloc) {
		typedef std::pair< TreeNode*, bool >	pair_type;
		pair_type		ret;

		if ( !head || end::isEnd(head) ) {
			return std::make_pair(create(nodeAlloc, valAlloc, value), true);
		}
		if ( comp(value, getData(head)) ) {
			/* if newNode->data < head->data */
			ret = _insertStepBlock(
				head,
				head->m_left,
				insert(head->m_left, value, comp, nodeAlloc, valAlloc),
				link_type(leftLink, head),
				end::setFirst
			);
		}
		else if ( comp(getData(head), value) ) {
			/* if newNode->data > head->data */
			ret = _insertStepBlock(
					head,
					head->m_right,
					insert(head->m_right, value, comp, nodeAlloc, valAlloc),
					link_type(rightLink, head),
					end::setLast
			);
		}
		else {
			/* if newNode->data == head->data */
			return std::make_pair(head, false);
		}
		if (ret.second) {
			_fixUp(head); /* Balancing the tree */
		}
		return ret;
	}
	class link_type {
	public:
		typedef void (*_link_type)(TreeNode * const, TreeNode * const);
		link_type(_link_type link, TreeNode * const head)
			: mc_link(link), m_head(head) {}
		link_type(const link_type & other)
			: mc_link(other.mc_link), m_head(other.m_head) {}

		~link_type() {}
		void operator()(TreeNode * const forLink) const {
			if (mc_link == rightLink) {
				mc_link(m_head, forLink);
			}
			else {
				mc_link(forLink, m_head);
			}
		}
	private:
		link_type() {}
		link_type & operator= (const link_type & other) { return *this; }

		const _link_type	mc_link;
		TreeNode * const	m_head;
	};
	static
	const std::pair< TreeNode*, bool >
					_insertStepBlock(TreeNode * const head,
									 TreeNode * const headNext,
									 const std::pair< TreeNode*, bool > ret,
									 const link_type link,
									 void (*endSet)(TreeNode * const, TreeNode * const)) {
		if (ret.second) {
			TreeNode * const	end = end::isEnd(headNext) ? headNext : nullptr;

			if (!headNext || end) {
				link(ret.first);
			}
			if (end) {
				endSet(end, ret.first);
			}
		}
		return ret;
	}
	static
	void			_fixUp(TreeNode * head) {
		if (isRed(head->m_right)) {
			head = rotateLeft(head);
		}
		if (isRed(head->m_left) && head->m_left && isRed(head->m_left->m_left)) {
			head = rotateRight(head);
		}
		if (isRed(head->m_left) && isRed(head->m_right)) {
			flipColors(head);
		}
	}
}; //class TreeNode
#pragma pack(pop)
