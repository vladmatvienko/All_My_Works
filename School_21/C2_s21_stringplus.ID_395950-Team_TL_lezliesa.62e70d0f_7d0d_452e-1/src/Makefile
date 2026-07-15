# Makefile для сборки библиотеки s21_string и unit-тестов

# Компилятор и флаги
# Определяем компилятор C, который будет использоваться для сборки
CC = gcc
# Флаги компиляции: 
# -Wall - включает все стандартные предупреждения
# -Wextra - включает дополнительные предупреждения
# -Werror - treats all warnings as errors
# -std=c11 - указывает использовать стандарт C11
# -g - включает отладочную информацию
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
# Флаги для сбора информации о покрытии кода gcov:
# -fprofile-arcs - генерирует информацию о переходах между базовыми блоками
# -ftest-coverage - генерирует информацию о покрытии тестами
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
# Библиотека для работы с gcov
GCOV_LIBS = -lgcov

# Имена файлов
# Имя библиотеки без расширения
LIB_NAME = s21_string
# Исходный файл библиотеки
LIB_SRC = s21_string.c
# Заголовочный файл библиотеки
LIB_HEADER = s21_string.h
# Объектный файл библиотеки (заменяем .c на .o)
LIB_OBJ = $(LIB_SRC:.c=.o)
# Имя исполняемого файла тестов
TEST_NAME = s21_string_test
# Исходный файл с тестами
TEST_SRC = s21_string_test.c
# Объектный файл тестов (заменяем .c на .o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Цели по умолчанию - специальные метки, которые не соответствуют файлам
# .PHONY указывает, что эти цели не являются именами файлов
.PHONY: all clean test gcov_report

# Цель по умолчанию - при запуске make без аргументов будет выполнена эта цель
# Собирает статическую библиотеку
all: lib$(LIB_NAME).a

# Правило сборки статической библиотеки из объектного файла
# ar - утилита для работы с архивами
# rcs - флаги: r - заменить файлы в архиве, c - создать архив, s - создать индекс
lib$(LIB_NAME).a: $(LIB_OBJ)
	ar rcs lib$(LIB_NAME).a $(LIB_OBJ)

# Правило компиляции исходного файла библиотеки в объектный файл
# $(CC) - вызов компилятора
# $(CFLAGS) - флаги компиляции
# -c - компилировать без линковки
# $(LIB_SRC) - входной файл
# -o $(LIB_OBJ) - выходной файл
# -I. - указываем текущую директорию для поиска заголовочных файлов
$(LIB_OBJ): $(LIB_SRC) $(LIB_HEADER)
	$(CC) $(CFLAGS) -c $(LIB_SRC) -o $(LIB_OBJ) -I.

# Цель для запуска тестов - сначала собирает тесты, потом запускает их
test: $(TEST_NAME)
	./$(TEST_NAME)

# Правило сборки исполняемого файла тестов
# Линкуем объектный файл тестов с библиотекой и библиотекой check
# -L. - указываем текущую директорию как путь для поиска библиотек
# -ls21_string - подключаем нашу библиотеку
# -lcheck - подключаем библиотеку тестирования Check
# -lrt - библиотека для работы со временем (для Check)
# -lpthread - библиотека потоков (для Check)
# -lm - математическая библиотека (для Check)
# -lsubunit - библиотека для работы с subunit
$(TEST_NAME): lib$(LIB_NAME).a $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_NAME) -L. -ls21_string -lcheck -lrt -lpthread -lm -lsubunit

# Правило компиляции исходного файла тестов в объектный файл
# Зависит от наличия библиотеки и исходного файла тестов
$(TEST_OBJ): $(TEST_SRC) lib$(LIB_NAME).a
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ) -I.

# Цель для генерации отчета о покрытии кода gcov
# Добавляем флаги gcov к основным флагам компиляции
gcov_report: CFLAGS += $(GCOV_FLAGS)
# Зависит от цели clean (очистка), библиотеки и объектного файла тестов
gcov_report: clean lib$(LIB_NAME).a $(TEST_OBJ)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_OBJ) -o $(TEST_NAME) -L. -ls21_string -lcheck -lrt -lpthread -lm -lsubunit $(GCOV_LIBS)
	./$(TEST_NAME)
	mkdir -p gcov_report
	lcov --capture --directory . --output-file gcov_report/coverage.info
	genhtml gcov_report/coverage.info --output-directory gcov_report
	@echo "GCOV report generated in gcov_report directory"

# Цель очистки - удаляет все сгенерированные файлы
clean:
	rm -f $(LIB_OBJ) lib$(LIB_NAME).a $(TEST_OBJ) $(TEST_NAME) *.gcda *.gcno *.gcov *.info
	rm -rf gcov_report