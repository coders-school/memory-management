#include <iostream>
#include <utility>
#include <string>

#include "unique_ptr_verbose.hpp"

void lineBreak();

int main() {
    // default c'tor
    unique_ptr<int> ptr0; // null
    lineBreak();
    
    // c'tor binding to nullptr
    unique_ptr<int> ptr1(nullptr); // null
    lineBreak();
    
    // parametrized  c'tor
    unique_ptr<int> ptr2(new int(77));
    std::cout << "2: " << *ptr2 << std::endl;
    lineBreak();
    
    // copying c'tor
    unique_ptr<int> ptr3(ptr2); // ptr2 & ptr3 the same
    std::cout << "2: " << *ptr2 << std::endl;
    std::cout << "3: " << *ptr3 << std::endl;
    unique_ptr<int> ptr9(ptr0); // copying null
    if (ptr9.get()) { std::cout << "9: " << *ptr2 << std::endl; } // null
    lineBreak();
    
    // moving c'tor
    unique_ptr<int> ptr4(std::move(ptr3)); // ptr3 null now
    if (ptr3.get()) { std::cout << "3: " << *ptr2 << std::endl; } // null
    std::cout << "4: " << *ptr4 << std::endl;
    lineBreak();
    
    // assignment binding to nullptr
    ptr3 = nullptr; // null before and now
    ptr2 = nullptr; // null now
    if (ptr3.get()) { std::cout << "3: " << *ptr3 << std::endl; } // null
    lineBreak();
    
    // moving operator
    unique_ptr<int> ptr5(ptr4); // copying c'tor (ptr5 & ptr4 the same)
    ptr5 = std::move(ptr4); // ptr4 null now
    if (ptr4.get()) { std::cout << "4: " << *ptr4 << std::endl; } // null
    std::cout << "5: " << *ptr5 << std::endl;
    lineBreak();

    // access operator
    int result = *(ptr5->get());
    std::cout << "-> : " << result << std::endl;
    lineBreak();

    // dereference operator
    result = *ptr5;
    std::cout << "* : " << result << std::endl;
    lineBreak();

    // get pointer
    result = *(ptr5.get());
    std::cout << "get(): " << result << std::endl;
    lineBreak();

    // release pointer
    int* ptr = ptr5.release();  // ptr5 null now
    if (ptr5.get()) { std::cout << "5: " << *ptr5 << std::endl; } // null
    std::cout << "release(): null" << std::endl;
    lineBreak();

    // reset pointer
    ptr5.reset(new int(99)); // has value now
    std::cout << "reset: " << *ptr5 << std::endl; // null
    ptr5.reset(nullptr); // null again
    lineBreak();

    return 0;
}

void lineBreak() {
    std::cout << std::string(30, '-') << std::endl;
}
