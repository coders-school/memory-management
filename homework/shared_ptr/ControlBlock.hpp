#pragma once

#include <atomic>
#include <functional>

template <typename T>
class ControlBlock {
public:
    virtual ~ControlBlock() = default;
    void incrementSharedRefCounter() { sharedRefCounter_++; }
    void decrementSharedRefCounter() { sharedRefCounter_--; }
    void increaseWeakRefCounter() { weakRefCounter_++; }
    void decreaseWeakRefCounter() { weakRefCounter_--; }
    size_t getSharedCounter() { return sharedRefCounter_.load(); }
    size_t getWeakCounter() { return weakRefCounter_.load(); }
    void setDeleter(std::function<void(T*)> del) { deleter_ = del; }
    virtual T* getObject() = 0;

protected:
    std::atomic<size_t> sharedRefCounter_ = 0;
    std::atomic<size_t> weakRefCounter_ = 0;
    std::function<void(T*)> deleter_ = [](T* ptr) { delete ptr; };
};

template <typename T>
class ControlBlockPtrData : public ControlBlock<T> {
public:
    ControlBlockPtrData(
        T* ptr = nullptr,
        std::function<void(T*)> deleter = [](T* ptr) { delete ptr; })
        : object_(ptr) {
        this->setDeleter(deleter);
        if (ptr) {
            this->sharedRefCounter_ = 1;
        }
    }

    ~ControlBlockPtrData() { callDeleter(); }
    void callDeleter() { this->deleter_(object_); }

    T* getObject() override { return object_; }

protected:
    T* object_ = nullptr;
};

template <typename T>
class ControlBlockObjData : public ControlBlock<T> {
public:
    template <typename... Args>
    ControlBlockObjData(Args... args)
        : object_(args...) {}
    T* getObject() override { return &object_; }

private:
    T object_;
};
