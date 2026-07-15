#ifndef S21_CONVERTOR_H_
#define S21_OCONVERTOR_H_

// коды ошибок
// 0 - ОК
// 1 - calculation error

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

typedef enum s21_convertor_result {
  S21_CONVERTOR_OK = 0,
  S21_CONVERTOR_ERRON = 1,
} s21_convertor_result;

#endif