#pragma once

#include "shared_ptr.hpp"

#include <type_traits>

namespace my {
template <typename Type>
class shared_ptr;

template <typename Type>
class weak_ptr {
public:
    template <typename OtherType>
    friend class shared_ptr;
    template <typename OtherType>
    friend class weak_ptr;

    ~weak_ptr();

    constexpr weak_ptr() noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType*, Type*>>>
    weak_ptr(const shared_ptr<OtherType>& other) noexcept;

    weak_ptr(const weak_ptr& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType*, Type*>>>
    weak_ptr(const weak_ptr<OtherType>& other) noexcept;

    weak_ptr(weak_ptr&& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType*, Type*>>>
    weak_ptr(weak_ptr<OtherType>&& other) noexcept;

    weak_ptr& operator=(const weak_ptr& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    weak_ptr& operator=(const weak_ptr<OtherType>& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    weak_ptr& operator=(const shared_ptr<OtherType>& other) noexcept;

    weak_ptr& operator=(weak_ptr&& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    weak_ptr& operator=(weak_ptr<OtherType>&& other) noexcept;

    bool expired() const noexcept;
    long use_count() const noexcept;
    shared_ptr<Type> lock();
    void reset() noexcept;

private:
    shared_ptr<Type>::ControlBlock* ctrlBlock_;
    Type* ptr_;
};

template <typename Type>
constexpr weak_ptr<Type>::weak_ptr() noexcept
    : ctrlBlock_(nullptr),
      ptr_(nullptr) {
}

template <typename Type>
template <class OtherType, typename>
weak_ptr<Type>::weak_ptr(const shared_ptr<OtherType>& other) noexcept
    : ctrlBlock_(reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_)),
      ptr_(other.ptr_) {
    if (ctrlBlock_) {
        ctrlBlock_->weakCount++;
    }
}

template <typename Type>
weak_ptr<Type>::weak_ptr(const weak_ptr& other) noexcept
    : ctrlBlock_(other.ctrlBlock_),
      ptr_(other.ptr_) {
    if (ctrlBlock_) {
        ctrlBlock_->weakCount++;
    }
}

template <class Type>
template <class OtherType, typename>
weak_ptr<Type>::weak_ptr(const weak_ptr<OtherType>& other) noexcept
    : ctrlBlock_(reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_)),
      ptr_(other.ptr_) {
    if (ctrlBlock_) {
        ctrlBlock_->weakCount++;
    }
}

template <class Type>
weak_ptr<Type>::weak_ptr(weak_ptr&& other) noexcept
    : ctrlBlock_(other.ctrlBlock_),
      ptr_(other.ptr_) {
    other.ptr_ = nullptr;
    other.ctrlBlock_ = nullptr;
}

template <class Type>
template <class OtherType, typename>
weak_ptr<Type>::weak_ptr(weak_ptr<OtherType>&& other) noexcept
    : ctrlBlock_(reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_)),
      ptr_(other.ptr_) {
    other.ptr_ = nullptr;
    other.ctrlBlock_ = nullptr;
}

template <class Type>
weak_ptr<Type>::~weak_ptr() {
    reset();
}

template <class Type>
void weak_ptr<Type>::reset() noexcept {
    if (ctrlBlock_) {
        if (ctrlBlock_->weakCount > 0) {
            ctrlBlock_->weakCount--;
        }
        if (ctrlBlock_->weakCount == 0 && ctrlBlock_->sharedCount_ == 0) {
            if (!ctrlBlock_->memory_storage_) {
                delete ctrlBlock_;
            } else {
                delete[] ctrlBlock_->memory_storage_;
            }
            ctrlBlock_ = nullptr;
        }
    }
    ctrlBlock_ = nullptr;
    ptr_ = nullptr;
}

template <class Type>
weak_ptr<Type>& weak_ptr<Type>::operator=(const weak_ptr& other) noexcept {
    ctrlBlock_ = other.ctrlBlock_;
    ptr_ = other.ptr_;
    if (ctrlBlock_) {
        ctrlBlock_->weakCount++;
    }
    return *this;
}

template <class Type>
template <class OtherType, typename>
weak_ptr<Type>& weak_ptr<Type>::operator=(const weak_ptr<OtherType>& other) noexcept {
    ctrlBlock_ = reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_);
    ptr_ = other.ptr_;
    if (ctrlBlock_) {
        ctrlBlock_->weakCount++;
    }

    return *this;
}

template <class Type>
template <class OtherType, typename>
weak_ptr<Type>& weak_ptr<Type>::operator=(const shared_ptr<OtherType>& other) noexcept {
    ctrlBlock_ = reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_);
    ptr_ = other.ptr_;
    if (ctrlBlock_) {
        ctrlBlock_->weakCount++;
    }

    return *this;
}

template <class Type>
weak_ptr<Type>& weak_ptr<Type>::operator=(weak_ptr&& other) noexcept {
    ctrlBlock_ = other.ctrlBlock_;
    ptr_ = other.ptr_;
    other.ctrlBlock_ = nullptr;
    other.ptr_ = nullptr;

    return *this;
}

template <class Type>
template <class OtherType, typename>
weak_ptr<Type>& weak_ptr<Type>::operator=(weak_ptr<OtherType>&& other) noexcept {
    ctrlBlock_ = reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_);
    ptr_ = other.ptr_;
    other.ctrlBlock_ = nullptr;
    other.ptr_ = nullptr;

    return *this;
}

template <class Type>
long weak_ptr<Type>::use_count() const noexcept {
    return ctrlBlock_ ? ctrlBlock_->sharedCount_.load()
                      : 0;
}

template <class Type>
bool weak_ptr<Type>::expired() const noexcept {
    return !static_cast<bool>(use_count());
}

template <class Type>
shared_ptr<Type> my::weak_ptr<Type>::lock() {
    return expired() ? shared_ptr<Type>() : shared_ptr<Type>(*this);
}

template <typename Type>
weak_ptr(shared_ptr<Type>) -> weak_ptr<Type>;
}  // namespace my
