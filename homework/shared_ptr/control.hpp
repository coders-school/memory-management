#pragma once
#include <atomic>
#include <functional>
namespace cs
{
template <typename ObjectType>
using Deleter = std::function<void(ObjectType*)>;

auto defaultDeleter = [](auto* data) { delete data; };

template <typename ObjectType>
class control_block
{
    std::atomic_size_t sharedRef_{1};
    std::atomic_size_t weakRef_{0};
    Deleter<ObjectType> deleter_{defaultDeleter};

   public:
    control_block() = default;
    control_block(Deleter<ObjectType> deleter);
    virtual ~control_block() = default;
    int getSharedRef() const noexcept;
    int getWeakRef() const noexcept;
    void incrementSharedRef() noexcept;
    void decrementSharedRef() noexcept;
    void incrementWeakRef() noexcept;
    void decrementWeakRef() noexcept;
    virtual ObjectType* getObject() noexcept;
    Deleter<ObjectType> getDeleter() noexcept;

};

template <typename ObjectType>
control_block<ObjectType>::control_block(Deleter<ObjectType> deleter)
:deleter_(deleter) {
}

template <typename ObjectType>
int control_block<ObjectType>::getSharedRef() const noexcept
{
    return sharedRef_;
}
template <typename ObjectType>
int control_block<ObjectType>::getWeakRef() const noexcept
{
    return weakRef_;
}
template <typename ObjectType>
void control_block<ObjectType>::incrementSharedRef() noexcept
{
    sharedRef_++;
}
template <typename ObjectType>
void control_block<ObjectType>::decrementSharedRef() noexcept
{
    sharedRef_--;
}
template <typename ObjectType>
void control_block<ObjectType>::incrementWeakRef() noexcept
{
    weakRef_++;
}

template <typename ObjectType>
void control_block<ObjectType>::decrementWeakRef() noexcept
{
    weakRef_--;
}

template <typename ObjectType>
ObjectType* control_block<ObjectType>::getObject() noexcept
{
    return nullptr;
}

template <typename ObjectType>
Deleter<ObjectType> control_block<ObjectType>::getDeleter() noexcept {
    return deleter_;
}

};  // namespace cs
