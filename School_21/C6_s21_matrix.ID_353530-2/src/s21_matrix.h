#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Коды возврата операций */
#define OK 0
#define ERROR_INCORRECT_MATRIX 1
#define ERROR_CALCULATION 2

/* Коды возврата сравнения */
#define SUCCESS 1
#define FAILURE 0

/* Точность сравнения вещественных чисел */
#define EPSILON 1e-6

/* Структура матрицы */
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/* Создание матрицы */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/* Очистка и уничтожение матрицы */
void s21_remove_matrix(matrix_t *A);

/* Сравнение матриц */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/* Сложение матриц */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Вычитание матриц */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Умножение матрицы на число */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/* Умножение матриц */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Транспонирование матрицы */
int s21_transpose(matrix_t *A, matrix_t *result);

/* Вычисление определителя */
int s21_determinant(matrix_t *A, double *result);

/* Вычисление матрицы алгебраических дополнений */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/* Вычисление обратной матрицы */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/* Вспомогательная функция для вычисления минора */
double s21_get_minor(matrix_t *A, int row, int col);

#endif