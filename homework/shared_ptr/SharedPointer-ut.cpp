#include <gtest/gtest.h>

#include "SharedPointer.hpp"
#include "WeakPointer.hpp"

int testValue = 5;

class TestClass {
public:
    int testFunction() {
        return testValue;
    }
};

class SharedPointerTest : public ::testing::Test {
protected:
    SharedPointerTest() : s_ptr(new int{testValue}) {}
    SharedPointer<int> s_ptr;
};

TEST_F(SharedPointerTest, shouldCreateSharedPointerFromWeakPointer) {
    WeakPointer<int> w_ptr{s_ptr};

    SharedPointer<int> ss_ptr{w_ptr};

    ASSERT_EQ(ss_ptr.get(), s_ptr.get());
}

TEST_F(SharedPointerTest, shouldCopySharedPointer) {
    auto newPtr(s_ptr);
    auto newPtr1 = s_ptr;

    ASSERT_EQ(*s_ptr, *newPtr);
    ASSERT_EQ(*s_ptr, *newPtr1);
}

TEST_F(SharedPointerTest, shouldMoveSharedPointer) {
    auto newPtr(std::move(s_ptr));
    ASSERT_EQ(*newPtr, testValue);
}

TEST_F(SharedPointerTest, shouldResetSharedPtr) {
    s_ptr.reset();

    ASSERT_EQ(s_ptr.get(), nullptr);
}

TEST_F(SharedPointerTest, shouldReturnUseCountOfSharedPointer) {
    int finalNumberOfReferences = 2;
    auto newPtr = s_ptr;

    ASSERT_EQ(s_ptr.use_count(), finalNumberOfReferences);
}

TEST_F(SharedPointerTest, shouldUseDereferenceOperatorOfSharedPointer) {
    ASSERT_EQ(*s_ptr, testValue);
}

TEST_F(SharedPointerTest, shouldUseArrowOperatorOfSharedPointer) {
    SharedPointer<TestClass> s_ptr(new TestClass{});

    ASSERT_EQ(s_ptr->testFunction(), testValue);
}
