#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int current_result = s21_comparison_for_all(value_1, value_2);
  if (current_result == -1) {
    result = 1;
  }
  return result;
}
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int current_result = s21_comparison_for_all(value_1, value_2);
  if (current_result == -1 || !current_result) {
    result = 1;
  }
  return result;
}
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int current_result = s21_comparison_for_all(value_1, value_2);
  if (current_result == 1) {
    result = 1;
  }
  return result;
}
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int current_result = s21_comparison_for_all(value_1, value_2);
  if (current_result == 1 || !current_result) {
    result = 1;
  }
  return result;
}
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int current_result = s21_comparison_for_all(value_1, value_2);
  if (!current_result) {
    result = 1;
  }
  return result;
}
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
