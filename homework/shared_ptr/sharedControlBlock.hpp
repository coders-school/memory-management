#pragma once

#include <atomic>

constexpr uint8_t defaultCounterValue = 0;

class SharedControlBlock {
public:
    SharedControlBlock();
    SharedControlBlock(const SharedControlBlock&) = delete;
    SharedControlBlock(SharedControlBlock&&) = delete;
    ~SharedControlBlock(){};

    unsigned int get() const;

    SharedControlBlock& operator=(const SharedControlBlock&) = delete;
    SharedControlBlock& operator=(SharedControlBlock&&) = delete;
    void operator++();
    void operator--();
    void reset();

private:
    std::atomic<unsigned int> counter_{};
};

SharedControlBlock::SharedControlBlock()
    : counter_(defaultCounterValue) {}

unsigned int SharedControlBlock::get() const {
    return counter_.load();
}

void SharedControlBlock::operator++() {
    counter_++;
}

void SharedControlBlock::operator--() {
    counter_--;
}

void SharedControlBlock::reset() {
    counter_ = defaultCounterValue;
}