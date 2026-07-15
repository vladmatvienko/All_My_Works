#ifndef SRC_MODEL_TRANSFORM_MATRIX_H_
#define SRC_MODEL_TRANSFORM_MATRIX_H_

#include "model/geometry.h"
#include "s21_matrix_oop.h"

namespace s21 {

class TransformMatrix {
 public:
  TransformMatrix();
  explicit TransformMatrix(const S21Matrix& matrix);

  Point3D TransformPoint(const Point3D& point) const;
  const S21Matrix& matrix() const noexcept;

 private:
  S21Matrix matrix_;
};

class TransformMatrixBuilder {
 public:
  static TransformMatrix CreateMoveMatrix(double x, double y, double z);
  static TransformMatrix CreateRotationMatrix(double x_degree, double y_degree,
                                              double z_degree);
  static TransformMatrix CreateScaleMatrix(double scale);

 private:
  static S21Matrix CreateIdentity();
  static S21Matrix CreateRotationX(double degree);
  static S21Matrix CreateRotationY(double degree);
  static S21Matrix CreateRotationZ(double degree);
};

}  // namespace s21

#endif  // SRC_MODEL_TRANSFORM_MATRIX_H_
