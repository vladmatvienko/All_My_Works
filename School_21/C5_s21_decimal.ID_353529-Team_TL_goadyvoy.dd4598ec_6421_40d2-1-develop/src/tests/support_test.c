#include "../s21_decimal.h"
#include "../s21_decimal_test.h"

// --- Тесты для s21_getbit ---
START_TEST(test_s21_getbit_low_bit) {
  unsigned int byte = 0b00000001;
  ck_assert_int_eq(s21_getbit(byte, 0), 1);
  ck_assert_int_eq(s21_getbit(byte, 1), 0);
}
END_TEST

START_TEST(test_s21_getbit_high_bit) {
  unsigned int byte = 0x80000000;  // 1000...0000
  ck_assert_int_eq(s21_getbit(byte, 31), 1);
  ck_assert_int_eq(s21_getbit(byte, 30), 0);
}
END_TEST

START_TEST(test_s21_getbit_middle_bit) {
  unsigned int byte = 0b00000000000000000000000001000000;  // 2^6
  ck_assert_int_eq(s21_getbit(byte, 6), 1);
  ck_assert_int_eq(s21_getbit(byte, 5), 0);
  ck_assert_int_eq(s21_getbit(byte, 7), 0);
}
END_TEST

START_TEST(test_s21_getbit_all_ones) {
  unsigned int byte = 0xFFFFFFFF;
  for (int i = 0; i < 32; i++) {
    ck_assert_int_eq(s21_getbit(byte, i), 1);
  }
}
END_TEST

START_TEST(test_s21_getbit_all_zeros) {
  unsigned int byte = 0x00000000;
  for (int i = 0; i < 32; i++) {
    ck_assert_int_eq(s21_getbit(byte, i), 0);
  }
}
END_TEST

// --- Тесты для s21_setbit ---
START_TEST(test_s21_setbit_set_to_one) {
  unsigned int byte = 0x00000000;
  s21_setbit(&byte, 5, 1);
  ck_assert_uint_eq(byte, 0b00000000000000000000000000100000);  // 2^5
}
END_TEST

START_TEST(test_s21_setbit_set_to_zero) {
  unsigned int byte = 0xFFFFFFFF;
  s21_setbit(&byte, 10, 0);
  ck_assert_uint_eq(byte, 0xFFFFFFFF ^ (1 << 10));
}
END_TEST

START_TEST(test_s21_setbit_no_change) {
  unsigned int byte = 0b00000000000000000000000000100000;
  s21_setbit(&byte, 5, 1);  // Set 5th bit to 1, already 1
  ck_assert_uint_eq(byte, 0b00000000000000000000000000100000);
  s21_setbit(&byte, 0, 0);  // Set 0th bit to 0, already 0
  ck_assert_uint_eq(byte, 0b00000000000000000000000000100000);
}
END_TEST

// --- Тесты для s21_getscale и s21_setscale ---
START_TEST(test_s21_getsetscale_zero) {
  s21_decimal val = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_getscale(val), 0);
  s21_setscale(&val, 0);
  ck_assert_int_eq(s21_getscale(val), 0);
}
END_TEST

START_TEST(test_s21_getsetscale_max) {
  s21_decimal val = {{0, 0, 0, 0}};
  s21_setscale(&val, 28);
  ck_assert_int_eq(s21_getscale(val), 28);
}
END_TEST

START_TEST(test_s21_getsetscale_with_sign) {
  s21_decimal val = {{0, 0, 0, 0x80000000}};  // Negative sign
  s21_setscale(&val, 15);
  ck_assert_int_eq(s21_getscale(val), 15);
  ck_assert_int_eq(s21_get_sign(val), 1);  // Sign should be preserved
}
END_TEST

START_TEST(test_s21_getsetscale_random) {
  s21_decimal val = {{123, 456, 789, 0}};
  s21_setscale(&val, 7);
  ck_assert_int_eq(s21_getscale(val), 7);
  s21_setscale(&val, 23);
  ck_assert_int_eq(s21_getscale(val), 23);
}
END_TEST

// --- Тесты для s21_get_sign и s21_set_sign ---
START_TEST(test_s21_getset_sign_positive) {
  s21_decimal val = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_get_sign(val), 0);
  s21_set_sign(&val, 0);
  ck_assert_int_eq(s21_get_sign(val), 0);
}
END_TEST

START_TEST(test_s21_getset_sign_negative) {
  s21_decimal val = {{1, 0, 0, 0}};
  s21_set_sign(&val, 1);
  ck_assert_int_eq(s21_get_sign(val), 1);
  s21_set_sign(&val, 1);  // Already negative
  ck_assert_int_eq(s21_get_sign(val), 1);
}
END_TEST

