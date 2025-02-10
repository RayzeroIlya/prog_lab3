#include "../gtest/gtest.h"
#include "../array.cpp"



TEST(ArrayTest, PushBack) {
    Array arr(5);
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_EQ(arr.get(1), 20);
}

TEST(ArrayTest, Insert) {
    Array arr(5);
    arr.push_back(10);
    arr.insert(0, 5);
    EXPECT_EQ(arr.get(0), 5);
    EXPECT_EQ(arr.get(1), 10);
}

TEST(ArrayTest, Remove) {
    Array arr(5);
    arr.push_back(10);
    arr.push_back(20);
    arr.remove(0);
    EXPECT_EQ(arr.get(0), 20);
}

TEST(ArrayTest, OutOfRange) {
    Array arr(5);
    arr.push_back(10);
    EXPECT_THROW(arr.get(1), std::out_of_range);
}