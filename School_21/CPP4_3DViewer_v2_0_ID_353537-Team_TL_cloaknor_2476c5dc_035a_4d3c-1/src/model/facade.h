#ifndef SRC_MODEL_FACADE_H_
#define SRC_MODEL_FACADE_H_

#include <memory>
#include <string>

#include "model/base_file_reader.h"
#include "model/obj_file_reader.h"
#include "model/render_settings.h"
#include "model/scene.h"
#include "model/scene_drawer_base.h"
#include "model/scene_loader.h"

namespace s21 {

class FacadeOperationResult {
 public:
  FacadeOperationResult() = default;
  explicit FacadeOperationResult(std::string message);

  bool IsSuccess() const noexcept;
  const std::string& GetErrorMessage() const noexcept;

 private:
  bool is_success_ = true;
  std::string error_message_;
};

class Facade {
 public:
  explicit Facade(std::unique_ptr<SceneDrawerBase> drawer);
  Facade(std::unique_ptr<BaseFileReader> reader,
         std::unique_ptr<SceneDrawerBase> drawer);
  ~Facade() = default;

  FacadeOperationResult LoadScene(const std::string& path);
  FacadeOperationResult MoveScene(double x, double y, double z);
  FacadeOperationResult RotateScene(double x_degree, double y_degree,
                                    double z_degree);
  FacadeOperationResult ScaleScene(double scale);
  void DrawScene(int viewport_width, int viewport_height);
  FacadeOperationResult ReplaceScene(Scene scene);
  Scene CloneScene() const;

  RenderSettings& GetRenderSettings() noexcept;
  const RenderSettings& GetRenderSettings() const noexcept;
  void SetRenderSettings(const RenderSettings& settings);

  std::string GetFilename() const;
  std::size_t GetVerticesCount() const noexcept;
  std::size_t GetEdgesCount() const noexcept;
  bool HasScene() const noexcept;

 private:
  FacadeOperationResult ApplyTransform(const TransformMatrix& matrix);

  std::unique_ptr<BaseFileReader> reader_;
  std::unique_ptr<SceneDrawerBase> drawer_;
  Scene scene_;
  RenderSettings render_settings_;
};

}  // namespace s21

#endif  // SRC_MODEL_FACADE_H_
