#pragma once

#include <atomic>
#include <functional>

template <typename T>
class ControlBlock {
public:
    ~ControlBlock(){};

    size_t getShared();
    size_t getWeak();

    void increaseWeak();
    void increaseShared();

    void decreaseWeak();
    void decreaseShared();

    std::function<void(T*)> deleter_ = [](T* ptrToDelete) { delete ptrToDelete; };

private:
    std::atomic<size_t> sharedRefs_ = 0;
    std::atomic<size_t> weakRefs_ = 0;
};

template <typename T>
class ControlBlockPtr : public ControlBlock<T> {
public:
    ControlBlockPtr(
        T* ptr = nullptr,
        std::function<void(T*)> defDeleter = [](T* ptrToDelete) { delete ptrToDelete; })
        : ptr_(ptr), deleter_(defDeleter) {}

    ~ControlBlockPtr() {
        deleter_(ptr_);
    }

private:
    T* ptr_;
    std::function<void(T*)> deleter_;
};

template <typename T>
size_t ControlBlock<T>::getShared() {
    return sharedRefs_.load();
}

template <typename T>
size_t ControlBlock<T>::getWeak() {
    return weakRefs_.load();
}

template <typename T>
void ControlBlock<T>::increaseWeak() {
    ++weakRefs_;
}

template <typename T>
void ControlBlock<T>::increaseShared() {
    ++sharedRefs_;
}

template <typename T>
void ControlBlock<T>::decreaseWeak() {
    --weakRefs_;
}

template <typename T>
void ControlBlock<T>::decreaseShared() {
    --sharedRefs_;
}

// template <typename T>
