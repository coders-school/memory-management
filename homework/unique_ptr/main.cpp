#include <iostream>
#include <utility>

#include "UniquePtr.hpp"

int main() {
    auto hello = UniquePtr<int>(new int(10));
    std::cout << "Value from hello: " << *hello << '\n';

    auto hello_2 = UniquePtr<int>(new int(20));
    std::cout << "Value from hello_2: " << *hello_2 << '\n';

    auto hello_3 = std::move(hello);
    std::cout << "Value from hello_3: " << *hello_3 << '\n';

    // auto hello4 = hello_3;  // this is forbidden :)
    return 0;
}
