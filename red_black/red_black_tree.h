#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

#include "red_black_node.h"

template<typename S, typename T>
class red_black_tree {
public:
	red_black_tree();
	~red_black_tree();
	bool search(const S &key, T &value);
	void insert(const S &key, const T &value);
	void remove(const S &key);
	void printTree();

private:
	red_black_node<S, T> *root;
	red_black_node<S, T> *searchHelper(const red_black_node<S, T> *currNode, const S &key);
	void printHelper(const red_black_node<S, T> *currNode);
	void insertHelper(red_black_node<S, T> *currNode, red_black_node<S, T> *parentNode, red_black_node<S, T> *newNode);
	red_black_node<S, T> *grandparent(red_black_node<S, T> *currNode);
	red_black_node<S, T> *uncle(red_black_node<S, T> *currNode);
	void rotate_left(red_black_node<S, T> *currNode);
	void rotate_right(red_black_node<S, T> * currNode);
	void insert_case1(red_black_node<S, T> *currNode);
	void insert_case2(red_black_node<S, T> *currNode);
	void insert_case3(red_black_node<S, T> *currNode);
	void insert_case4(red_black_node<S, T> *currNode);
	void insert_case5(red_black_node<S, T> *currNode);
	red_black_node<S, T> *sibling(red_black_node<S, T> *currNode);
	bool is_leaf(red_black_node<S, T> *currNode);
	void replace_node(red_black_node<S, T> *currNode, red_black_node<S, T> *child);
	void delete_one_child(red_black_node<S, T> *currNode);
	void delete_case1(red_black_node<S, T> *currNode);
	void delete_case2(red_black_node<S, T> *currNode);
	void delete_case3(red_black_node<S, T> *currNode);
	void delete_case4(red_black_node<S, T> *currNode);
	void delete_case5(red_black_node<S, T> *currNode);
	void delete_case6(red_black_node<S, T> *currNode);
};

template<typename S, typename T>
red_black_tree<S, T>::red_black_tree()
{
	root = 0;
}

template<typename S, typename T>
red_black_tree<S, T>::~red_black_tree()
{
	while (root)
	{
		remove(root->key);
	}
}

template<typename S, typename T>
bool red_black_tree<S, T>::search(const S &key, T &value)
{
	red_black_node<S, T> *reqNode = searchHelper(root, key);

	if (reqNode)
	{
		value = reqNode->value;
		return true;
	}

	return false;
}

template<typename S, typename T>
red_black_node<S, T> *red_black_tree<S, T>::searchHelper(const red_black_node<S, T> *currNode, const S &key)
{
	if (!currNode || key == currNode->key)
	{
		return currNode;
	}
	else if (key < currNode->key)
	{
		searchHelper(currNode->left_child, key);
	}
	else
	{
		searchHelper(currNode->right_child, key);
	}
}

template<typename S, typename T>
void red_black_tree<S, T>::insert(const S &key, const T &value)
{
	// TODO: Implement this method
	red_black_node<S, T> *newNode = new red_black_node<S, T>;
	newNode->key = key;
	newNode->value = value;
	newNode->left_child = 0;
	newNode->right_child = 0;
	newNode->parent = 0;
	newNode->color = RED;
	insertHelper(root, 0, newNode);
}

template<typename S, typename T>
void red_black_tree<S, T>::insertHelper(red_black_node<S, T> *currNode, red_black_node<S, T> *parentNode, red_black_node<S, T> *newNode)
{
	// TODO: Implement this method
	if (!currNode)
	{
		if (!root)
		{
			root = newNode;
		}
		else
		{
			newNode->parent = parentNode;
			if (newNode->parent->key > newNode->key)
			{
				newNode->parent->left_child = newNode;
			}
			else
			{
				newNode->parent->right_child = newNode;
			}
		}
		insert_case1(newNode);
	}
	else if (currNode->key > newNode->key)
	{
		newNode->parent = currNode;
		insertHelper(currNode->left_child, currNode, newNode);
	}
	else if (currNode->key < newNode->key)
	{
		newNode->parent = currNode;
		insertHelper(currNode->right_child, currNode, newNode);
	}
}

template<typename S, typename T>
void red_black_tree<S, T>::remove(const S &key)
{
	T value;
	red_black_tree<S, T> *delNode = searchHelper(key, value);
	if (delNode)
	{
		delete_one_child(delNode);
	}
}

template<typename S, typename T>
void red_black_tree<S, T>::printTree()
{
	printHelper(root);
}

