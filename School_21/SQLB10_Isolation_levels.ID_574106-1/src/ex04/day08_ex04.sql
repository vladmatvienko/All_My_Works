-- Session #1
-- 1. Начало транзакции
BEGIN;

-- Явная установка уровня изоляции SERIALIZABLE
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;

-- 2. Первое чтение рейтинга
-- В этот момент PostgreSQL фиксирует snapshot данных.
-- Все последующие чтения в этой транзакции будут видеть только этот снимок.
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый вывод: rating = 3.6

-- 3. Второе чтение рейтинга (После того, как Session #2 выполнила UPDATE и COMMIT)
-- Поскольку уровень изоляции SERIALIZABLE гарантирует, что транзакция видит
-- данные так, как будто она выполнялась одна (последовательно),
-- она НЕ увидит изменения, сделанные другими транзакциями после её старта.
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый вывод: rating = 4.6 (Значение НЕ изменилось!)
-- Аномалия Non-Repeatable Read предотвращена.

-- 4. Завершение транзакции
COMMIT;
-- 5. Третье чтение рейтинга
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Session #2

-- 1. Начало транзакции
BEGIN;

-- 2. Обновление рейтинга до 3.0
UPDATE pizzeria SET rating = 3.0 WHERE name = 'Pizza Hut';

-- 3. Фиксация изменений
-- Изменения записываются в БД, но Session #1 всё ещё работает со своим старым снимком.
COMMIT;

-- 4. Финальная проверка (после завершения всех транзакций)
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Ожидаемый вывод: rating = 3.0