#include "red_black_tree.h"

int main()
{
	red_black_tree<int, int> tree;

	tree.insert(5, 5);
	tree.insert(1, 1);
	tree.insert(7, 7);
	tree.insert(4, 4);
	tree.insert(9, 9);
	tree.insert(3, 3);

	tree.printTree();

	tree.remove(1);
	tree.printTree();

	tree.remove(7);
	tree.printTree();

	tree.remove(4);
	tree.printTree();

	tree.remove(5);
	tree.printTree();

	tree.remove(3);
	tree.printTree();

	tree.remove(9);
	tree.printTree();

	return 0;
}