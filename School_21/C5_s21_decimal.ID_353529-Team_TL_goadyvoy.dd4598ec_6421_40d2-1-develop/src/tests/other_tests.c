#include "../s21_decimal.h"
#include "../s21_decimal_test.h"

START_TEST(test_floor_positive_fraction) {
  s21_decimal a = {{7, 0, 0, 0x00010000}};  // 0.7
  s21_decimal expected = {{0, 0, 0, 0x00000000}};
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_negative_fraction) {
  s21_decimal a = {{7, 0, 0, 0x80010000}};         // -0.7
  s21_decimal expected = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_positive_integer) {
  s21_decimal a = {{5, 0, 0, 0x00000000}};  // 5
  s21_decimal expected = a;
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_negative_integer) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal expected = a;
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_null_pointer) {
  s21_decimal a = {{5, 0, 0, 0x00010000}};  // 0.5
  int code = s21_floor(a, NULL);
  ck_assert_int_eq(code, 1);
}

START_TEST(test_floor_large_positive_fraction) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 1e-28
  s21_decimal expected = {{0, 0, 0, 0x00000000}};
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_large_negative_fraction) {
  s21_decimal a = {{1, 0, 0, 0x801C0000}};  // -1e-28
  s21_decimal expected = {{1, 0, 0, 0x80000000}};
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_max_integer) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                    0x00000000}};  // Максимальное целое без знака
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, a));
}

START_TEST(test_floor_min_negative_integer) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                    0x80000000}};  // Минимальное целое со знаком
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, a));
}

START_TEST(test_floor_one_and_fraction) {
  s21_decimal a = {{10001, 0, 0, 0x00040000}};  // 1.0001
  s21_decimal expected = {{1, 0, 0, 0x00000000}};
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_negative_one_and_fraction) {
  s21_decimal a = {{10001, 0, 0, 0x80040000}};     // -1.0001
  s21_decimal expected = {{2, 0, 0, 0x80000000}};  // floor(-1.0001) == -2
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(s21_is_equal(result, expected));
}

START_TEST(test_floor_negative_fraction_edge) {
  // -79228162514264337593543950335.9 (почти MIN_DECIMAL - 0.9)
  s21_decimal a = {
      {4294967287, 4294967295, 4294967295, 0x80100000}};  // scale = 16
  s21_decimal result;
  int code = s21_floor(a, &result);
  ck_assert_int_eq(code, 0);
}

/* ======================== TRUNCATE TESTS ======================== */

START_TEST(truncate_positive_with_fraction) {
  s21_decimal val = {{1234567, 0, 0, 0}};
  s21_setscale(&val, 3);  // 1234.567
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 1234);
  ck_assert_int_eq(s21_getscale(res), 0);
}
END_TEST

