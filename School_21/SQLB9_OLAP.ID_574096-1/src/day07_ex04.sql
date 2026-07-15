SELECT p.name, 
       COUNT(pv.person_id) AS count_of_visits
FROM person p
JOIN person_visits pv ON p.id = pv.person_id
GROUP BY p.name
HAVING COUNT(pv.person_id) > 3;