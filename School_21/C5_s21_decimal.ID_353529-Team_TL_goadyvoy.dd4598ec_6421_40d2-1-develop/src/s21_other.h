#ifndef S21_OTHER_H_
#define S21_OTHER_H_

// коды ошибок
// 0 - ОК
// 1 - calculation error

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

typedef enum s21_other_result {
  S21_OTHER_OK = 0,
  S21_OTHER_ERROR = 1,
} s21_other_result;

#endif