#include "MyUniquePtr.hpp"
#include <iostream>
#include <cassert>
#include <memory>

class testClassInt
{
    
public:
    int m_a;

    testClassInt(int a) : m_a(a) {
        std::cout << m_a << std::endl;
    }
};

void assertMyUniquePtrCanbeMoved()
{
    int* intPtr = new int(1);
    MyUniquePtr<int> myUniqueptr(intPtr);
    MyUniquePtr<int> myUniqueptr2(std::move(myUniqueptr));

    assert(myUniqueptr2.get() == intPtr);
    //assert(myUniqueptr.get() == nullptr);

    myUniqueptr = std::move(myUniqueptr2);

    assert(myUniqueptr.get() == intPtr);
}

void assertMyUniquePtrCanHoldVariable()
{
    int* intPtr = new int(1);
    MyUniquePtr<int> myUniqueptr(intPtr);

    assert(myUniqueptr.get() == intPtr);
}

void assertMyUniquePtrCanAccessMethodsUsingArrow()
{
    struct testClass{
        bool simpeleMember() { return true; };
    };

    MyUniquePtr<testClass> ptr(new testClass());

    assert(ptr->simpeleMember());
}

void assertMyUniquePtrCanAccessMethodsUsingStar()
{
    struct testClass{
        bool simpeleMember() { return true; };
    };

    MyUniquePtr<testClass> ptr(new testClass());

    assert((*ptr).simpeleMember());
}

void assertMyUniquePtrCanReleaseOwnership()
{
    struct testClass{
        bool simpeleMember() { return true; };
    };

    testClass* standardPtr = nullptr;

    {
        MyUniquePtr<testClass> ptr(new testClass());
        standardPtr = ptr.release();
    }
    assert((*standardPtr).simpeleMember());
    delete standardPtr;
}

void assertMyUniquePtrCanResetStoredPointer()
{
    testClassInt* t1 = new testClassInt(1);
    testClassInt* t2 = new testClassInt(10);

    MyUniquePtr<testClassInt> ptr(t1);
    MyUniquePtr<testClassInt> ptr2(t2);
    assert(ptr->m_a == 1);

    std::unique_ptr<int>a;

}

int main()
{
    assertMyUniquePtrCanHoldVariable();
    assertMyUniquePtrCanbeMoved();
    assertMyUniquePtrCanAccessMethodsUsingArrow();
    assertMyUniquePtrCanAccessMethodsUsingStar();
    assertMyUniquePtrCanReleaseOwnership();
    assertMyUniquePtrCanResetStoredPointer();

    return 0;
}