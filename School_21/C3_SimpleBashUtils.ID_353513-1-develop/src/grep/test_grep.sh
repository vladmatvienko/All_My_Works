#!/bin/bash
# Указание что скрипт должен выполняться в bash

# Цвета для вывода
RED='\033[0;31m'       # Красный цвет для вывода ошибок
GREEN='\033[0;32m'     # Зеленый цвет для успешных операций
YELLOW='\033[1;33m'    # Желтый цвет для заголовков и предупреждений
NC='\033[0m'           # Код сброса цвета (No Color)

# Директория для тестовых файлов
TEST_DIR="test_files"
# Создание директории (опция -p создает родительские директории если нужно)
mkdir -p $TEST_DIR

# Создание тестовых файлов
# Файл 1: различные регистры и паттерны
echo "Hello world" > $TEST_DIR/file1.txt        # Первая строка: Hello world
echo "hello WORLD" >> $TEST_DIR/file1.txt       # Добавление строки: hello WORLD
echo "test line" >> $TEST_DIR/file1.txt         # Добавление строки: test line
echo "Another test" >> $TEST_DIR/file1.txt      # Добавление строки: Another test

# Файл 2: для тестирования паттернов
echo "pattern match" > $TEST_DIR/file2.txt      # Первая строка: pattern match
echo "no match here" >> $TEST_DIR/file2.txt     # Добавление строки: no match here
echo "PATTERN match" >> $TEST_DIR/file2.txt     # Добавление строки: PATTERN match

# Файл 3: простые строки для базовых тестов
echo "line 1" > $TEST_DIR/file3.txt             # Первая строка: line 1
echo "line 2" >> $TEST_DIR/file3.txt            # Добавление строки: line 2
echo "line 3" >> $TEST_DIR/file3.txt            # Добавление строки: line 3

# Файл с паттернами для тестирования флага -f
echo "hello" > $TEST_DIR/patterns.txt           # Первый паттерн: hello
echo "test" >> $TEST_DIR/patterns.txt           # Добавление паттерна: test

# Счетчики тестов
TESTS_PASSED=0    # Количество пройденных тестов
TESTS_FAILED=0    # Количество неудачных тестов

# Функция для запуска теста
run_test() {
    # Параметры функции:
    local test_name="$1"    # Название теста для вывода
    local flags="$2"        # Флаги для grep (например "-i -v")
    local pattern="$3"      # Паттерн для поиска
    local files="$4"        # Файлы для поиска
    local expected_exit="$5" # Ожидаемый код возврата

    # Вывод названия теста желтым цветом
    echo -e "${YELLOW}Testing: $test_name${NC}"
    
    # Запуск настоящего grep и сохранение вывода
    # $flags - флаги, "$pattern" - паттерн, $files - файлы
    # > real_output.txt - перенаправление stdout в файл
    # 2> real_error.txt - перенаправление stderr в файл
    grep $flags "$pattern" $files > real_output.txt 2> real_error.txt
    real_exit=$?  # Сохранение кода возврата реального grep
    
    # Запуск нашей реализации grep
    ./s21_grep $flags "$pattern" $files > our_output.txt 2> our_error.txt
    our_exit=$?  # Сохранение кода возврата нашей реализации
    
    # Сравнение выводов (stdout)
    diff_output=$(diff real_output.txt our_output.txt)
    # Нормализуем сообщения об ошибках (убираем префиксы)
    # Заменяем "grep:" на "s21_grep:" в ошибках реального grep
    sed 's/grep:/s21_grep:/g' real_error.txt > real_error_normalized.txt
    # Сравнение ошибок (stderr)
    diff_error=$(diff real_error_normalized.txt our_error.txt)
    
    # Проверка условий успешного теста:
    # 1. Коды возврата совпадают
    # 2. Нет различий в stdout
    # 3. Нет различий в stderr
    if [ "$real_exit" -eq "$our_exit" ] && [ -z "$diff_output" ] && [ -z "$diff_error" ]; then
        echo -e "${GREEN}PASS${NC}"  # Вывод PASS зеленым цветом
        ((TESTS_PASSED++))  # Увеличение счетчика пройденных тестов
    else
        echo -e "${RED}FAIL${NC}"  # Вывод FAIL красным цветом
        # Вывод информации о различиях
        echo "Real exit: $real_exit, Our exit: $our_exit"
        if [ -n "$diff_output" ]; then  # Если есть различия в выводе
            echo "Output diff:"
            echo "$diff_output"  # Показать различия
        fi
        if [ -n "$diff_error" ]; then  # Если есть различия в ошибках
            echo "Error diff:"
            echo "$diff_error"  # Показать различия
        fi
        ((TESTS_FAILED++))  # Увеличение счетчика неудачных тестов
    fi
    
    # Разделитель между тестами
    echo "----------------------------------------"
}

