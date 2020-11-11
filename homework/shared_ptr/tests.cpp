#include <gtest/gtest.h>

#include <memory>
#include "MakeShared.hpp"
#include "SharedPointer.hpp"
#include "WeakPointer.hpp"

constexpr int testValue = 5;
constexpr int testValue2 = 44;
constexpr int noReferences = 0;
constexpr int oneReference = 1;
constexpr int twoReferences = 2;
constexpr int threeReferences = 3;

class TestClass {
public:
    int testFunction() {
        return testValue;
    }
};

class SharedPointerTest : public ::testing::Test {
protected:
    SharedPointerTest() : s_ptr(new int{testValue}), rs_ptr(new int{testValue}) {}
    SharedPointer<int> s_ptr;
    std::shared_ptr<int> rs_ptr;
};

class WeakPointerTest : public ::testing::Test {
protected:
    WeakPointerTest() : ss_ptr(new int{testValue}), rss_ptr(new int{testValue}) {}
    SharedPointer<int> ss_ptr;
    WeakPointer<int> w_ptr{ss_ptr};
    std::shared_ptr<int> rss_ptr;
    std::weak_ptr<int> rw_ptr{rss_ptr};
};

class ControlBlockTest : public ::testing::Test {
protected:
    ControlBlock<int> testControlBlock;
};

TEST_F(SharedPointerTest, shouldCreateSharedPointerFromWeakPointer) {
    WeakPointer<int> w_ptr{s_ptr};
    SharedPointer<int> ss_ptr{w_ptr};

    ASSERT_EQ(ss_ptr.get(), s_ptr.get());

    std::weak_ptr<int> rw_ptr{rs_ptr};
    std::shared_ptr<int> rss_ptr{rw_ptr};

    ASSERT_EQ(rss_ptr.get(), rs_ptr.get());
}

TEST_F(SharedPointerTest, shouldCopySharedPointer) {
    auto newPtr(s_ptr);
    auto newPtr1 = s_ptr;

    ASSERT_EQ(*s_ptr, *newPtr);
    ASSERT_EQ(*s_ptr, *newPtr1);
    ASSERT_EQ(s_ptr.use_count(), threeReferences);

    auto newRPtr(rs_ptr);
    auto newRPtr1 = rs_ptr;

    ASSERT_EQ(*rs_ptr, *newRPtr);
    ASSERT_EQ(*rs_ptr, *newRPtr1);
    ASSERT_EQ(rs_ptr.use_count(), threeReferences);
}

TEST_F(SharedPointerTest, shouldMoveSharedPointer) {
    auto newPtr(std::move(s_ptr));
    ASSERT_EQ(*newPtr, testValue);
    ASSERT_EQ(newPtr.use_count(), oneReference);

    auto newRPtr(std::move(rs_ptr));
    ASSERT_EQ(*newRPtr, testValue);
    ASSERT_EQ(newRPtr.use_count(), oneReference);
}

TEST_F(SharedPointerTest, shouldUseCopyAssingnmentOperatorSharedPointer) {
    SharedPointer<int> newPtr;
    newPtr = s_ptr;
    ASSERT_EQ(*s_ptr, testValue);
    ASSERT_EQ(s_ptr.use_count(), twoReferences);

    std::shared_ptr<int> newRPtr;
    newRPtr = rs_ptr;
    ASSERT_EQ(*rs_ptr, testValue);
    ASSERT_EQ(rs_ptr.use_count(), twoReferences);
}

TEST_F(SharedPointerTest, shouldUseMoveAssingnmentOperatorSharedPointer) {
    SharedPointer<int> newPtr;
    newPtr = std::move(s_ptr);
    ASSERT_EQ(*newPtr, testValue);
    ASSERT_EQ(newPtr.use_count(), oneReference);
    ASSERT_EQ(s_ptr.get(), nullptr);

    std::shared_ptr<int> newRPtr;
    newRPtr = std::move(rs_ptr);
    ASSERT_EQ(*newRPtr, testValue);
    ASSERT_EQ(newRPtr.use_count(), oneReference);
    ASSERT_EQ(rs_ptr.get(), nullptr);
}
TEST_F(SharedPointerTest, shouldResetSharedPtrNoArgumentCase) {
    s_ptr.reset();
    ASSERT_EQ(s_ptr.get(), nullptr);

    rs_ptr.reset();
    ASSERT_EQ(rs_ptr.get(), nullptr);
}

