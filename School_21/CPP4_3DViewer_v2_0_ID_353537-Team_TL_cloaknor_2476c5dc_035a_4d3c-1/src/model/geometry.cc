#include "model/geometry.h"

#include <algorithm>

namespace s21 {

Edge::Edge(std::size_t begin, std::size_t end)
    : begin_(std::min(begin, end)), end_(std::max(begin, end)) {}

std::size_t Edge::begin() const noexcept { return begin_; }

std::size_t Edge::end() const noexcept { return end_; }

bool Edge::operator==(const Edge& other) const noexcept {
  return begin_ == other.begin_ && end_ == other.end_;
}

std::size_t EdgeHash::operator()(const Edge& edge) const noexcept {
  const std::size_t kHashMagic = 0x9e3779b9U;
  std::size_t seed = std::hash<std::size_t>{}(edge.begin());
  seed ^= std::hash<std::size_t>{}(edge.end()) + kHashMagic + (seed << 6) +
          (seed >> 2);
  return seed;
}

}  // namespace s21
