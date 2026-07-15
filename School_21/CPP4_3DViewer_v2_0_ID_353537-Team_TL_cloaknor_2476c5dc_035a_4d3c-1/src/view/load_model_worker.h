#ifndef SRC_VIEW_LOAD_MODEL_WORKER_H_
#define SRC_VIEW_LOAD_MODEL_WORKER_H_

#include <QObject>
#include <QString>

#include "model/scene.h"
#include "view/scene_meta.h"

namespace s21 {

class LoadModelWorker final : public QObject {
  Q_OBJECT

 public:
  explicit LoadModelWorker(QObject* parent = nullptr);

 public slots:
  void Load(const QString& path);

 signals:
  void Loaded(Scene scene);
  void Failed(QString error_message);
};

}  // namespace s21

#endif  // SRC_VIEW_LOAD_MODEL_WORKER_H_
