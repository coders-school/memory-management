#include <gtest/gtest.h>

#include "Unique_ptr.hpp"
#include "Data.hpp"

size_t day = 11;
std::string month = "January";
size_t year = 2016;

size_t new_day = 30;
std::string new_month = "October";
size_t new_year = 2014;



TEST(UniquePtrTest, Constructor_that_takes_RowPointer) {
    My_unique_ptr unique(new Data(day, month, year));
        ASSERT_EQ(unique->getDay(), day);
        ASSERT_EQ(unique->getMonth(), month);
        ASSERT_EQ(unique->getYear(), year);
}

TEST(UniquePtrTest, MoveConstructor) {
    My_unique_ptr resource(new Data(day, month, year));
    My_unique_ptr unique(std::move(resource));
        ASSERT_EQ(unique->getDay(), day);
        ASSERT_EQ(unique->getMonth(), month);
        ASSERT_EQ(unique->getYear(), year);
        ASSERT_EQ(resource.get(), nullptr);
}

TEST(UniquePtrTest, MoveAssigmentOperator) {
    My_unique_ptr resource(new Data(day, month, year));
    My_unique_ptr unique(new Data(0, "", 0));
    unique = std::move(resource);
        ASSERT_EQ(unique->getDay(), day);
        ASSERT_EQ(unique->getMonth(), month);
        ASSERT_EQ(unique->getYear(), year);
        ASSERT_EQ(resource.get(), nullptr);
}

TEST(UniquePtrTest, StarOperator) {
    My_unique_ptr unique(new Data(day, month, year));
    auto data = *unique;
        ASSERT_EQ(data.getDay(), day);
        ASSERT_EQ(data.getMonth(), month);
        ASSERT_EQ(data.getYear(), year);
}

TEST(UniquePtrTest, ArrowOperator) {
    My_unique_ptr unique(new Data(day, month, year));
        ASSERT_EQ(unique->getDay(), day);
        ASSERT_EQ(unique->getMonth(), month);
        ASSERT_EQ(unique->getYear(), year);
}

TEST(UniquePtrTest, Reset_JustReset) {
    My_unique_ptr unique(new Data(day, month, year));
        ASSERT_EQ(unique->getDay(), day);
        ASSERT_EQ(unique->getMonth(), month);
        ASSERT_EQ(unique->getYear(), year);
    unique.reset();
        ASSERT_EQ(unique.get(), nullptr);
}

TEST(UniquePtrTest, Reset_ResetByNewValue) {
    My_unique_ptr unique(new Data(day, month, year));
        ASSERT_EQ(unique->getDay(), day);
        ASSERT_EQ(unique->getMonth(), month);
        ASSERT_EQ(unique->getYear(), year);
    auto newData = new Data(new_day, new_month, new_year);
    unique.reset(newData); //some kind of problem !!!!
        ASSERT_EQ(unique->getDay(), new_day);
        ASSERT_EQ(unique->getMonth(), new_month);
        ASSERT_EQ(unique->getYear(), new_year);
        ASSERT_EQ(newData, unique.get());// and hire
}

TEST(UniquePtrTest, Release) {
    My_unique_ptr unique(new Data(day, month, year));
    auto ptr = unique.release();
        ASSERT_EQ(ptr->getDay(), day);
        ASSERT_EQ(ptr->getMonth(), month);
        ASSERT_EQ(ptr->getYear(), year);
        ASSERT_EQ(unique.get(), nullptr);
}

