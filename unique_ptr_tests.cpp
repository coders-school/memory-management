
#include <gtest/gtest.h>

#include "unique_ptr.hpp"

#include <iostream>
#include <string>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

class ClassForTestPurposes {
public:
    const std::string give_me_class() {
        return "This is class";
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
    //Not possible
    //my::unique_ptr<ClassForTestPurposes> b = a;
}

TEST(MyUniquePtr, disallow_copy_constructor) {
    my::unique_ptr<ClassForTestPurposes> a{nullptr};
    //Not possible
    //my::unique_ptr<ClassForTestPurposes> b{a};
}


