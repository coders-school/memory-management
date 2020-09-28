#include <utility>

#include "unique_ptr.hpp"

int main() {
    unique_ptr<int> ptr0;
    unique_ptr<int> ptr1(nullptr);
    
    unique_ptr<int> ptr2(new int(77));
    
    unique_ptr<int> ptr3(std::move(ptr2));
    
    // int result;
    int result = *(ptr3->get());
    int value = *ptr3;
    (void)result;
    (void)value;
    
    int* ptr = ptr3.release();
    delete ptr;

    ptr3.reset(new int(99));
    ptr3.reset(nullptr);

    return 0;
}
