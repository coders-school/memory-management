#pragma once 

#include <atomic>
#include <cstddef>
#include <functional>

template<typename T>
class ControlBlock {
public:
    ControlBlock() : sharedRef_(0), weakRef_(0) {}
    ControlBlock(const ControlBlock& ) = delete;
    ControlBlock& operator=(const ControlBlock& ) = delete;
    ~ControlBlock() = default

    void increasSharedRef() { sharedRef_ ++; };
    void increasWeakRef() {weakRef_++; };
    void decreaseSharedRef() {
        if(sharedRef_ > 0) {
            sharedRef_--;
        }
    };
    void DecreaseWeakRed() {
        if(weakRef_ > 0) {
            weakRef_--;
        }
    };

    size_t getSharedRefNumber() const [
        return sharedRef_.load();
    ];
    size_t getWeakRegNumber() const {
        return weakRef_.load();
    };

    

private:
    std::atomic<size_t> sharedRef_;
    std::atomic<size_t> weakRef_;
    std::function<void<T* ptr>> deleter_ = [](T* ptr) { delete ptr; };
};