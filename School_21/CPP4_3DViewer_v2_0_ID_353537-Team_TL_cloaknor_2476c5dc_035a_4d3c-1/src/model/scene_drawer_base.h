#ifndef SRC_MODEL_SCENE_DRAWER_BASE_H_
#define SRC_MODEL_SCENE_DRAWER_BASE_H_

#include "model/render_settings.h"
#include "model/scene.h"

namespace s21 {

class SceneDrawerBase {
 public:
  virtual ~SceneDrawerBase() = default;
  virtual void DrawScene(const Scene& scene, const RenderSettings& settings,
                         int viewport_width, int viewport_height) = 0;
};

}  // namespace s21

#endif  // SRC_MODEL_SCENE_DRAWER_BASE_H_
