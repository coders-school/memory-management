#pragma once

#include <atomic>
#include <cstddef>

class ControlBlock {
public:
    ControlBlock() : sharedRefs_(0), weakRefs_(0){};
    ControlBlock(const ControlBlock&) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;
    ~ControlBlock(){};

    size_t getShared();
    size_t getWeak();

    void increaseWeak();
    void increaseShared();

    void decreaseWeak();
    void decreaseShared();

private:
    std::atomic<size_t> sharedRefs_;
    std::atomic<size_t> weakRefs_;
};

size_t ControlBlock::getShared() {
    return sharedRefs_.load();
}

size_t ControlBlock::getWeak() {
    return weakRefs_.load();
}

void ControlBlock::increaseWeak() {
    ++weakRefs_;
}

void ControlBlock::increaseShared() {
    ++sharedRefs_;
}

void ControlBlock::decreaseWeak() {
    --weakRefs_;
}

void ControlBlock::decreaseShared() {
    --sharedRefs_;
}
