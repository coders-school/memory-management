#pragma once

template <typename T>
class unique_ptr 
{
  T* ptr_{nullptr};

public:
  unique_ptr() = default;
  explicit unique_ptr(T* ptr) : ptr_(ptr){}
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr(unique_ptr&& rhs) {
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
  }

  unique_ptr& operator=(const unique_ptr &) = delete;
  unique_ptr& operator=(unique_ptr && rhs){
    if (this != &rhs) {
      delete ptr_;
      ptr_ = rhs.ptr_;
      rhs.ptr_ = nullptr;
    }

    return *this;
  }

  T& operator*() const{
      return *ptr_;
  }

  T* operator->() const{
      return ptr_;
  }

  T* get() const{
      return ptr_;
  }

  T* release(){
      T* newPtr = ptr_;
      ptr_ = nullptr;
      return newPtr;
  }

  void reset(T* newPtr = nullptr){
      delete ptr_;
      ptr_ = newPtr;
  }
  
  ~unique_ptr(){
    delete ptr_;
  }
};