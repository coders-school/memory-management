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

    constexpr weak_ptr() noexcept;
    bool expired() const noexcept;
    long use_count() const noexcept;

    //============ TODO ======================

    // weak_ptr(const weak_ptr& other) noexcept;

    // template <class OtherType>
    // weak_ptr(const weak_ptr<OtherType>& other) noexcept;  // TODO:

    template <class OtherType>
    //   typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    //   typename = std::enable_if_t<std::is_same_v<OtherType&, Type&>>>
    weak_ptr(const shared_ptr<OtherType>& other) noexcept;  // TODO:

    // template <class Type>
    // weak_ptr(weak_ptr<Type>&& other) noexcept;  // TODO:

    // ~weak_ptr();  // TODO:

    // weak_ptr& operator=(const weak_ptr& other) noexcept;  // TODO:

    // template <class OtherType>
    // weak_ptr& operator=(const weak_ptr<OtherType>& other) noexcept;  // TODO:

    // template <class OtherType>
    // weak_ptr& operator=(const shared_ptr<OtherType>& other) noexcept;  // TODO:

    // weak_ptr& operator=(weak_ptr&& other) noexcept;  // TODO:

    // template <class OtherType>
    // weak_ptr& operator=(weak_ptr<OtherType>&& other) noexcept;  // TODO:

    // void reset() noexcept;  // TODO:

    // shared_ptr<Type> lock();  // TODO:

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

template <typename Type>
template <class OtherType>
weak_ptr<Type>::weak_ptr(const shared_ptr<OtherType>& other) noexcept
    : ctrlBlock_(other.ctrlBlock_),
      ptr_(other.ptr_) {
}

// template <class Type>
// weak_ptr<Type>::weak_ptr(const weak_ptr<Type>& r) noexcept {
//     // TODO:
// }

// template <class Type>
// weak_ptr<Type>::weak_ptr(weak_ptr<Type>&& r) noexcept {
//     // TODO:
// }

// template <class Type>
// weak_ptr<Type>::~weak_ptr() {  // TODO:}
//     // NOTE: remember about destruction of control block
// }

// template <class Type>
// weak_ptr<Type>& weak_ptr<Type>::operator=(const weak_ptr& r) noexcept {
//     // TODO:
// }

// template <class Type>
// template <class OtherType>
// weak_ptr<Type>& weak_ptr<Type>::operator=(const weak_ptr<OtherType>& other) noexcept {
//     // TODO:
// }

// template <class Type>
// template <class OtherType>
// weak_ptr<Type>& weak_ptr<Type>::operator=(const shared_ptr<OtherType>& other) noexcept {
//     // TODO:
// }

// template <class Type>
// weak_ptr<Type>& weak_ptr<Type>::operator=(weak_ptr&& r) noexcept {
//     // TODO:
// }

// template <class Type>
// template <class OtherType>
// weak_ptr<Type>& weak_ptr<Type>::operator=(weak_ptr<OtherType>&& other) noexcept {
//     // TODO:
// }

// template <class Type>
// void weak_ptr<Type>::reset() noexcept {
//     // TODO:
// }

template <class Type>
long weak_ptr<Type>::use_count() const noexcept {
    return ctrlBlock_ ? ctrlBlock_->sharedCount_.load()
                      : 0;
}

template <class Type>
bool weak_ptr<Type>::expired() const noexcept {
    return static_cast<bool>(use_count());
}

// template <class Type>
// shared_ptr<Type> std::weak_ptr<T>::lock() {
//     // TODO:
//     // expired() ? shared_ptr<T>() : shared_ptr<T>(*this)
// }

// //TODO: VERIFY DEDUCTION guides
// template <typename Type>
// weak_ptr(shared_ptr<Type>) -> weak_ptr<Type>;
}  // namespace my
