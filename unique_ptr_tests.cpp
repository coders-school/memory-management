
#include <gtest/gtest.h>
#include "unique_ptr.hpp"

#include <iostream>
#include <string>

template <class T>
class unique_ptr;

template class my::unique_ptr<int>;  // for coverage?

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

class ClassForTestPurposes {
    const std::string message = "This is class";

public:
    const std::string give_me_class() {
        return message;
    }

    friend bool operator==(const ClassForTestPurposes& obj1, const ClassForTestPurposes& obj2) noexcept {
        return obj1.message == obj2.message;
    }
};

class MyUniquePtr : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {}
};

TEST(MyUniquePtr, create_with_nullptr) {
    my::unique_ptr<ClassForTestPurposes> a;
    my::unique_ptr<ClassForTestPurposes> b{nullptr};

    EXPECT_TRUE(a == nullptr);
    EXPECT_TRUE(b == nullptr);
}

TEST(MyUniquePtr, check_operator_indication) {
    my::unique_ptr<ClassForTestPurposes> a{new ClassForTestPurposes};
    EXPECT_EQ(a->give_me_class(), "This is class");
}

TEST(MyUniquePtr, disallow_copy_assigement) {
    my::unique_ptr<ClassForTestPurposes> a{new ClassForTestPurposes};
    // Not possible
    // my::unique_ptr<ClassForTestPurposes> b = a;
}

TEST(MyUniquePtr, disallow_copy_constructor) {
    my::unique_ptr<ClassForTestPurposes> a{nullptr};
    // Not possible
    // my::unique_ptr<ClassForTestPurposes> b{a};
}

TEST(MyUniquePtr, allow_move_constructor) {
    my::unique_ptr<ClassForTestPurposes> a{new ClassForTestPurposes};
    my::unique_ptr<ClassForTestPurposes> b{std::move(a)};

    EXPECT_TRUE(a == nullptr);
    EXPECT_TRUE(b != nullptr);
}

TEST(MyUniquePtr, allow_move_assignment_operator) {
    my::unique_ptr<ClassForTestPurposes> a{new ClassForTestPurposes};
    my::unique_ptr<ClassForTestPurposes> b;
    b = std::move(a);

    EXPECT_TRUE(a == nullptr);
    EXPECT_TRUE(b != nullptr);
}

TEST(MyUniquePtr, check_access_operator) {
    my::unique_ptr<ClassForTestPurposes> a{new ClassForTestPurposes};
    ClassForTestPurposes b;

    ClassForTestPurposes& x = *a;

    EXPECT_TRUE(x == b);
}

TEST(MyUniquePtr, check_get_method) {
    my::unique_ptr<ClassForTestPurposes> a(new ClassForTestPurposes);

    ClassForTestPurposes* res = a.get();

    EXPECT_TRUE(res->give_me_class() == "This is class");
}

TEST(MyUniquePtr, check_release_method) {
    my::unique_ptr<ClassForTestPurposes> a(new ClassForTestPurposes);

    ClassForTestPurposes* res = a.release();
    assert(a.get() == nullptr);
    assert(a == nullptr);

    EXPECT_TRUE(res->give_me_class() == "This is class");
    delete res;
}

class IFoo {
public:
    virtual ~IFoo() {}
    virtual void Create(std::string x) = 0;
    virtual void Destroy() = 0;
};

struct Foo {  // object to manage
    std::string x_;
    Foo(std::string x)
        : x_{x} { std::cout << "Foo... " << x_ << "\n"; }
    ~Foo() { std::cout << "~Foo... " << x_ << "\n"; }
};

TEST(MyUniquePtr, check_reset_method) {
    std::cout << "Creating new Foo...\n";
    my::unique_ptr<Foo> up(new Foo("First"));  // up owns the Foo pointer (deleter D)

    std::cout << "Replace owned Foo with a new Foo...\n";
    up.reset(new Foo("Second"));  // calls deleter for the old one

    std::cout << "Release and delete the owned Foo...\n";
    up.reset(nullptr);
}