#include <string>
#include "gtest/gtest.h"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

TEST(sharedPointerTest, getFunctionShouldReturnRawPointer) {
    cs::shared_ptr<int> ptr(new int{1});
    int* raw_ptr = ptr.get();

    ASSERT_EQ(*raw_ptr, 1);
}

TEST(sharedPointerTest, starOperatorShouldReturnObject) {
    cs::shared_ptr<int> ptr(new int{1});

    ASSERT_EQ(*ptr, 1);
}

TEST(sharedPointerTest, arrowOperatorShouldCallPointedObjectMethods) {
    cs::shared_ptr<std::string> ala(new std::string{"Ala"});
    constexpr int size_of_ala = 3;

    ASSERT_EQ(ala->size(), size_of_ala);
}

TEST(sharedPointerTest, copyContructorShouldCopyPointer) {
    cs::shared_ptr<int> copied_ptr(new int{1});
    cs::shared_ptr<int> ptr(copied_ptr);

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(copied_ptr);
}

TEST(sharedPointerTest, MovingContructorShouldMovePointer) {
    cs::shared_ptr<int> moved_ptr(new int{1});
    cs::shared_ptr<int> ptr(std::move(moved_ptr));

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(!moved_ptr);
}

TEST(sharedPointerTest, copyAssignmentOperatorShouldCopyPointer) {
    cs::shared_ptr<int> copied_ptr(new int{1});
    cs::shared_ptr<int> ptr;
    ptr = copied_ptr;

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(copied_ptr);
}

TEST(sharedPointerTest, moveAssignmentOperatorShouldMovePointer) {
    cs::shared_ptr<int> copied_ptr(new int{1});
    cs::shared_ptr<int> ptr;
    ptr = std::move(copied_ptr);

    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(!copied_ptr);
}

TEST(sharedPointerTest, resetMethodShouldChangePointedObject) {
    cs::shared_ptr<int> ptr(new int{0});
    ptr.reset(new int{1});

    ASSERT_EQ(*ptr, 1);
}

TEST(sharedPointerTest, useCountMethodShouldReturnNumberOfReferences) {
    cs::shared_ptr<int> copied_ptr(new int{1});
    size_t numberOfUseCount = 1;
    ASSERT_EQ(copied_ptr.use_count(), numberOfUseCount);

    cs::shared_ptr<int> ptr(copied_ptr);
    ++numberOfUseCount;
    ASSERT_EQ(copied_ptr.use_count(), numberOfUseCount);
    ASSERT_EQ(ptr.use_count(), numberOfUseCount);
}

TEST(makeSharedTest, makeSharedCreatesTheSameValueAsSharedPtr) {
    cs::shared_ptr<int> someInt(new int{42});
    auto makeSomeInt = cs::make_shared<int>(42);
    ASSERT_EQ(*makeSomeInt, *someInt);
}
