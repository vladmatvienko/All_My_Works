#include "s21_decimal.h"

#define MAX_DECIMAL "79228162514264337593543950335"
#define NEGATIVE_MAX_DECIMAL "-79228162514264337593543950335"

int s21_check_correct_dec(s21_decimal value) {
  int error = 0;
  for (int i = 0; i < 16; i++) {
    if (s21_getbit(value.bits[3], i) != 0) {
      error = S21_ERROR;
    }
  }
  for (int i = 24; i < 31; i++) {
    if (s21_getbit(value.bits[3], i) != 0) {
      error = S21_ERROR;
    }
  }
  if (s21_getscale(value) < 0 || s21_getscale(value) > 28) error = S21_ERROR;
  return error;
}

int s21_sub_bigdec(s21_big_decimal bvalue_1, s21_big_decimal bvalue_2,
                   s21_big_decimal *bresult, int sign_v1, int sign_v2) {
  // так как выщитываем знак необходимо менять знак и передавать его поэтому
  // передаем знаки как сложению

  int zero = 0;
  if ((s21_check_zero_big_decimal(bvalue_2) == 1)) zero = 1;
  unsigned int carry = 0;
  s21_inverse_big(&bvalue_2);

  s21_add_big_32(&bvalue_2, 1);
  carry = s21_sum_bigdec(&bvalue_1, &bvalue_2, bresult);

  carry = carry + sign_v1 + sign_v2 + zero;  //-1
  if (s21_getbit(carry, 0) != 0) {
    s21_inverse_big(bresult);
  }

  s21_add_big_32(bresult, s21_getbit(carry, 0));

  return carry;
}

int s21_div_to_big_dec(s21_decimal value_1, s21_decimal value_2,
                       s21_big_decimal *result, int *scale) {
  int error = S21_ARITHMETIC_OK;
  s21_big_decimal bvalue_1 = {0};
  s21_big_decimal bvalue_2 = {0};
  s21_big_decimal remainder = {0};
  s21_big_decimal tmp_result = {0};
  s21_big_decimal tmp_remainder = {0};
  s21_big_decimal frac_quotient = {0};

  s21_copy_dec_to_bigdec(value_1, value_2, &bvalue_1, &bvalue_2);
  // нахождение целой части
  s21_leveling_scale(value_1, value_2, &bvalue_1, &bvalue_2);

  if (bvalue_1.bits[6] != 0 || bvalue_2.bits[6] != 0) {
    // printf("ARIFMETIC BIG\n");
    return S21_ARITHMETIC_BIG;
  }

  error = s21_div_to_big_dec_remainder(bvalue_1, bvalue_2, result, &remainder);

  tmp_result = *result;
  // нахождение дробной части
  *scale = 0;
  int frac_guard = 0;
  // printf("Считаем десятичную часть! %d\n",
  // s21_check_zero_big_decimal(remainder));
  while (s21_check_zero_big_decimal(remainder) == 0) {
    // printf("Десятичная часть!");
    if (frac_guard++ > 30) {  // Защита (больше 28 + запас)
      error = S21_ARITHMETIC_BIG;
      break;
    }

    s21_mul_10_big(&tmp_result);
    tmp_remainder = remainder;
    s21_mul_10_big(&tmp_remainder);

    s21_set_zero_big_decimal(&frac_quotient);
    error = s21_div_to_big_dec_remainder(tmp_remainder, bvalue_2,
                                         &frac_quotient, &remainder);
    // printf("Error =%d", error);
    if (error != S21_ARITHMETIC_OK) break;

    s21_add_big_32(&tmp_result, frac_quotient.bits[0]);
    *scale += 1;

    if ((*scale >= 29) && (frac_quotient.bits[0] != 0)) break;
  }

  *result = tmp_result;

  return error;
}

int s21_div_to_big_dec_remainder(s21_big_decimal value_1,
                                 s21_big_decimal value_2,
                                 s21_big_decimal *result,
                                 s21_big_decimal *remainder) {
  s21_big_decimal tmp_value_2 = value_2;
  s21_big_decimal tmp_result = value_1;
  s21_big_decimal temp = {0};
  // s21_big_decimal tmp_add_result = {0};

  s21_big_decimal mask = {{0x1, 0, 0, 0, 0, 0, 0}};
  int error = S21_ARITHMETIC_OK;

  s21_set_zero_big_decimal(result);
  s21_set_zero_big_decimal(remainder);

  if (s21_compare_mantisa(tmp_result, value_2) == 0) {
    s21_set_zero_big_decimal(remainder);
    *result = mask;
  } else if (s21_compare_mantisa(tmp_result, value_2) == -1) {
    s21_set_zero_big_decimal(result);
    *remainder = tmp_result;
  } else {
    int outer_guard = 0;
    while ((s21_compare_mantisa(tmp_result, value_2) >= 0)) {
      if (outer_guard++ > 300) {
        error = S21_ARITHMETIC_BIG;
        break;  // Прерываем, чтобы не зависнуть
      }

      s21_set_zero_big_decimal(&mask);
      s21_add_big_32(&mask, 1);
      tmp_value_2 = value_2;
      int cnt = 0;
      int q = 0;

      int inner_guard = 0;
      while ((s21_compare_mantisa(tmp_result, tmp_value_2) == 1) ||
             (s21_compare_mantisa(tmp_result, tmp_value_2) == 0)) {
        if (inner_guard++ > 256) {
          break;
        }

        temp = tmp_value_2;
        q = cnt;

        s21_shift_left_bigdec(&tmp_value_2);
        cnt++;
      }

      s21_sub_bigdec(tmp_result, temp, remainder, 0,
                     0);  // 0,1 не понятно как поймать
      tmp_result = *remainder;

      s21_shift_left_bigdec_32(&mask, q);

      s21_sum_bigdec(result, &mask, result);
      // tmp_add_result = *result;
    }
  }

  if (s21_compare_mantisa(tmp_result, value_2) != -1 &&
      s21_compare_mantisa(tmp_result, value_2) != 0) {
    *remainder = tmp_result;
  }

  return error;
}

