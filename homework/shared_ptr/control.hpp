#pragma once
#include <atomic>

namespace cs {
template <typename T>
class control_block
{
    std::atomic_size_t sharedRef_{1};
    std::atomic_size_t weakRef_{0};

   public:
    control_block() = default;
    int getSharedRef() const noexcept;
    int getWeakRef() const noexcept;
    void incrementSharedRef() noexcept;
    void decrementSharedRef() noexcept;
    void incrementWeakRef() noexcept;
    void decrementWeakRef() noexcept;
    virtual T* getObject() noexcept;
};

template <typename T>
int control_block<T>::getSharedRef() const noexcept
{
    return sharedRef_;
}
template <typename T>
int control_block<T>::getWeakRef() const noexcept
{
    return weakRef_;
}
template <typename T>
void control_block<T>::incrementSharedRef() noexcept
{
    sharedRef_++;
}
template <typename T>
void control_block<T>::decrementSharedRef() noexcept
{
    sharedRef_--;
}
template <typename T>
void control_block<T>::incrementWeakRef() noexcept
{
    weakRef_++;
}

template <typename T>
void control_block<T>::decrementWeakRef() noexcept {
    weakRef_--;
}

template <typename T>
T* control_block<T>::getObject() noexcept {
    return nullptr;
}


};
