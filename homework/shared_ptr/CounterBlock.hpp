#pragma once

#include <atomic>

constexpr unsigned int defaultCounterValue = 0;

class CounterBlock {
public:
    CounterBlock()
        : counter_(defaultCounterValue) {}
    CounterBlock(const CounterBlock&) = delete;
    CounterBlock(CounterBlock&&) = delete;
    CounterBlock& operator=(const CounterBlock&) = delete;
    CounterBlock& operator=(CounterBlock&&) = delete;
    ~CounterBlock() {}

    unsigned int getCounter() const noexcept;
    void resetCounter();
    void incrementCounter() noexcept;
    void decrementCounter() noexcept;

private:
    std::atomic<unsigned int> counter_;
};

void CounterBlock::incrementCounter() noexcept {
    counter_++;
}
void CounterBlock::decrementCounter() noexcept {
    counter_--;
}

unsigned int CounterBlock::getCounter() const noexcept {
    return counter_.load();
}

void CounterBlock::resetCounter() {
    counter_ = defaultCounterValue;
}