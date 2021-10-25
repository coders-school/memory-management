#pragma once 

#include <atomic>
#include <cstddef>

class controlBlock {
public:


private:
    std::atomic<int> sharedRef{1};
    std::atomic<int> weakRed{0};
};