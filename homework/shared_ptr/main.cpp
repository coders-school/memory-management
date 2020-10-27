#include "shared_ptr.hpp"

#include <iostream>

void myDel(void* p) {
    std::cout << "My deleter!\n";
    delete (int*)p;
}

int main() {
    coders::shared_ptr<int> testPtr{new int(23), myDel};
    coders::shared_ptr<int> testPtr_2{new int(666), myDel};
    // testPtr.setDeleter(myDel);
    

    return 0;
}