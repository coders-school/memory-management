#pragma once

namespace coders {

template <typename T>
class unique_ptr{
public:
    unique_ptr() = delete;
    unique_ptr(T* ptr);
    unique_ptr(const unique_ptr<T>&) = delete;
    unique_ptr(unique_ptr<T>&& ptr) noexcept;
    ~unique_ptr();

    T* get() const noexcept;
    T* release() noexcept;
    void reset(T* ptr) noexcept;

    unique_ptr<T>& operator=(unique_ptr<T>& ptr) = delete;
    unique_ptr<T>& operator=(unique_ptr<T>&& ptr) noexcept;
    T& operator*() const;
    T* operator->() const noexcept;


private:
    T* rawPtr_{nullptr};
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr) {
    rawPtr_ = ptr;
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& ptr) noexcept {
    rawPtr_ = ptr.rawPtr_;
    ptr.rawPtr_ = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (rawPtr_) {
        delete rawPtr_; 
    }
}

template <typename T>
T* unique_ptr<T>::get() const noexcept{ 
    return rawPtr_; 
}

template <typename T>
T* unique_ptr<T>::release() noexcept {
    T* tempPtr = rawPtr_;
    rawPtr_ = nullptr;
    return tempPtr;
}

template <typename T>
void unique_ptr<T>::reset(T* ptr) noexcept {
    T* oldPtr = rawPtr_;
    rawPtr_ = ptr;
    if (oldPtr) {
        delete oldPtr;  
    }
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& ptr) noexcept {
    if (this != &ptr) {
        delete rawPtr_;
        rawPtr_ = ptr.rawPtr_;
        ptr.rawPtr_ = nullptr;
    }
    return *this;
}

template <typename T>
T& unique_ptr<T>::operator*() const { 
    return *get(); 
}

template <typename T>
T* unique_ptr<T>::operator->() const noexcept {
    return get();
}

} //coders namespace
