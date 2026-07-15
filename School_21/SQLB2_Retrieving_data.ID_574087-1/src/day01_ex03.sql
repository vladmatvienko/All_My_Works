SELECT order_date AS action_date,
       person_id
FROM person_order INTERSECT ALL
SELECT visit_date,
       person_id
FROM person_visits
ORDER BY 1,
         2 DESC;