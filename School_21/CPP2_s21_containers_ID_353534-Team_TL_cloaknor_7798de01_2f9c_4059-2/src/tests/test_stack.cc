#include <gtest/gtest.h>

#include "s21_containers.h"

TEST(S21StackTest, ConstructorsAndAssignment) {
  s21::stack<int> empty;
  EXPECT_TRUE(empty.empty());

  s21::stack<int> from_list{1, 2, 3};
  EXPECT_EQ(from_list.size(), 3U);
  EXPECT_EQ(from_list.top(), 3);

  s21::stack<int> copied(from_list);
  s21::stack<int> moved(std::move(from_list));
  EXPECT_EQ(moved.top(), 3);
  EXPECT_TRUE(from_list.empty());

  moved = copied;
  EXPECT_EQ(moved.top(), 3);
}

TEST(S21StackTest, Modifiers) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.size(), 2U);
  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);

  s21::stack<int> other;
  other.push(5);
  stack.swap(other);
  EXPECT_EQ(stack.top(), 5);
}

TEST(S21StackTest, InsertManyBack) {
  s21::stack<int> stack;
  stack.insert_many_back(1, 2, 3);
  EXPECT_EQ(stack.size(), 3U);
  EXPECT_EQ(stack.top(), 3);
}
