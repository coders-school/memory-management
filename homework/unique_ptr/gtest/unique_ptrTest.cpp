#include <gtest/gtest.h>
#include "../unique_ptr.hpp"

class TestClass
{
public:
    int number_{100};
    int numberReturn()
    {
        return number_;
    }
};

class unique_ptrFixture : public ::testing::Test
{
public:
    ~unique_ptrFixture()
    {
        delete rawPtr;
    }

protected:
    unique_ptr<int> ptr;
    unique_ptr<int> ptr1{new int{10}};
    unique_ptr<TestClass> ptrToClass{new TestClass};
    int *rawPtr{new int{20}};
};

TEST_F(unique_ptrFixture, DefaultCtorTest)
{
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(unique_ptrFixture, ParametricCtorTest)
{
    EXPECT_EQ(*ptr1, 10);

    unique_ptr<int> ptr2{rawPtr};
    rawPtr = nullptr;
    EXPECT_EQ(*ptr2, 20);

    unique_ptr<int> ptr3(nullptr);
    EXPECT_EQ(ptr3.get(), nullptr);
}

TEST_F(unique_ptrFixture, MoveCtorTest)
{
    unique_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(*ptr2, 10);
}

TEST_F(unique_ptrFixture, MoveAssingnmentOperatorTest)
{
    unique_ptr<int> ptr2;
    ptr2 = std::move(ptr1);
    EXPECT_EQ(*ptr2, 10);

    unique_ptr<int> ptr3;
    ptr3 = std::move(rawPtr);
    rawPtr = nullptr;
    EXPECT_EQ(*ptr3, 20);

    unique_ptr<int> ptr4;
    ptr4 = nullptr;
    EXPECT_EQ(ptr4.get(), nullptr);
}

TEST_F(unique_ptrFixture, AsteriskOperatorTest)
{
    EXPECT_EQ(*ptr1, 10);
}

TEST_F(unique_ptrFixture, ArrowOperatorTest)
{
    EXPECT_EQ(ptrToClass->number_, 100);
    EXPECT_EQ(ptrToClass->numberReturn(), 100);
}

TEST_F(unique_ptrFixture, GetFunctionTest)
{
    unique_ptr<int> ptr2{new int{20}};
    EXPECT_EQ(*ptr2.get(), *rawPtr);

    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(unique_ptrFixture, ReleaseFunctionTest)
{
    TestClass *rawPtrToTestClass;
    rawPtrToTestClass = ptrToClass.release();
    EXPECT_EQ(rawPtrToTestClass->number_, 100);
    EXPECT_EQ(ptrToClass.get(), nullptr);
    delete rawPtrToTestClass;
}

TEST_F(unique_ptrFixture, ResetFunctionTest)
{
    ptrToClass->number_ = 50;
    ptrToClass.reset(new TestClass);
    EXPECT_EQ(ptrToClass->number_, 100);
}
