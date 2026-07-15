#ifndef SRC_VIEW_SCENE_META_H_
#define SRC_VIEW_SCENE_META_H_

#include <QMetaType>

#include "model/scene.h"

Q_DECLARE_METATYPE(s21::Scene)

namespace s21 {

void RegisterSceneMetaType();

}  // namespace s21

#endif  // SRC_VIEW_SCENE_META_H_
