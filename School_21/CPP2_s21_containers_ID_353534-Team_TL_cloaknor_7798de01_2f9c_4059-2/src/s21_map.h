#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

#include "s21_tree.h"

namespace s21 {

template <typename Key, typename T>
struct MapKeyOfValue {
  using value_type = std::pair<const Key, T>;
  const Key& operator()(const value_type& value) const noexcept { return value.first; }
};

template <typename Key, typename T, typename Compare = std::less<Key>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree_type = BinaryTree<key_type, value_type, MapKeyOfValue<Key, T>, Compare, false>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = std::size_t;

  map() = default;

  map(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }

  map(const map& m) = default;
  map(map&& m) noexcept = default;
  ~map() = default;

  map& operator=(const map& m) = default;
  map& operator=(map&& m) noexcept = default;

  mapped_type& at(const key_type& key) {
    auto it = tree_.find(key);
    if (it == end()) {
      throw std::out_of_range("map::at: key is not found");
    }
    return it->second;
  }

  const mapped_type& at(const key_type& key) const {
    auto it = tree_.find(key);
    if (it == end()) {
      throw std::out_of_range("map::at: key is not found");
    }
    return it->second;
  }

  mapped_type& operator[](const key_type& key) {
    auto result = insert({key, mapped_type{}});
    return result.first->second;
  }

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

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree_.insert_unique(value);
  }

  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj) {
    return insert({key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key, const mapped_type& obj) {
    auto result = insert({key, obj});
    if (!result.second) {
      result.first->second = obj;
    }
    return result;
  }

  void erase(iterator pos) { tree_.erase(pos); }
  void swap(map& other) noexcept { tree_.swap(other.tree_); }
  void merge(map& other) { tree_.merge(other.tree_); }

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

#endif  // S21_MAP_H_
