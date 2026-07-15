#ifndef S21_SET_H_
#define S21_SET_H_

#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

#include "s21_tree.h"

namespace s21 {

template <typename Key>
struct SetKeyOfValue {
  const Key& operator()(const Key& value) const noexcept { return value; }
};

template <typename Key, typename Compare = std::less<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree_type = BinaryTree<key_type, value_type, SetKeyOfValue<Key>, Compare, false>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = std::size_t;

  set() = default;

  set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  set(const set& s) = default;
  set(set&& s) noexcept = default;
  ~set() = default;

  set& operator=(const set& s) = default;
  set& operator=(set&& s) noexcept = default;

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
  std::pair<iterator, bool> insert(const value_type& value) { return tree_.insert_unique(value); }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(set& other) noexcept { tree_.swap(other.tree_); }
  void merge(set& other) { tree_.merge(other.tree_); }

  iterator find(const key_type& key) noexcept { return tree_.find(key); }
  const_iterator find(const key_type& key) const noexcept { return tree_.find(key); }
  bool contains(const key_type& key) const noexcept { return tree_.contains(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result;
    result.reserve(sizeof...(Args));
    (result.push_back(insert(std::forward<Args>(args))), ...);
    return result;
  }

 private:
  tree_type tree_{};
};

}  // namespace s21

#endif  // S21_SET_H_
