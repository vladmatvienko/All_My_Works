#include <ctype.h>  // Функции классификации символов
#include <errno.h>  // Переменные и функции обработки ошибок
#include <regex.h>   // Регулярные выражения
#include <stdio.h>   // Стандартный ввод/вывод
#include <stdlib.h>  // Стандартные функции (память, преобразования)
#include <string.h>  // Функции работы со строками

/* Структура для хранения флагов */
typedef struct {
  int e_flag; /* Флаг -e: шаблон */
  int i_flag; /* Флаг -i: игнорирование регистра */
  int v_flag; /* Флаг -v: инвертирование поиска */
  int c_flag; /* Флаг -c: только количество строк */
  int l_flag; /* Флаг -l: только имена файлов */
  int n_flag; /* Флаг -n: номера строк */
  int h_flag; /* Флаг -h: без имен файлов */
  int s_flag; /* Флаг -s: подавление ошибок */
  int f_flag; /* Флаг -f: регулярные выражения из файла */
  int o_flag; /* Флаг -o: только совпадающие части */
} Flags;

/* Структура для хранения шаблонов */
typedef struct {
  char **patterns; /* Массив строк-шаблонов */
  int count;       /* Текущее количество шаблонов */
  int capacity;    /* Емкость массива шаблонов */
} Patterns;

/* Кастомная реализация strdup */
char *custom_strdup(const char *s) {
  if (s == NULL) return NULL;  // Проверка на NULL указатель
  size_t len = strlen(s) + 1;  // Вычисление длины строки + нулевой байт
  char *dup = malloc(len);  // Выделение памяти
  if (dup != NULL) {  // Проверка успешности выделения памяти
    memcpy(dup, s, len);  // Копирование строки в новую память
  }
  return dup;  // Возврат указателя на новую строку
}

/* Инициализация структуры флагов нулевыми значениями */
void init_flags(Flags *flags) {
  flags->e_flag = 0;  // Инициализация флага -e
  flags->i_flag = 0;  // Инициализация флага -i
  flags->v_flag = 0;  // Инициализация флага -v
  flags->c_flag = 0;  // Инициализация флага -c
  flags->l_flag = 0;  // Инициализация флага -l
  flags->n_flag = 0;  // Инициализация флага -n
  flags->h_flag = 0;  // Инициализация флага -h
  flags->s_flag = 0;  // Инициализация флага -s
  flags->f_flag = 0;  // Инициализация флага -f
  flags->o_flag = 0;  // Инициализация флага -o
}

/* Инициализация структуры шаблонов */
void init_patterns(Patterns *patterns) {
  patterns->patterns = NULL;  // Инициализация массива шаблонов
  patterns->count = 0;  // Инициализация счетчика шаблонов
  patterns->capacity = 0;  // Инициализация емкости массива
}

/* Добавление шаблона в структуру */
void add_pattern(Patterns *patterns, const char *pattern) {
  // Проверка необходимости расширения массива
  if (patterns->count >= patterns->capacity) {
    // Увеличение емкости в 2 раза или установка начального значения 10
    patterns->capacity = patterns->capacity == 0 ? 10 : patterns->capacity * 2;
    // Перевыделение памяти под массив указателей
    patterns->patterns =
        realloc(patterns->patterns, patterns->capacity * sizeof(char *));
    if (!patterns->patterns) {  // Проверка успешности выделения памяти
      fprintf(stderr, "Memory allocation error\n");
      exit(EXIT_FAILURE);  // Аварийное завершение при ошибке
    }
  }

  // Копирование шаблона в массив
  patterns->patterns[patterns->count] = custom_strdup(pattern);
  if (!patterns
           ->patterns[patterns->count]) {  // Проверка успешности копирования
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);  // Аварийное завершение при ошибке
  }
  patterns->count++;  // Увеличение счетчика шаблонов
}

/* Освобождение памяти, занятой шаблонами */
void free_patterns(Patterns *patterns) {
  // Освобождение памяти каждой строки-шаблона
  for (int i = 0; i < patterns->count; i++) {
    free(patterns->patterns[i]);  // Освобождение памяти под строку
  }
  free(patterns->patterns);  // Освобождение памяти под массив указателей
}

