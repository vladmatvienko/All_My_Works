SELECT m.pizza_name, p2.name AS pizzeria_name
FROM person_order
FULL JOIN person p ON p.id = person_order.person_id
FULL JOIN menu m ON m.id = person_order.menu_id
FULL JOIN pizzeria p2 ON m.pizzeria_id = p2.id
WHERE p.name = 'Denis' OR p.name = 'Anna'
ORDER BY 1, 2;