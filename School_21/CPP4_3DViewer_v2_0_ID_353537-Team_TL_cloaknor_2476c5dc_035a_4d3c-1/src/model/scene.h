#ifndef SRC_MODEL_SCENE_H_
#define SRC_MODEL_SCENE_H_

#include <string>

#include "model/figure.h"

namespace s21 {

class Scene {
 public:
  Scene() = default;
  Scene(Figure figure, std::string filename);

  bool Empty() const noexcept;
  const Figure& figure() const;
  Figure& mutable_figure();
  const std::string& filename() const noexcept;
  std::size_t VerticesCount() const noexcept;
  std::size_t EdgesCount() const noexcept;
  void Transform(const TransformMatrix& matrix);
  void Clear() noexcept;

 private:
  Figure figure_;
  std::string filename_;
  bool has_figure_ = false;
};

}  // namespace s21

#endif  // SRC_MODEL_SCENE_H_
