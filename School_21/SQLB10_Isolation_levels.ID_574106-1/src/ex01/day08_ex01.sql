-- Session #1
-- Шаг 1: Начало транзакции
BEGIN;

-- Шаг 2: Чтение текущего рейтинга Pizza Hut
-- Ожидаемый результат: rating = 5
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Шаг 3: Обновление рейтинга до 4
-- Эта команда выполнится сразу, но изменения ещё не зафиксированы
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut';

-- Шаг 4: Фиксация изменений
-- После этого изменения становятся видимыми другим сессиям
COMMIT;

-- Шаг 5: Повторное чтение для проверки финального результата
-- Ожидаемый результат: rating = 3.6 (значение из Session #2)
-- Обновление Session #1 (rating = 4) было потеряно!
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';


-- Session #2
-- Шаг 1: Начало транзакции
BEGIN;

-- Шаг 2: Чтение текущего рейтинга Pizza Hut
-- Выполняется ПОСЛЕ шага 2 из Session #1
-- Ожидаемый результат: rating = 5
-- Обе сессии читают ОДНУ И ТУ ЖЕ версию данных
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Шаг 3: Обновление рейтинга до 3.6
-- Эта команда БУДЕТ ЖДАТЬ, пока Session #1 не выполнит COMMIT
-- После COMMIT Session #1, Session #2 обновит УЖЕ НОВУЮ версию строки
-- (rating = 4), перезаписав её на rating = 3.6
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

-- Шаг 4: Фиксация изменений
COMMIT;

-- Шаг 5: Повторное чтение для проверки финального результата
-- Ожидаемый результат: rating = 3.6
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';