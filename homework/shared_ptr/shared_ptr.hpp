#pragma once
// TODO: VERIFY INCLUDES

#include "weak_ptr.hpp"

#include <atomic>
// TODO: REMOVE
#include <functional>
#include <iostream>
#include <type_traits>
namespace my {

// TODO: VERIFY if needed
template <typename Type>
class weak_ptr;

template <typename Type>
void defaultDelete(Type* managedObj) {
    delete managedObj;
    managedObj = nullptr;
}

template <typename Type>
class shared_ptr {
public:
    template <typename OtherType>
    friend class shared_ptr;

    template <typename OtherType>
    friend class weak_ptr;

    // TODO: REMOVE
    // -------------------- DONE PART ----------------------
    // using ElementType = Type;  // TODO: REMOVE
    using DeleterType = std::function<void(Type*)>;
    struct ControlBlock;

    ~shared_ptr();

    constexpr shared_ptr() noexcept;

    constexpr shared_ptr(std::nullptr_t) noexcept;

    template <class Deleter = DeleterType>
    shared_ptr(std::nullptr_t ptr, Deleter deleter);

    template <typename OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType*, Type*>>>
    explicit shared_ptr(OtherType* ptr);

    template <typename OtherType,
              typename Deleter = DeleterType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    shared_ptr(OtherType* ptr, Deleter deleter);

    shared_ptr(const shared_ptr& other) noexcept;

    template <typename OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    shared_ptr(const shared_ptr<OtherType>& other) noexcept;

