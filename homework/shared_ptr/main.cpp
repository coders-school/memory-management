#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

#include <iostream>

void myDeleter(int* p) {
    std::cout << "My deleter!\n";
    delete p;
}

int main() {
    coders::shared_ptr<int> testPtr{new int(23),myDeleter};
    coders::shared_ptr<int> testPtr_2{new int(666), myDeleter};

    coders::shared_ptr<int> moved(std::move(testPtr));

    coders::weak_ptr<int> testWeak(testPtr);

    return 0;
}
