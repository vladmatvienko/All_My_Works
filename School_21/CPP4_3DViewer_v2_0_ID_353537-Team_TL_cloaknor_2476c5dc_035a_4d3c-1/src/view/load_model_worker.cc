#include "view/load_model_worker.h"

#include "model/obj_file_reader.h"

namespace s21 {

LoadModelWorker::LoadModelWorker(QObject* parent) : QObject(parent) {}

void LoadModelWorker::Load(const QString& path) {
  try {
    ObjFileReader reader;
    Scene scene = reader.ReadScene(path.toStdString());
    emit Loaded(std::move(scene));
  } catch (const std::exception& error) {
    emit Failed(QString::fromUtf8(error.what()));
  }
}

}  // namespace s21
