#pragma once

#include <atomic>
#include <functional>

template <typename T>
class ControlBlockBase {
public:
    virtual ~ControlBlockBase() = default;

    size_t getShared();
    size_t getWeak();

    void increaseWeak();
    void increaseShared();

    void decreaseWeak();
    void decreaseShared();

    virtual T* getData() = 0;

private:
    std::atomic<size_t> sharedRefs_{1};
    std::atomic<size_t> weakRefs_{0};
};

template <typename T>
class ControlBlock : public ControlBlockBase<T> {
public:
    ControlBlock(
        T* ptr = nullptr,
        std::function<void(T*)> deleter = [](T* ptrToDelete) { delete ptrToDelete; })
        : refs_(ptr), deleter_(deleter) {}

    ~ControlBlock() {
        deleter_(refs_);
    }

    T* getData() override {
        return refs_;
    }

private:
    T* refs_;
    std::function<void(T*)> deleter_;
};

template <typename T>
class ControlBlockData : public ControlBlockBase<T> {
public:
    template <typename... Args>
    ControlBlockData(Args&&... args) : data_(std::forward<Args>(args)...) {
        if (sizeof...(args) > 0) {
            isInitialized_ = true;
        }
    }
    T* getData() override {
        return &data_;
    }
    bool isInitialized() {
        return isInitialized_;
    }

private:
    T data_{};
    bool isInitialized_{};
};

template <typename T>
size_t ControlBlockBase<T>::getShared() {
    return sharedRefs_.load();
}

template <typename T>
size_t ControlBlockBase<T>::getWeak() {
    return weakRefs_.load();
}

template <typename T>
void ControlBlockBase<T>::increaseWeak() {
    ++weakRefs_;
}

template <typename T>
void ControlBlockBase<T>::increaseShared() {
    ++sharedRefs_;
}

template <typename T>
void ControlBlockBase<T>::decreaseWeak() {
    if (weakRefs_ > 0) {
        --weakRefs_;
    }
}

template <typename T>
void ControlBlockBase<T>::decreaseShared() {
    --sharedRefs_;
}
