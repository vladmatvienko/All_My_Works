#include "view/model_widget.h"

#include <Qt>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace s21 {

ModelWidget::ModelWidget(ViewerController* controller, QWidget* parent)
    : QOpenGLWidget(parent), controller_(controller) {}

void ModelWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void ModelWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void ModelWidget::paintGL() {
  if (controller_ != nullptr) {
    controller_->DrawScene(width(), height());
  }
}

QImage ModelWidget::CaptureFrame(int target_width, int target_height) {
  const QImage frame = grabFramebuffer();
  if (target_width <= 0 || target_height <= 0) {
    return frame;
  }
  return frame.scaled(target_width, target_height, Qt::IgnoreAspectRatio,
                      Qt::SmoothTransformation);
}

}  // namespace s21
