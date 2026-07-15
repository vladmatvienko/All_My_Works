#include <gtest/gtest.h>

#include <list>
#include <string>

#include "s21_containers.h"

namespace {

std::list<int> ToStdList(const s21::list<int>& container) {
  std::list<int> result;
  for (auto it = container.cbegin(); it != container.cend(); ++it) {
    result.push_back(*it);
  }
  return result;
}

}  // namespace

TEST(S21ListTest, DefaultConstructor) {
  s21::list<int> lst;
  EXPECT_TRUE(lst.empty());
  EXPECT_EQ(lst.size(), 0U);
}

TEST(S21ListTest, SizeConstructor) {
  s21::list<int> lst(5);
  EXPECT_EQ(lst.size(), 5U);
  for (const auto& value : lst) {
    EXPECT_EQ(value, 0);
  }
}

TEST(S21ListTest, InitializerListConstructor) {
  s21::list<int> lst{1, 2, 3, 4};
  EXPECT_EQ(ToStdList(lst), std::list<int>({1, 2, 3, 4}));
}

TEST(S21ListTest, CopyAndMove) {
  s21::list<int> original{1, 2, 3};
  s21::list<int> copied(original);
  s21::list<int> moved(std::move(original));
  EXPECT_EQ(ToStdList(copied), std::list<int>({1, 2, 3}));
  EXPECT_EQ(ToStdList(moved), std::list<int>({1, 2, 3}));
  EXPECT_TRUE(original.empty());
}

TEST(S21ListTest, AssignmentOperators) {
  s21::list<int> lhs{1};
  s21::list<int> rhs{2, 3};
  lhs = rhs;
  EXPECT_EQ(ToStdList(lhs), std::list<int>({2, 3}));
  s21::list<int> tmp{4, 5, 6};
  lhs = std::move(tmp);
  EXPECT_EQ(ToStdList(lhs), std::list<int>({4, 5, 6}));
  EXPECT_TRUE(tmp.empty());
}

TEST(S21ListTest, FrontBackAndCapacity) {
  s21::list<int> lst{10, 20, 30};
  EXPECT_EQ(lst.front(), 10);
  EXPECT_EQ(lst.back(), 30);
  EXPECT_FALSE(lst.empty());
  EXPECT_GT(lst.max_size(), 0U);
  lst.clear();
  EXPECT_TRUE(lst.empty());
}

TEST(S21ListTest, Iterators) {
  s21::list<int> lst{1, 2, 3};
  auto it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  EXPECT_NE(it, lst.end());
  EXPECT_EQ(it, lst.begin());

  s21::list<int>::const_iterator cit = lst.cbegin();
  EXPECT_EQ(*cit, 1);
  EXPECT_EQ(lst.size(), 3U);
}

TEST(S21ListTest, Modifiers) {
  s21::list<int> lst{1, 3};
  lst.insert(++lst.begin(), 2);
  lst.push_back(4);
  lst.push_front(0);
  EXPECT_EQ(ToStdList(lst), std::list<int>({0, 1, 2, 3, 4}));
  lst.pop_front();
  lst.pop_back();
  lst.erase(++lst.begin());
  EXPECT_EQ(ToStdList(lst), std::list<int>({1, 3}));
}

TEST(S21ListTest, SwapMergeSpliceReverseUniqueSort) {
  s21::list<int> first{1, 3, 5};
  s21::list<int> second{2, 4, 6};
  first.swap(second);
  EXPECT_EQ(ToStdList(first), std::list<int>({2, 4, 6}));

  s21::list<int> sorted_a{1, 4, 7};
  s21::list<int> sorted_b{2, 5, 8};
  sorted_a.merge(sorted_b);
  EXPECT_EQ(ToStdList(sorted_a), std::list<int>({1, 2, 4, 5, 7, 8}));
  EXPECT_TRUE(sorted_b.empty());

  s21::list<int> source{9, 10};
  s21::list<int> target{1, 2};
  target.splice(target.end(), source);
  EXPECT_TRUE(source.empty());
  EXPECT_EQ(ToStdList(target), std::list<int>({1, 2, 9, 10}));

  s21::list<int> reverse_me{1, 2, 3};
  reverse_me.reverse();
  EXPECT_EQ(ToStdList(reverse_me), std::list<int>({3, 2, 1}));

  s21::list<int> duplicates{1, 1, 2, 2, 2, 3};
  duplicates.unique();
  EXPECT_EQ(ToStdList(duplicates), std::list<int>({1, 2, 3}));

  s21::list<int> unsorted{3, 1, 4, 2};
  unsorted.sort();
  EXPECT_EQ(ToStdList(unsorted), std::list<int>({1, 2, 3, 4}));
}

TEST(S21ListTest, InsertMany) {
  s21::list<int> lst{1, 4};
  s21::list<int>::const_iterator pos = lst.cbegin();
  ++pos;
  auto it = lst.insert_many(pos, 2, 3);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(ToStdList(lst), std::list<int>({1, 2, 3, 4}));

  lst.insert_many_back(5, 6);
  EXPECT_EQ(ToStdList(lst), std::list<int>({1, 2, 3, 4, 5, 6}));

  lst.insert_many_front(0, -1);
  EXPECT_EQ(ToStdList(lst), std::list<int>({-1, 0, 1, 2, 3, 4, 5, 6}));
}

TEST(S21ListTest, InsertManyEdgeCases) {
  s21::list<std::string> lst{"a", "d"};
  lst.insert_many(lst.cend());
  EXPECT_EQ(lst.size(), 2U);

  lst.insert_many(lst.cbegin(), std::string("b"));
  EXPECT_EQ(lst.front(), "b");
}
