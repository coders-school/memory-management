#pragma once
#include "shared.hpp" //needed in order to create weak_ptr out of shared_ptr

namespace cs
{

template <typename T> //this forward declaration is a must have in order to use shared_ptr as a stand-alone file
class shared_ptr; //without this code shared_ptr would not compile on it's own!

template <typename T>
class weak_ptr
{
    template <typename U> friend class shared_ptr;

    control_block<T>* controlBlock_{nullptr};
    T* data_{nullptr};

    void releaseMemory() noexcept;

   public:
    weak_ptr() noexcept = default;
    explicit weak_ptr(const shared_ptr<T>&) noexcept;
    weak_ptr(const weak_ptr<T>&) noexcept;
    weak_ptr(weak_ptr<T>&&) noexcept;
    ~weak_ptr() noexcept;
    weak_ptr<T>& operator=(const weak_ptr<T>&) noexcept;
    weak_ptr<T>& operator=(weak_ptr<T>&&) noexcept;
    weak_ptr<T>& operator=(const shared_ptr<T>&) noexcept;

    bool expired() const noexcept;
    int use_count() const noexcept;
    void reset() noexcept;
    shared_ptr<T> lock() noexcept;
};

template <typename T>
weak_ptr<T>::weak_ptr(const cs::shared_ptr<T>& rhs) noexcept : data_(rhs.data_), controlBlock_(rhs.controlBlock_)
{
    controlBlock_->incrementWeakRef();
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T>& rhs) noexcept : data_(rhs.data_), controlBlock_(rhs.controlBlock_)
{
    controlBlock_->incrementWeakRef();
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr<T>&& rhs) noexcept : data_(rhs.data_), controlBlock_(rhs.controlBlock_)
{
    rhs.data_ = nullptr;
    rhs.controlBlock_ = nullptr;
}

template <typename T>
weak_ptr<T>::~weak_ptr() noexcept
{
    releaseMemory();
}

template <typename T>
void weak_ptr<T>::releaseMemory() noexcept
{
    if (controlBlock_) {
        controlBlock_->decrementWeakRef();
        if (controlBlock_->getSharedRef() == 0 && controlBlock_->getWeakRef() == 0) {
            delete controlBlock_;
            controlBlock_ = nullptr;
        }
    }
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }
    releaseMemory();
    data_ = rhs.data_;
    controlBlock_ = rhs.controlBlock_;
    controlBlock_->incrementWeakRef();
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr<T>&& rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    releaseMemory();
    data_ = rhs.data_;
    controlBlock_ = rhs.controlBlock_;
    rhs.data_ = nullptr;
    rhs.controlBlock_ = nullptr;
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<T>& rhs) noexcept {
    releaseMemory();
    data_ = rhs.data_;
    controlBlock_ = rhs.controlBlock_;
    controlBlock_->incrementWeakRef();
    return *this;
}

template <typename T>
bool weak_ptr<T>::expired() const noexcept
{
    return controlBlock_->getSharedRef() == 0;
}

template <typename T>
int weak_ptr<T>::use_count() const noexcept {
    if (controlBlock_) {
        return controlBlock_->getSharedRef();
    }
    return 0;
}

template <typename T>

void weak_ptr<T>::reset() noexcept {
    releaseMemory();
    data_ = nullptr;
    controlBlock_ = nullptr;
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() noexcept {
    if (use_count() == 0) {
        return {};
    }
    return shared_ptr<T>(*this);
}

};  // namespace cs
