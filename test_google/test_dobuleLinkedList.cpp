#include "../gtest/gtest.h"
#include "../doubleLinkedList.cpp" 

TEST(DoublyLinkedListTest, PushFront) {
    DoublyLinkedList list;
    list.push_front(10);
    list.push_front(20);
    EXPECT_TRUE(list.contains(20));
    EXPECT_TRUE(list.contains(10));
}

TEST(DoublyLinkedListTest, PopFront) {
    DoublyLinkedList list;
    list.push_front(10);
    list.push_front(20);
    list.pop_front();
    EXPECT_FALSE(list.contains(20));
}