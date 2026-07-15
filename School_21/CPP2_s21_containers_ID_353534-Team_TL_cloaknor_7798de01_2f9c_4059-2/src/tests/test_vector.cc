#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>

#include "s21_containers.h"

namespace {

std::vector<int> ToStdVector(const s21::vector<int>& container) {
  return std::vector<int>(container.begin(), container.end());
}

}  // namespace

TEST(S21VectorTest, DefaultConstructor) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0U);
  EXPECT_EQ(vec.capacity(), 0U);
}

TEST(S21VectorTest, SizeConstructor) {
  s21::vector<int> vec(4);
  EXPECT_EQ(vec.size(), 4U);
  for (std::size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], 0);
  }
}

TEST(S21VectorTest, InitializerListConstructor) {
  s21::vector<int> vec{1, 2, 3};
  EXPECT_EQ(ToStdVector(vec), std::vector<int>({1, 2, 3}));
}

TEST(S21VectorTest, CopyAndMove) {
  s21::vector<int> original{1, 2, 3};
  s21::vector<int> copied(original);
  s21::vector<int> moved(std::move(original));
  EXPECT_EQ(ToStdVector(copied), std::vector<int>({1, 2, 3}));
  EXPECT_EQ(ToStdVector(moved), std::vector<int>({1, 2, 3}));
  EXPECT_TRUE(original.empty());
}

TEST(S21VectorTest, AssignmentOperators) {
  s21::vector<int> lhs{1};
  s21::vector<int> rhs{2, 3};
  lhs = rhs;
  EXPECT_EQ(ToStdVector(lhs), std::vector<int>({2, 3}));
  s21::vector<int> tmp{4, 5};
  lhs = std::move(tmp);
  EXPECT_EQ(ToStdVector(lhs), std::vector<int>({4, 5}));
}

TEST(S21VectorTest, ElementAccess) {
  s21::vector<int> vec{10, 20, 30};
  EXPECT_EQ(vec.front(), 10);
  EXPECT_EQ(vec.back(), 30);
  EXPECT_EQ(vec[1], 20);
  EXPECT_EQ(vec.at(2), 30);
  EXPECT_NE(vec.data(), nullptr);
  EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(S21VectorTest, Capacity) {
  s21::vector<int> vec;
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10U);
  vec.push_back(1);
  vec.push_back(2);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.size(), 2U);
  EXPECT_GE(vec.capacity(), 2U);
  EXPECT_GT(vec.max_size(), 0U);
}

TEST(S21VectorTest, Modifiers) {
  s21::vector<int> vec{1, 3};
  vec.insert(vec.begin() + 1, 2);
  vec.push_back(4);
  EXPECT_EQ(ToStdVector(vec), std::vector<int>({1, 2, 3, 4}));
  vec.erase(vec.begin() + 1);
  vec.pop_back();
  EXPECT_EQ(ToStdVector(vec), std::vector<int>({1, 3}));
  vec.clear();
  EXPECT_TRUE(vec.empty());
}

TEST(S21VectorTest, Swap) {
  s21::vector<int> first{1, 2};
  s21::vector<int> second{3, 4, 5};
  first.swap(second);
  EXPECT_EQ(ToStdVector(first), std::vector<int>({3, 4, 5}));
  EXPECT_EQ(ToStdVector(second), std::vector<int>({1, 2}));
}

TEST(S21VectorTest, InsertMany) {
  s21::vector<int> vec{1, 5};
  auto it = vec.insert_many(vec.cbegin() + 1, 2, 3, 4);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(ToStdVector(vec), std::vector<int>({1, 2, 3, 4, 5}));
  vec.insert_many_back(6, 7);
  EXPECT_EQ(ToStdVector(vec), std::vector<int>({1, 2, 3, 4, 5, 6, 7}));
}

TEST(S21VectorTest, InsertManyEdgeCases) {
  s21::vector<int> vec{1, 2};
  vec.insert_many(vec.cend());
  EXPECT_EQ(vec.size(), 2U);
}

TEST(S21VectorTest, InsertAtBeginAndReserve) {
  s21::vector<int> vec{2, 3};
  vec.insert(vec.begin(), 1);
  EXPECT_EQ(ToStdVector(vec), std::vector<int>({1, 2, 3}));

  s21::vector<int> large;
  large.reserve(100);
  EXPECT_GE(large.capacity(), 100U);
  EXPECT_THROW(large.reserve(large.max_size() + 1), std::length_error);
}
