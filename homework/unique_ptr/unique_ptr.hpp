#pragma once

namespace my {

template <typename T>
class unique_ptr {
public:
    unique_ptr(T* ptr)
        : ptr_(ptr) {}
    unique_ptr()
        : ptr_(nullptr) {}
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& otherPtr);

    ~unique_ptr() { delete ptr_; }

    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& otherPtr);

    T* get() const { return ptr_; }
    T* release();
    void reset(T* newPtr = nullptr);

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& otherPtr) {
    ptr_ = otherPtr.release();
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& otherPtr) {
    if (ptr_ != otherPtr.get()) {
        delete ptr_;
        ptr_ = otherPtr.release();
    }
    return *this;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
}


}  // namespace my
