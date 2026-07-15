SELECT days::date AS missing_date
FROM
    (SELECT * FROM person_visits po
    WHERE person_id = 1 OR person_id = 2) AS po
RIGHT  JOIN generate_series('2022-01-01', '2022-01-10', interval '1 day') AS days ON po.visit_date = days
WHERE po.id IS NULL
ORDER BY 1;