SELECT p.name
FROM person p
FULL JOIN person_order po ON p.id = po.person_id
FULL JOIN menu m ON m.id = po.menu_id
WHERE m.pizza_name = 'pepperoni pizza'
  AND p.gender = 'female'
INTERSECT
SELECT p.name
FROM person p
FULL JOIN person_order po ON p.id = po.person_id
FULL JOIN menu m ON m.id = po.menu_id
WHERE m.pizza_name = 'cheese pizza'
  AND p.gender = 'female'
ORDER BY 1;