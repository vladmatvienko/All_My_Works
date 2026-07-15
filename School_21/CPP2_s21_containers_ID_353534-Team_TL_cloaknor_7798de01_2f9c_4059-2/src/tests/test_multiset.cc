#include <gtest/gtest.h>

#include <set>

#include "s21_containersplus.h"

namespace {

std::multiset<int> ToStdMultiset(const s21::multiset<int>& container) {
  return std::multiset<int>(container.begin(), container.end());
}

}  // namespace

TEST(S21MultisetTest, ConstructorsAndAssignment) {
  s21::multiset<int> empty;
  EXPECT_TRUE(empty.empty());

  s21::multiset<int> from_list{3, 1, 2, 2};
  EXPECT_EQ(ToStdMultiset(from_list), std::multiset<int>({1, 2, 2, 3}));

  s21::multiset<int> copied(from_list);
  s21::multiset<int> moved(std::move(from_list));
  EXPECT_EQ(ToStdMultiset(moved), std::multiset<int>({1, 2, 2, 3}));

  moved = copied;
  EXPECT_EQ(moved.count(2), 2U);
}

TEST(S21MultisetTest, ModifiersAndLookup) {
  s21::multiset<int> values;
  auto it1 = values.insert(2);
  auto it2 = values.insert(2);
  EXPECT_NE(it1, it2);
  EXPECT_EQ(values.count(2), 2U);
  EXPECT_TRUE(values.contains(2));
  EXPECT_NE(values.find(2), values.end());

  auto [low, high] = values.equal_range(2);
  EXPECT_EQ(values.count(2), 2U);
  EXPECT_EQ(*low, 2);
  EXPECT_EQ(*values.lower_bound(2), 2);
  EXPECT_EQ(values.upper_bound(2), high);

  values.erase(it1);
  EXPECT_EQ(values.count(2), 1U);

  s21::multiset<int> other{3, 3};
  values.merge(other);
  EXPECT_EQ(values.count(3), 2U);

  s21::multiset<int> swapped;
  values.swap(swapped);
  EXPECT_TRUE(values.empty());
  values.clear();
}

TEST(S21MultisetTest, InsertMany) {
  s21::multiset<int> values;
  auto results = values.insert_many(2, 1, 2, 3);
  ASSERT_EQ(results.size(), 4U);
  for (const auto& item : results) {
    EXPECT_TRUE(item.second);
  }
  EXPECT_EQ(ToStdMultiset(values), std::multiset<int>({1, 2, 2, 3}));
}
