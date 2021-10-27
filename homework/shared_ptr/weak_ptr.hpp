#pragma once

#include "shared_ptr.hpp"
#include "controlBlock.hpp"

template <typename T>
class Weak_Ptr
{
private:
    T *rawPtr_;
    ControlBlock<T> *cb_;
    void releaseMemory();

public:
    Weak_Ptr() = default;
    Weak_Ptr(const Weak_Ptr &ptr) noexcept;
    Weak_Ptr(Weak_Ptr &&ptr) noexcept;
    ~Weak_Ptr();

    Weak_Ptr &operator=(const Weak_Ptr &ptr);
    Weak_Ptr &operator=(Weak_Ptr &&ptr);

    long use_count() const noexcept;
    bool expired() const noexcept;
    shared_ptr<T> lock() const noexcept;
    void reset() noexcept;
};

template <typename T>
void Weak_Ptr<T>::releaseMemory() {
    if (cb_) {
        cb_->decreaseWeakRef();
        if (cb_->getSharedRef() == 0 && cb_->getWeakRef() == 0)
        {
            delete cb_;
            cb_ = nullptr;
        }
    }
}


template <typename T>
Weak_Ptr<T>::Weak_Ptr(const Weak_Ptr &ptr) noexcept : rawPtr_(ptr.rawPtr_), cb_(ptr.cb_)
{
    cb_->increasWeakRef();
}

template <typename T>
Weak_Ptr<T>::Weak_Ptr(Weak_Ptr &&ptr) noexcept : rawPtr_(ptr.rawPtr_), cb_(ptr.cb_)
{
    ptr.rawPtr_ = nullptr;
    ptr.cb_ = nullptr;
}

template <typename T>
Weak_Ptr<T>::~Weak_Ptr()
{
    releaseMemory();
}

template <typename T>
Weak_Ptr<T> &Weak_Ptr<T>::operator=(const Weak_Ptr &ptr) noexcept
{
    if (ptr != this)
    {
        releaseMemory();
        rawPtr_ = ptr.rawPtr_;
        cb_ = ptr.cb_;
        cb_->increasWeakRef();
    }
    return *this;
}

template <typename T>
Weak_Ptr<T> &Weak_Ptr<T>::operator=(Weak_Ptr &&ptr) noexcept
{
    if (ptr != this)
    {
        rawPtr_ = ptr.rawPtr_;
        cb_ = ptr.cb_;
        

    }
}
