#pragma once
// TODO: VERIFY if can be substituted with declaration but unlikely
#include "shared_ptr.hpp"

namespace my {
// TODO: VERIFY
//  template <typename Type, void (*DelType)(Type*)>
//  class shared_ptr;

// template <typename Type, void (*DelType)(Type*)>
// struct shared_ptr<Type, DelType>::ControlBlock;

template <typename Type>
class weak_ptr {
public:
    using ElementType = Type;
    // TODO: VERIFY
    // using DeleterType = void (*)(ElementType*);

    constexpr weak_ptr() noexcept;  // TODO:

    //============ TODO ======================

    // template <class Y>
    // weak_ptr(const weak_ptr<Y>& r) noexcept;  // TODO:

    // template <class Y>
    // weak_ptr(const shared_ptr<Y>& r) noexcept;  // TODO:

    // template <class Y>
    // weak_ptr(weak_ptr<Y>&& r) noexcept;  // TODO:

    // ~weak_ptr();  // TODO:

    // weak_ptr& operator=(const weak_ptr& r) noexcept;  // TODO:

    // template <class Y>
    // weak_ptr& operator=(const weak_ptr<Y>& r) noexcept;  // TODO:

    // template <class Y>
    // weak_ptr& operator=(const shared_ptr<Y>& r) noexcept;  // TODO:

    // weak_ptr& operator=(weak_ptr&& r) noexcept;  // TODO:

    // template <class Y>
    // weak_ptr& operator=(weak_ptr<Y>&& r) noexcept;  // TODO:

    // void reset() noexcept; // TODO:

    // long use_count() const noexcept; // TODO:

    // bool expired() const noexcept; // TODO:

    // std::weak_ptr<T>::lock(); // TODO:

    // ================= OPTIONAL ========================
    // void swap( weak_ptr& r ) noexcept; NOTE: OPTIONAL

private:
    shared_ptr<Type>::ControlBlock* ctrlBlock_;

    ElementType* ptr_;
};

template <typename Type>
constexpr weak_ptr<Type>::weak_ptr() noexcept
    : ctrlBlock_(nullptr),
      ptr_(nullptr) {
}
}  // namespace my
