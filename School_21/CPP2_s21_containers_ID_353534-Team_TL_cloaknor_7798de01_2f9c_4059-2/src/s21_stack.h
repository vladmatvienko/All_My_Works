#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <initializer_list>
#include <utility>

#include "s21_list.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  stack() = default;

  stack(std::initializer_list<value_type> const& items) : data_(items) {}

  stack(const stack& s) = default;
  stack(stack&& s) noexcept = default;
  ~stack() = default;

  stack& operator=(const stack& s) = default;
  stack& operator=(stack&& s) noexcept = default;

  const_reference top() const { return data_.back(); }
  reference top() { return data_.back(); }

  bool empty() const noexcept { return data_.empty(); }
  size_type size() const noexcept { return data_.size(); }

  void push(const_reference value) { data_.push_back(value); }
  void pop() { data_.pop_back(); }
  void swap(stack& other) noexcept { data_.swap(other.data_); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    data_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<value_type> data_{};
};

}  // namespace s21

#endif  // S21_STACK_H_