int s21_check_zero_decimal(s21_decimal value) {
  int zero = 0;
  for (int i = 2; i >= 0; i--) {
    if (value.bits[i] != 0) zero = 1;
  }
  return (zero != 0) ? 1 : 0;
}

int s21_check_zero_big_decimal(s21_big_decimal value) {
  for (int i = 0; i < 7; i++) {
    if (value.bits[i] != 0) return 0;
  }
  return 1;
}

void s21_set_zero_big_decimal(s21_big_decimal *value) {
  for (int i = 7; i >= 0; i--) {
    value->bits[i] = 0;
  }
}

void s21_set_zero_decimal(s21_decimal *value) {
  for (int i = 4; i >= 0; i--) {
    value->bits[i] = 0;
  }
}

// int s21_div_10_remainder(s21_big_decimal value) {
//   int remainder = 0;
//   int count = 0;
//   while ((s21_first_big_bit_search(value) > 96)) {
//     remainder = s21_div_10_big(&value);
//     if (remainder % 10 == 0) {
//       count++;
//     } else {
//       break;
//     }
//   }
//   return count;
// }

void s21_mul_to_big_dec(s21_decimal value_1, s21_decimal value_2,
                        s21_big_decimal *result) {
  value_1.bits[3] = 0x00000000;
  value_2.bits[3] = 0x00000000;
  s21_big_decimal bvalue_1 = {0};
  s21_big_decimal bvalue_2 = {0};
  s21_big_decimal temp = {0};
  s21_copy_dec_to_bigdec(value_1, value_2, &bvalue_1, &bvalue_2);

  int first_bit = s21_first_big_bit_search(bvalue_1);
  for (int i = 0; i < first_bit; i++) {
    s21_big_decimal temp_bvalue_2 = bvalue_2;
    if (s21_getbit_big_dec(bvalue_1, i) == 1) {
      s21_shift_left_bigdec_32(&temp_bvalue_2, i);
      s21_sum_bigdec(&temp, &temp_bvalue_2, result);
      for (int i = 0; i < 6; i++) {
        temp.bits[i] = result->bits[i];
        result->bits[i] = 0;
      }
    }
  }
  for (int i = 0; i < 6; i++) {
    result->bits[i] = temp.bits[i];
  }
  // result = &temp; //валгрид ка будет?
}

int s21_shift_left_bigdec_32(s21_big_decimal *big_value, int value) {
  int shift = 0;
  for (int i = 0; i < value; i++) {
    shift += s21_shift_left_bigdec(big_value);
  }
  return shift;
}
// int s21_shift_right_bigdec_32(s21_big_decimal *big_value, int value) {
//   int shift = 0;
//   for (int i = 0; i < value; i++) {
//     shift += s21_shift_right_bigdec(big_value);
//   }
//   return shift;
// }

int s21_shift_left_bigdec(s21_big_decimal *big_value) {
  unsigned long long carry = 0;
  for (int i = 0; i < 7; i++) {
    unsigned long long temp = (unsigned long long)big_value->bits[i] << 1;
    temp |= carry;
    big_value->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    // temp = (temp >> 32) | carry;
    carry = temp >> 32;
  }
  return (carry > 0) ? 1 : 0;
}

// int s21_shift_right_bigdec(s21_big_decimal *big_value) {
//   unsigned int carry = 0;
//   unsigned int new_carry = 0;
//   for (int i = 6; i >= 0; i--) {
//     new_carry = big_value->bits[i] & 1;
//     big_value->bits[i] = (big_value->bits[i] >> 1) | carry;
//     carry = new_carry << 31;
//   }
//   return (carry > 0) ? 1 : 0;
// }

// void s21_inverse(s21_decimal *bits) {
//   for (size_t i = 0; i < 3; i++) {
//     bits->bits[i] = ~bits->bits[i];
//   }
// }

void s21_inverse_big(s21_big_decimal *bits) {
  for (size_t i = 0; i < 7; i++) {
    bits->bits[i] = ~bits->bits[i];
  }
}

int s21_mul_10(s21_decimal *func_struct) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long cur =
        (unsigned long long)func_struct->bits[i] * 10ULL + carry;
    func_struct->bits[i] = (unsigned int)(cur & 0xFFFFFFFFULL);
    carry = cur >> 32;  // перенос в следующий блок
  }
  return carry == 0 ? 0 : 1;
}

int s21_mul_10_big(s21_big_decimal *func_struct) {
  unsigned long long carry = 0;
  for (int i = 0; i < 7; i++) {
    unsigned long long cur =
        (unsigned long long)func_struct->bits[i] * 10ULL + carry;
    func_struct->bits[i] = (unsigned int)(cur & 0xFFFFFFFFULL);
    carry = cur >> 32;  // перенос в следующий блок
  }
  return carry == 0 ? 0 : 1;
}

