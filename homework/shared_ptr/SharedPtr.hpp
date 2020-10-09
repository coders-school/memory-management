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
  ~SharedPtr();
  T *getPtr() const;
  ControlBlock<T> *getControlBlock() const;
  T &operator*() const noexcept;
  T *operator->() const noexcept;
  SharedPtr<T> &operator=(const SharedPtr<T> &other) noexcept;
  SharedPtr<T> &operator=(SharedPtr<T> &&other) noexcept;
  operator bool() const noexcept;
  void reset(T *NewRawPtr = nullptr);
  int use_count() const;

private:
  T *rawPtr_;
  ControlBlock<T> *ControlBlock_;
};

template <typename T> SharedPtr<T>::SharedPtr(T *rawPtr) : rawPtr_(rawPtr) {
  ControlBlock_ = new ControlBlock<T>;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&other) noexcept // move constructor
    : rawPtr_(other.rawPtr_), ControlBlock_(other.ControlBlock_) {
  other.rawPtr_ = nullptr;
  other.ControlBlock_ = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) noexcept // copy constructor
    : rawPtr_(other.rawPtr_), ControlBlock_(other.ControlBlock_) {
  ControlBlock_->sharedRefsCounter_++;
}

template <typename T> SharedPtr<T>::~SharedPtr() {
  if (ControlBlock_ != nullptr) {
    if (ControlBlock_->sharedRefsCounter_ >= 2) {
      ControlBlock_->sharedRefsCounter_--;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ >= 1) {
      ControlBlock_->deleter(rawPtr_);
      delete ControlBlock_; // Should be managed by weak_Ptr
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ == 0) {
      ControlBlock_->deleter(rawPtr_);
      delete ControlBlock_;
    }
  }
}

template <typename T> T *SharedPtr<T>::getPtr() const {
  if (rawPtr_) {
    return rawPtr_;
  } else
    return nullptr;
}

template <typename T> ControlBlock<T> *SharedPtr<T>::getControlBlock() const {
  return ControlBlock_;
}


template <typename T> T &SharedPtr<T>::operator*() const noexcept {
  return *rawPtr_;
}

template <typename T> T *SharedPtr<T>::operator->() const noexcept {
  return rawPtr_;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other) noexcept {
  if (other.rawPtr_ != rawPtr_) {
    if (ControlBlock_->sharedRefsCounter_ >= 2) {
      ControlBlock_->sharedRefsCounter_--;
      ControlBlock_ = other.ControlBlock_;
      ControlBlock_->sharedRefsCounter_++;
      rawPtr_ = other.rawPtr_;
      return *this;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ >= 1) {
      ControlBlock_->deleter(rawPtr_);
      rawPtr_ = other.rawPtr_;
      ControlBlock_ = other.ControlBlock_;
      ControlBlock_->sharedRefsCounter_++;
      return *this;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ == 0) {
      ControlBlock_->deleter(rawPtr_);
      delete ControlBlock_;
      rawPtr_ = other.rawPtr_;
      ControlBlock_ = other.ControlBlock_;
      ControlBlock_->sharedRefsCounter_++;
      return *this;
    } else
      return *this;
  } else
    return *this;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> &&other) noexcept {
  if (other.rawPtr_ != rawPtr_) {
    if (ControlBlock_->sharedRefsCounter_ >= 2) {
      ControlBlock_->sharedRefsCounter_--;
      ControlBlock_ = other.ControlBlock_;
      rawPtr_ = other.rawPtr_;
      other.ControlBlock_ = nullptr;
      other.rawPtr_ = nullptr;
      return *this;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ >= 1) {
      ControlBlock_->deleter(rawPtr_);
      rawPtr_ = other.rawPtr_;
      ControlBlock_ = other.ControlBlock_;
      other.ControlBlock_ = nullptr;
      other.rawPtr_ = nullptr;
      return *this;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ == 0) {
      ControlBlock_->deleter(rawPtr_);
      delete ControlBlock_;
      rawPtr_ = other.rawPtr_;
      ControlBlock_ = other.ControlBlock_;
      other.ControlBlock_ = nullptr;
      other.rawPtr_ = nullptr;
      return *this;
    } else
      return *this;
  } else
    return *this;
}

template <typename T> SharedPtr<T>::operator bool() const noexcept {
  return (this->getPtr() != nullptr);
}

template <typename T> void SharedPtr<T>::reset(T *NewRawPtr) {
  if (NewRawPtr != rawPtr_) {
    if (ControlBlock_->sharedRefsCounter_ >= 2) {
      ControlBlock_->sharedRefsCounter_--;
      ControlBlock_ = new ControlBlock<T>{};
      rawPtr_ = NewRawPtr;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ >= 1) {
      ControlBlock_->deleter(rawPtr_);
      delete ControlBlock_; // Should be managed by weak_Ptr
      rawPtr_ = NewRawPtr;
      ControlBlock_ = new ControlBlock<T>{};
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ == 0) {
      ControlBlock_->deleter(rawPtr_);
      delete ControlBlock_;
      rawPtr_ = NewRawPtr;
      ControlBlock_ = new ControlBlock<T>{};
    }
  }
}

template <typename T> int SharedPtr<T>::use_count() const {
  return ControlBlock_->sharedRefsCounter_;
}
