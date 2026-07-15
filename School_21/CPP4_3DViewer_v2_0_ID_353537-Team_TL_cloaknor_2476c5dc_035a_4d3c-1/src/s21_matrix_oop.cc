#include "s21_matrix_oop.h"

namespace s21 {

S21Matrix::S21Matrix() : matrix_(nullptr), rows_(0), cols_(0) {
  AllocateMatrix(1, 1);
}

S21Matrix::S21Matrix(int rows, int cols)
    : matrix_(nullptr), rows_(0), cols_(0) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Matrix dimensions must be positive");
  }
  AllocateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : matrix_(nullptr), rows_(0), cols_(0) {
  CopyFrom(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : matrix_(other.matrix_), rows_(other.rows_), cols_(other.cols_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { FreeMatrix(); }

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int rows) { Resize(rows, cols_); }

void S21Matrix::SetCols(int cols) { Resize(rows_, cols); }

int S21Matrix::get_rows() const noexcept { return GetRows(); }

int S21Matrix::get_cols() const noexcept { return GetCols(); }

void S21Matrix::set_rows(int rows) { SetRows(rows); }

void S21Matrix::set_cols(int cols) { SetCols(cols); }

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool is_equal = rows_ == other.rows_ && cols_ == other.cols_;
  for (int i = 0; is_equal && i < rows_; ++i) {
    for (int j = 0; is_equal && j < cols_; ++j) {
      is_equal = std::fabs(matrix_[i][j] - other.matrix_[i][j]) <= kEpsilon;
    }
  }
  return is_equal;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  CheckSameSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  CheckSameSize(other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns of the first matrix must be equal to the "
        "number of rows of the second matrix");
  }

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  CheckSquare();
  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor = MinorMatrix(i, j);
        double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
        result.matrix_[i][j] = sign * minor.Determinant();
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  CheckSquare();

  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = MinorMatrix(0, j);
      double sign = (j % 2 == 0) ? 1.0 : -1.0;
      result += sign * matrix_[0][j] * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  CheckSquare();
  double determinant = Determinant();
  if (std::fabs(determinant) <= kEpsilon) {
    throw std::logic_error("The matrix determinant is zero");
  }

  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    result = CalcComplements().Transpose();
    result.MulNumber(1.0 / determinant);
  }
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix tmp(other);
    FreeMatrix();
    matrix_ = tmp.matrix_;
    rows_ = tmp.rows_;
    cols_ = tmp.cols_;
    tmp.matrix_ = nullptr;
    tmp.rows_ = 0;
    tmp.cols_ = 0;
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    FreeMatrix();
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) noexcept {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  CheckIndexes(row, col);
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  CheckIndexes(row, col);
  return matrix_[row][col];
}

S21Matrix operator*(double num, const S21Matrix& matrix) {
  return matrix * num;
}

void S21Matrix::AllocateMatrix(int rows, int cols) {
  double** new_matrix = new double* [rows] {};
  try {
    for (int i = 0; i < rows; ++i) {
      new_matrix[i] = new double[cols]{};
    }
  } catch (...) {
    for (int i = 0; i < rows; ++i) {
      delete[] new_matrix[i];
    }
    delete[] new_matrix;
    throw;
  }
  matrix_ = new_matrix;
  rows_ = rows;
  cols_ = cols;
}

void S21Matrix::FreeMatrix() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CopyFrom(const S21Matrix& other) {
  AllocateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::Resize(int new_rows, int new_cols) {
  if (new_rows <= 0 || new_cols <= 0) {
    throw std::invalid_argument("Matrix dimensions must be positive");
  }

  S21Matrix tmp(new_rows, new_cols);
  int copied_rows = rows_ < new_rows ? rows_ : new_rows;
  int copied_cols = cols_ < new_cols ? cols_ : new_cols;
  for (int i = 0; i < copied_rows; ++i) {
    for (int j = 0; j < copied_cols; ++j) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = tmp;
}

void S21Matrix::CheckSameSize(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }
}

void S21Matrix::CheckSquare() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix must be square");
  }
}

void S21Matrix::CheckIndexes(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Matrix index is out of range");
  }
}

S21Matrix S21Matrix::MinorMatrix(int excluded_row, int excluded_col) const {
  S21Matrix result(rows_ - 1, cols_ - 1);
  int result_row = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i != excluded_row) {
      int result_col = 0;
      for (int j = 0; j < cols_; ++j) {
        if (j != excluded_col) {
          result.matrix_[result_row][result_col] = matrix_[i][j];
          ++result_col;
        }
      }
      ++result_row;
    }
  }
  return result;
}

}  // namespace s21
