#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <atomic>
#include <utility>
#include <functional>

namespace my {

template <typename T>
class shared_ptr {
public:
    // Constructors
    explicit shared_ptr(T* ptr = nullptr);
    shared_ptr(const shared_ptr& other);
    shared_ptr(shared_ptr&& other) noexcept;
    
    // Destructor
    ~shared_ptr();
    
    // Assignment operators
    shared_ptr& operator=(const shared_ptr& other);
    shared_ptr& operator=(shared_ptr&& other) noexcept;
    
    // Member functions
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    void reset(T* ptr = nullptr);
    size_t use_count() const;
    explicit operator bool() const;

private:
    void release();

    T* ptr_;
    struct ControlBlock {
        std::atomic<size_t> shared_refs;
        std::atomic<size_t> weak_refs;
        std::function<void(T*)> deleter;

        ControlBlock(T* ptr, std::function<void(T*)> del)
            : shared_refs(1), weak_refs(0), deleter(del) {}
    } *control_;
};

// Constructor
template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) : ptr_(ptr) {
    if (ptr) {
        control_ = new ControlBlock(ptr, [](T* p) { delete p; });
    } else {
        control_ = nullptr;
    }
}

// Copy constructor
template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& other)
    : ptr_(other.ptr_), control_(other.control_) {
    if (control_) {
        control_->shared_refs++;
    }
}

// Move constructor
template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept
    : ptr_(other.ptr_), control_(other.control_) {
    other.ptr_ = nullptr;
    other.control_ = nullptr;
}

// Destructor
template <typename T>
shared_ptr<T>::~shared_ptr() {
    release();
}

// Copy assignment
template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& other) {
    if (this != &other) {
        release();
        ptr_ = other.ptr_;
        control_ = other.control_;
        if (control_) {
            control_->shared_refs++;
        }
    }
    return *this;
}

// Move assignment
template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other) noexcept {
    if (this != &other) {
        release();
        ptr_ = other.ptr_;
        control_ = other.control_;
        other.ptr_ = nullptr;
        other.control_ = nullptr;
    }
    return *this;
}

// Dereference operator
template <typename T>
T& shared_ptr<T>::operator*() const {
    return *ptr_;
}

// Arrow operator
template <typename T>
T* shared_ptr<T>::operator->() const {
    return ptr_;
}

// Get raw pointer
template <typename T>
T* shared_ptr<T>::get() const {
    return ptr_;
}

// Reset pointer
template <typename T>
void shared_ptr<T>::reset(T* ptr) {
    release();
    ptr_ = ptr;
    if (ptr) {
        control_ = new ControlBlock(ptr, [](T* p) { delete p; });
    } else {
        control_ = nullptr;
    }
}

// Get use count
template <typename T>
size_t shared_ptr<T>::use_count() const {
    return control_ ? control_->shared_refs.load() : 0;
}

// Bool conversion
template <typename T>
shared_ptr<T>::operator bool() const {
    return ptr_ != nullptr;
}

// Release resources
template <typename T>
void shared_ptr<T>::release() {
    if (control_) {
        if (--control_->shared_refs == 0) {
            control_->deleter(ptr_);
            if (control_->weak_refs == 0) {
                delete control_;
            }
        }
    }
    ptr_ = nullptr;
    control_ = nullptr;
}

} // namespace my

#endif // SHARED_PTR_HPP
