#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <initializer_list>
#include <utility>

#include "s21_list.h"

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  queue() = default;

  queue(std::initializer_list<value_type> const& items) : data_(items) {}

  queue(const queue& q) = default;
  queue(queue&& q) noexcept = default;
  ~queue() = default;

  queue& operator=(const queue& q) = default;
  queue& operator=(queue&& q) noexcept = default;

  const_reference front() const { return data_.front(); }
  reference front() { return data_.front(); }

  const_reference back() const { return data_.back(); }
  reference back() { return data_.back(); }

  bool empty() const noexcept { return data_.empty(); }
  size_type size() const noexcept { return data_.size(); }

  void push(const_reference value) { data_.push_back(value); }
  void pop() { data_.pop_front(); }
  void swap(queue& other) noexcept { data_.swap(other.data_); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    data_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<value_type> data_{};
};

}  // namespace s21

#endif  // S21_QUEUE_H_
