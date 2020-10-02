#pragma once

#include <atomic>

class ReferenceCounterBlock {
public:
    unsigned int getCounter() const;
    void operator++();
    void operator--();

private:
    std::atomic<unsigned int> counter_{};
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