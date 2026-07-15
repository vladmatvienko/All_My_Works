// s21_string.c - Реализация функций библиотеки string.h
// Стандарт C11, структурное программирование

#include "s21_string.h"

#include <stdio.h>   // Для snprintf (в strerror)
#include <stdlib.h>  // Для malloc/free (в strerror)

// Объявление вспомогательной функции
static char *s21_strchr_local(const char *str, int c);

// Макросы для сообщений об ошибках в зависимости от операционной системы
#ifdef __APPLE__
#define ERR_COUNT 106
static const char *error_messages[ERR_COUNT] = {
    "Undefined error: 0",                               // 0
    "Operation not permitted",                          // 1
    "No such file or directory",                        // 2
    "No such process",                                  // 3
    "Interrupted system call",                          // 4
    "Input/output error",                               // 5
    "Device not configured",                            // 6
    "Argument list too long",                           // 7
    "Exec format error",                                // 8
    "Bad file descriptor",                              // 9
    "No child processes",                               // 10
    "Resource deadlock avoided",                        // 11
    "Cannot allocate memory",                           // 12
    "Permission denied",                                // 13
    "Bad address",                                      // 14
    "Block device required",                            // 15
    "Device / Resource busy",                           // 16
    "File exists",                                      // 17
    "Cross-device link",                                // 18
    "Operation not supported by device",                // 19
    "Not a directory",                                  // 20
    "Is a directory",                                   // 21
    "Invalid argument",                                 // 22
    "Too many open files in system",                    // 23
    "Too many open files",                              // 24
    "Inappropriate ioctl for device",                   // 25
    "Text file busy",                                   // 26
    "File too large",                                   // 27
    "No space left on device",                          // 28
    "Illegal seek",                                     // 29
    "Read-only file system",                            // 30
    "Too many links",                                   // 31
    "Broken pipe",                                      // 32
    "Numerical argument out of domain",                 // 33
    "Result too large",                                 // 34
    "Resource temporarily unavailable",                 // 35
    "Operation now in progress",                        // 36
    "Operation already in progress",                    // 37
    "Socket operation on non-socket",                   // 38
    "Destination address required",                     // 39
    "Message too long",                                 // 40
    "Protocol wrong type for socket",                   // 41
    "Protocol not available",                           // 42
    "Protocol not supported",                           // 43
    "Socket type not supported",                        // 44
    "Operation not supported",                          // 45
    "Protocol family not supported",                    // 46
    "Address family not supported by protocol family",  // 47
    "Address already in use",                           // 48
    "Can't assign requested address",                   // 49
    "Network is down",                                  // 50
    "Network is unreachable",                           // 51
    "Network dropped connection on reset",              // 52
    "Software caused connection abort",                 // 53
    "Connection reset by peer",                         // 54
    "No buffer space available",                        // 55
    "Socket is already connected",                      // 56
    "Socket is not connected",                          // 57
    "Can't send after socket shutdown",                 // 58
    "Too many references: can't splice",                // 59
    "Operation timed out",                              // 60
    "Connection refused",                               // 61
    "Too many levels of symbolic links",                // 62
    "File name too long",                               // 63
    "Host is down",                                     // 64
    "No route to host",                                 // 65
    "Directory not empty",                              // 66
    "Too many processes",                               // 67
    "Too many users",                                   // 68
    "Disc quota exceeded",                              // 69
    "Stale NFS file handle",                            // 70
    "Too many levels of remote in path",                // 71
    "RPC struct is bad",                                // 72
    "RPC version wrong",                                // 73
    "RPC prog. not avail",                              // 74
    "Program version wrong",                            // 75
    "Bad procedure for program",                        // 76
    "No locks available",                               // 77
    "Function not implemented",                         // 78
    "Inappropriate file type or format",                // 79
    "Authentication error",                             // 80
    "Need authenticator",                               // 81
    "Device power is off",                              // 82
    "Device error",                                     // 83
    "Value too large to be stored in data type",        // 84
    "Bad executable (or shared library)",               // 85
    "Bad CPU type in executable",                       // 86
    "Shared library version mismatch",                  // 87
    "Malformed Mach-o file",                            // 88
    "Operation canceled",                               // 89
    "Identifier removed",                               // 90
    "No message of desired type",                       // 91
    "Illegal byte sequence",                            // 92
    "Attribute not found",                              // 93
    "Bad message",                                      // 94
    "EMULTIHOP (Reserved)",                             // 95
    "No message available on STREAM",                   // 96
    "ENOLINK (Reserved)",                               // 97
    "No STREAM resources",                              // 98
    "Not a STREAM",                                     // 99
    "Protocol error",                                   // 100
    "STREAM ioctl timeout",                             // 101
    "Operation not supported on socket",                // 102
    "Policy not found",                                 // 103
    "State not recoverable",                            // 104
    "Previous owner died"                               // 105
};
#elif __linux__
#define ERR_COUNT 134
static const char *error_messages[ERR_COUNT] = {
    "Success",                                            // 0
    "Operation not permitted",                            // 1
    "No such file or directory",                          // 2
    "No such process",                                    // 3
    "Interrupted system call",                            // 4
    "Input/output error",                                 // 5
    "No such device or address",                          // 6
    "Argument list too long",                             // 7
    "Exec format error",                                  // 8
    "Bad file descriptor",                                // 9
    "No child processes",                                 // 10
    "Resource temporarily unavailable",                   // 11
    "Cannot allocate memory",                             // 12
    "Permission denied",                                  // 13
    "Bad address",                                        // 14
    "Block device required",                              // 15
    "Device or resource busy",                            // 16
    "File exists",                                        // 17
    "Invalid cross-device link",                          // 18
    "No such device",                                     // 19
    "Not a directory",                                    // 20
    "Is a directory",                                     // 21
    "Invalid argument",                                   // 22
    "Too many open files in system",                      // 23
    "Too many open files",                                // 24
    "Inappropriate ioctl for device",                     // 25
    "Text file busy",                                     // 26
    "File too large",                                     // 27
    "No space left on device",                            // 28
    "Illegal seek",                                       // 29
    "Read-only file system",                              // 30
    "Too many links",                                     // 31
    "Broken pipe",                                        // 32
    "Numerical argument out of domain",                   // 33
    "Numerical result out of range",                      // 34
    "Resource deadlock avoided",                          // 35
    "File name too long",                                 // 36
    "No locks available",                                 // 37
    "Function not implemented",                           // 38
    "Directory not empty",                                // 39
    "Too many levels of symbolic links",                  // 40
    "Unknown error 41",                                   // 41
    "No message of desired type",                         // 42
    "Identifier removed",                                 // 43
    "Channel number out of range",                        // 44
    "Level 2 not synchronized",                           // 45
    "Level 3 halted",                                     // 46
    "Level 3 reset",                                      // 47
    "Link number out of range",                           // 48
    "Protocol driver not attached",                       // 49
    "No CSI structure available",                         // 50
    "Level 2 halted",                                     // 51
    "Invalid exchange",                                   // 52
    "Invalid request descriptor",                         // 53
    "Exchange full",                                      // 54
    "No anode",                                           // 55
    "Invalid request code",                               // 56
    "Invalid slot",                                       // 57
    "Unknown error 58",                                   // 58
    "Bad font file format",                               // 59
    "Device not a stream",                                // 60
    "No data available",                                  // 61
    "Timer expired",                                      // 62
    "Out of streams resources",                           // 63
    "Machine is not on the network",                      // 64
    "Package not installed",                              // 65
    "Object is remote",                                   // 66
    "Link has been severed",                              // 67
    "Advertise error",                                    // 68
    "Srmount error",                                      // 69
    "Communication error on send",                        // 70
    "Protocol error",                                     // 71
    "Multihop attempted",                                 // 72
    "RFS specific error",                                 // 73
    "Bad message",                                        // 74
    "Value too large for defined data type",              // 75
    "Name not unique on network",                         // 76
    "File descriptor in bad state",                       // 77
    "Remote address changed",                             // 78
    "Can not access a needed shared library",             // 79
    "Accessing a corrupted shared library",               // 80
    ".lib section in a.out corrupted",                    // 81
    "Attempting to link in too many shared libraries",    // 82
    "Cannot exec a shared library directly",              // 83
    "Invalid or incomplete multibyte or wide character",  // 84
    "Interrupted system call should be restarted",        // 85
    "Streams pipe error",                                 // 86
    "Too many users",                                     // 87
    "Socket operation on non-socket",                     // 88
    "Destination address required",                       // 89
    "Message too long",                                   // 90
    "Protocol wrong type for socket",                     // 91
    "Protocol not available",                             // 92
    "Protocol not supported",                             // 93
    "Socket type not supported",                          // 94
    "Operation not supported",                            // 95
    "Protocol family not supported",                      // 96
    "Address family not supported by protocol",           // 97
    "Address already in use",                             // 98
    "Cannot assign requested address",                    // 99
    "Network is down",                                    // 100
    "Network is unreachable",                             // 101
    "Network dropped connection on reset",                // 102
    "Software caused connection abort",                   // 103
    "Connection reset by peer",                           // 104
    "No buffer space available",                          // 105
    "Transport endpoint is already connected",            // 106
    "Transport endpoint is not connected",                // 107
    "Cannot send after transport endpoint shutdown",      // 108
    "Too many references: cannot splice",                 // 109
    "Connection timed out",                               // 110
    "Connection refused",                                 // 111
    "Host is down",                                       // 112
    "No route to host",                                   // 113
    "Operation already in progress",                      // 114
    "Operation now in progress",                          // 115
    "Stale file handle",                                  // 116
    "Structure needs cleaning",                           // 117
    "Not a XENIX named type file",                        // 118
    "No XENIX semaphores available",                      // 119
    "Is a named type file",                               // 120
    "Remote I/O error",                                   // 121
    "Disk quota exceeded",                                // 122
    "No medium found",                                    // 123
    "Wrong medium type",                                  // 124
    "Operation canceled",                                 // 125
    "Required key not available",                         // 126
    "Key has expired",                                    // 127
    "Key has been revoked",                               // 128
    "Key was rejected by service",                        // 129
    "Owner died",                                         // 130
    "State not recoverable",                              // 131
    "Operation not supported on transport endpoint",      // 132
    "Operation not supported on socket"                   // 133
};
#else
// Для других систем используем минимальный набор
#define ERR_COUNT 256
static const char *error_messages[ERR_COUNT];
static int error_messages_initialized = 0;