START_TEST(truncate_negative_with_fraction) {
  s21_decimal val = {{1234567, 0, 0, 0}};
  s21_setscale(&val, 3);
  s21_set_sign(&val, 1);
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 1234);
  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(truncate_zero) {
  s21_decimal val = {{0, 0, 0, 0}};
  s21_setscale(&val, 10);
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(truncate_zero_to_null) {
  s21_decimal val = {{0, 0, 0, 0}};
  s21_setscale(&val, 10);
  int res = s21_truncate(val, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(truncate_whole_number) {
  s21_decimal val = {{789, 0, 0, 0}};
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 789);
}
END_TEST

START_TEST(truncate_max_value) {
  s21_decimal val = {{-1u, -1u, -1u, 0}};
  s21_setscale(&val, 5);
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert(s21_getscale(res) == 0);
}
END_TEST

START_TEST(truncate_min_negative_value) {
  s21_decimal val = {{-1u, -1u, -1u, 0}};
  s21_setscale(&val, 28);
  s21_set_sign(&val, 1);
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert(s21_get_sign(res) == 1);
}
END_TEST

START_TEST(truncate_near_half_down) {
  s21_decimal val = {{15, 0, 0, 0}};
  s21_setscale(&val, 1);  // 1.5
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 1);
}
END_TEST

START_TEST(truncate_negative_near_half) {
  s21_decimal val = {{15, 0, 0, 0}};
  s21_setscale(&val, 1);
  s21_set_sign(&val, 1);
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert(s21_get_sign(res));
}
END_TEST

START_TEST(truncate_only_fraction) {
  s21_decimal val = {{45, 0, 0, 0}};
  s21_setscale(&val, 2);  // 0.45
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(truncate_large_scale) {
  s21_decimal val = {{123456700, 0, 0, 0}};
  s21_setscale(&val, 6);
  s21_decimal res;
  s21_truncate(val, &res);
  ck_assert_int_eq(res.bits[0], 123);
}
END_TEST

START_TEST(truncate_max_dec) {
  s21_decimal val = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_setscale(&val, 1);

  s21_decimal res;
  int code = s21_truncate(val, &res);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_getscale(res), 0);

  ck_assert_int_eq(res.bits[0], 0x99999999);
  ck_assert_int_eq(res.bits[1], 0x99999999);
  ck_assert_int_eq(res.bits[2], 0x19999999);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

/* ======================== ROUND TESTS ======================== */

START_TEST(round_positive) {
  s21_decimal val = {{12345, 0, 0, 0}};
  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 12345);
}
END_TEST

START_TEST(round_positive_null) {
  s21_decimal val = {{12345, 0, 0, 0}};
  int res;
  res = s21_round(val, NULL);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(round_down_half) {
  s21_decimal val = {{5, 0, 0, 0}};  // 0.5
  s21_setscale(&val, 1);
  s21_decimal res;
  s21_round(val, &res);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(s21_getscale(res), 0);
}
END_TEST

START_TEST(round_up_half) {
  s21_decimal val = {{15, 0, 0, 0}};  // 1.5
  s21_setscale(&val, 1);
  s21_decimal res;
  s21_round(val, &res);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(s21_getscale(res), 0);
}
END_TEST

START_TEST(round_negative_half) {
  s21_decimal val = {{5, 0, 0, 0}};  // -0.5
  s21_setscale(&val, 1);
  s21_set_sign(&val, 1);
  s21_decimal res;
  s21_round(val, &res);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(round_negative_up) {
  s21_decimal val = {{25, 0, 0, 0}};  // -2.5
  s21_setscale(&val, 1);
  s21_set_sign(&val, 1);
  s21_decimal res;
  s21_round(val, &res);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

/* ======================== NEGATE TESTS ======================== */

START_TEST(negate_positive) {
  s21_decimal val = {{12345, 0, 0, 0}};
  s21_decimal res;
  s21_negate(val, &res);
  ck_assert_int_eq(s21_get_sign(res), 1);
  ck_assert_int_eq(res.bits[0], 12345);
}
END_TEST

START_TEST(negate_negative) {
  s21_decimal val = {{12345, 0, 0, 0}};
  s21_set_sign(&val, 1);
  s21_decimal res;
  s21_negate(val, &res);
  ck_assert_int_eq(s21_get_sign(res), 0);
  ck_assert_int_eq(res.bits[0], 12345);
}
END_TEST

START_TEST(negate_zero) {
  s21_decimal val = {{0, 0, 0, 0}};
  s21_decimal res;
  s21_negate(val, &res);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(negate_null) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = s21_negate(val, NULL);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(negate_scale_preserved) {
  s21_decimal val = {{98765, 0, 0, 0}};
  s21_setscale(&val, 5);
  s21_decimal res;
  s21_negate(val, &res);
  ck_assert_int_eq(s21_getscale(res), 5);
  ck_assert_int_eq(s21_get_sign(res), 1);
}
END_TEST

START_TEST(negate_max_value) {
  s21_decimal val = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal res;
  s21_negate(val, &res);
  ck_assert_int_eq(s21_get_sign(res), 1);
  ck_assert_int_eq(res.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(res.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(res.bits[2], 0xFFFFFFFF);
}
END_TEST

// Тесты на правку

START_TEST(test_s21_floor_positive_basic) {
  s21_decimal value = {{0x1E240, 0x0, 0x0, 0x30000}};  // 123.456
  s21_set_sign(&value, 0);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x7B, 0x0, 0x0, 0x0}};  // 123
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_negative_basic) {
  s21_decimal value = {{0x1E240, 0x0, 0x0, 0x30000}};  // -123.456
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x7C, 0x0, 0x0, 0x0}};  // -124
  s21_set_sign(&expected, 1);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_positive_exact) {
  s21_decimal value = {{0x1E078, 0x0, 0x0, 0x30000}};  // 123.000

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x7B, 0x0, 0x0, 0x0}};  // 123
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_zero) {
  s21_decimal value = {{0x0, 0x0, 0x0, 0x50000}};  // 0.00000

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_zero_dec(result), 1);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_floor_no_scale) {
  s21_decimal value = {{0x75BCD15, 0x0, 0x0, 0x0}};  // 123456789

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(result, value), 1);
}
END_TEST

