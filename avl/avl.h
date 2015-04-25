#ifndef AVL_H
#define AVL_H

#include <algorithm>
#include <stack>
#include <iostream>

#include "avl_node.h"

template<typename S, typename T>
class avl {

public:
	avl();
	~avl();
	bool search(S key, T &value);
	void insert(S key, T value);
	void remove(S key);
	void printTree();

private:
	avl_node<S, T> *root;
	avl_node<S, T> *searchHelper(S key, avl_node<S, T> *currNode);
	int balanceFactor(avl_node<S, T> *currNode);
	int height(avl_node<S, T> *currNode);
	void insertHelper(avl_node<S, T> *currNode, avl_node<S, T> *inNode, std::stack<avl_node<S, T> *> &insertPath);
	void balanceTree(std::stack<avl_node<S, T> *> &insertPath);
	avl_node<S, T>* rotateLeft(avl_node<S, T> *currNode);
	avl_node<S, T>* rotateRight(avl_node<S, T> *currNode);
	void removeHelper(avl_node<S, T> *currNode, S key, std::stack<avl_node<S, T> *> &ancestors);
	void printHelper(avl_node<S, T> *currNode);
};

template<typename S, typename T>
avl<S, T>::avl()
{
	root = nullptr;
}

template<typename S, typename T>
avl<S, T>::~avl()
{
	while (root)
	{
		remove(root->key);
	}
}

