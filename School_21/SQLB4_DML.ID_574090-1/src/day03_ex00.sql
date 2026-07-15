SELECT m.pizza_name,
       m.price,
       p2.name AS pizzeria_name,
       pv.visit_date
FROM person p
FULL JOIN person_visits pv ON p.id = pv.person_id
FULL JOIN pizzeria p2 ON pv.pizzeria_id = p2.id
FULL JOIN menu m ON p2.id = m.pizzeria_id
WHERE p.name = 'Kate'
  AND m.price BETWEEN 800 AND 1000
ORDER BY 1, 2, 3;