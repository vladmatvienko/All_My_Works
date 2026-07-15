   (SELECT DISTINCT p2.name AS pizzeria_name
    FROM person_order po
    JOIN person p ON po.person_id = p.id
    JOIN menu m ON po.menu_id = m.id
    JOIN pizzeria p2 ON m.pizzeria_id = p2.id
    WHERE p.gender = 'female'
    EXCEPT
    SELECT DISTINCT p2.name AS pizzeria_name
    FROM person_order po
    JOIN person p ON po.person_id = p.id
    JOIN menu m ON po.menu_id = m.id
    JOIN pizzeria p2 ON m.pizzeria_id = p2.id
    WHERE p.gender = 'male')
UNION
   (SELECT DISTINCT p2.name AS pizzeria_name
    FROM person_order po
    JOIN person p ON po.person_id = p.id
    JOIN menu m ON po.menu_id = m.id
    JOIN pizzeria p2 ON m.pizzeria_id = p2.id
    WHERE p.gender = 'male'
    EXCEPT
    SELECT DISTINCT p2.name AS pizzeria_name
    FROM person_order po
    JOIN person p ON po.person_id = p.id
    JOIN menu m ON po.menu_id = m.id
    JOIN pizzeria p2 ON m.pizzeria_id = p2.id
    WHERE p.gender = 'female')
ORDER BY 1;