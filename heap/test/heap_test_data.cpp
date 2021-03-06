#include <vector>
#include "heap_test_data.h"

std::vector<int> HeapTestData::GetIntVec1()
{
	int myInts[] = {1, 10, 5, 3, 9, 6, 4, 2};
	unsigned int count = 8;
	std::vector<int> vec;
	for (unsigned int i = 0; i < count; i++)
	{
		vec.push_back(myInts[i]);
	}
	return vec;
}

std::vector<int> HeapTestData::GetIntVec2()
{
	int myInts[] = {16, 39, 12, 94, 23, 53, 88, 92, 43, 15, 63, 26};
	unsigned int count = 12;
	std::vector<int> vec;
	for (unsigned int i = 0; i < count; i++)
	{
		vec.push_back(myInts[i]);
	}
	return vec;
}