# Функция для запуска теста с конкретной командной строкой
run_test_cmd() {
    local test_name="$1"    # Название теста
    local real_cmd="$2"     # Команда для реального grep
    local our_cmd="$3"      # Команда для нашей реализации
    local expected_exit="$4" # Ожидаемый код возврата

    echo -e "${YELLOW}Testing: $test_name${NC}"
    
    # Выполнение команды реального grep
    eval "$real_cmd" > real_output.txt 2> real_error.txt
    real_exit=$?  # Сохранение кода возврата
    
    # Выполнение команды нашей реализации
    eval "$our_cmd" > our_output.txt 2> our_error.txt
    our_exit=$?  # Сохранение кода возврата
    
    # Сравнение выводов
    diff_output=$(diff real_output.txt our_output.txt)
    # Нормализация сообщений об ошибках
    sed 's/grep:/s21_grep:/g' real_error.txt > real_error_normalized.txt
    diff_error=$(diff real_error_normalized.txt our_error.txt)
    
    # Проверка условий успеха
    if [ "$real_exit" -eq "$our_exit" ] && [ -z "$diff_output" ] && [ -z "$diff_error" ]; then
        echo -e "${GREEN}PASS${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}FAIL${NC}"
        echo "Real exit: $real_exit, Our exit: $our_exit"
        if [ -n "$diff_output" ]; then
            echo "Output diff:"
            echo "$diff_output"
        fi
        if [ -n "$diff_error" ]; then
            echo "Error diff:"
            echo "$diff_error"
        fi
        ((TESTS_FAILED++))
    fi
    
    echo "----------------------------------------"
}

# Функция для тестирования ввода из stdin
run_test_stdin() {
    local test_name="$1"    # Название теста
    local flags="$2"        # Флаги grep
    local pattern="$3"      # Паттерн для поиска
    local input="$4"        # Входные данные

    echo -e "${YELLOW}Testing: $test_name${NC}"
    
    # Запуск реального grep с данными из stdin
    echo "$input" | grep $flags "$pattern" > real_output.txt 2> real_error.txt
    real_exit=$?
    
    # Запуск нашей реализации с данными из stdin
    echo "$input" | ./s21_grep $flags "$pattern" > our_output.txt 2> our_error.txt
    our_exit=$?
    
    # Сравнение результатов
    diff_output=$(diff real_output.txt our_output.txt)
    # Нормализация сообщений об ошибках
    sed 's/grep:/s21_grep:/g' real_error.txt > real_error_normalized.txt
    diff_error=$(diff real_error_normalized.txt our_error.txt)
    
    # Проверка условий успеха
    if [ "$real_exit" -eq "$our_exit" ] && [ -z "$diff_output" ] && [ -z "$diff_error" ]; then
        echo -e "${GREEN}PASS${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}FAIL${NC}"
        ((TESTS_FAILED++))
    fi
    
    echo "----------------------------------------"
}

# Очистка предыдущих тестовых файлов
rm -f real_output.txt real_error.txt our_output.txt our_error.txt real_error_normalized.txt

# Заголовок тестирования
echo "========================================"
echo "STARTING INTEGRATION TESTS FOR S21_GREP"
echo "========================================"

# Базовые тесты
run_test "Basic pattern match" "" "hello" "$TEST_DIR/file1.txt" 0
run_test "Pattern not found" "" "nonexistent" "$TEST_DIR/file1.txt" 1
run_test "Multiple files" "" "test" "$TEST_DIR/file1.txt $TEST_DIR/file2.txt" 0