template<typename S, typename T>
void red_black_tree<S, T>::printHelper(const red_black_node<S, T> *currNode)
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

template<typename S, typename T>
red_black_node<S, T> *red_black_tree<S, T>::grandparent(red_black_node<S, T> *currNode)
{
	if (currNode && currNode->parent)
	{
		return currNode->parent->parent;
	}
	else
	{
		return 0;
	}
}

template<typename S, typename T>
red_black_node<S, T> *red_black_tree<S, T>::uncle(red_black_node<S, T> *currNode)
{
	red_black_node<S, T> *g = grandparent(currNode);
	if (!g)
	{
		return 0;
	}
	else if (currNode->parent == g->left_child)
	{
		return g->right_child;
	}
	else
	{
		return g->left_child;
	}
}

template<typename S, typename T>
void red_black_tree<S, T>::rotate_left(red_black_node<S, T> *currNode)
{
	// No rotation to perform
	if (!currNode || !currNode->right_child)
	{
		return;
	}


	red_black_node<S, T> *parent = currNode;
	red_black_node<S, T> *grandparent = parent->parent;
	red_black_node<S, T> *childN = parent->right_child;
	red_black_node<S, T> *oldLeftChildN = childN->left_child;

	if (grandparent->left_child == parent)
	{
		grandparent->left_child = childN;
	}
	else
	{
		grandparent->right_child = childN;
	}

	childN->left_child = parent;
	parent->right_child = oldLeftChildN;
}

template<typename S, typename T>
void red_black_tree<S, T>::rotate_right(red_black_node<S, T> *currNode)
{
	// No rotation to perform
	if (!currNode || !currNode->left_child)
	{
		return;
	}


	red_black_node<S, T> *parent = currNode;
	red_black_node<S, T> *grandparent = parent->parent;
	red_black_node<S, T> *childN = parent->left_child;
	red_black_node<S, T> *oldLeftChildN = childN->right_child;
	
	if (grandparent->left_child == parent)
	{
		grandparent->left_child = childN;
	}
	else
	{
		grandparent->right_child = childN;
	}

	childN->right_child = parent;
	parent->left_child = oldLeftChildN;
}

template<typename S, typename T>
void red_black_tree<S, T>::insert_case1(red_black_node<S, T> *currNode)
{
	// Newly inserted node is the root, and the root must always be black
	if (!currNode->parent)
	{
		currNode->color = BLACK;
	}
	else
	{
		insert_case2(currNode);
	}
}

template<typename S, typename T>
void red_black_tree<S, T>::insert_case2(red_black_node<S, T> *currNode)
{
	// Tree is still valid if newly inserted node's parent is black
	// because the new node is red, thus every path from the root to a leaf
	// still contains the same number of black nodes
	if (currNode->parent->color == BLACK)
	{
		return;
	}
	else
	{
		insert_case3(currNode);
	}
}

template<typename S, typename T>
void red_black_tree<S, T>::insert_case3(red_black_node<S, T> *currNode)
{
	// If the newly inserted node's parent and uncle are both red,
	// we must repaint them both to black and repaint the grandparent
	// to red. This may invalidate the tree since the grandparent might
	// be the root, and the root must be black. And the grandparent might
	// also have a red parent, in which case we break the property that
	// both children of a red node must be black. Thus we must go through
	// one tail-recursive call to insert_case1(g) , which if unrolled, is
	// guaranteed to be in a loop structure and have a constant number of 
	// rotations.

	/*   Example diagram:

                  G
               (black)
             /         \
            /           \
           /             \
       P                  U
     (red)              (red)
    /    \
    |    |
	N   ...
  (red)

                  |
                  V

                  G
                (red)
             /         \
            /           \
           /             \
       P                  U
    (black)             (black)
    /    \
    |    |
	N   ...
  (red)

  */

  red_black_node<S, T> *u = uncle(currNode);
  red_black_node<S, T> *g;

  if (u && u->color == RED)
  {
  	currNode->parent->color = BLACK;
  	u->color = BLACK;
  	g = grandparent(currNode);
  	g->color = RED;
  	insert_case1(g);
  }
  else
  {
  	insert_case4(currNode);
  }

}

