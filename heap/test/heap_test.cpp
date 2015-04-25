#include "gtest/gtest.h"
#include "heap.h"

TEST(HeapTest, HeapSizeOfZero)
{
  heap<int> aHeap;
  EXPECT_EQ(0, aHeap.size());
}

TEST(HeapTest, PositiveHeapSize)
{
  int count = 8;
  int arr[8] = { 1, 10, 5, 3, 9, 6, 4, 2 };
  heap<int> aHeap(arr, count);
  EXPECT_EQ(count, aHeap.size());
}

TEST(HeapTest, IsEmptyWhenEmpty)
{
  heap<int> aHeap;
  EXPECT_TRUE(aHeap.isEmpty());
}

TEST(HeapTest, IsNotEmptyWhenNotEmpty)
{
  int count = 8;
  int arr[8] = { 1, 10, 5, 3, 9, 6, 4, 2 };
  heap<int> aHeap(arr, count);
  EXPECT_FALSE(aHeap.isEmpty());
}

TEST(HeapTest, NonMaxElementInserted)
{
  int count = 8;
  int arr[8] = { 1, 10, 5, 3, 9, 6, 4, 2 };
  heap<int> aHeap(arr, count);
  aHeap.insert(7);
  EXPECT_EQ(10, aHeap.peek());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}