#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 1;
  if (dst != NULL) {
    error = 0;
    // обнуляем все ячейки децимала
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      s21_setbit(&dst->bits[3], 31, 1);  // устанавливаем знак минус
      src *= -1;
    }
    dst->bits[0] =
        src;  // записываем положительный инт в ячейку с наименьшим разрядом
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 1;
  if (dst == NULL || isnan(src)) {
    error = 1;
  } else {
    char float_str[100];
    sprintf(float_str, "%.29f", src);
    // printf("\n***%s***\n", float_str);
    int len_float_str = strlen(float_str);
    while (float_str[len_float_str - 1] == '0') {
      len_float_str--;
    }
    if (float_str[len_float_str] == '.') {
      len_float_str--;
      float_str[len_float_str] = '\0';
    } else {
      float_str[len_float_str] = '\0';
    }
    // printf("\n***%s***\n", float_str);
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    char final_float_str[100];
    error =
        s21_float_str_preparing_for_convert(src, float_str, final_float_str);
    if (!error) {
      s21_from_str_to_decimal(dst, final_float_str);
    }
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  }
  if (!error) {
    double dst_with_part_after_poin = decimal_to_double(src);
    dst_with_part_after_poin = trunc(dst_with_part_after_poin);

    if (dst_with_part_after_poin > INT_MAX ||
        dst_with_part_after_poin < INT_MIN) {
      error = 1;
    } else {
      *dst = dst_with_part_after_poin;
    }
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 1;
  if (dst != NULL) {
    *dst = decimal_to_float(src);
    error = 0;
  }
  return error;
}