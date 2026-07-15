#ifndef S21_TREE_H_
#define S21_TREE_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <utility>

namespace s21 {

template <typename Value>
struct TreeIteratorTypes {
  using difference_type = std::ptrdiff_t;
  using value_type = Value;
  using pointer = Value*;
  using reference = Value&;
  using iterator_category = std::bidirectional_iterator_tag;
};

template <typename Value>
struct TreeConstIteratorTypes {
  using difference_type = std::ptrdiff_t;
  using value_type = Value;
  using pointer = const Value*;
  using reference = const Value&;
  using iterator_category = std::bidirectional_iterator_tag;
};

template <typename Key, typename Value, typename KeyOfValue,
          typename Compare, bool Multi>
class BinaryTree {
 private:
  struct Node {
    explicit Node(const Value& item) : value(item) {}
    Value value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
  };

 public:
  using key_type = Key;
  using value_type = Value;
  using reference = Value&;
  using const_reference = const Value&;
  using size_type = std::size_t;

  class const_iterator;

  class iterator : public TreeIteratorTypes<Value> {
   public:
    iterator() = default;
    iterator(Node* node, const BinaryTree* tree) : node_(node), tree_(tree) {}

    reference operator*() const { return node_->value; }
    Value* operator->() const { return &node_->value; }

