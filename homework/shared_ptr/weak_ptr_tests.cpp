#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"


constexpr size_t zeroUseCount = 0;
constexpr int initialValue = 5;

struct WeakPtrTest : ::testing::Test {
    WeakPtrTest()
        : sptr{new int{initialValue}},
          wptr{sptr} {}

    my::shared_ptr<int> sptr;
    my::weak_ptr<int> wptr;
};

TEST(WeakPtrTestZeroUseCount, weakPtrCreatedWithDefaultCtorHasZerosUseCount) {
    my::weak_ptr<int> ptr{};

    ASSERT_EQ(ptr.use_count(), zeroUseCount);
}

TEST_F(WeakPtrTest, weakPtrBasedOnSharedPtrHasIncrementedUseCount) {
    ASSERT_NE(wptr.use_count(), zeroUseCount);
}

TEST_F(WeakPtrTest, lockMethodShouldReturnSharedPtrThatStoresManagedObject) {
    auto sptr2 = wptr.lock();

    ASSERT_EQ(sptr.get(), sptr2.get());

    my::weak_ptr<int> wptr2{};

    ASSERT_TRUE(wptr2.expired());
    std::cout << "wptr2.expired() = " << wptr2.expired() << "\n";
    // auto sptr3 = wptr2.lock();
    ASSERT_THAT(wptr2.lock().get(), ::testing::IsNull());
}

// TEST_F(WeakPtrTest, expireMethodInformsIfManagedObjectWasDeleted) {
//     ASSERT_FALSE(wptr.expired());

//     sptr.reset();
//     ASSERT_TRUE(wptr.expired());
// }

// TEST_F(WeakPtrTest, weakPtrMoveContructorMakesOriginalPtrExpired) {
//     constexpr int useCountValueSharedPtr = 1;
//     constexpr int useCountValueWeakPtr = 1;
//     constexpr int useCountWeakPtrAfterMove = 0;

//     ASSERT_EQ(wptr.use_count(), useCountValueWeakPtr);

//     my::weak_ptr<int> wptr2{std::move(wptr)};

//     ASSERT_EQ(wptr.use_count(), useCountWeakPtrAfterMove);
//     ASSERT_EQ(wptr2.use_count(), useCountValueWeakPtr);
//     ASSERT_EQ(sptr.use_count(), useCountValueSharedPtr);

//     ASSERT_TRUE(wptr.expired());
//     ASSERT_FALSE(wptr2.expired());
// }

// TEST_F(WeakPtrTest, weakPtrMoveAssignmentMakesOriginalPtrExpired) {
//     constexpr int useCountValueSharedPtr = 1;
//     constexpr int useCountValueWeakPtr = 1;
//     constexpr int useCountWeakPtrAfterMove = 0;

//     ASSERT_EQ(wptr.use_count(), useCountValueWeakPtr);

//     my::weak_ptr<int> wptr2{};
//     wptr2 = std::move(wptr);

//     ASSERT_EQ(wptr.use_count(), useCountWeakPtrAfterMove);
//     ASSERT_EQ(wptr2.use_count(), useCountValueWeakPtr);
//     ASSERT_EQ(sptr.use_count(), useCountValueSharedPtr);

//     ASSERT_TRUE(wptr.expired());
//     ASSERT_FALSE(wptr2.expired());
// }

// TEST_F(WeakPtrTest, weakPtrCopyContructorLeavesOriginalPtrNotExpired) {
//     constexpr int useCountValueSharedPtr = 1;
//     constexpr int useCountValueWeakPtr = 1;

//     ASSERT_EQ(wptr.use_count(), useCountValueWeakPtr);

//     my::weak_ptr<int> wptr2{wptr};

//     ASSERT_EQ(wptr.use_count(), useCountValueWeakPtr);
//     ASSERT_EQ(wptr2.use_count(), useCountValueWeakPtr);
//     ASSERT_EQ(sptr.use_count(), useCountValueSharedPtr);

//     ASSERT_FALSE(wptr.expired());
//     ASSERT_FALSE(wptr2.expired());
// }

// TEST_F(WeakPtrTest, weakPtrCopyAssignmentLeavesOriginalPtrNotExpired) {
//     constexpr int useCountValueSharedPtr = 1;
//     constexpr int useCountValueWeakPtr = 1;

//     ASSERT_EQ(wptr.use_count(), useCountValueWeakPtr);

//     my::weak_ptr<int> wptr2{};
//     wptr2 = wptr;

//     ASSERT_EQ(wptr.use_count(), useCountValueWeakPtr);
//     ASSERT_EQ(wptr2.use_count(), useCountValueWeakPtr);
//     ASSERT_EQ(sptr.use_count(), useCountValueSharedPtr);

//     ASSERT_FALSE(wptr.expired());
//     ASSERT_FALSE(wptr2.expired());
// }