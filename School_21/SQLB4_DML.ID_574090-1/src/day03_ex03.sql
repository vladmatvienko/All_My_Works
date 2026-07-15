   (SELECT p2.name AS pizzeria_name
    FROM person_visits pv
    JOIN person p ON pv.person_id = p.id
    JOIN pizzeria p2 ON pv.pizzeria_id = p2.id
    WHERE p.gender = 'female'
    EXCEPT ALL
    SELECT p2.name AS pizzeria_name
    FROM person_visits pv
    JOIN person p ON pv.person_id = p.id
    JOIN pizzeria p2 ON pv.pizzeria_id = p2.id
    WHERE p.gender = 'male')
UNION ALL
   (SELECT p2.name AS pizzeria_name
    FROM person_visits pv
    JOIN person p ON pv.person_id = p.id
    JOIN pizzeria p2 ON pv.pizzeria_id = p2.id
    WHERE p.gender = 'male'
    EXCEPT ALL
    SELECT p2.name AS pizzeria_name
    FROM person_visits pv
    JOIN person p ON pv.person_id = p.id
    JOIN pizzeria p2 ON pv.pizzeria_id = p2.id
    WHERE p.gender = 'female')
ORDER BY 1;