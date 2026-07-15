#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

#include "s21_set.h"
#include "s21_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree_type = BinaryTree<key_type, value_type, SetKeyOfValue<Key>, Compare, true>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = std::size_t;

  multiset() = default;

  multiset(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  multiset(const multiset& ms) = default;
  multiset(multiset&& ms) noexcept = default;
  ~multiset() = default;

  multiset& operator=(const multiset& ms) = default;
  multiset& operator=(multiset&& ms) noexcept = default;

  iterator begin() noexcept { return tree_.begin(); }
  const_iterator begin() const noexcept { return tree_.begin(); }
  const_iterator cbegin() const noexcept { return tree_.cbegin(); }

  iterator end() noexcept { return tree_.end(); }
  const_iterator end() const noexcept { return tree_.end(); }
  const_iterator cend() const noexcept { return tree_.cend(); }

  bool empty() const noexcept { return tree_.empty(); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() noexcept { tree_.clear(); }
  iterator insert(const value_type& value) { return tree_.insert_multi(value); }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(multiset& other) noexcept { tree_.swap(other.tree_); }
  void merge(multiset& other) { tree_.merge(other.tree_); }

  size_type count(const key_type& key) const noexcept { return tree_.count(key); }
  iterator find(const key_type& key) noexcept { return tree_.find(key); }
  const_iterator find(const key_type& key) const noexcept { return tree_.find(key); }
  bool contains(const key_type& key) const noexcept { return tree_.contains(key); }
  std::pair<iterator, iterator> equal_range(const key_type& key) noexcept {
    return tree_.equal_range(key);
  }
  std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const noexcept {
    return tree_.equal_range(key);
  }
  iterator lower_bound(const key_type& key) noexcept { return tree_.lower_bound(key); }
  const_iterator lower_bound(const key_type& key) const noexcept { return tree_.lower_bound(key); }
  iterator upper_bound(const key_type& key) noexcept { return tree_.upper_bound(key); }
  const_iterator upper_bound(const key_type& key) const noexcept { return tree_.upper_bound(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    result.reserve(sizeof...(Args));
    auto insert_one = [&](auto&& arg) {
      iterator it = insert(std::forward<decltype(arg)>(arg));
      result.emplace_back(it, true);
    };
    (insert_one(std::forward<Args>(args)), ...);
    return result;
  }

 private:
  tree_type tree_{};
};

}  // namespace s21

#endif  // S21_MULTISET_H_
