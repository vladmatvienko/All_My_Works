CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -pedantic -g
LDFLAGS = -lcheck -lm -lsubunit -lrt -lpthread
GCov_FLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1

# Файлы находятся в текущей директории (src)
SRCS = s21_matrix.c
OBJS = $(SRCS:.c=.o)
TEST_SRCS = tests.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

LIB_NAME = s21_matrix.a
TEST_NAME = test_matrix

all: clean $(LIB_NAME) test

# Компиляция объектных файлов библиотеки
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Создание статической библиотеки
$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

# Сборка и запуск тестов
test: $(LIB_NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_NAME) $(LDFLAGS) -o $(TEST_NAME)
	./$(TEST_NAME)

# Проверка на формат
clang:
	clang-format -n *.h *.c

# Запуск тестов под Valgrind для проверки памяти
valgrind: CFLAGS += -g -O0
valgrind: clean $(LIB_NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_NAME) $(LDFLAGS) -o $(TEST_NAME)
	valgrind $(VALGRIND_FLAGS) ./$(TEST_NAME)

# Генерация отчёта gcov в формате HTML
gcov_report: CFLAGS += $(GCov_FLAGS)
gcov_report: clean test
	lcov --capture --directory . --output-file coverage.info --include "*/s21_matrix.c" --ignore-errors empty
	genhtml -o report coverage.info --ignore-errors empty
	@echo "GCov report generated in report/index.html"

clean:
	rm -rf *.o $(LIB_NAME) $(TEST_NAME) *.gcda *.gcno *.gcov report coverage.info

.PHONY: all clean test clang valgrind gcov_report