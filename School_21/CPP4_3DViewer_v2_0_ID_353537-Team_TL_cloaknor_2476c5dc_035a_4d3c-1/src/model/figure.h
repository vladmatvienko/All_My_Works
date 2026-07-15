#ifndef SRC_MODEL_FIGURE_H_
#define SRC_MODEL_FIGURE_H_

#include <vector>

#include "model/geometry.h"
#include "model/scene_object.h"
#include "model/transform_matrix.h"

namespace s21 {

class Figure final : public SceneObject {
 public:
  Figure() = default;
  Figure(std::vector<Point3D> vertices, std::vector<Edge> edges);

  const std::vector<Point3D>& vertices() const noexcept;
  const std::vector<Edge>& edges() const noexcept;
  std::vector<Point3D>& mutable_vertices() noexcept;
  std::vector<Edge>& mutable_edges() noexcept;

  std::size_t VerticesCount() const noexcept;
  std::size_t EdgesCount() const noexcept;

  void Transform(const TransformMatrix& matrix) override;
  void Normalize();

 private:
  NormalizationParameters CalculateNormalizationParameters() const;

  std::vector<Point3D> vertices_;
  std::vector<Edge> edges_;
};

}  // namespace s21

#endif  // SRC_MODEL_FIGURE_H_
