SELECT p2.name AS pizzeria_name
FROM person p
JOIN person_visits pv ON p.id = pv.person_id
JOIN pizzeria p2 ON pv.pizzeria_id = p2.id
WHERE p.name = 'Andrey'
EXCEPT
SELECT p2.name AS pizzeria_name
FROM person p
JOIN person_order po ON p.id = po.person_id
JOIN menu m ON po.menu_id = m.id
JOIN pizzeria p2 ON m.pizzeria_id = p2.id
WHERE p.name = 'Andrey'
ORDER BY pizzeria_name;