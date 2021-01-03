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
	template < typename node_allocator_type, typename value_allocator_type >
	static
	void			destroy(TreeNode * const node,
							node_allocator_type & nodeAlloc,
							value_allocator_type & valAlloc) {
		valAlloc.destroy(node->data);
		valAlloc.deallocate(node->data, 1);
		nodeAlloc.deallocate(node, 1);
	}
	template < typename node_allocator_type, typename value_allocator_type >
	static
	void			clearTree(TreeNode * const endNode,
							  node_allocator_type & nodeAlloc,
							  value_allocator_type & valAlloc) {
		_clearTree(
			end::getRoot(endNode),
			nodeAlloc,
			valAlloc
		);
		end::roundOff(endNode);
	}
	template < typename node_allocator_type, typename value_allocator_type >
	static
	void			_clearTree(TreeNode * const head,
							   node_allocator_type & nodeAlloc,
							   value_allocator_type & valAlloc) {
		if (!head || end::isEnd(head)) {
			return;
		}
		_clearTree(head->m_right, nodeAlloc, valAlloc);
		_clearTree(head->m_left, nodeAlloc, valAlloc);
		destroy(head, nodeAlloc, valAlloc);
	}

	static
	void			linkRight(TreeNode * const parent, TreeNode * const right) {
		parent->m_right = right;
		if (right) {
			right->m_parent = parent;
		}
	}
	static
	void			linkLeft(TreeNode * const parent, TreeNode * const left) {
		parent->m_left = left;
		if (left) {
			left->m_parent = parent;
		}
	}
	static
	void			linkLeftEndSafe(TreeNode * const parent, TreeNode * const left) {
		if ( end::isEnd(left) ) {
			end::setFirst(left, parent);
		}
		else {
			linkLeft(parent, left);
		}
	}
	static
	void			linkRightEndSafe(TreeNode * const parent, TreeNode * const right) {
		if ( end::isEnd(right) ) {
			end::setLast(right, parent);
		}
		else {
			linkRight(parent, right);
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
	TreeNode *		getLastNodeByStep(const TreeNode * const root,
									  typename step::type step) {
		return (end::isEnd(root) || !step(root))
				? const_cast<TreeNode *>(root)
				: getLastNodeByStep(step(root), step);
	}

	inline static
	value_type &	getData(const TreeNode * const node) {
		return *(node->data);
	}

	struct end {
		template < typename node_allocator_type >
		static
		TreeNode *	create(node_allocator_type & alloc) {
			TreeNode * const	end = alloc.allocate(1);

			end->data = nullptr;
			roundOff(end);
			end->m_color = mc_black;
			return end;
		}
		template < typename node_allocator_type >
		inline static
		void		destroy(TreeNode * const end,
							node_allocator_type & alloc) {
			alloc.deallocate(end, 1);
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
		inline static
		void		roundOff(TreeNode * const endNode) {
			linkRight(endNode, endNode);
			linkLeft(endNode, endNode);
		}
	}; // subclass end

	static
	void			linkWithNewChild(TreeNode * const parent,
									 TreeNode * const oldChild,
									 TreeNode * const newChild) {
		if (end::isEnd(parent)) {
			end::setRoot(parent, newChild);
			return;
		}
		(parent->m_right == oldChild ? linkRight : linkLeft)(parent, newChild);
	}

	static
	TreeNode *		rotateLeft(TreeNode * const head) {
		TreeNode * const	x = head->m_right;

		linkWithNewChild(head->m_parent, head, x); /* todo: возможно, это не нужно */
		linkRight(head, x->m_left);
		linkLeft(x, head);

		x->m_color		= head->m_color;
		head->m_color	= mc_red;
		return x;
	}
	static
	TreeNode *		rotateRight(TreeNode * const head) {
		TreeNode * const	x = head->m_left;

		linkWithNewChild(head->m_parent, head, x);
		linkLeft(head, x->m_right);
		linkRight(x, head);

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
		std::pair< TreeNode*, bool >	ret;

		if ( !head || end::isEnd(head) ) {
			return std::make_pair(create(nodeAlloc, valAlloc, value), true);
		}
		if ( comp(value, getData(head)) ) {
			ret = _insertStepBlock(
				head->m_left,
				insert(head->m_left, value, comp, nodeAlloc, valAlloc),
				link_type(linkLeft, head),
				end::setFirst
			);
		}
		else if ( comp(getData(head), value) ) {
			ret = _insertStepBlock(
				head->m_right,
				insert(head->m_right, value, comp, nodeAlloc, valAlloc),
				link_type(linkRight, head),
				end::setLast
			);
		}
		else {
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
		link_type(const _link_type link, TreeNode * const head)
			: mc_link(link), m_head(head) {}
		link_type(const link_type & other)
			: mc_link(other.mc_link), m_head(other.m_head) {}

		~link_type() {}
		void operator()(TreeNode * const forLink) const {
			mc_link(m_head, forLink);
		}
	private:
		link_type() {}
		link_type & operator= (const link_type & other) { return *this; }

		const _link_type	mc_link;
		TreeNode * const	m_head;
	};
	static
	const std::pair< TreeNode*, bool >
					_insertStepBlock(TreeNode * const headNext,
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
	TreeNode *		_fixUp(TreeNode * head) {
		if (isRed(head->m_right)) {
			head = rotateLeft(head);
		}
		if (isRed(head->m_left) && head->m_left && isRed(head->m_left->m_left)) {
			head = rotateRight(head);
		}
		if (isRed(head->m_left) && isRed(head->m_right)) {
			flipColors(head);
		}
		return head;
	}

	static
	TreeNode *		moveRedLeft(TreeNode * head) {
		flipColors(head);
		if ( isRed(head->m_right->m_left) ) {
			head->m_right = rotateRight(head->m_right); /* todo: заменить замену парента вот тут на линк */
			head = rotateLeft(head);
			flipColors(head);
		}
		return head;
	}
	static
	TreeNode *		moveRedRight(TreeNode * head) {
		flipColors(head);
		if ( head->m_left && isRed(head->m_left->m_left) ) {
			head = rotateRight(head);
			flipColors(head);
		}
		return head;
	}
	template < typename node_allocator_type, typename value_allocator_type >
	static
	TreeNode *		deleteMin(TreeNode * head,
							  node_allocator_type & treeAlloc,
							  value_allocator_type & valAlloc) {
		TreeNode * const left = head->m_left;

		if (!left || end::isEnd(left)) {
			destroy(head, treeAlloc, valAlloc);
			return left;
		}
		if ( !isRed(head->m_left) && head->m_left && !isRed(head->m_left->m_left) ) {
			head = moveRedLeft(head);
		}
		TreeNode * const ret = deleteMin(head->m_left, treeAlloc, valAlloc);
		linkLeftEndSafe(head, ret);
		return _fixUp(head);
	}
	static
	TreeNode *		getMinNode(TreeNode * const head) {
		if (!head) {
			return nullptr; /* It's an error */
		}
		TreeNode * const	right	= head->m_right;
		TreeNode * const	left	= head->m_left;
		if (!left && !right) {
			return head;
		}
		return getMinNode( left ? left : right );
	}

	template < class Compare,
			   typename node_allocator_type,
			   typename value_allocator_type,
			   class print_type >
	static
	std::pair<TreeNode *, bool>
					deleteFromTree(TreeNode * head,
								   const value_type & value,
								   const Compare comp,
								   node_allocator_type & nodeAlloc,
								   value_allocator_type & valAlloc,
								   const print_type printTree) {
//		printTree(); /* todo debug */
		if (end::isEnd(head)) {
			return std::make_pair(head, false);
		}
		const bool					less	= comp(value, getData(head));
		std::pair<TreeNode *, bool>	ret		= std::make_pair(nullptr, false);

		if (less) {
			if ( !isRed(head->m_left) && head->m_left && !isRed(head->m_left->m_left) ) {
				head = moveRedLeft(head);
			}
			ret = deleteFromTree(head->m_left, value, comp, nodeAlloc, valAlloc, printTree);
			linkLeftEndSafe(head, ret.first);
//			printTree(); /* todo debug */
		}
		else {
			const bool		equal = !comp(getData(head), value);

			if (isRed(head->m_left)) {
				head = rotateRight(head);
				ret = deleteFromTree(head->m_right, value, comp, nodeAlloc, valAlloc, printTree);
				linkRightEndSafe(head, ret.first);
//				printTree(); /* todo debug */
				return std::make_pair(_fixUp(head), ret.second);
			}
			if ( equal && (!head->m_right || end::isEnd(head->m_right)) ) {
				TreeNode * const headRight = head->m_right;
				destroy(head, nodeAlloc, valAlloc);
				return std::make_pair(headRight, true);
			}
			if ( !isRed(head->m_right) && head->m_right && !isRed(head->m_right->m_left) ) {
				head = moveRedRight(head);
//				printTree(); /* todo debug */
			}
			if (equal) {
				TreeNode * const	minNode = getMinNode(head->m_right);
				destroy(
					moveWholeNodeAndGetHead(head, minNode),
					nodeAlloc,
					valAlloc
				);
				head = minNode;
				ret.second = true;
//				printTree(); /* todo debug */
			}
			else {
				ret = deleteFromTree(head->m_right, value, comp, nodeAlloc, valAlloc, printTree);
				linkRightEndSafe(head, ret.first);
//				printTree(); /* todo debug */
			}
		}
		return std::make_pair(_fixUp(head), ret.second);
	}
	static
	TreeNode *		moveWholeNodeAndGetHead(TreeNode * const head,
											TreeNode * const minNode) {
		TreeNode * const headLeft	= head->m_left;
		TreeNode * const headRight	= head->m_right;

		minNode->m_color = head->m_color;

		linkLeftEndSafe(minNode, headLeft);
		if (minNode->m_parent != head) {
			linkRight(minNode, headRight);
			linkLeft(minNode->m_parent, nullptr);
		}
		else {
			linkRight(minNode, nullptr);
		}
		linkWithNewChild(head->m_parent, head, minNode);
		return head;
	}
}; //class TreeNode
#pragma pack(pop)
