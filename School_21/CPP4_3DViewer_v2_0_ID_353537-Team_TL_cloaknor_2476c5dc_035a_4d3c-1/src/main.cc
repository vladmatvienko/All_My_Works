#include <QApplication>
#include <QSurfaceFormat>
#include <memory>

#include "controller/viewer_controller.h"
#include "model/facade.h"
#include "model/opengl_scene_drawer.h"
#include "model/scene.h"
#include "view/main_window.h"
#include "view/scene_meta.h"

namespace {

void ConfigureOpenGlSurfaceFormat() {
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  format.setVersion(2, 1);
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);
}

}  // namespace

int main(int argc, char* argv[]) {
  ConfigureOpenGlSurfaceFormat();

  QApplication application(argc, argv);
  s21::RegisterSceneMetaType();

  auto drawer = std::make_unique<s21::OpenGLSceneDrawer>();
  s21::Facade facade(std::move(drawer));
  s21::ViewerController controller(&facade);
  s21::MainWindow window(&controller);
  window.show();

  return application.exec();
}
