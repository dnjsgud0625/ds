#include "BinarySearchTree.h"
#include <iostream>
using namespace std;
void BinarySearchTree::insert(SoccerPlayerData& data) //insert function
{
	TreeNode *root = m_root, *pp = NULL;
	while (root) {
		pp = root; //pp is parent of root
		if (data.m_ability > root->m_data.m_ability) //bigger than root's data
			root = root->m_right; //go to right
		else if (data.m_ability < root->m_data.m_ability) //smaller than root's data
			root = root->m_left; //go to left
		else { //if data is same
			root->m_data.m_ability = data.m_ability;
			return;
		}
	}
	//start insert
	root = new TreeNode(data);
	if (m_root != NULL) //if tree is not empty
		if (data.m_ability < pp->m_data.m_ability) //smaller than root's data
			pp->m_left = root; //go to left
		else //bigger than root's data
			pp->m_right = root; //go to right
	else
		m_root = root; //if not root, root is m_root
}

void BinarySearchTree::deletion(int ability) //deletion function
{
	TreeNode *p = m_root, *q = NULL; //q is p's parent
	while (p->m_data.m_ability != ability) { //search part
		q = p; //q is parent of p
		if (ability < p->m_data.m_ability) //smaller than root's data
			p = p->m_left;
		else //bigger than root's data
			p = p->m_right;
	}
	if (p == NULL) //BST doesn't exist
		return; //not found
	if (p->m_left == NULL && p->m_right == NULL) { //if leaf node
		if (q == NULL) {//if p is root
			m_root = NULL; //delete root's data
		}
		else if (q->m_left == p) //delete left
			q->m_left = NULL;
		else //delete right
			q->m_right = NULL;
		delete p; //return
	}
	else if ((p->m_left == NULL) || (p->m_right == NULL)) { //if only have one child
		TreeNode * child;
		child = (p->m_left != NULL) ? p->m_left : p->m_right;
		//true : left child, false : right child
		if (q) { //q
			if (q->m_left == p) //left chld is p
				q->m_left = child;
			else //right child is p
				q->m_right = child;
		}
		else //q is null
			m_root = child;
	}
	//p has left and right child
	else {
		TreeNode *prevprev = p, *prev = p->m_left, *curr = p->m_left->m_right;
		while (curr) { //move to child node
			prevprev = prev;
			prev = curr;
			curr = curr->m_right;
		}
		p->m_data = prev->m_data; //value change
		if (prevprev == p) //parent go the child node
			prevprev->m_left = prev->m_left; //delete
		else //not move
			prevprev->m_right = prev->m_left;
		delete prev; //return
	}
}
void BinarySearchTree::Inorder(TreeNode * ord) //Inorder
{
	if (ord != NULL) { //have child
		Inorder(ord->m_left); //go left child
		cout << ord->m_data << endl; //print out child's data
		Inorder(ord->m_right); //go to right child
	}
	else if(ord == NULL) //don't have child
		return;
}

void BinarySearchTree::Release(TreeNode * rel)
{
	if (rel != NULL) {
		rel = rel->m_left;
		rel = rel->m_right;
		delete rel;
	}
	else
		return;
	m_root == NULL;
}

