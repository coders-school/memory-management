#pragma once
#include <stdio.h>


template <class T>
class unique_ptr
{

public:
  unique_ptr(T rawPtr);
  unique_ptr(unique_ptr<T> &&other); //move constructor
  ~unique_ptr();

  T get();
  T release();
  void reset();
  T &operator*();

private:
  T *rawPtr_;
};

template <class T>
unique_ptr<T>::unique_ptr(T rawPtr) : rawPtr_(&rawPtr){puts("Yes, we created uniqueptr!");};

template <class T>
unique_ptr<T>::unique_ptr(unique_ptr<T> &&other)
    : rawPtr_(nullptr)
{
}

template <class T>
unique_ptr<T>::~unique_ptr()
{
  delete rawPtr_;
}

template <class T>
T unique_ptr<T>::get()
{
  return *rawPtr_;
}

template <class T>
T unique_ptr<T>::release()
{
}

template <class T>
void unique_ptr<T>::reset()
{
}
template <class T>
T &unique_ptr<T>::operator*()
{
}