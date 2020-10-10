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
    void callDeleter() const { deleter(); }
    void setDeleter(std::function<void()> del) { deleter = del; }

private:
    std::atomic<size_t> shared_refs = 1;
    std::atomic<size_t> weak_refs = 0;
    std::function<void()> deleter;
};

template <typename T>
class BlockAndData : public ControlBlock {
public:
    template <typename... Args>
    BlockAndData(Args&&... args) : object_(std::forward(args)...){};
    T getObject() const { return object_; }

private:
    T object_;
};
