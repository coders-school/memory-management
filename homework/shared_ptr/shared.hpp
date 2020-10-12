#pragma once

#include <stdexcept>

#include "bad_weak_ptr.hpp"
#include "control.hpp"
#include "controlObject.hpp"
#include "weak.hpp"  //necessary to create c-tor with cs::weak_ptr as argument

namespace cs
{
template <typename T>  // this forward declaration is a must-have in order to be able to use weak.hpp as a stand-alone
                       // file
class weak_ptr;  // without this line weak.hpp on it's own would not compile!

template <typename T>
class shared_ptr;

template <typename T, typename... Ts>
shared_ptr<T> make_shared(Ts&&...);

template <typename T>
class shared_ptr
{
    template <typename U>
    friend class weak_ptr;

    template <typename U, typename... Ts>
    friend shared_ptr<U> make_shared(Ts&&...);

    T* data_{nullptr};
    control_block<T>* controlBlock_{nullptr};

    void releaseMemory() noexcept;
    shared_ptr(control_block<T>*) noexcept;

   public:
    shared_ptr() noexcept = default;
    explicit shared_ptr(T* data, Deleter<T>deleter = defaultDeleter);
    shared_ptr(const shared_ptr&) noexcept;
    shared_ptr(shared_ptr&&) noexcept;
    explicit shared_ptr(const weak_ptr<T>&);
    ~shared_ptr() noexcept;

    shared_ptr& operator=(shared_ptr&&) noexcept;
    shared_ptr& operator=(const shared_ptr&) noexcept;

    T* get() const noexcept { return data_; }
    T& operator*() noexcept { return *data_; }
    T* operator->() noexcept { return data_; }
    operator bool() const noexcept { return data_ != nullptr; }
    int use_count() const noexcept;
    void reset(T* data = nullptr, Deleter<T> deleter = defaultDeleter) noexcept;
    // void reset(T* data, Deleter<T> deleter) noexcept;
};

template <typename T, typename... Ts>
shared_ptr<T> make_shared(Ts&&... args)
{
    return shared_ptr<T>{new controlObject<T>(std::forward<T>(args)...)};
}

template <typename T>
shared_ptr<T>::shared_ptr(control_block<T>* block) noexcept
{
    if (block->getObject()) {
        data_ = block->getObject();
        controlBlock_ = block;
    }
}
template <typename T>
shared_ptr<T>::shared_ptr(T* data, Deleter<T> deleter): data_(data)
{
    try {
        controlBlock_ = new control_block<T>(deleter);
    }
    catch (const std::bad_alloc&) {
        delete data_;
        throw;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& rhs) noexcept : data_(rhs.data_), controlBlock_(rhs.controlBlock_)
{
    controlBlock_->incrementSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& rhs) noexcept : data_(rhs.data_), controlBlock_(rhs.controlBlock_)
{
    rhs.data_ = nullptr;
    rhs.controlBlock_ = nullptr;
}

template <typename T>
shared_ptr<T>::shared_ptr(const weak_ptr<T>& rhs)
{
    if (rhs.expired()) {
        throw cs::bad_weak_ptr{};
    }
    data_ = rhs.data_;
    controlBlock_ = rhs.controlBlock_;
    controlBlock_->incrementSharedRef();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    releaseMemory();
    data_ = rhs.data_;
    controlBlock_ = rhs.controlBlock_;
    if (controlBlock_) {
        controlBlock_->incrementSharedRef();
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& rhs) noexcept
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
shared_ptr<T>::~shared_ptr() noexcept
{
    releaseMemory();
}

template <typename T>
void shared_ptr<T>::releaseMemory() noexcept
{
    if (!controlBlock_) {
        return;
    }
    controlBlock_->decrementSharedRef();
    if (controlBlock_->getObject()) {
        if (controlBlock_->getSharedRef() == 0 && controlBlock_->getWeakRef() == 0) {
            delete controlBlock_;
            controlBlock_ = nullptr;
        }
    } else {
        if (controlBlock_->getSharedRef() == 0) {
            controlBlock_->getDeleter()(data_);
            data_ = nullptr;
            if (controlBlock_->getWeakRef() == 0) {
                delete controlBlock_;
                controlBlock_ = nullptr;
            }
        }
    }
}
template <typename T>
void shared_ptr<T>::reset(T* data, Deleter<T> deleter) noexcept
{
    releaseMemory();
    data_ = data;
    if (data != nullptr) {
        controlBlock_ = new control_block<T>(deleter);
    } else {
        controlBlock_ = nullptr;
    }
}

template <typename T>
int shared_ptr<T>::use_count() const noexcept
{
    if (controlBlock_) {
        return controlBlock_->getSharedRef();
    }
    return 0;
}
};  // namespace cs
