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

    void increasSharedRef();
    void increasWeakRef();
    void decreaseSharedRef();
    void DecreaseWeakRed();

    

private:
    std::atomic<size_t> sharedRef_;
    std::atomic<size_t> weakRef_;
    std::function<void<T* ptr>> deleter_ = [](T* ptr) { delete ptr; };
};