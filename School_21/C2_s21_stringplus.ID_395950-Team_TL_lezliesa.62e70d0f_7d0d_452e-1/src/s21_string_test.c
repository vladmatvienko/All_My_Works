// s21_string_test.c - Unit-тесты для библиотеки s21_string

#include <check.h>
#include <stdlib.h>
#include <string.h>

// Подключаем заголовочный файл нашей библиотеки
#include "s21_string.h"

// Тесты для s21_strcspn
START_TEST(test_strcspn_basic) {
  // Определяем тестовые строки: основная строка и строка разделителей
  const char *str1 = "hello world";
  const char *str2 = " ";

  // Вызываем нашу реализацию функции strcspn
  s21_size_t result = s21_strcspn(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  size_t expected = strcspn(str1, str2);

  // Проверяем, что результаты совпадают
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_strcspn_no_match) {
  // Определяем тестовые строки без совпадений
  const char *str1 = "hello";
  const char *str2 = "xyz";

  // Вызываем нашу реализацию функции strcspn
  s21_size_t result = s21_strcspn(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  size_t expected = strcspn(str1, str2);

  // Проверяем, что результаты совпадают
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_strcspn_empty_str1) {
  // Первая строка пустая, вторая содержит символы
  const char *str1 = "";
  const char *str2 = "abc";

  // Вызываем нашу реализацию функции strcspn
  s21_size_t result = s21_strcspn(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  size_t expected = strcspn(str1, str2);

  // Проверяем, что результаты совпадают (должно быть 0)
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_strcspn_empty_str2) {
  // Первая строка содержит символы, вторая пустая
  const char *str1 = "hello";
  const char *str2 = "";

  // Вызываем нашу реализацию функции strcspn
  s21_size_t result = s21_strcspn(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  size_t expected = strcspn(str1, str2);

  // Проверяем, что результаты совпадают (вся строка подходит)
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_strcspn_first_char_match) {
  // Первый символ первой строки совпадает с разделителем
  const char *str1 = "abc";
  const char *str2 = "a";

  // Вызываем нашу реализацию функции strcspn
  s21_size_t result = s21_strcspn(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  size_t expected = strcspn(str1, str2);

  // Проверяем, что результаты совпадают (должно быть 0)
  ck_assert_uint_eq(result, expected);
}
END_TEST

START_TEST(test_strcspn_multiple_chars) {
  // Строка с несколькими возможными разделителями
  const char *str1 = "hello world";
  const char *str2 = "ol";

  // Вызываем нашу реализацию функции strcspn
  s21_size_t result = s21_strcspn(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  size_t expected = strcspn(str1, str2);

  // Проверяем, что результаты совпадают
  ck_assert_uint_eq(result, expected);
}
END_TEST

// Тесты для s21_strerror
START_TEST(test_strerror_valid_codes) {
  // Массив тестовых кодов ошибок
  int test_codes[] = {0, 1, 2, 13, 22, 35};
  // Вычисляем количество тестов в массиве
  int num_tests = sizeof(test_codes) / sizeof(test_codes[0]);

  // Проходим по всем тестовым кодам
  for (int i = 0; i < num_tests; i++) {
    // Вызываем нашу реализацию функции strerror
    char *result = s21_strerror(test_codes[i]);
    // Вызываем стандартную реализацию для сравнения
    char *expected = strerror(test_codes[i]);

    // Проверяем, что обе функции вернули ненулевые указатели
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(expected);
  }
}
END_TEST

START_TEST(test_strerror_invalid_codes) {
  // Тестируем отрицательный код ошибки
  char *result1 = s21_strerror(-1);
  // Тестируем слишком большой код ошибки
  char *result2 = s21_strerror(1000);

  // Проверяем, что функция вернула ненулевые указатели
  ck_assert_ptr_nonnull(result1);
  ck_assert_ptr_nonnull(result2);
}
END_TEST

START_TEST(test_strerror_zero) {
  // Тестируем нулевой код ошибки
  char *result = s21_strerror(0);
  // Получаем стандартное сообщение об ошибке
  char *expected = strerror(0);

  // Проверяем, что обе функции вернули ненулевые указатели
  ck_assert_ptr_nonnull(result);
  ck_assert_ptr_nonnull(expected);
}
END_TEST

// Тесты для s21_strpbrk
START_TEST(test_strpbrk_basic) {
  // Определяем тестовые строки
  const char *str1 = "hello world";
  const char *str2 = "ow";

  // Вызываем нашу реализацию функции strpbrk
  char *result = s21_strpbrk(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strpbrk(str1, str2);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strpbrk_no_match) {
  // Определяем тестовые строки без совпадений
  const char *str1 = "hello";
  const char *str2 = "xyz";

  // Вызываем нашу реализацию функции strpbrk
  char *result = s21_strpbrk(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strpbrk(str1, str2);

  // Проверяем, что указатели совпадают (должны быть NULL)
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strpbrk_empty_str1) {
  // Первая строка пустая
  const char *str1 = "";
  const char *str2 = "abc";

  // Вызываем нашу реализацию функции strpbrk
  char *result = s21_strpbrk(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strpbrk(str1, str2);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strpbrk_empty_str2) {
  // Вторая строка пустая
  const char *str1 = "hello";
  const char *str2 = "";

  // Вызываем нашу реализацию функции strpbrk
  char *result = s21_strpbrk(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strpbrk(str1, str2);

  // Проверяем, что указатели совпадают (должны быть NULL)
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strpbrk_first_char) {
  // Ищем первый символ строки
  const char *str1 = "abc";
  const char *str2 = "a";

  // Вызываем нашу реализацию функции strpbrk
  char *result = s21_strpbrk(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strpbrk(str1, str2);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strpbrk_last_char) {
  // Ищем последний символ строки
  const char *str1 = "hello";
  const char *str2 = "o";

  // Вызываем нашу реализацию функции strpbrk
  char *result = s21_strpbrk(str1, str2);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strpbrk(str1, str2);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Тесты для s21_strrchr
START_TEST(test_strrchr_basic) {
  // Определяем тестовую строку и искомый символ
  const char *str = "hello world";
  int c = 'o';

  // Вызываем нашу реализацию функции strrchr
  char *result = s21_strrchr(str, c);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strrchr(str, c);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  // Ищем символ, которого нет в строке
  const char *str = "hello";
  int c = 'x';

  // Вызываем нашу реализацию функции strrchr
  char *result = s21_strrchr(str, c);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strrchr(str, c);

  // Проверяем, что указатели совпадают (должны быть NULL)
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_empty_string) {
  // Ищем символ в пустой строке
  const char *str = "";
  int c = 'a';

  // Вызываем нашу реализацию функции strrchr
  char *result = s21_strrchr(str, c);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strrchr(str, c);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_null_char) {
  // Ищем нулевой символ (конец строки)
  const char *str = "hello";
  int c = '\0';

  // Вызываем нашу реализацию функции strrchr
  char *result = s21_strrchr(str, c);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strrchr(str, c);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_first_char) {
  // Ищем первый символ в строке с повторениями
  const char *str = "abcabc";
  int c = 'a';

  // Вызываем нашу реализацию функции strrchr
  char *result = s21_strrchr(str, c);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strrchr(str, c);

  // Проверяем, что указатели совпадают (должен найти последнее 'a')
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strrchr_multiple_occurrences) {
  // Ищем символ с несколькими вхождениями
  const char *str = "hello world hello";
  int c = 'l';

  // Вызываем нашу реализацию функции strrchr
  char *result = s21_strrchr(str, c);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strrchr(str, c);

  // Проверяем, что указатели совпадают (должен найти последнее 'l')
  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Тесты для s21_strstr
START_TEST(test_strstr_basic) {
  // Определяем строки для поиска подстроки
  const char *haystack = "hello world";
  const char *needle = "world";

  // Вызываем нашу реализацию функции strstr
  char *result = s21_strstr(haystack, needle);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strstr(haystack, needle);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_not_found) {
  // Ищем подстроку, которой нет в основной строке
  const char *haystack = "hello";
  const char *needle = "xyz";

  // Вызываем нашу реализацию функции strstr
  char *result = s21_strstr(haystack, needle);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strstr(haystack, needle);

  // Проверяем, что указатели совпадают (должны быть NULL)
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  // Ищем пустую подстроку
  const char *haystack = "hello";
  const char *needle = "";

  // Вызываем нашу реализацию функции strstr
  char *result = s21_strstr(haystack, needle);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strstr(haystack, needle);

  // Проверяем, что указатели совпадают (должна вернуть haystack)
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  // Ищем подстроку в пустой строке
  const char *haystack = "";
  const char *needle = "hello";

  // Вызываем нашу реализацию функции strstr
  char *result = s21_strstr(haystack, needle);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strstr(haystack, needle);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_both_empty) {
  // Ищем пустую подстроку в пустой строке
  const char *haystack = "";
  const char *needle = "";

  // Вызываем нашу реализацию функции strstr
  char *result = s21_strstr(haystack, needle);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strstr(haystack, needle);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_full_match) {
  // Ищем строку в самой себе
  const char *haystack = "hello";
  const char *needle = "hello";

  // Вызываем нашу реализацию функции strstr
  char *result = s21_strstr(haystack, needle);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strstr(haystack, needle);

  // Проверяем, что указатели совпадают
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_overlapping) {
  // Ищем подстроку в строке с перекрытием
  const char *haystack = "ababa";
  const char *needle = "aba";

  // Вызываем нашу реализацию функции strstr
  char *result = s21_strstr(haystack, needle);
  // Вызываем стандартную реализацию для сравнения
  char *expected = strstr(haystack, needle);

  // Проверяем, что указатели совпадают (должна найти первое вхождение)
  ck_assert_ptr_eq(result, expected);
}
END_TEST

// Тесты для s21_strtok
START_TEST(test_strtok_basic) {
  // Создаем две идентичные строки для тестирования
  // Используем массивы char[], а не указатели const char*, чтобы можно было
  // модифицировать
  char str1[] = "hello,world,test";
  char str2[] = "hello,world,test";
  // Определяем разделитель
  const char *delim = ",";

  // Вызываем нашу реализацию функции для первого токена
  char *result1 = s21_strtok(str1, delim);
  // Вызываем стандартную реализацию для сравнения
  char *expected1 = strtok(str2, delim);

  // Проверяем, что первый токен совпадает
  ck_assert_str_eq(result1, expected1);

  // Вызываем обе функции для второго токена (с NULL)
  result1 = s21_strtok(((void *)0), delim);
  expected1 = strtok(((void *)0), delim);

  // Проверяем, что второй токен совпадает
  ck_assert_str_eq(result1, expected1);

  // Вызываем обе функции для третьего токена
  result1 = s21_strtok(((void *)0), delim);
  expected1 = strtok(((void *)0), delim);

  // Проверяем, что третий токен совпадает
  ck_assert_str_eq(result1, expected1);
}
END_TEST

START_TEST(test_strtok_multiple_delimiters) {
  // Создаем строки с разными типами разделителей
  char str1[] = "hello, world; test";
  char str2[] = "hello, world; test";
  // Определяем несколько разделителей
  const char *delim = ", ;";

  // Вызываем нашу реализацию функции
  char *result1 = s21_strtok(str1, delim);
  // Вызываем стандартную реализацию для сравнения
  char *expected1 = strtok(str2, delim);

  // Проверяем, что первый токен совпадает
  ck_assert_str_eq(result1, expected1);
}
END_TEST

START_TEST(test_strtok_no_delimiters) {
  // Создаем строку без разделителей
  char str1[] = "helloworld";
  char str2[] = "helloworld";
  // Определяем разделитель, которого нет в строке
  const char *delim = ",";

  // Вызываем нашу реализацию функции
  char *result1 = s21_strtok(str1, delim);
  // Вызываем стандартную реализацию для сравнения
  char *expected1 = strtok(str2, delim);

  // Проверяем, что токен совпадает (вся строка является токеном)
  ck_assert_str_eq(result1, expected1);

  // Проверяем, что следующий вызов возвращает NULL
  result1 = s21_strtok(((void *)0), delim);
  expected1 = strtok(((void *)0), delim);

  // Проверяем, что оба возвращают NULL
  ck_assert_ptr_eq(result1, expected1);
}
END_TEST

START_TEST(test_strtok_only_delimiters) {
  // Создаем строку только из разделителей
  char str1[] = ",,,";
  char str2[] = ",,,";
  // Определяем разделитель
  const char *delim = ",";

  // Вызываем нашу реализацию функции
  char *result1 = s21_strtok(str1, delim);
  // Вызываем стандартную реализацию для сравнения
  char *expected1 = strtok(str2, delim);

  // Проверяем, что обе функции возвращают NULL
  ck_assert_ptr_eq(result1, expected1);
}
END_TEST

START_TEST(test_strtok_empty_string) {
  // Создаем пустую строку
  char str1[] = "";
  char str2[] = "";
  // Определяем разделитель
  const char *delim = ",";

  // Вызываем нашу реализацию функции
  char *result1 = s21_strtok(str1, delim);
  // Вызываем стандартную реализацию для сравнения
  char *expected1 = strtok(str2, delim);

  // Проверяем, что обе функции возвращают NULL
  ck_assert_ptr_eq(result1, expected1);
}
END_TEST

START_TEST(test_strtok_consecutive_calls) {
  // Создаем строку с несколькими токенами
  char str1[] = "one,two,three,four";
  char str2[] = "one,two,three,four";
  // Определяем разделитель
  const char *delim = ",";

  // Массивы для хранения токенов
  char *tokens1[4];
  char *tokens2[4];

  // Получаем первый токен из обеих реализаций
  tokens1[0] = s21_strtok(str1, delim);
  tokens2[0] = strtok(str2, delim);

  // Получаем остальные токены через последовательные вызовы
  for (int i = 1; i < 4; i++) {
    tokens1[i] = s21_strtok(((void *)0), delim);
    tokens2[i] = strtok(((void *)0), delim);
  }

  // Сравниваем все полученные токены
  for (int i = 0; i < 4; i++) {
    // Если оба токена NULL, продолжаем
    if (tokens1[i] == ((void *)0) && tokens2[i] == NULL) {
      continue;
    }
    // Проверяем, что токены совпадают
    ck_assert_str_eq(tokens1[i], tokens2[i]);
  }
}
END_TEST

// Создание тестовой suite
Suite *string_suite(void) {
  // Объявляем указатели на suite и test case
  Suite *s;
  TCase *tc_core;

  // Создаем новую тестовую suite с именем "String"
  s = suite_create("String");

  // Тесты для strcspn
  tc_core = tcase_create("strcspn");
  tcase_add_test(tc_core, test_strcspn_basic);
  tcase_add_test(tc_core, test_strcspn_no_match);
  tcase_add_test(tc_core, test_strcspn_empty_str1);
  tcase_add_test(tc_core, test_strcspn_empty_str2);
  tcase_add_test(tc_core, test_strcspn_first_char_match);
  tcase_add_test(tc_core, test_strcspn_multiple_chars);
  suite_add_tcase(s, tc_core);

  // Тесты для strerror
  tc_core = tcase_create("strerror");
  tcase_add_test(tc_core, test_strerror_valid_codes);
  tcase_add_test(tc_core, test_strerror_invalid_codes);
  tcase_add_test(tc_core, test_strerror_zero);
  suite_add_tcase(s, tc_core);

  // Тесты для strpbrk
  tc_core = tcase_create("strpbrk");
  tcase_add_test(tc_core, test_strpbrk_basic);
  tcase_add_test(tc_core, test_strpbrk_no_match);
  tcase_add_test(tc_core, test_strpbrk_empty_str1);
  tcase_add_test(tc_core, test_strpbrk_empty_str2);
  tcase_add_test(tc_core, test_strpbrk_first_char);
  tcase_add_test(tc_core, test_strpbrk_last_char);
  suite_add_tcase(s, tc_core);

  // Тесты для strrchr
  tc_core = tcase_create("strrchr");
  tcase_add_test(tc_core, test_strrchr_basic);
  tcase_add_test(tc_core, test_strrchr_not_found);
  tcase_add_test(tc_core, test_strrchr_empty_string);
  tcase_add_test(tc_core, test_strrchr_null_char);
  tcase_add_test(tc_core, test_strrchr_first_char);
  tcase_add_test(tc_core, test_strrchr_multiple_occurrences);
  suite_add_tcase(s, tc_core);

  // Тесты для strstr
  tc_core = tcase_create("strstr");
  tcase_add_test(tc_core, test_strstr_basic);
  tcase_add_test(tc_core, test_strstr_not_found);
  tcase_add_test(tc_core, test_strstr_empty_needle);
  tcase_add_test(tc_core, test_strstr_empty_haystack);
  tcase_add_test(tc_core, test_strstr_both_empty);
  tcase_add_test(tc_core, test_strstr_full_match);
  tcase_add_test(tc_core, test_strstr_overlapping);
  suite_add_tcase(s, tc_core);

  // Тесты для strtok
  tc_core = tcase_create("strtok");
  tcase_add_test(tc_core, test_strtok_basic);
  tcase_add_test(tc_core, test_strtok_multiple_delimiters);
  tcase_add_test(tc_core, test_strtok_no_delimiters);
  tcase_add_test(tc_core, test_strtok_only_delimiters);
  tcase_add_test(tc_core, test_strtok_empty_string);
  tcase_add_test(tc_core, test_strtok_consecutive_calls);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  // Объявляем переменную для подсчета проваленных тестов
  int number_failed;
  // Объявляем указатели на suite и srunner
  Suite *s;
  SRunner *sr;

  // Создаем тестовую suite
  s = string_suite();
  // Создаем srunner для запуска тестов
  sr = srunner_create(s);

  // Запускаем все тесты в нормальном режиме
  srunner_run_all(sr, CK_NORMAL);
  // Получаем количество проваленных тестов
  number_failed = srunner_ntests_failed(sr);
  // Освобождаем память, занятую srunner
  srunner_free(sr);

  // Возвращаем 0, если все тесты прошли успешно, и 1, если были проваленные
  // тесты
  return (number_failed == 0) ? 0 : 1;
}