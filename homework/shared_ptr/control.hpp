#pragma once
#include <atomic>
#include <functional>
namespace cs
{
template <typename T>
using Deleter = std::function<void(T*)>;

auto defaultDeleter = [](auto* data) { delete data; };

template <typename T>
class control_block
{
    std::atomic_size_t sharedRef_{1};
    std::atomic_size_t weakRef_{0};
    Deleter<T> deleter_{defaultDeleter};

   public:
    control_block() = default;
    control_block(Deleter<T> deleter);
    virtual ~control_block() = default;
    int getSharedRef() const noexcept;
    int getWeakRef() const noexcept;
    void incrementSharedRef() noexcept;
    void decrementSharedRef() noexcept;
    void incrementWeakRef() noexcept;
    void decrementWeakRef() noexcept;
    virtual T* getObject() noexcept;
    Deleter<T> getDeleter() noexcept;

};

template <typename T>
control_block<T>::control_block(Deleter<T> deleter)
:deleter_(deleter) {
}

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
void control_block<T>::decrementWeakRef() noexcept
{
    weakRef_--;
}

template <typename T>
T* control_block<T>::getObject() noexcept
{
    return nullptr;
}

template <typename T>
Deleter<T> control_block<T>::getDeleter() noexcept {
    return deleter_;
}

};  // namespace cs
