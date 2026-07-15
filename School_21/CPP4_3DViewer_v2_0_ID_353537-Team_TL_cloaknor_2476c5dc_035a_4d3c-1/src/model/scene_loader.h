#ifndef SRC_MODEL_SCENE_LOADER_H_
#define SRC_MODEL_SCENE_LOADER_H_

#include <string>

#include "model/scene.h"

namespace s21 {

class SceneLoader {
 public:
  static Scene LoadObjScene(const std::string& path);
};

}  // namespace s21

#endif  // SRC_MODEL_SCENE_LOADER_H_
