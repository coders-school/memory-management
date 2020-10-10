#include <atomic>

namespace cs
{
class control_block
{
    std::atomic_size_t sharedRef_{1};
    std::atomic_size_t weakRef_{0};

   public:
    control_block() = default;
    int getSharedRef() const noexcept { return sharedRef_; }
    int getWeakRef() const noexcept { return weakRef_; }
    void incrementSharedRef() noexcept { sharedRef_++; }
    void decrementSharedRef() noexcept { sharedRef_--; }
    void incrementWeakRef() noexcept { weakRef_++; }
};

template <typename T>
class shared_ptr
{
    T* data_{nullptr};
    control_block* controlBlock{nullptr};

    void releaseMemory() noexcept;

   public:
    shared_ptr() noexcept = default;
    shared_ptr(T* data) noexcept;
    shared_ptr(const shared_ptr&) noexcept;
    shared_ptr(shared_ptr&&) noexcept;
    ~shared_ptr() noexcept;

    shared_ptr& operator=(shared_ptr&&) noexcept;
    shared_ptr& operator=(const shared_ptr&) noexcept;

    T* get() const noexcept { return data_; }
    T& operator*() noexcept { return *data_; }
    T* operator->() noexcept { return data_; }
    operator bool() const noexcept { return data_ != nullptr; }
    int use_count() const noexcept;
    void reset(T* data = nullptr) noexcept;
};

template <typename T>
shared_ptr<T>::shared_ptr(T* data) noexcept : data_(data)
{
    controlBlock = new control_block();
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& rhs) noexcept : data_(rhs.data_), controlBlock(rhs.controlBlock)
{
    controlBlock->incrementSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& rhs) noexcept : data_(rhs.data_), controlBlock(rhs.controlBlock)
{
    rhs.data_ = nullptr;
    rhs.controlBlock = nullptr;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    releaseMemory();
    data_ = rhs.data_;
    controlBlock = rhs.controlBlock;
    if (controlBlock) {
        controlBlock->incrementSharedRef();
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    releaseMemory();
    data_ = rhs.data_;
    controlBlock = rhs.controlBlock;
    rhs.data_ = nullptr;
    rhs.controlBlock = nullptr;
    return *this;
}

template <typename T>
shared_ptr<T>::~shared_ptr() noexcept
{
    releaseMemory();
}

template <typename T>
void shared_ptr<T>::releaseMemory() noexcept
{
    if (controlBlock) {
        controlBlock->decrementSharedRef();
        if (controlBlock->getSharedRef() == 0) {
            delete data_;
            delete controlBlock;
        }
    }
}

template <typename T>
void shared_ptr<T>::reset(T* data) noexcept
{
    releaseMemory();
    data_ = data;
    controlBlock = new control_block();
}

template <typename T>
int shared_ptr<T>::use_count() const noexcept
{
    if (controlBlock) {
        return controlBlock->getSharedRef();
    }
    return 0;
}
};  // namespace cs