START_TEST(test_s21_getset_sign_toggle) {
  s21_decimal val = {{1, 0, 0, 0}};
  s21_set_sign(&val, 1);
  ck_assert_int_eq(s21_get_sign(val), 1);
  s21_set_sign(&val, 0);
  ck_assert_int_eq(s21_get_sign(val), 0);
}
END_TEST

START_TEST(test_s21_getset_sign_with_scale) {
  s21_decimal val = {{1, 0, 0, (10 << 16)}};  // Positive with scale
  s21_set_sign(&val, 1);
  ck_assert_int_eq(s21_get_sign(val), 1);
  ck_assert_int_eq(s21_getscale(val), 10);  // Scale should be preserved
}
END_TEST

// --- Тесты для s21_check_correct_dec ---
START_TEST(test_s21_check_correct_dec_valid) {
  s21_decimal val = {{1, 2, 3, (5 << 16)}};
  ck_assert_int_eq(s21_check_correct_dec(val), 0);
}
END_TEST

START_TEST(test_s21_check_correct_dec_invalid_reserved_low) {
  s21_decimal val = {{1, 2, 3, 0x00000001}};  // Bit 0 set
  ck_assert_int_eq(s21_check_correct_dec(val), S21_ERROR);
}
END_TEST

START_TEST(test_s21_check_correct_dec_invalid_reserved_high) {
  s21_decimal val = {{1, 2, 3, 0x01000000}};  // Bit 24 set
  ck_assert_int_eq(s21_check_correct_dec(val), S21_ERROR);
}
END_TEST

START_TEST(test_s21_check_correct_dec_invalid_scale_too_high) {
  s21_decimal val = {{1, 2, 3, (29 << 16)}};  // Scale 29
  ck_assert_int_eq(s21_check_correct_dec(val), S21_ERROR);
}
END_TEST

START_TEST(test_s21_check_correct_dec_invalid_scale_negative) {
  s21_decimal val = {{1, 2, 3, 4294901760U}};  // Negative scale
  ck_assert_int_eq(s21_check_correct_dec(val), S21_ERROR);
}
END_TEST

// --- Тесты для s21_is_zero_dec ---
START_TEST(test_s21_is_zero_dec_true) {
  s21_decimal val = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_zero_dec(val), 1);
}
END_TEST

START_TEST(test_s21_is_zero_dec_true_with_scale) {
  s21_decimal val = {{0, 0, 0, (10 << 16)}};
  ck_assert_int_eq(s21_is_zero_dec(val), 1);
}
END_TEST

START_TEST(test_s21_is_zero_dec_true_with_sign) {
  s21_decimal val = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_zero_dec(val), 1);
}
END_TEST

START_TEST(test_s21_is_zero_dec_false) {
  s21_decimal val = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_zero_dec(val), 0);
}
END_TEST

// --- Тесты для s21_set_zero_decimal ---
START_TEST(test_s21_set_zero_decimal_basic) {
  s21_decimal val = {{1, 2, 3, 0x80010000}};
  s21_set_zero_decimal(&val);
  ck_assert_uint_eq(val.bits[0], 0);
  ck_assert_uint_eq(val.bits[1], 0);
  ck_assert_uint_eq(val.bits[2], 0);
  ck_assert_uint_eq(val.bits[3], 0);
}
END_TEST

// --- Тесты для s21_mul_10 ---
START_TEST(test_s21_mul_10_no_carry) {
  s21_decimal val = {{10, 0, 0, 0}};
  int carry = s21_mul_10(&val);
  ck_assert_int_eq(carry, 0);
  ck_assert_uint_eq(val.bits[0], 100);
}
END_TEST

START_TEST(test_s21_mul_10_with_carry) {
  s21_decimal val = {
      {0x19999999, 0, 0, 0}};  //  0x19999999 * 10 = 0xFFFFFFFA (без переноса)
  int carry = s21_mul_10(&val);
  ck_assert_int_eq(carry, 0);  // Нет переноса из bits[2]
  ck_assert_uint_eq(val.bits[0], 0xFFFFFFFA);
  ck_assert_uint_eq(val.bits[1], 0);
}
END_TEST

START_TEST(test_s21_mul_10_overflow_to_next_bit) {
  s21_decimal val = {{0x10000000, 0, 0, 0}};  // 2^28
  val.bits[0] = 0x10000000;                   // 2^28
  int carry = s21_mul_10(&val);
  ck_assert_int_eq(carry, 0);
  ck_assert_uint_eq(val.bits[0], 0xA0000000);  // 2^28 * 10 = 10 * 2^28
  ck_assert_uint_eq(val.bits[1], 0);
}
END_TEST

