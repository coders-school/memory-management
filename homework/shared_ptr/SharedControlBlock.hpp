#pragma once

#include <atomic>
#include <cstddef>
#include <functional>

template <typename T>
class SharedControlBlock {
public:
    virtual ~SharedControlBlock() = default;

    size_t getSharedRefsCount() const { return sharedRefsCount_.load(); }
    void incrementSharedRefsCount() { ++sharedRefsCount_; }
    void decrementSharedRefsCount() { --sharedRefsCount_; }

    size_t getWeakRefsCount() const { return weakRefsCount_.load(); }
    void incrementWeakRefsCount() { ++weakRefsCount_; }
    void decrementWeakRefsCount() { --weakRefsCount_; }

    std::function<void(T*)> defaultDeleter = [](T* ptr = nullptr) { delete ptr; };

    virtual T* getObj() = 0;

private:
    std::atomic<size_t> sharedRefsCount_ = 1;
    std::atomic<size_t> weakRefsCount_ = 0;
};

template <typename T>
class SharedControlBlockObj : public SharedControlBlock<T> {
public:
    SharedControlBlockObj(
        T* ptr = nullptr,
        std::function<void(T*)> deleter = [](T* ptr) { delete ptr; })
        : obj_(ptr), defaultDeleter(deleter) {}

    ~SharedControlBlockObj() { callDefaultDeleter(); }

    void callDefaultDeleter() { defaultDeleter(obj_); }
    T* getObj() override { return obj_; };

private:
    T* obj_ = nullptr;
    std::function<void(T*)> defaultDeleter = [](T* ptr = nullptr) { delete ptr; };
};
