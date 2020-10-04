#pragma once

#include <atomic>
#include <cstddef>

template <typename T>
class control_block {
public:
    control_block() {}
    control_block(const control_block&) = delete; 
    control_block& operator=(const control_block&) = delete;
    ~control_block() = default;

    size_t getSharedRefs() const { return sharedRefs_; }
    size_t getWeakRefs() const { return weakRefs_; }

    void incrementSharedRefs() { sharedRefs_++; }
    void decrementSharedRefs() { sharedRefs_--; }
    void incrementWeakRefs() { weakRefs_++; }
    void decrementWeakRefs() { weakRefs_--; }



    void (*deleter_)(void*) {nullptr};
private:
    T* rawPtrInCtrlBlock_{nullptr};
    std::atomic_size_t sharedRefs_{0};
    std::atomic_size_t weakRefs_{0};
};