int s21_div_10_big(s21_big_decimal *func_struct) {
  unsigned long long current = 0;
  unsigned long long remainder = 0;
  for (int i = 6; i >= 0; i--) {
    current = ((unsigned long long)remainder << 32) | func_struct->bits[i];
    func_struct->bits[i] = current / 10;
    remainder = current % 10;
  }
  return (int)remainder;
}

// void s21_mul_10_scale(s21_decimal *func_struct, int scale) {
//   for (int i = 0; i < scale; i++) {
//     s21_mul_10(func_struct);
//   }
// }

void s21_add_32(s21_decimal *bits, unsigned int digit) {
  // Прибавление + int
  unsigned long long cur = (unsigned long long)bits->bits[0] + digit;
  bits->bits[0] = (unsigned int)(cur & 0xFFFFFFFFULL);
  unsigned long long carry = cur >> 32;

  for (int i = 1; i < 3 && carry; i++) {
    cur = (unsigned long long)bits->bits[i] + carry;
    bits->bits[i] = (unsigned int)(cur & 0xFFFFFFFFULL);
    carry = cur >> 32;
  }
}

void s21_add_big_32(s21_big_decimal *bits, unsigned int digit) {
  // Прибавление + int
  unsigned long long cur = (unsigned long long)bits->bits[0] + digit;
  bits->bits[0] = (unsigned int)(cur & 0xFFFFFFFFULL);
  unsigned long long carry = cur >> 32;

  for (int i = 1; i < 7 && carry; i++) {
    cur = (unsigned long long)bits->bits[i] + carry;
    bits->bits[i] = (unsigned int)(cur & 0xFFFFFFFFULL);
    carry = cur >> 32;
  }
}

void s21_setscale(s21_decimal *func_struct, int scale) {
  scale = scale << 16;
  unsigned int mask = 0x00FF0000;
  func_struct->bits[3] = (func_struct->bits[3] & ~mask) | (scale & mask);
}

int s21_getscale(s21_decimal value) {
  int scale = 0;
  scale = value.bits[3] << 1;
  scale = scale >> 17;
  return scale;
}

void s21_from_str_to_decimal(s21_decimal *func_struct, char *str) {
  // printf("Value dec: %s\n", str);
  // bits->bits[0] = 0xFF;
  while (*str) {
    if (*str >= '0' && *str <= '9') {
      s21_mul_10(func_struct);  // умножаем текущее число на 10
      s21_add_32(func_struct, *str - '0');  // прибавляем цифру
    } else if (str[0] == '-')  // 79,228,162,514,264,337,593,543,950,335
                               // 79,228,162,514,264,337,593,543,950.2467
    {
      s21_setbit(&func_struct->bits[3], 31, 1);
    } else if (*str == '.') {
      char *tmp_str = str;
      int scale = -1;
      while (*tmp_str != '\0') {
        scale++;
        tmp_str++;
      }

      // printf("String: %s Scale; %d\n",str, scale);
      s21_setscale(func_struct, scale);
    }

    str++;
  }
}

void s21_setbit(unsigned int *byte, int pos, int bit) {
  // printf("Position set bit: %d\n", pos);
  unsigned int mask = 1 << pos;
  if (bit == 1) {
    *byte = *byte | mask;
  } else {
    // unsigned int mask = 0xFF000000;
    *byte = *byte | mask;
    *byte = *byte ^ mask;
  }
}

int s21_getbit(unsigned int byte, int pos) {
  // printf("Byte: Dex: 0x%08X | Dec: %10u\n", byte, byte);
  unsigned int getbit = 0;
  unsigned int mask = 1 << pos;  // 0000 0000 0000 0000 0000 0000 0000 0001
  byte = byte & mask;
  if (byte != 0) {
    getbit = byte >> pos;
  }
  // printf("Bit: Dex: 0x%08X | Dec: %10u\n", getbit, getbit);
  return getbit;
}

// int s21_getbit_dec(s21_decimal value, int pos) {
//   int getbit = 0;

//   // unsigned int mask = 0;
//   int temp = 32;
//   for (int i = 0; i < 3; i++) {
//     if (pos < temp) {
//       pos = pos % 32;
//       getbit = s21_getbit(value.bits[i], pos);
//       break;
//     }

//     temp += 32;
//   }

//   return getbit;
// }

int s21_getbit_big_dec(s21_big_decimal value, int pos) {
  int getbit = 0;

  // unsigned int mask = 0;
  int temp = 32;
  for (int i = 0; i < 6; i++) {
    if (pos < temp) {
      pos = pos % 32;
      getbit = s21_getbit(value.bits[i], pos);
      break;
    }

    temp += 32;
  }

  return getbit;
}

// int s21_first_bit_search(s21_decimal bits) {
//   int pos = 0;
//   int carry = 0;
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j <= 31; j++) {
//       if (((bits.bits[i] >> j) & 1) == 1) {
//         pos = j + carry;
//         // break;
//       }

//       printf("%d", (bits.bits[i] >> j) & 1);
//     }

//     carry += 32;
//   }
//   return 96 - pos;
// }

int s21_first_big_bit_search(s21_big_decimal bits) {
  int pos = 0;
  int carry = 1;
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j <= 31; j++) {
      if (((bits.bits[i] >> j) & 1) == 1) {
        pos = j + carry;
      }
    }
    carry += 32;
  }

  return pos;
}

