#pragma once

#include <cstddef>

#include "controlBlock.hpp"

class weak_ptr;

template <typename T>
class shared_ptr
{
public:
    shared_ptr(T *ptr) : rawPtr_(ptr), cb_(new ControlBlock<T>){};

    shared_ptr(const shared_ptr &ptr) noexcept;
    shared_ptr(shared_ptr &&ptr) noexcept;
    ~shared_ptr() noexcept;

    shared_ptr& operator=(const shared_ptr& ptr) noexcept;
    shared_ptr& operator=(shared_ptr &&ptr) noexcept;
    T &operator*() const noexcept;
    T *operator->() const noexcept;
    T *get() const noexcept;
    T *reset() noexcept;
    long use_count() const;
    explicit opeartor bool() const;

private:
    T *rawPtr_{nullptr};
    ControlBlock<T> *cb_{nullptr};
    void deleteStoredPointers();
};

template <typename T>
T *shared_ptr<T>::get() const noexcept
{
    return rawPtr_;
}

template <typename T> // TODO
T *shared_ptr<T>::reset() noexcept
{
}

template <typename T>
T &shared_ptr<T>::operator*() const noexcept
{
    return *ptr_;
}

template <typename T>
T *shared_ptr<T>::operator->() const noexcept
{
    return ptr_;
}

template <typename T> // TODO
void shared_ptr<T>::deleteStoredPointers()
{
    if (cb_)
    {
        cb_->decreaseSharedRef();
        if (cb_->getSharedRef() == 0 && cb_->getWeakRef() == 0)
        {
            delete cb_;
        }
    }
}

template <typename T>
shared_ptr<T>::~shared_ptr() noexcept
{
    deleteStoredPointers();
}

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
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& ptr) noexcept {
    if(&ptr != this) {
        deleteStoredPointers();
        rawPtr_ = ptr.rawPtr_;
        cb_ = ptr.cb_;
        cb_->increasSharedRef();
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& ptr) noexcept {
    if(ptr != this) {
        rawPtr_ = ptr.rawPtr_;
        cb_ = ptr.cb_;
        cb_->increasSharedRef();
        ptr_ = nullptr;
        cb_ = nullptr;
    }
    return this;
}