void initialize_error_messages() {
  // Если массив сообщений уже инициализирован, выходим
  if (error_messages_initialized) return;
  // Заполняем массив сообщениями по умолчанию
  for (int i = 0; i < ERR_COUNT; i++) {
    error_messages[i] = "Unknown error";
  }
  // Помечаем, что инициализация выполнена
  error_messages_initialized = 1;
}
#endif

// Функция s21_strcspn вычисляет длину начального сегмента str1,
// который полностью состоит из символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;  // Инициализируем счетчик длины сегмента
  // Пока не достигнут конец строки str1
  while (str1[count] != '\0') {
    // Проходим по всем символам строки str2
    s21_size_t i = 0;
    while (str2[i] != '\0') {
      // Если символ из str1 совпадает с символом из str2
      if (str1[count] == str2[i]) {
        // Возвращаем текущую длину сегмента
        return count;
      }
      i++;  // Переходим к следующему символу в str2
    }
    count++;  // Переходим к следующему символу в str1
  }
  // Если достигнут конец строки str1, возвращаем её длину
  return count;
}

// Функция s21_strerror выполняет поиск во внутреннем массиве номера ошибки
// errnum и возвращает указатель на строку с сообщением об ошибке.
char *s21_strerror(int errnum) {
  // Статический буфер для хранения сообщения об ошибке
  static char buffer[1024];

  // Проверяем, является ли номер ошибки корректным
  if (errnum < 0 || errnum >= ERR_COUNT) {
    // Если номер ошибки некорректен, формируем сообщение "Unknown error: X"
    snprintf(buffer, sizeof(buffer), "Unknown error: %d", errnum);
    return buffer;
  }

// Для систем, отличных от macOS и Linux, инициализируем массив сообщений
#ifndef __APPLE__
#ifndef __linux__
  initialize_error_messages();
#endif
#endif

  // Возвращаем указатель на строку с сообщением об ошибке
  return (char *)error_messages[errnum];
}