int s21_sum_bits(unsigned int value_1, unsigned int value_2,
                 unsigned int *result_p) {
  unsigned long int result = value_1;
  unsigned long int carry = value_2;
  unsigned long int sum_witout_carry = 0;
  unsigned long int carry_mask = 0;

  while (carry != 0) {
    sum_witout_carry = result ^ carry;
    carry_mask = result & carry;
    carry = carry_mask << 1;
    result = sum_witout_carry;
  }
  *result_p = result & 0xFFFFFFFF;
  carry = result >> 32;

  return carry;
}

int s21_sum_bigdec(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2,
                   s21_big_decimal *big_result) {
  int error = 0;

  unsigned int carry = 0;
  unsigned int new_carry = 0;

  for (size_t i = 0; i < 7; i++) {
    unsigned int tmp = 0;
    carry = s21_sum_bits(big_value_1->bits[i], carry, &tmp);
    new_carry = s21_sum_bits(tmp, big_value_2->bits[i], &big_result->bits[i]);
    carry = carry | new_carry;
    if (i == 2 && carry != 0) {
      error = 1;
    }
  }

  return error;
}

void s21_copy_dec_to_bigdec(s21_decimal value_1, s21_decimal value_2,
                            s21_big_decimal *big_value_1,
                            s21_big_decimal *big_value_2) {
  *big_value_1 = (s21_big_decimal){0};
  *big_value_2 = (s21_big_decimal){0};
  for (size_t i = 0; i < 3; i++) {
    big_value_1->bits[i] = value_1.bits[i];
    big_value_2->bits[i] = value_2.bits[i];
  }
}

void s21_copy_bigdec_to_dec(s21_big_decimal big_value, s21_decimal *value) {
  for (size_t i = 0; i < 3; i++) {
    value->bits[i] = big_value.bits[i];
  }
}

int s21_leveling_scale(s21_decimal value_1, s21_decimal value_2,
                       s21_big_decimal *big_value_1,
                       s21_big_decimal *big_value_2) {
  int scale_v1 = s21_getscale(value_1);
  int scale_v2 = s21_getscale(value_2);

  // обнуляем битс3 для корректного копирования
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  s21_copy_dec_to_bigdec(value_1, value_2, big_value_1, big_value_2);
  int return_scale = 0;

  if (scale_v1 == scale_v2) {
    return_scale = scale_v1;
  } else if (scale_v1 < scale_v2) {
    int diff = scale_v2 - scale_v1;

    for (int i = 0; i < diff; i++) {
      s21_mul_10_big(big_value_1);
    }
    return_scale = scale_v2;
  } else {
    int diff = scale_v1 - scale_v2;

    for (int i = 0; i < diff; i++) {
      s21_mul_10_big(big_value_2);
    }
    return_scale = scale_v1;
  }
  return return_scale;
}

int s21_normal_dec_result(s21_decimal *normal_value, s21_big_decimal big_value,
                          int scale, int sign) {
  int error = S21_ARITHMETIC_OK;
  int remainder = 0;
  int remainder_no_zero = 0;
  if (scale < 0) {
    scale = 0;
    if (sign)
      error = S21_ARITHMETIC_SMALL;
    else
      error = S21_ARITHMETIC_BIG;
  } else {
    while ((s21_first_big_bit_search(big_value) > 96) || (scale > 28)) {
      int prev_remainder = remainder;
      remainder = s21_div_10_big(&big_value);
      scale--;
      if (prev_remainder) remainder_no_zero = 1;
      if (scale < 0) {
        scale = 0;
        if (sign)
          error = S21_ARITHMETIC_SMALL;
        else
          error = S21_ARITHMETIC_BIG;
        break;
      }
    }

    s21_round_finance_big(&big_value, remainder, remainder_no_zero);
    if ((big_value.bits[3] != 0) && (!sign)) error = S21_ARITHMETIC_BIG;
    if ((big_value.bits[3] != 0) && (sign)) error = S21_ARITHMETIC_SMALL;

    s21_copy_bigdec_to_dec(big_value, normal_value);
    s21_setscale(normal_value, scale);
    s21_setbit(&normal_value->bits[3], 31, sign);
  }
  return error;
}

