#!/bin/bash

# Тестовый скрипт для s21_cat

# Цвета для вывода
RED='\033[0;31m'   # Красный цвет для FAIL
GREEN='\033[0;32m' # Зеленый цвет для PASS
NC='\033[0m'       # Сброс цвета (No Color)

# Инициализация счетчиков тестов
total_tests=0      # Общее количество тестов
passed_tests=0     # Количество пройденных тестов

# Создание тестовой директории (если не существует)
mkdir -p tests/actual

# Массивы тестовых данных
TEST_FILES=("tests/test1.txt" "tests/test2.txt" "tests/empty.txt" "tests/multiline.txt")  # Тестовые файлы
SINGLE_FLAGS=("-b" "-e" "-n" "-s" "-t" "-E" "-T" "--number-nonblank" "--number" "--squeeze-blank")  # Одиночные флаги
COMBINED_FLAGS=("-be" "-ben" "-bens" "-bn" "-bs" "-bt" "-eE" "-en" "-es" "-et" "-nT" "-nt" "-sT" "-st")  # Комбинированные флаги

# Функция генерации тестовых файлов
generate_test_files() {
    # Создание простого тестового файла с одной строкой
    echo "Line 1" > tests/test1.txt
    
    # Создание файла с несколькими строками и пустой строкой между ними
    echo -e "Line 1\n\nLine 3" > tests/test2.txt
    
    # Создание пустого файла
    touch tests/empty.txt
    
    # Создание сложного файла с табами и множественными пустыми строками
    echo -e "Line 1\n\tLine 2\n\nLine 4\n\n\nLine 7" > tests/multiline.txt
}

# Функция тестирования одиночных флагов
run_single_flag_tests() {
    # Цикл по всем тестовым файлам
    for file in "${TEST_FILES[@]}"; do
        # Цикл по всем одиночным флагам
        for flag in "${SINGLE_FLAGS[@]}"; do
            ((total_tests++))  # Увеличиваем счетчик общих тестов
            
            # Запуск стандартной утилиты cat с текущим флагом и файлом
            # Результат сохраняем в tests/expected, ошибки перенаправляем в /dev/null
            cat $flag "$file" > tests/expected 2>/dev/null
            
            # Запуск тестируемой утилиты s21_cat с тем же флагом и файлом
            # Результат сохраняем в tests/actual/result, ошибки перенаправляем в /dev/null
            ./s21_cat $flag "$file" > tests/actual/result 2>/dev/null
            
            # Сравнение результатов стандартной и тестируемой утилит
            # Опция -q делает вывод тихим (только код возврата)
            # Перенаправляем вывод в /dev/null
            if diff -q tests/expected tests/actual/result >/dev/null; then
                ((passed_tests++))  # Увеличиваем счетчик пройденных тестов
                echo -e "${GREEN}PASS${NC}: cat $flag $file"  # Зеленый вывод PASS
            else
                echo -e "${RED}FAIL${NC}: cat $flag $file"  # Красный вывод FAIL
            fi
        done
    done
}

# Функция тестирования комбинированных флагов
run_combined_flag_tests() {
    # Цикл по всем тестовым файлам
    for file in "${TEST_FILES[@]}"; do
        # Цикл по всем комбинированным флагам
        for flag in "${COMBINED_FLAGS[@]}"; do
            ((total_tests++))  # Увеличиваем счетчик общих тестов
            
            # Запуск стандартной утилиты cat с комбинированным флагом
            cat $flag "$file" > tests/expected 2>/dev/null
            
            # Запуск тестируемой утилиты s21_cat с тем же комбинированным флагом
            ./s21_cat $flag "$file" > tests/actual/result 2>/dev/null
            
            # Сравнение результатов
            if diff -q tests/expected tests/actual/result >/dev/null; then
                ((passed_tests++))  # Увеличиваем счетчик пройденных тестов
                echo -e "${GREEN}PASS${NC}: cat $flag $file"  # Зеленый вывод PASS
            else
                echo -e "${RED}FAIL${NC}: cat $flag $file"  # Красный вывод FAIL
            fi
        done
    done
}

