#ifndef SRC_MODEL_OPENGL_SCENE_DRAWER_H_
#define SRC_MODEL_OPENGL_SCENE_DRAWER_H_

#include "model/scene_drawer_base.h"

namespace s21 {

class OpenGLSceneDrawer final : public SceneDrawerBase {
 public:
  void DrawScene(const Scene& scene, const RenderSettings& settings,
                 int viewport_width, int viewport_height) override;

 private:
  static void ApplyProjection(const RenderSettings& settings,
                              int viewport_width, int viewport_height);
  static void DrawEdges(const Figure& figure, const RenderSettings& settings);
  static void DrawVertices(const Figure& figure,
                           const RenderSettings& settings);
};

}  // namespace s21

#endif  // SRC_MODEL_OPENGL_SCENE_DRAWER_H_
