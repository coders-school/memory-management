#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../UniquePointer.hpp"

class TestObject {
public:
    TestObject() = default;
    ~TestObject() { Destructor(); }

    MOCK_METHOD(void, Destructor, (), (noexcept));
};

TEST(unique_ptr, destructor) {
    auto ptr = new TestObject();
    auto smartPtr = UniquePointer<TestObject>(ptr);

    EXPECT_CALL(*ptr, Destructor).Times(1);
}

TEST(unique_ptr, default_constructor) {
    auto smartPtr = UniquePointer<TestObject>();

    EXPECT_EQ(nullptr, smartPtr.get());
}

TEST(unique_ptr, parametric_constructor) {
    auto ptr = new int{5};
    auto smartPtr = UniquePointer<int>(ptr);

    EXPECT_EQ(ptr, smartPtr.get());
}

TEST(unique_ptr, get) {
    auto ptr = new int{5};
    auto smartPtr = UniquePointer<int>(ptr);

    EXPECT_EQ(ptr, smartPtr.get());
}

TEST(unique_ptr, reset) {
    auto ptr = new int{5};
    auto smartPtr = UniquePointer<int>(ptr);

    smartPtr.reset(nullptr);
    EXPECT_EQ(nullptr, smartPtr.get());

    auto otherPtr = new int{6};
    smartPtr.reset(otherPtr);
    EXPECT_EQ(otherPtr, smartPtr.get());
}

TEST(unique_ptr, move_assignment_from_nullptr_to_nullptr) {
    auto testedSmartPtr = UniquePointer<TestObject>();
    auto otherSmartPtr = UniquePointer<TestObject>();

    testedSmartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(testedSmartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(unique_ptr, move_assignment_from_nullptr_to_ptr) {
    auto ptr = new TestObject();
    auto testedSmartPtr = UniquePointer<TestObject>();
    auto otherSmartPtr = UniquePointer<TestObject>(ptr);

    EXPECT_CALL(*ptr, Destructor).Times(1);

    testedSmartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(testedSmartPtr.get(), ptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(unique_ptr, move_assignment_from_ptr_to_nullptr) {
    auto ptr = new TestObject();
    auto testedSmartPtr = UniquePointer<TestObject>(ptr);
    auto otherSmartPtr = UniquePointer<TestObject>();

    EXPECT_CALL(*ptr, Destructor).Times(1);

    testedSmartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(testedSmartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(unique_ptr, move_assignment_from_ptr_to_ptr) {
    auto ptr = new TestObject();
    auto ptr2 = new TestObject();
    auto testedSmartPtr = UniquePointer<TestObject>(ptr);
    auto otherSmartPtr = UniquePointer<TestObject>(ptr2);

    EXPECT_CALL(*ptr, Destructor).Times(1);
    EXPECT_CALL(*ptr2, Destructor).Times(1);

    testedSmartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(testedSmartPtr.get(), ptr2);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(unique_ptr, move_ctor_with_nullptr) {
    auto otherSmartPtr = UniquePointer<TestObject>();

    UniquePointer<TestObject> testedSmartPtr(std::move(otherSmartPtr));

    EXPECT_EQ(testedSmartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(unique_ptr, move_ctor_with_ptr) {
    auto ptr = new TestObject();
    auto otherSmartPtr = UniquePointer<TestObject>(ptr);

    EXPECT_CALL(*ptr, Destructor).Times(1);

    UniquePointer<TestObject> testedSmartPtr(std::move(otherSmartPtr));

    EXPECT_EQ(testedSmartPtr.get(), ptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(unique_ptr, star_operator) {
    auto ptr = new int{5};
    auto smartPtr = UniquePointer<int>(ptr);

    EXPECT_EQ(*ptr, *smartPtr.get());
}
