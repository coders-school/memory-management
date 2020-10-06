#pragma once

#include <atomic>
#include <cstddef>

class ControlBlock {
public:
    ControlBlock()
        : sharedRefs_(0), weakRefs_(0){};
    ControlBlock(const ControlBlock&) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;
    ~ControlBlock(){};

    size_t getShared();
    size_t getWeak();

    void increaseWeak();

    ControlBlock& operator++();
    ControlBlock& operator--();
    //   ControlBlock operator++(int);
    //   ControlBlock operator--(int);

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

void ControlBlock::increaseWeak() {
    weakRefs_ += 1;
}

ControlBlock& ControlBlock::operator--() {
    --sharedRefs_;
    return *this;
}

ControlBlock& ControlBlock::operator++() {
    ++sharedRefs_;
    return *this;
}
/*
ControlBlock ControlBlock::operator--(int) {
    ControlBlock Temp;
    Temp.weakRefs_ = (weakRefs_)--;
    return *this;
}

ControlBlock ControlBlock::operator++(int) {
    ControlBlock Temp;
    Temp.weakRefs_ = (weakRefs_)++;
    return Temp;
}
*/
