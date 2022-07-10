#include <gtest/gtest.h>
#include "weak_ptr.hpp"

class TestClass {
public:
    int number_{100};
    int numberReturn() {
        return number_;
    }
};

class weak_ptrFixture : public ::testing::Test {
public:
protected:
    my::weak_ptr<int> emptyWeakPtr;
    my::shared_ptr<int> emptySharedPtr;
    my::shared_ptr<int> sharedPtrToInt1{new int{10}};
    my::weak_ptr<int> weakPtrToInt1{sharedPtrToInt1};
};

TEST_F(weak_ptrFixture, DefaultCtorTest) {
    EXPECT_EQ(emptyWeakPtr.get(), nullptr);
}

TEST_F(weak_ptrFixture, ParametricCtorTest) {
    EXPECT_EQ(*weakPtrToInt1.get(), 10);

    my::weak_ptr<int> weakPtrToInt2{weakPtrToInt1};
    EXPECT_EQ(*weakPtrToInt2, 10);

    my::weak_ptr<int> weakPtrToInt3{emptyWeakPtr};
    EXPECT_EQ(weakPtrToInt3.get(), nullptr);
}

//     my::shared_ptr<int> ptrToInt2{rawPtr};
//     rawPtr = nullptr;
//     EXPECT_EQ(*ptrToInt2, 20);
//     EXPECT_EQ(ptrToInt1.use_count(), 1);

//     my::shared_ptr<int> ptrToInt3(nullptr);
//     EXPECT_EQ(ptrToInt3.get(), nullptr);
//     EXPECT_EQ(ptrToInt3.use_count(), 0);
// }

// TEST_F(shared_ptrFixture, CopyCtorTest) {
//     my::shared_ptr<int> ptrToInt2{ptrToInt1};
//     EXPECT_EQ(*ptrToInt2, 10);
//     EXPECT_EQ(ptrToInt1.use_count(), 2);

//     my::shared_ptr<int> ptrToInt3{ptrToInt2};
//     EXPECT_EQ(*ptrToInt3, 10);
//     EXPECT_EQ(ptrToInt3.use_count(), 3);

//     my::shared_ptr<int> ptrToInt4{emptyPtr};
//     EXPECT_EQ(ptrToInt4.get(), nullptr);
//     EXPECT_EQ(ptrToInt4.use_count(), 0);
// }

// TEST_F(shared_ptrFixture, MoveCtorTest) {
//     my::shared_ptr<int> ptrToInt2{std::move(ptrToInt1)};
//     EXPECT_EQ(ptrToInt1.get(), nullptr);
//     EXPECT_EQ(ptrToInt1.use_count(), 0);
//     EXPECT_EQ(*ptrToInt2, 10);
//     EXPECT_EQ(ptrToInt2.use_count(), 1);

//     my::shared_ptr<int> ptrToInt3(rawPtr);
//     rawPtr = nullptr;
//     EXPECT_EQ(*ptrToInt3, 20);
//     EXPECT_EQ(ptrToInt3.use_count(), 1);

//     my::shared_ptr<int> ptrToInt4(emptyPtr);
//     EXPECT_EQ(ptrToInt4.get(), nullptr);
//     EXPECT_EQ(ptrToInt4.use_count(), 0);
// }

// TEST_F(shared_ptrFixture, CopyAssingnmentOperatorTest) {
//     my::shared_ptr<int> ptrToInt2 = ptrToInt1;
//     EXPECT_EQ(*ptrToInt2, 10);
//     EXPECT_EQ(ptrToInt2.use_count(), 2);

//     my::shared_ptr<int> ptrToInt3 = emptyPtr;
//     EXPECT_EQ(ptrToInt3.get(), nullptr);
//     EXPECT_EQ(ptrToInt3.use_count(), 0);
// }

// TEST_F(shared_ptrFixture, MoveAssingnmentOperatorTest) {
//     my::shared_ptr<int> ptrToInt2;
//     ptrToInt2 = std::move(ptrToInt1);
//     EXPECT_EQ(ptrToInt1.get(), nullptr);
//     EXPECT_EQ(ptrToInt1.use_count(), 0);
//     EXPECT_EQ(*ptrToInt2, 10);
//     EXPECT_EQ(ptrToInt2.use_count(), 1);

//     my::shared_ptr<int> ptrToInt3;
//     EXPECT_EQ(ptrToInt3.use_count(), 0);
//     ptrToInt3 = std::move(rawPtr);
//     rawPtr = nullptr;
//     EXPECT_EQ(*ptrToInt3, 20);
//     EXPECT_EQ(ptrToInt3.use_count(), 1);

//     my::shared_ptr<int> ptrToInt4;
//     EXPECT_EQ(ptrToInt4.use_count(), 0);
//     ptrToInt4 = nullptr;
//     EXPECT_EQ(ptrToInt4.get(), nullptr);
//     EXPECT_EQ(ptrToInt4.use_count(), 0);
// }

TEST_F(weak_ptrFixture, AsteriskOperatorTest) {
    EXPECT_EQ(*weakPtrToInt1, 10);
}

// TEST_F(shared_ptrFixture, ArrowOperatorTest) {
//     EXPECT_EQ(ptrToClass->number_, 100);
//     EXPECT_EQ(ptrToClass->numberReturn(), 100);
// }

TEST_F(weak_ptrFixture, GetFunctionTest) {
    EXPECT_EQ(emptyWeakPtr.get(), nullptr);
}

// TEST_F(shared_ptrFixture, ReleaseFunctionTest) {
//     TestClass* rawPtrToTestClass;
//     rawPtrToTestClass = ptrToClass.release();
//     EXPECT_EQ(rawPtrToTestClass->number_, 100);
//     EXPECT_EQ(ptrToClass.get(), nullptr);
//     delete rawPtrToTestClass;
// }

// TEST_F(shared_ptrFixture, ResetFunctionWithParamaterTest) {
//     ptrToClass->number_ = 50;
//     ptrToClass.reset(new TestClass);
//     EXPECT_EQ(ptrToClass->number_, 100);
// }

// TEST_F(shared_ptrFixture, ResetFunctionTest) {
//     ptrToInt1.reset();
//     EXPECT_EQ(ptrToInt1.get(), nullptr);
// }

TEST_F(weak_ptrFixture, UseCountFunctionTest) {
    EXPECT_EQ(emptyWeakPtr.use_count(), 0);
    EXPECT_EQ(weakPtrToInt1.use_count(), 1);
}