/* Кастомная реализация getline */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
  // Проверка валидности параметров
  if (lineptr == NULL || n == NULL || stream == NULL) {
    return -1;  // Возврат ошибки при невалидных параметрах
  }

  // Выделение начальной памяти при необходимости
  if (*lineptr == NULL) {
    *n = 128;               // Начальный размер буфера
    *lineptr = malloc(*n);  // Выделение памяти
    if (*lineptr == NULL) {
      return -1;  // Возврат ошибки при неудаче
    }
  }

  size_t pos = 0;  // Текущая позиция в буфере
  int c;           // Текущий символ

  // Чтение символов пока не EOF
  while ((c = fgetc(stream)) != EOF) {
    // Проверка необходимости расширения буфера
    if (pos + 1 >= *n) {
      size_t new_size = *n * 2;  // Удвоение размера буфера
      char *new_ptr = realloc(*lineptr, new_size);  // Перевыделение памяти
      if (new_ptr == NULL) {
        return -1;  // Возврат ошибки при неудаче
      }
      *lineptr = new_ptr;  // Обновление указателя
      *n = new_size;       // Обновление размера
    }

    (*lineptr)[pos++] = (char)c;  // Сохранение символа в буфер

    // Прерывание при достижении конца строки
    if (c == '\n') {
      break;
    }
  }

  // Проверка на пустой ввод
  if (pos == 0 && c == EOF) {
    return -1;  // Возврат ошибки при пустом вводе
  }

  (*lineptr)[pos] = '\0';  // Добавление нулевого терминатора
  return pos;  // Возврат количества прочитанных символов
}

/* Чтение шаблонов из файла */
int read_patterns_from_file(Patterns *patterns, const char *filename) {
  FILE *file = fopen(filename, "r");  // Открытие файла для чтения
  if (!file) {  // Проверка успешности открытия
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    return 1;  // Возврат ошибки
  }

  char *line = NULL;  // Буфер для строки
  size_t len = 0;     // Длина буфера
  ssize_t read;  // Количество прочитанных символов

  // Чтение файла построчно
  while ((read = custom_getline(&line, &len, file)) != -1) {
    // Удаление символа новой строки если присутствует
    if (read > 0 && line[read - 1] == '\n') {
      line[read - 1] = '\0';  // Замена \n на \0
    }
    // Добавление непустых строк как шаблонов
    if (strlen(line) > 0) {
      add_pattern(patterns, line);  // Добавление шаблона
    }
  }

  free(line);    // Освобождение буфера
  fclose(file);  // Закрытие файла
  return 0;      // Успешное завершение
}

/* Компиляция регулярного выражения с учетом флагов */
regex_t compile_regex(const char *pattern, int i_flag) {
  regex_t regex;  // Структура для скомпилированного regex
  int flags = REG_EXTENDED;  // Флаги компиляции
  if (i_flag) {  // Проверка флага игнорирования регистра
    flags |= REG_ICASE;  // Добавление флага игнорирования регистра
  }

  // Компиляция регулярного выражения
  int ret = regcomp(&regex, pattern, flags);
  if (ret != 0) {          // Проверка ошибок компиляции
    char error_msg[1024];  // Буфер для сообщения об ошибке
    regerror(ret, &regex, error_msg,
             sizeof(error_msg));  // Получение сообщения об ошибке
    fprintf(stderr, "Regex compilation error: %s\n", error_msg);
    exit(EXIT_FAILURE);  // Аварийное завершение при ошибке
  }

  return regex;  // Возврат скомпилированного regex
}

