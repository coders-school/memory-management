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
    //void callDeleter() { deleter_(); }
    void setDeleter(std::function<void()> del) { deleter_ = del; }
    virtual T* getObject() = 0;

protected:
    std::atomic<size_t> sharedRefCounter_ = 1;
    std::atomic<size_t> weakRefCounter_ = 0;
    std::function<void(T*)> deleter_ = [](T* ptr) { delete ptr; };
};

template <typename T>
class ControlBlockData : public ControlBlock<T> {
public:
    ControlBlockData(
        T* ptr = nullptr,
        std::function<void(T*)> deleter = [](T* ptr) { delete ptr; })
        : object_(ptr), deleter_(deleter) {}

    ~ControlBlockData() { deleter_(object_); }
    void callDeleter() { deleter_(object_); }

    T* getObject() override { return object_; }

private:
    T* object_ = nullptr;
    std::function<void(T*)> deleter_ = [](T* ptr) { delete ptr; };
};
