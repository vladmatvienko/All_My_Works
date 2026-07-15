#include "../s21_decimal.h"
#include "../s21_decimal_test.h"

s21_decimal create_decimal(int low, int mid, int high, int sign, int scale);

// Tests for s21_add
START_TEST(test_s21_add_basic_positive) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{8, 0, 0, 0}};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_negative_positive) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{2, 0, 0, 0x80000000}};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_add_underflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_s21_add_negative_numbers) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{8, 0, 0, 0x80000000}};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_with_zero) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{5, 0, 0, 0}};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_different_scales) {
  s21_decimal a = {{100, 0, 0, 0x00020000}};  // 1.00 (масштаб 2)
  s21_decimal b = {{10, 0, 0, 0x00010000}};   // 1.0 (масштаб 1)
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_add_positive_negative_equal) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_large_numbers) {
  s21_decimal a = {{0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_add_negative_large_numbers) {
  s21_decimal a = {{0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_add_max_scale) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal b = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_add_zero_result) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_mixed_scales) {
  s21_decimal a = {{123, 0, 0, 0x00020000}};  // 1.23
  s21_decimal b = {{456, 0, 0, 0x00030000}};  // 0.456
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

// Tests for s21_sub
START_TEST(test_s21_sub_basic_positive) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{2, 0, 0, 0}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_negative_positive) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{8, 0, 0, 0}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_positive_negative) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{8, 0, 0, 0x80000000}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_negative_negative) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{2, 0, 0, 0x80000000}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_zero_result) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_large_numbers) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_underflow) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_sub_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_s21_sub_with_scale) {
  s21_decimal a = {{500, 0, 0, 0x00010000}};  // 5.00
  s21_decimal b = {{300, 0, 0, 0x00010000}};  // 3.00
  s21_decimal result = {0};
  s21_decimal expected = {{20, 0, 0, 0x00000000}};  // 2.00

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(expected, result), 1);
}
END_TEST

START_TEST(test_s21_sub_different_scales) {
  s21_decimal a = {{50, 0, 0, 0x00010000}};   // 5.0
  s21_decimal b = {{300, 0, 0, 0x00020000}};  // 3.00
  s21_decimal result = {0};
  s21_decimal expected = {{2, 0, 0, 0x00000000}};  // 2.00

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(expected, result), 1);
}
END_TEST

