#include "../Queue/TQueue.h"

#include "gtest.h"

TEST(TQueue, can_create_queue_with_positive_size){
    ASSERT_NO_THROW(TQueue<int> m(5));
}

TEST(TQueue, throws_when_create_queue_with_negative_size) {
    ASSERT_ANY_THROW(TQueue<int> queue(-5));
}

TEST(TQueue, can_create_copied_queue) {
    TQueue<int> m(5);
    ASSERT_NO_THROW(TQueue<int> m1(m));
}

TEST(TQueue, copied_queue_is_equal_to_source_one) {
    TQueue<int> m(5);
    TQueue<int> m1(m);
    EXPECT_EQ(m, m1);
}

TEST(TQueue, empty_queue) {
    TQueue<int> m(5);
    ASSERT_NO_THROW(m.isEmpty() == true);
}

TEST(TQueue, no_empty_queue) {
    TQueue<int> m(5);
    m.push(1);
    ASSERT_NO_THROW(m.isEmpty() == false);
}

TEST(TQueue, full_queue) {
    TQueue<int> m(2);
    m.push(5);
    m.push(2);
    ASSERT_NO_THROW(m.isFull() == true);
}

TEST(TQueue, no_full_queue) {
    TQueue<int> m(5);
    m.push(5);
    m.push(10);
    ASSERT_NO_THROW(m.isFull() == false);
}

TEST(TQueue, front_function) {
    TQueue<int> m(3);
    m.push(2);
    m.push(3);
    ASSERT_NO_THROW(m.front() == 2);  
}

TEST(TQueue, back_function) {
    TQueue<int> m(3);
    m.push(2);
    m.push(3);
    ASSERT_NO_THROW(m.back() == 3); 
}

TEST(TQueue, clear_stack) {
    TQueue<int>m(2);
    m.push(5);
    m.push(2);
    m.clear();
    ASSERT_NO_THROW(m.isEmpty() == true);
}

TEST(TQueue, push_function) {
    TQueue<int> m(2);
    m.push(2);
    m.push(3);
    ASSERT_NO_THROW(m.back() == 3);
}

TEST(TQueue, pop_function) {
    TQueue<int> m(2);
    m.push(2);
    m.push(3);
    m.pop();
    ASSERT_NO_THROW(m.front() == 3);
}

TEST(TQueue, pop_from_empty_queue_throws_exception) {
    TQueue<int> m(3);
    ASSERT_ANY_THROW(m.pop());  
}

TEST(TQueue, push_to_full_queue_throws_exception) {
    TQueue<int> m(2);
    m.push(1);
    m.push(2);
    ASSERT_ANY_THROW(m.push(3));
}

TEST(TQueue, compare_queues) {
    TQueue<int> m(2);
    m.push(5);
    m.push(2);
    TQueue<int> m1(m);
    ASSERT_NO_THROW(m == m1);
}

TEST(TQueue, compare_queue_different_head) {
    TQueue<int> m(5);
    TQueue<int> m1(m);
    m.push(5);
    m.push(10);
    m1.push(10);
    m1.push(5);
    m1.push(10);
    m1.pop();
    ASSERT_NO_THROW(m == m1);
}

TEST(TQueue, no_compare_queue) {
    TQueue<int> m(2);
    TQueue<int> m1(m);
    m.push(5);
    m.push(10);
    m1.push(10);
    m1.push(5);
    ASSERT_NO_THROW(m != m1);
}