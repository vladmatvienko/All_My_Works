COMMENT ON TABLE person_discounts IS 'Хранит персональные процентные скидки для каждого клиента в конкретной пиццерии.';

COMMENT ON COLUMN person_discounts.id IS 'Уникальный идентификатор записи о скидке (первичный ключ).';

COMMENT ON COLUMN person_discounts.person_id IS 'Ссылка на клиента (person), которому предоставляется скидка.';

COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Ссылка на пиццерию (pizzeria), в которой применяется скидка.';

COMMENT ON COLUMN person_discounts.discount IS 'Процент скидки (от 0 до 100), применяемый к заказам.';

SELECT count(*) = 5 AS check
FROM pg_description
WHERE objoid = 'person_discounts'::regclass;