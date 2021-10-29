#pragma once

#include <cstddef>

#include "controlBlock.hpp"

class weak_ptr;

template <typename T>
class shared_ptr
{
public:
    shared_ptr(T *ptr){};

    // Copy constructor
    shared_ptr(const shared_ptr &ptr) noexcept;
    shared_ptr(shared_ptr &&ptr) noexcept;
    ~shared_ptr() noexcept;

    shared_ptr<T> &operator=(const shared_ptr &ptr) noexcept;
    shared_ptr<T> &operator=(shared_ptr &&ptr) noexcept;

    T &operator*() const noexcept { return *ptr_; };
    T *operator->() const noexcept { return ptr_; };
    const T *get() const noexcept;
    T *reset() noexcept;
    long use_count() const noexcept;
    explicit operator bool() const noexcept;

private:
    T *rawPtr_{nullptr};
    ControlBlock<T> *cb_{nullptr};
    git void deleteStoredPointers();
};

template <typename T>
shared_ptr<T>::shared_ptr(T *ptr) : rawPtr_(ptr), cb_(new ControlBlock<T>) {}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr &ptr) noexcept : rawPtr_(ptr.rawPtr_), cb_(ptr.cb_)
{
    cb_->increasSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr &&ptr) noexcept : rawPtr_(ptr.rawPtr_), cb_(ptr.cb_)
{
    ptr.rawPtr_ = nullptr;
    ptr.cb_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() noexcept
{
    cb_->decreaseSharedRef();
}

template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr &ptr) noexcept
{
    if (ptr != this)
    {
        deleteStoredPointers();
        rawPtr_ = ptr.rawPtr_;
        cb_ = ptr.cb_;
        cb_->increasSharedRef();
    }
    return *this;
}

template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr &&ptr) noexpect
{
    if (ptr != this)
    {
        deleteStoredPointers();
        rawPtr_ = ptr.rawPtr_;
        cb_ = ptr.cb_;
        rawPtr_ = nullptr;
        cb_ = nullptr;
    }
    return *this;
}

template <typename T>
const T *shared_ptr<T>::get() const noexcept
{
    return rawPtr_;
}

template <typename T>
T *shared_ptr<T>::reset() noexcept
{
}

template <typname T>
long shared_ptr<T>::use_count() const noexcept
{
    if (cb_)
    {
        return cb_->getSharedRef();
    }
    return 0;
}