// Функция s21_strpbrk находит первый символ в строке str1,
// который соответствует любому символу, указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  // Проходим по всем символам строки str1
  while (*str1 != '\0') {
    // Проходим по всем символам строки str2
    const char *p = str2;
    while (*p != '\0') {
      // Если символы совпадают
      if (*str1 == *p) {
        // Возвращаем указатель на найденный символ в str1
        return (char *)str1;
      }
      p++;  // Переходим к следующему символу в str2
    }
    str1++;  // Переходим к следующему символу в str1
  }
  // Если совпадений не найдено, возвращаем NULL
  return S21_NULL;
}

// Функция s21_strrchr выполняет поиск последнего вхождения символа c
// (беззнаковый тип) в строке, на которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  const char *last = S21_NULL;  // Указатель на последнее найденное вхождение
  char ch = (char)c;            // Преобразуем int в char

  // Проходим по всей строке
  while (*str != '\0') {
    // Если текущий символ совпадает с искомым
    if (*str == ch) {
      last = str;  // Запоминаем позицию
    }
    str++;  // Переходим к следующему символу
  }

  // Проверяем, если искомый символ - это нулевой символ
  if (ch == '\0') {
    // Возвращаем указатель на конец строки
    return (char *)str;
  }

  // Возвращаем указатель на последнее вхождение символа
  return (char *)last;
}

