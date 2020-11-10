#pragma once

#include <atomic>
#include <functional>

template <typename T>
class ControlBlock {
public:
    ControlBlock() = default;
    void increaseSharedRef() { shared_refs += 1; }
    void decreaseSharedRef() { shared_refs -= 1; }
    void increaseWeakRef() { weak_refs += 1; }
    void decreaseWeakRef() { weak_refs -= 1; }
    std::atomic<size_t>& getShared() { return shared_refs; }
    std::atomic<size_t>& getWeak() { return weak_refs; }
    std::function<void(T*)>& getDeleter() { return deleter; }
    virtual ~ControlBlock() = default;

private:
    std::atomic<size_t> shared_refs = 1;
    std::atomic<size_t> weak_refs = 0;
    std::function<void(T*)> deleter = [](T* ptr) { delete ptr; };
};

template <typename T>
class BlockAndData : public ControlBlock<T> {
public:
    template <typename... Args>
    BlockAndData<T>(Args... args) : object_(args...), ControlBlock<T>() {}
    const T& getObject() const { return object_; }

private:
    T object_;
};
