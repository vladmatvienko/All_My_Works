-- Session #1
-- 1. Начало транзакции
BEGIN;

-- Явная установка уровня изоляции REPEATABLE READ
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- 2. Чтение текущего рейтинга (фиксация моментального снимка данных)
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый вывод: rating = 3.6

-- 3. Обновление рейтинга до 4
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut';
-- Команда выполняется успешно. Изменение пока видно только в рамках Session #1.

-- 4. Фиксация изменений
COMMIT;
-- Снимок завершён, новая версия строки опубликована в БД.

-- 5. Финальная проверка результата
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый вывод: rating = 4.0


-- Session #2
-- 1. Начало транзакции
BEGIN;

-- Явная установка уровня изоляции REPEATABLE READ
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- 2. Чтение рейтинга (видит снимок, созданный в момент BEGIN)
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый вывод: rating = 3.6

-- 3. Попытка обновления рейтинга до 3.6
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
-- Возникнет ОШИБКА:  не удалось сериализовать доступ из-за параллельного изменения

-- 4. ROLLBACK Откат прерванной транзакции (обязательно после ошибки в psql)
COMMIT;

-- 5. Финальная проверка результата
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый вывод: rating = 4.0
-- Session #2 видит результат успешной Session #1, так как собственная транзакция откатилась.