    shared_ptr(shared_ptr&& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    shared_ptr(shared_ptr<OtherType>&& other) noexcept;

    shared_ptr& operator=(const shared_ptr& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    shared_ptr& operator=(const shared_ptr<OtherType>& other) noexcept;

    shared_ptr& operator=(shared_ptr&& other) noexcept;

    template <class OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    shared_ptr& operator=(shared_ptr<OtherType>&& other) noexcept;

    template <typename OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType*, Type*>>>
    explicit shared_ptr(const weak_ptr<OtherType>& other);

    void reset() noexcept;

    template <typename OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType*, Type*>>>
    void reset(OtherType* ptr);

    template <typename OtherType,
              typename Deleter = DeleterType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType&, Type&>>>
    void reset(OtherType* ptr, Deleter deleter);

    Type* get() const noexcept;

    long use_count() const noexcept;

    // // TODO: REMOVE
    // // long weak_count() const noexcept;

    // // DeleterType get_deleter() const noexcept;

    explicit operator bool() const noexcept;

    Type& operator*() const noexcept;

    Type* operator->() const noexcept;

    //  -------------------- MAYBE OPTIONAL  ----------------------
    // TODO: REMOVE

    // template <class Y, class Deleter>
    // shared_ptr(std::unique_ptr<Y, Deleter>&& r);   NOTE: maybe optional

    // template <class Y, class Deleter>
    // shared_ptr& operator=(std::unique_ptr<Y, Deleter>&& r);   NOTE: maybe optional

    // // TODO: CONSIDER deduction guides

    // // ------------------ PURE OPTIONAL ---------------------------------
    // template <class Y, class Deleter, class Alloc>
    // shared_ptr(Y* ptr, Deleter d, Alloc alloc);  // NOTE:  OPTIONAL

    // template <class Deleter, class Alloc>
    // shared_ptr(std::nullptr_t ptr, Deleter d, Alloc alloc);  // NOTE:  OPTIONAL

    // template <class Y>
    // shared_ptr(const shared_ptr<Y>& r, element_type* ptr) noexcept;  // NOTE:  OPTIONAL

    // template <class Y, class Deleter, class Alloc>
    // void reset(Y* ptr, Deleter d, Alloc alloc);  // NOTE:  OPTIONAL

    // void swap(shared_ptr& r) noexcept;  // NOTE:  OPTIONAL

    // element_type* get() const noexcept;  // NOTE:  OPTIONAL

    // bool unique() const noexcept;  // NOTE: OPTIONAL

    // template <class Y>
    // bool owner_before(const shared_ptr<Y>& other) const noexcept;  // NOTE: OPTIONAL

    // template <class Y>
    // bool owner_before(const weak_ptr<Y>& other) const noexcept;  // NOTE: OPTIONAL

private:
    void freeCurrentOwnership();

    ControlBlock* ctrlBlock_;
    Type* ptr_;
};
// TODO: VERIFY
//  template <typename Type, void (*DelType)(Type*)>
//  struct shared_ptr<Type, DelType>::ControlBlock {
//      ControlBlock(size_t sharedCount = 0,
//                   size_t weakCount = 0,
//                   DeleterType deleter = DelType)
//          : sharedCount_{sharedCount},
//            weakCount{weakCount},
//            deleter_{deleter} {}

//     std::atomic<size_t> sharedCount_;
//     std::atomic<size_t> weakCount;
//     DeleterType deleter_;
// };
template <typename Type>
struct shared_ptr<Type>::ControlBlock {
    ControlBlock(size_t sharedCount = 0,
                 size_t weakCount = 0,
                 DeleterType deleter = defaultDelete<Type>)
        : sharedCount_{sharedCount},
          weakCount{weakCount},
          deleter_{deleter} {}

    std::atomic<size_t> sharedCount_;
    std::atomic<size_t> weakCount;
    DeleterType deleter_;
};

template <typename Type>
constexpr shared_ptr<Type>::shared_ptr() noexcept
    : ctrlBlock_{nullptr}, ptr_{nullptr} {
}

template <typename Type>
constexpr shared_ptr<Type>::shared_ptr(std::nullptr_t) noexcept
    // TODO: VERIFY if empty initialization
    : shared_ptr{} {}

template <typename Type>
template <class Deleter>
shared_ptr<Type>::shared_ptr(std::nullptr_t, Deleter)
    // TODO: VERIFY if empty initialization
    : shared_ptr{} {}

// TODO: VERIFY maybe enable_if not needed here and everywhere
template <typename Type>
template <typename OtherType, typename>
shared_ptr<Type>::shared_ptr(OtherType* ptr)
    : ctrlBlock_(new ControlBlock{1, 0}),
      ptr_(static_cast<Type*>(ptr)) {
}

template <typename Type>
template <class OtherType, class Deleter, typename>
shared_ptr<Type>::shared_ptr(OtherType* ptr, Deleter deleter)
    : ctrlBlock_(new ControlBlock{1, 0, deleter}),
      ptr_(static_cast<Type*>(ptr)) {
}

template <typename Type>
Type* shared_ptr<Type>::get() const noexcept {
    return ptr_;
}

template <typename Type>
long shared_ptr<Type>::use_count() const noexcept {
    return ctrlBlock_ ? ctrlBlock_->sharedCount_.load()
                      : 0;
}

// // // TODO: REMOVE maybe
// // template <typename Type, void (*DelType)(Type*)>
// // long shared_ptr<Type, DelType>::weak_count() const noexcept {
// //     return ctrlBlock_ ? ctrlBlock_->weakCount.load()
// //                       : 0;
// // }

// // TODO: VERIFY maybe remove
// // template <typename Type, void (*DelType)(Type*)>
// // shared_ptr<Type, DelType>::DeleterType
// // shared_ptr<Type, DelType>::get_deleter() const noexcept {
// //     return ctrlBlock_ ? ctrlBlock_->deleter_
// //                       : nullptr;
// // }

template <typename Type>
shared_ptr<Type>::shared_ptr(const shared_ptr& other) noexcept
    : ctrlBlock_(other.ctrlBlock_), ptr_(other.ptr_) {
    if (ptr_) {
        ctrlBlock_->sharedCount_ += 1;
    }
}

template <typename Type>
template <typename OtherType, typename>
shared_ptr<Type>::shared_ptr(const shared_ptr<OtherType>& other) noexcept
    : ctrlBlock_(reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_)),
      ptr_(other.get()) {
    if (ptr_) {
        ctrlBlock_->sharedCount_ += 1;
    }
}

template <typename Type>
shared_ptr<Type>::shared_ptr(shared_ptr&& other) noexcept
    : ctrlBlock_(other.ctrlBlock_),
      ptr_(other.ptr_) {
    other.ptr_ = nullptr;
    other.ctrlBlock_ = nullptr;
}

template <typename Type>
template <typename OtherType, typename>
shared_ptr<Type>::shared_ptr(shared_ptr<OtherType>&& other) noexcept
    : ctrlBlock_(reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_)),
      ptr_(other.ptr_) {
    other.ptr_ = nullptr;
    other.ctrlBlock_ = nullptr;
}

template <typename Type>
template <typename OtherType, typename>
shared_ptr<Type>::shared_ptr(const weak_ptr<OtherType>& other)
    : ctrlBlock_(reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_)),
      ptr_(other.ptr_) {
    if (ctrlBlock_) {
        ctrlBlock_->sharedCount_++;
    }
}

