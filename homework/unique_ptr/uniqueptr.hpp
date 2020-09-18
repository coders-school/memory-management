#pragma once
#include <iostream>
#include <stdexcept>
#include <stdio.h>

template <typename T> class unique_ptr {

public:
  unique_ptr(T *rawPtr);                              // creation constructor
  unique_ptr(unique_ptr<T> &&other) noexcept;         // move constructor
  unique_ptr(const unique_ptr &) = delete;            // copy constructor
  unique_ptr &operator=(const unique_ptr &) = delete; // copy assigment operator
  ~unique_ptr();

  T *get() const;
  T release();
  void reset(T *rawPtr) noexcept;
  T &operator*();

private:
  T *rawPtr_;
};

template <typename T>
unique_ptr<T>::unique_ptr(T *rawPtr)
    : rawPtr_(rawPtr){}; // creation constructor

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T> &&other) noexcept // move constructor
    : rawPtr_(other.rawPtr_)

{
  other.rawPtr_ = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() // destructor
{
  delete rawPtr_;
}

template <typename T>
T *unique_ptr<T>::get() const { /* if(rawPtr_ == nullptr)
                                 throw std::range_error("Trying to access empty
                                 unique_ptr using .get()"); else  */
  return rawPtr_;
}

template <typename T> T unique_ptr<T>::release() {
  T* result = rawPtr_;
  rawPtr_ = nullptr;
  return result;
}

template <typename T> void unique_ptr<T>::reset(T *NewRawPtr) noexcept {
  delete rawPtr_;
  rawPtr_ = NewRawPtr;
}
template <typename T> T &unique_ptr<T>::operator*() {
  if (rawPtr_ != nullptr) {
    return *rawPtr_;
  } else
    throw std::runtime_error("dereferecing nullptr");
}
