#ifndef SRC_MODEL_GEOMETRY_H_
#define SRC_MODEL_GEOMETRY_H_

#include <cstddef>
#include <functional>

namespace s21 {

struct Point3D {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
};

class Edge {
 public:
  Edge() = default;
  Edge(std::size_t begin, std::size_t end);

  std::size_t begin() const noexcept;
  std::size_t end() const noexcept;

  bool operator==(const Edge& other) const noexcept;

 private:
  std::size_t begin_ = 0;
  std::size_t end_ = 0;
};

struct EdgeHash {
  std::size_t operator()(const Edge& edge) const noexcept;
};

struct NormalizationParameters {
  double min_x = 0.0;
  double max_x = 0.0;
  double min_y = 0.0;
  double max_y = 0.0;
  double min_z = 0.0;
  double max_z = 0.0;
  double dtype = 1.0;
};

}  // namespace s21

#endif  // SRC_MODEL_GEOMETRY_H_
