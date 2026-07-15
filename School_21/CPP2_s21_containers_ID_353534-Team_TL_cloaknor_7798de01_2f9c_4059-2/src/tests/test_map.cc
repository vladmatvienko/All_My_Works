#include <gtest/gtest.h>

#include <map>
#include <stdexcept>
#include <string>

#include "s21_containers.h"

namespace {

using MapValue = std::pair<const int, std::string>;

std::map<int, std::string> ToStdMap(const s21::map<int, std::string>& container) {
  return std::map<int, std::string>(container.begin(), container.end());
}

}  // namespace

TEST(S21MapTest, ConstructorsAndAssignment) {
  s21::map<int, std::string> empty;
  EXPECT_TRUE(empty.empty());

  s21::map<int, std::string> from_list{{1, "one"}, {2, "two"}};
  EXPECT_EQ(ToStdMap(from_list), (std::map<int, std::string>{{1, "one"}, {2, "two"}}));

  s21::map<int, std::string> copied(from_list);
  s21::map<int, std::string> moved(std::move(from_list));
  EXPECT_EQ(ToStdMap(copied), (std::map<int, std::string>{{1, "one"}, {2, "two"}}));
  EXPECT_TRUE(from_list.empty());

  moved = copied;
  EXPECT_EQ(moved.at(2), "two");
}

TEST(S21MapTest, ElementAccess) {
  s21::map<int, std::string> dict{{1, "one"}};
  EXPECT_EQ(dict.at(1), "one");
  EXPECT_THROW(dict.at(42), std::out_of_range);
  dict[2] = "two";
  EXPECT_EQ(dict[2], "two");
  dict[3];
  EXPECT_EQ(dict.at(3), "");
}

TEST(S21MapTest, CapacityAndIterators) {
  s21::map<int, int> dict{{3, 30}, {1, 10}, {2, 20}};
  EXPECT_EQ(dict.size(), 3U);
  EXPECT_FALSE(dict.empty());
  EXPECT_GT(dict.max_size(), 0U);
  EXPECT_EQ(dict.begin()->first, 1);
  EXPECT_EQ((--dict.end())->first, 3);
}

TEST(S21MapTest, ModifiersAndLookup) {
  s21::map<int, std::string> dict;
  auto [it, inserted] = dict.insert(MapValue{1, "one"});
  EXPECT_TRUE(inserted);
  EXPECT_EQ(it->second, "one");

  auto [it2, inserted2] = dict.insert(2, "two");
  EXPECT_TRUE(inserted2);

  auto [it3, assigned] = dict.insert_or_assign(1, "updated");
  EXPECT_FALSE(assigned);
  EXPECT_EQ(dict.at(1), "updated");

  EXPECT_TRUE(dict.contains(2));
  EXPECT_FALSE(dict.contains(99));
  EXPECT_NE(dict.find(2), dict.end());

  dict.erase(it);
  EXPECT_FALSE(dict.contains(1));

  s21::map<int, std::string> other{{3, "three"}};
  dict.merge(other);
  EXPECT_TRUE(dict.contains(3));

  s21::map<int, std::string> swapped;
  dict.swap(swapped);
  EXPECT_TRUE(dict.empty());
  EXPECT_FALSE(swapped.empty());
  dict.clear();
}

TEST(S21MapTest, FindAndMoveAssignment) {
  s21::map<int, std::string> dict{{1, "one"}, {2, "two"}};
  EXPECT_NE(dict.find(1), dict.end());
  EXPECT_EQ(dict.find(1)->second, "one");
  EXPECT_EQ(dict.find(99), dict.end());

  const s21::map<int, std::string>& cref = dict;
  EXPECT_NE(cref.find(2), cref.end());

  s21::map<int, std::string> other;
  other = std::move(dict);
  EXPECT_TRUE(dict.empty());
  EXPECT_EQ(other.at(1), "one");
}

TEST(S21MapTest, InsertMany) {
  s21::map<int, std::string> dict;
  auto results = dict.insert_many(MapValue{2, "two"}, MapValue{1, "one"}, MapValue{2, "dup"});
  ASSERT_EQ(results.size(), 3U);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_FALSE(results[2].second);
  EXPECT_EQ(ToStdMap(dict), (std::map<int, std::string>{{1, "one"}, {2, "two"}}));
}