START_TEST(test_s21_floor_max_scale) {
  s21_decimal value = {
      {0x75BCD15, 0x0, 0x0, 0x1C0000}};  // 0.0000000000000000000000123456789

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_negative_max_scale) {
  s21_decimal value = {
      {0x75BCD15, 0x0, 0x0, 0x1C0000}};  // -0.0000000000000000000000123456789
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x1, 0x0, 0x0, 0x0}};  // -1
  s21_set_sign(&expected, 1);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_large_number) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x50000}};  // Very large number with scale

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_floor_null_result) {
  s21_decimal value = {{0x7B, 0x0, 0x0, 0x0}};  // 123

  int error = s21_floor(value, NULL);

  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_s21_floor_positive_half) {
  // 123.5 = 1235 / 10
  s21_decimal value = {{0x4D3, 0x0, 0x0, 0x10000}};  // 0x4D3 = 1235
  s21_set_sign(&value, 0);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  // floor(123.5) = 123
  s21_decimal expected = {{123, 0x0, 0x0, 0x0}};
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Отрицательное число с дробной частью 0.5
START_TEST(test_s21_floor_negative_half) {
  // -123.5
  s21_decimal value = {{0x4D3, 0x0, 0x0, 0x10000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{124, 0x0, 0x0, 0x0}};
  s21_set_sign(&expected, 1);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Очень маленькое положительное число (меньше 1)
START_TEST(test_s21_floor_small_positive) {
  // 0.0000000001
  s21_decimal value = {{1, 0x0, 0x0, 0xA0000}};

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0, 0x0, 0x0, 0x0}};
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Очень маленькое отрицательное число (больше -1)
START_TEST(test_s21_floor_small_negative) {
  // -0.0000000001
  s21_decimal value = {{1, 0x0, 0x0, 0xA0000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{1, 0x0, 0x0, 0x0}};
  s21_set_sign(&expected, 1);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Максимально возможное положительное значение
START_TEST(test_s21_floor_max_positive) {
  // Максимальное значение: 79228162514264337593543950335
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&value, 0);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(result, value), 1);
}
END_TEST

// Тест: Минимально возможное отрицательное значение
START_TEST(test_s21_floor_min_negative) {
  // Минимальное значение: -79228162514264337593543950335
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(result, value), 1);
}
END_TEST

// Тест: Число с масштабом 28 (максимальный)
START_TEST(test_s21_floor_scale_28_positive) {
  // 1.0 * 10^-28
  s21_decimal value = {{1, 0x0, 0x0, 0x1C0000}};

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Число с масштабом 28 (максимальный), отрицательное
START_TEST(test_s21_floor_scale_28_negative) {
  // -1.0 * 10^-28
  s21_decimal value = {{1, 0x0, 0x0, 0x1C0000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{1, 0x0, 0x0, 0x0}};
  s21_set_sign(&expected, 1);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Число, где усечение приводит к переносу в старшие разряды
START_TEST(test_s21_floor_carry_propagation) {
  // 4294967296.9 = 42949672969 / 10
  // Мантисса: 42949672969 = 0xA * 2^32 + 9
  s21_decimal value = {{9, 0xA, 0x0, 0x10000}};  // bits[0]=9, bits[1]=10 (0xA)

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  // Ожидаем: 4294967296 = 0x100000000 = bits[0]=0, bits[1]=1
  s21_decimal expected = {{0x0, 0x1, 0x0, 0x0}};
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_floor_borrow_propagation) {
  // -4294967297.1 = -42949672971 / 10
  // Мантисса: 42949672971 = 0xA * 2^32 + 11
  s21_decimal value = {
      {11, 0xA, 0x0, 0x10000}};  // bits[0]=11 (0xB), bits[1]=10 (0xA)
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_floor(value, &result);

  ck_assert_int_eq(error, 0);

  // Ожидаем: -4294967298
  // 4294967298 = 0x100000002 = bits[0]=2, bits[1]=1
  s21_decimal expected = {{2, 0x1, 0x0, 0x0}};
  s21_set_sign(&expected, 1);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// ==================== s21_round TESTS ====================

START_TEST(test_s21_round_positive_half_down) {
  s21_decimal value = {{0x4, 0x0, 0x0, 0x10000}};  // 0.4

  s21_decimal result;
  int error = s21_round(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_negative_half_down) {
  s21_decimal value = {{0x4, 0x0, 0x0, 0x10000}};  // -0.4
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_round(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_border_case) {
  s21_decimal value = {{0x1F3, 0x0, 0x0, 0x30000}};  // 0.499

  s21_decimal result;
  int error = s21_round(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_round_no_scale) {
  s21_decimal value = {{0x75BCD15, 0x0, 0x0, 0x0}};  // 123456789

  s21_decimal result;
  int error = s21_round(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(result, value), 1);
}
END_TEST

START_TEST(test_s21_round_zero) {
  s21_decimal value = {{0x0, 0x0, 0x0, 0x50000}};  // 0.00000

  s21_decimal result;
  int error = s21_round(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_zero_dec(result), 1);
}
END_TEST

START_TEST(test_s21_round_max_precision) {
  s21_decimal value = {{0x1, 0x0, 0x0, 0x1C0000}};  // 1e-28

  s21_decimal result;
  int error = s21_round(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// ==================== s21_truncate TESTS ====================

START_TEST(test_s21_truncate_positive_basic) {
  s21_decimal value = {{0x1E240, 0x0, 0x0, 0x30000}};  // 123.456

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x7B, 0x0, 0x0, 0x0}};  // 123
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_negative_basic) {
  s21_decimal value = {{0x1E240, 0x0, 0x0, 0x30000}};  // -123.456
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x7B, 0x0, 0x0, 0x0}};  // -123
  s21_set_sign(&expected, 1);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_no_scale) {
  s21_decimal value = {{0x75BCD15, 0x0, 0x0, 0x0}};  // 123456789

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(result, value), 1);
}
END_TEST

START_TEST(test_s21_truncate_zero) {
  s21_decimal value = {{0x0, 0x0, 0x0, 0xA0000}};  // 0.0000000000

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_zero_dec(result), 1);
}
END_TEST

START_TEST(test_s21_truncate_max_scale) {
  s21_decimal value = {{0x75BCD15, 0x0, 0x0, 0x1C0000}};  // 1.23456789e-28

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_small_fraction) {
  s21_decimal value = {{0x1, 0x0, 0x0, 0xA0000}};  // 0.0000000001

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_s21_truncate_large_number) {
  s21_decimal value = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};  // Very large number / 10

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_getscale(result), 0);
}
END_TEST

// ... (ваши существующие тесты: test_s21_truncate_positive_basic,
// test_s21_truncate_negative_basic, и т.д.)

// Тест: Отрицательное число с очень маленькой дробной частью
START_TEST(test_s21_truncate_negative_small_fraction) {
  // -0.0000000001
  s21_decimal value = {{1, 0x0, 0x0, 0xA0000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  s21_set_sign(&expected, 0);                     // truncate(-0.0000000001) = 0

  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Число, где усечение требует заема через разряды (например, 0.999...9)
// Тест: Число, где усечение требует заема через разряды (например, 0.999...9)
START_TEST(test_s21_truncate_carry_propagation) {
  // 429496729.5 (0xFFFFFFFF с scale=1)
  s21_decimal value = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  // Ожидаем: 429496729 (отбросили .5)
  s21_decimal expected = {{429496729, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Отрицательное число с заемом
START_TEST(test_s21_truncate_borrow_propagation) {
  // -4294967295.9
  s21_decimal value = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  // - (4294967295 / 10) = -429496729
  s21_decimal expected = {{429496729, 0x0, 0x0, 0x0}};  // -429496729
  s21_set_sign(&expected, 1);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Число, равное 1.0 * 10^-28 (максимальный масштаб, минимальное ненулевое
// значение)
START_TEST(test_s21_truncate_min_positive) {
  // 1.0 * 10^-28
  s21_decimal value = {{1, 0x0, 0x0, 0x1C0000}};

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Отрицательное число, равное -1.0 * 10^-28
START_TEST(test_s21_truncate_min_negative) {
  // -1.0 * 10^-28
  s21_decimal value = {{1, 0x0, 0x0, 0x1C0000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тест: Усечение числа, которое после деления на 10^scale становится 0
START_TEST(test_s21_truncate_becomes_zero) {
  // 5 * 10^-1 = 0.5
  s21_decimal value = {{5, 0x0, 0x0, 0x10000}};

  s21_decimal result;
  int error = s21_truncate(value, &result);

  ck_assert_int_eq(error, 0);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};  // 0
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// ==================== s21_negate TESTS ====================

START_TEST(test_s21_negate_positive_to_negative) {
  s21_decimal value = {{0x75BCD15, 0x0, 0x0, 0x0}};  // 123456789
  s21_set_sign(&value, 0);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 1);
  ck_assert_int_eq(result.bits[0], 0x75BCD15);
}
END_TEST

START_TEST(test_s21_negate_negative_to_positive) {
  s21_decimal value = {{0x75BCD15, 0x0, 0x0, 0x0}};  // -123456789
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
  ck_assert_int_eq(result.bits[0], 0x75BCD15);
}
END_TEST

START_TEST(test_s21_negate_negative_zero) {
  s21_decimal value = {{0x0, 0x0, 0x0, 0x0}};  // -0
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_zero_dec(result), 1);
  ck_assert_int_eq(s21_get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_negate_with_scale) {
  s21_decimal value = {{0x1E240, 0x0, 0x0, 0x30000}};  // -123.456
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
  ck_assert_int_eq(result.bits[0], 0x1E240);
  ck_assert_int_eq(s21_getscale(result), 3);
}
END_TEST

START_TEST(test_s21_negate_max_value) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};  // max value
  s21_set_sign(&value, 0);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 1);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_s21_negate_null_result) {
  s21_decimal value = {{0x7B, 0x0, 0x0, 0x0}};  // 123

  int error = s21_negate(value, NULL);

  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_s21_negate_double_negate) {
  s21_decimal value = {{0x7B, 0x0, 0x0, 0x0}};  // 123

  s21_decimal result1, result2;
  int error1 = s21_negate(value, &result1);
  int error2 = s21_negate(result1, &result2);

  ck_assert_int_eq(error1, 0);
  ck_assert_int_eq(error2, 0);
  ck_assert_int_eq(s21_is_equal(value, result2), 1);
}
END_TEST

// ... (ваши существующие тесты: test_s21_negate_positive_to_negative,
// test_s21_negate_zero, и т.д.)

// Тест: Отрицание максимального отрицательного значения
START_TEST(test_s21_negate_min_value) {
  // Минимальное значение: -79228162514264337593543950335
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 0);  // Стало положительным
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

// Тест: Отрицание числа с максимальным масштабом
START_TEST(test_s21_negate_max_scale) {
  // -1.0 * 10^-28
  s21_decimal value = {{1, 0x0, 0x0, 0x1C0000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 0);  // Стало положительным
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_getscale(result), 28);
}
END_TEST

// Тест: Отрицание положительного числа с максимальным масштабом
START_TEST(test_s21_negate_positive_max_scale) {
  // 1.0 * 10^-28
  s21_decimal value = {{1, 0x0, 0x0, 0x1C0000}};
  s21_set_sign(&value, 0);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 1);  // Стало отрицательным
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_getscale(result), 28);
}
END_TEST

// Тест: Отрицание числа, равного 0.000...1 (масштаб 27)
START_TEST(test_s21_negate_very_small) {
  // 1.0 * 10^-27
  s21_decimal value = {{1, 0x0, 0x0, 0x1B0000}};
  s21_set_sign(&value, 0);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 1);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_getscale(result), 27);
}
END_TEST

// Тест: Отрицание отрицательного числа, равного -0.000...1
START_TEST(test_s21_negate_negative_very_small) {
  // -1.0 * 10^-27
  s21_decimal value = {{1, 0x0, 0x0, 0x1B0000}};
  s21_set_sign(&value, 1);

  s21_decimal result;
  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_get_sign(result), 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_getscale(result), 27);
}
END_TEST

Suite *suite_create_other(void) {
  Suite *s = suite_create("Other");
  TCase *tc_other = tcase_create("Core");

  tcase_add_test(tc_other, test_floor_positive_fraction);
  tcase_add_test(tc_other, test_floor_negative_fraction);
  tcase_add_test(tc_other, test_floor_positive_integer);
  tcase_add_test(tc_other, test_floor_negative_integer);
  tcase_add_test(tc_other, test_floor_null_pointer);
  tcase_add_test(tc_other, test_floor_large_positive_fraction);
  tcase_add_test(tc_other, test_floor_large_negative_fraction);
  tcase_add_test(tc_other, test_floor_max_integer);
  tcase_add_test(tc_other, test_floor_min_negative_integer);
  tcase_add_test(tc_other, test_floor_one_and_fraction);
  tcase_add_test(tc_other, test_floor_negative_one_and_fraction);
  tcase_add_test(tc_other, test_floor_negative_fraction_edge);

  tcase_add_test(tc_other, truncate_positive_with_fraction);
  tcase_add_test(tc_other, truncate_negative_with_fraction);
  tcase_add_test(tc_other, truncate_zero);
  tcase_add_test(tc_other, truncate_zero_to_null);
  tcase_add_test(tc_other, truncate_whole_number);
  tcase_add_test(tc_other, truncate_max_value);
  tcase_add_test(tc_other, truncate_min_negative_value);
  tcase_add_test(tc_other, truncate_near_half_down);
  tcase_add_test(tc_other, truncate_negative_near_half);
  tcase_add_test(tc_other, truncate_only_fraction);
  tcase_add_test(tc_other, truncate_large_scale);
  tcase_add_test(tc_other, truncate_max_dec);

  tcase_add_test(tc_other, round_positive);
  tcase_add_test(tc_other, round_positive_null);
  tcase_add_test(tc_other, round_down_half);
  tcase_add_test(tc_other, round_up_half);
  tcase_add_test(tc_other, round_negative_half);
  tcase_add_test(tc_other, round_negative_up);

  tcase_add_test(tc_other, negate_positive);
  tcase_add_test(tc_other, negate_negative);
  tcase_add_test(tc_other, negate_zero);
  tcase_add_test(tc_other, negate_null);
  tcase_add_test(tc_other, negate_scale_preserved);
  tcase_add_test(tc_other, negate_max_value);

  tcase_add_test(tc_other, test_s21_floor_positive_basic);
  tcase_add_test(tc_other, test_s21_floor_negative_basic);
  tcase_add_test(tc_other, test_s21_floor_positive_exact);
  tcase_add_test(tc_other, test_s21_floor_zero);
  tcase_add_test(tc_other, test_s21_floor_no_scale);
  tcase_add_test(tc_other, test_s21_floor_max_scale);
  tcase_add_test(tc_other, test_s21_floor_negative_max_scale);
  tcase_add_test(tc_other, test_s21_floor_large_number);
  tcase_add_test(tc_other, test_s21_floor_null_result);
  tcase_add_test(tc_other, test_s21_floor_positive_half);
  tcase_add_test(tc_other, test_s21_floor_negative_half);
  tcase_add_test(tc_other, test_s21_floor_small_positive);
  tcase_add_test(tc_other, test_s21_floor_small_negative);
  tcase_add_test(tc_other, test_s21_floor_max_positive);
  tcase_add_test(tc_other, test_s21_floor_min_negative);
  tcase_add_test(tc_other, test_s21_floor_scale_28_positive);
  tcase_add_test(tc_other, test_s21_floor_scale_28_negative);
  tcase_add_test(tc_other, test_s21_floor_carry_propagation);
  tcase_add_test(tc_other, test_s21_floor_borrow_propagation);

  tcase_add_test(tc_other, test_s21_round_positive_half_down);
  tcase_add_test(tc_other, test_s21_round_negative_half_down);
  tcase_add_test(tc_other, test_s21_round_border_case);
  tcase_add_test(tc_other, test_s21_round_no_scale);
  tcase_add_test(tc_other, test_s21_round_zero);
  tcase_add_test(tc_other, test_s21_round_max_precision);

  tcase_add_test(tc_other, test_s21_truncate_positive_basic);
  tcase_add_test(tc_other, test_s21_truncate_negative_basic);
  tcase_add_test(tc_other, test_s21_truncate_no_scale);
  tcase_add_test(tc_other, test_s21_truncate_zero);
  tcase_add_test(tc_other, test_s21_truncate_max_scale);
  tcase_add_test(tc_other, test_s21_truncate_small_fraction);
  tcase_add_test(tc_other, test_s21_truncate_large_number);

  tcase_add_test(tc_other, test_s21_truncate_carry_propagation);
  tcase_add_test(tc_other, test_s21_truncate_borrow_propagation);
  tcase_add_test(tc_other, test_s21_truncate_negative_small_fraction);
  tcase_add_test(tc_other, test_s21_truncate_min_positive);
  tcase_add_test(tc_other, test_s21_truncate_min_negative);
  tcase_add_test(tc_other, test_s21_truncate_becomes_zero);

  tcase_add_test(tc_other, test_s21_negate_positive_to_negative);
  tcase_add_test(tc_other, test_s21_negate_negative_to_positive);
  tcase_add_test(tc_other, test_s21_negate_negative_zero);
  tcase_add_test(tc_other, test_s21_negate_with_scale);
  tcase_add_test(tc_other, test_s21_negate_max_value);
  tcase_add_test(tc_other, test_s21_negate_null_result);
  tcase_add_test(tc_other, test_s21_negate_double_negate);

  tcase_add_test(tc_other, test_s21_negate_min_value);
  tcase_add_test(tc_other, test_s21_negate_max_scale);
  tcase_add_test(tc_other, test_s21_negate_positive_max_scale);
  tcase_add_test(tc_other, test_s21_negate_very_small);
  tcase_add_test(tc_other, test_s21_negate_negative_very_small);

  suite_add_tcase(s, tc_other);
  return s;
}