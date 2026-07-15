#include "s21_matrix.h"

/* Создание матрицы */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  /* Проверка аргументов (допустимый выход) */
  if (result == NULL || rows <= 0 || columns <= 0) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)calloc(rows, sizeof(double *));

  if (result->matrix == NULL) {
    status = ERROR_CALCULATION;
    return status;
  }

  /* Выделение памяти под элементы матрицы */
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      /* Очистка памяти при ошибке выделения */
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      result->matrix = NULL;
      status = ERROR_CALCULATION;
      return status;
    }
  }
  return status;
}

/* Очистка и уничтожение матрицы */
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

/* Сравнение матриц */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  /* Проверка аргументов */
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    result = FAILURE;
    return result;
  }
  /* Проверка размеров */
  if (A->rows != B->rows || A->columns != B->columns) {
    result = FAILURE;
    return result;
  }

  /* Попиксельное сравнение с учетом точности */
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
        result = FAILURE;
        return result;
      }
    }
  }
  return result;
}

/* Сложение матриц */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  /* Проверка аргументов и размеров */
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->rows != B->rows || A->columns != B->columns) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return status;
}

/* Вычитание матриц */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  /* Проверка аргументов и размеров */
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->rows != B->rows || A->columns != B->columns) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return status;
}

/* Умножение матрицы на число */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;
  /* Проверка аргументов */
  if (A == NULL || result == NULL || A->matrix == NULL) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return status;
}

/* Умножение матриц */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  /* Проверка совместимости размеров */
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->columns != B->rows) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  status = s21_create_matrix(A->rows, B->columns, result);
  if (status != OK) {
    return status;
  }

  /* Вычисление произведения */
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return status;
}

/* Транспонирование матрицы */
int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = OK;
  /* Проверка аргументов */
  if (A == NULL || result == NULL || A->matrix == NULL) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  status = s21_create_matrix(A->columns, A->rows, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return status;
}

/* Вычисление минора (вспомогательная функция) */
double s21_get_minor(matrix_t *A, int row, int col) {
  matrix_t minor_matrix = {0};
  double det = 0;
  /* Создание матрицы порядка n-1 */
  if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix) != OK) {
    return 0;
  }

  /* Заполнение минора исключением строки и столбца */
  for (int i = 0, k = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int j = 0, l = 0; j < A->columns; j++) {
      if (j == col) continue;
      minor_matrix.matrix[k][l] = A->matrix[i][j];
      l++;
    }
    k++;
  }

  s21_determinant(&minor_matrix, &det);
  s21_remove_matrix(&minor_matrix);
  return det;
}

/* Вычисление определителя */
int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  /* Проверка аргументов и квадратности */
  if (A == NULL || result == NULL || A->matrix == NULL ||
      A->rows != A->columns) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return status;
  }

  if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return status;
  }

  *result = 0;
  /* Разложение по первой строке */
  for (int j = 0; j < A->columns; j++) {
    double minor = s21_get_minor(A, 0, j);
    if (j % 2 == 0) {
      *result += A->matrix[0][j] * minor;
    } else {
      *result -= A->matrix[0][j] * minor;
    }
  }
  return status;
}

/* Вычисление матрицы алгебраических дополнений */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  /* Проверка аргументов и квадратности */
  if (A == NULL || result == NULL || A->matrix == NULL ||
      A->rows != A->columns) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double minor = s21_get_minor(A, i, j);
      if ((i + j) % 2 == 0) {
        result->matrix[i][j] = minor;
      } else {
        result->matrix[i][j] = -minor;
      }
    }
  }
  return status;
}

/* Вычисление обратной матрицы */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  double det = 0;
  matrix_t complements = {0};
  matrix_t trans_complements = {0};

  /* Проверка аргументов и квадратности */
  if (A == NULL || result == NULL || A->matrix == NULL ||
      A->rows != A->columns) {
    status = ERROR_INCORRECT_MATRIX;
    return status;
  }

  /* Вычисление определителя */
  status = s21_determinant(A, &det);
  if (status != OK || fabs(det) < EPSILON) {
    status = ERROR_CALCULATION;
    return status;
  }

  /* Вычисление матрицы алгебраических дополнений */
  status = s21_calc_complements(A, &complements);
  if (status != OK) {
    return status;
  }

  /* Транспонирование матрицы дополнений */
  status = s21_transpose(&complements, &trans_complements);
  if (status != OK) {
    s21_remove_matrix(&complements);
    return status;
  }

  /* Умножение на 1/det */
  status = s21_mult_number(&trans_complements, 1.0 / det, result);

  /* Очистка временных матриц */
  s21_remove_matrix(&complements);
  s21_remove_matrix(&trans_complements);

  return status;
}