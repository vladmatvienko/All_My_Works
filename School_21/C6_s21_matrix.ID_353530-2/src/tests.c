#include <check.h>

#include "s21_matrix.h"

/* ==================== CREATE_MATRIX TESTS ==================== */
START_TEST(test_create_matrix_basic) {
  matrix_t test_matrix;
  int res = s21_create_matrix(3, 3, &test_matrix);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(test_matrix.rows, 3);
  ck_assert_int_eq(test_matrix.columns, 3);
  ck_assert_ptr_nonnull(test_matrix.matrix);
  s21_remove_matrix(&test_matrix);
}
END_TEST

START_TEST(test_create_matrix_1x1) {
  matrix_t test_matrix;
  int res = s21_create_matrix(1, 1, &test_matrix);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(test_matrix.rows, 1);
  ck_assert_int_eq(test_matrix.columns, 1);
  s21_remove_matrix(&test_matrix);
}
END_TEST

START_TEST(test_create_matrix_large) {
  matrix_t test_matrix;
  int res = s21_create_matrix(10, 10, &test_matrix);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(test_matrix.rows, 10);
  ck_assert_int_eq(test_matrix.columns, 10);
  s21_remove_matrix(&test_matrix);
}
END_TEST

START_TEST(test_create_matrix_zero_rows) {
  matrix_t test_matrix;
  int res = s21_create_matrix(0, 3, &test_matrix);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_zero_cols) {
  matrix_t test_matrix;
  int res = s21_create_matrix(3, 0, &test_matrix);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_null_ptr) {
  int res = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== REMOVE_MATRIX TESTS ==================== */
START_TEST(test_remove_matrix_basic) {
  matrix_t test_matrix;
  s21_create_matrix(3, 3, &test_matrix);
  s21_remove_matrix(&test_matrix);
  ck_assert_ptr_null(test_matrix.matrix);
  ck_assert_int_eq(test_matrix.rows, 0);
  ck_assert_int_eq(test_matrix.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null) { s21_remove_matrix(NULL); }
END_TEST

/* ==================== EQ_MATRIX TESTS ==================== */
START_TEST(test_eq_matrix_equal) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_not_equal) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  B.matrix[0][0] = 2.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_diff_size) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_precision) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0000001;
  B.matrix[0][0] = 1.0000002;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_null) {
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
}
END_TEST

/* ==================== SUM_MATRIX TESTS ==================== */
START_TEST(test_sum_matrix_basic) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 1.0;

  int res = s21_sum_matrix(&A, &B, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 2.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[0][1], 3.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][0], 4.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][1], 5.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_sum_matrix_diff_size) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  int res = s21_sum_matrix(&A, &B, &R);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_null) {
  int res = s21_sum_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== SUB_MATRIX TESTS ==================== */
START_TEST(test_sub_matrix_basic) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 3.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 1.0;

  int res = s21_sub_matrix(&A, &B, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 4.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[0][1], 2.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][0], 1.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][1], 0.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_sub_matrix_diff_size) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  int res = s21_sub_matrix(&A, &B, &R);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_null) {
  int res = s21_sub_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== MULT_NUMBER TESTS ==================== */
START_TEST(test_mult_number_basic) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int res = s21_mult_number(&A, 2.0, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 2.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[0][1], 4.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][0], 6.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][1], 8.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_number_zero) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 5.0;

  int res = s21_mult_number(&A, 0.0, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 0.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_number_negative) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2.0;

  int res = s21_mult_number(&A, -1.0, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], -2.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_number_null) {
  int res = s21_mult_number(NULL, 2.0, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== MULT_MATRIX TESTS ==================== */
START_TEST(test_mult_matrix_basic) {
  matrix_t A, B, R;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  B.matrix[0][0] = 7;
  B.matrix[0][1] = 8;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 10;
  B.matrix[2][0] = 11;
  B.matrix[2][1] = 12;

  int res = s21_mult_matrix(&A, &B, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(R.rows, 2);
  ck_assert_int_eq(R.columns, 2);
  ck_assert_double_eq_tol(R.matrix[0][0], 58, EPSILON);
  ck_assert_double_eq_tol(R.matrix[0][1], 64, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][0], 139, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][1], 154, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_matrix_incompatible) {
  matrix_t A, B, R;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);

  int res = s21_mult_matrix(&A, &B, &R);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_identity) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;

  int res = s21_mult_matrix(&A, &A, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 1, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][1], 1, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_matrix_null) {
  int res = s21_mult_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== TRANSPOSE TESTS ==================== */
START_TEST(test_transpose_basic) {
  matrix_t A, R;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  int res = s21_transpose(&A, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(R.rows, 3);
  ck_assert_int_eq(R.columns, 2);
  ck_assert_double_eq_tol(R.matrix[0][0], 1.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[0][1], 4.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][0], 2.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][1], 5.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_transpose_square) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int res = s21_transpose(&A, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][1], 3.0, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][0], 2.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_transpose_1x1) {
  matrix_t A, R;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int res = s21_transpose(&A, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 5.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_transpose_null) {
  int res = s21_transpose(NULL, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== DETERMINANT TESTS ==================== */
START_TEST(test_determinant_1x1) {
  matrix_t A;
  double det;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, 5.0, EPSILON);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
  matrix_t A;
  double det;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, -2.0, EPSILON);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3_zero) {
  matrix_t A;
  double det;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3_nonzero) {
  matrix_t A;
  double det;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 1;

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, 1.0, EPSILON);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_non_square) {
  matrix_t A;
  double det;
  s21_create_matrix(2, 3, &A);

  int res = s21_determinant(&A, &det);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_null) {
  int res = s21_determinant(NULL, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== CALC_COMPLEMENTS TESTS ==================== */
START_TEST(test_calc_complements_basic) {
  matrix_t A, R;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(R.rows, 3);
  ck_assert_int_eq(R.columns, 3);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_2x2) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 4, EPSILON);
  ck_assert_double_eq_tol(R.matrix[0][1], -3, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][0], -2, EPSILON);
  ck_assert_double_eq_tol(R.matrix[1][1], 1, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_non_square) {
  matrix_t A, R;
  s21_create_matrix(2, 3, &A);

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_null) {
  int res = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== INVERSE_MATRIX TESTS ==================== */
START_TEST(test_inverse_matrix_basic) {
  matrix_t A, R;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, OK);

  matrix_t E;
  s21_mult_matrix(&A, &R, &E);
  ck_assert_double_eq_tol(E.matrix[0][0], 1.0, EPSILON);
  ck_assert_double_eq_tol(E.matrix[1][1], 1.0, EPSILON);
  ck_assert_double_eq_tol(E.matrix[2][2], 1.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_inverse_matrix_2x2) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, OK);

  matrix_t E;
  s21_mult_matrix(&A, &R, &E);
  ck_assert_double_eq_tol(E.matrix[0][0], 1.0, EPSILON);
  ck_assert_double_eq_tol(E.matrix[1][1], 1.0, EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_inverse_matrix_singular) {
  matrix_t A, R;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, ERROR_CALCULATION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_non_square) {
  matrix_t A, R;
  s21_create_matrix(2, 3, &A);

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_null) {
  int res = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(res, ERROR_INCORRECT_MATRIX);
}
END_TEST

