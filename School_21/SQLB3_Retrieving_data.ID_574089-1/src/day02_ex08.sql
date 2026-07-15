SELECT p.name
FROM person p
FULL JOIN person_order po ON p.id = po.person_id
FULL JOIN menu m ON m.id = po.menu_id
WHERE gender= 'male' AND address IN ('Moscow', 'Samara')
  AND pizza_name IN ('pepperoni pizza', 'mushroom pizza')
ORDER BY 1 DESC;