#include <gtest/gtest.h>
#include "shared_ptr.hpp"

class TestClass {
public:
    TestClass(int number = 2) noexcept
        : number_(number) {}
    int getNumber() {
        return number_;
    }

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
    EXPECT_EQ(ptrToClass2.use_count(), 1);

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
    my::shared_ptr<TestClass> ptrToClass2{emptyPtr};
    EXPECT_EQ(ptrToClass2.get(), nullptr);
    EXPECT_EQ(ptrToClass2.use_count(), 0);

    my::shared_ptr<TestClass> ptrToClass3{ptrToClass1};
    EXPECT_NE(ptrToClass3.get(), nullptr);
    EXPECT_EQ(ptrToClass3.use_count(), 2);
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

    my::shared_ptr<TestClass> ptrToClass5{nullptr};
    EXPECT_EQ(ptrToClass5.get(), nullptr);
    EXPECT_EQ(ptrToClass5.use_count(), 0);
}

TEST_F(shared_ptrFixture, DtorTest) {
    {
        my::shared_ptr<TestClass> ptrToClass2{new TestClass{30}};
        {
            my::shared_ptr<TestClass> ptrToClass3{ptrToClass2};
            EXPECT_EQ(ptrToClass2.use_count(), 2);
        }
        EXPECT_EQ(ptrToClass2.use_count(), 1);
        EXPECT_NE(ptrToClass2.get(), nullptr);
        EXPECT_NE(ptrToClass2.getControlBlockPtr(), nullptr);
    }
}

TEST_F(shared_ptrFixture, CopyAssingnmentOperatorTest) {
    my::shared_ptr<TestClass> ptrToClass2{ptrToClass1};
    ptrToClass2 = ptrToClass1;
    EXPECT_EQ(ptrToClass1.get(), ptrToClass2.get());

    my::shared_ptr<TestClass> ptrToClass3{};
    my::shared_ptr<TestClass> ptrToClass4{};
    ptrToClass3 = ptrToClass4;
    EXPECT_EQ(ptrToClass3.get(), nullptr);
    EXPECT_EQ(ptrToClass3.getControlBlockPtr(), nullptr);
    EXPECT_EQ(ptrToClass3.use_count(), 0);
    EXPECT_EQ(ptrToClass4.get(), nullptr);
    EXPECT_EQ(ptrToClass4.getControlBlockPtr(), nullptr);
    EXPECT_EQ(ptrToClass4.use_count(), 0);

    my::shared_ptr<TestClass> ptrToClass5;
    my::shared_ptr<TestClass> ptrToClass6{new TestClass{30}};
    ptrToClass5 = ptrToClass6;
    EXPECT_EQ((*ptrToClass5).getNumber(), 30);
    EXPECT_EQ(ptrToClass5.get(), ptrToClass6.get());
    EXPECT_EQ(ptrToClass5.getControlBlockPtr(), ptrToClass6.getControlBlockPtr());
    EXPECT_EQ(ptrToClass5.use_count(), 2);

    my::shared_ptr<TestClass> ptrToClass7{new TestClass{40}};
    my::shared_ptr<TestClass> ptrToClass8;
    ptrToClass7 = ptrToClass8;
    EXPECT_EQ(ptrToClass7.get(), nullptr);
    EXPECT_EQ(ptrToClass7.getControlBlockPtr(), nullptr);
    EXPECT_EQ(ptrToClass7.use_count(), 0);
    EXPECT_EQ(ptrToClass8.get(), nullptr);
    EXPECT_EQ(ptrToClass8.getControlBlockPtr(), nullptr);
    EXPECT_EQ(ptrToClass8.use_count(), 0);

    my::shared_ptr<TestClass> ptrToClass9{new TestClass{50}};
    my::shared_ptr<TestClass> ptrToClass10{new TestClass{60}};
    ptrToClass9 = ptrToClass10;
    EXPECT_EQ((*ptrToClass9).getNumber(), 60);
    EXPECT_EQ(ptrToClass9.get(), ptrToClass10.get());
    EXPECT_EQ(ptrToClass9.getControlBlockPtr(), ptrToClass10.getControlBlockPtr());
    EXPECT_EQ(ptrToClass9.use_count(), 2);
}

