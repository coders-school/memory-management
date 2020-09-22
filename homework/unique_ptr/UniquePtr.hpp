#pragma once

template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* ptr) noexcept;
    UniquePtr(UniquePtr&& uniquePtr) noexcept;
    UniquePtr(const UniquePtr&) = delete;
    ~UniquePtr() { delete ptr_; }
    T* get() const noexcept { return ptr_; }
    T* operator->();
    T& operator*() const;
    UniquePtr<T>& operator=(UniquePtr&& ptr) noexcept;
    UniquePtr<T>& operator=(const UniquePtr&) = delete;
    T* release() noexcept;
    void reset(T* ptr) noexcept;

private:
    T* ptr_;
};

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr) noexcept : ptr_(ptr) {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& ptr) noexcept {
    this->ptr_ = ptr.release();
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& ptr) noexcept {
    if (this != &ptr) {
        this->reset(ptr.release());
    }
    return *this;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
    return *UniquePtr<T>::get();
}

template <typename T>
T* UniquePtr<T>::operator->() {
    return UniquePtr<T>::get();
}

template <typename T>
T* UniquePtr<T>::release() noexcept {
    T* old_ptr = ptr_;
    ptr_ = nullptr;
    return old_ptr;
}

template <typename T>
void UniquePtr<T>::reset(T* ptr) noexcept {
    delete ptr_;
    ptr_ = ptr;
}