/* Обработка одного файла */
int process_file(const char *filename, Patterns *patterns, Flags *flags,
                 int multiple_files) {
  FILE *file;
  // Определение источника данных (файл или stdin)
  if (strcmp(filename, "-") == 0) {
    file = stdin;  // Использование стандартного ввода
  } else {
    file = fopen(filename, "r");  // Открытие файла для чтения
  }

  if (!file) {  // Проверка успешности открытия
    if (!flags->s_flag) {  // Проверка флага подавления ошибок
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    }
    return 2;  // Возврат кода ошибки
  }

  // Выделение памяти для массива скомпилированных regex
  regex_t *compiled_regexes = malloc(patterns->count * sizeof(regex_t));
  if (!compiled_regexes) {  // Проверка успешности выделения
    fprintf(stderr, "Memory allocation error\n");
    if (file != stdin) fclose(file);  // Закрытие файла если нужно
    return 2;                         // Возврат кода ошибки
  }

  // Компиляция всех шаблонов
  for (int i = 0; i < patterns->count; i++) {
    compiled_regexes[i] = compile_regex(patterns->patterns[i], flags->i_flag);
  }

  char *line = NULL;  // Буфер для строки
  size_t len = 0;     // Длина буфера
  ssize_t read;  // Количество прочитанных символов
  int line_number = 0;   // Номер текущей строки
  int match_count = 0;   // Счетчик совпадений
  int file_matched = 0;  // Флаг совпадения в файле

  // Чтение файла построчно
  while ((read = custom_getline(&line, &len, file)) != -1) {
    line_number++;  // Увеличение номера строки
    int matched = 0;  // Флаг совпадения для текущей строки

    // Проверка всех шаблонов для текущей строки
    for (int i = 0; i < patterns->count; i++) {
      int ret =
          regexec(&compiled_regexes[i], line, 0, NULL, 0);  // Выполнение поиска
      if (ret == 0) {  // Проверка совпадения
        matched = 1;   // Установка флага совпадения
        break;  // Прерывание цикла при первом совпадении
      } else if (ret != REG_NOMATCH) {  // Проверка ошибок выполнения
        char error_msg[1024];  // Буфер для сообщения об ошибке
        regerror(ret, &compiled_regexes[i], error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex match error: %s\n", error_msg);
      }
    }

    // Определение результата с учетом флага инверсии
    if ((matched && !flags->v_flag) || (!matched && flags->v_flag)) {
      match_count++;  // Увеличение счетчика совпадений

      // Обработка флага -l (только имена файлов)
      if (flags->l_flag) {
        file_matched = 1;  // Установка флага совпадения в файле
        break;  // Прерывание при первом совпадении
      }

      // Обработка обычного вывода (не -c и не -l)
      if (!flags->c_flag && !flags->l_flag) {
        // Вывод имени файла если нужно
        if (multiple_files && !flags->h_flag) {
          printf("%s:", filename);  // Вывод имени файла
        }

        // Вывод номера строки если нужно
        if (flags->n_flag) {
          printf("%d:", line_number);  // Вывод номера строки
        }

        // Обработка флага -o (только совпадающие части)
        if (flags->o_flag) {
          // Поиск всех вхождений всех шаблонов
          for (int i = 0; i < patterns->count; i++) {
            regmatch_t matches[1];  // Структура для информации о совпадении
            const char *ptr = line;  // Указатель на текущую позицию в строке

            // Поиск всех вхождений текущего шаблона
            while (regexec(&compiled_regexes[i], ptr, 1, matches, 0) == 0) {
              if (matches[0].rm_so == -1)
                break;  // Проверка валидности совпадения

              int start = matches[0].rm_so;  // Начальная позиция совпадения
              int end = matches[0].rm_eo;  // Конечная позиция совпадения

              // Вывод имени файла если нужно
              if (multiple_files && !flags->h_flag) {
                printf("%s:", filename);
              }
              // Вывод номера строки если нужно
              if (flags->n_flag) {
                printf("%d:", line_number);
              }

              // Вывод совпадающей части
              for (int j = start; j < end; j++) {
                putchar(ptr[j]);  // Посимвольный вывод
              }
              printf("\n");  // Перевод строки

              ptr += end;  // Перемещение указателя за совпадение
            }
          }
        } else {
          printf("%s", line);  // Вывод всей строки
          // Добавление перевода строки если его нет
          if (line[read - 1] != '\n') {
            printf("\n");
          }
        }
      }
    }
  }

  // Обработка флага -c (подсчет совпадений)
  if (flags->c_flag) {
    // Вывод имени файла если нужно
    if (multiple_files && !flags->h_flag) {
      printf("%s:", filename);
    }
    printf("%d\n", match_count);  // Вывод количества совпадений
  }

  // Обработка флага -l (только имена файлов с совпадениями)
  if (flags->l_flag && file_matched) {
    printf("%s\n", filename);  // Вывод имени файла
  }

  free(line);  // Освобождение буфера строки
  // Освобождение памяти скомпилированных regex
  for (int i = 0; i < patterns->count; i++) {
    regfree(&compiled_regexes[i]);  // Освобождение памяти regex
  }
  free(compiled_regexes);  // Освобождение массива regex
  if (file != stdin) fclose(file);  // Закрытие файла если нужно

  return match_count > 0 ? 0
                         : 1;  // Возврат 0 при совпадениях, 1 при отсутствии
}

/* Парсинг одиночных флагов */
int parse_single_flag(char flag, Flags *flags) {
  switch (flag) {
    case 'e':
      flags->e_flag = 1;
      break;  // Установка флага -e
    case 'i':
      flags->i_flag = 1;
      break;  // Установка флага -i
    case 'v':
      flags->v_flag = 1;
      break;  // Установка флага -v
    case 'c':
      flags->c_flag = 1;
      break;  // Установка флага -c
    case 'l':
      flags->l_flag = 1;
      break;  // Установка флага -l
    case 'n':
      flags->n_flag = 1;
      break;  // Установка флага -n
    case 'h':
      flags->h_flag = 1;
      break;  // Установка флага -h
    case 's':
      flags->s_flag = 1;
      break;  // Установка флага -s
    case 'f':
      flags->f_flag = 1;
      break;  // Установка флага -f
    case 'o':
      flags->o_flag = 1;
      break;  // Установка флага -o
    default:
      return 0;  // Неизвестный флаг
  }
  return 1;  // Успешное распознавание флага
}

/* Парсинг аргументов командной строки */
int parse_arguments(int argc, char *argv[], Flags *flags, Patterns *patterns,
                    char ***files, int *file_count) {
  int i = 1;  // Индекс текущего аргумента (пропускаем имя программы)
  *file_count = 0;  // Инициализация счетчика файлов
  *files = NULL;    // Инициализация массива файлов
  int error_occurred = 0;  // Флаг ошибки

  // Обработка всех аргументов
  while (i < argc) {
    if (argv[i][0] == '-') {    // Проверка на флаг
      if (argv[i][1] == '-') {  // Проверка на длинный флаг (не поддерживается)
        fprintf(stderr, "Unknown option: %s\n", argv[i]);
        return 2;                        // Возврат ошибки
      } else if (strlen(argv[i]) > 2) {  // Проверка на группу флагов (-abc)
        // Обработка каждого символа в группе флагов
        for (size_t j = 1; j < strlen(argv[i]); j++) {
          if (!parse_single_flag(argv[i][j], flags)) {  // Парсинг флага
            fprintf(stderr, "Unknown option: -%c\n", argv[i][j]);
            return 2;  // Возврат ошибки при неизвестном флаге
          }
        }
        i++;  // Переход к следующему аргументу
      } else {
        char flag = argv[i][1];  // Извлечение символа флага
        // Обработка флагов с параметрами (-e и -f)
        if (flag == 'e' || flag == 'f') {
          if (i + 1 < argc) {  // Проверка наличия аргумента
            if (flag == 'e') {
              add_pattern(patterns, argv[i + 1]);  // Добавление шаблона из -e
            } else {
              // Чтение шаблонов из файла для -f
              if (read_patterns_from_file(patterns, argv[i + 1]) != 0) {
                error_occurred = 2;  // Установка флага ошибки
              }
            }
            i += 2;  // Пропуск флага и его аргумента
          } else {
            fprintf(stderr, "Option -%c requires an argument\n", flag);
            return 2;  // Возврат ошибки при отсутствии аргумента
          }
        } else {
          // Обработка одиночных флагов без параметров
          if (!parse_single_flag(flag, flags)) {
            fprintf(stderr, "Unknown option: -%c\n", flag);
            return 2;  // Возврат ошибки при неизвестном флаге
          }
          i++;  // Переход к следующему аргументу
        }
      }
    } else {
      // Обработка аргумента-файла
      (*file_count)++;  // Увеличение счетчика файлов
      *files =
          realloc(*files, *file_count * sizeof(char *));  // Расширение массива
      if (!*files) {  // Проверка успешности выделения
        fprintf(stderr, "Memory allocation error\n");
        return 2;  // Возврат ошибки
      }
      (*files)[*file_count - 1] = argv[i];  // Сохранение имени файла
      i++;  // Переход к следующему аргументу
    }
  }

  // Извлечение шаблона из аргументов если не был указан флагами -e или -f
  if (patterns->count == 0 && *file_count > 0) {
    int pattern_found = 0;  // Флаг найденного шаблона
    // Поиск первого не-флагового аргумента как шаблона
    for (int j = 0; j < *file_count; j++) {
      if ((*files)[j][0] != '-') {  // Проверка что это не флаг
        add_pattern(patterns, (*files)[j]);  // Добавление как шаблона
        // Сдвиг оставшихся файлов в массиве
        for (int k = j; k < *file_count - 1; k++) {
          (*files)[k] = (*files)[k + 1];
        }
        (*file_count)--;  // Уменьшение счетчика файлов
        pattern_found = 1;  // Установка флага найденного шаблона
        break;  // Прерывание после первого шаблона
      }
    }
    if (!pattern_found) {  // Проверка найден ли шаблон
      fprintf(stderr, "No pattern specified\n");
      return 2;  // Возврат ошибки
    }
  }

  // Проверка что хотя бы один шаблон указан
  if (patterns->count == 0) {
    fprintf(stderr, "No pattern specified\n");
    return 2;  // Возврат ошибки
  }

  return error_occurred;  // Возврат результата парсинга
}

/* Основная функция */
int main(int argc, char *argv[]) {
  // Проверка минимального количества аргументов
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [options] pattern [file...]\n", argv[0]);
    return 2;  // Возврат ошибки использования
  }

  Flags flags;          // Структура флагов
  Patterns patterns;    // Структура шаблонов
  char **files = NULL;  // Массив имен файлов
  int file_count = 0;   // Количество файлов

  init_flags(&flags);        // Инициализация флагов
  init_patterns(&patterns);  // Инициализация шаблонов

  // Парсинг аргументов командной строки
  int parse_result =
      parse_arguments(argc, argv, &flags, &patterns, &files, &file_count);
  if (parse_result != 0) {  // Проверка ошибок парсинга
    free_patterns(&patterns);  // Освобождение памяти шаблонов
    free(files);          // Освобождение памяти файлов
    return parse_result;  // Возврат кода ошибки
  }

  int multiple_files = (file_count > 1);  // Определение множественности файлов
  int any_matches = 0;  // Флаг наличия хотя бы одного совпадения
  int exit_code = 0;  // Код возврата программы

  // Обработка случая когда файлы не указаны (чтение из stdin)
  if (file_count == 0) {
    int result = process_file("-", &patterns, &flags,
                              multiple_files);  // Обработка stdin
    any_matches = (result == 0);  // Установка флага совпадений
    exit_code = result;  // Сохранение кода возврата
  } else {
    // Обработка всех указанных файлов
    for (int i = 0; i < file_count; i++) {
      int result = process_file(files[i], &patterns, &flags,
                                multiple_files);  // Обработка файла
      if (result == 0) {  // Проверка совпадений
        any_matches = 1;  // Установка флага совпадений
      }
      if (result == 2 && exit_code == 0) {  // Проверка ошибок файловой системы
        exit_code = 2;  // Сохранение кода ошибки
      }
    }
  }

  free_patterns(&patterns);  // Освобождение памяти шаблонов
  free(files);  // Освобождение памяти файлов

  if (exit_code == 2) {  // Проверка ошибок файловой системы
    return 2;            // Возврат кода ошибки
  }
  return any_matches ? 0 : 1;  // Возврат 0 при совпадениях, 1 при отсутствии
}