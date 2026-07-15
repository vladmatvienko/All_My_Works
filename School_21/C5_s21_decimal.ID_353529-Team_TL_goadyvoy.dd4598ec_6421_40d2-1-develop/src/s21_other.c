#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 1;

  if (result != NULL && s21_is_valid_decimal(value)) {
    error = 0;
    int sign = s21_get_sign(value);
    int scale = s21_getscale(value);

    *result = value;

    if (scale != 0 && !s21_is_zero_dec(value)) {
      s21_decimal truncated = {0};
      error = s21_truncate(value, &truncated);

      if (!error) {
        *result = truncated;

        if (sign) {
          if (!s21_is_equal(value, truncated)) {
            s21_decimal one = {{1, 0, 0, 0}};
            s21_set_sign(&one, 1);

            error = s21_add(truncated, one, result);
          }
        }
      }
    }
  }

  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 1;

  if (result != NULL && s21_is_valid_decimal(value)) {
    error = 0;
    int sign = s21_get_sign(value);
    int scale = s21_getscale(value);

    *result = value;

    if (scale == 0 || s21_is_zero_dec(value)) {
      s21_setscale(result, 0);
    } else {
      s21_decimal abs_value = value;
      s21_set_sign(&abs_value, 0);

      s21_decimal truncated = {0};
      s21_decimal fractional = {0};
      s21_decimal half = {{5, 0, 0, 0}};
      s21_setscale(&half, 1);

      if (s21_truncate(abs_value, &truncated) == 0 &&
          s21_sub_internal(abs_value, truncated, &fractional) == 0) {
        int fractional_scale = s21_getscale(fractional);
        for (int i = 1; i < fractional_scale && error == 0; i++) {
          error = s21_mul_10(&half);
        }

        if (error == 0) {
          s21_setscale(&half, fractional_scale);

          if (s21_is_less(half, fractional)) {
            s21_decimal one = {{1, 0, 0, 0}};
            s21_decimal rounded_up = {0};
            error = s21_add(truncated, one, &rounded_up);
            if (error == 0) {
              s21_set_sign(&rounded_up, sign);
              *result = rounded_up;
            }
          } else if (s21_is_equal(fractional, half)) {
            if ((truncated.bits[0] & 1) == 0) {
              s21_set_sign(&truncated, sign);
              *result = truncated;
            } else {
              s21_decimal one = {{1, 0, 0, 0}};
              s21_decimal rounded_up = {0};
              error = s21_add(truncated, one, &rounded_up);
              if (error == 0) {
                s21_set_sign(&rounded_up, sign);
                *result = rounded_up;
              }
            }
          } else {
            s21_set_sign(&truncated, sign);
            *result = truncated;
          }

          if (error == 0) {
            s21_setscale(result, 0);
          }
        }
      } else {
        error = 1;
      }
    }
  }

  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 1;

  if (result != NULL && s21_is_valid_decimal(value)) {
    error = 0;
    int scale = s21_getscale(value);

    *result = value;
    s21_setscale(result, 0);

    if (scale > 0) {
      for (int i = 0; i < scale && !error; i++) {
        error = s21_div_10(result);
      }
    }
  }

  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 1;

  if (result != NULL) {
    if (s21_is_valid_decimal(value)) {
      *result = value;

      int current_sign = s21_get_sign(*result);
      s21_set_sign(result, !current_sign);

      error = 0;
    }
  }

  return error;
}