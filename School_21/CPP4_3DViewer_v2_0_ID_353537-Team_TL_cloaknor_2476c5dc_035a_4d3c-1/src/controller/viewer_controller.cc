#include "controller/viewer_controller.h"

#include <stdexcept>

namespace s21 {

ViewerController::ViewerController(Facade* facade) : facade_(facade) {
  if (facade_ == nullptr) {
    throw std::invalid_argument("Controller facade must not be null");
  }
}

FacadeOperationResult ViewerController::LoadModel(const std::string& path) {
  return facade_->LoadScene(path);
}

FacadeOperationResult ViewerController::ReplaceScene(Scene scene) {
  return facade_->ReplaceScene(std::move(scene));
}

FacadeOperationResult ViewerController::MoveModel(double x, double y,
                                                  double z) {
  return facade_->MoveScene(x, y, z);
}

FacadeOperationResult ViewerController::RotateModel(double x_degree,
                                                    double y_degree,
                                                    double z_degree) {
  return facade_->RotateScene(x_degree, y_degree, z_degree);
}

FacadeOperationResult ViewerController::ScaleModel(double scale) {
  return facade_->ScaleScene(scale);
}

void ViewerController::DrawScene(int viewport_width, int viewport_height) {
  facade_->DrawScene(viewport_width, viewport_height);
}

RenderSettings& ViewerController::RenderSettingsRef() noexcept {
  return facade_->GetRenderSettings();
}

const RenderSettings& ViewerController::RenderSettingsRef() const noexcept {
  return facade_->GetRenderSettings();
}

void ViewerController::ApplyRenderSettings(const RenderSettings& settings) {
  facade_->SetRenderSettings(settings);
}

std::string ViewerController::Filename() const {
  return facade_->GetFilename();
}

std::size_t ViewerController::VerticesCount() const noexcept {
  return facade_->GetVerticesCount();
}

std::size_t ViewerController::EdgesCount() const noexcept {
  return facade_->GetEdgesCount();
}

bool ViewerController::HasScene() const noexcept { return facade_->HasScene(); }

Scene ViewerController::CloneScene() const { return facade_->CloneScene(); }

}  // namespace s21