TEST_F(SharedPointerTest, shouldResetSharedPtrWithArgumentCase) {
    auto newPtr(s_ptr);
    auto newPtr1 = s_ptr;
    ASSERT_EQ(s_ptr.use_count(), threeReferences);
    s_ptr.reset(new int(testValue2));
    ASSERT_EQ(newPtr.use_count(), twoReferences);
    ASSERT_EQ(s_ptr.use_count(), oneReference);
    ASSERT_EQ(*s_ptr, testValue2);

    auto newRPtr(rs_ptr);
    auto newRPtr1 = rs_ptr;
    ASSERT_EQ(rs_ptr.use_count(), threeReferences);
    rs_ptr.reset(new int(testValue2));
    ASSERT_EQ(newRPtr.use_count(), twoReferences);
    ASSERT_EQ(rs_ptr.use_count(), oneReference);
    ASSERT_EQ(*rs_ptr, testValue2);
}

TEST_F(SharedPointerTest, shouldReturnUseCountOfSharedPointer) {
    auto newPtr = s_ptr;

    ASSERT_EQ(s_ptr.use_count(), twoReferences);

    auto newRPtr = rs_ptr;

    ASSERT_EQ(rs_ptr.use_count(), twoReferences);
}

TEST_F(SharedPointerTest, shouldUseDereferenceOperatorOfSharedPointer) {
    ASSERT_EQ(*s_ptr, testValue);
    ASSERT_EQ(*rs_ptr, testValue);
}

TEST_F(SharedPointerTest, shouldUseArrowOperatorOfSharedPointer) {
    SharedPointer<TestClass> s_ptr(new TestClass{});

    ASSERT_EQ(s_ptr->testFunction(), testValue);

    std::shared_ptr<TestClass> rs_ptr(new TestClass{});

    ASSERT_EQ(rs_ptr->testFunction(), testValue);
}

TEST_F(SharedPointerTest, shouldReturnBoolWhenUsingBoolOperator) {
    SharedPointer<int> s_ptrNew;

    ASSERT_TRUE(s_ptr);
    ASSERT_FALSE(s_ptrNew);

    std::shared_ptr<int> rs_ptrRNew;

    ASSERT_TRUE(rs_ptr);
    ASSERT_FALSE(rs_ptrRNew);
}

TEST_F(WeakPointerTest, shouldReturnUseCountEqualTo0WhenCreatedByDefault) {
    WeakPointer<int> test_w_ptr;
    ASSERT_EQ(test_w_ptr.use_count(), noReferences);

    std::weak_ptr<int> test_rw_ptr;
    ASSERT_EQ(test_rw_ptr.use_count(), noReferences);
}

TEST_F(WeakPointerTest, shouldReturnUseCountEqualTo1WhenCreatedBySharedPointer) {
    ASSERT_EQ(w_ptr.use_count(), oneReference);
    ASSERT_EQ(rw_ptr.use_count(), oneReference);
}

TEST_F(WeakPointerTest, shouldReturnSharedPointerWhenLockWeakPointer) {
    auto s_ptrNew = w_ptr.lock();
    ASSERT_EQ(*s_ptrNew, testValue);

    auto rs_ptrNew = rw_ptr.lock();
    ASSERT_EQ(*rs_ptrNew, testValue);
}

TEST_F(WeakPointerTest, shouldReturnNullptrSharedPointerWhenLockWeakPointerWithNoSharedPointer) {
    WeakPointer<int> test_w_ptr;
    auto s_ptrNew = test_w_ptr.lock();
    ASSERT_EQ(s_ptrNew.get(), nullptr);

    std::weak_ptr<int> test_rw_ptr;
    auto rs_ptrNew = test_rw_ptr.lock();
    ASSERT_EQ(rs_ptrNew.get(), nullptr);
}

