#include <utility>

#include "unique_ptr.hpp"

int main() {
    unique_ptr<int> ptr0;
    unique_ptr<int> ptr1(nullptr);
    
    unique_ptr<int> ptr2(new int(77));
    
    unique_ptr<int> ptr3(ptr2);
    unique_ptr<int> ptr9(ptr0);

    unique_ptr<int> ptr4(std::move(ptr3));
    
    ptr3 = nullptr;
    ptr2 = nullptr;
    
    unique_ptr<int> ptr5(ptr4);
    ptr5 = std::move(ptr4);

    int result;
    result = *(ptr5->get());
    result = *ptr5;

    int* ptr = ptr5.release();

    ptr5.reset(new int(99));
    ptr5.reset(nullptr);

    return 0;
}
