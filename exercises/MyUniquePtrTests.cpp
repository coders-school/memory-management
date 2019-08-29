#include "MyUniquePtr.hpp"

#include <cassert>

class testClassInt
{
    
public:
    int m_a;

    testClassInt(int a) : m_a(a) {}
};

void assertMyUniquePtrCanHoldVariable()
{
    int* intPtr = new int(1);
    MyUniquePtr<int> myUniqueptr(intPtr);

    assert(myUniqueptr.get() == intPtr);
}

void assertMyUniquePtrCanbeMoved()
{
    int* intPtr = new int(1);
    MyUniquePtr<int> myUniqueptr(intPtr);
    MyUniquePtr<int> myUniqueptr2(std::move(myUniqueptr));

    assert(myUniqueptr2.get() == intPtr);
    assert(myUniqueptr.get() == nullptr);

    myUniqueptr = std::move(myUniqueptr2);

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
    MyUniquePtr<testClassInt> ptr(new testClassInt(1));
    assert(ptr->m_a == 1);

    ptr.reset(new testClassInt(10));
    assert(ptr->m_a == 10);

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
