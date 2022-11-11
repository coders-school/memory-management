#pragma once

namespace my {

template <typename T>
class shared_ptr {
public:
    constexpr shared_ptr() noexcept;                // TODO:
    constexpr shared_ptr(std::nullptr_t) noexcept;  // TODO:

    template <class Y>
    explicit shared_ptr(Y* ptr);  // TODO:

    template <class Y, class Deleter>
    shared_ptr(Y* ptr, Deleter d);  // TODO:

    template <class Deleter>
    shared_ptr(std::nullptr_t ptr, Deleter d);  // TODO:   // NOTE: maybe optional

    shared_ptr(const shared_ptr& r) noexcept;  // TODO:

    shared_ptr(shared_ptr&& r) noexcept;  // TODO:

    template <class Y>
    shared_ptr(shared_ptr<Y>&& r) noexcept;  // TODO:   // NOTE: maybe optional

    template <class Y>
    shared_ptr(const shared_ptr<Y>& r) noexcept;  // TODO: // NOTE: maybe optional

    template <class Y>
    explicit shared_ptr(const std::weak_ptr<Y>& r);  // TODO:

    template <class Y, class Deleter>
    shared_ptr(std::unique_ptr<Y, Deleter>&& r);  // TODO:

    ~shared_ptr();  // TODO:

    shared_ptr& operator=(const shared_ptr& r) noexcept;  // TODO:

    template <class Y>
    shared_ptr& operator=(const shared_ptr<Y>& r) noexcept;  // NOTE: maybe optional

    shared_ptr& operator=(shared_ptr&& r) noexcept;  // TODO:

    template <class Y>
    shared_ptr& operator=(shared_ptr<Y>&& r) noexcept;  // NOTE: maybe optional

    template <class Y, class Deleter>
    shared_ptr& operator=(std::unique_ptr<Y, Deleter>&& r);  // TODO:

    void reset() noexcept;  // TODO:

    template <class Y>
    void reset(Y* ptr);  // TODO:

    template <class Y, class Deleter>
    void reset(Y* ptr, Deleter d);  // TODO:

    T* get() const noexcept;  // TODO:

    T& operator*() const noexcept;  // TODO:

    T* operator->() const noexcept;  // TODO:

    long use_count() const noexcept;  // TODO:

    explicit operator bool() const noexcept;  // TODO:

    // TODO: CONSIDER deduction guides

    // ------------------ PURE OPTIONAL ---------------------------------
    template <class Y, class Deleter, class Alloc>
    shared_ptr(Y* ptr, Deleter d, Alloc alloc);  // NOTE:  OPTIONAL

    template <class Deleter, class Alloc>
    shared_ptr(std::nullptr_t ptr, Deleter d, Alloc alloc);  // NOTE:  OPTIONAL

    template <class Y>
    shared_ptr(const shared_ptr<Y>& r, element_type* ptr) noexcept;  // NOTE:  OPTIONAL

    template <class Y, class Deleter, class Alloc>
    void reset(Y* ptr, Deleter d, Alloc alloc);  // NOTE:  OPTIONAL

    void swap(shared_ptr& r) noexcept;  // NOTE:  OPTIONAL

    element_type* get() const noexcept;  // NOTE:  OPTIONAL

    bool unique() const noexcept;  // NOTE: OPTIONAL

    template <class Y>
    bool owner_before(const shared_ptr<Y>& other) const noexcept;  // NOTE: OPTIONAL

    template <class Y>
    bool owner_before(const std::weak_ptr<Y>& other) const noexcept;  // NOTE: OPTIONAL
};
}  // namespace my