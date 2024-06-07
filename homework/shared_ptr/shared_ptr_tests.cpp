#include "shared_ptr.hpp"
#include <gtest/gtest.h>

template class my::shared_ptr<int>;

TEST(SharedPtrTest, BasicUsage) {
    my::shared_ptr<int> sp(new int(42));
    EXPECT_TRUE(sp);
    EXPECT_EQ(*sp, 42);
    EXPECT_EQ(sp.use_count(), 1);
}

TEST(SharedPtrTest, CopyConstructor) {
    my::shared_ptr<int> sp1(new int(42));
    my::shared_ptr<int> sp2(sp1);
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

TEST(SharedPtrTest, MoveConstructor) {
    my::shared_ptr<int> sp1(new int(42));
    my::shared_ptr<int> sp2(std::move(sp1));
    EXPECT_FALSE(sp1);
    EXPECT_TRUE(sp2);
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(SharedPtrTest, CopyAssignment) {
    my::shared_ptr<int> sp1(new int(42));
    my::shared_ptr<int> sp2;
    sp2 = sp1;
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

TEST(SharedPtrTest, MoveAssignment) {
    my::shared_ptr<int> sp1(new int(42));
    my::shared_ptr<int> sp2;
    sp2 = std::move(sp1);
    EXPECT_FALSE(sp1);
    EXPECT_TRUE(sp2);
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(SharedPtrTest, Reset) {
    my::shared_ptr<int> sp(new int(42));
    sp.reset(new int(84));
    EXPECT_EQ(*sp, 84);
    EXPECT_EQ(sp.use_count(), 1);
}

TEST(SharedPtrTest, Destructor) {
    my::shared_ptr<int> sp(new int(42));
    {
        my::shared_ptr<int> sp2(sp);
        EXPECT_EQ(sp.use_count(), 2);
    }
    EXPECT_EQ(sp.use_count(), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}