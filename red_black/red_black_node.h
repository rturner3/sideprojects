#ifndef RED_BLACK_NODE_H
#define RED_BLACK_NODE_H

#define BLACK true
#define RED false

template<typename S, typename T>
struct red_black_node
{
	S key;
	T value;
	bool color;
	red_black_node<S, T> *left_child;
	red_black_node<S, T> *right_child;
	red_black_node<S, T> *parent;
};

#endif // RED_BLACK_NODE_H