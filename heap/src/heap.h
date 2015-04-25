#include <vector>
#include <cmath>
#include <algorithm>

enum HeapComp {MIN_HEAP, MAX_HEAP};

template <class T>
class heap {
  public:
    heap()
    {
      comp = MAX_HEAP;
    }
    heap(std::vector<T> vec, unsigned long count)
    {
      initWithVector(vec, count, MAX_HEAP);
    }
    heap(std::vector<T> vec, unsigned long count, int heapComp)
    {
      initWithVector(vec, count, heapComp);
    }
    unsigned long size() const;
    void insert(T obj);
    bool isEmpty() const;
    T peek() const;

  private:
    std::vector<T> _v;
    int comp;
    void heapify();
    void siftDown(unsigned long start, unsigned long end);
    void initWithVector(std::vector<T> vec, unsigned long count, int heapComp);
};


template <class T>
unsigned long heap<T>::size() const
{
  return _v.size();
}

template <class T>
void heap<T>::insert(T obj)
{
  _v.push_back(obj);
  heapify();
}

template <class T>
bool heap<T>::isEmpty() const
{
  return _v.empty();
}

template <class T>
T heap<T>::peek() const
{
  return _v.front();
}

template <class T>
void heap<T>::heapify()
{
  unsigned long heapSize = size();
  // start is index of last parent in heap
  int start = floor((heapSize - 2) / 2);
  while (start >= 0)
  {
    siftDown(start--, heapSize - 1);
  }
}

template <class T>
void heap<T>::siftDown(unsigned long start, unsigned long end)
{
  unsigned long root = start;
  // If root has a left child
  while (root * 2 + 1 <= end)
  {
    unsigned long child = root * 2 + 1;
    unsigned long swap = root;

    // If left child's key is greater than root's key
    if ((comp == MAX_HEAP && _v[swap] < _v[child])
        || (comp == MIN_HEAP && _v[swap] > _v[child]))
    {
      swap = child;
    }
    // If there is a right child and the right child's key is greater than swap's key
    if (child + 1 <= end
        && ((comp == MAX_HEAP && _v[swap] < _v[child + 1])
             || (comp == MIN_HEAP && _v[swap] > _v[child + 1])))
    {
      swap = child + 1;
    }
    if (swap == root)
    {
      return;
    }
    else
    {
      T temp = _v[root];
      _v[root] = _v[swap];
      _v[swap] = temp;
      root = swap;
    }
  }
}

template <class T>
void heap<T>::initWithVector(std::vector<T> vec, unsigned long count, int heapComp)
{
    comp = heapComp;
    for (unsigned long i = 0; i < count; i++)
    {
      insert(vec[i]);
    }
}