TEST_F(shared_ptrFixture, MoveAssingnmentOperatorTest) {
    my::shared_ptr<TestClass> ptrToClass2{ptrToClass1};
    ptrToClass2 = ptrToClass1;
    EXPECT_EQ(ptrToClass1.get(), ptrToClass2.get());

    my::shared_ptr<TestClass> ptrToClass3{};
    my::shared_ptr<TestClass> ptrToClass4{};
    ptrToClass3 = ptrToClass4;
    EXPECT_EQ(ptrToClass3.get(), nullptr);
    EXPECT_EQ(ptrToClass3.getControlBlockPtr(), nullptr);
    EXPECT_EQ(ptrToClass3.use_count(), 0);
    EXPECT_EQ(ptrToClass4.get(), nullptr);
    EXPECT_EQ(ptrToClass4.getControlBlockPtr(), nullptr);
    EXPECT_EQ(ptrToClass4.use_count(), 0);

    // my::shared_ptr<TestClass> ptrToClass5{new TestClass{30}};

    // my::shared_ptr<TestClass> ptrToClass2;
    // ptrToClass2 = std::move(ptrToClass1);
    // EXPECT_EQ(ptrToClass1.get(), nullptr);
    // EXPECT_EQ(ptrToClass1.use_count(), 0);
    // EXPECT_EQ((*ptrToClass2).getNumber(), 10);
    // EXPECT_EQ(ptrToClass2.use_count(), 1);

    // my::shared_ptr<TestClass> ptrToClass3;
    // EXPECT_EQ(ptrToClass3.use_count(), 0);
    // ptrToClass3 = std::move(rawPtr);
    // rawPtr = nullptr;
    // EXPECT_EQ((*ptrToClass3).getNumber(), 20);
    // EXPECT_EQ(ptrToClass3.use_count(), 1);

    // my::shared_ptr<TestClass> ptrToClass4;
    // EXPECT_EQ(ptrToClass4.use_count(), 0);
    // ptrToClass4 = nullptr;
    // EXPECT_EQ(ptrToClass4.get(), nullptr);
    // EXPECT_EQ(ptrToClass4.use_count(), 0);
}

TEST_F(shared_ptrFixture, BoolOperatorTest) {
    EXPECT_FALSE(emptyPtr);
    EXPECT_TRUE(ptrToClass1);
}

TEST_F(shared_ptrFixture, AsteriskOperatorTest) {
    EXPECT_EQ((*ptrToClass1).getNumber(), 10);
}

TEST_F(shared_ptrFixture, ArrowOperatorTest) {
    EXPECT_EQ(ptrToClass1->number_, 10);
}

TEST_F(shared_ptrFixture, GetFunctionTest) {
    EXPECT_EQ(emptyPtr.get(), nullptr);
}

TEST_F(shared_ptrFixture, ReleaseFunctionTest) {
    TestClass* rawPtrToTestClass;
    rawPtrToTestClass = ptrToClass1.release();
    EXPECT_EQ((*rawPtrToTestClass).getNumber(), 10);
    EXPECT_EQ(ptrToClass1.get(), nullptr);
    delete rawPtrToTestClass;
}

TEST_F(shared_ptrFixture, ResetFunctionWithParamaterTest) {
    ptrToClass1->number_ = 50;
    ptrToClass1.reset(new TestClass);
    EXPECT_EQ((*ptrToClass1).getNumber(), 2);
}

TEST_F(shared_ptrFixture, ResetFunctionTest) {
    ptrToClass1.reset();
    EXPECT_EQ(ptrToClass1.get(), nullptr);
}

TEST_F(shared_ptrFixture, UseCountFunctionTest) {
    EXPECT_EQ(emptyPtr.use_count(), 0);
    EXPECT_EQ(ptrToClass1.use_count(), 1);
    EXPECT_EQ(ptrToClass1.use_count(), 1);
}

TEST_F(shared_ptrFixture, getControlBlockPtrTest) {
    EXPECT_EQ(emptyPtr.getControlBlockPtr(), nullptr);
}