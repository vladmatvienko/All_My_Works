#include <gtest/gtest.h>

#include <stdexcept>

#include "s21_containersplus.h"

TEST(S21ArrayTest, ConstructorsAndAssignment) {
  s21::array<int, 3> empty{};
  EXPECT_EQ(empty.size(), 3U);
  EXPECT_FALSE(empty.empty());

  s21::array<int, 3> from_list{1, 2, 3};
  EXPECT_EQ(from_list[0], 1);
  EXPECT_EQ(from_list[2], 3);

  s21::array<int, 3> copied(from_list);
  s21::array<int, 3> moved(std::move(from_list));
  EXPECT_EQ(moved[1], 2);

  moved = copied;
  EXPECT_EQ(moved.at(2), 3);
}

TEST(S21ArrayTest, ElementAccess) {
  s21::array<int, 4> arr{10, 20, 30, 40};
  EXPECT_EQ(arr.front(), 10);
  EXPECT_EQ(arr.back(), 40);
  EXPECT_EQ(arr[2], 30);
  EXPECT_EQ(arr.at(1), 20);
  EXPECT_NE(arr.data(), nullptr);
  EXPECT_THROW(arr.at(4), std::out_of_range);
}

TEST(S21ArrayTest, CapacityAndIterators) {
  s21::array<int, 2> arr{1, 2};
  EXPECT_EQ(arr.size(), 2U);
  EXPECT_EQ(arr.max_size(), 2U);
  EXPECT_EQ(*arr.begin(), 1);
  EXPECT_EQ(arr.end() - arr.begin(), 2);
}

TEST(S21ArrayTest, Modifiers) {
  s21::array<int, 3> first{1, 2, 3};
  s21::array<int, 3> second{4, 5, 6};
  first.swap(second);
  EXPECT_EQ(first[0], 4);
  first.fill(7);
  EXPECT_EQ(first[2], 7);
}

TEST(S21ArrayTest, ZeroSizeArray) {
  s21::array<int, 0> arr{};
  EXPECT_TRUE(arr.empty());
  EXPECT_EQ(arr.size(), 0U);
}
