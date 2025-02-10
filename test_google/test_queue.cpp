#include "../gtest/gtest.h"
#include "../queue.cpp" 

TEST(QueueTest, PushAndPop) {
    Queue q;
    q.push(10);
    q.push(20);
    EXPECT_EQ(q.front(), 10);
    q.pop();
    EXPECT_EQ(q.front(), 20);
}