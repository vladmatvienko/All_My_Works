#include "model/scene.h"

#include <stdexcept>
#include <utility>

namespace s21 {

Scene::Scene(Figure figure, std::string filename)
    : figure_(std::move(figure)),
      filename_(std::move(filename)),
      has_figure_(true) {}

bool Scene::Empty() const noexcept { return !has_figure_; }

const Figure& Scene::figure() const {
  if (!has_figure_) {
    throw std::logic_error("Scene is empty");
  }
  return figure_;
}

Figure& Scene::mutable_figure() {
  if (!has_figure_) {
    throw std::logic_error("Scene is empty");
  }
  return figure_;
}

const std::string& Scene::filename() const noexcept { return filename_; }

std::size_t Scene::VerticesCount() const noexcept {
  return has_figure_ ? figure_.VerticesCount() : 0U;
}

std::size_t Scene::EdgesCount() const noexcept {
  return has_figure_ ? figure_.EdgesCount() : 0U;
}

void Scene::Transform(const TransformMatrix& matrix) {
  if (has_figure_) {
    figure_.Transform(matrix);
  }
}

void Scene::Clear() noexcept {
  figure_ = Figure();
  filename_.clear();
  has_figure_ = false;
}

}  // namespace s21
