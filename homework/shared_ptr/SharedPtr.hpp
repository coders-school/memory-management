#pragma once
#include <atomic>
#include <iostream>
#include <vector>

template <typename T> class ControlBlock {

public:
  std::atomic<size_t> sharedRefsCounter_{1};
  std::atomic<size_t> weakRefsCounter_{0};
  void deleter(T *rawPtr) { delete rawPtr; };
};

template <typename T> class SharedPtr {

public:
  SharedPtr(T *rawPtr = nullptr);
  SharedPtr(SharedPtr<T> &&other) noexcept;      // move constructor
  SharedPtr(const SharedPtr<T> &other) noexcept; // copy constructor
  T *get() const;
  T &operator*() const noexcept;
  T *operator->() const noexcept;
  T &operator=(const SharedPtr<T> &other) noexcept;
  void reset(T *NewRawPtr = nullptr);
  int use_count() const;

private:
  T *rawPtr_;
  ControlBlock<T> *ControlBlock_;
};

template <typename T>
SharedPtr<T>::SharedPtr(T *rawPtr)
    : rawPtr_(rawPtr), ControlBlock_(new ControlBlock<T>) {}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&other) noexcept // move constructor
    : rawPtr_(other.rawPtr_), ControlBlock_(other.ControlBlock_) {
  other.rawPtr_ = nullptr;
  other.ControlBlock_ = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) noexcept // copy constructor
    : rawPtr_(other.rawPtr_), ControlBlock_(other.ControlBlock_) {
  ControlBlock_->sharedRefsCounter_.exchange(
      ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) + 1,
      std::memory_order_relaxed);
}

template <typename T>
T &SharedPtr<T>::operator=(const SharedPtr<T> &other) noexcept {
  if (other != this) {
    rawPtr_ = other.rawPtr_;
    ControlBlock_ = other.ControlBlock_;
    ControlBlock_->sharedRefsCounter_.exchange(
        ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) + 1,
        std::memory_order_relaxed);
  } else
    return this;
}

template <typename T> T *SharedPtr<T>::get() const { return rawPtr_; }

template <typename T> T &SharedPtr<T>::operator*() const noexcept {
  return *rawPtr_;
}

template <typename T> T *SharedPtr<T>::operator->() const noexcept {
  return rawPtr_;
}

template <typename T> void SharedPtr<T>::reset(T *NewRawPtr) {
  if (ControlBlock_->sharedRefsCounter_ >= 2) {
    ControlBlock_->sharedRefsCounter_.exchange(
        ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) - 1,
        std::memory_order_relaxed);
      ControlBlock_ = new ControlBlock<T>{};
      rawPtr_ = NewRawPtr;
      return;
  }
  else if(ControlBlock_->sharedRefsCounter_ == 1){
    ControlBlock_->deleter(rawPtr_);
    delete ControlBlock_; //if weak_ptr will be created, this must be removed !!
    rawPtr_ = NewRawPtr;
    ControlBlock_ = new ControlBlock<T>{};
    return;
  }
}

template <typename T> int SharedPtr<T>::use_count() const {
  return ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed);
}

/*

template <typename T> class unique_ptr {

public:
  unique_ptr(T *rawPtr = nullptr);            // creation constructor
  unique_ptr(unique_ptr<T> &&other) noexcept; // move constructor
  unique_ptr(const unique_ptr<T> &) = delete; // copy constructor
  unique_ptr<T> &
  operator=(const unique_ptr<T> &) = delete; // copy assigment operator
  unique_ptr<T> &operator=(unique_ptr<T> &&otherUniquePtr) noexcept;
  ~unique_ptr();
  T *get() const;
  T *release();
  void reset(T *NewRawPtr = nullptr);
  T &operator*();

private:
  T *rawPtr_{nullptr};
};

template <typename T>
unique_ptr<T>::unique_ptr(T *rawPtr)
    : rawPtr_(rawPtr) {} // creation constructor

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T> &&other) noexcept // move constructor
    : rawPtr_(other.rawPtr_) {
  other.rawPtr_ = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() // destructor
{
  delete rawPtr_;
}

template <typename T>
unique_ptr<T> &unique_ptr<T>::
operator=(unique_ptr<T> &&otherUniquePtr) noexcept {
  if (this != &otherUniquePtr) {
    delete rawPtr_;
    rawPtr_ = otherUniquePtr.rawPtr_;
    otherUniquePtr = nullptr;
  }
  return *this;
}

template <typename T> T *unique_ptr<T>::get() const { return rawPtr_; }

template <typename T> T *unique_ptr<T>::release() {
  T *result = rawPtr_;
  rawPtr_ = nullptr;
  return result;
}

template <typename T> void unique_ptr<T>::reset(T *NewRawPtr) {
  delete rawPtr_;
  rawPtr_ = NewRawPtr;
}
template <typename T> T &unique_ptr<T>::operator*() {
  if (rawPtr_ != nullptr) {
    return *rawPtr_;
  } else
    throw std::runtime_error("dereferecing nullptr");
} */