void s21_round_finance_big(s21_big_decimal *big_value, int remainder,
                           int no_zero_flag) {
  // банковское округление
  // округляем последнюю цифру, с учетом остатка
  // если 1-4 то просто делим
  // если от 6 до 9 то прибавляем к 0 биту 1
  // если 5 то смотрим какой бит будет при делении на 10, если четная то
  // округление вниз, если нечетная то округление вверх

  int should_round_up = 0;

  if (remainder > 5) {
    should_round_up = 1;
  } else if (remainder == 5) {
    if (no_zero_flag != 0) {
      should_round_up = 1;
    } else {
      s21_big_decimal tmp = *big_value;
      int last_digit = s21_div_10_big(&tmp) % 10;
      should_round_up = (last_digit % 2 == 1);
    }
  }

  if (should_round_up) {
    s21_add_big_32(big_value, 1);
  }
}
/*
void s21_print(s21_decimal *func_struct) {
  for (int j = 0; j < 4; j++) {
    if (j == 0) {
      printf("Number: ");
      s21_print_decimal_bit(*func_struct);
      // printf("bits[%d]:\n", j);
    } else if (j == 3) {
      printf("\n         Exp:");
    }
    printf("\nbits[%d]: ", j);
    for (int i = 31; i >= 0; i--) {
      printf("%d", (func_struct->bits[j] >> i) & 1);
      if (i % 8 == 0) printf(" ");
    }
    printf("| Dex: 0x%08X | Dec: %10u", func_struct->bits[j],
           func_struct->bits[j]);
  }

  printf(
      "\n**********************************************************************"
      "**********\n");
}

void s21_print_big(s21_big_decimal *func_struct) {
  for (int j = 0; j < 7; j++) {
    if (j == 0) {
      printf("Number:");
      // printf("bits[%d]:\n", j);
    }
    printf("\nbits[%d]: ", j);
    for (int i = 31; i >= 0; i--) {
      printf("%d", (func_struct->bits[j] >> i) & 1);
      if (i % 8 == 0) printf(" ");
    }
    printf("| Dex: 0x%08X | Dec: %10u", func_struct->bits[j],
           func_struct->bits[j]);
  }
  // printf("\nFull:    ");
  // for (int j = 3; j >= 0; j--)
  // {
  //     for (int i = 31; i>= 0; i--){
  //         printf ("%d",(func_struct->bits[j] >> i) & 1);
  //         if (i % 8 == 0) printf(" ");
  //     }
  //     printf("| ");
  // }
  printf(
      "\n**********************************************************************"
      "**********\n");
}

void s21_print_decimal_bit(s21_decimal dec) {
  char buffer[200] = {0};
  char temp[200] = {0};

  // Извлекаем знак и масштаб
  int is_negative = (dec.bits[3] >> 31) & 1;
  int scale = (dec.bits[3] >> 16) & 0xFF;

  // Обрабатываем специальный случай: ноль
  if (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) {
    printf("0");
    return;
  }

  // Преобразуем 96-битное число в строку вручную
  unsigned int num[3] = {dec.bits[0], dec.bits[1], dec.bits[2]};
  unsigned int temp_len = 0;

  // Алгоритм деления на 10 для преобразования числа в строку
  int non_zero = 1;
  while (non_zero) {
    non_zero = 0;

    // Делим 96-битное число на 10
    unsigned long long remainder = 0;
    for (int i = 2; i >= 0; i--) {
      unsigned long long value = ((unsigned long long)remainder << 32) + num[i];
      num[i] = value / 10;
      remainder = value % 10;
      if (num[i] != 0) non_zero = 1;
    }

    // Добавляем цифру в начало строки
    if (temp_len < sizeof(temp) - 1) {
      for (int i = temp_len; i > 0; i--) {
        temp[i] = temp[i - 1];
      }
      temp[0] = '0' + (char)remainder;
      temp_len++;
    }
  }

  int len = temp_len;

  // Добавляем десятичную точку
  if (scale > 0 && scale < len) {
    int point_pos = len - scale;

    // Копируем часть до точки
    strncpy(buffer, temp, point_pos);
    buffer[point_pos] = '.';

    // Копируем часть после точки
    strncpy(buffer + point_pos + 1, temp + point_pos, scale);
    buffer[point_pos + 1 + scale] = '\0';
  } else if (scale >= len) {
    // Добавляем ведущие нули
    buffer[0] = '0';
    buffer[1] = '.';

    for (int i = 0; i < scale - len; i++) {
      buffer[2 + i] = '0';
    }

    strcpy(buffer + 2 + (scale - len), temp);
  } else {
    // Без десятичной точки
    strcpy(buffer, temp);
  }

  // Удаляем лишние нули после точки
  if (scale > 0) {
    int buf_len = strlen(buffer);
    int i = buf_len - 1;

    // Удаляем конечные нули
    while (i >= 0 && buffer[i] == '0') {
      buffer[i] = '\0';
      i--;
    }

    // Если после точки ничего не осталось, удаляем точку
    if (i >= 0 && buffer[i] == '.') {
      buffer[i] = '\0';
    }
  }

  // Печатаем результат
  if (is_negative && buffer[0] != '0') {
    printf("-%s", buffer);
  } else {
    printf("%s", buffer);
  }
}

void s21_print_big_decimal_bits(s21_big_decimal dec, int sign, int scale) {
  char buffer[200] = {0};
  char temp[200] = {0};

  // Проверяем, является ли число нулем (все биты с 0 по 6 равны 0)
  int is_zero = 1;
  for (int i = 0; i < 7; i++) {
    if (dec.bits[i] != 0) {
      is_zero = 0;
      break;
    }
  }

  if (is_zero) {
    printf("0");
    return;
  }

  // Создаем массив для хранения 224-битного числа
  unsigned int num[7];
  for (int i = 0; i < 7; i++) {
    num[i] = dec.bits[i];
  }

  unsigned int temp_len = 0;
  int non_zero = 1;

  // Алгоритм деления на 10 для преобразования 224-битного числа в строку
  while (non_zero) {
    non_zero = 0;

    // Делим 224-битное число на 10
    unsigned long long remainder = 0;
    for (int i = 6; i >= 0; i--) {
      unsigned long long value = ((unsigned long long)remainder << 32) + num[i];
      num[i] = value / 10;
      remainder = value % 10;
      if (num[i] != 0) non_zero = 1;
    }

    // Добавляем цифру в начало строки
    if (temp_len < sizeof(temp) - 1) {
      // Сдвигаем существующие символы вправо
      for (int i = temp_len; i > 0; i--) {
        temp[i] = temp[i - 1];
      }
      temp[0] = '0' + (char)remainder;
      temp_len++;
    }
  }

  int len = temp_len;

  // Обрабатываем десятичную точку в зависимости от масштаба
  if (scale > 0 && scale < len) {
    // Точка внутри числа
    int point_pos = len - scale;
    strncpy(buffer, temp, point_pos);
    buffer[point_pos] = '.';
    strncpy(buffer + point_pos + 1, temp + point_pos, scale);
    buffer[point_pos + 1 + scale] = '\0';
  } else if (scale >= len) {
    // Точка перед числом (добавляем ведущие нули)
    buffer[0] = '0';
    buffer[1] = '.';

    int zeros_needed = scale - len;
    for (int i = 0; i < zeros_needed; i++) {
      buffer[2 + i] = '0';
    }

    strcpy(buffer + 2 + zeros_needed, temp);
  } else {
    // Без десятичной точки
    strcpy(buffer, temp);
  }

  // Удаляем лишние нули после десятичной точки
  if (scale > 0) {
    int buf_len = strlen(buffer);
    int i = buf_len - 1;

    // Удаляем конечные нули
    while (i >= 0 && buffer[i] == '0') {
      buffer[i] = '\0';
      i--;
    }

    // Если после точки ничего не осталось, удаляем точку
    if (i >= 0 && buffer[i] == '.') {
      buffer[i] = '\0';
    }
  }

  // Печатаем результат с учетом знака
  if (sign && buffer[0] != '0') {
    printf("-%s", buffer);
  } else {
    printf("%s", buffer);
  }
}
*/
int s21_is_zero(s21_big_decimal big_value) {
  return big_value.bits[0] == 0 && big_value.bits[1] == 0 &&
         big_value.bits[2] == 0;
}

