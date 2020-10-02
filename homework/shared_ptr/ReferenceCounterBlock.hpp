#pragma once

#include <atomic>

constexpr unsigned int defaultCounterValue = 0;

class ReferenceCounterBlock {
public:
    ReferenceCounterBlock()
        : counter_(defaultCounterValue) {}
    ReferenceCounterBlock(const ReferenceCounterBlock&) = delete;
    ReferenceCounterBlock(ReferenceCounterBlock&&) = delete;
    ReferenceCounterBlock& operator=(const ReferenceCounterBlock&) = delete;
    ReferenceCounterBlock& operator=(ReferenceCounterBlock&&) = delete;
    ~ReferenceCounterBlock() {}

    unsigned int getCounter() const;
    void operator++();
    void operator--();

private:
    std::atomic<unsigned int> counter_;
};

void ReferenceCounterBlock::operator++() {
    counter_++;
}

void ReferenceCounterBlock::operator--() {
    counter_--;
}

unsigned int ReferenceCounterBlock::getCounter() const {
    return counter_.load();
}