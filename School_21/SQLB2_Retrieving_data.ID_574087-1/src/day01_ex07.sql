SELECT order_date,
       name || ' (age:'||age||')' AS person_information
 FROM person_order
 INNER JOIN person p ON p.id = person_order.person_id
 ORDER BY 1, 2;