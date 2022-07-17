#include <gtest/gtest.h>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

class TestClass {
public:
    int number_{100};
    int numberReturn() {
        return number_;
    }
};

class weak_ptrFixture : public ::testing::Test {
public:
protected:
    my::weak_ptr<int> emptyWeakPtr;
    my::shared_ptr<int> emptySharedPtr;
    my::shared_ptr<int> sharedPtrToInt1{new int{10}};
    my::weak_ptr<int> weakPtrToInt1{sharedPtrToInt1};
};

TEST_F(weak_ptrFixture, DefaultCtorTest) {
    my::shared_ptr<int> emptySharedPtr2 = emptyWeakPtr.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);
}

TEST_F(weak_ptrFixture, CopyCtorSharedPtrAsArgumentTest) {
    my::weak_ptr<int> emptyWeakPtr2{emptySharedPtr};
    my::shared_ptr<int> emptySharedPtr2 = emptyWeakPtr2.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);

    // std::cout << sharedPtrToInt1.getControlBlockPtr()->getSharedRefs() << std::endl;
    // std::cout << sharedPtrToInt1.getControlBlockPtr()->getWeakRefs() << std::endl;
    my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
    // std::cout << sharedPtrToInt1.getControlBlockPtr()->getSharedRefs() << std::endl;
    // std::cout << sharedPtrToInt1.getControlBlockPtr()->getWeakRefs() << std::endl;
    EXPECT_EQ(*sharedPtrToInt2, 10);
}

TEST_F(weak_ptrFixture, CopyCtorWeakPtrAsArgumentTest) {
    my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
    EXPECT_EQ(*sharedPtrToInt2, 10);
}

TEST_F(weak_ptrFixture, LockFunctionTest) {
    my::weak_ptr<int> emptyWeakPtr2{emptySharedPtr};
    my::shared_ptr<int> emptySharedPtr2 = emptyWeakPtr2.lock();
    EXPECT_EQ(emptySharedPtr2.get(), nullptr);

    my::shared_ptr<int> sharedPtrToInt2 = weakPtrToInt1.lock();
    EXPECT_EQ(*sharedPtrToInt2, 10);
}