TEST_F(WeakPointerTest, shouldUseMoveConstructor) {
    WeakPointer<int> w_ptrNew{std::move(w_ptr)};
    ASSERT_TRUE(w_ptr.expired());
    ASSERT_FALSE(w_ptrNew.expired());
    ASSERT_EQ(w_ptrNew.use_count(), oneReference);

    std::weak_ptr<int> rw_ptrNew{std::move(rw_ptr)};
    ASSERT_TRUE(rw_ptr.expired());
    ASSERT_FALSE(rw_ptrNew.expired());
    ASSERT_EQ(rw_ptrNew.use_count(), oneReference);
}

TEST_F(WeakPointerTest, shouldUseMoveAssignment) {
    WeakPointer<int> w_ptrNew;
    w_ptrNew = std::move(w_ptr);
    ASSERT_TRUE(w_ptr.expired());
    ASSERT_EQ(w_ptrNew.use_count(), oneReference);

    std::weak_ptr<int> rw_ptrNew;
    rw_ptrNew = std::move(rw_ptr);
    ASSERT_TRUE(rw_ptr.expired());
    ASSERT_EQ(rw_ptrNew.use_count(), oneReference);
}

TEST_F(WeakPointerTest, shouldUseCopyAssignment) {
    WeakPointer<int> w_ptrNew;
    w_ptrNew = w_ptr;
    ASSERT_EQ(w_ptr.use_count(), oneReference);

    std::weak_ptr<int> rw_ptrNew;
    rw_ptrNew = rw_ptr;
    ASSERT_EQ(rw_ptr.use_count(), oneReference);
}

TEST_F(ControlBlockTest, shouldGetSharedRefs) {
    ASSERT_EQ(testControlBlock.getShared(), oneReference);
}

TEST_F(ControlBlockTest, shouldGetWeakRefs) {
    ASSERT_EQ(testControlBlock.getWeak(), noReferences);
}

TEST_F(ControlBlockTest, shouldIncreaseSharedRefs) {
    testControlBlock.increaseShared();
    ASSERT_EQ(testControlBlock.getShared(), twoReferences);
}

TEST_F(ControlBlockTest, shouldIncreaseWeakRefs) {
    testControlBlock.increaseWeak();
    ASSERT_EQ(testControlBlock.getWeak(), oneReference);
}

TEST_F(ControlBlockTest, shouldDecreaseSharedRefs) {
    testControlBlock.increaseShared();
    testControlBlock.decreaseShared();
    ASSERT_EQ(testControlBlock.getShared(), oneReference);
}

TEST_F(ControlBlockTest, shouldDecreaseWeakRefs) {
    testControlBlock.increaseWeak();
    testControlBlock.decreaseWeak();
    ASSERT_EQ(testControlBlock.getWeak(), noReferences);
}

TEST(MakeSharedTest, shouldUseMakeSharedOnSingleTestValue) {
    auto ms_ptr = MakeShared<int>(testValue);
    ASSERT_EQ(*ms_ptr, testValue);

    auto rms_ptr = std::make_shared<int>(testValue);
    ASSERT_EQ(*rms_ptr, testValue);
}

TEST(MakeSharedTest, shouldUseMakeSharedOnExampleStructure) {
    struct TestStructure {
        TestStructure(int x, int y, int z) : x_(x), y_(y), z_(z){};
        int x_;
        int y_;
        int z_;
    };
    auto ms_ptr = MakeShared<TestStructure>(testValue, testValue, testValue);
    ASSERT_EQ(ms_ptr->x_, testValue);
    ASSERT_EQ(ms_ptr->y_, testValue);
    ASSERT_EQ(ms_ptr->z_, testValue);

    auto rms_ptr = std::make_shared<TestStructure>(testValue, testValue, testValue);
    ASSERT_EQ(rms_ptr->x_, testValue);
    ASSERT_EQ(rms_ptr->y_, testValue);
    ASSERT_EQ(rms_ptr->z_, testValue);
}