START_TEST(test_s21_mul_10_overflow_decimal) {
  s21_decimal val = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int carry = s21_mul_10(&val);
  ck_assert_int_eq(carry, 1);  // Should overflow
}
END_TEST

// --- Тесты для s21_div_10 ---
START_TEST(test_s21_div_10_no_remainder) {
  s21_decimal val = {{100, 0, 0, 0}};
  int error = s21_div_10(&val);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(val.bits[0], 10);
}
END_TEST

START_TEST(test_s21_div_10_with_remainder) {
  s21_decimal val = {{123, 0, 0, 0}};
  int error = s21_div_10(&val);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(val.bits[0], 12);
}
END_TEST

START_TEST(test_s21_div_10_large_number) {
  s21_decimal val = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int error = s21_div_10(&val);
  ck_assert_int_eq(error, 0);
  // Expected value for (2^96 - 1) / 10
  ck_assert_uint_eq(val.bits[0], 0x99999999);
  ck_assert_uint_eq(val.bits[1], 0x99999999);
  ck_assert_uint_eq(val.bits[2], 0x19999999);
}
END_TEST

START_TEST(test_s21_div_10_zero) {
  s21_decimal val = {{0, 0, 0, 0}};
  int error = s21_div_10(&val);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(val.bits[0], 0);
}
END_TEST

// --- Тесты для s21_sum_bits ---
START_TEST(test_s21_sum_bits_no_carry) {
  unsigned int res_p;
  int carry = s21_sum_bits(1, 2, &res_p);
  ck_assert_int_eq(carry, 0);
  ck_assert_uint_eq(res_p, 3);
}
END_TEST

START_TEST(test_s21_sum_bits_with_carry) {
  unsigned int res_p;
  int carry = s21_sum_bits(0xFFFFFFFF, 1, &res_p);
  ck_assert_int_eq(carry, 1);
  ck_assert_uint_eq(res_p, 0);
}
END_TEST

START_TEST(test_s21_sum_bits_multiple_carry) {
  unsigned int res_p;
  int carry = s21_sum_bits(0xFFFFFFFF, 0xFFFFFFFF, &res_p);
  ck_assert_int_eq(carry, 1);
  ck_assert_uint_eq(res_p, 0xFFFFFFFE);
}
END_TEST

// --- Тесты для s21_add_32 ---
START_TEST(test_s21_add_32_no_carry) {
  s21_decimal val = {{1, 0, 0, 0}};
  s21_add_32(&val, 2);
  ck_assert_uint_eq(val.bits[0], 3);
  ck_assert_uint_eq(val.bits[1], 0);
  ck_assert_uint_eq(val.bits[2], 0);
}
END_TEST

START_TEST(test_s21_add_32_with_carry) {
  s21_decimal val = {{0xFFFFFFFF, 0, 0, 0}};
  s21_add_32(&val, 1);
  ck_assert_uint_eq(val.bits[0], 0);
  ck_assert_uint_eq(val.bits[1], 1);
  ck_assert_uint_eq(val.bits[2], 0);
}
END_TEST

START_TEST(test_s21_add_32_multiple_carry) {
  s21_decimal val = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_add_32(&val, 1);
  ck_assert_uint_eq(val.bits[0], 0);
  ck_assert_uint_eq(val.bits[1], 0);
  ck_assert_uint_eq(val.bits[2], 1);
}
END_TEST

// --- Тесты для s21_from_str_to_decimal ---
START_TEST(test_s21_from_str_to_decimal_integer) {
  s21_decimal val = {0};
  char *str = "12345";
  s21_from_str_to_decimal(&val, str);
  ck_assert_uint_eq(val.bits[0], 12345);
  ck_assert_int_eq(s21_getscale(val), 0);
  ck_assert_int_eq(s21_get_sign(val), 0);
}
END_TEST

START_TEST(test_s21_from_str_to_decimal_negative_integer) {
  s21_decimal val = {0};
  char *str = "-6789";
  s21_from_str_to_decimal(&val, str);
  ck_assert_uint_eq(val.bits[0], 6789);
  ck_assert_int_eq(s21_getscale(val), 0);
  ck_assert_int_eq(s21_get_sign(val), 1);
}
END_TEST

START_TEST(test_s21_from_str_to_decimal_float) {
  s21_decimal val = {0};
  char *str = "12.345";
  s21_from_str_to_decimal(&val, str);
  ck_assert_uint_eq(val.bits[0], 12345);
  ck_assert_int_eq(s21_getscale(val), 3);
  ck_assert_int_eq(s21_get_sign(val), 0);
}
END_TEST

