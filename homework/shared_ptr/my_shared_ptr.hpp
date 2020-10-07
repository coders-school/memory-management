#pragma once

#include "Counter.hpp"

template <typename T> class my_shared_ptr {

public:
  explicit my_shared_ptr(T *ptr) : ptr_(ptr) 
    { 
      counter_ptr->count_++;
  };

  my_shared_ptr() : counter_ptr(new Counter()) { ptr_ = nullptr; };

  my_shared_ptr(const my_shared_ptr<T> &other_shared_ptr) {
    ptr_ = other_shared_ptr.get();
    counter_ptr = other_shared_ptr.getCounter();

    counter_ptr->count_++;
  };

  my_shared_ptr(my_shared_ptr<T> &&ptr_m) { ptr_ = ptr_m.release(); }

  void operator=(const my_shared_ptr<T> &other_shared_ptr) {
    this->ptr_ = other_shared_ptr.get();
    counter_ptr = other_shared_ptr.getCounter();
    counter_ptr->count_++;
  };

  T *get() { return ptr_; }
  Counter *getCounter() { return counter_ptr; }

  T *release() {
    T *tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  };

  void reset(T *new_ptr) {
    delete ptr_;
    ptr_ = new_ptr;
  };

  ~my_shared_ptr() { delete ptr_; }

  T operator*() { return *ptr_; };
  T *operator->() { return this->ptr_; };

private:
  T *ptr_ = nullptr;
  Counter *counter_ptr = nullptr;
};
