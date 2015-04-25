#include <vector>
#include "gtest/gtest.h"
#include "heap_test_data.h"
#include "heap.h"

TEST(HeapTest, HeapSizeOfZero)
{
  heap<int> aHeap;
  EXPECT_EQ(0, aHeap.size());
}

TEST(HeapTest, PositiveHeapSize)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, ints.size());
  EXPECT_EQ(ints.size(), aHeap.size());
}

TEST(HeapTest, IsEmptyWhenEmpty)
{
  heap<int> aHeap;
  EXPECT_TRUE(aHeap.isEmpty());
}

TEST(HeapTest, IsNotEmptyWhenNotEmpty)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, ints.size());
  EXPECT_FALSE(aHeap.isEmpty());
}

TEST(HeapTest, PeekOnMaxHeapGivesMaxElement)
{
  heap<int> aHeap;
  for (int i = 0; i < 10; i++)
  {
    aHeap.insert(i);
    EXPECT_EQ(i, aHeap.peek());
  }
}

TEST(HeapTest, DefaultHeapIsMaxHeap)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, ints.size());
  EXPECT_EQ(10, aHeap.peek());
}

TEST(HeapTest, NonMaxElementInsertedIntoMaxHeap)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, ints.size());
  for (int i = 0; i < 10; i++)
  {
    aHeap.insert(i);
    EXPECT_EQ(10, aHeap.peek());
  }
}

TEST(HeapTest, MaxElementInsertedIntoMaxHeap)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, ints.size());
  aHeap.insert(100);
  EXPECT_EQ(100, aHeap.peek());
}

TEST(HeapTest, CreateMinHeap)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, ints.size(), MIN_HEAP);
  EXPECT_EQ(1, aHeap.peek());
}

TEST(HeapTest, CreateHeapWithNoInitialElementsGivesMaxHeap)
{
  heap<int> aHeap;
  for (int i = 0; i < 15; i += 3)
  {
    aHeap.insert(i);
  }
  EXPECT_EQ(12, aHeap.peek());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}