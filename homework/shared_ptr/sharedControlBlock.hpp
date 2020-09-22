#pragma once

#include <atomic>
#include <functional>

template <typename T>
class SharedControlBlock {
public:
    virtual ~SharedControlBlock() = default;

    void incrementSharedRefs() { ++sharedRefs_; }
    void decrementSharedRefs() { --sharedRefs_; }
    size_t getSharedRefs() const { return sharedRefs_.load(); }

    void incrementWeakRefs() { ++weakRefs_; }
    void decrementWeakRefs() { --weakRefs_; }
    size_t getWeakRefs() const { return weakRefs_.load(); }

    virtual T* getPtr() = 0;

    std::function<void(T*)> deleter;

protected:
    std::atomic<size_t> sharedRefs_ = 1;
    std::atomic<size_t> weakRefs_ = 0;
};

template <typename T>
class SharedControlBlockPtr : public SharedControlBlock<T> {
public:
    SharedControlBlockPtr(
        T* ptr = nullptr,
        std::function<void(T*)> defDeleter = [](T* ptrToDelete) { delete ptrToDelete; })
        : object_(ptr), deleter(defDeleter) {}

    ~SharedControlBlockPtr() { deleter(object_); }

    T* getPtr() override { return object_; }

private:
    T* object_;

    std::function<void(T*)> deleter;
};

template <typename T>
class SharedControlBlockObj : public SharedControlBlock<T> {
public:
    template <typename... Args>
    SharedControlBlockObj(Args... args)
        : object_(args...) {}
    T* getPtr() override { return &object_; }

private:
    T object_;
};
