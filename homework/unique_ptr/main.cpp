#include "UniquePtr.hpp"

#include <iostream>
#include <string>

int main() {
    UniquePtr<std::string> strPtr1{};
    strPtr1 = new std::string("First pointer");
    std::cout << "strPtr1: " << *strPtr1 << '\n';

    UniquePtr<std::string> strPtr2(new std::string{"Second pointer"});
    std::cout << "strPtr2: " << *strPtr2 << '\n';
    strPtr2 = std::move(strPtr1);
    std::cout << "\n---strPtr2 = std::move(strPtr1)--- \n";
    if (strPtr1.get() == nullptr) {
        std::cout << "strPtr1: nullptr" << '\n';
    }
    std::cout << "strPtr2: " << *strPtr2 << '\n';
    std::cout << "strPtr2 length = " << strPtr2->length() << '\n';

    std::cout << "\n---strPtr1.reset--- \n";
    strPtr1.reset(new std::string("New first string"));
    std::cout << "strPtr1: " << *strPtr1 << '\n';

    std::cout << "\n---strPtr3 = strPtr1.release()--- \n";
    auto strPtr3 = strPtr1.release();
    if (strPtr1.get() == nullptr) {
        std::cout << "strPtr1: nullptr" << '\n';
    }
    std::cout << "strPtr3: " << *strPtr3 << '\n';

    return 0;
}
