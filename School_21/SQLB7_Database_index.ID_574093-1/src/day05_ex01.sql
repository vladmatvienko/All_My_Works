SET enable_seqscan = OFF;

EXPLAIN ANALYZE
SELECT m.pizza_name, pz.name AS pizzeria_name
FROM menu m JOIN pizzeria pz ON m.pizzeria_id = pz.id;

SET enable_seqscan = ON;