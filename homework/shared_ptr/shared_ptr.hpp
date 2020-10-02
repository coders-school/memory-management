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
    shared_ptr(T* ptr) : ptr_(ptr), cb_(new ControlBlock([&](){ delete ptr_; })) {}
    ~shared_ptr();
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

private:
    T* ptr_;
    ControlBlock* cb_;
};

template <typename T>
shared_ptr<T>::~shared_ptr() {
    cb_->decreaseSharedRef();
    if(cb_->getShared() == 0) {
        cb_->callDeleter();
        if(cb_->getWeak() == 0) {
            delete cb_;
        }
    }
}
