#include <iostream>

#include "SharedPointer.hpp"
#include "WeakPointer.hpp"

int main() {
    std::cout << "\n\nWeak pointers: \n";
    SharedPointer<int> s_ptr(new int(33));
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    WeakPointer<int> w_ptr(s_ptr);
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";
    // w_ptr = s_ptr;
    auto sp = w_ptr.lock();
    if (!w_ptr.expired()) {
        std::cout << "sp = " << *sp << "\n";
    } else {
        std::cout << "Unable to lock \n";
    }
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";
    w_ptr.reset();
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";
    auto ssp = w_ptr.lock();
    if (!w_ptr.expired()) {
        std::cout << "ssp = " << *ssp << "\n";
    } else {
        std::cout << "Unable to lock \n";
    }
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";
    w_ptr = s_ptr;
    auto sssp = w_ptr.lock();
    if (!w_ptr.expired()) {
        std::cout << "sssp = " << *sssp << "\n";
    } else {
        std::cout << "Unable to lock \n";
    }
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";

    return 0;
}