# Тесты флагов
run_test "Ignore case -i" "-i" "world" "$TEST_DIR/file1.txt" 0
run_test "Invert match -v" "-v" "hello" "$TEST_DIR/file1.txt" 0
run_test "Count matches -c" "-c" "test" "$TEST_DIR/file1.txt" 0
run_test "Line numbers -n" "-n" "hello" "$TEST_DIR/file1.txt" 0
run_test "Only filenames -l" "-l" "test" "$TEST_DIR/file1.txt $TEST_DIR/file2.txt" 0
run_test "Suppress filenames -h" "-h" "test" "$TEST_DIR/file1.txt $TEST_DIR/file2.txt" 0
run_test "Only matching parts -o" "-o" "test" "$TEST_DIR/file1.txt" 0

# Тесты с несколькими флагами
run_test "Multiple flags -i -v" "-i -v" "world" "$TEST_DIR/file1.txt" 0
run_test "Multiple flags -c -n" "-c -n" "test" "$TEST_DIR/file1.txt" 0

# Тесты флага -e
run_test_cmd "Multiple -e patterns" \
    "grep -e hello -e world $TEST_DIR/file1.txt" \
    "./s21_grep -e hello -e world $TEST_DIR/file1.txt" \
    0

run_test_cmd "-e with other flags" \
    "grep -i -e HELLO $TEST_DIR/file1.txt" \
    "./s21_grep -i -e HELLO $TEST_DIR/file1.txt" \
    0

# Тесты флага -f
run_test_cmd "Patterns from file -f" \
    "grep -f $TEST_DIR/patterns.txt $TEST_DIR/file1.txt" \
    "./s21_grep -f $TEST_DIR/patterns.txt $TEST_DIR/file1.txt" \
    0

run_test_cmd "-f with other flags" \
    "grep -n -f $TEST_DIR/patterns.txt $TEST_DIR/file1.txt" \
    "./s21_grep -n -f $TEST_DIR/patterns.txt $TEST_DIR/file1.txt" \
    0

# Тесты обработки ошибок (игнорируем разницу в префиксах ошибок)
run_test_cmd "Non-existent file" \
    "grep pattern nonexistent.txt 2>/dev/null || true" \
    "./s21_grep pattern nonexistent.txt 2>/dev/null || true" \
    2

run_test_cmd "Non-existent pattern file" \
    "grep -f nonexistent.txt $TEST_DIR/file1.txt 2>/dev/null || true" \
    "./s21_grep -f nonexistent.txt $TEST_DIR/file1.txt 2>/dev/null || true" \
    2

run_test "With -s flag" "-s" "pattern" "nonexistent.txt" 1

# Тесты ввода из stdin
run_test_stdin "Stdin input" "" "hello" "hello world\nthis is a test"
run_test_stdin "Stdin with flags" "-i" "HELLO" "hello world\nTEST"

# Крайние случаи
run_test "Empty pattern" "" "" "$TEST_DIR/file1.txt" 0
run_test "Special characters" "" "[a-z]" "$TEST_DIR/file1.txt" 0
run_test "Regex patterns" "" "^hello" "$TEST_DIR/file1.txt" 0

# Очистка тестовых файлов
rm -f real_output.txt real_error.txt our_output.txt our_error.txt real_error_normalized.txt
rm -rf $TEST_DIR  # Рекурсивное удаление тестовой директории

# Вывод результатов тестирования
echo "========================================"
echo "TEST RESULTS:"
echo -e "${GREEN}PASSED: $TESTS_PASSED${NC}"  # Зеленый вывод пройденных тестов
if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "${GREEN}FAILED: $TESTS_FAILED${NC}"  # Зеленый если нет неудачных
else
    echo -e "${RED}FAILED: $TESTS_FAILED${NC}"    # Красный если есть неудачные
fi
echo "========================================"

# Установка кода возврата скрипта
if [ $TESTS_FAILED -eq 0 ]; then
    exit 0  # Успех - все тесты пройдены
else
    exit 1  # Неудача - есть непройденные тесты
fi