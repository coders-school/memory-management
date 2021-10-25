#pragma once 

#include <atomic>
#include <cstddef>

class ControlBlock {
public:
    ControlBlock() : sharedRef_(0), weakRef_(0) {}
    ControlBlock(const ControlBlock& ) = delete;
    ControlBlock& operator=(const ControlBlock& ) = delete;

private:
    std::atomic<int> sharedRef_;
    std::atomic<int> weakRef_;
};