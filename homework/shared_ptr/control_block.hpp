#pragma once

#include <atomic>

class control_block {
public:
    control_block()
        : sharedRefs_(0), weakRefs_(0) {}
    control_block(const control_block&) = delete; 
    control_block& operator=(const control_block&) = delete;
    ~control_block() {
        sharedRefs_ = 0;
        weakRefs_ = 0;
    }

    control_block& operator--() {
        --sharedRefs_;
        return *this;
    };

    void increaseWeakRefs() {
        ++weakRefs_;
    };

    void decreaseWeakRefs() {
        --weakRefs_;
    };

    control_block& operator++() {
        ++sharedRefs_;
        return *this;
    };
    size_t getRefs() { return sharedRefs_; }
    size_t getWeakRefs() { return weakRefs_; }
    //void sharedDeleter() { sharedRefs_ = 0; }

private:
    std::atomic<size_t> sharedRefs_;
    std::atomic<size_t> weakRefs_;
};