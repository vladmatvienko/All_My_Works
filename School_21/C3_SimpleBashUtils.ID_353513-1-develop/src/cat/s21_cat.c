#include <stdio.h>  // Стандартный ввод/вывод
#include <stdlib.h>  // Стандартные функции (exit, malloc, free)
#include <string.h>  // Функции для работы со строками

// Структура для хранения флагов программы
typedef struct {
  int number_nonblank;  // Флаг -b: нумерует только непустые строки
  int show_ends;  // Флаг -e: показывает символы конца строки как $
  int number;     // Флаг -n: нумерует все строки
  int squeeze_blank;  // Флаг -s: сжимает несколько пустых строк в одну
  int show_tabs;      // Флаг -t: показывает табы как ^I
  int show_nonprinting;  // Общий флаг для отображения непечатаемых символов
} Flags;

// Инициализация всех флагов нулевыми значениями
void init_flags(Flags *flags) {
  flags->number_nonblank = 0;  // Выключить нумерацию непустых строк
  flags->show_ends = 0;  // Выключить отображение конца строк
  flags->number = 0;  // Выключить нумерацию всех строк
  flags->squeeze_blank = 0;  // Выключить сжатие пустых строк
  flags->show_tabs = 0;  // Выключить отображение табов
  flags->show_nonprinting = 0;  // Выключить отображение непечатаемых символов
}

// Парсинг одного флага из аргумента командной строки
int parse_single_flag(char *arg, Flags *flags) {
  // Проверка флага -b или --number-nonblank
  if (strcmp(arg, "-b") == 0 || strcmp(arg, "--number-nonblank") == 0) {
    flags->number_nonblank = 1;  // Включить нумерацию непустых строк
    return 1;  // Успешное распознавание флага
  }
  // Проверка флага -e (эквивалент -vE)
  else if (strcmp(arg, "-e") == 0) {
    flags->show_ends = 1;  // Включить отображение конца строк
    flags->show_nonprinting = 1;  // Включить отображение непечатаемых символов
    return 1;
  }
  // Проверка флага -E или --show-ends
  else if (strcmp(arg, "-E") == 0) {
    flags->show_ends = 1;  // Включить только отображение конца строк
    return 1;
  }
  // Проверка флага -n или --number
  else if (strcmp(arg, "-n") == 0 || strcmp(arg, "--number") == 0) {
    flags->number = 1;  // Включить нумерацию всех строк
    return 1;
  }
  // Проверка флага -s или --squeeze-blank
  else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--squeeze-blank") == 0) {
    flags->squeeze_blank = 1;  // Включить сжатие пустых строк
    return 1;
  }
  // Проверка флага -t (эквивалент -vT)
  else if (strcmp(arg, "-t") == 0) {
    flags->show_tabs = 1;  // Включить отображение табов
    flags->show_nonprinting = 1;  // Включить отображение непечатаемых символов
    return 1;
  }
  // Проверка флага -T или --show-tabs
  else if (strcmp(arg, "-T") == 0) {
    flags->show_tabs = 1;  // Включить только отображение табов
    return 1;
  }
  // Проверка флага --help
  else if (strcmp(arg, "--help") == 0) {
    // Вывод справки по использованию программы
    printf(
        "Usage: s21_cat [OPTION]... [FILE]...\n"
        "Concatenate FILE(s) to standard output.\n\n"
        "  -b, --number-nonblank    number nonempty output lines\n"
        "  -e                       equivalent to -vE\n"
        "  -E, --show-ends          display $ at end of each line\n"
        "  -n, --number             number all output lines\n"
        "  -s, --squeeze-blank      suppress repeated empty output lines\n"
        "  -t                       equivalent to -vT\n"
        "  -T, --show-tabs          display TAB characters as ^I\n");
    exit(0);  // Завершение программы после вывода справки
  }
  return 0;  // Флаг не распознан
}

// Парсинг комбинированных флагов (например, -ben)
int parse_combined_flags(char *arg, Flags *flags) {
  // Проверка, что это флаг (начинается с '-') и не одиночный '-'
  if (arg[0] != '-' || arg[1] == '\0') {
    return 0;  // Не комбинированный флаг
  }

  int parsed = 0;  // Флаг успешного парсинга
  // Перебор всех символов после '-'
  for (int i = 1; arg[i] != '\0'; i++) {
    char flag_str[3] = "-x";  // Создание строки для одиночного флага
    flag_str[1] = arg[i];  // Установка символа флага

    // Парсинг одиночного флага
    if (parse_single_flag(flag_str, flags)) {
      parsed = 1;  // Успешно распознан хотя бы один флаг
    } else {
      return 0;  // Неизвестный флаг, прекращаем обработку
    }
  }
  return parsed;  // Возврат результата парсинга
}

