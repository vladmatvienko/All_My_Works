#include "view/scene_meta.h"

namespace s21 {

void RegisterSceneMetaType() {
  qRegisterMetaType<Scene>();
  qRegisterMetaType<Scene>("s21::Scene");
  qRegisterMetaType<Scene>("Scene");
}

}  // namespace s21