// сравнение мантис двух бигдецималов
int s21_compare_mantisa(s21_big_decimal big_value_1,
                        s21_big_decimal big_value_2) {
  int result = 0;
  // проходим по мантисе бигдецимал начиная со старших разрядов и идём к младшим
  // если значение i-ые ячейки с битами не равны, то делаем вывод, что значения
  // бигдецималов не равны,меняем результат и завершаем проход
  for (int i = 6; i >= 0; i--) {
    if (big_value_1.bits[i] > big_value_2.bits[i]) {
      result = 1;
      break;
    } else if (big_value_1.bits[i] < big_value_2.bits[i]) {
      result = -1;
      break;
    }
  }
  // возвращаем результат:
  // 0, если big_value_1 = big_value_2
  // 1, big_value_1 > big_value_2
  // -1, big_value_1 < big_value_2
  return result;
}

// 0 - big_value_1 = big_value_2
// 1 - big_value_1 > big_value_2
// -1 - big_value_1 < big_value_2
int s21_total_comparison(s21_big_decimal big_value_1,
                         s21_big_decimal big_value_2, int sign_of_value_1,
                         int sign_of_value_2) {
  int result = 0;
  if (s21_is_zero(big_value_1) &&
      s21_is_zero(big_value_2)) {  // проверка на нули с разными знаками (0=-0)
    result = 0;
  } else if (sign_of_value_1 == sign_of_value_2 &&
             sign_of_value_1 == 0) {  // оба числа положительные
    if (s21_compare_mantisa(big_value_1, big_value_2) ==
        0) {  // первое = второе
      result = 0;
    } else if (s21_compare_mantisa(big_value_1, big_value_2) ==
               1) {  // первое > второе
      result = 1;
    } else if (s21_compare_mantisa(big_value_1, big_value_2) ==
               -1) {  // первое < второе
      result = -1;
    }
  } else if (sign_of_value_1 == sign_of_value_2 &&
             sign_of_value_1 == 1) {  // оба числа отрицательные
    if (s21_compare_mantisa(big_value_1, big_value_2) ==
        0) {  // первое = второе
      result = 0;
    } else if (s21_compare_mantisa(big_value_1, big_value_2) ==
               1) {  // первое < второе
      result = -1;
    } else if (s21_compare_mantisa(big_value_1, big_value_2) ==
               -1) {  // первое > второе
      result = 1;
    }
  } else if (sign_of_value_1 >
             sign_of_value_2) {  // разные знаки --> первое < второе
    result = -1;
  } else if (sign_of_value_1 <
             sign_of_value_2) {  // разные знаки --> первое > второе
    result = 1;
  }
  return result;
}

// предфинальная функция для сравнения
int s21_comparison_for_all(
    s21_decimal value_1, s21_decimal value_2) {  // принимаем 2 обычных децимала
  s21_big_decimal big_value_1 = {0};  // создаются 2 бигдецимала
  s21_big_decimal big_value_2 = {0};
  s21_leveling_scale(value_1, value_2, &big_value_1,
                     &big_value_2);  // входные децималы копируются в
                                     // бигдецималы и приводятся к одному скейлу
  int sign_of_value_1 =
      s21_getbit(value_1.bits[3], 31);  // извлекаем знаки входных децималов
  int sign_of_value_2 = s21_getbit(value_2.bits[3], 31);
  return s21_total_comparison(
      big_value_1, big_value_2, sign_of_value_1,
      sign_of_value_2);  // возвращаем результат, 0, 1 или -1
}