    iterator& operator++() {
      node_ = tree_->Next(node_);
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    iterator& operator--() {
      node_ = tree_->Prev(node_);
      return *this;
    }

    iterator operator--(int) {
      iterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const iterator& other) const {
      return node_ == other.node_ && tree_ == other.tree_;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

   private:
    friend class BinaryTree;
    friend class const_iterator;
    Node* node_ = nullptr;
    const BinaryTree* tree_ = nullptr;
  };

  class const_iterator : public TreeConstIteratorTypes<Value> {
   public:
    const_iterator() = default;
    const_iterator(const Node* node, const BinaryTree* tree)
        : node_(node), tree_(tree) {}
    const_iterator(const iterator& other) : node_(other.node_), tree_(other.tree_) {}

    const_reference operator*() const { return node_->value; }
    const Value* operator->() const { return &node_->value; }

    const_iterator& operator++() {
      node_ = tree_->Next(const_cast<Node*>(node_));
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    const_iterator& operator--() {
      node_ = tree_->Prev(const_cast<Node*>(node_));
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const const_iterator& other) const {
      return node_ == other.node_ && tree_ == other.tree_;
    }

    bool operator!=(const const_iterator& other) const { return !(*this == other); }

   private:
    friend class BinaryTree;
    const Node* node_ = nullptr;
    const BinaryTree* tree_ = nullptr;
  };

  BinaryTree() = default;
  explicit BinaryTree(const Compare& comp) : comp_(comp) {}

  BinaryTree(const BinaryTree& other) : comp_(other.comp_) { CopyFrom(other); }

  BinaryTree(BinaryTree&& other) noexcept { MoveFrom(other); }

  ~BinaryTree() { clear(); }

  BinaryTree& operator=(const BinaryTree& other) {
    if (this != &other) {
      clear();
      comp_ = other.comp_;
      CopyFrom(other);
    }
    return *this;
  }

  BinaryTree& operator=(BinaryTree&& other) noexcept {
    if (this != &other) {
      clear();
      comp_ = other.comp_;
      MoveFrom(other);
    }
    return *this;
  }

  iterator begin() noexcept { return iterator(Min(root_), this); }
  const_iterator begin() const noexcept { return const_iterator(Min(root_), this); }
  const_iterator cbegin() const noexcept { return const_iterator(Min(root_), this); }

  iterator end() noexcept { return iterator(nullptr, this); }
  const_iterator end() const noexcept { return const_iterator(nullptr, this); }
  const_iterator cend() const noexcept { return const_iterator(nullptr, this); }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2U;
  }

  void clear() noexcept {
    ClearNode(root_);
    root_ = nullptr;
    size_ = 0;
  }

  std::pair<iterator, bool> insert_unique(const value_type& value) {
    Node* existing = FindNode(KeyOfValue{}(value));
    if (existing != nullptr) {
      return {iterator(existing, this), false};
    }
    Node* inserted = InsertNode(value);
    return {iterator(inserted, this), true};
  }

  iterator insert_multi(const value_type& value) {
    return iterator(InsertNode(value), this);
  }

  void erase(iterator pos) {
    if (pos.node_ == nullptr || pos.tree_ != this) {
      return;
    }
    EraseNode(pos.node_);
    --size_;
  }

  iterator find(const key_type& key) noexcept { return iterator(FindNode(key), this); }
  const_iterator find(const key_type& key) const noexcept {
    return const_iterator(FindNode(key), this);
  }

  bool contains(const key_type& key) const noexcept { return FindNode(key) != nullptr; }

  size_type count(const key_type& key) const noexcept {
    size_type result = 0;
    for (auto it = lower_bound(key); it != end() && IsEqual(KeyOfValue{}(*it), key); ++it) {
      ++result;
      if constexpr (!Multi) {
        break;
      }
    }
    return result;
  }

  iterator lower_bound(const key_type& key) noexcept {
    return iterator(LowerBoundNode(key), this);
  }

  const_iterator lower_bound(const key_type& key) const noexcept {
    return const_iterator(LowerBoundNode(key), this);
  }

  iterator upper_bound(const key_type& key) noexcept {
    return iterator(UpperBoundNode(key), this);
  }

  const_iterator upper_bound(const key_type& key) const noexcept {
    return const_iterator(UpperBoundNode(key), this);
  }

  std::pair<iterator, iterator> equal_range(const key_type& key) noexcept {
    return {lower_bound(key), upper_bound(key)};
  }

  std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const noexcept {
    return {lower_bound(key), upper_bound(key)};
  }

  void swap(BinaryTree& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  void merge(BinaryTree& other) {
    if (this == &other) {
      return;
    }
    for (auto it = other.begin(); it != other.end();) {
      auto current = it++;
      if constexpr (Multi) {
        insert_multi(*current);
        other.erase(current);
      } else {
        auto result = insert_unique(*current);
        if (result.second) {
          other.erase(current);
        }
      }
    }
  }

 private:
  Node* root_ = nullptr;
  size_type size_ = 0;
  Compare comp_{};

  bool IsEqual(const key_type& lhs, const key_type& rhs) const {
    return !comp_(lhs, rhs) && !comp_(rhs, lhs);
  }

  static Node* Min(Node* node) noexcept {
    while (node != nullptr && node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  static const Node* Min(const Node* node) noexcept {
    while (node != nullptr && node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  static Node* Max(Node* node) noexcept {
    while (node != nullptr && node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

  Node* Next(Node* node) const noexcept {
    if (node == nullptr) {
      return Min(root_);
    }
    if (node->right != nullptr) {
      return Min(node->right);
    }
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

  Node* Prev(Node* node) const noexcept {
    if (node == nullptr) {
      return Max(root_);
    }
    if (node->left != nullptr) {
      return Max(node->left);
    }
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }

  Node* FindNode(const key_type& key) const noexcept {
    Node* current = root_;
    while (current != nullptr) {
      key_type current_key = KeyOfValue{}(current->value);
      if (comp_(key, current_key)) {
        current = current->left;
      } else if (comp_(current_key, key)) {
        current = current->right;
      } else {
        return current;
      }
    }
    return nullptr;
  }

  Node* LowerBoundNode(const key_type& key) const noexcept {
    Node* current = root_;
    Node* result = nullptr;
    while (current != nullptr) {
      key_type current_key = KeyOfValue{}(current->value);
      if (!comp_(current_key, key)) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return result;
  }

  Node* UpperBoundNode(const key_type& key) const noexcept {
    Node* current = root_;
    Node* result = nullptr;
    while (current != nullptr) {
      key_type current_key = KeyOfValue{}(current->value);
      if (comp_(key, current_key)) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return result;
  }

  Node* InsertNode(const value_type& value) {
    Node* parent = nullptr;
    Node** current = &root_;
    key_type key = KeyOfValue{}(value);
    while (*current != nullptr) {
      parent = *current;
      key_type current_key = KeyOfValue{}((*current)->value);
      if (comp_(key, current_key)) {
        current = &((*current)->left);
      } else {
        current = &((*current)->right);
      }
    }
    Node* node = new Node(value);
    node->parent = parent;
    *current = node;
    ++size_;
    return node;
  }

  void Transplant(Node* old_node, Node* new_node) noexcept {
    if (old_node->parent == nullptr) {
      root_ = new_node;
    } else if (old_node == old_node->parent->left) {
      old_node->parent->left = new_node;
    } else {
      old_node->parent->right = new_node;
    }
    if (new_node != nullptr) {
      new_node->parent = old_node->parent;
    }
  }

  void EraseNode(Node* node) noexcept {
    if (node->left == nullptr) {
      Transplant(node, node->right);
    } else if (node->right == nullptr) {
      Transplant(node, node->left);
    } else {
      Node* successor = Min(node->right);
      if (successor->parent != node) {
        Transplant(successor, successor->right);
        successor->right = node->right;
        successor->right->parent = successor;
      }
      Transplant(node, successor);
      successor->left = node->left;
      successor->left->parent = successor;
    }
    delete node;
  }

  void ClearNode(Node* node) noexcept {
    if (node == nullptr) {
      return;
    }
    ClearNode(node->left);
    ClearNode(node->right);
    delete node;
  }

  void CopyFrom(const BinaryTree& other) {
    for (const auto& value : other) {
      if constexpr (Multi) {
        insert_multi(value);
      } else {
        insert_unique(value);
      }
    }
  }

  void MoveFrom(BinaryTree& other) noexcept {
    root_ = other.root_;
    size_ = other.size_;
    comp_ = other.comp_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
};

}  // namespace s21

#endif  // S21_TREE_H_
