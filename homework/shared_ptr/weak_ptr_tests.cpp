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
    my::weak_ptr<TestClass> emptyWeakPtr;
    my::shared_ptr<TestClass> emptySharedPtr;
    my::shared_ptr<TestClass> sharedPtrToClass1{new TestClass{10}};
    my::weak_ptr<TestClass> weakPtrToClass1{sharedPtrToClass1};
    TestClass* rawPtr{new TestClass{20}};
};

TEST_F(weak_ptrFixture, DefaultCtorTest) {
    my::shared_ptr<TestClass> emptySharedPtr2 = emptyWeakPtr.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);
}

TEST_F(weak_ptrFixture, CopyCtorSharedPtrAsArgumentTest) {
    my::weak_ptr<TestClass> emptyWeakPtr2{emptySharedPtr};
    my::shared_ptr<TestClass> emptySharedPtr2 = emptyWeakPtr2.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);
    EXPECT_EQ(emptySharedPtr2.use_count(), 0);

    my::shared_ptr<TestClass> sharedPtrToClass2 = weakPtrToClass1.lock();
    EXPECT_EQ((*sharedPtrToClass2).getNumber(), 10);
    EXPECT_EQ(sharedPtrToClass2.use_count(), 2);
}

TEST_F(weak_ptrFixture, CopyCtorWeakPtrAsArgumentTest) {
    my::weak_ptr<TestClass> emptyWeakPtr2{emptyWeakPtr};
    my::shared_ptr<TestClass> emptySharedPtr2 = emptyWeakPtr2.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);
    EXPECT_EQ(emptySharedPtr2.use_count(), 0);

    my::weak_ptr<TestClass> weakPtrToClass2{weakPtrToClass1};
    my::shared_ptr<TestClass> sharedPtrToClass2 = weakPtrToClass2.lock();
    EXPECT_EQ((*sharedPtrToClass2).getNumber(), 10);
    EXPECT_EQ(sharedPtrToClass2.use_count(), 2);
}

TEST_F(weak_ptrFixture, MoveCtorWeakPtrAsArgumentTest) {
    my::weak_ptr<TestClass> emptyWeakPtr2{std::move(emptyWeakPtr)};
    my::shared_ptr<TestClass> emptySharedPtr2 = emptyWeakPtr2.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);
    EXPECT_EQ(emptySharedPtr2.use_count(), 0);

    my::weak_ptr<TestClass> weakPtrToClass2{std::move(weakPtrToClass1)};
    my::shared_ptr<TestClass> sharedPtrToClass2 = weakPtrToClass2.lock();
    EXPECT_EQ((*sharedPtrToClass2).getNumber(), 10);
    EXPECT_EQ(sharedPtrToClass2.use_count(), 2);
    my::shared_ptr<TestClass> sharedPtrToClass3 = weakPtrToClass1.lock();
    EXPECT_EQ(sharedPtrToClass3.get(), nullptr);
    EXPECT_EQ(sharedPtrToClass3.use_count(), 0);
}

TEST_F(weak_ptrFixture, CopyOperatorWeakPtrAsArgumentTest) {
    my::weak_ptr<TestClass> emptyWeakPtr2 = emptyWeakPtr;
    my::shared_ptr<TestClass> emptySharedPtr2 = emptyWeakPtr2.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);
    EXPECT_EQ(emptySharedPtr2.use_count(), 0);

    my::weak_ptr<TestClass> weakPtrToClass2;
    weakPtrToClass2 = weakPtrToClass1;
    my::shared_ptr<TestClass> sharedPtrToClass2 = weakPtrToClass2.lock();
    EXPECT_EQ((*sharedPtrToClass2).getNumber(), 10);
    EXPECT_EQ(sharedPtrToClass2.use_count(), 2);

    my::shared_ptr<TestClass> sharedPtrToClass4{new TestClass{40}};
    my::weak_ptr<TestClass> weakPtrToClass3{sharedPtrToClass4};
    my::weak_ptr<TestClass> weakPtrToClass4;
    weakPtrToClass3 = weakPtrToClass4;
    my::shared_ptr<TestClass> sharedPtrToClass5 = weakPtrToClass3.lock();
    EXPECT_EQ(sharedPtrToClass5.get(), nullptr);
    EXPECT_EQ(sharedPtrToClass5.use_count(), 0);

    my::shared_ptr<TestClass> sharedPtrToClass6{new TestClass{60}};
    my::weak_ptr<TestClass> weakPtrToClass5{sharedPtrToClass6};
    my::shared_ptr<TestClass> sharedPtrToClass7{new TestClass{70}};
    my::weak_ptr<TestClass> weakPtrToClass6{sharedPtrToClass6};
    weakPtrToClass5 = weakPtrToClass6;
    my::shared_ptr<TestClass> sharedPtrToClass8 = weakPtrToClass5.lock();
    EXPECT_EQ((*sharedPtrToClass8).getNumber(), 60);
    EXPECT_EQ(sharedPtrToClass8.use_count(), 2);
}