/* ==================== TEST SUITE ==================== */
Suite *matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Matrix Operations");
  tc_core = tcase_create("Core");

  /* Create matrix tests */
  tcase_add_test(tc_core, test_create_matrix_basic);
  tcase_add_test(tc_core, test_create_matrix_1x1);
  tcase_add_test(tc_core, test_create_matrix_large);
  tcase_add_test(tc_core, test_create_matrix_zero_rows);
  tcase_add_test(tc_core, test_create_matrix_zero_cols);
  tcase_add_test(tc_core, test_create_matrix_null_ptr);

  /* Remove matrix tests */
  tcase_add_test(tc_core, test_remove_matrix_basic);
  tcase_add_test(tc_core, test_remove_matrix_null);

  /* Eq matrix tests */
  tcase_add_test(tc_core, test_eq_matrix_equal);
  tcase_add_test(tc_core, test_eq_matrix_not_equal);
  tcase_add_test(tc_core, test_eq_matrix_diff_size);
  tcase_add_test(tc_core, test_eq_matrix_precision);
  tcase_add_test(tc_core, test_eq_matrix_null);

  /* Sum matrix tests */
  tcase_add_test(tc_core, test_sum_matrix_basic);
  tcase_add_test(tc_core, test_sum_matrix_diff_size);
  tcase_add_test(tc_core, test_sum_matrix_null);

  /* Sub matrix tests */
  tcase_add_test(tc_core, test_sub_matrix_basic);
  tcase_add_test(tc_core, test_sub_matrix_diff_size);
  tcase_add_test(tc_core, test_sub_matrix_null);

  /* Mult number tests */
  tcase_add_test(tc_core, test_mult_number_basic);
  tcase_add_test(tc_core, test_mult_number_zero);
  tcase_add_test(tc_core, test_mult_number_negative);
  tcase_add_test(tc_core, test_mult_number_null);

  /* Mult matrix tests */
  tcase_add_test(tc_core, test_mult_matrix_basic);
  tcase_add_test(tc_core, test_mult_matrix_incompatible);
  tcase_add_test(tc_core, test_mult_matrix_identity);
  tcase_add_test(tc_core, test_mult_matrix_null);

  /* Transpose tests */
  tcase_add_test(tc_core, test_transpose_basic);
  tcase_add_test(tc_core, test_transpose_square);
  tcase_add_test(tc_core, test_transpose_1x1);
  tcase_add_test(tc_core, test_transpose_null);

  /* Determinant tests */
  tcase_add_test(tc_core, test_determinant_1x1);
  tcase_add_test(tc_core, test_determinant_2x2);
  tcase_add_test(tc_core, test_determinant_3x3_zero);
  tcase_add_test(tc_core, test_determinant_3x3_nonzero);
  tcase_add_test(tc_core, test_determinant_non_square);
  tcase_add_test(tc_core, test_determinant_null);

  /* Calc complements tests */
  tcase_add_test(tc_core, test_calc_complements_basic);
  tcase_add_test(tc_core, test_calc_complements_2x2);
  tcase_add_test(tc_core, test_calc_complements_non_square);
  tcase_add_test(tc_core, test_calc_complements_null);

  /* Inverse matrix tests */
  tcase_add_test(tc_core, test_inverse_matrix_basic);
  tcase_add_test(tc_core, test_inverse_matrix_2x2);
  tcase_add_test(tc_core, test_inverse_matrix_singular);
  tcase_add_test(tc_core, test_inverse_matrix_non_square);
  tcase_add_test(tc_core, test_inverse_matrix_null);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = matrix_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}