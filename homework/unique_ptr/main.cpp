#include "unique_ptr.hpp"

int main() {
    ma::unique_ptr<int> ptr{new int{5}};
    ptr = std::move(ptr);
 
    std::cout << *ptr << '\n';
    std::cout << ptr.get() << '\n'; //:P
    auto rawPtr = ptr.release();
    delete rawPtr;
 
    // cs::unique_ptr<int> ptr2 = ptr;
    ma::unique_ptr<int> ptr3{new int{5}};
    // ptr3 = std::move(ptr);
    ma::unique_ptr<int> ptr2 = std::move(ptr);
    ptr.reset(new int{10});
    ptr.reset();
}
