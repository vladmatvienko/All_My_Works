#include "s21_decimal.h"

#include "s21_decimal_test.h"

// Вспомогательная функция для создания s21_decimal в тестах
s21_decimal create_decimal(int low, int mid, int high, int sign, int scale) {
  s21_decimal result = {
      {(unsigned int)low, (unsigned int)mid, (unsigned int)high, 0}};
  if (sign) s21_set_sign(&result, 1);
  if (scale >= 0 && scale <= 28) s21_setscale(&result, scale);
  return result;
}

int compare_abs(s21_decimal value_1, s21_decimal value_2, int *result) {
  s21_big_decimal big_val1 = {0};
  s21_big_decimal big_val2 = {0};

  s21_leveling_scale(value_1, value_2, &big_val1, &big_val2);

  int cmp_result = s21_compare_mantisa(big_val1, big_val2);

  *result = cmp_result;

  // Возвращаем 1 если числа равны, 0 если разные (соответствует оригинальной
  // сигнатуре)
  return (cmp_result == 0) ? 1 : 0;
}

// Функция для запуска и отчета о тестах
int run_and_report(Suite *suite) {
  printf("\n");
  SRunner *sr = srunner_create(suite);
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed;
}

// main для запуска всех тестов
int main(void) {
  int failed = 0;
  failed += run_and_report(suite_support_functions());
  failed += run_and_report(suite_create_arithmetic());
  failed += run_and_report(suite_create_compare());
  failed += run_and_report(suite_create_conversion());
  failed += run_and_report(suite_create_other());

  if (failed == 0) {
    printf("\n\033[1;32mAll tests passed successfully!\033[0m\n\n");
  } else {
    printf("\033[1;31mSome tests failed. Total failures: %d\033[0m\n\n",
           failed);
  }
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
