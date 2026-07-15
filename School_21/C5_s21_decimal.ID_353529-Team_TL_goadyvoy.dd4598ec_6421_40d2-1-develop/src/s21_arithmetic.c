#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = S21_ARITHMETIC_OK;
  s21_big_decimal bvalue_1 = {0};
  s21_big_decimal bvalue_2 = {0};
  s21_big_decimal bresult = {0};
  if (!result)
    error = S21_ERROR;
  else if ((s21_check_correct_dec(value_1) == S21_ERROR) ||
           (s21_check_correct_dec(value_2) == S21_ERROR))
    error = S21_ERROR;
  else {
    // Сложение положительного и отрицательного числа равняется вычитанию
    // value_1 + -value2 = value_1 - value_2
    if ((s21_getbit(value_1.bits[3], 31) == 0) &&
        (s21_getbit(value_2.bits[3], 31) == 1)) {
      s21_setbit(&value_2.bits[3], 31, 0);
      error = s21_sub(value_1, value_2, result);
    }
    // Сложение сложение двух отрицательных чисел равно результату сложения с
    // обратным знаком
    //-value_1 + -value2 = -(value_1 + value_2)
    else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
             (s21_getbit(value_2.bits[3], 31) == 1)) {
      int scale_base =
          s21_leveling_scale(value_1, value_2, &bvalue_1, &bvalue_2);
      if (scale_base > 28) error = S21_ARITHMETIC_BIG;
      int carry = s21_sum_bigdec(&bvalue_1, &bvalue_2, &bresult);
      if (carry == 1) error = S21_ARITHMETIC_BIG;

      error = s21_normal_dec_result(result, bresult, scale_base, 1);
    }
    // Сложение положительного и отрицательного числа равняется вычитанию
    //-value_1 + value2  = value_2 - value_1
    else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
             (s21_getbit(value_2.bits[3], 31) == 0)) {
      s21_setbit(&value_1.bits[3], 31, 0);
      error = s21_sub(value_2, value_1, result);
    }
    // Сложение сложение двух положительных чисел
    // value_1 + value2 = value_1 + value_2
    else if ((s21_getbit(value_1.bits[3], 31) == 0) &&
             (s21_getbit(value_2.bits[3], 31) == 0)) {
      int scale_base =
          s21_leveling_scale(value_1, value_2, &bvalue_1, &bvalue_2);
      if (scale_base > 28) error = S21_ARITHMETIC_BIG;

      int carry = s21_sum_bigdec(&bvalue_1, &bvalue_2, &bresult);
      if (carry == 1) error = S21_ARITHMETIC_BIG;
      error = s21_normal_dec_result(result, bresult, scale_base, 0);
    }
  }

  if (!s21_check_zero_decimal(*result)) s21_set_zero_decimal(result);
  if (error != S21_ARITHMETIC_OK) s21_set_zero_decimal(result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = S21_ARITHMETIC_OK;
  unsigned int carry = 0;
  s21_big_decimal bvalue_1 = {0};
  s21_big_decimal bvalue_2 = {0};
  s21_big_decimal bresult = {0};

  if (!result)
    error = S21_ERROR;
  else if ((s21_check_correct_dec(value_1) == S21_ERROR) ||
           (s21_check_correct_dec(value_2) == S21_ERROR))
    error = S21_ERROR;
  else {
    // value_1 - value2 = (+value_1) - (+value_2) // (value_1 не меняется
    // value_2 в дополнительном коде)
    if ((s21_getbit(value_1.bits[3], 31) == 0) &&
        (s21_getbit(value_2.bits[3], 31) == 0)) {
      int scale_base =
          s21_leveling_scale(value_1, value_2, &bvalue_1, &bvalue_2);
      // printf("SCALE %d\n", scale_base);
      int sign_v1 = s21_getbit(value_1.bits[3], 31);
      s21_setbit(&value_2.bits[3], 31, 1);
      int sign_v2 = s21_getbit(value_2.bits[3], 31);
      carry = s21_sub_bigdec(bvalue_1, bvalue_2, &bresult, sign_v1, sign_v2);
      error = s21_normal_dec_result(result, bresult, scale_base,
                                    s21_getbit(carry, 0));
    }

    //-value_1 - value2 = (-value_1) - (+value_2) = -(value_1 + value_2)
    // Числа передаются в сумуу знак меняетя
    else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
             (s21_getbit(value_2.bits[3], 31) == 0)) {
      s21_setbit(&value_2.bits[3], 31, 1);
      error = s21_add(value_1, value_2, result);
      s21_setbit(&result->bits[3], 31, 1);
    }

    //-value_1 - -value2  = (-value_1) +(+value_2) = value_2 - value_1
    // меняем местами значения
    else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
             (s21_getbit(value_2.bits[3], 31) == 1)) {
      int scale_base =
          s21_leveling_scale(value_1, value_2, &bvalue_1, &bvalue_2);
      int sign_v1 = s21_getbit(value_1.bits[3], 31);
      s21_setbit(&value_2.bits[3], 31, 0);
      int sign_v2 = s21_getbit(value_2.bits[3], 31);
      carry = s21_sub_bigdec(bvalue_2, bvalue_1, &bresult, sign_v2, sign_v1);
      error = s21_normal_dec_result(result, bresult, scale_base,
                                    s21_getbit(carry, 0));

    }

    // value_1 - -value2 (value_1) - (-value_2) = value_1 + value_2 //value_1 ,
    // value_2 передается в сумуу знак меняетя
    else if ((s21_getbit(value_1.bits[3], 31) == 0) &&
             (s21_getbit(value_2.bits[3], 31) == 1)) {
      s21_setbit(&value_2.bits[3], 31, 0);
      error = s21_add(value_1, value_2, result);
      s21_setbit(&result->bits[3], 31, 0);
    }
  }
  if (!s21_check_zero_decimal(*result)) s21_set_zero_decimal(result);
  if (error != S21_ARITHMETIC_OK) s21_set_zero_decimal(result);
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = S21_ARITHMETIC_OK;

  int scale_v1 = s21_getscale(value_1);
  int scale_v2 = s21_getscale(value_2);
  s21_big_decimal bresult = {0};

  if (!result)
    error = S21_ERROR;
  else if ((s21_check_correct_dec(value_1) == S21_ERROR) ||
           (s21_check_correct_dec(value_2) == S21_ERROR))
    error = S21_ERROR;
  else {
    s21_mul_to_big_dec(value_1, value_2, &bresult);

    int scale_res = scale_v1 + scale_v2;
    // value_1 * -value2
    if ((s21_getbit(value_1.bits[3], 31) == 0) &&
        (s21_getbit(value_2.bits[3], 31) == 1)) {
      error = s21_normal_dec_result(result, bresult, scale_res, 1);
    }
    //-value_1 * -value2
    else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
             (s21_getbit(value_2.bits[3], 31) == 1)) {
      error = s21_normal_dec_result(result, bresult, scale_res, 0);
    }
    //-value_1 * value2
    else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
             (s21_getbit(value_2.bits[3], 31) == 0)) {
      error = s21_normal_dec_result(result, bresult, scale_res, 1);
    }
    // value_1 * value2
    else if ((s21_getbit(value_1.bits[3], 31) == 0) &&
             (s21_getbit(value_2.bits[3], 31) == 0)) {
      error = s21_normal_dec_result(result, bresult, scale_res, 0);
    }
  }

  if (!s21_check_zero_decimal(*result)) s21_set_zero_decimal(result);
  if (error != S21_ARITHMETIC_OK) s21_set_zero_decimal(result);
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = S21_ARITHMETIC_OK;

  s21_big_decimal bresult = {0};

  if (!result)
    error = S21_ERROR;
  else if ((s21_check_correct_dec(value_1) == S21_ERROR) ||
           (s21_check_correct_dec(value_2) == S21_ERROR))
    error = S21_ERROR;
  else if (!s21_check_zero_decimal(value_2))
    error = S21_ARITHMETIC_ZERO_DIV;
  else {
    int scale_res = 0;
    int res_sign = (s21_getbit(value_1.bits[3], 31) == 0) ^
                   (s21_getbit(value_2.bits[3], 31) == 1);
    error = s21_div_to_big_dec(value_1, value_2, &bresult, &scale_res);
    if ((error == 1) && (res_sign == 1)) {
      error = S21_ARITHMETIC_SMALL;
    }

    if (!error) {
      // value_1 / -value2
      if ((s21_getbit(value_1.bits[3], 31) == 0) &&
          (s21_getbit(value_2.bits[3], 31) == 1)) {
        error = s21_normal_dec_result(result, bresult, scale_res, 1);
      }
      //-value_1 / -value2
      else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
               (s21_getbit(value_2.bits[3], 31) == 1)) {
        error = s21_normal_dec_result(result, bresult, scale_res, 0);
      }
      //-value_1 / value2
      else if ((s21_getbit(value_1.bits[3], 31) == 1) &&
               (s21_getbit(value_2.bits[3], 31) == 0)) {
        error = s21_normal_dec_result(result, bresult, scale_res, 1);
      }
      // value_1 / value2
      else if ((s21_getbit(value_1.bits[3], 31) == 0) &&
               (s21_getbit(value_2.bits[3], 31) == 0)) {
        error = s21_normal_dec_result(result, bresult, scale_res, 0);
      }
    }
  }

  if (!s21_check_zero_decimal(*result)) s21_set_zero_decimal(result);
  if (error != S21_ARITHMETIC_OK) s21_set_zero_decimal(result);
  return error;
}