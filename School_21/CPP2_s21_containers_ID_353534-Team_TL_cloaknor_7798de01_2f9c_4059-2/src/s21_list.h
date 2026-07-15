#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <initializer_list>
#include <iterator>
#include <limits>
#include <utility>

namespace s21 {

template <typename T>
struct ListIteratorTypes {
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::bidirectional_iterator_tag;
};

template <typename T>
struct ListConstIteratorTypes {
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = const T*;
  using reference = const T&;
  using iterator_category = std::bidirectional_iterator_tag;
};

template <typename T>
class list {
 private:
  struct BaseNode {
    BaseNode* prev = this;
    BaseNode* next = this;
  };

  struct Node : BaseNode {
    explicit Node(const T& item) : value(item) {}
    explicit Node(T&& item) : value(std::move(item)) {}
    T value;
  };

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  class const_iterator;

  class iterator : public ListIteratorTypes<T> {
   public:
    iterator() = default;
    explicit iterator(BaseNode* node) : node_(node) {}

    typename ListIteratorTypes<T>::reference operator*() const {
      return static_cast<Node*>(node_)->value;
    }
    T* operator->() const { return &static_cast<Node*>(node_)->value; }

    iterator& operator++() {
      node_ = node_->next;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    iterator& operator--() {
      node_ = node_->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const iterator& other) const { return node_ == other.node_; }
    bool operator!=(const iterator& other) const { return node_ != other.node_; }

   private:
    friend class list;
    friend class const_iterator;
    BaseNode* node_ = nullptr;
  };

  class const_iterator : public ListConstIteratorTypes<T> {
   public:
    const_iterator() = default;
    explicit const_iterator(const BaseNode* node) : node_(node) {}
    const_iterator(const iterator& other) : node_(other.node_) {}

    const_reference operator*() const { return static_cast<const Node*>(node_)->value; }
    const T* operator->() const { return &static_cast<const Node*>(node_)->value; }

    const_iterator& operator++() {
      node_ = node_->next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    const_iterator& operator--() {
      node_ = node_->prev;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const const_iterator& other) const { return node_ == other.node_; }
    bool operator!=(const const_iterator& other) const { return node_ != other.node_; }

   private:
    friend class list;
    const BaseNode* node_ = nullptr;
  };

  list() = default;

  explicit list(size_type n) {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type{});
    }
  }

  list(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      push_back(item);
    }
  }

  list(const list& l) { CopyFrom(l); }

  list(list&& l) noexcept { MoveFrom(l); }

  ~list() { clear(); }

  list& operator=(const list& l) {
    if (this != &l) {
      clear();
      CopyFrom(l);
    }
    return *this;
  }

  list& operator=(list&& l) noexcept {
    if (this != &l) {
      clear();
      MoveFrom(l);
    }
    return *this;
  }

  const_reference front() const { return *begin(); }
  reference front() { return *begin(); }

  const_reference back() const {
    const_iterator last = cend();
    return *(--last);
  }

  reference back() {
    iterator last = end();
    return *(--last);
  }

  iterator begin() noexcept { return iterator(sentinel_.next); }
  const_iterator begin() const noexcept { return const_iterator(sentinel_.next); }
  const_iterator cbegin() const noexcept { return const_iterator(sentinel_.next); }

