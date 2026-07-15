#ifndef SRC_VIEW_MODEL_WIDGET_H_
#define SRC_VIEW_MODEL_WIDGET_H_

#include <QImage>
#include <QOpenGLWidget>

#include "controller/viewer_controller.h"

namespace s21 {

class ModelWidget final : public QOpenGLWidget {
 public:
  explicit ModelWidget(ViewerController* controller, QWidget* parent = nullptr);

  QImage CaptureFrame(int target_width, int target_height);

 protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

 private:
  ViewerController* controller_ = nullptr;
};

}  // namespace s21

#endif  // SRC_VIEW_MODEL_WIDGET_H_
