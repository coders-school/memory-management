#include <atomic>
#include "control.hpp"

template <typename T>
class weak_ptr;
namespace cs
{
template <typename T>
class shared_ptr
{
    template<typename U> friend class weak_ptr;
    T* data_{nullptr};
    control_block* controlBlock_{nullptr};

    void releaseMemory() noexcept;

   public:
    shared_ptr() noexcept = default;
    shared_ptr(T* data) noexcept;
    shared_ptr(const shared_ptr&) noexcept;
    shared_ptr(shared_ptr&&) noexcept;
    ~shared_ptr() noexcept;

    shared_ptr& operator=(shared_ptr&&) noexcept;
    shared_ptr& operator=(const shared_ptr&) noexcept;

    T* get() const noexcept { return data_; }
    T& operator*() noexcept { return *data_; }
    T* operator->() noexcept { return data_; }
    operator bool() const noexcept { return data_ != nullptr; }
    int use_count() const noexcept;
    void reset(T* data = nullptr) noexcept;
};

template <typename T>
shared_ptr<T>::shared_ptr(T* data) noexcept : data_(data)
{
    controlBlock_ = new control_block();
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
    if (controlBlock_) {
        controlBlock_->decrementSharedRef();
        if (controlBlock_->getSharedRef() == 0) {
            delete data_;
            delete controlBlock_;
        }
    }
}

template <typename T>
void shared_ptr<T>::reset(T* data) noexcept
{
    releaseMemory();
    data_ = data;
    controlBlock_ = new control_block();
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
