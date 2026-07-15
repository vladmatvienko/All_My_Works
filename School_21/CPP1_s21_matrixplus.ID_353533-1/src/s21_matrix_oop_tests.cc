#include <gtest/gtest.h>

#include <utility>

#include "s21_matrix_oop.h"

namespace {

void FillMatrix(S21Matrix* matrix, const double* values) {
  int index = 0;
  for (int i = 0; i < matrix->GetRows(); ++i) {
    for (int j = 0; j < matrix->GetCols(); ++j) {
      (*matrix)(i, j) = values[index++];
    }
  }
}

void ExpectMatrixNear(const S21Matrix& actual, const S21Matrix& expected) {
  ASSERT_EQ(actual.GetRows(), expected.GetRows());
  ASSERT_EQ(actual.GetCols(), expected.GetCols());
  for (int i = 0; i < actual.GetRows(); ++i) {
    for (int j = 0; j < actual.GetCols(); ++j) {
      EXPECT_NEAR(actual(i, j), expected(i, j), 1e-7);
    }
  }
}

TEST(ConstructorTest, DefaultConstructorCreatesOneByOneZeroMatrix) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetCols(), 1);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
}

TEST(ConstructorTest, ParametrizedConstructorCreatesZeroMatrix) {
  S21Matrix matrix(2, 3);
  EXPECT_EQ(matrix.get_rows(), 2);
  EXPECT_EQ(matrix.get_cols(), 3);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 0.0);
}

TEST(ConstructorTest, ConstructorThrowsOnInvalidSize) {
  EXPECT_THROW(S21Matrix(0, 1), std::invalid_argument);
  EXPECT_THROW(S21Matrix(1, -2), std::invalid_argument);
}

TEST(ConstructorTest, CopyConstructorMakesDeepCopy) {
  S21Matrix source(2, 2);
  double values[] = {1.0, 2.0, 3.0, 4.0};
  FillMatrix(&source, values);

  S21Matrix copy(source);
  source(0, 0) = 100.0;

  EXPECT_DOUBLE_EQ(copy(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(source(0, 0), 100.0);
}

TEST(ConstructorTest, MoveConstructorTransfersData) {
  S21Matrix source(2, 2);
  source(1, 1) = 42.0;

  S21Matrix moved(std::move(source));

  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetCols(), 2);
  EXPECT_DOUBLE_EQ(moved(1, 1), 42.0);
}

TEST(AccessorMutatorTest, SetRowsExpandsAndShrinksMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 4.0;

  matrix.SetRows(3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 2);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(2, 1), 0.0);

  matrix.set_rows(1);
  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_THROW(matrix(1, 1), std::out_of_range);
}

TEST(AccessorMutatorTest, SetColsExpandsAndShrinksMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 4.0;

  matrix.SetCols(3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 0.0);

  matrix.set_cols(1);
  EXPECT_EQ(matrix.GetCols(), 1);
  EXPECT_THROW(matrix(0, 1), std::out_of_range);
}

TEST(AccessorMutatorTest, SetSizeThrowsOnInvalidValue) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.SetRows(0), std::invalid_argument);
  EXPECT_THROW(matrix.SetCols(-1), std::invalid_argument);
}

TEST(OperationTest, EqMatrixUsesEpsilon) {
  S21Matrix left(1, 2);
  S21Matrix right(1, 2);
  left(0, 0) = 1.0;
  left(0, 1) = 2.0;
  right(0, 0) = 1.0 + 1e-8;
  right(0, 1) = 2.0 - 1e-8;

  EXPECT_TRUE(left.EqMatrix(right));
  EXPECT_TRUE(left == right);
}

TEST(OperationTest, SumMatrixAndPlusOperator) {
  S21Matrix left(2, 2);
  S21Matrix right(2, 2);
  S21Matrix expected(2, 2);
  double left_values[] = {1.0, 2.0, 3.0, 4.0};
  double right_values[] = {5.0, 6.0, 7.0, 8.0};
  double expected_values[] = {6.0, 8.0, 10.0, 12.0};
  FillMatrix(&left, left_values);
  FillMatrix(&right, right_values);
  FillMatrix(&expected, expected_values);

  S21Matrix result = left + right;
  ExpectMatrixNear(result, expected);

  left += right;
  ExpectMatrixNear(left, expected);
}

TEST(OperationTest, SubMatrixAndMinusOperator) {
  S21Matrix left(2, 2);
  S21Matrix right(2, 2);
  S21Matrix expected(2, 2);
  double left_values[] = {5.0, 6.0, 7.0, 8.0};
  double right_values[] = {1.0, 2.0, 3.0, 4.0};
  double expected_values[] = {4.0, 4.0, 4.0, 4.0};
  FillMatrix(&left, left_values);
  FillMatrix(&right, right_values);
  FillMatrix(&expected, expected_values);

  S21Matrix result = left - right;
  ExpectMatrixNear(result, expected);

  left -= right;
  ExpectMatrixNear(left, expected);
}

