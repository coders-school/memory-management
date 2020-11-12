#pragma once
#include <atomic>
#include <iostream>
#include <vector>

template <typename T> class ControlBlock {
public:
  std::atomic<size_t> sharedRefsCounter_{1};
  std::atomic<size_t> weakRefsCounter_{0};
  void deleter(T *rawPtr) {
    if (rawPtr != nullptr) {
      delete rawPtr;
    }
  };
};

template <typename T> class SharedPtr {
public:
  SharedPtr(T *rawPtr = nullptr);
  SharedPtr(SharedPtr<T> &&other) noexcept; // move constructor
  SharedPtr(const SharedPtr<T> &other);     // copy constructor
  ~SharedPtr();
  T *get() const;
  T &operator*() const noexcept;
  T *operator->() const noexcept;
  SharedPtr<T> &operator=(const SharedPtr<T> &other);
  SharedPtr<T> &operator=(SharedPtr<T> &&other);
  operator bool() const noexcept;
  void reset(T *NewRawPtr = nullptr);
  size_t use_count() const;

private:
  T *rawPtr_;
  ControlBlock<T> *controlBlock_;
  void deleteAllIfCountersZero();
};

template <typename T>
SharedPtr<T>::SharedPtr(T *rawPtr)
    : rawPtr_(rawPtr), controlBlock_(new ControlBlock<T>{}) {}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&other) noexcept // move constructor
    : rawPtr_(other.rawPtr_), controlBlock_(other.controlBlock_) {
  other.rawPtr_ = nullptr;
  other.controlBlock_ = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) // copy constructor
    : rawPtr_(other.rawPtr_), controlBlock_(other.controlBlock_) {
  controlBlock_->sharedRefsCounter_++;
}

template <typename T> SharedPtr<T>::~SharedPtr() {
  if (controlBlock_ != nullptr) {
    controlBlock_->sharedRefsCounter_--;
    deleteAllIfCountersZero();
  }
}

template <typename T> void SharedPtr<T>::deleteAllIfCountersZero() {
  if (controlBlock_->sharedRefsCounter_ == 0) {
    controlBlock_->deleter(rawPtr_);
    rawPtr_ = nullptr;
  }
  if (controlBlock_->weakRefsCounter_ == 0 &&
      controlBlock_->sharedRefsCounter_ == 0) {
    delete controlBlock_;
    controlBlock_ = nullptr;
  }
}

template <typename T> T *SharedPtr<T>::get() const { return rawPtr_; }

template <typename T> T &SharedPtr<T>::operator*() const noexcept {
  return *rawPtr_;
}

template <typename T> T *SharedPtr<T>::operator->() const noexcept {
  return rawPtr_;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other) {
  if (this != &other) {
    controlBlock_->sharedRefsCounter_--;
      deleteAllIfCountersZero();
      rawPtr_ = other.rawPtr_;
      controlBlock_ = other.controlBlock_;
      controlBlock_->sharedRefsCounter_++;
    }
  return *this;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> &&other) {

  if (other.rawPtr_ != rawPtr_) {
    controlBlock_->sharedRefsCounter_--;
      deleteAllIfCountersZero();
      rawPtr_ = other.rawPtr_;
      controlBlock_ = other.controlBlock_;
      other.rawPtr_ = nullptr;
      other.controlBlock_ = nullptr;
  }
  return *this;
}

template <typename T> SharedPtr<T>::operator bool() const noexcept {
  return (rawPtr_ != nullptr);
}

template <typename T> void SharedPtr<T>::reset(T *NewRawPtr) {
    
    controlBlock_->sharedRefsCounter_--;
    deleteAllIfCountersZero();
    if(controlBlock_ == nullptr){
    controlBlock_ = new ControlBlock<T>;
    }
    rawPtr_ = NewRawPtr;
}

template <typename T> size_t SharedPtr<T>::use_count() const {
  return controlBlock_->sharedRefsCounter_;
}
