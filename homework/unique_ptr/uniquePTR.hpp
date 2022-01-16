#pragma once
#include <utility>
template <typename T>
class unique_ptr 
{
  T* ptr_{nullptr};

public:
  unique_ptr() = default;
  explicit unique_ptr(T* ptr) : ptr_(ptr){}
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr(unique_ptr&& rhs) noexcept{
    ptr_ = std::exchange(rhs.ptr_, nullptr);
  }

  unique_ptr& operator=(const unique_ptr &) = delete;
  unique_ptr& operator=(unique_ptr && rhs) noexcept{
    if (this != &rhs) {
      delete ptr_;
      ptr_ = std::exchange(rhs.ptr_, nullptr);
    }

    return *this;
  }

  const T& operator*() const {
      return *ptr_;
  }

  T* operator->() const {
      return ptr_;
  }

  T* get() const {
      return ptr_;
  }

  T* release(){
      return std::exchange(ptr_, nullptr);
  }

  void reset(T* newPtr = nullptr){
      delete ptr_;
      ptr_ = newPtr;
  }
  
  ~unique_ptr(){
    delete ptr_;
  }
};