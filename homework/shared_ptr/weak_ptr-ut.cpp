// Placeholder
#include "gtest/gtest.h"
#include "weak_ptr.hpp"

TEST(WeakPointerTests, WeakPointerCreation) {
    constexpr size_t numberOfUseCount = 1;
    struct Something {};
    cs::shared_ptr<Something> shared_something(new Something{});
    cs::weak_ptr<Something> weak_something{shared_something};

    ASSERT_EQ(weak_something.use_count(), numberOfUseCount);
    ASSERT_EQ(shared_something.use_count(), numberOfUseCount);
}

TEST(WeakPointerTests, WeakPointerExpired) {
    constexpr size_t numberOfUseCount = 1;
    cs::weak_ptr<int> w_ptr;
    {
        auto s_ptr = cs::shared_ptr<int>(new int{5});
        w_ptr = s_ptr;
        ASSERT_EQ(w_ptr.use_count(), numberOfUseCount);
    }
    ASSERT_TRUE(w_ptr.expired());
}

TEST(WeakPointerTests, WeakPointerLock) {
    constexpr size_t numberOfUseCount = 2;
    constexpr int expectedValue{42};
    cs::shared_ptr<int> shared_something(new int{42});
    cs::weak_ptr<int> weak_something{shared_something};
    auto locked = weak_something.lock();

    ASSERT_EQ(shared_something.use_count(), numberOfUseCount);
    ASSERT_EQ(*locked, expectedValue);
}
