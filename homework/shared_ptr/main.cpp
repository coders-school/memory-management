#include "shared_ptr.hpp"

#include <iostream>

void myDel(void* p) {
    std::cout << "My deleter!\n";
    delete (int*)p;
}

int main() {
    coders::shared_ptr<int> SharedPtr{new int(23)};
    // SharedPtr.setDeleter(myDel);
    

    return 0;
}