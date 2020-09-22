#include "gtest/gtest.h"
#include "unique_ptr.hpp"
#include <string>


TEST(UniquePtrTest, StarOperatorShouldReturnObject) {
    unique_ptr<int> ptr(new int{42});
    *ptr = 1;

    ASSERT_TRUE(*ptr == 1);
}

TEST(UniquePtrTest, ArrowOperatorShouldReturnObject) {
    unique_ptr<std::string> ala(new std::string{"Ala"});

    ASSERT_TRUE(ala->size() == 3);
}

TEST(UniquePtrTest, GetFunctionShouldReturnRawPointerAndResetChangePointer) {
    unique_ptr<int> ptr;
    ASSERT_TRUE(ptr.get() == nullptr);

    ptr.reset(new int{42});
    ASSERT_TRUE(ptr.get() != nullptr);
    ASSERT_TRUE(*ptr.get() == 42);
}

TEST(UniquePtrTest, CopyingConstructorShouldSetNullptr) {
    unique_ptr<int> temp(new int{42});
    unique_ptr<int> main_ptr = std::move(temp);

    ASSERT_TRUE(temp.get() == nullptr);
    ASSERT_TRUE(main_ptr.get() != nullptr);
    ASSERT_TRUE(*main_ptr == 42);
}

TEST(UniquePtrTest, CopyAssignOperatorShouldSetNullptr) {
    unique_ptr<int> temp(new int{42});
    unique_ptr<int> main_ptr;
    main_ptr = std::move(temp);

    ASSERT_TRUE(temp.get() == nullptr);
    ASSERT_TRUE(main_ptr.get() != nullptr);
    ASSERT_TRUE(*main_ptr == 42);
}

TEST(UniquePtrTest, CopyAssignOperatorShouldAssignWhenMainPtrIsNotNullptr) {
    unique_ptr<int> temp(new int{42});
    unique_ptr<int> main_ptr(new int{1});
    main_ptr = std::move(temp);

    ASSERT_TRUE(temp.get() == nullptr);
    ASSERT_TRUE(main_ptr.get() != nullptr);
    ASSERT_TRUE(*main_ptr == 42);
}

TEST(UniquePtrTest, ReleaseFunctionShouldSetNullptrAndReturnPointer) {
    unique_ptr<int> temp(new int{42});
    int* ptr = temp.release();

    ASSERT_TRUE(*ptr == 42);
    delete ptr;
}
