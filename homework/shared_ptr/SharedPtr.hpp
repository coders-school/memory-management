#pragma once
#include <atomic>
#include <iostream>
#include <vector>

template <typename T> class SharedPtr {

public:
  SharedPtr(T *rawPtr = nullptr);
  SharedPtr(SharedPtr<T> &&other) noexcept;      // move constructor
  SharedPtr(const SharedPtr<T> &other) noexcept; // copy constructor
  T *get() const;
  T &operator*() const noexcept;
  T *operator->() const noexcept;
  operator = (const SharedPtr<T> & other);
  void reset(T *NewRawPtr = nullptr);

private:
  T *rawPtr_{};
public: 
  std::vector<std::atomic<size_t> *> ControlBlock{
      new std::atomic<size_t>{},  // sharedRefsCounter,
      new std::atomic<size_t>{}}; // weakRefsCounter
};

template <typename T> SharedPtr<T>::SharedPtr(T *rawPtr) : rawPtr_(rawPtr) {
  ControlBlock.at(0)++;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&other) noexcept // move constructor
    : rawPtr_(other.rawPtr_) {
  other.rawPtr_ = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) noexcept // copy constructor
    : rawPtr_(other.rawPtr_) {
  ControlBlock.at(0)++;
}

template <typename T> T *SharedPtr<T>::get() const { return rawPtr_; }

template <typename T> T &SharedPtr<T>::operator*() const noexcept {
  return *rawPtr_;
}

template <typename T> T *SharedPtr<T>::operator->() const noexcept {
  return rawPtr_;
}

template <typename T> void SharedPtr<T>::reset(T *NewRawPtr) {
  delete rawPtr_;
  rawPtr_ = NewRawPtr;
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
