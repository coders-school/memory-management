#pragma once

template<typename T>
class unique_ptr {
public:
    unique_ptr(T* pointer = nullptr) : pointer_(pointer) {}
    unique_ptr(unique_ptr& ptr) = delete;
    unique_ptr(unique_ptr&& ptr);
    unique_ptr& operator=(const unique_ptr& ptr) = delete;
    unique_ptr& operator=(unique_ptr&& ptr);
    ~unique_ptr();
    T& operator*() const { return *pointer_; }
    T* operator->() const { return pointer_; }
    T* get() const { return pointer_; }
    T* release();
    void reset(T* new_ptr = nullptr);
private:
    T* pointer_;
};

template<typename T>
unique_ptr<T>::~unique_ptr() {
    delete pointer_;
}

template<typename T>
T* unique_ptr<T>::release() {
    T* temp = pointer_;
    pointer_ = nullptr;
    return temp;
}

template<typename T>
void unique_ptr<T>::reset(T* new_ptr) {
    delete pointer_;
    pointer_ = new_ptr;
}

template<typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& ptr) {
    if(this != &ptr) {
        delete pointer_;
        pointer_ = ptr.pointer_;
        ptr.pointer_ = nullptr;
    }
    return *this;
}

template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& ptr) : pointer_(ptr.pointer_) {
    ptr.pointer_ = nullptr;
}
