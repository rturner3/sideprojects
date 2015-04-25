#include <string>
#include <iostream>

#include "avl.h"

int main()
{
	avl<int, char> tree;
	tree.insert(1, 'd');
	tree.insert(5, 'a');
	tree.insert(3, 'c');
	tree.insert(4, 'z');
	tree.insert(10, 't');

	char value = 0;

	if (tree.search(1, value))
	{
		std::cout << "value = " << value << std::endl;
	}

	tree.printTree();
	std::cout << std::endl;

	tree.remove(5);

	tree.printTree();
	std::cout << std::endl;

	tree.remove(1);

	tree.printTree();
	std::cout << std::endl;

	tree.remove(3);

	tree.printTree();
	std::cout << std::endl;
	return 0;
}