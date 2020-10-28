#pragma once

#include <atomic>
#include <cstddef>
#include <functional>

namespace coders {

template <typename T>
using Deleter = std::function<void(T*)>;

auto defaultDeleter = [](auto* ptr) { delete ptr; };

template <typename T>
class control_block {
public:
    control_block(Deleter<T> deleter = defaultDeleter)
        : deleter_(deleter) {}
    control_block(const control_block&) = delete;
    control_block(control_block&&) = delete;
    control_block& operator=(const control_block&) = delete;
    control_block& operator=(control_block&&) = delete;

    size_t getSharedRefs() const noexcept { return sharedRefs_; }
    size_t getWeakRefs() const noexcept { return weakRefs_; }
    Deleter<T> getDeleter() const noexcept { return deleter_; }

    void incrementSharedRefs() noexcept { sharedRefs_++; }
    void decrementSharedRefs() noexcept { sharedRefs_--; }
    void incrementWeakRefs() noexcept { weakRefs_++; }
    void decrementWeakRefs() noexcept { weakRefs_--; }

private:
    std::atomic_size_t sharedRefs_{0};
    std::atomic_size_t weakRefs_{0};
    std::function<void(T*)> deleter_{defaultDeleter};
};

}  // namespace coders
