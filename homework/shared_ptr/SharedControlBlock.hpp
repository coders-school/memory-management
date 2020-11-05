#pragma once

#include <atomic>
#include <cstddef>
#include <functional>
#include <iostream>

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

    void callDefaultDeleter() { defaultDeleter(obj_); }

    virtual T* getObj() = 0;

private:
    std::atomic<size_t> sharedRefsCount_ = 1;
    std::atomic<size_t> weakRefsCount_ = 0;

    T* obj_ = nullptr;
    std::function<void(T*)> defaultDeleter = [](T* ptr = nullptr) { delete ptr; };
};

template <typename T>
class SharedControlBlockObj : public SharedControlBlock<T> {
public:
    SharedControlBlockObj(
        T* ptr = nullptr,
        std::function<void(T*)> deleter = [](T* ptr) { delete ptr; })
        : obj_(ptr), defaultDeleter(deleter) {}

    ~SharedControlBlockObj() { defaultDeleter(obj_); }

    void callDefaultDeleter() {
        defaultDeleter(obj_);
    }
    T* getObj() override { return obj_; };

private:
    T* obj_ = nullptr;
    std::function<void(T*)> defaultDeleter = [](T* ptr = nullptr) { delete ptr; };
};

template <typename T>
class SharedControlBlockData : public SharedControlBlock<T> {
public:
    template <typename... Args>
    SharedControlBlockData(Args... args)
        : object_(args...) {}

    T* getObj() override { return &object_; }

private:
    T object_;
};
