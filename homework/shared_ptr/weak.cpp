#include "shared.cpp"

namespace cs {

template <typename T>
class weak_ptr {
    control_block* controlBlock_{nullptr};
    T* data_;

    public:
    weak_ptr() noexcept = default;
    weak_ptr(const cs::shared_ptr<T>&) noexcept;
    weak_ptr(const weak_ptr<T>&) noexcept;
    weak_ptr(weak_ptr<T>&&) noexcept;

};

template<typename T>
weak_ptr<T>::weak_ptr(const cs::shared_ptr<T>& rhs) noexcept
: data_(rhs.data_), controlBlock_(rhs.controlBlock_) {
    controlBlock_->incrementWeakRef();
}

template<typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T>& rhs) noexcept 
: data_(rhs.data_)
{
    controlBlock_->decrementWeakRef();
    controlBlock_ = rhs.controlBlock_;
    controlBlock_->incrementWeakRef();
}


};
