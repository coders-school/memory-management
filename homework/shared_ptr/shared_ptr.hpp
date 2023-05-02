#include <iostream>

/*
shared_ptr
(50 XP) Implement your own shared_ptr (simplified).

shared_ptr is a RAII class:

V   Holds a pointer to managed object (template class)
V   Holds a pointer to shared control block with 2 counters and a deleter:
V   shared_refs count (as std::atomic<size_t>)
V   weak_refs count (as std::atomic<size_t>)
V   deleter (function pointer)
V   Constructor copies a pointer and allocate the control block
V   Destructor decrease shared_refs and:
V   if shared_refs == 0 -> release the managed object
V   if shared_refs == 0 and weak_refs == 0 -> release the control block
V   Copying is allowed - it increments shared_refs
Moving is allowed and it means:
Copying original pointers to a new object
Setting source pointer to nullptr
Member functions: operator*(), operator->(), get(), reset(), use_count(), operator bool()
Should be implemented in shared_ptr.hpp file inside my namespace
Tests should be written inside shared_ptr_tests.cpp using GoogleTest or Catch2
You should instantiate shared_ptr template class in shared_ptr_tests.cpp above your test cases, e.g. template class my::shared_ptr<int>; It's needed for code coverage check to work properly.
Do not forget about CI - UT + Valgrind / ASAN. Work in pairs.

Read the notes on cppreference.com
*/
#include <atomic>
#include <iostream>

namespace my {

void print_msg(const std::string& msg) {
    std::cout << static_cast<std::string>(msg) << std::endl;
}

template <class T>
void default_deleter(T* ptr) {
    if (ptr) {
        print_msg("Called default deleter!");
        print_msg("Deleting " + std::to_string(*ptr));
        delete ptr;
        ptr = nullptr;
    }
}

template <class T>
class ControlBlock {
    /*
    Holds a pointer to shared control block with 2 counters and a deleter:
    shared_refs count (as std::atomic<size_t>)
    weak_refs count (as std::atomic<size_t>)
    deleter (function pointer)
    */

public:
    ControlBlock(T* ptr)
        : ptr_(ptr) {
        print_msg("constructor ControlBlock");
    }

    ControlBlock(T* ptr, std::function<void(T*)> deleter)
        : ptr_(ptr), deleter_ptr_{deleter} {
        print_msg("constructor ControlBlock with deleter");
    }

    ~ControlBlock() {
        print_msg("destructor ~ControlBlock");
    }

    void call_deleter() {
        deleter_ptr_(ptr_);
    }

    std::atomic<size_t> shared_refs() const {
        return shared_refs_.load();
    }

    std::atomic<size_t> weak_refs() const {
        return weak_refs_.load();
    }

    void increment_shared() {
        shared_refs_.exchange(shared_refs_ + 1);
    }

    void decrement_shared() {
        if (shared_refs_) {
            shared_refs_.exchange(shared_refs_ - 1);
        }
    }

private:
    T* ptr_ = nullptr;
    std::atomic<size_t> shared_refs_ = 1;
    std::atomic<size_t> weak_refs_ = 0;
    std::function<void(T* ptr)> deleter_ptr_ = static_cast<void (*)(T*)>(my::default_deleter<T>);
};

template <class T>
class shared_ptr {
    T* ptr_ = nullptr;
    ControlBlock<T>* control_block_ptr = nullptr;

public:
    shared_ptr(T* ptr = nullptr)
        : ptr_{ptr}, control_block_ptr{new ControlBlock<T>(ptr_)} {
        print_msg("constructor shared_ptr (body)");
        if (ptr_) {
            print_msg("Created " + std::to_string(*ptr_));
        }
    }

    shared_ptr(T* ptr, std::function<void(T*)> deleter)
        : ptr_{ptr}, control_block_ptr{new ControlBlock<T>(ptr_, deleter)} {
        print_msg("constructor shared_ptr (body) with deleter");
        if (ptr_) {
            print_msg("Created " + std::to_string(*ptr_));
        }
    }

    ~shared_ptr() {
        print_msg("destructor ~shared_ptr");
        control_block_ptr->decrement_shared();
        if (control_block_ptr->shared_refs() == 0) {
            control_block_ptr->call_deleter();
        }
        if (control_block_ptr->shared_refs() == 0 && control_block_ptr->weak_refs() == 0) {
            delete control_block_ptr;
        }
    }

    std::atomic<size_t> get_shared_cnt() const {
        // print_msg("control_block_ptr = " + std::to_string((control_block_ptr ? true : false)));
        return control_block_ptr->shared_refs();
    }

    std::atomic<size_t> get_weak_cnt() const {
        return control_block_ptr->weak_refs();
    }

    shared_ptr& operator=(const shared_ptr& other) {
        print_msg("assignment operator");
        /* from cppreference
        Replaces the managed object with the one managed by other.

If *this already owns an object and it is the last shared_ptr owning it, and other is not the same as *this, the object is destroyed through the owned deleter.

1) Shares ownership of the object managed by other. If other manages no object, *this manages no object too. Equivalent to shared_ptr<T>(other).swap(*this).
        */
        if (this != &other) {  // avoid self-assignment

            if (control_block_ptr) {
                if (control_block_ptr->shared_refs() == 1) {
                    control_block_ptr->call_deleter();
                    // delete ptr_;
                    delete control_block_ptr;
                }
            }

            // Share ownership of the object managed by other
            ptr_ = other.ptr_;
            control_block_ptr = other.control_block_ptr;
            if (control_block_ptr) {
                control_block_ptr->increment_shared();
            }
        }

        return *this;
    }

    shared_ptr(const shared_ptr& other) {
        print_msg("copy constructor");
        ptr_ = other.ptr_;
        control_block_ptr = other.control_block_ptr;
        control_block_ptr->increment_shared();
    }
};

}  // namespace my