TEST(OperationTest, MulNumberAndNumberOperators) {
  S21Matrix matrix(2, 2);
  S21Matrix expected(2, 2);
  double matrix_values[] = {1.0, -2.0, 3.5, 4.0};
  double expected_values[] = {2.0, -4.0, 7.0, 8.0};
  FillMatrix(&matrix, matrix_values);
  FillMatrix(&expected, expected_values);

  ExpectMatrixNear(matrix * 2.0, expected);
  ExpectMatrixNear(2.0 * matrix, expected);

  matrix *= 2.0;
  ExpectMatrixNear(matrix, expected);
}

TEST(OperationTest, MulMatrixAndMatrixOperator) {
  S21Matrix left(2, 3);
  S21Matrix right(3, 2);
  S21Matrix expected(2, 2);
  double left_values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double right_values[] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
  double expected_values[] = {58.0, 64.0, 139.0, 154.0};
  FillMatrix(&left, left_values);
  FillMatrix(&right, right_values);
  FillMatrix(&expected, expected_values);

  S21Matrix result = left * right;
  ExpectMatrixNear(result, expected);

  left *= right;
  ExpectMatrixNear(left, expected);
}

TEST(OperationTest, Transpose) {
  S21Matrix matrix(2, 3);
  S21Matrix expected(3, 2);
  double matrix_values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double expected_values[] = {1.0, 4.0, 2.0, 5.0, 3.0, 6.0};
  FillMatrix(&matrix, matrix_values);
  FillMatrix(&expected, expected_values);

  ExpectMatrixNear(matrix.Transpose(), expected);
}

TEST(OperationTest, Determinant) {
  S21Matrix matrix(3, 3);
  double values[] = {1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0, 1.0};
  FillMatrix(&matrix, values);

  EXPECT_NEAR(matrix.Determinant(), -40.0, 1e-7);
}

TEST(OperationTest, CalcComplements) {
  S21Matrix matrix(3, 3);
  S21Matrix expected(3, 3);
  double matrix_values[] = {1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0, 1.0};
  double expected_values[] = {0.0, 10.0, -20.0, 4.0, -14.0,
                              8.0, -8.0, -2.0,  4.0};
  FillMatrix(&matrix, matrix_values);
  FillMatrix(&expected, expected_values);

  ExpectMatrixNear(matrix.CalcComplements(), expected);
}

TEST(OperationTest, InverseMatrix) {
  S21Matrix matrix(3, 3);
  S21Matrix expected(3, 3);
  double matrix_values[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};
  double expected_values[] = {1.0,   -1.0, 1.0,   -38.0, 41.0,
                              -34.0, 27.0, -29.0, 24.0};
  FillMatrix(&matrix, matrix_values);
  FillMatrix(&expected, expected_values);

  ExpectMatrixNear(matrix.InverseMatrix(), expected);
}

TEST(OperationTest, OneByOneSpecialCases) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 4.0;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), 4.0);
  EXPECT_DOUBLE_EQ(matrix.CalcComplements()(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix.InverseMatrix()(0, 0), 0.25);
}

TEST(ExceptionTest, ThrowsOnDimensionMismatch) {
  S21Matrix two_by_two(2, 2);
  S21Matrix two_by_three(2, 3);
  S21Matrix three_by_two(3, 2);

  EXPECT_THROW(two_by_two.SumMatrix(two_by_three), std::invalid_argument);
  EXPECT_THROW(two_by_two.SubMatrix(two_by_three), std::invalid_argument);
  EXPECT_THROW(two_by_two + two_by_three, std::invalid_argument);
  EXPECT_THROW(two_by_two - two_by_three, std::invalid_argument);
  EXPECT_NO_THROW(two_by_three * three_by_two);
  EXPECT_THROW(two_by_two.MulMatrix(three_by_two), std::invalid_argument);
}

TEST(ExceptionTest, ThrowsOnNonSquareAndSingularMatrix) {
  S21Matrix non_square(2, 3);
  EXPECT_THROW(non_square.Determinant(), std::invalid_argument);
  EXPECT_THROW(non_square.CalcComplements(), std::invalid_argument);
  EXPECT_THROW(non_square.InverseMatrix(), std::invalid_argument);

  S21Matrix singular(2, 2);
  double values[] = {1.0, 2.0, 2.0, 4.0};
  FillMatrix(&singular, values);
  EXPECT_THROW(singular.InverseMatrix(), std::logic_error);
}

TEST(OperatorTest, AssignmentOperators) {
  S21Matrix matrix(2, 2);
  matrix(0, 1) = 7.0;

  S21Matrix copy;
  copy = matrix;
  matrix(0, 1) = 1.0;
  EXPECT_DOUBLE_EQ(copy(0, 1), 7.0);

  S21Matrix moved;
  moved = std::move(copy);
  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetCols(), 2);
  EXPECT_DOUBLE_EQ(moved(0, 1), 7.0);
}

TEST(OperatorTest, IndexOperatorThrowsOnInvalidIndex) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 2), std::out_of_range);
}

}  // namespace
