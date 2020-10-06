#pragma once

#include <atomic>

template <typename T>
class control_block {
public:
    control_block()
        : sharedRefs_(0), weakRefs_(0) {}
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
    //void sharedDeleter() { sharedRefs_ = 0; }

private:
    std::atomic<size_t> sharedRefs_;
    std::atomic<size_t> weakRefs_;

};

template <typename T>
class continuous_block : public control_block<T> {
public: 
    
    template<typename ...Args>
    continuous_block(Args&& ...args) : object_{args...} {
    }

    T* getObjectPointer() override{
        return &object_;
    }
private:
    T object_;
};

template <typename T>
class normal_block : public control_block<T> {
public:
    normal_block(T* ptr = nullptr) {
        object_ = ptr;
    }
    T* getObjectPointer() override {
        return object_;
    }
    

private:
    T* object_{nullptr};
};