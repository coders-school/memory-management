#include "gtest/gtest.h"
#include "shared_ptr.hpp"
#include <string>

TEST(sharedPointerTest, getFunctionShouldReturnRawPointer) {
    shared_ptr<int> ptr(new int{1});
    int* raw_ptr = ptr.get();

    ASSERT_EQ(*raw_ptr, 1);
}

TEST(sharedPointerTest, starOperatorShouldReturnObject) {
    shared_ptr<int> ptr(new int{1});

    ASSERT_EQ(*ptr, 1);
}

TEST(sharedPointerTest, arrowOperatorShouldCallPointedObjectMethods) {
    shared_ptr<std::string> ala(new std::string{"Ala"});
    constexpr int size_of_ala = 3;

    ASSERT_EQ(ala->size(), size_of_ala);
}

TEST(sharedPointerTest, copyContructorShouldCopyPointer) {
    shared_ptr<int> copied_ptr(new int{1});
    shared_ptr<int> ptr(copied_ptr);

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(copied_ptr);
}

TEST(sharedPointerTest, MovingContructorShouldMovePointer) {
    shared_ptr<int> moved_ptr(new int{1});
    shared_ptr<int> ptr(std::move(moved_ptr));

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(!moved_ptr);
}

TEST(sharedPointerTest, copyAssignmentOperatorShouldCopyPointer) {
    shared_ptr<int> copied_ptr(new int{1});
    shared_ptr<int> ptr;
    ptr = copied_ptr;

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(copied_ptr);
}

TEST(sharedPointerTest, moveAssignmentOperatorShouldMovePointer) {
    shared_ptr<int> copied_ptr(new int{1});
    shared_ptr<int> ptr;
    ptr = std::move(copied_ptr);

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(!copied_ptr);
}

TEST(sharedPointerTest, resetMethodShouldChangePointedObject) {
    shared_ptr<int> ptr(new int{0});
    ptr.reset(new int{1});

    ASSERT_EQ(*ptr, 1);
}

TEST(sharedPointerTest, useCountMethodShouldReturnNumberOfReferences) {
    shared_ptr<int> copied_ptr(new int{1});
    ASSERT_EQ(copied_ptr.use_count(), 1);

    shared_ptr<int> ptr(copied_ptr);
    ASSERT_EQ(copied_ptr.use_count(), 2);
    ASSERT_EQ(ptr.use_count(), 2);
}
