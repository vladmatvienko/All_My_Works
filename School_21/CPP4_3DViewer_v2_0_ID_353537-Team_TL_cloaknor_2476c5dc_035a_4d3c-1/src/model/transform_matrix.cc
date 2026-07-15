#include "model/transform_matrix.h"

#include <cmath>
#include <stdexcept>

namespace s21 {
namespace {
constexpr double kPi = 3.14159265358979323846;

double ToRadians(double degree) { return degree * kPi / 180.0; }
}  // namespace

TransformMatrix::TransformMatrix()
    : matrix_(TransformMatrixBuilder::CreateScaleMatrix(1.0).matrix()) {}

TransformMatrix::TransformMatrix(const S21Matrix& matrix) : matrix_(matrix) {
  if (matrix_.GetRows() != 4 || matrix_.GetCols() != 4) {
    throw std::invalid_argument("Transform matrix must be 4x4");
  }
}

Point3D TransformMatrix::TransformPoint(const Point3D& point) const {
  S21Matrix vector(4, 1);
  vector(0, 0) = point.x;
  vector(1, 0) = point.y;
  vector(2, 0) = point.z;
  vector(3, 0) = 1.0;

  S21Matrix result = matrix_ * vector;
  double w = result(3, 0);
  if (std::fabs(w) < 1e-12) {
    w = 1.0;
  }
  return {result(0, 0) / w, result(1, 0) / w, result(2, 0) / w};
}

const S21Matrix& TransformMatrix::matrix() const noexcept { return matrix_; }

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(double x, double y,
                                                         double z) {
  S21Matrix result = CreateIdentity();
  result(0, 3) = x;
  result(1, 3) = y;
  result(2, 3) = z;
  return TransformMatrix(result);
}

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(double x_degree,
                                                             double y_degree,
                                                             double z_degree) {
  S21Matrix result = CreateRotationZ(z_degree) * CreateRotationY(y_degree) *
                     CreateRotationX(x_degree);
  return TransformMatrix(result);
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(double scale) {
  if (std::fabs(scale) < 1e-12) {
    throw std::invalid_argument("Scale must not be zero");
  }
  S21Matrix result = CreateIdentity();
  result(0, 0) = scale;
  result(1, 1) = scale;
  result(2, 2) = scale;
  return TransformMatrix(result);
}

S21Matrix TransformMatrixBuilder::CreateIdentity() {
  S21Matrix result(4, 4);
  for (int i = 0; i < 4; ++i) {
    result(i, i) = 1.0;
  }
  return result;
}

S21Matrix TransformMatrixBuilder::CreateRotationX(double degree) {
  S21Matrix result = CreateIdentity();
  const double radians = ToRadians(degree);
  const double cos_value = std::cos(radians);
  const double sin_value = std::sin(radians);
  result(1, 1) = cos_value;
  result(1, 2) = -sin_value;
  result(2, 1) = sin_value;
  result(2, 2) = cos_value;
  return result;
}

S21Matrix TransformMatrixBuilder::CreateRotationY(double degree) {
  S21Matrix result = CreateIdentity();
  const double radians = ToRadians(degree);
  const double cos_value = std::cos(radians);
  const double sin_value = std::sin(radians);
  result(0, 0) = cos_value;
  result(0, 2) = sin_value;
  result(2, 0) = -sin_value;
  result(2, 2) = cos_value;
  return result;
}

S21Matrix TransformMatrixBuilder::CreateRotationZ(double degree) {
  S21Matrix result = CreateIdentity();
  const double radians = ToRadians(degree);
  const double cos_value = std::cos(radians);
  const double sin_value = std::sin(radians);
  result(0, 0) = cos_value;
  result(0, 1) = -sin_value;
  result(1, 0) = sin_value;
  result(1, 1) = cos_value;
  return result;
}

}  // namespace s21
