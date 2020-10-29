#include "shared.hpp"

#include <gtest/gtest.h>

class SharedTest : public ::testing::Test
{
   protected:
    int defaultValue{5};
    int anotherValue{10};
    cs::shared_ptr<int> defaultShared{new int{defaultValue}};
    void release() {
    throw std::exception();
}
};

TEST_F(SharedTest, defaultSharedShouldBeNullptr)
{
    cs::shared_ptr<int> test;
    EXPECT_EQ(test.get(), nullptr);
}

TEST_F(SharedTest, sharedWhenCreatedFromRawPtrShouldAllocateControlBlock)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(test.use_count(), 1);
}

TEST_F(SharedTest, sharedWhenCopiedShouldIncreaseRefCount)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    cs::shared_ptr<int> test2(test);
    EXPECT_EQ(test.use_count(), 2);
    EXPECT_EQ(test2.use_count(), 2);
}

TEST_F(SharedTest, sharedDestructorShouldDecreaseRefCount)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    {
        cs::shared_ptr<int> test2(test);
        EXPECT_EQ(test.use_count(), 2);
        EXPECT_EQ(test2.use_count(), 2);
    }
    EXPECT_EQ(test.use_count(), 1);
}

TEST_F(SharedTest, sharedMoveCtorShouldNotIncreaseRefCounter)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(test.use_count(), 1);
    cs::shared_ptr<int> test2(std::move(test));
    EXPECT_EQ(test2.use_count(), 1);
    cs::shared_ptr<int> test3(cs::shared_ptr<int>(new int{defaultValue}));
    EXPECT_EQ(test3.use_count(), 1);
}

TEST_F(SharedTest, sharedMoveAssignmentShouldNotIncreaseRefCounter)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(test.use_count(), 1);
    cs::shared_ptr<int> test2 = std::move(test);
    EXPECT_EQ(test2.use_count(), 1);
}

TEST_F(SharedTest, sharedCopyAssignmentShouldIncreaseRefCounter)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(test.use_count(), 1);
    cs::shared_ptr<int> test2;
    test2 = test;
    EXPECT_EQ(test2.use_count(), 2);
    EXPECT_EQ(test.use_count(), 2);
}

TEST_F(SharedTest, sharedCopyAssignmentShouldReleaseMemoryIfSharedRefIs0)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    cs::shared_ptr<int> test2(new int{anotherValue});
    EXPECT_EQ(test.use_count(), 1);
    EXPECT_EQ(test2.use_count(), 1);
    test2 = test;
    EXPECT_EQ(test.use_count(), 2);
    EXPECT_EQ(test2.use_count(), 2);
}

TEST_F(SharedTest, sharedDereferenceShouldReturnTheObject)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(*test, defaultValue);
}

TEST_F(SharedTest, sharedDereferenceShouldChangeValueWhenAssignedTo)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(*test, defaultValue);
    *test = anotherValue;
    EXPECT_EQ(*test, anotherValue);
}

TEST_F(SharedTest, sharedArrowOperatorShoulCallFunctionsOfAssignedObject)
{
    struct foo {
        void use(){};
    };
    cs::shared_ptr<foo> test(new foo());
    test->use();
}

TEST_F(SharedTest, sharedResetShouldChangeManagedObject)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(*test, defaultValue);
    test.reset(new int{anotherValue});
    EXPECT_EQ(*test, anotherValue);
}

TEST_F(SharedTest, sharedDefaultResetShouldSetToNullptr)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(*test, defaultValue);
    test.reset();
    EXPECT_EQ(test.get(), nullptr);
}

TEST_F(SharedTest, sharedOperatorBoolShouldCheckIfManagedObjectIsNotNullptr)
{
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(test, true);
    test.reset();
    EXPECT_EQ(test, false);
}

TEST_F(SharedTest, sharedCanBeCreatedWithCustomDeleter) {
    int arraySize{10};
    auto arrayDeleter = [](int* data) { delete [] data; };
    cs::shared_ptr<int> test(new int[arraySize]{}, arrayDeleter);
}

TEST_F(SharedTest, customDeleterShouldNotChangeSize) {
    auto arrayDeleter = [](int* data) { delete [] data; };
    cs::shared_ptr<int> customShared(new int[defaultValue]{}, arrayDeleter);
    EXPECT_EQ(sizeof(customShared), sizeof(defaultShared));
}

TEST_F(SharedTest, sharedShouldThrowExcepetionWhenCreatedFromHangingWeakPtr) {
    cs::weak_ptr<int> dangling{defaultShared};
    defaultShared.reset();
    EXPECT_THROW(cs::shared_ptr<int> shared{dangling}, cs::bad_weak_ptr);
}

TEST_F(SharedTest, sharedShouldThrowExceptionWhenCreatedFromEmptyWeakPtr) {
    cs::weak_ptr<int> emptyWeak{};
    EXPECT_THROW(cs::shared_ptr<int> shared{emptyWeak}, cs::bad_weak_ptr);
}

TEST_F(SharedTest, resetCanBeUseWithOneArgument) {
    defaultShared.reset(new int{anotherValue});
    EXPECT_EQ(*defaultShared, anotherValue);
}

TEST_F(SharedTest, resetCanBeUseWithCustomDeleter) {
    auto customDeleter = [](int* data) { delete [] data; };
    defaultShared.reset(new int[defaultValue]{}, customDeleter);
}

TEST_F(SharedTest, sharedPtrCanBeCopiedFromEmptySharedPtr) {
    cs::shared_ptr<int> emptyShared1{};
    cs::shared_ptr<int> emptyShared2{};
    emptyShared1 = emptyShared2;
    EXPECT_EQ(emptyShared1.get(), nullptr);
}