TEST_F(weak_ptrFixture, CopyOperatorSharedPtrAsArgument) {
    my::weak_ptr<TestClass> emptyWeakPtr2 = emptySharedPtr;
    my::shared_ptr<TestClass> emptySharedPtr2 = emptyWeakPtr2.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);
    EXPECT_EQ(emptySharedPtr2.use_count(), 0);

    my::weak_ptr<TestClass> weakPtrToClass2;
    weakPtrToClass2 = sharedPtrToClass1;
    my::shared_ptr<TestClass> sharedPtrToClass2 = weakPtrToClass2.lock();
    EXPECT_EQ((*sharedPtrToClass2).getNumber(), 10);
    EXPECT_EQ(sharedPtrToClass2.use_count(), 2);

    my::shared_ptr<TestClass> sharedPtrToClass4{new TestClass{40}};
    my::weak_ptr<TestClass> weakPtrToClass3{sharedPtrToClass4};
    my::shared_ptr<TestClass> emptySharedPtr3;
    weakPtrToClass3 = emptySharedPtr3;
    my::shared_ptr<TestClass> emptySharedPtr4 = weakPtrToClass3.lock();
    EXPECT_EQ(emptySharedPtr4.get(), nullptr);
    EXPECT_EQ(emptySharedPtr4.use_count(), 0);

    my::shared_ptr<TestClass> sharedPtrToClass5{new TestClass{50}};
    my::weak_ptr<TestClass> weakPtrToClass4{sharedPtrToClass5};
    my::shared_ptr<TestClass> sharedPtrToClass6{new TestClass{60}};
    weakPtrToClass4 = sharedPtrToClass6;
    my::shared_ptr<TestClass> sharedPtrToClass7 = weakPtrToClass4.lock();
    EXPECT_EQ((*sharedPtrToClass6).getNumber(), 60);
    EXPECT_EQ(sharedPtrToClass6.use_count(), 2);
    EXPECT_EQ((*sharedPtrToClass7).getNumber(), 60);
    EXPECT_EQ(sharedPtrToClass2.use_count(), 2);
}

// TEST_F(weak_ptrFixture, MoveOperatorWeakPtrAsArgument) {
// }

TEST_F(weak_ptrFixture, UseCountFunctionTest) {
    EXPECT_EQ(emptyWeakPtr.use_count(), 0);
    EXPECT_EQ(weakPtrToClass1.use_count(), 1);
}

TEST_F(weak_ptrFixture, ExpiredFunctionTest) {
    EXPECT_EQ(emptyWeakPtr.expired(), true);
    EXPECT_EQ(weakPtrToClass1.expired(), false);
}

TEST_F(weak_ptrFixture, LockFunctionTest) {
    auto emptySharedPointer2 = emptyWeakPtr.lock();
    EXPECT_EQ(emptySharedPtr.get(), nullptr);
}

TEST_F(weak_ptrFixture, ResetFunctionTest) {
    weakPtrToClass1.reset();
    my::shared_ptr<TestClass> sharedPtrToClass2 = weakPtrToClass1.lock();
    EXPECT_EQ(sharedPtrToClass2.get(), nullptr);
}