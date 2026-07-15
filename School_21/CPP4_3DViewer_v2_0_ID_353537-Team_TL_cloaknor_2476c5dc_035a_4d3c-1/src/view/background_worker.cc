#include "view/background_worker.h"

#include "model/scene_loader.h"
#include "model/transform_matrix.h"

namespace s21 {

BackgroundWorker::BackgroundWorker(QObject* parent) : QObject(parent) {}

void BackgroundWorker::LoadModel(const QString& path) {
  try {
    Scene scene = SceneLoader::LoadObjScene(path.toStdString());
    emit ModelLoaded(std::move(scene));
  } catch (const std::exception& error) {
    emit Failed(QString::fromUtf8(error.what()));
  }
}

void BackgroundWorker::MoveScene(Scene scene, double x, double y, double z) {
  try {
    scene.Transform(TransformMatrixBuilder::CreateMoveMatrix(x, y, z));
    emit SceneTransformed(std::move(scene));
  } catch (const std::exception& error) {
    emit Failed(QString::fromUtf8(error.what()));
  }
}

void BackgroundWorker::RotateScene(Scene scene, double x_degree,
                                   double y_degree, double z_degree) {
  try {
    scene.Transform(TransformMatrixBuilder::CreateRotationMatrix(
        x_degree, y_degree, z_degree));
    emit SceneTransformed(std::move(scene));
  } catch (const std::exception& error) {
    emit Failed(QString::fromUtf8(error.what()));
  }
}

void BackgroundWorker::ScaleScene(Scene scene, double scale) {
  try {
    scene.Transform(TransformMatrixBuilder::CreateScaleMatrix(scale));
    emit SceneTransformed(std::move(scene));
  } catch (const std::exception& error) {
    emit Failed(QString::fromUtf8(error.what()));
  }
}

}  // namespace s21
