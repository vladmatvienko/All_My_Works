#include "../s21_decimal.h"
#include "../s21_decimal_test.h"

// Tests for s21_is_less
START_TEST(test_s21_is_less_positive_positive_less) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(2, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_positive_positive_greater) {
  s21_decimal value_1 = create_decimal(2, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_positive_negative) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 1, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_negative_positive) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 1, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_scales) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 1);
  s21_decimal value_2 = create_decimal(10, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_large_numbers) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST
START_TEST(test_s21_is_less_zero_positive) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_zero_negative) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = create_decimal(1, 0, 0, 1, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_negative_negative_less) {
  s21_decimal value_1 = create_decimal(2, 0, 0, 1, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 1, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_scales_negative) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 1, 1);
  s21_decimal value_2 = create_decimal(10, 0, 0, 1, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_large_scales) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 20);
  s21_decimal value_2 = create_decimal(1000, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_near_max_values) {
  s21_decimal value_1 = {{MAX4BITE - 1, MAX4BITE, MAX4BITE, 0}};
  s21_decimal value_2 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

// Tests for s21_is_less_or_equal
START_TEST(test_s21_is_less_or_equal_less) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(2, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_greater) {
  s21_decimal value_1 = create_decimal(2, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_scales) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 1);
  s21_decimal value_2 = create_decimal(10, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
}
END_TEST

// Tests for s21_is_greater
START_TEST(test_s21_is_greater_greater) {
  s21_decimal value_1 = create_decimal(2, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_less) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(2, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_scales) {
  s21_decimal value_1 = create_decimal(10, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

// Tests for s21_is_greater_or_equal
START_TEST(test_s21_is_greater_or_equal_greater) {
  s21_decimal value_1 = create_decimal(2, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_less) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(2, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_scales) {
  s21_decimal value_1 = create_decimal(10, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
}
END_TEST

// Tests for s21_is_equal
START_TEST(test_s21_is_equal_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_not_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(2, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_different_signs) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 1, 0);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_scales) {
  s21_decimal value_1 = create_decimal(10, 0, 0, 0, 1);
  s21_decimal value_2 = create_decimal(10, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_large_numbers) {
  s21_decimal value_1 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal value_2 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_zero_with_scale) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, (10 << 16)}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

// Tests for s21_is_not_equal
START_TEST(test_s21_is_not_equal_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_not_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(2, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_different_signs) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 1, 0);
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_scales) {
  s21_decimal value_1 = create_decimal(10, 0, 0, 0, 1);
  s21_decimal value_2 = create_decimal(10, 0, 0, 0, 0);
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(test_abs_compare_positive_positive_less) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(2, 0, 0, 0, 0);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_abs_compare_positive_positive_greater) {
  s21_decimal value_1 = create_decimal(2, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_abs_compare_positive_positive_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 0, 0);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_abs_compare_scales) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 0, 1);
  s21_decimal value_2 = create_decimal(10, 0, 0, 0, 0);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_abs_compare_large_numbers) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_abs_compare_max_values) {
  s21_decimal value_1 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal value_2 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_compare_abs_negative_numbers_less) {
  s21_decimal value_1 = create_decimal(2, 0, 0, 1, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 1, 0);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_compare_abs_negative_numbers_equal) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 1, 0);
  s21_decimal value_2 = create_decimal(1, 0, 0, 1, 0);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_compare_abs_scales_and_negative) {
  s21_decimal value_1 = create_decimal(1, 0, 0, 1, 1);
  s21_decimal value_2 = create_decimal(10, 0, 0, 1, 0);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_abs_compare_zero_values_both_zero) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_abs_compare_zero_values_one_scaled) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = create_decimal(0, 0, 0, 0, 10);
  int result = 0;
  compare_abs(value_1, value_2, &result);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *suite_create_compare(void) {
  Suite *s = suite_create("Comparison");
  TCase *tc_compare = tcase_create("Core");

  tcase_add_test(tc_compare, test_s21_is_less_positive_positive_less);
  tcase_add_test(tc_compare, test_s21_is_less_positive_positive_greater);
  tcase_add_test(tc_compare, test_s21_is_less_positive_negative);
  tcase_add_test(tc_compare, test_s21_is_less_negative_positive);
  tcase_add_test(tc_compare, test_s21_is_less_scales);
  tcase_add_test(tc_compare, test_s21_is_less_large_numbers);
  tcase_add_test(tc_compare, test_s21_is_less_zero_positive);
  tcase_add_test(tc_compare, test_s21_is_less_zero_negative);
  tcase_add_test(tc_compare, test_s21_is_less_negative_negative_less);
  tcase_add_test(tc_compare, test_s21_is_less_scales_negative);
  tcase_add_test(tc_compare, test_s21_is_less_large_scales);
  tcase_add_test(tc_compare, test_s21_is_less_near_max_values);

  tcase_add_test(tc_compare, test_s21_is_less_or_equal_less);
  tcase_add_test(tc_compare, test_s21_is_less_or_equal_equal);
  tcase_add_test(tc_compare, test_s21_is_less_or_equal_greater);
  tcase_add_test(tc_compare, test_s21_is_less_or_equal_scales);

  tcase_add_test(tc_compare, test_s21_is_greater_greater);
  tcase_add_test(tc_compare, test_s21_is_greater_equal);
  tcase_add_test(tc_compare, test_s21_is_greater_less);
  tcase_add_test(tc_compare, test_s21_is_greater_scales);

  tcase_add_test(tc_compare, test_s21_is_greater_or_equal_greater);
  tcase_add_test(tc_compare, test_s21_is_greater_or_equal_equal);
  tcase_add_test(tc_compare, test_s21_is_greater_or_equal_less);
  tcase_add_test(tc_compare, test_s21_is_greater_or_equal_scales);

  tcase_add_test(tc_compare, test_s21_is_equal_equal);
  tcase_add_test(tc_compare, test_s21_is_equal_not_equal);
  tcase_add_test(tc_compare, test_s21_is_equal_different_signs);
  tcase_add_test(tc_compare, test_s21_is_equal_scales);
  tcase_add_test(tc_compare, test_s21_is_equal_large_numbers);
  tcase_add_test(tc_compare, test_s21_is_equal_zero_with_scale);

  tcase_add_test(tc_compare, test_s21_is_not_equal_equal);
  tcase_add_test(tc_compare, test_s21_is_not_equal_not_equal);
  tcase_add_test(tc_compare, test_s21_is_not_equal_different_signs);
  tcase_add_test(tc_compare, test_s21_is_not_equal_scales);

  tcase_add_test(tc_compare, test_abs_compare_positive_positive_less);
  tcase_add_test(tc_compare, test_abs_compare_positive_positive_greater);
  tcase_add_test(tc_compare, test_abs_compare_positive_positive_equal);
  tcase_add_test(tc_compare, test_abs_compare_scales);
  tcase_add_test(tc_compare, test_abs_compare_large_numbers);
  tcase_add_test(tc_compare, test_abs_compare_max_values);
  tcase_add_test(tc_compare, test_compare_abs_negative_numbers_less);
  tcase_add_test(tc_compare, test_compare_abs_negative_numbers_equal);
  tcase_add_test(tc_compare, test_compare_abs_scales_and_negative);
  tcase_add_test(tc_compare, test_abs_compare_zero_values_both_zero);
  tcase_add_test(tc_compare, test_abs_compare_zero_values_one_scaled);
  suite_add_tcase(s, tc_compare);
  return s;
}
