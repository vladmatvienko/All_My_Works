INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT (SELECT MAX(id) FROM person_order) + gs,
       (SELECT MIN(id) FROM person) + gs - 1,
       (SELECT id FROM menu WHERE pizza_name = 'greek pizza'),
       '2022-02-25'
FROM generate_series(1, (SELECT COUNT(*) FROM person)) AS gs;

