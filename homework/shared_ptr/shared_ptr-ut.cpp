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
    constexpr size_t useCountBeforeCopy = 1;
    constexpr size_t useCountAfterCopy = 2;
    cs::shared_ptr<int> copied_ptr(new int{1});
    ASSERT_EQ(copied_ptr.use_count(), useCountBeforeCopy);
    cs::shared_ptr<int> ptr(copied_ptr);

    ASSERT_EQ(ptr.use_count(), useCountAfterCopy);
    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(copied_ptr);
}

TEST(sharedPointerTest, MovingContructorShouldMovePointer) {
    cs::shared_ptr<int> moved_ptr(new int{1});
    cs::shared_ptr<int> ptr(std::move(moved_ptr));

    ASSERT_EQ(*ptr, 1);
    ASSERT_FALSE(moved_ptr);
}

TEST(sharedPointerTest, copyAssignmentOperatorShouldCopyPointer) {
    constexpr size_t useCountBeforeCopy = 1;
    constexpr size_t useCountAfterCopy = 2;
    cs::shared_ptr<int> copied_ptr(new int{1});
    cs::shared_ptr<int> ptr{new int{2}};
    ASSERT_EQ(copied_ptr.use_count(), useCountBeforeCopy);
    ptr = copied_ptr;

    ASSERT_EQ(copied_ptr.use_count(), useCountAfterCopy);
    ASSERT_EQ(*ptr, 1);
    ASSERT_TRUE(copied_ptr);
}

TEST(sharedPointerTest, moveAssignmentOperatorShouldMovePointer) {
    cs::shared_ptr<int> copied_ptr(new int{1});
    cs::shared_ptr<int> ptr{new int{2}};
    ptr = std::move(copied_ptr);

    ASSERT_EQ(*ptr, 1);
    ASSERT_FALSE(copied_ptr);
}

TEST(sharedPointerTest, resetMethodShouldChangePointedObject) {
    constexpr size_t numberOfUseCount = 1;
    cs::shared_ptr<int> ptr(new int{0});
    ASSERT_EQ(ptr.use_count(), numberOfUseCount);
    ptr.reset(new int{1});
    ASSERT_EQ(ptr.use_count(), numberOfUseCount);
    ASSERT_EQ(*ptr, 1);
}

TEST(sharedPointerTest, resetMethodWithoutArgumentsShouldChangePointedObject) {
    constexpr size_t useCountBeforeReset = 2;
    constexpr size_t useCountAfterReset = 0;
    cs::shared_ptr<int> ptr(new int{0});
    cs::shared_ptr<int> ptr_doing_nothing(ptr);
    ASSERT_EQ(ptr.use_count(), useCountBeforeReset);
    ptr.reset();
    ASSERT_EQ(ptr.use_count(), useCountAfterReset);
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(makeSharedTest, makeSharedCreatesTheSameValueAsSharedPtr) {
    constexpr int value = 42;
    cs::shared_ptr<int> someInt(new int{value});
    auto makeSomeInt = cs::make_shared<int>(value);
    ASSERT_EQ(*makeSomeInt, *someInt);
}

TEST(makeSharedTest, makeSharedShouldNotAfectCopying) {
    constexpr size_t useCountBeforeCopy = 1;
    constexpr size_t useCountAfterCopy = 2;
    const std::string str = "string";
    auto copied_ptr = cs::make_shared<std::string>(str);
    ASSERT_EQ(copied_ptr.use_count(), useCountBeforeCopy);
    auto ptr(copied_ptr);
    ASSERT_EQ(*ptr, str);
    ASSERT_EQ(ptr.use_count(), useCountAfterCopy);
}

TEST(makeSharedTest, makeSharedShouldNotAfectMoving) {
    const std::string str = "string";
    auto moved_ptr = cs::make_shared<std::string>(str);
    auto ptr(std::move(moved_ptr));
    ASSERT_EQ(*ptr, str);
}