template<typename S, typename T>
void red_black_tree<S, T>::insert_case4(red_black_node<S, T> *currNode)
{
	/*   Example diagram:

                  G
               (black)
             /         \
            /           \
           /             \
       P                  U
     (red)             (black)
    /    \
    |    |
    1    N
       (red)
      /     \
     2       3

                  |
                  V

                  G
               (black)
             /         \
            /           \
           /             \
       N                  U
     (red)             (black)
    /    \
    |    |
    P    3
  (red)
  /   \
 1     2

This is the rotate left case. If P is the right child of G, then we do a right rotate instead.

*/

	red_black_node<S, T> *g = grandparent(currNode);

	if ((currNode == currNode->parent->right_child) && (currNode->parent == g->left_child))
	{
		rotate_left(currNode->parent);

		currNode = currNode->left_child;
	}
	else if ((currNode == currNode->parent->left_child) && (currNode->parent == g->right_child))
	{
		rotate_right(currNode->parent);

		currNode = currNode->right_child;
	}

	insert_case5(currNode);
}

template<typename S, typename T>
void red_black_tree<S, T>::insert_case5(red_black_node<S, T> *currNode)
{
		/*   Example diagram:

                  G
               (black)
             /         \
            /           \
           /             \
       P                  U
     (red)             (black)
    /    \
    |    |
    N    3
  (red)
 /     \
1       2

                  |
                  V

                  P
               (black)
             /         \
            /           \
           /             \
       N                  G
     (red)              (red)
    /    \             /     \
    |    |            3       U
    1    2                 (black)


This is the rotate left case. If P is the right child of G, then we do a right rotate instead.

*/

	red_black_node<S, T> *g = grandparent(currNode);

	currNode->parent->color = BLACK;
	g->color = RED;
	if (currNode == currNode->parent->left_child)
	{
		rotate_right(g);
	}
	else
	{
		rotate_left(g);
	}
}

template<typename S, typename T>
red_black_node<S, T> *red_black_tree<S, T>::sibling(red_black_node<S, T> *currNode)
{
	if (currNode == currNode->parent->left_child)
	{
		return currNode->parent->right_child;
	}
	else
	{
		return currNode->parent->left_child;
	}
}

template<typename S, typename T>
bool red_black_tree<S, T>::is_leaf(red_black_node<S, T> *currNode)
{
	if (!currNode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename S, typename T>
void red_black_tree<S, T>::replace_node(red_black_node<S, T> *currNode, red_black_node<S, T> *child)
{
	if (currNode && child)
	{
		currNode->key = child->key;
		currNode->value = child->value;
	}
}

// TODO: Check that this function works
template<typename S, typename T>
void red_black_tree<S, T>::delete_one_child(red_black_node<S, T> *currNode)
{
	// Parent is NULL leaf
	if (!currNode)
	{
		delete_case1(currNode);
	}
	else
	{
		red_black_node<S, T> *child = is_leaf(currNode->right_child) ? currNode->left_child : currNode->right_child;

		replace_node(currNode, child);
		if (currNode->color == BLACK)
		{
			if (child->color == RED)
			{
				child->color = BLACK;
			}
			else
			{
				delete_case1(child);
			}
		}
	}

	delete currNode;
}

template<typename S, typename T>
void red_black_tree<S, T>::delete_case1(red_black_node<S, T> *currNode)
{
	// Make sure currNode != new root
	if (currNode->parent != NULL)
	{
		delete_case2(currNode);
	}
}

/*
N is the node we want to delete

Example diagram:

                  P
               (black)
             /         \
            /           \
           /             \
          N               S
       (black)          (red)
                       /     \
                      Sl      Sr
                    (black)  (black)

                  |
                  V

                  S
               (black)
             /         \
            /           \
           /             \
          P               Sr
        (red)           (black)
       /     \
      N      Sl
   (black)  (black)                    


*/
template<typename S, typename T>
void red_black_tree<S, T>::delete_case2(red_black_node<S, T> *currNode)
{
	red_black_node<S, T> *sib = sibling(currNode);

	if (sib->color == RED)
	{
		currNode->parent->color = RED;
		sib->color = BLACK;
		if (currNode == currNode->parent->left_child)
		{
			rotate_left(currNode->parent);
		}
		else
		{
			rotate_right(currNode->parent);
		}
	}
	delete_case3(currNode);
}

template<typename S, typename T>
void red_black_tree<S, T>::delete_case3(red_black_node<S, T> *currNode)
{
	
}

template<typename S, typename T>
void red_black_tree<S, T>::delete_case4(red_black_node<S, T> *currNode)
{
	
}

template<typename S, typename T>
void red_black_tree<S, T>::delete_case5(red_black_node<S, T> *currNode)
{
	
}

template<typename S, typename T>
void red_black_tree<S, T>::delete_case6(red_black_node<S, T> *currNode)
{
	
}

#endif // RED_BLACK_TREE_H