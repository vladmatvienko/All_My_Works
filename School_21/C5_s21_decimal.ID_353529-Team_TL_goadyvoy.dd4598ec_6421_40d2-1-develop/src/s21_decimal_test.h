#ifndef S21_DECIMAL_TEST_H_
#define S21_DECIMAL_TEST_H_

#include <check.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_support.h"

#define MAX_SCALE 28
#define MAX4BITE 0xffffffffU
#define SIGN_BIT 0x80000000
#define SCALE_MASK 0xFF0000
#define CLEAR_SIGN_MASK 0x7FFFFFFF
#define LOWER_32_BITS_MASK 0xFFFFFFFF

// Enum для кодов ошибок
typedef enum {
  S21_OK = 0,
  S21_TOO_LARGE = 1,
  S21_TOO_SMALL = 2,
  S21_DIVISION_BY_ZERO = 3,
  S21_CONVERSION_ERROR = 1,
  S21_CALCULATION_ERROR = 1
} s21_error_code;

// Вспомогательные функции для создания и манипуляции decimal в тестах
s21_decimal create_decimal(int low, int mid, int high, int sign, int scale);

// Функции для работы с s21_work_decimal (внутренние для тестов арифметики)
int compare_abs(s21_decimal value_1, s21_decimal value_2, int *result);

// Объявления Suite для основных тестовых наборов
Suite *suite_support_functions(void);
Suite *suite_create_arithmetic(void);
Suite *suite_create_compare(void);
Suite *suite_create_conversion(void);
Suite *suite_create_other(void);

#endif  // S21_DECIMAL_TEST_H_
