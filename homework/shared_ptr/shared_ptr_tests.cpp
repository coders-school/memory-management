
#include <gtest/gtest.h>
#include "shared_ptr.hpp"

#include <iostream>
#include <string>

template <class T>
class shared_ptr;

template class my::shared_ptr<int>;  // for coverage?

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

class SharedPtrClassTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    SharedPtrClassTest() {
        // You can do set-up work for each test here.
    }

    ~SharedPtrClassTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
};

TEST_F(SharedPtrClassTest, whenCreatedWithNullptr_thenPossibleToDelete) {
    my::shared_ptr<int> shared_ptr{nullptr};
}

void print_msg(const std::string& msg) {
    std::cout << static_cast<std::string>(msg) << std::endl;
}

void my_fancy_deleter(int* ptr) {
    if (ptr) {
        print_msg("Called fancy deleter!");
        print_msg("Deleting " + std::to_string(*ptr));
        delete ptr;
        ptr = nullptr;
    }
}

TEST_F(SharedPtrClassTest, whenCreatedWithNullptrAndCustomDeleter_thenPossibleToDelete) {
    my::shared_ptr<int> shared_ptr{nullptr, my_fancy_deleter};
}

TEST_F(SharedPtrClassTest, whenCreatedPtrToInt_thenPossibleToDelete) {
    my::shared_ptr<int> shared_ptr{new int(7)};
}

TEST_F(SharedPtrClassTest, whenCreatedPtrToIntWithCustomDeleter_thenPossibleToDelete) {
    my::shared_ptr<int> shared_ptr{new int(9), my_fancy_deleter};
}

TEST_F(SharedPtrClassTest, whenCreatedPtrToIntBeforeSharedPtrCreated_thenPossibleToDelete) {
    auto int_ptr = new int(13);
    my::shared_ptr<int> shared_ptr{int_ptr};
}

TEST_F(SharedPtrClassTest, whenCreatedWithNullptr_thenExpectOneSharedAndZeroWeakCnts) {
    my::shared_ptr<int> shared_ptr{nullptr};
    EXPECT_EQ(0, shared_ptr.use_count());
}

TEST_F(SharedPtrClassTest, whenCreatedIntWithPtrAndCreatedSecondPtrWithCopy_thenExpectTwoSharedAndZeroWeakCnts) {
    my::shared_ptr<int> shared_ptr{new int(11)};
    EXPECT_EQ(1, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
    {
        auto shared_ptr2 = shared_ptr;
        EXPECT_EQ(2, shared_ptr2.get_shared_cnt());
        EXPECT_EQ(0, shared_ptr2.get_weak_cnt());
    }
    EXPECT_EQ(1, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
}

TEST_F(SharedPtrClassTest, whenCreatedIntWithThreePtrs_thenExpectOneSharedCntAtTheEndOfTestAnyway) {
    my::shared_ptr<int> shared_ptr{new int(13)};
    EXPECT_EQ(1, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
    {
        auto shared_ptr2 = shared_ptr;
        auto shared_ptr3 = shared_ptr2;
        EXPECT_EQ(3, shared_ptr3.get_shared_cnt());
        EXPECT_EQ(0, shared_ptr3.get_weak_cnt());
    }
    EXPECT_EQ(1, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
}

TEST_F(SharedPtrClassTest, checkAssignOpeatorForPtrOwningNullptr) {
    my::shared_ptr<int> shared_ptr{new int(15)};
    EXPECT_EQ(1, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
    my::shared_ptr<int> shared_ptr2;
    shared_ptr2 = shared_ptr;
    EXPECT_EQ(2, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
    EXPECT_EQ(2, shared_ptr2.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr2.get_weak_cnt());
}

TEST_F(SharedPtrClassTest, checkAssignOpeatorForPtrOwningSomeMemory) {
    my::shared_ptr<int> shared_ptr{new int(15)};
    EXPECT_EQ(1, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
    my::shared_ptr<int> shared_ptr2{new int(17)};
    shared_ptr2 = shared_ptr;
    EXPECT_EQ(2, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
    EXPECT_EQ(2, shared_ptr2.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr2.get_weak_cnt());
}

TEST_F(SharedPtrClassTest, checkMoveConstructor) {
    my::shared_ptr<int> ptr{new int(15)};
    my::shared_ptr<int> second_ptr{std::move(ptr)};
    EXPECT_EQ(0, ptr.use_count());
    EXPECT_EQ(1, second_ptr.use_count());
}

TEST_F(SharedPtrClassTest, checkMovingOperator) {
    my::shared_ptr<int> shared_ptr{new int(15)};
    EXPECT_EQ(1, shared_ptr.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr.get_weak_cnt());
    my::shared_ptr<int> shared_ptr2{new int(17)};
    shared_ptr2 = std::move(shared_ptr);
    EXPECT_EQ(nullptr, shared_ptr);
    EXPECT_EQ(1, shared_ptr2.get_shared_cnt());
    EXPECT_EQ(0, shared_ptr2.get_weak_cnt());
}

TEST_F(SharedPtrClassTest, checkDereferenceOperator) {
    my::shared_ptr<int> shared_ptr{new int(17)};
    EXPECT_EQ(17, *shared_ptr);
}

class MyClass {
public:
    int value;
    MyClass(int val)
        : value(val) {}
    int get_value() const { return value; }
};

TEST_F(SharedPtrClassTest, checkReturnPointerOperator) {
    my::shared_ptr<MyClass> ptr{new MyClass(42)};
    EXPECT_EQ(42, ptr->get_value());
}

TEST_F(SharedPtrClassTest, checkGetMethod) {
    my::shared_ptr<MyClass> ptr{new MyClass(42)};
    EXPECT_EQ(42, ptr.get()->get_value());
}

TEST_F(SharedPtrClassTest, checkResetWithoutArgs) {
    my::shared_ptr<int> ptr{new int(42)};
    EXPECT_EQ(1, ptr.use_count());
    ptr.reset();
    EXPECT_EQ(0, ptr.use_count());
}

TEST_F(SharedPtrClassTest, checkResetWithArgs) {
    my::shared_ptr<int> ptr{new int(42)};
    EXPECT_EQ(1, ptr.use_count());
    EXPECT_EQ(42, *ptr.get());
    ptr.reset(new int(72));
    EXPECT_EQ(1, ptr.use_count());
    EXPECT_EQ(72, *ptr.get());
}

TEST_F(SharedPtrClassTest, checkBoolOperator) {
    my::shared_ptr<int> ptr1;
    my::shared_ptr<int> ptr2(new int(42));

    EXPECT_FALSE(ptr1);
    EXPECT_TRUE(ptr2);

    ptr1.reset(new int(13));
    EXPECT_TRUE(ptr1);
}