// Функция s21_strstr находит первое вхождение всей строки needle
// (не включая завершающий нулевой символ), которая появляется в строке
// haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  // Если needle - пустая строка, возвращаем haystack
  if (*needle == '\0') {
    return (char *)haystack;
  }

  // Проходим по строке haystack
  while (*haystack != '\0') {
    // Сравниваем подстроку haystack с needle
    const char *h = haystack;
    const char *n = needle;

    // Пока символы совпадают и не достигнут конец needle
    while (*n != '\0' && *h == *n) {
      h++;  // Переход к следующему символу в haystack
      n++;  // Переход к следующему символу в needle
    }

    // Если достигнут конец needle, значит подстрока найдена
    if (*n == '\0') {
      return (char *)haystack;
    }

    haystack++;  // Переход к следующему символу в haystack
  }

  // Если подстрока не найдена, возвращаем NULL
  return S21_NULL;
}

// Функция s21_strtok разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *saved_pointer = S21_NULL;  // Статический указатель для сохранения позиции между вызовами
  char *token_start;  // Указатель на начало токена

  // Если str не NULL, начинаем с него, иначе продолжаем с сохраненной позиции
  if (str == S21_NULL) {
    str = saved_pointer;
  }

  // Если строка пуста, возвращаем NULL
  if (str == S21_NULL) {
    return S21_NULL;
  }

  // Пропускаем начальные разделители
  while (*str != '\0' && s21_strchr_local(delim, *str) != S21_NULL) {
    str++;
  }

  // Если достигнут конец строки, сбрасываем saved_pointer и возвращаем NULL
  if (*str == '\0') {
    saved_pointer = S21_NULL;
    return S21_NULL;
  }

  // Запоминаем начало токена
  token_start = str;

  // Ищем конец токена (первый разделитель или конец строки)
  while (*str != '\0' && s21_strchr_local(delim, *str) == S21_NULL) {
    str++;
  }

  // Если не достигнут конец строки
  if (*str != '\0') {
    *str = '\0';  // Завершаем токен нулевым символом
    saved_pointer = str + 1;  // Сохраняем позицию для следующего вызова
  } else {
    saved_pointer = S21_NULL;  // Сбрасываем saved_pointer
  }

  // Возвращаем указатель на начало токена
  return token_start;
}

// Вспомогательная функция для s21_strtok (поиск символа в строке)
static char *s21_strchr_local(const char *str, int c) {
  char ch = (char)c;
  while (*str != '\0') {
    if (*str == ch) {
      return (char *)str;
    }
    str++;
  }
  if (ch == '\0') {
    return (char *)str;
  }
  return S21_NULL;
}