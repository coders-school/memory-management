#include <gtest/gtest.h>
#include "shared_ptr.hpp"

using namespace my;

TEST(SharedPtrTest, DefaultConstructor) {
    shared_ptr<int> sp;
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    EXPECT_FALSE(sp);
}

TEST(SharedPtrTest, ConstructorWithPointer) {
    shared_ptr<int> sp(new int(10));
    EXPECT_NE(sp.get(), nullptr);
    EXPECT_EQ(*sp, 10);
    EXPECT_EQ(sp.use_count(), 1);
    EXPECT_TRUE(sp);
}

TEST(SharedPtrTest, CopyConstructor) {
    shared_ptr<int> sp1(new int(20));
    shared_ptr<int> sp2(sp1);
    EXPECT_EQ(sp1.get(), sp2.get());
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

TEST(SharedPtrTest, MoveConstructor) {
    shared_ptr<int> sp1(new int(30));
    shared_ptr<int> sp2(std::move(sp1));
    EXPECT_EQ(sp1.get(), nullptr);
    EXPECT_EQ(sp1.use_count(), 0);
    EXPECT_NE(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(SharedPtrTest, CopyAssignment) {
    shared_ptr<int> sp1(new int(40));
    shared_ptr<int> sp2;
    sp2 = sp1;
    EXPECT_EQ(sp1.get(), sp2.get());
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

TEST(SharedPtrTest, MoveAssignment) {
    shared_ptr<int> sp1(new int(50));
    shared_ptr<int> sp2;
    sp2 = std::move(sp1);
    EXPECT_EQ(sp1.get(), nullptr);
    EXPECT_EQ(sp1.use_count(), 0);
    EXPECT_NE(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(SharedPtrTest, Reset) {
    shared_ptr<int> sp(new int(60));
    sp.reset(new int(70));
    EXPECT_NE(sp.get(), nullptr);
    EXPECT_EQ(*sp, 70);
    EXPECT_EQ(sp.use_count(), 1);
}

TEST(SharedPtrTest, UseCount) {
    shared_ptr<int> sp1(new int(80));
    shared_ptr<int> sp2(sp1);
    shared_ptr<int> sp3(sp2);
    EXPECT_EQ(sp1.use_count(), 3);
    EXPECT_EQ(sp2.use_count(), 3);
    EXPECT_EQ(sp3.use_count(), 3);
}

TEST(SharedPtrTest, BoolConversion) {
    shared_ptr<int> sp1;
    shared_ptr<int> sp2(new int(90));
    EXPECT_FALSE(sp1);
    EXPECT_TRUE(sp2);
}

// Explicit instantiation for coverage
template class my::shared_ptr<int>;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
