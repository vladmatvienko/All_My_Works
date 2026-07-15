#ifndef SRC_CONTROLLER_VIEWER_CONTROLLER_H_
#define SRC_CONTROLLER_VIEWER_CONTROLLER_H_

#include <string>

#include "model/facade.h"
#include "model/render_settings.h"
#include "model/scene.h"

namespace s21 {

class ViewerController final {
 public:
  explicit ViewerController(Facade* facade);

  FacadeOperationResult LoadModel(const std::string& path);
  FacadeOperationResult ReplaceScene(Scene scene);
  FacadeOperationResult MoveModel(double x, double y, double z);
  FacadeOperationResult RotateModel(double x_degree, double y_degree,
                                    double z_degree);
  FacadeOperationResult ScaleModel(double scale);
  void DrawScene(int viewport_width, int viewport_height);
  Scene CloneScene() const;

  RenderSettings& RenderSettingsRef() noexcept;
  const RenderSettings& RenderSettingsRef() const noexcept;
  void ApplyRenderSettings(const RenderSettings& settings);

  std::string Filename() const;
  std::size_t VerticesCount() const noexcept;
  std::size_t EdgesCount() const noexcept;
  bool HasScene() const noexcept;

 private:
  Facade* facade_ = nullptr;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_VIEWER_CONTROLLER_H_
