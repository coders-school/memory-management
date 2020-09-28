#pragma once

#include <atomic>

class control_block {
public:
    control_block()
        : sharedRefs_(0) {}
    control_block(const control_block&) = delete; 
    control_block& operator=(const control_block&) = delete;
    ~control_block() {}

    void incrementRefs() { sharedRefs_++; }
    void decrementRefs() { sharedRefs_--; }
    size_t getRefs() { return sharedRefs_; }
    //void sharedDeleter() { sharedRefs_ = 0; }

private:
    std::atomic<size_t> sharedRefs_;
};