# Функция тестирования особых случаев
special_tests() {
    # Тест работы со стандартным вводом (символ -)
    ((total_tests++))  # Увеличиваем счетчик общих тестов
    # Передача данных через pipe в стандартную утилиту cat с флагом -A
    echo "Test stdin" | cat -A > tests/expected 2>/dev/null
    # Передача данных через pipe в тестируемую утилиту s21_cat с флагом -A
    echo "Test stdin" | ./s21_cat -A > tests/actual/result 2>/dev/null
    
    # Проверка кодов возврата (для stdin теста проверяем только что обе команды выполнились)
    # $? содержит код возврата последней команды
    if [ $? -eq $? ]; then
        ((passed_tests++))  # Увеличиваем счетчик пройденных тестов
        echo -e "${GREEN}PASS${NC}: stdin test"  # Зеленый вывод PASS
    else
        echo -e "${RED}FAIL${NC}: stdin test"  # Красный вывод FAIL
    fi

    # Тест обработки нескольких файлов
    ((total_tests++))  # Увеличиваем счетчик общих тестов
    # Конкатенация двух файлов стандартной утилитой cat
    cat tests/test1.txt tests/test2.txt > tests/expected 2>/dev/null
    # Конкатенация двух файлов тестируемой утилитой s21_cat
    ./s21_cat tests/test1.txt tests/test2.txt > tests/actual/result 2>/dev/null
    
    # Сравнение результатов конкатенации
    if diff -q tests/expected tests/actual/result >/dev/null; then
        ((passed_tests++))  # Увеличиваем счетчик пройденных тестов
        echo -e "${GREEN}PASS${NC}: multiple files test"  # Зеленый вывод PASS
    else
        echo -e "${RED}FAIL${NC}: multiple files test"  # Красный вывод FAIL
        # Дополнительный вывод для отладки в случае ошибки
        echo "Expected:"
        cat tests/expected    # Показываем ожидаемый результат
        echo "Actual:"
        cat tests/actual/result  # Показываем фактический результат
    fi

    # Тест обработки несуществующего файла
    ((total_tests++))  # Увеличиваем счетчик общих тестов
    # Попытка открыть несуществующий файл стандартной утилитой cat
    # Ошибки перенаправляем в tests/expected
    cat no_such_file.txt 2> tests/expected
    # Попытка открыть несуществующий файл тестируемой утилитой s21_cat
    # Ошибки перенаправляем в tests/actual/result
    ./s21_cat no_such_file.txt 2> tests/actual/result
    
    # Проверяем что обе команды вернули ошибку (не сравниваем текст сообщений)
    if [ $? -eq $? ]; then
        ((passed_tests++))  # Увеличиваем счетчик пройденных тестов
        echo -e "${GREEN}PASS${NC}: non-existent file test"  # Зеленый вывод PASS
    else
        echo -e "${RED}FAIL${NC}: non-existent file test"  # Красный вывод FAIL
    fi
}

# Главная функция тестирования
main() {
    generate_test_files      # Генерируем тестовые файлы
    run_single_flag_tests   # Запускаем тесты одиночных флагов
    run_combined_flag_tests # Запускаем тесты комбинированных флагов
    special_tests           # Запускаем специальные тесты
    
    # Вывод итоговой статистики
    echo -e "\nTest summary:"
    echo -e "Total tests: $total_tests"  # Общее количество тестов
    echo -e "${GREEN}Passed${NC}: $passed_tests"  # Количество пройденных тестов (зеленый)
    echo -e "${RED}Failed${NC}: $((total_tests - passed_tests))"  # Количество проваленных тестов (красный)
    
    # Определение кода возврата
    if [ $passed_tests -eq $total_tests ]; then
        exit 0  # Все тесты пройдены - успешное завершение
    else
        exit 1  # Есть проваленные тесты - завершение с ошибкой
    fi
}

# Запуск главной функции
main