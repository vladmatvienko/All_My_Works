SELECT order_date,
       name || ' (age:'||age||')' AS person_information
FROM person_order
NATURAL JOIN (SELECT p.id AS person_id,
                             name,
                             age
              FROM person p)
ORDER BY 1, 2;