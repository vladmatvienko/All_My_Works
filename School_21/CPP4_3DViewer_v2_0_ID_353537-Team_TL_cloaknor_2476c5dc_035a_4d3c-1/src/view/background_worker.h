#ifndef SRC_VIEW_BACKGROUND_WORKER_H_
#define SRC_VIEW_BACKGROUND_WORKER_H_

#include <QObject>
#include <QString>

#include "model/scene.h"
#include "view/scene_meta.h"

namespace s21 {

class BackgroundWorker final : public QObject {
  Q_OBJECT

 public:
  explicit BackgroundWorker(QObject* parent = nullptr);

 public slots:
  void LoadModel(const QString& path);
  void MoveScene(Scene scene, double x, double y, double z);
  void RotateScene(Scene scene, double x_degree, double y_degree,
                   double z_degree);
  void ScaleScene(Scene scene, double scale);

 signals:
  void ModelLoaded(Scene scene);
  void SceneTransformed(Scene scene);
  void Failed(QString error_message);
};

}  // namespace s21

#endif  // SRC_VIEW_BACKGROUND_WORKER_H_
