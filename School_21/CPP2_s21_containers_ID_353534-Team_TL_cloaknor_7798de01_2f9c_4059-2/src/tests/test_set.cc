#include <gtest/gtest.h>

#include <set>

#include "s21_containers.h"

namespace {

std::set<int> ToStdSet(const s21::set<int>& container) {
  return std::set<int>(container.begin(), container.end());
}

}  // namespace

TEST(S21SetTest, ConstructorsAndAssignment) {
  s21::set<int> empty;
  EXPECT_TRUE(empty.empty());

  s21::set<int> from_list{3, 1, 2};
  EXPECT_EQ(ToStdSet(from_list), std::set<int>({1, 2, 3}));

  s21::set<int> copied(from_list);
  s21::set<int> moved(std::move(from_list));
  EXPECT_EQ(ToStdSet(moved), std::set<int>({1, 2, 3}));
  EXPECT_TRUE(from_list.empty());

  moved = copied;
  EXPECT_TRUE(moved.contains(2));
}

TEST(S21SetTest, CapacityAndIterators) {
  s21::set<int> values{5, 1, 3};
  EXPECT_EQ(values.size(), 3U);
  EXPECT_FALSE(values.empty());
  EXPECT_GT(values.max_size(), 0U);
  EXPECT_EQ(*values.begin(), 1);
}

TEST(S21SetTest, ModifiersAndLookup) {
  s21::set<int> values;
  auto [it, inserted] = values.insert(2);
  EXPECT_TRUE(inserted);
  auto [it2, inserted2] = values.insert(2);
  EXPECT_FALSE(inserted2);
  EXPECT_TRUE(values.contains(2));
  EXPECT_EQ(values.find(2), it);
  values.erase(it);
  EXPECT_FALSE(values.contains(2));

  s21::set<int> other{3, 4};
  values.insert(1);
  values.merge(other);
  EXPECT_TRUE(values.contains(4));

  s21::set<int> swapped;
  values.swap(swapped);
  EXPECT_TRUE(values.empty());
  values.clear();
}

TEST(S21SetTest, InsertMany) {
  s21::set<int> values;
  auto results = values.insert_many(3, 1, 2, 2);
  ASSERT_EQ(results.size(), 4U);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_FALSE(results[3].second);
  EXPECT_EQ(ToStdSet(values), std::set<int>({1, 2, 3}));
}
