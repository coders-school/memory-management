#pragma once

#include <atomic>
#include <functional>

class ControlBlock {
public:
    ControlBlock(std::function<void()> del) : deleter(del) {}
    void increaseSharedRef() { shared_refs += 1; }
    void decreaseSharedRef() { shared_refs -= 1; }
    void increaseWeakRef() { weak_refs += 1; }
    void decreaseWeakRef() { weak_refs -= 1; }
    std::atomic<size_t>& getShared() { return shared_refs; }
    std::atomic<size_t>& getWeak() { return weak_refs; }
    void callDeleter() { deleter(); }

private:
    std::atomic<size_t> shared_refs = 1;
    std::atomic<size_t> weak_refs = 0;
    std::function<void()> deleter;
};

template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr = nullptr, std::function<void()> del = new ControlBlock([&]() { delete ptr_; }))
        : ptr_(ptr), cb_(del) {}
    shared_ptr(const shared_ptr& ptr);
    shared_ptr(shared_ptr&& ptr);
    shared_ptr& operator=(const shared_ptr& ptr);
    shared_ptr& operator=(shared_ptr&& ptr);
    ~shared_ptr();
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

private:
    void deletePointers();
    T* ptr_;
    ControlBlock* cb_;
};

template <typename T>
void shared_ptr<T>::deletePointers() {
    cb_->decreaseSharedRef();
    if (cb_->getShared() == 0) {
        cb_->callDeleter();
        if (cb_->getWeak() == 0) {
            delete cb_;
        }
    }
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    deletePointers();
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& ptr) {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->increaseSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& ptr) {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    ptr.ptr_ = nullptr;
    ptr.cb_ = nullptr;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& ptr) {
    if (&ptr != this) {
        deletePointers();
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->increaseSharedRef();
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& ptr) {
    if (&ptr != this) {
        deletePointers();
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        ptr.ptr_ = nullptr;
        ptr.cb_ = nullptr;
    }
    return *this;
}
