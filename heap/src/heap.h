#include <vector>
#include <cmath>

template <class T>
class heap {
  public:
    heap() {}
    heap(T *arr, unsigned long count)
    {
      for (int i = 0; i < count; i++)
      {
        insert(arr[i]);
      }
    }
    unsigned long size() const;
    void insert(T obj);
    bool isEmpty() const;
    T peek() const;

  private:
    std::vector<T> _v;
    void heapify();
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
  unsigned long start = (unsigned long)floor((heapSize - 2) / 2);
}