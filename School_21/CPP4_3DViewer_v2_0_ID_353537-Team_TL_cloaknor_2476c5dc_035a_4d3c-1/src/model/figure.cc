#include "model/figure.h"

#include <algorithm>
#include <cmath>
#include <utility>

namespace s21 {

Figure::Figure(std::vector<Point3D> vertices, std::vector<Edge> edges)
    : vertices_(std::move(vertices)), edges_(std::move(edges)) {}

const std::vector<Point3D>& Figure::vertices() const noexcept {
  return vertices_;
}

const std::vector<Edge>& Figure::edges() const noexcept { return edges_; }

std::vector<Point3D>& Figure::mutable_vertices() noexcept { return vertices_; }

std::vector<Edge>& Figure::mutable_edges() noexcept { return edges_; }

std::size_t Figure::VerticesCount() const noexcept { return vertices_.size(); }

std::size_t Figure::EdgesCount() const noexcept { return edges_.size(); }

void Figure::Transform(const TransformMatrix& matrix) {
  for (Point3D& vertex : vertices_) {
    vertex = matrix.TransformPoint(vertex);
  }
}

void Figure::Normalize() {
  if (vertices_.empty()) {
    return;
  }
  const NormalizationParameters parameters = CalculateNormalizationParameters();
  const double center_x = (parameters.min_x + parameters.max_x) / 2.0;
  const double center_y = (parameters.min_y + parameters.max_y) / 2.0;
  const double center_z = (parameters.min_z + parameters.max_z) / 2.0;
  const double scale =
      std::fabs(parameters.dtype) < 1e-12 ? 1.0 : 2.0 / parameters.dtype;

  for (Point3D& vertex : vertices_) {
    vertex.x = (vertex.x - center_x) * scale;
    vertex.y = (vertex.y - center_y) * scale;
    vertex.z = (vertex.z - center_z) * scale;
  }
}

NormalizationParameters Figure::CalculateNormalizationParameters() const {
  NormalizationParameters parameters;
  parameters.min_x = parameters.max_x = vertices_.front().x;
  parameters.min_y = parameters.max_y = vertices_.front().y;
  parameters.min_z = parameters.max_z = vertices_.front().z;

  for (const Point3D& vertex : vertices_) {
    parameters.min_x = std::min(parameters.min_x, vertex.x);
    parameters.max_x = std::max(parameters.max_x, vertex.x);
    parameters.min_y = std::min(parameters.min_y, vertex.y);
    parameters.max_y = std::max(parameters.max_y, vertex.y);
    parameters.min_z = std::min(parameters.min_z, vertex.z);
    parameters.max_z = std::max(parameters.max_z, vertex.z);
  }

  const double dx = parameters.max_x - parameters.min_x;
  const double dy = parameters.max_y - parameters.min_y;
  const double dz = parameters.max_z - parameters.min_z;
  parameters.dtype = std::max({dx, dy, dz});
  return parameters;
}

}  // namespace s21