START_TEST(test_s21_from_str_to_decimal_negative_float) {
  s21_decimal val = {0};
  char *str = "-9.8765";
  s21_from_str_to_decimal(&val, str);
  ck_assert_uint_eq(val.bits[0], 98765);
  ck_assert_int_eq(s21_getscale(val), 4);
  ck_assert_int_eq(s21_get_sign(val), 1);
}
END_TEST

START_TEST(test_s21_from_str_to_decimal_zero) {
  s21_decimal val = {0};
  char *str = "0";
  s21_from_str_to_decimal(&val, str);
  ck_assert_uint_eq(val.bits[0], 0);
  ck_assert_int_eq(s21_getscale(val), 0);
  ck_assert_int_eq(s21_get_sign(val), 0);
}
END_TEST

START_TEST(test_s21_from_str_to_decimal_zero_with_scale) {
  s21_decimal val = {0};
  char *str = "0.00";
  s21_from_str_to_decimal(&val, str);
  ck_assert_uint_eq(val.bits[0], 0);
  ck_assert_int_eq(s21_getscale(val), 2);
  ck_assert_int_eq(s21_get_sign(val), 0);
}
END_TEST

// --- Тесты для s21_is_valid_decimal ---
START_TEST(test_s21_is_valid_decimal_valid) {
  s21_decimal val = {{1, 2, 3, (10 << 16)}};
  ck_assert_int_eq(s21_is_valid_decimal(val), 1);
}
END_TEST

START_TEST(test_s21_is_valid_decimal_invalid_scale) {
  s21_decimal val = {{1, 2, 3, (29 << 16)}};  // Scale > 28
  ck_assert_int_eq(s21_is_valid_decimal(val), 0);
}
END_TEST

START_TEST(test_s21_is_valid_decimal_invalid_reserved_low) {
  s21_decimal val = {{1, 2, 3, 0x00000001}};  // Reserved bit 0 set
  ck_assert_int_eq(s21_is_valid_decimal(val), 0);
}
END_TEST

START_TEST(test_s21_is_valid_decimal_invalid_reserved_high) {
  s21_decimal val = {{1, 2, 3, 0x01000000}};  // Reserved bit 24 set
  ck_assert_int_eq(s21_is_valid_decimal(val), 0);
}
END_TEST

// --- Тесты для s21_decimal_get_zero ---
START_TEST(test_s21_decimal_get_zero) {
  s21_decimal zero = s21_decimal_get_zero();
  ck_assert_uint_eq(zero.bits[0], 0);
  ck_assert_uint_eq(zero.bits[1], 0);
  ck_assert_uint_eq(zero.bits[2], 0);
  ck_assert_uint_eq(zero.bits[3], 0);
}
END_TEST

