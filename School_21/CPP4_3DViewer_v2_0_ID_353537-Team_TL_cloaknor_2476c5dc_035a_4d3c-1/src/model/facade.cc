#include "model/facade.h"

#include <exception>
#include <stdexcept>
#include <utility>

namespace s21 {

FacadeOperationResult::FacadeOperationResult(std::string message)
    : is_success_(false), error_message_(std::move(message)) {}

bool FacadeOperationResult::IsSuccess() const noexcept { return is_success_; }

const std::string& FacadeOperationResult::GetErrorMessage() const noexcept {
  return error_message_;
}

Facade::Facade(std::unique_ptr<SceneDrawerBase> drawer)
    : Facade(std::make_unique<ObjFileReader>(), std::move(drawer)) {}

Facade::Facade(std::unique_ptr<BaseFileReader> reader,
               std::unique_ptr<SceneDrawerBase> drawer)
    : reader_(std::move(reader)), drawer_(std::move(drawer)) {
  if (!reader_ || !drawer_) {
    throw std::invalid_argument("Facade dependencies must not be null");
  }
}

FacadeOperationResult Facade::LoadScene(const std::string& path) {
  try {
    scene_ = SceneLoader::LoadObjScene(path);
    return FacadeOperationResult();
  } catch (const std::exception& error) {
    return FacadeOperationResult(error.what());
  }
}

FacadeOperationResult Facade::MoveScene(double x, double y, double z) {
  return ApplyTransform(TransformMatrixBuilder::CreateMoveMatrix(x, y, z));
}

FacadeOperationResult Facade::RotateScene(double x_degree, double y_degree,
                                          double z_degree) {
  return ApplyTransform(TransformMatrixBuilder::CreateRotationMatrix(
      x_degree, y_degree, z_degree));
}

FacadeOperationResult Facade::ScaleScene(double scale) {
  try {
    return ApplyTransform(TransformMatrixBuilder::CreateScaleMatrix(scale));
  } catch (const std::exception& error) {
    return FacadeOperationResult(error.what());
  }
}

void Facade::DrawScene(int viewport_width, int viewport_height) {
  drawer_->DrawScene(scene_, render_settings_, viewport_width, viewport_height);
}

FacadeOperationResult Facade::ReplaceScene(Scene scene) {
  if (scene.Empty()) {
    return FacadeOperationResult("Loaded scene is empty");
  }
  scene_ = std::move(scene);
  return FacadeOperationResult();
}

Scene Facade::CloneScene() const {
  if (scene_.Empty()) {
    return Scene();
  }
  return Scene(scene_.figure(), scene_.filename());
}

RenderSettings& Facade::GetRenderSettings() noexcept {
  return render_settings_;
}

const RenderSettings& Facade::GetRenderSettings() const noexcept {
  return render_settings_;
}

void Facade::SetRenderSettings(const RenderSettings& settings) {
  render_settings_ = settings;
}

std::string Facade::GetFilename() const { return scene_.filename(); }

std::size_t Facade::GetVerticesCount() const noexcept {
  return scene_.VerticesCount();
}

std::size_t Facade::GetEdgesCount() const noexcept {
  return scene_.EdgesCount();
}

bool Facade::HasScene() const noexcept { return !scene_.Empty(); }

FacadeOperationResult Facade::ApplyTransform(const TransformMatrix& matrix) {
  if (scene_.Empty()) {
    return FacadeOperationResult("Load a model first");
  }
  scene_.Transform(matrix);
  return FacadeOperationResult();
}

}  // namespace s21
