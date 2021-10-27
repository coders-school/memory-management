#pragma once

#include "shared_ptr.hpp"
#include "controlBlock.hpp"

template <typename T>
class Weak_Ptr
{
private:
    T *rawPtr_;
    ControlBlock<T> *cb_;

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