// TODO: VERIFY if controlblock destroyed always
template <typename Type>
shared_ptr<Type>::~shared_ptr() {
    freeCurrentOwnership();
}

template <typename Type>
shared_ptr<Type>& shared_ptr<Type>::operator=(const shared_ptr& other) noexcept {
    if (this == &other) {
        return *this;
    }

    freeCurrentOwnership();

    ptr_ = other.ptr_;
    ctrlBlock_ = other.ctrlBlock_;
    ctrlBlock_->sharedCount_++;

    return *this;
}

template <typename Type>
template <class OtherType, typename>
shared_ptr<Type>& shared_ptr<Type>::operator=(const shared_ptr<OtherType>& other) noexcept {
    if (this == reinterpret_cast<const shared_ptr<Type>*>(&other)) {
        return *this;
    }

    freeCurrentOwnership();

    ptr_ = other.get();
    ctrlBlock_ = reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_);
    ctrlBlock_->sharedCount_++;

    return *this;
}

template <typename Type>
shared_ptr<Type>& shared_ptr<Type>::operator=(shared_ptr&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    freeCurrentOwnership();

    ptr_ = other.get();
    ctrlBlock_ = other.ctrlBlock_;

    other.ptr_ = nullptr;
    other.ctrlBlock_ = nullptr;

    return *this;
}

template <typename Type>
template <class OtherType, typename>
shared_ptr<Type>& shared_ptr<Type>::operator=(shared_ptr<OtherType>&& other) noexcept {
    if (this == reinterpret_cast<const shared_ptr<Type>*>(&other)) {
        return *this;
    }

    freeCurrentOwnership();

    ptr_ = other.get();
    ctrlBlock_ = reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.ctrlBlock_);

    other.ptr_ = nullptr;
    other.ctrlBlock_ = nullptr;

    return *this;
}

template <typename Type>
void shared_ptr<Type>::freeCurrentOwnership() {
    if (ptr_) {
        ctrlBlock_->sharedCount_--;

        if (ctrlBlock_->sharedCount_ == 0) {
            ctrlBlock_->deleter_(ptr_);

            if (ctrlBlock_->weakCount == 0) {
                delete ctrlBlock_;
                ctrlBlock_ = nullptr;
            }
        }
        ptr_ = nullptr;
    }
    // TODO: VERIFY perhaps needed to prevent leaks
    else {
        if (ctrlBlock_ && ctrlBlock_->weakCount == 0) {
            delete ctrlBlock_;
            ctrlBlock_ = nullptr;
        }
    }
}

template <typename Type>
shared_ptr<Type>::operator bool() const noexcept {
    return static_cast<bool>(ptr_);
}

template <typename Type>
Type& shared_ptr<Type>::operator*() const noexcept {
    return *ptr_;
}

template <typename Type>
Type* shared_ptr<Type>::operator->() const noexcept {
    return ptr_;
}

template <typename Type>
void shared_ptr<Type>::reset() noexcept {
    freeCurrentOwnership();
    ctrlBlock_ = nullptr;
}

template <typename Type>
template <typename OtherType, typename>
void shared_ptr<Type>::reset(OtherType* ptr) {
    freeCurrentOwnership();
    ptr_ = ptr;

    if (ptr_) {
        ctrlBlock_ = new ControlBlock(1, 0);
    }
}

template <typename Type>
template <typename OtherType, typename Deleter, typename>
void shared_ptr<Type>::reset(OtherType* ptr, Deleter deleter) {
    freeCurrentOwnership();
    ptr_ = ptr;

    if (ptr_) {
        ctrlBlock_ = new ControlBlock(1, 0, deleter);
    }
}

}  // namespace my
