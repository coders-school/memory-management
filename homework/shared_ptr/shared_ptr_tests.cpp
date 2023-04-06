#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "shared_ptr.hpp"

template class my::shared_ptr<int>;

class TestObject {
public:
    TestObject() = default;
    ~TestObject() noexcept { Destructor(); }

    MOCK_METHOD(void, Destructor, (), (noexcept));
};

TEST(shared_ptr, destructor) {
    auto ptr = new TestObject();
    auto smartPtr = my::shared_ptr<TestObject>(ptr);

    EXPECT_CALL(*ptr, Destructor);
}

TEST(shared_ptr, default_constructor) {
    auto smartPtr = my::shared_ptr<TestObject>();

    EXPECT_EQ(smartPtr.get(), nullptr);
}

TEST(shared_ptr, parametric_constructor) {
    auto ptr = new int{5};
    auto smartPtr = my::shared_ptr<int>(ptr);

    EXPECT_EQ(smartPtr.get(), ptr);
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

TEST(shared_ptr, move_ctor_with_nullptr) {
    auto otherSmartPtr = my::shared_ptr<TestObject>();

    my::shared_ptr<TestObject> smartPtr(std::move(otherSmartPtr));

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_ctor_with_ptr) {
    auto ptr = new TestObject();
    auto otherSmartPtr = my::shared_ptr<TestObject>(ptr);

    EXPECT_CALL(*ptr, Destructor);

    my::shared_ptr<TestObject> smartPtr(std::move(otherSmartPtr));

    EXPECT_EQ(smartPtr.get(), ptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_nullptr_to_nullptr) {
    auto smartPtr = my::shared_ptr<TestObject>();
    auto otherSmartPtr = my::shared_ptr<TestObject>();

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_nullptr_to_ptr) {
    auto otherPtr = new TestObject();
    auto smartPtr = my::shared_ptr<TestObject>();
    auto otherSmartPtr = my::shared_ptr<TestObject>(otherPtr);

    EXPECT_CALL(*otherPtr, Destructor);

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), otherPtr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_ptr_to_nullptr) {
    auto ptr = new TestObject();
    auto smartPtr = my::shared_ptr<TestObject>(ptr);
    auto otherSmartPtr = my::shared_ptr<TestObject>();

    EXPECT_CALL(*ptr, Destructor);

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), nullptr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
}

TEST(shared_ptr, move_assignment_from_ptr_to_ptr) {
    auto ptr = new TestObject();
    auto otherPtr = new TestObject();
    auto smartPtr = my::shared_ptr<TestObject>(ptr);
    auto otherSmartPtr = my::shared_ptr<TestObject>(otherPtr);

    EXPECT_CALL(*ptr, Destructor);
    EXPECT_CALL(*otherPtr, Destructor);

    smartPtr = std::move(otherSmartPtr);

    EXPECT_EQ(smartPtr.get(), otherPtr);
    EXPECT_EQ(otherSmartPtr.get(), nullptr);
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

TEST(shared_ptr, release) {
    auto ptr = new int{5};
    auto smartPtr = my::shared_ptr<int>(ptr);

    auto releasedPtr = smartPtr.release();
    EXPECT_EQ(releasedPtr, ptr);
    EXPECT_EQ(smartPtr.get(), nullptr);
    delete ptr;
}