// --- Тесты для s21_sub_internal (используется в s21_other.c) ---
START_TEST(test_s21_sub_internal_basic) {
  s21_decimal val1 = {{5, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  int status = s21_sub_internal(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 3);
  ck_assert_int_eq(s21_getscale(result), 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_sub_internal_with_scale) {
  s21_decimal val1 = {{50, 0, 0, (1 << 16)}};  // 5.0
  s21_decimal val2 = {{25, 0, 0, (1 << 16)}};  // 2.5
  s21_decimal result = {0};
  int status = s21_sub_internal(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 25);
  ck_assert_int_eq(s21_getscale(result), 1);
}
END_TEST

START_TEST(test_s21_sub_internal_different_scales) {
  s21_decimal val1 = {{500, 0, 0, (2 << 16)}};  // 5.00
  s21_decimal val2 = {{25, 0, 0, (1 << 16)}};   // 2.5
  s21_decimal result = {0};
  int status = s21_sub_internal(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 250);  // 5.00 - 2.50 = 2.50
  ck_assert_int_eq(s21_getscale(result), 2);
}
END_TEST

START_TEST(test_s21_sub_internal_borrow_across_bits) {
  s21_decimal val1 = {{0, 1, 0, 0}};  // 2^32
  s21_decimal val2 = {{1, 0, 0, 0}};  // 1
  s21_decimal result = {0};
  int status = s21_sub_internal(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_sub_internal_negative_result_error) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  int status = s21_sub_internal(val1, val2, &result);
  ck_assert_int_eq(status, 1);  // Should return error if val1 < val2
}
END_TEST

// --- Тесты для s21_float_str_preparing_for_convert и его внутренних функций
// ---
START_TEST(test_s21_float_str_preparing_for_convert_positive_small) {
  float src = 0.000000123f;
  char float_str[100];
  char final_float_str[100];
  sprintf(float_str, "%.29f", src);
  int error =
      s21_float_str_preparing_for_convert(src, float_str, final_float_str);
  ck_assert_int_eq(error, 0);
  ck_assert_str_eq(final_float_str, "0.0000001230000");
}
END_TEST

START_TEST(test_s21_float_str_preparing_for_convert_negative_small) {
  float src = -0.000000123f;
  char float_str[100];
  char final_float_str[100];
  sprintf(float_str, "%.29f", src);
  int error =
      s21_float_str_preparing_for_convert(src, float_str, final_float_str);
  ck_assert_int_eq(error, 0);
  ck_assert_str_eq(final_float_str, "-0.0000001230000");
}
END_TEST

START_TEST(test_s21_float_str_preparing_for_convert_too_small) {
  float src = 1e-29f;  // Too small for decimal
  char float_str[100];
  char final_float_str[100];
  sprintf(float_str, "%.29f", src);
  int error =
      s21_float_str_preparing_for_convert(src, float_str, final_float_str);
  ck_assert_int_eq(error, 1);  // Should be an error
  ck_assert_str_eq(final_float_str, "0");
}
END_TEST

START_TEST(test_s21_float_str_preparing_for_convert_too_large) {
  float src = 8e28f;  // Too large for decimal
  char float_str[100];
  char final_float_str[100];
  sprintf(float_str, "%.29f", src);
  int error =
      s21_float_str_preparing_for_convert(src, float_str, final_float_str);
  ck_assert_int_eq(error, 1);  // Should be an error
}
END_TEST

START_TEST(test_s21_float_str_preparing_for_convert_normal_positive) {
  float src = 123.456f;
  char float_str[100];
  char final_float_str[100];
  sprintf(float_str, "%.29f", src);
  int error =
      s21_float_str_preparing_for_convert(src, float_str, final_float_str);
  ck_assert_int_eq(error, 0);
  ck_assert_str_eq(final_float_str, "123.4560");
}
END_TEST

START_TEST(test_s21_float_str_preparing_for_convert_normal_negative) {
  float src = -123.456f;
  char float_str[100];
  char final_float_str[100];
  sprintf(float_str, "%.29f", src);
  int error =
      s21_float_str_preparing_for_convert(src, float_str, final_float_str);
  ck_assert_int_eq(error, 0);
  ck_assert_str_eq(final_float_str, "-123.4560");
}
END_TEST

// --- Тесты для decimal_to_double ---
START_TEST(test_decimal_to_double_positive_integer) {
  s21_decimal src = {{123, 0, 0, 0}};
  double res = decimal_to_double(src);
  ck_assert_double_eq(res, 123.0);
}
END_TEST

START_TEST(test_decimal_to_double_negative_integer) {
  s21_decimal src = {{123, 0, 0, 0x80000000}};
  double res = decimal_to_double(src);
  ck_assert_double_eq(res, -123.0);
}
END_TEST

START_TEST(test_decimal_to_double_positive_float) {
  s21_decimal src = {{12345, 0, 0, (2 << 16)}};  // 123.45
  double res = decimal_to_double(src);
  ck_assert_double_eq(res, 123.45);
}
END_TEST

START_TEST(test_decimal_to_double_negative_float) {
  s21_decimal src = {{12345, 0, 0, (2 << 16) | 0x80000000}};  // -123.45
  double res = decimal_to_double(src);
  ck_assert_double_eq(res, -123.45);
}
END_TEST

START_TEST(test_decimal_to_double_zero) {
  s21_decimal src = {{0, 0, 0, 0}};
  double res = decimal_to_double(src);
  ck_assert_double_eq(res, 0.0);
}
END_TEST

// --- Тесты для decimal_to_float ---
START_TEST(test_decimal_to_float_positive_integer) {
  s21_decimal src = {{123, 0, 0, 0}};
  float res = decimal_to_float(src);
  ck_assert_float_eq(res, 123.0f);
}
END_TEST

START_TEST(test_decimal_to_float_negative_integer) {
  s21_decimal src = {{123, 0, 0, 0x80000000}};
  float res = decimal_to_float(src);
  ck_assert_float_eq(res, -123.0f);
}
END_TEST

START_TEST(test_decimal_to_float_positive_float) {
  s21_decimal src = {{12345, 0, 0, (2 << 16)}};  // 123.45
  float res = decimal_to_float(src);
  ck_assert_float_eq(res, 123.45f);
}
END_TEST

START_TEST(test_decimal_to_float_negative_float) {
  s21_decimal src = {{12345, 0, 0, (2 << 16) | 0x80000000}};  // -123.45
  float res = decimal_to_float(src);
  ck_assert_float_eq(res, -123.45f);
}
END_TEST

START_TEST(test_decimal_to_float_zero) {
  s21_decimal src = {{0, 0, 0, 0}};
  float res = decimal_to_float(src);
  ck_assert_float_eq(res, 0.0f);
}
END_TEST

// --- Новые тесты для s21_leveling_scale ---
START_TEST(test_s21_leveling_scale_equal_scales) {
  s21_decimal v1 = create_decimal(123, 0, 0, 0, 2);  // 1.23
  s21_decimal v2 = create_decimal(456, 0, 0, 0, 2);  // 4.56
  s21_big_decimal b1 = {0}, b2 = {0};
  int common_scale = s21_leveling_scale(v1, v2, &b1, &b2);
  ck_assert_int_eq(common_scale, 2);
  // Мантиссы скопированы без изменений (проверяем первое слово)
  ck_assert_uint_eq(b1.bits[0], 123);
  ck_assert_uint_eq(b2.bits[0], 456);
  ck_assert_int_eq(s21_check_zero_big_decimal(b1), 0);
  ck_assert_int_eq(s21_check_zero_big_decimal(b2), 0);
}
END_TEST

START_TEST(test_s21_leveling_scale_v1_larger_scale) {
  s21_decimal v1 = create_decimal(123, 0, 0, 0, 5);  // 0.00123
  s21_decimal v2 = create_decimal(456, 0, 0, 0, 2);  // 4.56
  s21_big_decimal b1 = {0}, b2 = {0};
  int common_scale = s21_leveling_scale(v1, v2, &b1, &b2);
  ck_assert_int_eq(common_scale, 5);
  // v2 умножена на 10^(5-2) = 456 * 1000 = 456000
  ck_assert_uint_eq(b2.bits[0], 456000);
  // v1 без изменений
  ck_assert_uint_eq(b1.bits[0], 123);
}
END_TEST

START_TEST(test_s21_leveling_scale_v2_larger_scale) {
  s21_decimal v1 = create_decimal(123, 0, 0, 0, 2);  // 1.23
  s21_decimal v2 = create_decimal(456, 0, 0, 0, 5);  // 0.00456
  s21_big_decimal b1 = {0}, b2 = {0};
  int common_scale = s21_leveling_scale(v1, v2, &b1, &b2);
  ck_assert_int_eq(common_scale, 5);
  // v1 умножена на 10^(5-2) = 123 * 1000 = 123000
  ck_assert_uint_eq(b1.bits[0], 123000);
  ck_assert_uint_eq(b2.bits[0], 456);
}
END_TEST

START_TEST(test_s21_leveling_scale_zero_values) {
  s21_decimal v1 = create_decimal(0, 0, 0, 0, 10);
  s21_decimal v2 = create_decimal(0, 0, 0, 0, 5);
  s21_big_decimal b1 = {0}, b2 = {0};
  int common_scale = s21_leveling_scale(v1, v2, &b1, &b2);
  ck_assert_int_eq(common_scale, 10);  // Берется максимальный scale
  ck_assert_int_eq(s21_check_zero_big_decimal(b1), 1);
  ck_assert_int_eq(s21_check_zero_big_decimal(b2), 1);
}
END_TEST

START_TEST(test_s21_leveling_scale_max_scale_no_overflow) {
  s21_decimal v1 = create_decimal(1, 0, 0, 0, 28);
  s21_decimal v2 = create_decimal(1, 0, 0, 0, 28);
  s21_big_decimal b1 = {0}, b2 = {0};
  int common_scale = s21_leveling_scale(v1, v2, &b1, &b2);
  ck_assert_int_eq(common_scale, 28);
  ck_assert_uint_eq(b1.bits[0], 1);
  ck_assert_uint_eq(b2.bits[0], 1);
}
END_TEST

START_TEST(test_s21_round_finance_big_round_down_less_5) {
  s21_big_decimal big = {
      {4, 0, 0, 0, 0, 0, 0, 0}};  // 4, remainder=4 (<5, не округляем)
  int remainder = 4;
  int no_zero_flag = 0;
  s21_round_finance_big(&big, remainder, no_zero_flag);
  ck_assert_uint_eq(big.bits[0], 4);  // Без изменений
}
END_TEST

START_TEST(test_s21_round_finance_big_bankers_even) {
  s21_big_decimal big = {
      {2, 0, 0, 0, 0, 0, 0,
       0}};  // 2 (четное), remainder=5 -> округляем к четному (остается 2)
  int remainder = 5;
  int no_zero_flag = 0;
  s21_round_finance_big(&big, remainder, no_zero_flag);
  ck_assert_uint_eq(big.bits[0], 2);  // Банковское: к ближайшему четному
}
END_TEST

START_TEST(test_s21_round_finance_big_bankers_odd) {
  s21_big_decimal big = {
      {1, 0, 0, 0, 0, 0, 0,
       0}};  // 1 (нечетное), remainder=5 -> округляем вверх к 2 (четному)
  int remainder = 5;
  int no_zero_flag = 0;
  s21_round_finance_big(&big, remainder, no_zero_flag);
  ck_assert_uint_eq(big.bits[0], 2);
}
END_TEST

START_TEST(test_s21_round_finance_big_no_zero_flag_preserve) {
  s21_big_decimal big = {
      {100, 0, 0, 0, 0, 0, 0, 0}};  // 100, remainder=0, с trailing zeros
  int remainder = 0;
  int no_zero_flag = 1;  // Не обнуляем trailing zeros
  s21_round_finance_big(&big, remainder, no_zero_flag);
  ck_assert_uint_eq(big.bits[0], 100);  // Сохраняем как есть
}
END_TEST

START_TEST(test_s21_round_finance_big_carry_propagation) {
  s21_big_decimal big = {{0xFFFFFFFF, 0, 0, 0, 0, 0, 0,
                          0}};  // 0xFFFFFFFF, remainder=5 -> +1 с переносом
  int remainder = 5;
  int no_zero_flag = 0;
  s21_round_finance_big(&big, remainder, no_zero_flag);
  ck_assert_uint_eq(big.bits[0], 0);  // Перенос в следующий бит
  ck_assert_uint_eq(big.bits[1], 1);  // Carry в bits[1]
}
END_TEST

START_TEST(test_s21_round_finance_big_remainder_zero_no_change) {
  s21_big_decimal big = {{123, 0, 0, 0, 0, 0, 0, 0}};
  int remainder = 0;
  int no_zero_flag = 0;
  s21_round_finance_big(&big, remainder, no_zero_flag);
  ck_assert_uint_eq(big.bits[0], 123);  // Без изменений
}
END_TEST

START_TEST(test_s21_round_finance_big_zero_input) {
  s21_big_decimal big = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int remainder = 3;
  int no_zero_flag = 0;
  s21_round_finance_big(&big, remainder, no_zero_flag);
  ck_assert_int_eq(s21_check_zero_big_decimal(big), 1);  // 0 остается 0
}
END_TEST

Suite *suite_support_functions(void) {
  Suite *s = suite_create("Support_functions");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_getbit_low_bit);
  tcase_add_test(tc_core, test_s21_getbit_high_bit);
  tcase_add_test(tc_core, test_s21_getbit_middle_bit);
  tcase_add_test(tc_core, test_s21_getbit_all_ones);
  tcase_add_test(tc_core, test_s21_getbit_all_zeros);

  tcase_add_test(tc_core, test_s21_setbit_set_to_one);
  tcase_add_test(tc_core, test_s21_setbit_set_to_zero);
  tcase_add_test(tc_core, test_s21_setbit_no_change);

  tcase_add_test(tc_core, test_s21_getsetscale_zero);
  tcase_add_test(tc_core, test_s21_getsetscale_max);
  tcase_add_test(tc_core, test_s21_getsetscale_with_sign);
  tcase_add_test(tc_core, test_s21_getsetscale_random);

  tcase_add_test(tc_core, test_s21_getset_sign_positive);
  tcase_add_test(tc_core, test_s21_getset_sign_negative);
  tcase_add_test(tc_core, test_s21_getset_sign_toggle);
  tcase_add_test(tc_core, test_s21_getset_sign_with_scale);

  tcase_add_test(tc_core, test_s21_check_correct_dec_valid);
  tcase_add_test(tc_core, test_s21_check_correct_dec_invalid_reserved_low);
  tcase_add_test(tc_core, test_s21_check_correct_dec_invalid_reserved_high);
  tcase_add_test(tc_core, test_s21_check_correct_dec_invalid_scale_too_high);
  tcase_add_test(tc_core, test_s21_check_correct_dec_invalid_scale_negative);

  tcase_add_test(tc_core, test_s21_is_zero_dec_true);
  tcase_add_test(tc_core, test_s21_is_zero_dec_true_with_scale);
  tcase_add_test(tc_core, test_s21_is_zero_dec_true_with_sign);
  tcase_add_test(tc_core, test_s21_is_zero_dec_false);

  tcase_add_test(tc_core, test_s21_set_zero_decimal_basic);

  tcase_add_test(tc_core, test_s21_mul_10_no_carry);
  tcase_add_test(tc_core, test_s21_mul_10_with_carry);
  tcase_add_test(tc_core, test_s21_mul_10_overflow_to_next_bit);
  tcase_add_test(tc_core, test_s21_mul_10_overflow_decimal);

  tcase_add_test(tc_core, test_s21_div_10_no_remainder);
  tcase_add_test(tc_core, test_s21_div_10_with_remainder);
  tcase_add_test(tc_core, test_s21_div_10_large_number);
  tcase_add_test(tc_core, test_s21_div_10_zero);

  tcase_add_test(tc_core, test_s21_sum_bits_no_carry);
  tcase_add_test(tc_core, test_s21_sum_bits_with_carry);
  tcase_add_test(tc_core, test_s21_sum_bits_multiple_carry);

  tcase_add_test(tc_core, test_s21_add_32_no_carry);
  tcase_add_test(tc_core, test_s21_add_32_with_carry);
  tcase_add_test(tc_core, test_s21_add_32_multiple_carry);

  tcase_add_test(tc_core, test_s21_from_str_to_decimal_integer);
  tcase_add_test(tc_core, test_s21_from_str_to_decimal_negative_integer);
  tcase_add_test(tc_core, test_s21_from_str_to_decimal_float);
  tcase_add_test(tc_core, test_s21_from_str_to_decimal_negative_float);
  tcase_add_test(tc_core, test_s21_from_str_to_decimal_zero);
  tcase_add_test(tc_core, test_s21_from_str_to_decimal_zero_with_scale);

  tcase_add_test(tc_core, test_s21_is_valid_decimal_valid);
  tcase_add_test(tc_core, test_s21_is_valid_decimal_invalid_scale);
  tcase_add_test(tc_core, test_s21_is_valid_decimal_invalid_reserved_low);
  tcase_add_test(tc_core, test_s21_is_valid_decimal_invalid_reserved_high);

  tcase_add_test(tc_core, test_s21_decimal_get_zero);

  tcase_add_test(tc_core, test_s21_sub_internal_basic);
  tcase_add_test(tc_core, test_s21_sub_internal_with_scale);
  tcase_add_test(tc_core, test_s21_sub_internal_different_scales);
  tcase_add_test(tc_core, test_s21_sub_internal_borrow_across_bits);
  tcase_add_test(tc_core, test_s21_sub_internal_negative_result_error);

  tcase_add_test(tc_core,
                 test_s21_float_str_preparing_for_convert_positive_small);
  tcase_add_test(tc_core,
                 test_s21_float_str_preparing_for_convert_negative_small);
  tcase_add_test(tc_core, test_s21_float_str_preparing_for_convert_too_small);
  tcase_add_test(tc_core, test_s21_float_str_preparing_for_convert_too_large);
  tcase_add_test(tc_core,
                 test_s21_float_str_preparing_for_convert_normal_positive);
  tcase_add_test(tc_core,
                 test_s21_float_str_preparing_for_convert_normal_negative);

  tcase_add_test(tc_core, test_decimal_to_double_positive_integer);
  tcase_add_test(tc_core, test_decimal_to_double_negative_integer);
  tcase_add_test(tc_core, test_decimal_to_double_positive_float);
  tcase_add_test(tc_core, test_decimal_to_double_negative_float);
  tcase_add_test(tc_core, test_decimal_to_double_zero);

  tcase_add_test(tc_core, test_decimal_to_float_positive_integer);
  tcase_add_test(tc_core, test_decimal_to_float_negative_integer);
  tcase_add_test(tc_core, test_decimal_to_float_positive_float);
  tcase_add_test(tc_core, test_decimal_to_float_negative_float);
  tcase_add_test(tc_core, test_decimal_to_float_zero);

  tcase_add_test(tc_core, test_s21_leveling_scale_equal_scales);
  tcase_add_test(tc_core, test_s21_leveling_scale_v1_larger_scale);
  tcase_add_test(tc_core, test_s21_leveling_scale_v2_larger_scale);
  tcase_add_test(tc_core, test_s21_leveling_scale_zero_values);
  tcase_add_test(tc_core, test_s21_leveling_scale_max_scale_no_overflow);

  tcase_add_test(tc_core, test_s21_round_finance_big_round_down_less_5);
  tcase_add_test(tc_core, test_s21_round_finance_big_bankers_even);
  tcase_add_test(tc_core, test_s21_round_finance_big_bankers_odd);
  tcase_add_test(tc_core, test_s21_round_finance_big_no_zero_flag_preserve);
  tcase_add_test(tc_core, test_s21_round_finance_big_carry_propagation);
  tcase_add_test(tc_core, test_s21_round_finance_big_remainder_zero_no_change);
  tcase_add_test(tc_core, test_s21_round_finance_big_zero_input);

  suite_add_tcase(s, tc_core);
  return s;
}
