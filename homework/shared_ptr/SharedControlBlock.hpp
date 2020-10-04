#pragma once

#include <atomic>
#include <cstddef>
#include <functional>

template <typename T>
class SharedControlBlock {
public:
    SharedControlBlock(std::function<void(T*)> deleter = [](T* ptr) { delete ptr; })
        : defaultDeleter(deleter) {}

    size_t getSharedRefsCount() const { return sharedRefsCount_.load(); }
    void incrementSharedRefsCount() { ++sharedRefsCount_; }
    void decrementSharedRefsCount() { --sharedRefsCount_; }

    size_t getWeakRefsCount() const { return weakRefsCount_.load(); }
    void incrementWeakRefsCount() { ++weakRefsCount_; }
    void decrementWeakRefsCount() { --weakRefsCount_; }

    std::function<void(T*)> defaultDeleter;

private:
    std::atomic<size_t> sharedRefsCount_ = 1;
    std::atomic<size_t> weakRefsCount_ = 0;
};
