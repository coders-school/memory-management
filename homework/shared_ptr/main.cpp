#include <iostream>
#include "Scooter.hpp"
#include "SharedPtr.hpp"

int main() {
    int power{100};
    SharedPtr<Scooter> scooter(new Scooter(power));
    if (scooter) {
        std::cout << "scooter: There is something inside \n";
    }
    SharedPtr<Scooter> scooter2{};
    if (scooter2) {
        std::cout << "Scooter2: There is something inside \n";
    } else {
        std::cout << "Scooter2: pointer is empty \n";
	}
    return 0;
}
