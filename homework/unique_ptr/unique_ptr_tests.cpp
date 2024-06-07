TEST(UniquePtrTest, BasicUsage) {
  // Test basic usage
  my::unique_ptr<int> ptr(new int(42));
  EXPECT_EQ(*ptr, 42);
  EXPECT_EQ(ptr.get(), ptr.release());
}

TEST(UniquePtrTest, MoveOwnership) {
  // Test move semantics
  my::unique_ptr<int> ptr1(new int(10));
  my::unique_ptr<int> ptr2(std::move(ptr1));
  EXPECT_EQ(ptr1.get(), nullptr);
  EXPECT_EQ(*ptr2, 10);

  ptr1 = std::move(ptr2);
  EXPECT_EQ(ptr2.get(), nullptr);
  EXPECT_EQ(*ptr1, 10);
}

TEST(UniquePtrTest, Reset) {
  // Test reset
  my::unique_ptr<int> ptr(new int(20));
  ptr.reset(new int(30));
  EXPECT_EQ(*ptr, 30);
}

// Add more tests as needed

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}