#include <iostream>
#include "SharedPtr.hpp"

constexpr double testingValue = 15;

int main() {
    {
        coders_school::shared_ptr<int> data(new int{5});
        std::cout << "UZYCIA " << data.use_count() << '\n';
        {
            coders_school::shared_ptr<int> ala = data;
            std::cout << "UZYCIA " << data.use_count() << '\n';
            {
                coders_school::shared_ptr<int> ania = data;
                std::cout << "UZYCIA " << data.use_count() << '\n';
            }
            std::cout << "UZYCIA " << data.use_count() << '\n';
        }
        std::cout << "UZYCIA " << data.use_count() << '\n';
    }

    coders_school::shared_ptr<int> raw;
    coders_school::shared_ptr<int> braw;
    coders_school::shared_ptr<double> ein(new double{10.0});
    std::cout << *ein << '\n';
    std::cout << ein.get() << '\n';
    std::cout << ein.use_count() << '\n';

    struct ArrowOperatorTest {
        double returningTestValue() { return testingValue; }
    };

    coders_school::shared_ptr<ArrowOperatorTest> test(new ArrowOperatorTest{});
    std::cout << test->returningTestValue() << '\n';

    coders_school::shared_ptr<int> zwei(new int{10});
    coders_school::shared_ptr<int> moveTesting = std::move(zwei);
}