// Placeholder
#include "gtest/gtest.h"
#include "weak_ptr.hpp"


TEST(WeakPointerTests, WeakPointerCreation) {
    struct Something {};
    cs::shared_ptr<Something> shared_something(new Something{});
    cs::weak_ptr<Something> weak_something{shared_something};
    
    ASSERT_EQ(weak_something.use_count(), 1);
    ASSERT_EQ(shared_something.use_count(), 1);
}

TEST(WeakPointerTests, WeakPointerExpired) {
  cs::weak_ptr<int> w_ptr;
  {
    auto s_ptr = cs::shared_ptr<int>(new int{5});
    w_ptr = s_ptr;
    ASSERT_EQ(w_ptr.use_count(), 1);
    
  }
  ASSERT_TRUE(w_ptr.expired());
  
}
