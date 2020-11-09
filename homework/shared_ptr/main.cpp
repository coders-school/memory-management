#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

#include <iostream>
#include <memory>

void myDeleter(int* p) {
    std::cout << "My deleter!\n";
    delete p;
}

int main() {
    coders::shared_ptr<int> testPtr{new int(23),myDeleter};
    coders::shared_ptr<int> testPtr_2{new int(666), myDeleter};

    coders::shared_ptr<int> moved(std::move(testPtr));

    coders::weak_ptr<int> testWeak(testPtr);

    coders::shared_ptr<int> emptySharedPtr{};
    std::cout << "emptySharedPtr.use_count() = " << emptySharedPtr.use_count() << '\n';
    coders::shared_ptr<int> copiedSharedPtr{emptySharedPtr};
    std::cout << "copiedSharedPtr.use_count() = " << copiedSharedPtr.use_count() << '\n';
    copiedSharedPtr.reset();
    std::cout << "emptySharedPtr.use_count() after copied reset = " << emptySharedPtr.use_count() << '\n';
    std::cout << "copiedSharedPtr.use_count() after copied reset = " << copiedSharedPtr.use_count() << '\n';

    std::cout<<"\n\n";
    coders::shared_ptr<int> anotherEmptySharedPtr{};
    std::cout << "anotherEmptySharedPtr.use_count() = " << anotherEmptySharedPtr.use_count() << '\n';
    coders::shared_ptr<int> anotherMovedSharedPtr;
    anotherMovedSharedPtr = anotherEmptySharedPtr;
    std::cout << "anotherCopiedSharedPtr.use_count() = " << anotherMovedSharedPtr.use_count() << '\n';
    anotherMovedSharedPtr.reset();
    std::cout << "anotherEmptySharedPtr.use_count() after move reset = " << anotherEmptySharedPtr.use_count() << '\n';
    std::cout << "anotherMovedSharedPtr.use_count() after move reset = " << anotherMovedSharedPtr.use_count() << '\n';

    return 0;
}
