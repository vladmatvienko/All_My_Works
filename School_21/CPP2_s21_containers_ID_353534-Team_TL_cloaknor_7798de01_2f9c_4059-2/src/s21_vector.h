#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  vector() noexcept = default;

  explicit vector(size_type n) { Reallocate(n); ConstructDefault(0, n); size_ = n; }

  vector(std::initializer_list<value_type> const& items) {
    Reallocate(items.size());
    for (const auto& item : items) {
      EmplaceBack(item);
    }
  }

  vector(const vector& v) { CopyFrom(v); }

  vector(vector&& v) noexcept { MoveFrom(v); }

  ~vector() { DestroyAndDeallocate(); }

  vector& operator=(const vector& v) {
    if (this != &v) {
      DestroyAndDeallocate();
      CopyFrom(v);
    }
    return *this;
  }

  vector& operator=(vector&& v) noexcept {
    if (this != &v) {
      DestroyAndDeallocate();
      MoveFrom(v);
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("vector::at: position is out of range");
    }
    return data_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("vector::at: position is out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() const { return data_[0]; }
  reference front() { return data_[0]; }

  const_reference back() const { return data_[size_ - 1]; }
  reference back() { return data_[size_ - 1]; }

  T* data() noexcept { return data_; }
  const T* data() const noexcept { return data_; }

  iterator begin() noexcept { return data_; }
  const_iterator begin() const noexcept { return data_; }
  const_iterator cbegin() const noexcept { return data_; }

  iterator end() noexcept { return data_ + size_; }
  const_iterator end() const noexcept { return data_ + size_; }
  const_iterator cend() const noexcept { return data_ + size_; }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type capacity() const noexcept { return capacity_; }

  size_type max_size() const noexcept {
    return std::allocator_traits<Allocator>::max_size(allocator_);
  }

  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("vector::reserve: requested size is too large");
    }
    if (size > capacity_) {
      ReallocatePreserving(size);
    }
  }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      ReallocatePreserving(size_);
    }
  }

  void clear() noexcept { DestroyRange(0, size_); size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type index = static_cast<size_type>(pos - begin());
    if (index > size_) {
      throw std::out_of_range("vector::insert: invalid iterator position");
    }
    value_type value_copy(value);
    if (size_ == capacity_) {
      size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      if (new_capacity < size_ + 1) {
        new_capacity = size_ + 1;
      }
      ReallocatePreserving(new_capacity);
    }
    if (index == size_) {
      ConstructAt(size_, value_copy);
    } else {
      ConstructAt(size_, std::move_if_noexcept(data_[size_ - 1]));
      for (size_type i = size_ - 1; i > index; --i) {
        data_[i] = std::move_if_noexcept(data_[i - 1]);
      }
      data_[index] = value_copy;
    }
    ++size_;
    return begin() + index;
  }

  void erase(iterator pos) {
    size_type index = static_cast<size_type>(pos - begin());
    if (index >= size_) {
      return;
    }
    for (size_type i = index; i + 1 < size_; ++i) {
      data_[i] = std::move_if_noexcept(data_[i + 1]);
    }
    DestroyAt(size_ - 1);
    --size_;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    ConstructAt(size_, value);
    ++size_;
  }

  void pop_back() {
    if (!empty()) {
      DestroyAt(size_ - 1);
      --size_;
    }
  }

  void swap(vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    if constexpr (sizeof...(Args) == 0) {
      return const_cast<iterator>(pos);
    } else {
      size_type index = static_cast<size_type>(pos - begin());
      size_type first_index = index;
      bool is_first = true;
      auto insert_one = [&](auto&& arg) {
        if (is_first) {
          first_index = index;
          is_first = false;
        }
        insert(begin() + index, std::forward<decltype(arg)>(arg));
        ++index;
      };
      (insert_one(std::forward<Args>(args)), ...);
      return begin() + first_index;
    }
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push_back(std::forward<Args>(args)), ...);
  }

 private:
  using Allocator = std::allocator<value_type>;
  using AllocatorTraits = std::allocator_traits<Allocator>;

  Allocator allocator_{};
  T* data_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  template <typename U>
  void ConstructAt(size_type index, U&& value) {
    AllocatorTraits::construct(allocator_, data_ + index, std::forward<U>(value));
  }

  void DestroyAt(size_type index) noexcept {
    AllocatorTraits::destroy(allocator_, data_ + index);
  }

  void DestroyRange(size_type begin_index, size_type end_index) noexcept {
    for (size_type i = begin_index; i < end_index; ++i) {
      DestroyAt(i);
    }
  }

  void ConstructDefault(size_type begin_index, size_type end_index) {
    size_type i = begin_index;
    try {
      for (; i < end_index; ++i) {
        AllocatorTraits::construct(allocator_, data_ + i);
      }
    } catch (...) {
      DestroyRange(begin_index, i);
      throw;
    }
  }

  void Reallocate(size_type new_capacity) {
    data_ = new_capacity == 0 ? nullptr : AllocatorTraits::allocate(allocator_, new_capacity);
    capacity_ = new_capacity;
  }

  void ReallocatePreserving(size_type new_capacity) {
    T* new_data = new_capacity == 0 ? nullptr : AllocatorTraits::allocate(allocator_, new_capacity);
    size_type constructed = 0;
    try {
      for (; constructed < size_; ++constructed) {
        AllocatorTraits::construct(allocator_, new_data + constructed,
                                   std::move_if_noexcept(data_[constructed]));
      }
    } catch (...) {
      for (size_type i = 0; i < constructed; ++i) {
        AllocatorTraits::destroy(allocator_, new_data + i);
      }
      if (new_data != nullptr) {
        AllocatorTraits::deallocate(allocator_, new_data, new_capacity);
      }
      throw;
    }
    DestroyRange(0, size_);
    if (data_ != nullptr) {
      AllocatorTraits::deallocate(allocator_, data_, capacity_);
    }
    data_ = new_data;
    capacity_ = new_capacity;
  }

  template <typename U>
  void EmplaceBack(U&& value) {
    ConstructAt(size_, std::forward<U>(value));
    ++size_;
  }

  void CopyFrom(const vector& v) {
    Reallocate(v.size_);
    size_type constructed = 0;
    try {
      for (; constructed < v.size_; ++constructed) {
        ConstructAt(constructed, v.data_[constructed]);
      }
    } catch (...) {
      DestroyRange(0, constructed);
      if (data_ != nullptr) {
        AllocatorTraits::deallocate(allocator_, data_, capacity_);
      }
      data_ = nullptr;
      capacity_ = 0;
      throw;
    }
    size_ = v.size_;
  }

  void MoveFrom(vector& v) noexcept {
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  void DestroyAndDeallocate() noexcept {
    DestroyRange(0, size_);
    if (data_ != nullptr) {
      AllocatorTraits::deallocate(allocator_, data_, capacity_);
    }
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
};

}  // namespace s21

#endif  // S21_VECTOR_H_
