#pragma once

#include <atomic>

template <typename T>
class control_block {
public:
    control_block();
    void incrementRefs() { sharedRefs_++; }
    void decrementRefs() { sharedRefs_--; }

    //void sharedDeleter(T*) { delete T; }
private:
    std::atomic<size_t> sharedRefs_;
};