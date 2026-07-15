WITH days AS (SELECT days::date
           FROM generate_series('2022-01-01', '2022-01-10', interval '1 day') AS days)
SELECT days::date AS missing_date
FROM (SELECT * FROM person_visits pv
      WHERE person_id = 1 OR person_id = 2) AS pv
RIGHT JOIN days ON pv.visit_date = days
WHERE pv.id IS NULL
ORDER BY 1;