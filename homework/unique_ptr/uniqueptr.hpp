#pragma once
#include <stdexcept>
#include <stdio.h>
#include <iostream>

template <class T> class unique_ptr {

public:
  unique_ptr(T *rawPtr);                      // creation constructor
  unique_ptr(unique_ptr<T> &&other) noexcept; // move constructor
  unique_ptr(const unique_ptr &) = delete;    // copy constructor
  unique_ptr &operator=(const unique_ptr &) = delete;  // copy assigment operator
  ~unique_ptr();

  T *get() const;
  T release();
  void reset();
  T &operator*();

private:
  T *rawPtr_;
};

template <class T> unique_ptr<T>::unique_ptr(T *rawPtr) : rawPtr_(rawPtr) {
  puts("Yes, we created uniqueptr! :)");
}; // creation constructor

template <class T>
unique_ptr<T>::unique_ptr(unique_ptr<T> &&other) noexcept // move constructor
    : rawPtr_(other.rawPtr_)

{
  other.rawPtr_ = nullptr;
}

template <class T>
unique_ptr<T>::~unique_ptr() // destructor
{
  std::cout << "Destructor called where raw_ptr adress is: " << this->rawPtr_ << '\n';
  delete rawPtr_;
}

template <class T>
T *unique_ptr<T>::get() const { /* if(rawPtr_ == nullptr)
                                 throw std::range_error("Trying to access empty
                                 unique_ptr using .get()"); else  */
  return rawPtr_;
}

template <class T> T unique_ptr<T>::release() {
  auto result = rawPtr_;
  rawPtr_ = nullptr;
  return result;
}

template <class T> void unique_ptr<T>::reset() { rawPtr_ = nullptr; }
template <class T> T &unique_ptr<T>::operator*() { return *rawPtr_; }