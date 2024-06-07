#ifndef MY_SHARED_PTR_HPP
#define MY_SHARED_PTR_HPP

#include <atomic>
#include <functional>

namespace my {

template <typename T>
class shared_ptr {
public:
    // Constructor
    explicit shared_ptr(T* ptr = nullptr) : ptr_(ptr), control_block_(nullptr) {
        if (ptr) {
            control_block_ = new control_block();
            control_block_->shared_refs.store(1);
            control_block_->weak_refs.store(0);
            control_block_->deleter = [](T* ptr) { delete ptr; };
        }
    }

    // Copy constructor
    shared_ptr(const shared_ptr& other) : ptr_(other.ptr_), control_block_(other.control_block_) {
        if (control_block_) {
            control_block_->shared_refs.fetch_add(1);
        }
    }

    // Move constructor
    shared_ptr(shared_ptr&& other) noexcept : ptr_(other.ptr_), control_block_(other.control_block_) {
        other.ptr_ = nullptr;
        other.control_block_ = nullptr;
    }

    // Destructor
    ~shared_ptr() {
        release();
    }

    // Copy assignment operator
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            control_block_ = other.control_block_;
            if (control_block_) {
                control_block_->shared_refs.fetch_add(1);
            }
        }
        return *this;
    }

    // Move assignment operator
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            control_block_ = other.control_block_;
            other.ptr_ = nullptr;
            other.control_block_ = nullptr;
        }
        return *this;
    }

    // Dereference operator
    T& operator*() const {
        return *ptr_;
    }

    // Member access operator
    T* operator->() const {
        return ptr_;
    }

    // Get raw pointer
    T* get() const {
        return ptr_;
    }

    // Reset pointer
    void reset(T* ptr = nullptr) {
        release();
        if (ptr) {
            ptr_ = ptr;
            control_block_ = new control_block();
            control_block_->shared_refs.store(1);
            control_block_->weak_refs.store(0);
            control_block_->deleter = [](T* ptr) { delete ptr; };
        }
    }

    // Get use count
    size_t use_count() const {
        return control_block_ ? control_block_->shared_refs.load() : 0;
    }

    // Conversion to bool
    operator bool() const {
        return ptr_ != nullptr;
    }

private:
    struct control_block {
        std::atomic<size_t> shared_refs;
        std::atomic<size_t> weak_refs;
        std::function<void(T*)> deleter;
    };

    void release() {
        if (control_block_) {
            if (control_block_->shared_refs.fetch_sub(1) == 1) {
                control_block_->deleter(ptr_);
                if (control_block_->weak_refs.load() == 0) {
                    delete control_block_;
                }
            }
        }
    }

    T* ptr_;
    control_block* control_block_;
};

} // namespace my

#endif // MY_SHARED_PTR_HPP