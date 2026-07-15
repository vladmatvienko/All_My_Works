#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  array() = default;

  array(std::initializer_list<value_type> const& items) {
    size_type i = 0;
    for (const auto& item : items) {
      if (i >= N) {
        break;
      }
      data_[i++] = item;
    }
  }

  array(const array& a) = default;
  array(array&& a) noexcept = default;
  ~array() = default;

  array& operator=(const array& a) = default;
  array& operator=(array&& a) noexcept = default;

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("array::at: position is out of range");
    }
    return data_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= N) {
      throw std::out_of_range("array::at: position is out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() const { return data_[0]; }
  reference front() { return data_[0]; }

  const_reference back() const { return data_[N - 1]; }
  reference back() { return data_[N - 1]; }

  iterator data() noexcept { return data_; }
  const_iterator data() const noexcept { return data_; }

  iterator begin() noexcept { return data_; }
  const_iterator begin() const noexcept { return data_; }
  const_iterator cbegin() const noexcept { return data_; }

  iterator end() noexcept { return data_ + N; }
  const_iterator end() const noexcept { return data_ + N; }
  const_iterator cend() const noexcept { return data_ + N; }

  bool empty() const noexcept { return N == 0; }
  size_type size() const noexcept { return N; }
  size_type max_size() const noexcept { return N; }

  void swap(array& other) noexcept {
    for (size_type i = 0; i < N; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = value;
    }
  }

 private:
  value_type data_[N == 0 ? 1 : N]{};
};

}  // namespace s21

#endif  // S21_ARRAY_H_
