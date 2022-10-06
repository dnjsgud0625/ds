#pragma once

#include "TreeNode.h"
#include <iostream>

#include <crtdbg.h>
#include <stack>
using namespace std;

class BinarySearchTree
{
	friend class TransferWindowManager;
private:
	TreeNode * m_root;

public:
	BinarySearchTree() { m_root = NULL; }
	~BinarySearchTree() {
		Release(m_root);
	};
;
	void insert(SoccerPlayerData& data); //insert function
	void deletion(int ability); // ability = key
	static void Inorder(TreeNode * ord); //inorder function
	void Release(TreeNode* rel);

	friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree) {
	// fill in your code to print in-order traversal of a binary search tree
		
		Inorder(tree.m_root);
		return os;
	}
};
