#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

template class my::weak_ptr<int>;

class TestType {
public:
    TestType() = default;
    ~TestType() noexcept { Destructor(); }

    MOCK_METHOD(void, Destructor, (), (noexcept));
};

TEST(weak_ptr, destructor) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, default_constructor) {
    my::weak_ptr<TestType> weakPointer;

    EXPECT_EQ(weakPointer.get(), nullptr);
}

TEST(weak_ptr, copy_constructor) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);

    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    EXPECT_EQ(weakPointer.get(), pointer);
    EXPECT_EQ(sharedPointer.get(), pointer);
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, copy_assignment) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    my::weak_ptr<TestType> weakPointer;

    weakPointer = sharedPointer;

    EXPECT_EQ(weakPointer.get(), pointer);
    EXPECT_EQ(sharedPointer.get(), pointer);
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, move_constructor) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    auto otherWeakPointer = my::weak_ptr<TestType>(std::move(weakPointer));

    EXPECT_EQ(weakPointer.get(), nullptr);
    EXPECT_EQ(otherWeakPointer.get(), pointer);
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, move_assignment) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    auto otherWeakPointer = std::move(weakPointer);

    EXPECT_EQ(weakPointer.get(), nullptr);
    EXPECT_EQ(otherWeakPointer.get(), pointer);
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, reset) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    weakPointer.reset();

    EXPECT_EQ(weakPointer.expired(), true);
    EXPECT_EQ(weakPointer.get(), nullptr);
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, use_count) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    EXPECT_EQ(weakPointer.use_count(), 1);

    auto otherWeakPointer = my::weak_ptr<TestType>(weakPointer);

    EXPECT_EQ(weakPointer.use_count(), 1);
    EXPECT_EQ(otherWeakPointer.use_count(), 1);

    otherWeakPointer = std::move(weakPointer);

    EXPECT_EQ(otherWeakPointer.use_count(), 1);
    // EXPECT_EQ(weakPointer.use_count(), 1);  // -> should cause segmentation fault
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, expired) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    EXPECT_EQ(weakPointer.expired(), false);
    weakPointer.reset();
    EXPECT_EQ(weakPointer.expired(), true);
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, lock) {
    auto pointer = new TestType();
    auto sharedPointer = my::shared_ptr<TestType>(pointer);
    auto weakPointer = my::weak_ptr<TestType>(sharedPointer);

    auto otherSharedPointer = weakPointer.lock();

    EXPECT_EQ(otherSharedPointer.get(), pointer);
    EXPECT_EQ(otherSharedPointer.use_count(), 2);
    EXPECT_CALL(*pointer, Destructor);
}

TEST(weak_ptr, reference_cycle) {
    struct Node {
        my::shared_ptr<Node> child;
        my::weak_ptr<Node> parent;
    };

    auto root = my::shared_ptr<Node>(new Node);
    auto leaf = my::shared_ptr<Node>(new Node);

    root->child = leaf;
    leaf->parent = root;
}