// Парсинг всех аргументов командной строки
int parse_args(int argc, char *argv[], Flags *flags) {
  int file_index = 1;  // Индекс первого потенциального файла

  // Перебор всех аргументов командной строки
  for (int i = 1; i < argc; i++) {
    // Проверка, является ли аргумент флагом (начинается с '-')
    if (argv[i][0] == '-') {
      // Попытка парсинга как комбинированных флагов
      if (!parse_combined_flags(argv[i], flags)) {
        // Если не комбинированные, пробуем как одиночные
        if (!parse_single_flag(argv[i], flags)) {
          // Вывод сообщения об ошибке для неизвестного флага
          fprintf(stderr, "s21_cat: invalid option -- '%s'\n", argv[i] + 1);
          return -1;  // Возврат ошибки
        }
      }
      file_index = i + 1;  // Обновление индекса первого файла
    } else {
      break;  // Достигли первого файла, прекращаем обработку флагов
    }
  }

  return file_index;  // Возврат индекса первого файла
}

// Обработка одного файла с применением установленных флагов
void process_file(FILE *file, Flags flags) {
  int ch;              // Текущий читаемый символ
  int line_num = 1;    // Номер текущей строки
  int prev_ch = '\n';  // Предыдущий символ (для определения начала строки)
  int squeeze = 0;     // Флаг сжатия пустых строк

  // Обработка приоритета флагов: -b имеет приоритет над -n
  if (flags.number_nonblank) {
    flags.number =
        0;  // Отключаем нумерацию всех строк если включена нумерация непустых
  }

  // Чтение файла посимвольно до конца файла (EOF)
  while ((ch = fgetc(file)) != EOF) {
    // Обработка флага -s: сжатие пустых строк
    if (flags.squeeze_blank) {
      // Если текущий и предыдущий символы - переводы строк
      if (ch == '\n' && prev_ch == '\n') {
        if (squeeze) continue;  // Пропускаем повторяющиеся пустые строки
        squeeze = 1;  // Устанавливаем флаг сжатия
      } else {
        squeeze = 0;  // Сбрасываем флаг сжатия
      }
    }

    // Обработка нумерации строк: в начале новой строки
    if (prev_ch == '\n') {
      // Если включена нумерация всех строк ИЛИ нумерация только непустых и
      // текущая строка не пустая
      if (flags.number || (flags.number_nonblank && ch != '\n')) {
        printf("%6d\t", line_num++);  // Вывод номера строки с форматированием
      }
    }

    // Обработка флага -t: отображение табов
    if (flags.show_tabs && ch == '\t') {
      printf("^I");  // Замена таба на ^I
      prev_ch = ch;  // Сохранение текущего символа как предыдущего
      continue;      // Переход к следующему символу
    }

    // Обработка флага -e: отображение символов конца строки
    if (flags.show_ends && ch == '\n') {
      printf("$");  // Добавление $ перед переводом строки
    }

    // Обработка непечатаемых символов для флагов -e и -t
    if (flags.show_nonprinting) {
      // Обработка управляющих символов (кроме таба, перевода строки и возврата
      // каретки)
      if (ch >= 0 && ch < 32 && ch != '\t' && ch != '\n' && ch != '\r') {
        printf("^%c", ch + 64);  // Преобразование в ^X формат
        prev_ch = ch;  // Сохранение текущего символа
        continue;      // Переход к следующему символу
      }
      // Обработка символа DELETE (127)
      else if (ch == 127) {
        printf("^?");  // Отображение как ^?
        prev_ch = ch;  // Сохранение текущего символа
        continue;      // Переход к следующему символу
      }
    }

    // Вывод текущего символа без изменений
    putchar(ch);
    prev_ch = ch;  // Сохранение текущего символа для следующей итерации
  }
}

// Главная функция программы
int main(int argc, char *argv[]) {
  Flags flags;  // Создание структуры для флагов
  init_flags(&flags);  // Инициализация флагов

  // Если нет аргументов командной строки
  if (argc == 1) {
    process_file(stdin, flags);  // Обработка стандартного ввода
    return 0;                    // Успешное завершение
  }

  // Парсинг аргументов командной строки
  int file_index = parse_args(argc, argv, &flags);
  if (file_index == -1) {
    return 1;  // Завершение с ошибкой
  }

  // Обработка каждого файла
  int files_processed = 0;  // Счетчик обработанных файлов
  for (int i = file_index; i < argc; i++) {
    // Проверка, является ли аргумент stdin (символ '-')
    if (strcmp(argv[i], "-") == 0) {
      process_file(stdin, flags);  // Обработка стандартного ввода
      files_processed++;  // Увеличение счетчика
    } else {
      // Открытие файла для чтения
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        // Вывод сообщения об ошибке если файл не найден
        fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
        continue;  // Переход к следующему файлу
      }
      process_file(file, flags);  // Обработка файла
      fclose(file);               // Закрытие файла
      files_processed++;          // Увеличение счетчика
    }
  }

  // Если не было обработано ни одного файла, читаем из stdin
  if (files_processed == 0) {
    process_file(stdin, flags);  // Обработка стандартного ввода
  }

  return 0;  // Успешное завершение программы
}