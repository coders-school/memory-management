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

    std::vector<SharedPointer<int>> ownSharedPointerVector{};
    std::vector<SharedPointer<int>> ownMakeSharedVector{};
    ownSharedPointerVector.reserve(50000);
    ownMakeSharedVector.reserve(50000);

    std::vector<std::shared_ptr<int>> libraryMakeSharedVector{};
    std::vector<std::shared_ptr<int>> librarySharedPointerVector{};
    libraryMakeSharedVector.reserve(50000);
    librarySharedPointerVector.reserve(50000);

    //CREATING OWN SHARED POINTER AND MAKE SHARED

    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            ownMakeSharedVector.emplace_back(MakeShared<int>(i));
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Create Own MakeShared: " << fullTime.count() << " seconds.\n";
    }
    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            ownSharedPointerVector.emplace_back(new int{i});
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Create Own SharedPointer: " << fullTime.count() << " seconds.\n";
    }

    //CREATING STDANDARD LIBRARY SHARED POINTER AND MAKE SHARED

    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            libraryMakeSharedVector.emplace_back(std::make_shared<int>(i));
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Create Library MakeShared: " << fullTime.count() << " seconds.\n";
    }
    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            librarySharedPointerVector.emplace_back(new int{i});
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Create Library SharedPointer: " << fullTime.count() << " seconds.\n";
    }

    //USING OWN SHARED POINTER AND MAKE SHARED

    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            ownMakeSharedVector[i];
            for (int i = 0; i < 10000; ++i) {
                ownMakeSharedVector[i];
            }
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Using Own MakeShared: " << fullTime.count() << " seconds.\n";
    }
    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            ownSharedPointerVector[i];
            for (int i = 0; i < 10000; ++i) {
                ownSharedPointerVector[i];
            }
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Using Own SharedPointer: " << fullTime.count() << " seconds.\n";
    }

    //USING STDANDARD LIBRARY SHARED POINTER AND MAKE SHARED

    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            libraryMakeSharedVector[i];
            for (int i = 0; i < 10000; ++i) {
                libraryMakeSharedVector[i];
            }
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Using Library MakeShared: " << fullTime.count() << " seconds.\n";
    }
    {
        high_resolution_clock::time_point timeStart = high_resolution_clock::now();

        for (int i = 0; i < 50000; ++i) {
            librarySharedPointerVector[i];
            for (int i = 0; i < 10000; ++i) {
                librarySharedPointerVector[i];
            }
        }

        high_resolution_clock::time_point timeStop = high_resolution_clock::now();

        duration<double> fullTime = duration_cast<duration<double>>(timeStop - timeStart);

        std::cout << "Timer Using Library SharedPointer: " << fullTime.count() << " seconds.\n";
    }

    return 0;
}
