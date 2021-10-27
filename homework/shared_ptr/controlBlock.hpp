#pragma once

#include <atomic>
#include <cstddef>
#include <functional>

template <typename T>
using Deleter = std::function<void(T *ptr)>;

auto defaultDeleter = [](auto* ptr) { delete ptr; };

template <typename T>
class ControlBlock
{
public:
    ControlBlock() = default;
    ControlBlock(Deleter<T> deleter);
    // ControlBlock& operator=(const ControlBlock& ) = delete;
    ~ControlBlock() = default;

    void increasSharedRef();
    void increasWeakRef();

    void decreaseSharedRef();
    void decreaseWeakRef();

    size_t getSharedRef() const noexcept;
    size_t getWeakRef() const noexcept;

    Deleter<T> getDeleter() noexcept;

private:
    std::atomic<size_t> sharedRef_{1};
    std::atomic<size_t> weakRef_{0};
    Deleter<T> deleter_{defaultDeleter};
};

template<typename T>
ControlBlock<T>::ControlBlock(Deleter<T> deleter) : deleter_(deleter) {};

template <typename T>
size_t ControlBlock<T>::getSharedRef() const noexcept
{
    return sharedRef_.load();
}
template <typename T>
size_t ControlBlock<T>::getWeakRef() const noexcept
{
    return weakRef_.load();
}
template <typename T>
Deleter<T> ControlBlock<T>::getDeleter() noexcept {
    return deleter_;
} 

template <typename T>
void ControlBlock<T>::decreaseWeakRef()
{
    if (weakRef_ > 0)
    {
        weakRef_--;
    }
};
template <typename T>
void ControlBlock<T>::decreaseSharedRef()
{
    if (sharedRef_ > 0)
    {
        sharedRef_--;
    }
};

template <typename T>
void ControlBlock<T>::increasSharedRef()
{
    sharedRef_++;
};

template <typename T>
void ControlBlock<T>::increasWeakRef()
{
    weakRef_++;
};
