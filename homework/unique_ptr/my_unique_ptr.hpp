#pragma once

template <typename T> class my_unique_ptr {

public:
  explicit my_unique_ptr(T *ptr) : ptr_(ptr){};

  my_unique_ptr() : ptr_(nullptr) {}

  my_unique_ptr(my_unique_ptr<T> &&ptr_m) : ptr_{ptr_m.release()} {}

  T &operator=(my_unique_ptr<T> &&ptr_m) {
    this->ptr_ = ptr_.release();
    return *(this->ptr_);
  }

  my_unique_ptr(const my_unique_ptr<T> &) = delete;
  void operator=(const my_unique_ptr<T> &) = delete;

  T *get() const { return ptr_; }

  T *release() {
    T *tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  };

  void reset(T *new_ptr = nullptr) {
    delete ptr_;
    ptr_ = new_ptr;
  };

  ~my_unique_ptr() { delete ptr_; }

  T &operator*() { return *ptr_; };
  T *operator->() { return this->ptr_; };

private:
  T *ptr_ = nullptr;
};
