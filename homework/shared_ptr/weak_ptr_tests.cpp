#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

template class my::weak_ptr<int>;

TEST(WeakPtrTest, InitTest) {
    my::weak_ptr<uint8_t> ptr1;
    ASSERT_EQ(ptr1.use_count(), 0);
    ASSERT_EQ(ptr1.expired(), true);

    my::shared_ptr<int> ptr2{new int(1)};
    my::weak_ptr ptr3{ptr2};
    ASSERT_EQ(ptr3.use_count(), 1);
    ASSERT_EQ(ptr3.expired(), false);
}

TEST(WeakPtrTest, CopyTest) {
    my::shared_ptr ptr1{new int(1)};
    my::weak_ptr ptr2{ptr1};
    my::weak_ptr ptr3{ptr2};
    my::weak_ptr<int> ptr4;
    ptr4 = ptr3;
    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr2.use_count(), 1);
    ASSERT_EQ(ptr3.use_count(), 1);
    ASSERT_EQ(ptr4.use_count(), 1);
    my::shared_ptr ptr5 = ptr2.lock();
    ASSERT_EQ(ptr5.get(), ptr1.get());
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);
    ASSERT_EQ(ptr3.use_count(), 2);
    ASSERT_EQ(ptr4.use_count(), 2);
    my::shared_ptr ptr6 = ptr3.lock();
    ASSERT_EQ(ptr6.get(), ptr1.get());
    ASSERT_EQ(ptr1.use_count(), 3);
    ASSERT_EQ(ptr2.use_count(), 3);
    ASSERT_EQ(ptr3.use_count(), 3);
    ASSERT_EQ(ptr4.use_count(), 3);
    my::shared_ptr ptr7 = ptr4.lock();
    ASSERT_EQ(ptr7.get(), ptr1.get());
    ASSERT_EQ(ptr1.use_count(), 4);
    ASSERT_EQ(ptr2.use_count(), 4);
    ASSERT_EQ(ptr3.use_count(), 4);
    ASSERT_EQ(ptr4.use_count(), 4);
    my::shared_ptr ptr8{new int(2)};
    ptr2 = ptr8;
    ASSERT_EQ(*ptr2.lock().get(), *ptr8.get());
}

TEST(WeakPtrTest, MoveTest) {
    my::shared_ptr<int> ptr1{new int(1)};
    my::weak_ptr ptr2{ptr1};
    my::weak_ptr ptr3{std::move(ptr2)};
    ASSERT_EQ(ptr2.lock().get(), nullptr);
    ASSERT_EQ(ptr3.lock().get(), ptr1.get());
    my::weak_ptr<int> ptr4;
    ptr4 = std::move(ptr3);
    ASSERT_EQ(ptr3.lock().get(), nullptr);
    ASSERT_EQ(ptr4.lock().get(), ptr1.get());
}

TEST(WeakPtrTest, ResetTest) {
    my::shared_ptr<int> ptr1{new int(1)};
    my::weak_ptr ptr2{ptr1};
    ASSERT_EQ(ptr2.lock().get(), ptr1.get());
    ptr2.reset();
    ASSERT_EQ(ptr2.lock().get(), nullptr);
}

TEST(WeakPtrTest, ExpiredTest) {
    my::weak_ptr<int> ptr1;
    ASSERT_TRUE(ptr1.expired());
    {
        my::shared_ptr ptr2{new int(1)};
        ptr1 = ptr2;
        ASSERT_FALSE(ptr1.expired());
    }
    ASSERT_TRUE(ptr1.expired());
}
