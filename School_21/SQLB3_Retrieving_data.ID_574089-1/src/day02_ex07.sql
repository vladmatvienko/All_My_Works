SELECT p.name AS pizzeria_name
FROM menu m 
FULL JOIN pizzeria p ON m.pizzeria_id = p.id
FULL JOIN person_visits pv ON p.id = pv.pizzeria_id
FULL JOIN person p2 ON pv.person_id  = p2.id
WHERE p2.name = 'Dmitriy' AND visit_date = '2022-01-08' AND price < 800;