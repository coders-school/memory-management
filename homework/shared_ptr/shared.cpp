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

   public:
    shared_ptr() = default;
    shared_ptr(T* data);
    shared_ptr(const shared_ptr&);
    ~shared_ptr();

    T* get() const noexcept { return data_; }
    int use_count() const noexcept { return controlBlock->getSharedRef(); }
};

template <typename T>
shared_ptr<T>::shared_ptr(T* data) : data_(data)
{
    controlBlock = new control_block();
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& rhs) : data_(rhs.data_), controlBlock(rhs.controlBlock)
{
    controlBlock->incrementSharedRef();
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
    if (controlBlock) {
        controlBlock->decrementSharedRef();
        if (controlBlock->getSharedRef() == 0) {
            delete data_;
        }
    }
}
};  // namespace cs
