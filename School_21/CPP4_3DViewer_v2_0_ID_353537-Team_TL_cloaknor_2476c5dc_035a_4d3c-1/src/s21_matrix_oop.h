#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <stdexcept>

namespace s21 {

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);

  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(int rows);
  void set_cols(int cols);

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num) noexcept;
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  friend S21Matrix operator*(double num, const S21Matrix& matrix);

 private:
  static constexpr double kEpsilon = 1e-7;

  double** matrix_;
  int rows_;
  int cols_;

  void AllocateMatrix(int rows, int cols);
  void FreeMatrix() noexcept;
  void CopyFrom(const S21Matrix& other);
  void Resize(int new_rows, int new_cols);
  void CheckSameSize(const S21Matrix& other) const;
  void CheckSquare() const;
  void CheckIndexes(int row, int col) const;
  S21Matrix MinorMatrix(int excluded_row, int excluded_col) const;
};

}  // namespace s21

using S21Matrix = s21::S21Matrix;

#endif  // SRC_S21_MATRIX_OOP_H_