template<typename S, typename T>
bool avl<S, T>::search(S key, T &value)
{
	avl_node<S, T> *reqNode = searchHelper(key, root);
	if (reqNode)
	{
		value = reqNode->value;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename S, typename T>
void avl<S, T>::insert(S key, T value)
{
	avl_node<S, T> *new_node = new avl_node<S, T>;
	new_node->key = key;
	new_node->value = value;
	new_node->left_child = nullptr;
	new_node->right_child = nullptr;
	std::stack<avl_node<S, T> *> insertPath;
	insertHelper(root, new_node, insertPath);
	balanceTree(insertPath);
}

template<typename S, typename T>
void avl<S, T>::remove(S key)
{
	std::stack<avl_node<S, T> *> ancestors;
	removeHelper(root, key, ancestors);
	balanceTree(ancestors);
}

template<typename S, typename T>
avl_node<S, T> *avl<S, T>::searchHelper(S key, avl_node<S, T> *currNode)
{
	if (!currNode || currNode->key == key)
	{
		return currNode;
	}
	else if (key < currNode->key)
	{
		return searchHelper(key, currNode->left_child);
	}
	else // key > currNode->key
	{
		return searchHelper(key, currNode->right_child);
	}
}

template<typename S, typename T>
int avl<S, T>::balanceFactor(avl_node<S, T> *currNode)
{
	return height(currNode->left_child) - height(currNode->right_child);
}

template<typename S, typename T>
int avl<S, T>::height(avl_node<S, T> *currNode)
{
	if (!currNode)
	{
		return -1;
	}
	return 1 + std::max(height(currNode->left_child), height(currNode->right_child));
}

template<typename S, typename T>
void avl<S, T>::insertHelper(avl_node<S, T> *currNode, avl_node<S, T> *inNode, std::stack<avl_node<S, T> *> &insertPath)
{
	if (!currNode)
	{
		if (insertPath.empty())
		{
			root = inNode;
		}
		else
		{
			avl_node<S, T> *parentNode = insertPath.top();
			if (parentNode->key > inNode->key)
			{
				parentNode->left_child = inNode;
			}
			else
			{
				parentNode->right_child = inNode;
			}
		}
	}
	else if (currNode->key > inNode->key)
	{
		insertPath.push(currNode);
		insertHelper(currNode->left_child, inNode, insertPath);
	}
	else if (currNode->key < inNode->key)
	{
		insertPath.push(currNode);
		insertHelper(currNode->right_child, inNode, insertPath);
	}
}

template<typename S, typename T>
void avl<S, T>::balanceTree(std::stack<avl_node<S, T> *> &insertPath)
{
	while (!insertPath.empty())
	{
		avl_node<S, T> *currNode = insertPath.top();
		insertPath.pop();
		if (balanceFactor(currNode) == 2) // Left column is unbalanced
		{
			if (balanceFactor(currNode->left_child) == -1) // Left right case
			{
				currNode->left_child = rotateLeft(currNode->left_child); // Reduce to left left case
			}

			// Left left case
			if (currNode == root)
			{
				root = rotateRight(currNode);
			}
			else
			{
				currNode = rotateRight(currNode);
			}
		}
		else if (balanceFactor(currNode) == -2) // the right column
		{
			if(balanceFactor(currNode->right_child) == 1) // Right left case
			{
				currNode->right_child = rotateRight(currNode->right_child); // reduce to right right case
			}

			// right right case
			if (currNode == root)
			{
				root = rotateLeft(currNode);
			}
			else
			{
				currNode = rotateLeft(currNode);
			}
		}
	}
}

template<typename S, typename T>
avl_node<S, T> *avl<S, T>::rotateLeft(avl_node<S, T> *currNode)
{
	// There is no rotation to perform
	if (!currNode || !currNode->right_child)
	{
		return nullptr;
	}

	avl_node<S, T> *new_parent_old_left_child = currNode->right_child->left_child;
	avl_node<S, T> *new_parent = currNode->right_child;
	avl_node<S, T> *new_left_child = currNode;

	// Perform the left rotate
	currNode = new_parent;
	currNode->left_child = new_left_child;
	currNode->left_child->right_child = new_parent_old_left_child;

	return currNode;
}

template<typename S, typename T>
avl_node<S, T> *avl<S, T>::rotateRight(avl_node<S, T> *currNode)
{
	if (!currNode || !currNode->left_child)
	{
		return nullptr;
	}

	avl_node<S, T> *new_parent_old_right_child = currNode->left_child->right_child;
	avl_node<S, T> *new_parent = currNode->left_child;
	avl_node<S, T> *new_right_child = currNode;

	// Perform the right rotate
	currNode = new_parent;
	currNode->right_child = new_right_child;
	currNode->right_child->left_child = new_parent_old_right_child;

	return currNode;
}

template<typename S, typename T>
void avl<S, T>::removeHelper(avl_node<S, T> *currNode, S key, std::stack<avl_node<S, T> *> &ancestors)
{
	if (!currNode)
	{
		return;
	}
	else if (key < currNode->key)
	{
		ancestors.push(currNode);
		removeHelper(currNode->left_child, key, ancestors);
	}
	else if (key > currNode->key)
	{
		ancestors.push(currNode);
		removeHelper(currNode->right_child, key, ancestors);
	}
	else // key == currNode->key
	{
		// nodeX == node with the value we need to delete
		avl_node<S, T> *nodeX = currNode;
		avl_node<S, T> *nodeZ = nodeX;
		avl_node<S, T> *nodeZParent = !ancestors.empty() ? ancestors.top() : nullptr;

		if (currNode->left_child && currNode->right_child)
		{
			avl_node<S, T> *nodeY = currNode;
			if (balanceFactor(nodeY) > 0)
			{
				nodeZParent = nodeY;
				nodeY = nodeY->left_child;
				while(1)
				{
					if (!nodeY->right_child)
					{
						break;
					}

					nodeZParent = nodeY;
					nodeY = nodeY->right_child;
				}
				// nodeY == largest member of node X's left subtree
			}
			else
			{
				nodeZParent = nodeY;
				nodeY = nodeY->right_child;
				while(1)
				{
					if (!nodeY->left_child)
					{
						break;
					}

					nodeZParent = nodeY;
					nodeY = nodeY->left_child;
				}
				// nodeY == smallest member of node X's right subtree
			}

			nodeX->key = nodeY->key;
			nodeX->value = nodeY->value;

			// nodeZ == old node Y
			nodeZ = nodeY;
		}

		// node Z is the node we're going to delete
		if (nodeZParent)
		{
			if (nodeZ == nodeZParent->left_child)
			{
				nodeZParent->left_child = nodeZ->right_child;
			}
			else
			{
				nodeZParent->right_child = nodeZ->left_child;
			}
		}
		else
		{
			if (root->left_child)
			{
				root = root->left_child;
			}
			else if (root->right_child)
			{
				root = root->right_child;
			}
			else
			{
				root = nullptr;
			}
		}

		delete nodeZ;
	}
}

template<typename S, typename T>
void avl<S, T>::printTree()
{
	std::cout << "root = " << root << std::endl;
	printHelper(root);
}

template<typename S, typename T>
void avl<S, T>::printHelper(avl_node<S, T> *currNode)
{
	if (!currNode)
	{
		return;
	}

	if (currNode->left_child)
	{
		printHelper(currNode->left_child);
	}

	std::cout << currNode << " " << currNode->key << " " << currNode->value << " ";
	std::cout << currNode->left_child << " " << currNode->right_child << std::endl;

	if (currNode->right_child)
	{
		printHelper(currNode->right_child);
	}
}

#endif // AVL_H