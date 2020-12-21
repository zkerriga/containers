#include "gtest/gtest.h"
#include <iterator>
#include <vector>
#include <cmath>

namespace tree {
	typedef struct		s_tree
	{
		char			content;
		struct s_tree	*left;
		struct s_tree	*right;
	}					t_tree;

	void	ft_leafadd(t_tree **tree, t_tree *fresh)
	{
		if (*tree)
		{
			if ((*tree)->content < fresh->content)
				ft_leafadd(&(*tree)->left, fresh);
			else
				ft_leafadd(&(*tree)->right, fresh);
		}
		else
			*tree = fresh;
	}
	t_tree	*ft_leafnew(char content)
	{
		t_tree	*leaf;

		leaf = (t_tree *)malloc(sizeof(t_tree));
		if (leaf)
		{
			leaf->content = content;
			leaf->left = nullptr;
			leaf->right = nullptr;
		}
		return (leaf);
	}
	void	ft_treepreorder(t_tree *tree, t_tree * end,
							const std::function<void (t_tree*, size_t)> & func,
							size_t lvl = 0) {
		func(tree, lvl);
		if (tree != end)
		{
			ft_treepreorder(tree->left, end, func, lvl + 1);
			ft_treepreorder(tree->right, end, func, lvl + 1);
		}
	}
}

std::vector< std::vector<char> >
treeToTab(tree::t_tree * root, tree::t_tree * end, size_t lvl) {
	std::vector< std::vector<char> >	tab(lvl);

	auto lambda = [&](tree::t_tree * tree, size_t level) {
		if (level < lvl) {
			if (tree) {
				tab[level].push_back(tree->content);
			}
			else {
				tab[level].push_back('0');
				for (size_t iLvl = level + 1; iLvl < lvl; ++iLvl) {
					for (size_t j = 0; j < std::pow(2, (iLvl - level)); ++j) {
						tab[iLvl].push_back('.');
					}
				}
			}
		}
	};
	tree::ft_treepreorder(root, end, lambda, 0);
	return tab;
}

#include <algorithm>
void printTreeFromTab(std::vector< std::vector<char> > & tab) {
	std::cout << "TREE:" << std::endl;
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

char getRandAlpha() {
	return static_cast<char>(random() % ('z' - 'a') + 'a');
}

TEST(tree, first) {
	tree::t_tree *	root = nullptr;

	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < 2; ++i) {
		tree::ft_leafadd(&root, tree::ft_leafnew(getRandAlpha()));
	}

	std::vector< std::vector<char> > tab = treeToTab(root, nullptr, 3);
	printTreeFromTab(tab);
}