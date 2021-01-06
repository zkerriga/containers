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
	TreeNode *		iterateNode(const TreeNode * const node,
								typename step::type step,
								typename step::type antiStep) {
		if (end::isEnd(node)) {
			return antiStep(node);
		}
		return step(node)
				? _getLastNodeByStep(step(node), antiStep)
				: _getFirstStepParent(node, step);
	}
	inline static
	value_type &	getData(const TreeNode * const node) {
		return *(node->data);
	}
	inline static
	bool			isEndOrNull(const TreeNode * const node) {
		return (!node || end::isEnd(node));
	}
	inline static
	void			flipColor(TreeNode * const node) {
		if (!isEndOrNull(node)) {
			node->m_color = !node->m_color;
		}
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

		if ( isEndOrNull(head) ) {
			return std::make_pair(create(nodeAlloc, valAlloc, value), true);
		}
		if ( comp(value, getData(head)) ) {
			ret = _insertStepBlock(
					head->m_left,
					insert(head->m_left, value, comp, nodeAlloc, valAlloc),
					_link_type(linkLeft, head),
					end::setFirst
			);
		}
		else if ( comp(getData(head), value) ) {
			ret = _insertStepBlock(
					head->m_right,
					insert(head->m_right, value, comp, nodeAlloc, valAlloc),
					_link_type(linkRight, head),
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
	template < class Compare,
			   typename node_allocator_type,
			   typename value_allocator_type >
	static
	TreeNode *		deleteFromTree(TreeNode * head,
								   const value_type & value,
								   const Compare comp,
								   node_allocator_type & nodeAlloc,
								   value_allocator_type & valAlloc) {
		if ( isEndOrNull(head) ) {
			return head;
		}
		if ( comp(value, getData(head)) ) {
			if ( !isRed(head->m_left) && !isRed(head->m_left->m_left) ) {
				head = _moveRedLeft(head);
			}
			_linkLeftEndSafe(
					head,
					deleteFromTree(head->m_left, value, comp, nodeAlloc,
								   valAlloc)
			);
		}
		else {
			if ( isRed(head->m_left) ) {
				head = _rotateRight(head);
				_linkRightEndSafe(
						head,
						deleteFromTree(head->m_right, value, comp, nodeAlloc,
									   valAlloc)
				);
				return _fixUp(head);
			}
			if ( !comp(getData(head), value) && isEndOrNull(head->m_right) ) {
				TreeNode * const	headChild = (!head->m_left && end::isEnd(head->m_right))
										? head->m_right
										: head->m_left;
				destroy(head, nodeAlloc, valAlloc);
				return headChild;
			}
			if ( !isRed(head->m_right) && head->m_right && !isRed(head->m_right->m_left) ) {
				head = _moveRedRight(head);
			}
			if ( !comp(getData(head), value) ) {
				TreeNode * const	minNode = _getMinNode(head->m_right);
				destroy(
						_moveWholeNodeAndGetHead(head, minNode),
						nodeAlloc,
						valAlloc
				);
				head = minNode;
			}
			else {
				_linkRightEndSafe(
						head,
						deleteFromTree(head->m_right, value, comp, nodeAlloc,
									   valAlloc)
				);
			}
		}
		return _fixUp(head);
	}
	template < class Compare >
	static
	TreeNode *		findOrGetNull(TreeNode * const head,
								  const value_type & value,
								  const Compare comp) {
		if ( isEndOrNull(head) ) {
			return nullptr;
		}
		TreeNode *	next = nullptr;
		if ( comp(value, getData(head)) ) {
			next = head->m_left;
		}
		else if ( comp(getData(head), value) ){
			next = head->m_right;
		}
		else {
			return head;
		}
		return findOrGetNull(next, value, comp);
	}

private:
	template < typename node_allocator_type, typename value_allocator_type >
	static
	void			_clearTree(TreeNode * const head,
							   node_allocator_type & nodeAlloc,
							   value_allocator_type & valAlloc) {
		if (isEndOrNull(head)) {
			return;
		}
		_clearTree(head->m_right, nodeAlloc, valAlloc);
		_clearTree(head->m_left, nodeAlloc, valAlloc);
		destroy(head, nodeAlloc, valAlloc);
	}

	class _link_type {
	public:
		typedef void (*_type)(TreeNode * const, TreeNode * const);
		_link_type(const _type link, TreeNode * const head)
				: mc_link(link), m_head(head) {}
		_link_type(const _link_type & other)
				: mc_link(other.mc_link), m_head(other.m_head) {}

		~_link_type() {}
		void operator()(TreeNode * const forLink) const {
			mc_link(m_head, forLink);
		}
	private:
		_link_type() {}
		_link_type & operator= (const _link_type & other) { return *this; }

		const _type	mc_link;
		TreeNode * const	m_head;
	};
	static
	void			_linkRightEndSafe(TreeNode * const parent,
									  TreeNode * const right) {
		if ( end::isEnd(right) ) {
			end::setLast(right, parent);
		}
		else {
			linkRight(parent, right);
		}
	}
	static
	void			_linkLeftEndSafe(TreeNode * const parent,
									 TreeNode * const left) {
		if ( end::isEnd(left) ) {
			end::setFirst(left, parent);
		}
		else {
			linkLeft(parent, left);
		}
	}
	static
	void			_linkWithNewChild(TreeNode * const parent,
									  const TreeNode * const oldChild,
									  TreeNode * const newChild) {
		if (end::isEnd(parent)) {
			end::setRoot(parent, newChild);
			return;
		}
		(parent->m_right == oldChild ? linkRight : linkLeft)(parent, newChild);
	}

	inline static
	bool			_isStepChild(const TreeNode * const node,
								 const typename step::type step) {
		return (node == step(node->m_parent));
	}
	static
	TreeNode *		_getFirstStepParent(const TreeNode * const node,
										const typename step::type step) {
		return _isStepChild(node, step)
			   ? _getFirstStepParent(node->m_parent, step)
			   : node->m_parent;
	}
	static
	TreeNode *		_getLastNodeByStep(const TreeNode * const root,
									   const typename step::type step) {
		return (end::isEnd(root) || !step(root))
			   ? const_cast<TreeNode *>(root)
			   : _getLastNodeByStep(step(root), step);
	}

	static
	TreeNode *		_rotateLeft(TreeNode * const head) {
		TreeNode * const	x = head->m_right;

		_linkWithNewChild(head->m_parent, head, x);
		linkRight(head, x->m_left);
		linkLeft(x, head);

		x->m_color		= head->m_color;
		head->m_color	= mc_red;
		return x;
	}
	static
	TreeNode *		_rotateRight(TreeNode * const head) {
		TreeNode * const	x = head->m_left;

		_linkWithNewChild(head->m_parent, head, x);
		linkLeft(head, x->m_right);
		linkRight(x, head);

		x->m_color		= head->m_color;
		head->m_color	= mc_red;
		return x;
	}

	static
	const std::pair< TreeNode*, bool >
					_insertStepBlock(TreeNode * const headNext,
									 const std::pair< TreeNode*, bool > ret,
									 const _link_type link,
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
	TreeNode *		_fixUp(TreeNode * head) _NOEXCEPT {
		if (isRed(head->m_right)) {
			head = _rotateLeft(head);
		}
		if (isRed(head->m_left) && head->m_left && isRed(head->m_left->m_left)) {
			head = _rotateRight(head);
		}
		if (isRed(head->m_left) && isRed(head->m_right)) {
			_flipColors(head);
		}
		return head;
	}

	static
	TreeNode *		_moveRedLeft(TreeNode * head) _NOEXCEPT {
		_flipColors(head);
		if ( head->m_right && isRed(head->m_right->m_left) ) {
			linkRight(head, _rotateRight(head->m_right));
			head = _rotateLeft(head);
			_flipColors(head);
		}
		return head;
	}
	static
	TreeNode *		_moveRedRight(TreeNode * head) _NOEXCEPT {
		_flipColors(head);
		if ( head->m_left && isRed(head->m_left->m_left) ) {
			head = _rotateRight(head);
			_flipColors(head);
		}
		return head;
	}
	static
	TreeNode *		_getMinNode(TreeNode * const head) {
		return (!head->m_left)
			   ? head
			   : _getMinNode(head->m_left);
	}
	static
	TreeNode *		_moveWholeNodeAndGetHead(TreeNode * const head,
											 TreeNode * const minNode) {
		minNode->m_color = head->m_color;

		if (minNode->m_parent != head) {
			linkLeft(minNode->m_parent, minNode->m_right);
			linkRight(minNode, head->m_right);
		}
		_linkLeftEndSafe(minNode, head->m_left);
		_linkWithNewChild(head->m_parent, head, minNode);
		return head;
	}

	static
	TreeNode *		_flipColors(TreeNode * const head) {
		flipColor(head);
		flipColor(head->m_left);
		flipColor(head->m_right);
		return head;
	}
}; //class TreeNode
#pragma pack(pop)