START_TEST(test_s21_sub_negative_result) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{2, 0, 0, 0x80000000}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_sub_equal_magnitude_opposite_signs) {
  s21_decimal a = {{12345, 0, 0, 0}};
  s21_decimal b = {{12345, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{24690, 0, 0, 0}};

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// s21_mul
START_TEST(test_s21_mul_basic_positive) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{15, 0, 0, 0}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_negative_positive) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{15, 0, 0, 0x80000000}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_positive_negative) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{15, 0, 0, 0x80000000}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_negative_negative) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{15, 0, 0, 0}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_mul_underflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{2, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_mul_with_zero) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_zero_with_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_with_scale) {
  s21_decimal a = {{5, 0, 0, 0x00010000}};  // 0.5
  s21_decimal b = {{2, 0, 0, 0x00010000}};  // 0.2
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_different_scales) {
  s21_decimal a = {{123, 0, 0, 0x00020000}};  // 1.23
  s21_decimal b = {{456, 0, 0, 0x00030000}};  // 0.456
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_large_numbers) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_mul_negative_large_numbers) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_s21_mul_max_scale) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal b = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_one_as_operand) {
  s21_decimal a = {{12345, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{12345, 0, 0, 0}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_negative_one_as_operand) {
  s21_decimal a = {{12345, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{12345, 0, 0, 0x80000000}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_small_numbers) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, 0}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_precision_scaling) {
  s21_decimal a = {{123456789, 0, 0, 0x00050000}};  // 1234.56789
  s21_decimal b = {{987654321, 0, 0, 0x00030000}};  // 987.654321
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_boundary_values) {
  s21_decimal a = {{0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_fractional_precision) {
  s21_decimal a = {{12345, 0, 0, 0x00040000}};  // 1.2345
  s21_decimal b = {{10000, 0, 0, 0x00040000}};  // 1.0000
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_edge_case_very_small) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal b = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_edge_case_very_large) {
  s21_decimal a = {{1000000, 0, 0, 0}};
  s21_decimal b = {{1000000, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_mixed_scales) {
  s21_decimal a = {{12345, 0, 0, 0x00030000}};  // 12.345
  s21_decimal b = {{100, 0, 0, 0x00010000}};    // 10.0
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_zero_scale_edge) {
  s21_decimal a = {{123456789, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{123456789, 0, 0, 0}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_repeating_decimal) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_underflow_check) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_overflow_check) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_mul_equal_magnitude_opposite_signs) {
  s21_decimal a = {{12345, 0, 0, 0}};
  s21_decimal b = {{12345, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{152399025, 0, 0, 0x80000000}};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_mul_large_scale_numbers) {
  s21_decimal a = {{123456789, 0, 0, 0x00100000}};  // 12.3456789
  s21_decimal b = {{987654321, 0, 0, 0x00100000}};  // 98.7654321
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_maximum_scale) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal b = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_extreme_values) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_mul_negative_extreme_values) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_mul_mixed_extreme_values) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

// s21_div
START_TEST(test_s21_div_basic_positive) {
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{3, 0, 0, 0}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_negative_positive) {
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{3, 0, 0, 0x80000000}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_positive_negative) {
  s21_decimal a = {{6, 0, 0, 0x80000000}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{3, 0, 0, 0x80000000}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_negative_negative) {
  s21_decimal a = {{6, 0, 0, 0x80000000}};
  s21_decimal b = {{2, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{3, 0, 0, 0}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_by_zero) {
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 3);  // DIV_BY_ZERO
}
END_TEST

START_TEST(test_s21_div_zero_numerator) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_equal_numbers) {
  s21_decimal a = {{7, 0, 0, 0}};
  s21_decimal b = {{7, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, 0}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_with_scale) {
  s21_decimal a = {{12341235, 0, 0, 0x00020000}};  // 5.00
  s21_decimal b = {{5, 0, 0, 0x00030000}};
  s21_decimal result = {0};
  s21_decimal expected = {{24682470, 0, 0, 0x00000000}};  // 2.50

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_different_scales) {
  s21_decimal a = {{1000, 0, 0, 0x00030000}};  // 1.000
  s21_decimal b = {{25, 0, 0, 0x00010000}};    // 2.5
  s21_decimal result = {0};
  s21_decimal expected = {{4, 0, 0, 0x00010000}};  // 0.4

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_large_numbers) {
  s21_decimal a = {{0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_small_numbers) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal b = {{2, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000002
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_precision_loss) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_negative_result) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{6, 0, 0, 0x00010000}};  // 0.6 truncated to 0

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_max_scale_numerator) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_max_scale_denominator) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_both_max_scale) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal b = {{1, 0, 0, 0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, 0}};  // 1

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_div_overflow_check) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_underflow_check) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_repeating_decimal) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_edge_case_very_small) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1000000, 0, 0, 0x00060000}};  // 1,000,000.000000
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_edge_case_very_large) {
  s21_decimal a = {{1000000, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x00060000}};  // 0.000001
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_mixed_signs_with_scale) {
  s21_decimal a = {{12345, 0, 0, 0x00030000}};  // 12.345
  s21_decimal b = {{100, 0, 0, 0x00010000}};    // 10.0
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_zero_scale_edge) {
  s21_decimal a = {{123456789, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_fractional_precision) {
  s21_decimal a = {{1234567, 0, 0, 0x00050000}};  // 12.34567
  s21_decimal b = {{98765, 0, 0, 0x00030000}};    // 98.765
  s21_decimal result = {0};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_div_boundary_values) {
  s21_decimal a = {{0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0}};
  s21_decimal b = {{0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, 0}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

Suite *suite_create_arithmetic(void) {
  Suite *s = suite_create("Arithmetic");
  TCase *tc_arithmetic = tcase_create("Core");

  tcase_add_test(tc_arithmetic, test_s21_add_basic_positive);
  tcase_add_test(tc_arithmetic, test_s21_add_negative_positive);
  tcase_add_test(tc_arithmetic, test_s21_add_overflow);
  tcase_add_test(tc_arithmetic, test_s21_add_underflow);
  tcase_add_test(tc_arithmetic, test_s21_add_negative_numbers);
  tcase_add_test(tc_arithmetic, test_s21_add_with_zero);
  tcase_add_test(tc_arithmetic, test_s21_add_different_scales);
  tcase_add_test(tc_arithmetic, test_s21_add_positive_negative_equal);
  tcase_add_test(tc_arithmetic, test_s21_add_large_numbers);
  tcase_add_test(tc_arithmetic, test_s21_add_negative_large_numbers);
  tcase_add_test(tc_arithmetic, test_s21_add_max_scale);
  tcase_add_test(tc_arithmetic, test_s21_add_zero_result);
  tcase_add_test(tc_arithmetic, test_s21_add_mixed_scales);

  tcase_add_test(tc_arithmetic, test_s21_sub_basic_positive);
  tcase_add_test(tc_arithmetic, test_s21_sub_negative_positive);
  tcase_add_test(tc_arithmetic, test_s21_sub_positive_negative);
  tcase_add_test(tc_arithmetic, test_s21_sub_negative_negative);
  tcase_add_test(tc_arithmetic, test_s21_sub_zero_result);
  tcase_add_test(tc_arithmetic, test_s21_sub_large_numbers);
  tcase_add_test(tc_arithmetic, test_s21_sub_underflow);
  tcase_add_test(tc_arithmetic, test_s21_sub_overflow);
  tcase_add_test(tc_arithmetic, test_s21_sub_with_scale);
  tcase_add_test(tc_arithmetic, test_s21_sub_different_scales);
  tcase_add_test(tc_arithmetic, test_s21_sub_negative_result);
  tcase_add_test(tc_arithmetic, test_s21_sub_equal_magnitude_opposite_signs);

  tcase_add_test(tc_arithmetic, test_s21_mul_basic_positive);
  tcase_add_test(tc_arithmetic, test_s21_mul_negative_positive);
  tcase_add_test(tc_arithmetic, test_s21_mul_positive_negative);
  tcase_add_test(tc_arithmetic, test_s21_mul_negative_negative);
  tcase_add_test(tc_arithmetic, test_s21_mul_overflow);
  tcase_add_test(tc_arithmetic, test_s21_mul_underflow);
  tcase_add_test(tc_arithmetic, test_s21_mul_with_zero);
  tcase_add_test(tc_arithmetic, test_s21_mul_zero_with_zero);
  tcase_add_test(tc_arithmetic, test_s21_mul_with_scale);
  tcase_add_test(tc_arithmetic, test_s21_mul_different_scales);
  tcase_add_test(tc_arithmetic, test_s21_mul_large_numbers);
  tcase_add_test(tc_arithmetic, test_s21_mul_negative_large_numbers);
  tcase_add_test(tc_arithmetic, test_s21_mul_max_scale);
  tcase_add_test(tc_arithmetic, test_s21_mul_one_as_operand);
  tcase_add_test(tc_arithmetic, test_s21_mul_negative_one_as_operand);
  tcase_add_test(tc_arithmetic, test_s21_mul_small_numbers);
  tcase_add_test(tc_arithmetic, test_s21_mul_precision_scaling);
  tcase_add_test(tc_arithmetic, test_s21_mul_boundary_values);
  tcase_add_test(tc_arithmetic, test_s21_mul_fractional_precision);
  tcase_add_test(tc_arithmetic, test_s21_mul_edge_case_very_small);
  tcase_add_test(tc_arithmetic, test_s21_mul_edge_case_very_large);
  tcase_add_test(tc_arithmetic, test_s21_mul_mixed_scales);
  tcase_add_test(tc_arithmetic, test_s21_mul_zero_scale_edge);
  tcase_add_test(tc_arithmetic, test_s21_mul_repeating_decimal);
  tcase_add_test(tc_arithmetic, test_s21_mul_underflow_check);
  tcase_add_test(tc_arithmetic, test_s21_mul_overflow_check);
  tcase_add_test(tc_arithmetic, test_s21_mul_equal_magnitude_opposite_signs);
  tcase_add_test(tc_arithmetic, test_s21_mul_large_scale_numbers);
  tcase_add_test(tc_arithmetic, test_s21_mul_maximum_scale);
  tcase_add_test(tc_arithmetic, test_s21_mul_extreme_values);
  tcase_add_test(tc_arithmetic, test_s21_mul_negative_extreme_values);
  tcase_add_test(tc_arithmetic, test_s21_mul_mixed_extreme_values);

  tcase_add_test(tc_arithmetic, test_s21_div_basic_positive);
  tcase_add_test(tc_arithmetic, test_s21_div_negative_positive);
  tcase_add_test(tc_arithmetic, test_s21_div_positive_negative);
  tcase_add_test(tc_arithmetic, test_s21_div_negative_negative);
  tcase_add_test(tc_arithmetic, test_s21_div_by_zero);
  tcase_add_test(tc_arithmetic, test_s21_div_zero_numerator);
  tcase_add_test(tc_arithmetic, test_s21_div_equal_numbers);
  tcase_add_test(tc_arithmetic, test_s21_div_with_scale);
  tcase_add_test(tc_arithmetic, test_s21_div_different_scales);
  tcase_add_test(tc_arithmetic, test_s21_div_large_numbers);
  tcase_add_test(tc_arithmetic, test_s21_div_small_numbers);
  tcase_add_test(tc_arithmetic, test_s21_div_precision_loss);
  tcase_add_test(tc_arithmetic, test_s21_div_negative_result);
  tcase_add_test(tc_arithmetic, test_s21_div_max_scale_numerator);
  tcase_add_test(tc_arithmetic, test_s21_div_max_scale_denominator);
  tcase_add_test(tc_arithmetic, test_s21_div_both_max_scale);
  tcase_add_test(tc_arithmetic, test_s21_div_overflow_check);
  tcase_add_test(tc_arithmetic, test_s21_div_underflow_check);
  tcase_add_test(tc_arithmetic, test_s21_div_repeating_decimal);
  tcase_add_test(tc_arithmetic, test_s21_div_edge_case_very_small);
  tcase_add_test(tc_arithmetic, test_s21_div_edge_case_very_large);
  tcase_add_test(tc_arithmetic, test_s21_div_mixed_signs_with_scale);
  tcase_add_test(tc_arithmetic, test_s21_div_zero_scale_edge);
  tcase_add_test(tc_arithmetic, test_s21_div_fractional_precision);
  tcase_add_test(tc_arithmetic, test_s21_div_boundary_values);

  suite_add_tcase(s, tc_arithmetic);
  return s;
}
