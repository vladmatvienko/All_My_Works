#ifndef S21_SUPPORT_H_
#define S21_SUPPORT_H_

// Вспомогательные функции

// Печать (для отладки)
// void s21_print(s21_decimal *bits);
// void s21_print_big(s21_big_decimal *bits);
// void s21_print_decimal_bit(s21_decimal bits);
// void s21_print_big_decimal_bits(s21_big_decimal dec, int sign, int scale);

// Конвертация строки (используется в s21_convertor.c)
void s21_from_str_to_decimal(s21_decimal *bits, char *str);

// Функции сравнения big_decimal
int s21_is_zero(s21_big_decimal big_value);
int s21_compare_mantisa(s21_big_decimal big_value_1,
                        s21_big_decimal big_value_2);
int s21_total_comparison(s21_big_decimal big_value_1,
                         s21_big_decimal big_value_2, int sign_of_value_1,
                         int sign_of_value_2);
int s21_comparison_for_all(s21_decimal value_1, s21_decimal value_2);

// Функции поиска
int s21_getbit(unsigned int byte, int pos);
int s21_getbit_big_dec(s21_big_decimal value, int pos);
int s21_check_correct_dec(s21_decimal value);
int s21_first_big_bit_search(s21_big_decimal bits);

// Функции изменения
void s21_setscale(s21_decimal *bits, int scale);
int s21_getscale(s21_decimal bits);
int s21_check_zero_decimal(s21_decimal value);
int s21_check_zero_big_decimal(s21_big_decimal value);
void s21_setbit(unsigned int *byte, int pos, int bit);
int s21_leveling_scale(s21_decimal value_1, s21_decimal value_2,
                       s21_big_decimal *big_value_1,
                       s21_big_decimal *big_value_2);
void s21_copy_dec_to_bigdec(s21_decimal value_1, s21_decimal value_2,
                            s21_big_decimal *big_value_1,
                            s21_big_decimal *big_value_2);
void s21_copy_bigdec_to_dec(s21_big_decimal big_value, s21_decimal *value);
int s21_normal_dec_result(s21_decimal *normal_value, s21_big_decimal big_value,
                          int scale, int sign);
void s21_round_finance_big(s21_big_decimal *big_value, int remainder,
                           int no_zero_flag);
// void s21_inverse(s21_decimal *bits);
void s21_inverse_big(s21_big_decimal *bits);
void s21_set_zero_decimal(s21_decimal *value);
void s21_set_zero_big_decimal(s21_big_decimal *value);

// Арифметические вспомогательные функции
int s21_sum_bigdec(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2,
                   s21_big_decimal *big_result);
int s21_sum_bits(unsigned int value_1, unsigned int value_2,
                 unsigned int *result_p);
int s21_div_10_big(s21_big_decimal *func_struct);
int s21_mul_10(s21_decimal *func_struct);
int s21_mul_10_big(s21_big_decimal *func_struct);
int s21_sub_bigdec(s21_big_decimal bvalue_1, s21_big_decimal bvalue_2,
                   s21_big_decimal *bresult, int sign_v1, int sign_v2);
void s21_add_32(s21_decimal *bits, unsigned int digit);
void s21_add_big_32(s21_big_decimal *bits, unsigned int digit);
void s21_mul_to_big_dec(s21_decimal value_1, s21_decimal value_2,
                        s21_big_decimal *result);
int s21_div_to_big_dec(s21_decimal value_1, s21_decimal value_2,
                       s21_big_decimal *result, int *scale);
int s21_div_to_big_dec_remainder(s21_big_decimal value_1,
                                 s21_big_decimal value_2,
                                 s21_big_decimal *result,
                                 s21_big_decimal *remainder);

// Функции сдвига
int s21_shift_left_bigdec(s21_big_decimal *big_value);
// int s21_shift_right_bigdec(s21_big_decimal *big_value);
int s21_shift_left_bigdec_32(s21_big_decimal *big_value, int value);
// int s21_shift_right_bigdec_32(s21_big_decimal *big_value, int value);

// Вспомогательные функции для конвертации float
int s21_float_str_preparing_for_convert(float src, char *float_str,
                                        char *final_float_str);
int check_minimal_float_value(float src, char *float_str);
int check_maximum_float_value(float src, char *float_str);
void make_final_float_str(float src, char *float_str, char *final_float_str);
void negative(char *float_str, char *final_str);
void positive(char *float_str, char *final_str);
int len_to_point(char *float_str);
double decimal_to_double(s21_decimal src);
float decimal_to_float(s21_decimal src);

// Дополнительные вспомогательные функции
int s21_get_sign(s21_decimal value);
int s21_is_zero_dec(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
int s21_div_10(s21_decimal *func_struct);
s21_decimal s21_decimal_get_zero();
int s21_is_valid_decimal(s21_decimal dec);
int s21_sub_internal(s21_decimal value1, s21_decimal value2,
                     s21_decimal *result);

#endif
