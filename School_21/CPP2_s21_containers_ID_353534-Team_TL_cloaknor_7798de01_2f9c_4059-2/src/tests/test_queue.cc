#include <gtest/gtest.h>

#include "s21_containers.h"

TEST(S21QueueTest, ConstructorsAndAssignment) {
  s21::queue<int> empty;
  EXPECT_TRUE(empty.empty());

  s21::queue<int> from_list{1, 2, 3};
  EXPECT_EQ(from_list.size(), 3U);
  EXPECT_EQ(from_list.front(), 1);
  EXPECT_EQ(from_list.back(), 3);

  s21::queue<int> copied(from_list);
  s21::queue<int> moved(std::move(from_list));
  EXPECT_EQ(moved.front(), 1);
  EXPECT_TRUE(from_list.empty());

  moved = copied;
  EXPECT_EQ(moved.back(), 3);
}

TEST(S21QueueTest, Modifiers) {
  s21::queue<int> queue;
  queue.push(1);
  queue.push(2);
  EXPECT_EQ(queue.size(), 2U);
  EXPECT_EQ(queue.front(), 1);
  queue.pop();
  EXPECT_EQ(queue.front(), 2);

  s21::queue<int> other{3};
  queue.swap(other);
  EXPECT_EQ(queue.front(), 3);
}

TEST(S21QueueTest, InsertManyBack) {
  s21::queue<int> queue;
  queue.insert_many_back(1, 2, 3);
  EXPECT_EQ(queue.size(), 3U);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 3);
}
