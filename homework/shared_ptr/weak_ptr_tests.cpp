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
    auto ptr = new TestType();
    auto smartPtr = my::weak_ptr<TestType>(ptr);

    EXPECT_CALL(*ptr, Destructor);
    delete ptr;
}

TEST(weak_ptr, default_constructor) {
    my::weak_ptr<TestType> smartPtr;

    EXPECT_EQ(smartPtr.get(), nullptr);
}

// TEST(weak_ptr, parametric_constructor) {
//     auto ptr = new int{5};
//     auto smartPtr = my::weak_ptr<int>(ptr);

//     EXPECT_EQ(smartPtr.get(), ptr);
// }

// TEST(weak_ptr, copy_constructor_with_nullptr) {
//     my::weak_ptr<TestType> otherSmartPtr;
//     my::weak_ptr<TestType> smartPtr(otherSmartPtr);

//     EXPECT_EQ(smartPtr.get(), nullptr);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
// }

// TEST(weak_ptr, copy_constructor_with_ptr) {
//     auto ptr = new TestType();
//     auto otherSmartPtr = my::weak_ptr<TestType>(ptr);

//     EXPECT_CALL(*ptr, Destructor);

//     my::weak_ptr<TestType> smartPtr(otherSmartPtr);

//     EXPECT_EQ(smartPtr.get(), ptr);
//     EXPECT_EQ(otherSmartPtr.get(), ptr);
// }

// TEST(weak_ptr, copy_assignment_from_nullptr_to_nullptr) {
//     auto smartPtr = my::weak_ptr<TestType>();
//     auto otherSmartPtr = my::weak_ptr<TestType>();

//     smartPtr = otherSmartPtr;

//     EXPECT_EQ(smartPtr.get(), nullptr);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
// }

// TEST(weak_ptr, copy_assignment_from_ptr_to_nullptr) {
//     my::weak_ptr<TestType> smartPtr;
//     auto otherPtr = new TestType();
//     auto otherSmartPtr = my::weak_ptr<TestType>(otherPtr);

//     EXPECT_CALL(*otherPtr, Destructor);

//     smartPtr = otherSmartPtr;

//     EXPECT_EQ(smartPtr.get(), otherPtr);
//     EXPECT_EQ(otherSmartPtr.get(), otherPtr);
// }

// TEST(weak_ptr, move_constructor_with_nullptr) {
//     my::weak_ptr<TestType> otherSmartPtr;
//     my::weak_ptr<TestType> smartPtr(std::move(otherSmartPtr));

//     EXPECT_EQ(smartPtr.get(), nullptr);
//     EXPECT_EQ(smartPtr.use_count(), 1);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
//     // EXPECT_EQ(otherSmartPtr.use_count(), 0);  // -> should cause segmentation fault
// }

// TEST(weak_ptr, move_constructor_with_ptr) {
//     auto otherPtr = new TestType();
//     auto otherSmartPtr = my::weak_ptr<TestType>(otherPtr);

//     EXPECT_CALL(*otherPtr, Destructor);

//     my::weak_ptr<TestType> smartPtr(std::move(otherSmartPtr));

//     EXPECT_EQ(smartPtr.get(), otherPtr);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
// }

// TEST(weak_ptr, move_assignment_from_nullptr_to_nullptr) {
//     auto smartPtr = my::weak_ptr<TestType>();
//     auto otherSmartPtr = my::weak_ptr<TestType>();

//     smartPtr = std::move(otherSmartPtr);

//     EXPECT_EQ(smartPtr.get(), nullptr);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
// }

// TEST(weak_ptr, move_assignment_from_nullptr_to_ptr) {
//     auto otherPtr = new TestType();
//     auto smartPtr = my::weak_ptr<TestType>();
//     auto otherSmartPtr = my::weak_ptr<TestType>(otherPtr);

//     EXPECT_CALL(*otherPtr, Destructor);

//     smartPtr = std::move(otherSmartPtr);

//     EXPECT_EQ(smartPtr.get(), otherPtr);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
// }

// TEST(weak_ptr, move_assignment_from_ptr_to_nullptr) {
//     auto ptr = new TestType();
//     auto smartPtr = my::weak_ptr<TestType>(ptr);
//     auto otherSmartPtr = my::weak_ptr<TestType>();

//     EXPECT_CALL(*ptr, Destructor);

//     smartPtr = std::move(otherSmartPtr);

//     EXPECT_EQ(smartPtr.get(), nullptr);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
// }

// TEST(weak_ptr, move_assignment_from_ptr_to_ptr) {
//     auto ptr = new TestType();
//     auto otherPtr = new TestType();
//     auto smartPtr = my::weak_ptr<TestType>(ptr);
//     auto otherSmartPtr = my::weak_ptr<TestType>(otherPtr);

//     EXPECT_CALL(*ptr, Destructor);
//     EXPECT_CALL(*otherPtr, Destructor);

//     smartPtr = std::move(otherSmartPtr);

//     EXPECT_EQ(smartPtr.get(), otherPtr);
//     EXPECT_EQ(otherSmartPtr.get(), nullptr);
// }

// TEST(weak_ptr, reset) {
//     auto ptr = new int{5};
//     auto smartPtr = my::weak_ptr<int>(ptr);

//     smartPtr.reset();
//     EXPECT_EQ(smartPtr.get(), nullptr);

//     smartPtr.reset(nullptr);
//     EXPECT_EQ(smartPtr.get(), nullptr);

//     auto otherPtr = new int{6};
//     smartPtr.reset(otherPtr);
//     EXPECT_EQ(smartPtr.get(), otherPtr);
// }

// TEST(weak_ptr, use_count) {
//     auto smartPtr = my::weak_ptr<int>();

//     EXPECT_EQ(smartPtr.use_count(), 1);

//     auto otherPtr = new int{5};
//     auto otherSmartPtr = my::weak_ptr<int>(otherPtr);

//     smartPtr = otherSmartPtr;

//     EXPECT_EQ(smartPtr.use_count(), 2);
//     EXPECT_EQ(otherSmartPtr.use_count(), 2);

//     smartPtr = std::move(otherSmartPtr);

//     EXPECT_EQ(smartPtr.use_count(), 1);
//     // EXPECT_EQ(otherSmartPtr.use_count(), 1);  // -> should cause segmentation fault
// }

TEST(weak_ptr, reference_cycle) {
    struct Node {
        my::shared_ptr<Node> child;
        my::shared_ptr<Node> parent;
    };

    auto root = my::shared_ptr<Node>(new Node);
    auto leaf = my::shared_ptr<Node>(new Node);

    root->child = leaf;
    leaf->parent = root;
}