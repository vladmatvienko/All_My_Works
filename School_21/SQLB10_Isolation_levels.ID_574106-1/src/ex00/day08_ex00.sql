-- Session #1
BEGIN;
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut';
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат: id | name      | rating -> 1 | Pizza Hut | 5
-- ДО выполнения COMMIT изменения видны только в текущей сессии.

-- Session #2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат: rating остаётся прежним, так как транзакция Session #1 ещё не зафиксирована.

-- Session #1 (продолжение)
COMMIT;

-- Session #2 (продолжение)
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат: rating = 5. Изменения стали видимыми после фиксации транзакции в Session #1.

--UPDATE pizzeria SET rating = 4.6 WHERE name = 'Pizza Hut';
