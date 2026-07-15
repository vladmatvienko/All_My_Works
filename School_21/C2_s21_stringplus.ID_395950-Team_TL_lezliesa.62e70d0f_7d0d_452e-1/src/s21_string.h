// s21_string.h - Заголовочный файл для библиотеки s21_string

#ifndef S21_STRING_H
#define S21_STRING_H

// Определение типа s21_size_t как аналог size_t
typedef unsigned long s21_size_t;

// Макрос NULL как аналог S21_NULL
#define S21_NULL ((void *)0)

// Объявление функций библиотеки
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

#endif