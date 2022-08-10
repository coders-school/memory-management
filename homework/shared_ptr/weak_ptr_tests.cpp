#include <gtest/gtest.h>
#include "weak_ptr.hpp"

class TestClass {
public:
    TestClass(int number = 2) noexcept
        : number_(number) {}
    int getNumber() {
        return number_;
    }

    int number_;
};

template class my::weak_ptr<TestClass>;

class weak_ptrFixture : public ::testing::Test {
public:
    ~weak_ptrFixture() {
        delete rawPtr;
    }

protected:
    my::weak_ptr<int> emptyWeakPtr;
    my::shared_ptr<int> emptySharedPtr;
    my::shared_ptr<int> sharedPtrToInt1{new int{10}};
    // my::weak_ptr<int> weakPtrToInt1{sharedPtrToInt1};
    TestClass* rawPtr{new TestClass{20}};
};

TEST_F(weak_ptrFixture, DefaultCtorTest) {
    // my::shared_ptr<int> emptySharedPtr2 = emptyWeakPtr.lock();
    // EXPECT_EQ(emptySharedPtr2.get(), nullptr);
}

// TEST_F(weak_ptrFixture, CopyCtorSharedPtrAsArgumentTest) {
//     my::weak_ptr<int> emptyWeakPtr2{emptySharedPtr};
//     my::shared_ptr<int> emptySharedPtr2 = emptyWeakPtr2.lock();
//     EXPECT_EQ(emptySharedPtr2.get(), nullptr);

//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
//     EXPECT_EQ(*sharedPtrToInt2, 10);
// }

// TEST_F(weak_ptrFixture, CopyCtorWeakPtrAsArgumentTest) {
//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
//     EXPECT_EQ(*sharedPtrToInt2, 10);
// }

// TEST_F(weak_ptrFixture, MoveCtorWeakPtrAsArgumentTest) {
//     my::weak_ptr<int> weakPtrToInt2{std::move(weakPtrToInt1)};
//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
//     EXPECT_EQ(sharedPtrToInt2.get(), nullptr);

//     my::shared_ptr<int> sharedPtrToInt3 = weakPtrToInt2.lock();
//     EXPECT_EQ(*sharedPtrToInt3, 10);
// }

// TEST_F(weak_ptrFixture, CopyOperatorWeakPtrAsArgumentTest) {
//     my::weak_ptr<int> weakPtrToInt2 = weakPtrToInt1;
//     EXPECT_EQ(weakPtrToInt2.use_count(), 1);

//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
//     EXPECT_EQ(*sharedPtrToInt2, 10);

//     my::shared_ptr<int> sharedPtrToInt3 = weakPtrToInt2.lock();
//     EXPECT_EQ(*sharedPtrToInt3, 10);
// }

// TEST_F(weak_ptrFixture, CopyOperatorSharedPtrAsArgument) {
//     my::weak_ptr<int> weakPtrToInt2 = sharedPtrToInt1;
//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt2.lock();
//     EXPECT_EQ(*sharedPtrToInt2, 10);
// }

// TEST_F(weak_ptrFixture, MoveOperatorWeakPtrAsArgumentAdded) {
//     my::weak_ptr<int> weakPtrToInt2 = std::move(weakPtrToInt1);
//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt2.lock();
//     EXPECT_EQ(*sharedPtrToInt2, 10);
//     my::shared_ptr<int> sharedPtrToInt3 = weakPtrToInt1.lock();
//     EXPECT_EQ(sharedPtrToInt3.get(), nullptr);
// }

// TEST_F(weak_ptrFixture, UseCountFunctionTest) {
//     EXPECT_EQ(emptyWeakPtr.use_count(), 0);
//     EXPECT_EQ(weakPtrToInt1.use_count(), 1);
// }

// TEST_F(weak_ptrFixture, ExpiredFunctionTest) {
//     EXPECT_EQ(emptyWeakPtr.expired(), true);
//     EXPECT_EQ(weakPtrToInt1.expired(), false);
// }

// TEST_F(weak_ptrFixture, LockFunctionTest) {
//     my::weak_ptr<int> emptyWeakPtr2{emptySharedPtr};
//     my::shared_ptr<int> emptySharedPtr2 = emptyWeakPtr2.lock();
//     EXPECT_EQ(emptySharedPtr2.get(), nullptr);

//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
//     EXPECT_EQ(*sharedPtrToInt2, 10);
// }

// TEST_F(weak_ptrFixture, ResetFunctionTest) {
//     weakPtrToInt1.reset();
//     my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
//     EXPECT_EQ(sharedPtrToInt2.get(), nullptr);
// }