#ifndef SRC_MODEL_SCENE_OBJECT_H_
#define SRC_MODEL_SCENE_OBJECT_H_

namespace s21 {

class TransformMatrix;

class SceneObject {
 public:
  virtual ~SceneObject() = default;
  virtual void Transform(const TransformMatrix& matrix) = 0;
};

}  // namespace s21

#endif  // SRC_MODEL_SCENE_OBJECT_H_
