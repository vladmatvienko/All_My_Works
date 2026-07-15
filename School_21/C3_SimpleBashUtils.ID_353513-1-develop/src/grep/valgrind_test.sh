#!/bin/bash
# Указание что скрипт должен выполняться в bash

# Вывод сообщения о начале проверки памяти
echo "Running valgrind memory check..."

# Создание тестового файла для проверки
echo "test line 1" > test_valgrind.txt  # Создание файла с первой тестовой строкой
echo "test line 2" >> test_valgrind.txt # Добавление второй тестовой строки в файл

# Запуск valgrind для проверки памяти с детальными настройками
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_out.txt ./s21_grep "test" test_valgrind.txt
# --leak-check=full: включить полную проверку утечек памяти
# --show-leak-kinds=all: показывать все виды утечек памяти
# --track-origins=yes: отслеживать источники неинициализированных значений
# --verbose: подробный вывод информации
# --log-file=valgrind_out.txt: сохранить вывод в файл valgrind_out.txt
# ./s21_grep "test" test_valgrind.txt: команда для тестирования (поиск "test" в файле)

# Проверка отчета valgrind на наличие ошибок памяти
if grep -q "ERROR SUMMARY: 0 errors" valgrind_out.txt && \
   grep -q "All heap blocks were freed" valgrind_out.txt; then
    # Если найдены фразы об отсутствии ошибок и полном освобождении памяти
    echo "Valgrind test: PASS - No memory leaks"  # Сообщение об успешной проверке
else
    # Если обнаружены проблемы с памятью
    echo "Valgrind test: FAIL - Memory issues detected"  # Сообщение об ошибке
    # Вывод relevant частей отчета valgrind
    cat valgrind_out.txt | grep -E "ERROR SUMMARY|leak"  # Поиск и вывод информации об ошибках и утечках
    # Очистка временных файлов перед выходом
    rm -f test_valgrind.txt valgrind_out.txt
    exit 1  # Завершение скрипта с кодом ошибки
fi

# Очистка временных файлов после успешного тестирования
rm -f test_valgrind.txt valgrind_out.txt valgrind_out2.txt
# Удаление тестового файла и файлов с отчетами valgrind

# Вывод сообщения о завершении тестирования
echo "Valgrind testing completed"