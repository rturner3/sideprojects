#ifndef AVL_NODE_H
#define AVL_NODE_H

template<typename S, typename T>
struct avl_node
{
	S key;
	T value;
	avl_node<S, T> *left_child;
	avl_node<S, T> *right_child;
};

#endif // AVL_NODE_H