  iterator end() noexcept { return iterator(&sentinel_); }
  const_iterator end() const noexcept { return const_iterator(&sentinel_); }
  const_iterator cend() const noexcept { return const_iterator(&sentinel_); }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2U;
  }

  void clear() noexcept {
    BaseNode* current = sentinel_.next;
    while (current != &sentinel_) {
      BaseNode* next = current->next;
      delete static_cast<Node*>(current);
      current = next;
    }
    ResetSentinel();
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    Node* node = new Node(value);
    LinkBefore(pos.node_, node);
    ++size_;
    return iterator(node);
  }

  void erase(iterator pos) {
    if (pos.node_ == &sentinel_) {
      return;
    }
    BaseNode* node = pos.node_;
    Unlink(node);
    delete static_cast<Node*>(node);
    --size_;
  }

  void push_back(const_reference value) { insert(end(), value); }
  void pop_back() {
    if (!empty()) {
      erase(--end());
    }
  }

  void push_front(const_reference value) { insert(begin(), value); }
  void pop_front() {
    if (!empty()) {
      erase(begin());
    }
  }

  void swap(list& other) noexcept {
    if (this == &other) {
      return;
    }
    list tmp(std::move(other));
    other = std::move(*this);
    *this = std::move(tmp);
  }

  void merge(list& other) {
    if (this == &other) {
      return;
    }
    iterator this_it = begin();
    iterator other_it = other.begin();
    while (other_it != other.end()) {
      if (this_it == end()) {
        BaseNode* first = other_it.node_;
        TransferRange(end().node_, first, other.sentinel_.prev);
        size_ += other.size_;
        other.size_ = 0;
        other.ResetSentinel();
        break;
      }
      if (*other_it < *this_it) {
        iterator next = other_it;
        ++next;
        TransferRange(this_it.node_, other_it.node_, other_it.node_);
        ++size_;
        --other.size_;
        other_it = next;
      } else {
        ++this_it;
      }
    }
  }

  void splice(const_iterator pos, list& other) {
    if (this == &other || other.empty()) {
      return;
    }
    BaseNode* first = other.sentinel_.next;
    BaseNode* last = other.sentinel_.prev;
    TransferRange(const_cast<BaseNode*>(pos.node_), first, last);
    size_ += other.size_;
    other.size_ = 0;
    other.ResetSentinel();
  }

  void reverse() noexcept {
    if (size_ < 2) {
      return;
    }
    BaseNode* current = &sentinel_;
    do {
      std::swap(current->next, current->prev);
      current = current->prev;
    } while (current != &sentinel_);
  }

  void unique() {
    if (size_ < 2) {
      return;
    }
    iterator current = begin();
    iterator next = current;
    ++next;
    while (next != end()) {
      if (*current == *next) {
        iterator to_delete = next;
        ++next;
        erase(to_delete);
      } else {
        current = next;
        ++next;
      }
    }
  }

  void sort() {
    if (size_ < 2) {
      return;
    }
    bool swapped = true;
    while (swapped) {
      swapped = false;
      for (iterator it = begin(); it != end();) {
        iterator next = it;
        ++next;
        if (next == end()) {
          break;
        }
        if (*next < *it) {
          std::swap(*it, *next);
          swapped = true;
        }
        it = next;
      }
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    if constexpr (sizeof...(Args) == 0) {
      return iterator(const_cast<BaseNode*>(pos.node_));
    } else {
      iterator first_it = end();
      iterator last_it = end();
      bool is_first = true;
      auto insert_one = [&](auto&& arg) {
        if (is_first) {
          first_it = insert(iterator(const_cast<BaseNode*>(pos.node_)),
                            std::forward<decltype(arg)>(arg));
          last_it = first_it;
          is_first = false;
        } else {
          iterator next_it = last_it;
          ++next_it;
          last_it = insert(next_it, std::forward<decltype(arg)>(arg));
        }
      };
      (insert_one(std::forward<Args>(args)), ...);
      return first_it;
    }
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (push_front(std::forward<Args>(args)), ...);
  }

 private:
  BaseNode sentinel_{};
  size_type size_ = 0;

  void ResetSentinel() noexcept {
    sentinel_.prev = &sentinel_;
    sentinel_.next = &sentinel_;
  }

  static void LinkBefore(BaseNode* pos, BaseNode* node) noexcept {
    node->next = pos;
    node->prev = pos->prev;
    pos->prev->next = node;
    pos->prev = node;
  }

  static void Unlink(BaseNode* node) noexcept {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = node;
    node->prev = node;
  }

  static void TransferRange(BaseNode* pos, BaseNode* first, BaseNode* last) noexcept {
    BaseNode* before_first = first->prev;
    BaseNode* after_last = last->next;
    before_first->next = after_last;
    after_last->prev = before_first;

    BaseNode* before_pos = pos->prev;
    before_pos->next = first;
    first->prev = before_pos;
    last->next = pos;
    pos->prev = last;
  }

  void CopyFrom(const list& other) {
    for (const auto& value : other) {
      push_back(value);
    }
  }

  void MoveFrom(list& other) noexcept {
    if (other.empty()) {
      ResetSentinel();
      size_ = 0;
      return;
    }
    sentinel_.next = other.sentinel_.next;
    sentinel_.prev = other.sentinel_.prev;
    sentinel_.next->prev = &sentinel_;
    sentinel_.prev->next = &sentinel_;
    size_ = other.size_;
    other.ResetSentinel();
    other.size_ = 0;
  }

};

}  // namespace s21

#endif  // S21_LIST_H_
