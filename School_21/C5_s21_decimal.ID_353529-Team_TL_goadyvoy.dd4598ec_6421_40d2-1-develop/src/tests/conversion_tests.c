#include "../s21_decimal.h"
#include "../s21_decimal_test.h"

START_TEST(test_s21_from_int_to_decimal_01_positive) {
  int src = 123;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq(s21_get_sign(dst), 0);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_02_negative) {
  int src = -456;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], 456);
  ck_assert_int_eq(s21_get_sign(dst), 1);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_03_zero) {
  int src = 0;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(dst), 0);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_04_INT_MAX) {
  int src = INT_MAX;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], INT_MAX);
  ck_assert_int_eq(s21_get_sign(dst), 0);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_05_INT_MIN) {
  int src = INT_MIN;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], 2147483648U);
  ck_assert_int_eq(s21_get_sign(dst), 1);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_06_null_dst) {
  int src = 123;
  int status = s21_from_int_to_decimal(src, NULL);
  ck_assert_int_eq(status, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_07_large_positive_int) {
  int src = 2000000000;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], src);
  ck_assert_int_eq(s21_get_sign(dst), 0);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_08_large_negative_int) {
  int src = -2000000000;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], 2000000000U);
  ck_assert_int_eq(s21_get_sign(dst), 1);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_09_single_digit_positive) {
  int src = 7;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], 7);
  ck_assert_int_eq(s21_get_sign(dst), 0);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_10_single_digit_negative) {
  int src = -9;
  s21_decimal dst;
  int status = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst.bits[0], 9);
  ck_assert_int_eq(s21_get_sign(dst), 1);
  ck_assert_int_eq(s21_getscale(dst), 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_01_positive_exact) {
  s21_decimal src = create_decimal(123, 0, 0, 0, 0);
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, 123);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_02_negative_exact) {
  s21_decimal src = create_decimal(456, 0, 0, 1, 0);
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, -456);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_03_positive_with_scale_discard) {
  s21_decimal src = create_decimal(12345, 0, 0, 0, 2);  // 123.45
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, 123);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_04_negative_with_scale_discard) {
  s21_decimal src = create_decimal(12345, 0, 0, 1, 2);  // -123.45
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, -123);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_05_zero) {
  s21_decimal src = create_decimal(0, 0, 0, 0, 0);
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_06_large_number_fits_int) {
  s21_decimal src = {{1234567890, 0, 0, 0}};
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, 1234567890);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_07_overflow_positive) {
  s21_decimal src = {{0x80000000, 0, 0, 0}};
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_08_overflow_negative) {
  s21_decimal src_int_min = {{0x80000000u, 0u, 0u, (1u << 31)}};
  int dst_int_min;
  int status_int_min = s21_from_decimal_to_int(src_int_min, &dst_int_min);
  ck_assert_int_eq(status_int_min, S21_OK);
  ck_assert_int_eq(dst_int_min, INT_MIN);
  s21_decimal src_too_small = {{0x80000001u, 0u, 0u, (1u << 31)}};
  int dst_too_small;
  int status_too_small = s21_from_decimal_to_int(src_too_small, &dst_too_small);
  ck_assert_int_eq(status_too_small, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_09_null_dst) {
  s21_decimal src = create_decimal(123, 0, 0, 0, 0);
  int status = s21_from_decimal_to_int(src, NULL);
  ck_assert_int_eq(status, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_10_large_with_scale_fits) {
  s21_decimal src = {{1234567890, 0, 0, 0}};  // 1234567890
  s21_setscale(&src, 0);
  int dst;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, 1234567890);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_11_negative_zero) {
  s21_decimal src = create_decimal(0, 0, 0, 1, 0);
  int dst = 12345;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_12_scale_to_zero_ok) {
  s21_decimal src = create_decimal(5, 0, 0, 0, 28);
  int dst = -1;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_13_nonzero_high_words_error) {
  s21_decimal src = create_decimal(0, 0, 1, 0, 1);
  int dst = 0;
  int status = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(status, S21_CONVERSION_ERROR);
}
END_TEST

// --- Тесты для s21_from_float_to_decimal---

START_TEST(test_s21_from_float_to_decimal_01_positive) {
  float src = 123.45f;
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(s21_get_sign(dst), 0);
  ck_assert_int_eq(dst.bits[0], 1234500);
  ck_assert_int_eq(s21_getscale(dst), 4);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_02_negative) {
  float src = -678.90f;
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(s21_get_sign(dst), 1);
  ck_assert_int_eq(dst.bits[0], 6789000);
  ck_assert_int_eq(s21_getscale(dst), 4);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_13_negative_zero_sign_cleared) {
  float src = -0.0f;
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(s21_getscale(dst), 0);
  ck_assert_int_eq(s21_get_sign(dst), 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_14_scale_gt_28_error) {
  float src = 1.000001e-28f;  // 0.0000000000000000000000000001
  s21_decimal dst;
  int status = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(status, S21_OK);
}
END_TEST

// --- Тесты для s21_from_decimal_to_float---

START_TEST(test_s21_from_decimal_to_float_01_positive) {
  s21_decimal src = create_decimal(12345, 0, 0, 0, 2);  // 123.45
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_float_eq(dst, 123.45f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_02_negative) {
  s21_decimal src = create_decimal(67890, 0, 0, 1, 1);  // -6789.0
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_float_eq(dst, -6789.0f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_03_zero) {
  s21_decimal src = create_decimal(0, 0, 0, 0, 0);
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_float_eq(dst, 0.0f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_04_null_dst) {
  s21_decimal src = create_decimal(123, 0, 0, 0, 0);
  int status = s21_from_decimal_to_float(src, NULL);
  ck_assert_int_eq(status, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_05_large_number) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF, 0}};
  s21_setscale(&src, 20);
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_msg(!isinf(dst), "Не бесконечность");
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_06_small_number) {
  s21_decimal src = {{1, 0, 0, (1 << 16)}};
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_float_eq(dst, 0.1f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_07_very_small_number) {
  s21_decimal src = {{1, 0, 0, (30 << 16)}};
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_float_eq(dst, 1e-30f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_08_precision_loss_scenario) {
  float original_float = 1.234567890123456789f;
  s21_decimal dec_val;
  int status_to_dec = s21_from_float_to_decimal(original_float, &dec_val);
  ck_assert_int_eq(status_to_dec, S21_OK);

  float converted_float;
  int status_to_float = s21_from_decimal_to_float(dec_val, &converted_float);
  ck_assert_int_eq(status_to_float, S21_OK);
  ck_assert_float_le(fabsf(converted_float - original_float),
                     FLT_EPSILON * 100);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_09_with_middle_bits) {
  s21_decimal src = {{0xFFFFFFFF, 0x1, 0, 0}};
  s21_setscale(&src, 5);
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_msg(!isinf(dst), "Не бесконечность");
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_10_with_high_bits) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0x1, 0}};
  s21_setscale(&src, 10);
  float dst;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_msg(!isinf(dst), "Не бесконечность");
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_11_subnormal_error) {
  // 1e-39
  s21_decimal src = create_decimal(1, 0, 0, 0, 39);
  float dst = 0.0f;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_12_negative_zero_to_zero_value) {
  s21_decimal src = create_decimal(0, 0, 0, 1, 0);  // -0
  float dst = 1.0f;
  int status = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(status, S21_OK);
  ck_assert(fabsf(dst) <= 0.0f);
}
END_TEST

Suite *suite_create_conversion(void) {
  Suite *s = suite_create("Conversion");
  TCase *tc_convert = tcase_create("Core");

  tcase_add_test(tc_convert, test_s21_from_int_to_decimal_01_positive);
  tcase_add_test(tc_convert, test_s21_from_int_to_decimal_02_negative);
  tcase_add_test(tc_convert, test_s21_from_int_to_decimal_03_zero);
  tcase_add_test(tc_convert, test_s21_from_int_to_decimal_04_INT_MAX);
  tcase_add_test(tc_convert, test_s21_from_int_to_decimal_05_INT_MIN);
  tcase_add_test(tc_convert, test_s21_from_int_to_decimal_06_null_dst);
  tcase_add_test(tc_convert,
                 test_s21_from_int_to_decimal_07_large_positive_int);
  tcase_add_test(tc_convert,
                 test_s21_from_int_to_decimal_08_large_negative_int);
  tcase_add_test(tc_convert,
                 test_s21_from_int_to_decimal_09_single_digit_positive);
  tcase_add_test(tc_convert,
                 test_s21_from_int_to_decimal_10_single_digit_negative);

  // Тесты для s21_from_decimal_to_int
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_01_positive_exact);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_02_negative_exact);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_int_03_positive_with_scale_discard);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_int_04_negative_with_scale_discard);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_05_zero);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_int_06_large_number_fits_int);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_07_overflow_positive);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_08_overflow_negative);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_09_null_dst);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_int_10_large_with_scale_fits);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_11_negative_zero);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_int_12_scale_to_zero_ok);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_int_13_nonzero_high_words_error);

  // Тесты для s21_from_float_to_decimal
  tcase_add_test(tc_convert, test_s21_from_float_to_decimal_01_positive);
  tcase_add_test(tc_convert, test_s21_from_float_to_decimal_02_negative);
  tcase_add_test(tc_convert,
                 test_s21_from_float_to_decimal_13_negative_zero_sign_cleared);
  tcase_add_test(tc_convert,
                 test_s21_from_float_to_decimal_14_scale_gt_28_error);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_01_positive);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_02_negative);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_03_zero);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_04_null_dst);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_05_large_number);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_06_small_number);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_float_07_very_small_number);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_float_08_precision_loss_scenario);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_float_09_with_middle_bits);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_10_with_high_bits);
  tcase_add_test(tc_convert, test_s21_from_decimal_to_float_11_subnormal_error);
  tcase_add_test(tc_convert,
                 test_s21_from_decimal_to_float_12_negative_zero_to_zero_value);

  suite_add_tcase(s, tc_convert);
  return s;
}