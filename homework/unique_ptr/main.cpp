#include <iostream>

#include "uniquePtr.hpp"

int main() {
    unique_ptr<double> firstPtr(new double{5.5});
    std::cout << *firstPtr << '\n';

    double* secondPtr = firstPtr.get();
    std::cout << *secondPtr << '\n';

    unique_ptr<double> thirdPtr(new double{5.5});
    thirdPtr.reset(new double{7.5});
    std::cout << *thirdPtr << '\n';

    unique_ptr<double> fourthPtr;
    try {
        *fourthPtr;
    } catch (NullptrException& e) { std::cout << e.what() << '\n'; }

    return 0;
}
