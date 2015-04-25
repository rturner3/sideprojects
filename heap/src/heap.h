#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>

enum HeapComp {MIN_HEAP, MAX_HEAP};

template <class T>
class heap {
  public:
    heap()
    {
      comp = MAX_HEAP;
    }
    heap(std::vector<T> vec)
    {
      initWithVector(vec, MAX_HEAP);
    }
    heap(std::vector<T> vec, int heapComp)
    {
      initWithVector(vec, heapComp);
    }
    heap(heap<T> heap1, heap<T> heap2)
    {
      initWithTwoHeaps(heap1, heap2, MAX_HEAP);
    }
    heap(heap<T> heap1, heap<T> heap2, int heapComp)
    {
      initWithTwoHeaps(heap1, heap2, heapComp);
    }
    unsigned long size() const;
    void insert(T obj);
    bool isEmpty() const;
    T peek() const;
    T pop();
    void replace(T obj);
    std::vector<T> getValues() const;

  private:
    std::vector<T> _v;
    int comp;
    void heapify();
    void siftDown(unsigned long start, unsigned long end);
    void initWithVector(std::vector<T> vec, int heapComp);
    void initWithTwoHeaps(heap<T> heap1, heap<T> heap2, int heapComp);
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
void heap<T>::initWithVector(std::vector<T> vec, int heapComp)
{
    comp = heapComp;
    _v.insert(_v.end(), vec.begin(), vec.end());
    heapify();
}

template <class T>
T heap<T>::pop()
{
  if (isEmpty())
  {
    throw std::logic_error("No elements to pop from heap");
  }
  T popped = peek();
  _v.erase(_v.begin());
  heapify();
  return popped;
}

template <class T>
void heap<T>::replace(T obj)
{
  _v.erase(_v.begin());
  insert(obj);
}

template <class T>
void heap<T>::initWithTwoHeaps(heap<T> heap1, heap<T> heap2, int heapComp)
{
  comp = heapComp;
  std::vector<T> heap1Values = heap1.getValues();
  std::vector<T> heap2Values = heap2.getValues();
  _v.insert(_v.end(), heap1Values.begin(), heap1Values.end());
  _v.insert(_v.end(), heap1Values.begin(), heap2Values.end());
  heapify();
}

template <class T>
std::vector<T> heap<T>::getValues() const
{
  std::vector<T> values(_v);
  return values;
}

