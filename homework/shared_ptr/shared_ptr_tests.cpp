#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>
#include "shared_ptr.hpp"

template class my::shared_ptr<int>;

class TestType {
public:
    TestType() = default;
    ~TestType() noexcept { Destructor(); }

    MOCK_METHOD(void, Destructor, (), (noexcept));
};

TEST(shared_ptr, destructor) {
    auto ptr = new TestType();
    auto smartPtr = my::shared_ptr<TestType>(ptr);

    EXPECT_CALL(*ptr, Destructor);
}

TEST(shared_ptr, default_constructor) {
    my::shared_ptr<TestType> smartPtr;

    EXPECT_EQ(smartPtr.get(), nullptr);
}

TEST(shared_ptr, parametric_constructor) {
    auto ptr = new int{5};
    auto smartPtr = my::shared_ptr<int>(ptr);

    EXPECT_EQ(smartPtr.get(), ptr);
}

TEST(shared_ptr, copy_constructor_with_nullptr) {
    my::shared_ptr<TestType> otherSmartPtr;
    my::shared_ptr<TestType> smartPtr(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, copy_constructor_with_ptr) {
    auto ptr = new TestType();
    auto otherSmartPtr = my::shared_ptr<TestType>(ptr);

    EXPECT_CALL(*ptr, Destructor);

    my::shared_ptr<TestType> smartPtr(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), ptr);
    EXPECT_EQ(otherSmartPtr.get(), ptr);
}

TEST(shared_ptr, copy_assignment_from_nullptr_to_nullptr) {
    auto smartPtr = my::shared_ptr<TestType>();
    auto otherSmartPtr = my::shared_ptr<TestType>();

    smartPtr = otherSmartPtr;

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, copy_assignment_from_ptr_to_nullptr) {
    my::shared_ptr<TestType> smartPtr;
    auto otherPtr = new TestType();
    auto otherSmartPtr = my::shared_ptr<TestType>(otherPtr);

    EXPECT_CALL(*otherPtr, Destructor);

    smartPtr = otherSmartPtr;

    EXPECT_EQ(smartPtr.get(), otherPtr);
    EXPECT_EQ(otherSmartPtr.get(), otherPtr);
}

TEST(shared_ptr, move_constructor_with_nullptr) {
    my::shared_ptr<TestType> otherSmartPtr;
    my::shared_ptr<TestType> smartPtr(std::move(otherSmartPtr));

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(smartPtr.use_count(), 1);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
    // EXPECT_EQ(otherSmartPtr.use_count(), 0);
}

TEST(shared_ptr, move_constructor_with_ptr) {
    auto otherPtr = new TestType();
    auto otherSmartPtr = my::shared_ptr<TestType>(otherPtr);

    EXPECT_CALL(*otherPtr, Destructor);

    my::shared_ptr<TestType> smartPtr(std::move(otherSmartPtr));

    EXPECT_EQ(smartPtr.get(), otherPtr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_nullptr_to_nullptr) {
    auto smartPtr = my::shared_ptr<TestType>();
    auto otherSmartPtr = my::shared_ptr<TestType>();

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_nullptr_to_ptr) {
    auto otherPtr = new TestType();
    auto smartPtr = my::shared_ptr<TestType>();
    auto otherSmartPtr = my::shared_ptr<TestType>(otherPtr);

    EXPECT_CALL(*otherPtr, Destructor);

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), otherPtr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_ptr_to_nullptr) {
    auto ptr = new TestType();
    auto smartPtr = my::shared_ptr<TestType>(ptr);
    auto otherSmartPtr = my::shared_ptr<TestType>();

    EXPECT_CALL(*ptr, Destructor);

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_ptr_to_ptr) {
    auto ptr = new TestType();
    auto otherPtr = new TestType();
    auto smartPtr = my::shared_ptr<TestType>(ptr);
    auto otherSmartPtr = my::shared_ptr<TestType>(otherPtr);

    EXPECT_CALL(*ptr, Destructor);
    EXPECT_CALL(*otherPtr, Destructor);

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), otherPtr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, reset) {
    auto ptr = new int{5};
    auto smartPtr = my::shared_ptr<int>(ptr);

    smartPtr.reset();
    EXPECT_EQ(smartPtr.get(), nullptr);

    smartPtr.reset(nullptr);
    EXPECT_EQ(smartPtr.get(), nullptr);

    auto otherPtr = new int{6};
    smartPtr.reset(otherPtr);
    EXPECT_EQ(smartPtr.get(), otherPtr);
}

TEST(shared_ptr, star_operator) {
    auto ptr = new int{5};
    auto smartPtr = my::shared_ptr<int>(ptr);

    EXPECT_EQ(*ptr, *smartPtr);
}

TEST(shared_ptr, arrow_operator) {
    struct Foo {
        int foo() { return 5; }
    };
    auto ptr = new Foo{};
    my::shared_ptr<Foo> fooPtr{ptr};

    EXPECT_EQ(fooPtr->foo(), 5);
}

TEST(shared_ptr, use_count) {
    auto smartPtr = my::shared_ptr<int>();

    EXPECT_EQ(smartPtr.use_count(), 1);

    auto otherPtr = new int{5};
    auto otherSmartPtr = my::shared_ptr<int>(otherPtr);

    smartPtr = otherSmartPtr;

    EXPECT_EQ(smartPtr.use_count(), 2);
    EXPECT_EQ(otherSmartPtr.use_count(), 2);

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.use_count(), 1);
    // EXPECT_EQ(otherSmartPtr.use_count(), 1);  // -> should cause undefined behaviour
}
