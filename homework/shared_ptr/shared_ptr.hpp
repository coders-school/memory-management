#pragma once
// TODO: VERIFY INCLUDES
#include <atomic>
// TODO: REMOVE
#include <iostream>
#include <type_traits>
namespace my {

template <typename Type>
void defaultDelete(Type* managedObj) {
    delete managedObj;
}
// TODO: VERIFY
//  template <typename Type, template <typename DelType> class Deleter = defaultDelete<Type>>
//  template <typename Type, template <typename DelType> typename = defaultDelete>
//  template <typename Type, typename Deleter = typename defaultDelete<Type>>
template <typename Type, void (*DelType)(Type*) = defaultDelete>
class shared_ptr {
public:
    // TODO: REMOVE
    // -------------------- DONE PART ----------------------
    using ElementType = Type;
    using DeleterType = void (*)(ElementType*);
    struct ControlBlock;

    constexpr shared_ptr() noexcept;
    constexpr shared_ptr(std::nullptr_t) noexcept;

    template <typename OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType, Type>>>
    explicit shared_ptr(OtherType* ptr);

    shared_ptr(const shared_ptr& other) noexcept;

    template <typename OtherType,
              typename = std::enable_if_t<std::is_convertible_v<OtherType, Type>>>
    shared_ptr(const shared_ptr<OtherType>& other) noexcept;

    Type* get() const noexcept;
    long use_count() const noexcept;
    // TODO: VERIFY
    long weak_count() const noexcept;
    DeleterType get_deleter() const noexcept;
    // TODO: VERIFY
    ControlBlock* get_control_block() const noexcept;

    //  -------------------- END OF DONE PART ----------------------

    template <typename OtherType,
              typename Deleter,
              typename = std::enable_if_t<std::is_convertible_v<OtherType, Type>>>
    shared_ptr(OtherType* ptr, Deleter d);  // TODO:

    // template <class Deleter>
    // shared_ptr(std::nullptr_t ptr, Deleter d);  // TODO:   // NOTE: maybe optional

    // shared_ptr(shared_ptr&& r) noexcept;  // TODO:

    // template <class Y>
    // shared_ptr(shared_ptr<Y>&& r) noexcept;  // TODO:   // NOTE: maybe optional

    // template <class Y>
    // explicit shared_ptr(const weak_ptr<Y>& r);  // TODO:

    // template <class Y, class Deleter>
    // shared_ptr(std::unique_ptr<Y, Deleter>&& r);  // TODO:

    // ~shared_ptr();  // TODO:

    // shared_ptr& operator=(const shared_ptr& r) noexcept;  // TODO:

    // template <class Y>
    // shared_ptr& operator=(const shared_ptr<Y>& r) noexcept;  // NOTE: maybe optional

    // shared_ptr& operator=(shared_ptr&& r) noexcept;  // TODO:

    // template <class Y>
    // shared_ptr& operator=(shared_ptr<Y>&& r) noexcept;  // NOTE: maybe optional

    // template <class Y, class Deleter>
    // shared_ptr& operator=(std::unique_ptr<Y, Deleter>&& r);  // TODO:

    // void reset() noexcept;  // TODO:

    // template <class Y>
    // void reset(Y* ptr);  // TODO:

    // template <class Y, class Deleter>
    // void reset(Y* ptr, Deleter d);  // TODO:

    // T& operator*() const noexcept;  // TODO:

    // T* operator->() const noexcept;  // TODO:

    // explicit operator bool() const noexcept;  // TODO:

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
    ControlBlock* ctrlBlock_ = nullptr;
    ElementType* ptr_ = nullptr;
};

template <typename Type, typename Deleter>
struct shared_ptr<Type>::ControlBlock {
    ControlBlock(size_t sharedCount = 0,
                 size_t weakCount = 0,
                 DeleterType deleter = nullptr)
        : sharedCount_{sharedCount},
          weakCount{weakCount},
          deleter_{deleter} {}

    std::atomic<size_t> sharedCount_;
    std::atomic<size_t> weakCount;
    DeleterType deleter_;
};

template <typename Type, typename Deleter constexpr shared_ptr<Type>::shared_ptr() noexcept : ctrlBlock_{}, ptr_{nullptr} {
}

template <typename Type, typename Deleter constexpr shared_ptr<Type>::shared_ptr(std::nullptr_t) noexcept : shared_ptr{} {}

template <typename Type, typename Deleter template <typename OtherType, typename> shared_ptr<Type>::shared_ptr(OtherType* ptr) : ctrlBlock_(new ControlBlock{1, 0, nullptr}), ptr_(static_cast<Type*>(ptr)) {
}
// TODO: VERIFY
template <typename Type, typename Deleter template <class OtherType, class Deleter, typename> shared_ptr<Type>::shared_ptr(OtherType* ptr, Deleter d) {
}

// end of Verify

template <typename Type, typename Deleter Type* shared_ptr<Type>::get() const noexcept {
    return ptr_;
}

template <typename Type, typename Deleter long shared_ptr<Type>::use_count() const noexcept {
    return ctrlBlock_ ? ctrlBlock_->sharedCount_.load()
                      : 0;
}
// TODO: REMOVE maybe
template <typename Type, typename Deleter long shared_ptr<Type>::weak_count() const noexcept {
    return ctrlBlock_ ? ctrlBlock_->weakCount.load()
                      : 0;
}

template <typename Type, typename Deleter shared_ptr<Type>::DeleterType shared_ptr<Type>::get_deleter() const noexcept {
    return ctrlBlock_ ? ctrlBlock_->deleter_
                      : nullptr;
}

template <typename Type, typename Deleter shared_ptr<Type>::ControlBlock* shared_ptr<Type>::get_control_block() const noexcept {
    return ctrlBlock_;
}

template <typename Type, typename Deleter shared_ptr<Type>::shared_ptr(const shared_ptr& other) noexcept : ctrlBlock_(other.ctrlBlock_), ptr_(other.ptr_) {
    if (ptr_) {
        ctrlBlock_->sharedCount_ += 1;
    }
}

template <typename Type, typename Deleter>
template <typename OtherType, typename>
shared_ptr<Type>::shared_ptr(const shared_ptr<OtherType>& other) noexcept
    : ctrlBlock_(reinterpret_cast<shared_ptr<Type>::ControlBlock*>(other.get_control_block())),
      ptr_(other.get()) {
    if (ptr_) {
        ctrlBlock_->sharedCount_ += 1;
    }
}

}  // namespace my
