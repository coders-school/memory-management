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

    ControlBlock& operator++();
    ControlBlock& operator--();

private:
    std::atomic<size_t> sharedRefs_;
    std::atomic<size_t> weakRefs_;
};

size_t ControlBlock::getShared() {
    return sharedRefs_;
}

size_t ControlBlock::getWeak() {
    return weakRefs_;
}

ControlBlock& ControlBlock::operator--() {
    --sharedRefs_;
    return *this;
}

ControlBlock& ControlBlock::operator++() {
    ++sharedRefs_;
    return *this;
}