int s21_get_sign(s21_decimal value) {
  return (value.bits[3] & 0x80000000) >> 31;
}

int s21_is_zero_dec(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

// int s21_is_less_simple(s21_decimal value1, s21_decimal value2,
//                        s21_decimal *result) {
//   int error = 0;
//   if (result == NULL) error = 1;
//   result->bits[0] = (value1.bits[0] < value2.bits[0]) ? 1 : 0;

//   return error;
// }

void s21_set_sign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= 0x80000000;
  } else {
    value->bits[3] &= 0x7FFFFFFF;
  }
}

int s21_div_10(s21_decimal *value) {
  int error = 0;
  if (value == NULL) {
    error = 1;
  } else {
    unsigned long long carry = 0;

    for (int i = 2; i >= 0; i--) {
      unsigned long long current =
          carry * 4294967296ULL + value->bits[i];  // 4294967296 = 2^32
      value->bits[i] = (unsigned int)(current / 10);
      carry = current % 10;
    }
  }
  return error;
}

int s21_is_valid_decimal(s21_decimal dec) {
  int is_valid = 1;
  unsigned int scale = (dec.bits[3] >> 16) & 0xFF;  // Извлекаем биты 16-23
  unsigned int reserved_low = dec.bits[3] & 0xFFFF;         // Биты 0-15
  unsigned int reserved_high = (dec.bits[3] >> 24) & 0x7F;  // Биты 24-30

  // Проверка: степень должна быть от 0 до 28
  if (scale > 28) {
    is_valid = 0;
  }

  // Проверка: зарезервированные биты (0-15 и 24-30) должны быть нулями
  if (reserved_low != 0 || reserved_high != 0) {
    is_valid = 0;
  }

  return is_valid;
}

s21_decimal s21_decimal_get_zero() {
  s21_decimal zero = {{0, 0, 0, 0}};
  return zero;
}

int s21_sub_internal(s21_decimal value1, s21_decimal value2,
                     s21_decimal *result) {
  if (result == NULL) return 1;

  // Приводим к одному масштабу
  int scale1 = s21_getscale(value1);
  int scale2 = s21_getscale(value2);
  int max_scale = (scale1 > scale2) ? scale1 : scale2;

  // Приводим оба числа к максимальному масштабу
  if (scale1 < max_scale) {
    for (int i = 0; i < max_scale - scale1; i++) {
      if (s21_mul_10(&value1) != 0) return 1;
    }
    s21_setscale(&value1, max_scale);
  }

  if (scale2 < max_scale) {
    for (int i = 0; i < max_scale - scale2; i++) {
      if (s21_mul_10(&value2) != 0) return 1;
    }
    s21_setscale(&value2, max_scale);
  }

  // Выполняем вычитание мантисс
  unsigned int borrow = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long diff = (unsigned long long)value1.bits[i] -
                              (unsigned long long)value2.bits[i] - borrow;
    result->bits[i] = (unsigned int)diff;
    borrow = (diff > 0xFFFFFFFFULL) ? 1 : 0;
  }

  // Если остался заём, значит value1 < value2 - ошибка
  if (borrow != 0) {
    return 1;
  }

  // Устанавливаем scale результата
  s21_setscale(result, max_scale);
  s21_set_sign(result, 0);  // Результат всегда положительный

  return 0;
}
// преобразовываем строку с float для перевода в децимал
int s21_float_str_preparing_for_convert(float src, char *float_str,
                                        char *final_float_str) {
  int error = 0;
  if (src != 0.0) {
    error = check_minimal_float_value(src, float_str);
  }
  if (error || src == 0.0) {
    final_float_str[0] = '0';
    final_float_str[1] = '\0';
  } else {
    make_final_float_str(src, float_str, final_float_str);
    error = check_maximum_float_value(src, final_float_str);
  }
  return error;
}

int check_minimal_float_value(float src, char *float_str) {
  int error = 0;
  if ((src >= 0 && float_str[0] == '0') || (src < 0 && float_str[1] == '0')) {
    int j = src > 0 ? 2 : 3;
    int zeros_flag = 1;
    for (int i = 0; i < 27; i++) {
      if (float_str[j] != '0') {
        zeros_flag = 0;
        break;
      }
      j++;
    }
    if (zeros_flag && float_str[j] == '0') {
      error = 1;
    }
  }
  return error;
}

int check_maximum_float_value(float src, char *final_float_str) {
  int error = 0;
  char *max_decimal = src >= 0 ? MAX_DECIMAL : NEGATIVE_MAX_DECIMAL;
  if (final_float_str[0] == 'i' || final_float_str[1] == 'i') {
    error = 1;
  }

  if (!error) {
    int len_of_int_part = 0;
    while (final_float_str[len_of_int_part] != '\0' &&
           final_float_str[len_of_int_part] != '.') {  // 23.459
      len_of_int_part++;
    }
    // len_of_int_part += src >= 0 ? 0 : -1;
    if ((src >= 0 && len_of_int_part == 29) ||
        (src < 0 && len_of_int_part == 30)) {
      for (int i = src >= 0 ? 0 : 1; i < 29 + (src >= 0 ? 0 : 1); i++) {
        if (final_float_str[i] > max_decimal[i]) {
          error = 1;
          break;
        } else if (final_float_str[i] < max_decimal[i]) {
          error = 0;
          break;
        }
      }
    } else if ((src >= 0 && len_of_int_part > 29) ||
               (src < 0 && len_of_int_part > 30)) {
      error = 1;
    }
  }
  return error;
}

