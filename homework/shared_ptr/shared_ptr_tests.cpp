#include <gtest/gtest.h>
#include "shared_ptr.hpp"

class TestClass {
public:
    TestClass(int number = 2) noexcept
        : number_(number) {}
    int getNumber() {
        return number_;
    }

private:
    int number_;
};

template class my::shared_ptr<TestClass>;

class shared_ptrFixture : public ::testing::Test {
public:
    ~shared_ptrFixture() {
        delete rawPtr;
    }

protected:
    my::shared_ptr<TestClass> emptyPtr;
    my::shared_ptr<TestClass> ptrToClass1{new TestClass{10}};
    TestClass* rawPtr{new TestClass{20}};
};

TEST_F(shared_ptrFixture, DefaultCtorTest) {
    EXPECT_EQ(emptyPtr.get(), nullptr);
}

TEST_F(shared_ptrFixture, ParametricCtorTest) {
    EXPECT_EQ((*ptrToClass1).getNumber(), 10);

    my::shared_ptr<TestClass> ptrToClass2{rawPtr};
    rawPtr = nullptr;
    EXPECT_EQ((*ptrToClass2).getNumber(), 20);
    EXPECT_EQ(ptrToClass1.use_count(), 1);

    my::shared_ptr<TestClass> ptrToClass3(nullptr);
    EXPECT_EQ(ptrToClass3.get(), nullptr);
    EXPECT_EQ(ptrToClass3.use_count(), 0);
}

TEST_F(shared_ptrFixture, ParametricCtorWithDeleterTest) {
    my::shared_ptr<TestClass> ptrToClass2{rawPtr, [](TestClass* ptr_) { delete ptr_; }};
    rawPtr = nullptr;
    EXPECT_EQ((*ptrToClass2).getNumber(), 20);
}

TEST_F(shared_ptrFixture, CopyCtorTest) {
    my::shared_ptr<TestClass> ptrToClass2{ptrToClass1};
    EXPECT_EQ((*ptrToClass2).getNumber(), 10);
    EXPECT_EQ(ptrToClass1.use_count(), 2);

    my::shared_ptr<TestClass> ptrToClass3{ptrToClass2};
    EXPECT_EQ((*ptrToClass3).getNumber(), 10);
    EXPECT_EQ(ptrToClass3.use_count(), 3);

    my::shared_ptr<TestClass> ptrToClass4{emptyPtr};
    EXPECT_EQ(ptrToClass4.get(), nullptr);
    EXPECT_EQ(ptrToClass4.use_count(), 0);
}

TEST_F(shared_ptrFixture, MoveCtorTest) {
    my::shared_ptr<TestClass> ptrToClass2{std::move(ptrToClass1)};
    EXPECT_EQ(ptrToClass1.get(), nullptr);
    EXPECT_EQ(ptrToClass1.use_count(), 0);
    EXPECT_EQ((*ptrToClass2).getNumber(), 10);
    EXPECT_EQ(ptrToClass2.use_count(), 1);

    my::shared_ptr<TestClass> ptrToClass3{rawPtr};
    rawPtr = nullptr;
    EXPECT_EQ((*ptrToClass3).getNumber(), 20);
    EXPECT_EQ(ptrToClass3.use_count(), 1);

    my::shared_ptr<TestClass> ptrToClass4{emptyPtr};
    EXPECT_EQ(ptrToClass4.get(), nullptr);
    EXPECT_EQ(ptrToClass4.use_count(), 0);
}

TEST_F(shared_ptrFixture, CopyAssingnmentOperatorTest) {
    my::shared_ptr<TestClass> ptrToClass2 = ptrToClass1;
    EXPECT_EQ((*ptrToClass2).getNumber(), 10);
    EXPECT_EQ(ptrToClass2.use_count(), 2);

    my::shared_ptr<TestClass> ptrToClass3 = emptyPtr;
    EXPECT_EQ(ptrToClass3.get(), nullptr);
    EXPECT_EQ(ptrToClass3.use_count(), 0);
}

TEST_F(shared_ptrFixture, MoveAssingnmentOperatorTest) {
    my::shared_ptr<TestClass> ptrToClass2;
    ptrToClass2 = std::move(ptrToClass1);
    EXPECT_EQ(ptrToClass1.get(), nullptr);
    EXPECT_EQ(ptrToClass1.use_count(), 0);
    EXPECT_EQ(*ptrToClass2, 10);
    EXPECT_EQ(ptrToClass2.use_count(), 1);

    my::shared_ptr<TestClass> ptrToClass3;
    EXPECT_EQ(ptrToClass3.use_count(), 0);
    ptrToClass3 = std::move(rawPtr);
    rawPtr = nullptr;
    EXPECT_EQ((*ptrToClass3).getNumber(), 20);
    EXPECT_EQ(ptrToClass3.use_count(), 1);

    my::shared_ptr<TestClass> ptrToClass4;
    EXPECT_EQ(ptrToClass4.use_count(), 0);
    ptrToClass4 = nullptr;
    EXPECT_EQ(ptrToClass4.get(), nullptr);
    EXPECT_EQ(ptrToClass4.use_count(), 0);
}

TEST_F(shared_ptrFixture, BoolOperatorTest) {
    EXPECT_FALSE(emptyPtr);
    EXPECT_TRUE(ptrToClass1);
}

TEST_F(shared_ptrFixture, AsteriskOperatorTest) {
    EXPECT_EQ((*ptrToClass1).getNumber(), 10);
}

TEST_F(shared_ptrFixture, ArrowOperatorTest) {
    EXPECT_EQ(ptrToClass->number_, 100);
    EXPECT_EQ(ptrToClass->numberReturn(), 100);
}

TEST_F(shared_ptrFixture, GetFunctionTest) {
    my::shared_ptr<TestClass> ptrToClass2{new TestClass{20}};
    EXPECT_EQ(*ptrToClass2.get(), *rawPtr);

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
    ptrToClass1.reset();
    EXPECT_EQ(ptrToClass1.get(), nullptr);
}

TEST_F(shared_ptrFixture, UseCountFunctionTest) {
    EXPECT_EQ(emptyPtr.use_count(), 0);
    EXPECT_EQ(ptrToClass1.use_count(), 1);
    EXPECT_EQ(ptrToClass.use_count(), 1);
}

TEST_F(shared_ptrFixture, getControlBlockPtrTest) {
    EXPECT_EQ(emptyPtr.getControlBlockPtr(), nullptr);
}