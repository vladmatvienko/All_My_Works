#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

// Общие структуры
typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

// Вспомогательные функции
#include "s21_support.h"

// Базовые модули
#include "s21_arithmetic.h"
#include "s21_comparison.h"
#include "s21_convertor.h"
#include "s21_other.h"

// Необходимые для корректной работы вспомогательных
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Общие константы
#define S21_ERROR -1

#endif