void make_final_float_str(float src, char *float_str, char *final_float_str) {
  if (src < 0) {
    negative(float_str, final_float_str);
  } else {
    positive(float_str, final_float_str);
  }
}

void negative(char *float_str, char *final_str) {
  int flag_of_significant_figure = 0;
  int figures_cnt = 0;
  int end_flag = 0;
  final_str[0] = '-';
  int j = 1;
  int len_befor_point = len_to_point(float_str);
  while (figures_cnt < 7) {
    if (float_str[j] == '\0') {
      end_flag = 1;
      break;
    }
    if (float_str[j] == '.') {
      final_str[j] = '.';
    } else if (float_str[j] != '0' && !flag_of_significant_figure) {
      flag_of_significant_figure = 1;
      final_str[j] = float_str[j];
      figures_cnt++;
    } else if (flag_of_significant_figure) {
      final_str[j] = float_str[j];
      figures_cnt++;
    } else if (float_str[j] == '0') {
      final_str[j] = '0';
    }
    j++;
  }
  int len_final_str = j;
  if (!end_flag && ((float_str[j] != '.' && float_str[j] > '4') ||
                    (float_str[j] == '.' && float_str[j + 1] > '4'))) {
    j--;
    while (j != 0 && (final_str[j] == '9' || final_str[j] == '.')) {
      if (final_str[j] != '.') {
        final_str[j] = '0';
      }
      j--;
    }
    if (j == 0) {
      for (int i = len_final_str; i >= 2; i--) {
        final_str[i] = final_str[i - 1];
      }
      final_str[1] = '1';
      len_final_str++;
    } else {
      final_str[j] = (char)((int)final_str[j] + 1);
    }
  }
  for (int i = len_final_str; i < len_befor_point; i++) {
    final_str[i] = '0';
  }
  if (len_befor_point > len_final_str) {
    final_str[len_befor_point] = '\0';
  } else {
    final_str[len_final_str] = '\0';
  }
  // printf("str:%s\n", float_str);
  // printf("FINAL_STR:%s\n", final_str);
}

void positive(char *float_str, char *final_str) {
  int flag_of_significant_figure = 0;
  int figures_cnt = 0;
  int end_flag = 0;
  int j = 0;
  int len_befor_point = len_to_point(float_str);
  while (figures_cnt < 7) {
    if (float_str[j] == '\0') {
      end_flag = 1;
      break;
    }
    if (float_str[j] == '.') {
      final_str[j] = '.';
    } else if (float_str[j] != '0' && !flag_of_significant_figure) {
      flag_of_significant_figure = 1;
      final_str[j] = float_str[j];
      figures_cnt++;
    } else if (flag_of_significant_figure) {
      final_str[j] = float_str[j];
      figures_cnt++;
    } else if (float_str[j] == '0') {
      final_str[j] = '0';
    }
    j++;
  }
  int len_final_str = j;
  if (!end_flag && ((float_str[j] != '.' && float_str[j] > '4') ||
                    (float_str[j] == '.' && float_str[j + 1] > '4'))) {
    j--;
    while (j != -1 && (final_str[j] == '9' || final_str[j] == '.')) {
      if (final_str[j] != '.') {
        final_str[j] = '0';
      }
      j--;
    }
    if (j == -1) {
      for (int i = len_final_str; i >= 1; i--) {
        final_str[i] = final_str[i - 1];
      }
      final_str[0] = '1';
      len_final_str++;
    } else {
      final_str[j] = (char)((int)final_str[j] + 1);
    }
  }
  for (int i = len_final_str; i < len_befor_point; i++) {
    final_str[i] = '0';
  }
  if (len_befor_point > len_final_str) {
    final_str[len_befor_point] = '\0';
  } else {
    final_str[len_final_str] = '\0';
  }

  // printf("str:%s\n", float_str);
  // printf("FINAL_STR:%s\n", final_str);
}

int len_to_point(char *float_str) {
  int len = 0;
  while (float_str[len] != '.' && float_str[len] != '\0') {
    len++;
  }
  return len;
}

double decimal_to_double(s21_decimal src) {
  int sign = s21_getbit(src.bits[3], 31);
  int scale = s21_getscale(src);
  double result = 0.0;

  result += (double)src.bits[2] * pow(2.0, 64.0);
  result += (double)src.bits[1] * pow(2.0, 32.0);
  result += (double)src.bits[0];

  if (scale > 0) {
    result /= pow(10.0, (double)scale);
  }

  if (sign) {
    result *= -1;
  }

  return result;
}

float decimal_to_float(s21_decimal src) {
  int sign = s21_getbit(src.bits[3], 31);
  int scale = s21_getscale(src);
  float result = 0.0;

  result += (float)src.bits[2] * pow(2.0, 64.0);
  result += (float)src.bits[1] * pow(2.0, 32.0);
  result += (float)src.bits[0];

  if (scale > 0) {
    result /= pow(10.0, (float)scale);
  }

  if (sign) {
    result *= -1;
  }
  return result;
}