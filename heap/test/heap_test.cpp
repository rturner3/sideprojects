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
  heap<int> aHeap(ints);
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
  heap<int> aHeap(ints);
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
  heap<int> aHeap(ints);
  EXPECT_EQ(10, aHeap.peek());
}

TEST(HeapTest, NonMaxElementInsertedIntoMaxHeap)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints);
  for (int i = 0; i < 10; i++)
  {
    aHeap.insert(i);
    EXPECT_EQ(10, aHeap.peek());
  }
}

TEST(HeapTest, MaxElementInsertedIntoMaxHeap)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints);
  aHeap.insert(100);
  EXPECT_EQ(100, aHeap.peek());
}

TEST(HeapTest, CreateMinHeap)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MIN_HEAP);
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

TEST(HeapTest, PoppingOffMinHeapPopsMinElement)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MIN_HEAP);
  EXPECT_EQ(1, aHeap.pop());
  EXPECT_EQ(2, aHeap.peek());
}

TEST(HeapTest, PoppingOffMaxHeapPopsMaxElement)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MAX_HEAP);
  EXPECT_EQ(10, aHeap.pop());
  EXPECT_EQ(9, aHeap.peek());
}

TEST(HeapTest, ReplaceOnMaxHeapPopsMaxElement)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MAX_HEAP);
  aHeap.replace(0);
  EXPECT_EQ(9, aHeap.peek());
}

TEST(HeapTest, ReplaceOnMaxHeapAddsNewElement)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MAX_HEAP);
  aHeap.replace(11);
  EXPECT_EQ(11, aHeap.peek());
}

TEST(HeapTest, ReplaceOnMinHeapPopsMinElement)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MIN_HEAP);
  aHeap.replace(99);
  EXPECT_EQ(2, aHeap.peek());
}

TEST(HeapTest, ReplaceOnMinHeapAddsNewElement)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MIN_HEAP);
  aHeap.replace(0);
  EXPECT_EQ(0, aHeap.peek());
}

TEST(HeapTest, GetHeapReturnsValues)
{
  std::vector<int> ints = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints, MIN_HEAP);
  std::vector<int> vals = aHeap.getValues();
  EXPECT_EQ(8, vals.size());
}

TEST(HeapTest, MergeMaxAndMaxHeapToMaxHeap)
{
  std::vector<int> ints1 = HeapTestData::GetIntVec1();
  heap<int> aHeap(ints1, MAX_HEAP);
  std::vector<int> ints2 = HeapTestData::GetIntVec2();
  heap<int> aSecondHeap(ints2, MAX_HEAP);
  heap<int> aThirdHeap(aHeap, aSecondHeap, MAX_HEAP);
  EXPECT_EQ(94, aThirdHeap.peek());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}