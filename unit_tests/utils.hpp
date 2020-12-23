
#pragma once

#include <iterator>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

#include "Any.hpp"
#include "tree_node.hpp"

namespace printTree {

using tree = TreeNode< std::pair<const char, Any> >;

void	treePreOrder(const tree * const node, const tree * const end,
					 const std::function<void (const tree *, const size_t)> & func,
					 size_t lvl = 0) {
	func(node, lvl);
	if (node && node != end)
	{
		treePreOrder(tree::step::left(node), end, func, lvl + 1);
		treePreOrder(tree::step::right(node), end, func, lvl + 1);
	}
}

void	treeToTab(std::vector< std::vector< char > > & tab,
				  const tree * const root,
				  const tree * const end) {
	const size_t	lvl = tab.size();

	auto lambda = [&](const tree * const node, const size_t level) {
		if (level < lvl) {
			if (node && !tree::end::isEndNode(node)) {
				tab[level].push_back(tree::getData(node).first);
			}
			else {
				tab[level].push_back('_');
				for (size_t iLvl = level + 1; iLvl < lvl; ++iLvl) {
					for (size_t j = 0; j < std::pow(2, (iLvl - level)); ++j) {
						tab[iLvl].push_back('.');
					}
				}
			}
		}
	};
	treePreOrder(root, end, lambda, 0);
}

void	printTreeFromTab(const std::vector< std::vector<char> > & tab) {
	const size_t	size = tab.size();

	for (size_t lvl = 0; lvl < size; ++lvl) {
		std::string		offset(std::pow(2, size - lvl - 1) - 1, ' ');
		std::cout << offset << tab[lvl][0];

		std::for_each(tab[lvl].begin() + 1, tab[lvl].end(), [=](char ch) {
			std::string		offset(std::pow(2, size - lvl) - 1, ' ');
			std::cout << offset << ch;
		});
		std::cout << std::endl;
	}
}

void	print(const tree * const end, const size_t lvl) {
	std::vector< std::vector< char > >	tab(lvl);
	treeToTab(tab, tree::end::getRoot(end), end);
	printTreeFromTab(tab);
}

} //namespace printTree
