#include "MakeShared.hpp"
#include "SharedPointer.hpp"

#include <iostream>
#include <memory>
#include <utility>

#include <chrono>
#include <ctime>
#include <ratio>
#include <vector>

using namespace std::chrono;

int main()
{
    std::cout << "Shared pointers: \n";
    SharedPointer<int> ptr2(new int(44));
    std::cout << *ptr2 << "\n";
    int* man_ptr = ptr2.get();
    std::cout << *man_ptr << "\n";
    std::cout << *ptr2.get() << "\n";
    std::cout << ptr2.use_count() << "\n";
    SharedPointer<int> ptr3(ptr2);
    *ptr3 += 5;

    SharedPointer<int> ptr4(ptr2);
    std::cout << ptr2.use_count() << "\n";

    std::cout << *ptr3.get() << "\n";
    std::cout << *ptr2.get() << "\n";
    std::cout << ptr3.use_count() << "\n";

    auto msPtr = MakeShared<int>(20);
    std::cout << *msPtr << "\n";
    std::cout << *msPtr.get() << "\n";
    std::cout << msPtr.use_count() << "\n";
    SharedPointer<int> ptr5 = msPtr;
    std::cout << msPtr.use_count() << "\n";
    {
        SharedPointer<int> ptr = msPtr;
        std::cout << msPtr.use_count() << "\n";
    }
    std::cout << msPtr.use_count() << "\n";

    auto msPtrPair = MakeShared<std::pair<int, int>>(std::make_pair(555, 111));
    std::cout << (*msPtrPair).first << "\n";
    std::cout << (*msPtrPair).second << "\n";

    std::vector<SharedPointer<int>> testVector1{};
    std::vector<SharedPointer<int>> testVector2{};
    testVector1.reserve(50000);
    testVector2.reserve(50000);

    std::vector<std::shared_ptr<int>> testVector3{};
    std::vector<std::shared_ptr<int>> testVector4{};
    testVector3.reserve(50000);
    testVector4.reserve(50000);

    {
        high_resolution_clock::time_point timeStart2 = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            testVector2.emplace_back(MakeShared<int>(i));
        }

        high_resolution_clock::time_point timeStop2 = high_resolution_clock::now();

        duration<double> fullTime2 = duration_cast<duration<double>>(timeStop2 - timeStart2);

        std::cout << "Timer MakeShared: " << fullTime2.count() << " seconds.\n";

        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            testVector1.emplace_back(new int{i});
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer SharedPointer: " << fullTime.count() << " seconds.\n";
   
    }

    {
        high_resolution_clock::time_point timeStart2 = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            testVector3.emplace_back(std::make_shared<int>(i));
        }

        high_resolution_clock::time_point timeStop2 = high_resolution_clock::now();

        duration<double> fullTime2 = duration_cast<duration<double>>(timeStop2 - timeStart2);

        std::cout << "Timer LibraryMakeShared: " << fullTime2.count() << " seconds.\n";

        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            testVector4.emplace_back(new int{i});
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer LibrarySharedPointer: " << fullTime.count() << " seconds.\n";
   
    }

    return 0;
}
