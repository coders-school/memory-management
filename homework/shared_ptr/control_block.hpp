#pragma once

#include <atomic>
#include <functional>
#include <iostream>

template <typename T>
class control_block {
public:
    control_block(std::function<void(T*)> deleter = [](T* ptr) { delete ptr;} )
        : sharedRefs_(0), weakRefs_(0), deleter_(deleter) {};
    control_block(const control_block&) = delete; 
    control_block& operator=(const control_block&) = delete;
    virtual ~control_block() {
        sharedRefs_ = 0;
        weakRefs_ = 0;
    }

    control_block& operator--() {
        --sharedRefs_;
        return *this;
    };

    void increaseWeakRefs() {
        ++weakRefs_;
    };

    void decreaseWeakRefs() {
        --weakRefs_;
    };

    control_block& operator++() {
        ++sharedRefs_;
        return *this;
    };
    size_t getRefs() { return sharedRefs_; }
    size_t getWeakRefs() { return weakRefs_; }
    virtual T* getObjectPointer() {return nullptr;};

    std::function<void(T*)> deleter_;
    bool expired() const noexcept { return sharedRefs_ == 0; }

private:
    std::atomic<size_t> sharedRefs_ {};
    std::atomic<size_t> weakRefs_{};
};

template <typename T>
class continuous_block : public control_block<T> {
public: 
    
    template<typename ...Args>
    continuous_block(Args&& ...args) : object_{std::forward<Args>(args)...}, control_block<T>([](T* ptr) {}) {
    }

    T* getObjectPointer() override{
        return &object_;
    }
    ~continuous_block() {
    }

private:
    T object_;
};

