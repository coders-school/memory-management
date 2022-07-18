#include <gtest/gtest.h>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

class TestClass {
public:
    int number_{100};
    int numberReturn() {
        return number_;
    }
};

class shared_ptrFixture : public ::testing::Test {
public:
    ~shared_ptrFixture() {
        delete rawPtr;
    }

protected:
    my::shared_ptr<int> emptyPtr;
    my::shared_ptr<int> ptrToInt1{new int{10}};
    my::shared_ptr<TestClass> ptrToClass{new TestClass};
    int* rawPtr{new int{20}};
};

TEST_F(shared_ptrFixture, DefaultCtorTest) {
    EXPECT_EQ(emptyPtr.get(), nullptr);
}

TEST_F(shared_ptrFixture, ParametricCtorTest) {
    EXPECT_EQ(*ptrToInt1, 10);

    my::shared_ptr<int> ptrToInt2{rawPtr};
    rawPtr = nullptr;
    EXPECT_EQ(*ptrToInt2, 20);
    EXPECT_EQ(ptrToInt1.use_count(), 1);

    my::shared_ptr<int> ptrToInt3(nullptr);
    EXPECT_EQ(ptrToInt3.get(), nullptr);
    EXPECT_EQ(ptrToInt3.use_count(), 0);
}

TEST_F(shared_ptrFixture, CopyCtorTest) {
    my::shared_ptr<int> ptrToInt2{ptrToInt1};
    EXPECT_EQ(*ptrToInt2, 10);
    EXPECT_EQ(ptrToInt1.use_count(), 2);

    my::shared_ptr<int> ptrToInt3{ptrToInt2};
    EXPECT_EQ(*ptrToInt3, 10);
    EXPECT_EQ(ptrToInt3.use_count(), 3);

    my::shared_ptr<int> ptrToInt4{emptyPtr};
    EXPECT_EQ(ptrToInt4.get(), nullptr);
    EXPECT_EQ(ptrToInt4.use_count(), 0);
}

TEST_F(shared_ptrFixture, MoveCtorTest) {
    my::shared_ptr<int> ptrToInt2{std::move(ptrToInt1)};
    EXPECT_EQ(ptrToInt1.get(), nullptr);
    EXPECT_EQ(ptrToInt1.use_count(), 0);
    EXPECT_EQ(*ptrToInt2, 10);
    EXPECT_EQ(ptrToInt2.use_count(), 1);

    my::shared_ptr<int> ptrToInt3(rawPtr);
    rawPtr = nullptr;
    EXPECT_EQ(*ptrToInt3, 20);
    EXPECT_EQ(ptrToInt3.use_count(), 1);

    my::shared_ptr<int> ptrToInt4(emptyPtr);
    EXPECT_EQ(ptrToInt4.get(), nullptr);
    EXPECT_EQ(ptrToInt4.use_count(), 0);
}

TEST_F(shared_ptrFixture, CopyCtorWeakPtrAsArgumentTest) {
    my::weak_ptr<int> weakPtrToInt1{ptrToInt1};
    auto sharedPtrToInt2 = weakPtrToInt1.lock();
    EXPECT_EQ(*sharedPtrToInt2, 10);
}

TEST_F(shared_ptrFixture, CopyAssingnmentOperatorTest) {
    my::shared_ptr<int> ptrToInt2 = ptrToInt1;
    EXPECT_EQ(*ptrToInt2, 10);
    EXPECT_EQ(ptrToInt2.use_count(), 2);

    my::shared_ptr<int> ptrToInt3 = emptyPtr;
    EXPECT_EQ(ptrToInt3.get(), nullptr);
    EXPECT_EQ(ptrToInt3.use_count(), 0);
}

TEST_F(shared_ptrFixture, MoveAssingnmentOperatorTest) {
    my::shared_ptr<int> ptrToInt2;
    ptrToInt2 = std::move(ptrToInt1);
    EXPECT_EQ(ptrToInt1.get(), nullptr);
    EXPECT_EQ(ptrToInt1.use_count(), 0);
    EXPECT_EQ(*ptrToInt2, 10);
    EXPECT_EQ(ptrToInt2.use_count(), 1);

    my::shared_ptr<int> ptrToInt3;
    EXPECT_EQ(ptrToInt3.use_count(), 0);
    ptrToInt3 = std::move(rawPtr);
    rawPtr = nullptr;
    EXPECT_EQ(*ptrToInt3, 20);
    EXPECT_EQ(ptrToInt3.use_count(), 1);

    my::shared_ptr<int> ptrToInt4;
    EXPECT_EQ(ptrToInt4.use_count(), 0);
    ptrToInt4 = nullptr;
    EXPECT_EQ(ptrToInt4.get(), nullptr);
    EXPECT_EQ(ptrToInt4.use_count(), 0);
}

TEST_F(shared_ptrFixture, AsteriskOperatorTest) {
    EXPECT_EQ(*ptrToInt1, 10);
}

TEST_F(shared_ptrFixture, ArrowOperatorTest) {
    EXPECT_EQ(ptrToClass->number_, 100);
    EXPECT_EQ(ptrToClass->numberReturn(), 100);
}

TEST_F(shared_ptrFixture, GetFunctionTest) {
    my::shared_ptr<int> ptrToInt2{new int{20}};
    EXPECT_EQ(*ptrToInt2.get(), *rawPtr);

    EXPECT_EQ(emptyPtr.get(), nullptr);
}

TEST_F(shared_ptrFixture, ReleaseFunctionTest) {
    TestClass* rawPtrToTestClass;
    rawPtrToTestClass = ptrToClass.release();
    EXPECT_EQ(rawPtrToTestClass->number_, 100);
    EXPECT_EQ(ptrToClass.get(), nullptr);
    delete rawPtrToTestClass;
}

TEST_F(shared_ptrFixture, ResetFunctionWithParamaterTest) {
    ptrToClass->number_ = 50;
    ptrToClass.reset(new TestClass);
    EXPECT_EQ(ptrToClass->number_, 100);
}

TEST_F(shared_ptrFixture, ResetFunctionTest) {
    ptrToInt1.reset();
    EXPECT_EQ(ptrToInt1.get(), nullptr);
}

TEST_F(shared_ptrFixture, UseCountFunctionTest) {
    EXPECT_EQ(emptyPtr.use_count(), 0);
    EXPECT_EQ(ptrToInt1.use_count(), 1);
    EXPECT_EQ(ptrToClass.use_count(), 1);
}

TEST_F(shared_ptrFixture, getControlBlockRefTest) {
    EXPECT_EQ(emptyPtr.getControlBlockPtr(), nullptr);
    EXPECT_EQ(ptrToInt1.getControlBlockPtr()->getSharedRefs(), 1);
}