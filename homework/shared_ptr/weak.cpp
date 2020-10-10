#include "shared.cpp"

namespace cs
{
template <typename T>
class weak_ptr
{
    control_block* controlBlock_{nullptr};
    T* data_{nullptr};

    void releaseMemory() noexcept;

   public:
    weak_ptr() noexcept = default;
    weak_ptr(const cs::shared_ptr<T>&) noexcept;
    weak_ptr(const weak_ptr<T>&) noexcept;
    weak_ptr(weak_ptr<T>&&) noexcept;
    ~weak_ptr() noexcept;

    bool expired() const noexcept;
    int use_count() const noexcept;
};

template <typename T>
weak_ptr<T>::weak_ptr(const cs::shared_ptr<T>& rhs) noexcept : data_(rhs.data_), controlBlock_(rhs.controlBlock_)
{
    controlBlock_->incrementWeakRef();
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T>& rhs) noexcept : data_(rhs.data_)
{
    releaseMemory();
    controlBlock_ = rhs.controlBlock_;
    controlBlock_->incrementWeakRef();
}

template <typename T>
bool weak_ptr<T>::expired() const noexcept
{
    return controlBlock_->getSharedRef() == 0;
}

template <typename T>
weak_ptr<T>::~weak_ptr() noexcept
{
    releaseMemory();
}

template <typename T>
void weak_ptr<T>::releaseMemory() noexcept
{
    if (controlBlock_) {
        controlBlock_->decrementWeakRef();
        if (controlBlock_->getSharedRef() == 0 && controlBlock_->getWeakRef() == 0) {
            delete controlBlock_;
            controlBlock_ = nullptr;
        }
    }
}

template <typename T>
int weak_ptr<T>::use_count() const noexcept {
    if (controlBlock_) {
        return controlBlock_->getSharedRef();
    }
    return 0;
}
};  // namespace cs
