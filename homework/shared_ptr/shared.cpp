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
    shared_ptr(shared_ptr&&);
    ~shared_ptr();

    shared_ptr& operator=(shared_ptr&&) = default;
    shared_ptr& operator=(const shared_ptr&) noexcept;

    T* get() const noexcept { return data_; }
    T& operator*() noexcept { return *data_; }
    T* operator->() noexcept { return data_; }
    operator bool() const noexcept { return data_ != nullptr; }
    int use_count() const noexcept { return controlBlock->getSharedRef(); }
    void reset(T* data = nullptr) noexcept { data_ = data; }

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
shared_ptr<T>::shared_ptr(shared_ptr&& temp) : data_(temp.data_), controlBlock(temp.controlBlock)
{
    temp.data_ = nullptr;
    temp.controlBlock = nullptr;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    data_ = rhs.data_;
    controlBlock = rhs.controlBlock;
    if (controlBlock) {
        controlBlock->incrementSharedRef();
    }
    return *this;
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
