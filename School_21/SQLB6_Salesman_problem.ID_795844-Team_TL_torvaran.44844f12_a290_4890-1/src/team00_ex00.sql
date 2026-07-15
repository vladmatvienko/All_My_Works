DROP TABLE IF EXISTS nodes;

CREATE TABLE nodes (
    point1 VARCHAR(1),
    point2 VARCHAR(1),
    cost   INTEGER
);

INSERT INTO nodes VALUES
    ('a', 'b', 10), ('b', 'a', 10),
    ('a', 'c', 15), ('c', 'a', 15),
    ('a', 'd', 20), ('d', 'a', 20),
    ('b', 'd', 25), ('d', 'b', 25),
    ('c', 'd', 30), ('d', 'c', 30),
    ('b', 'c', 35), ('c', 'b', 35);

WITH RECURSIVE tours AS (
    SELECT
        'a'::varchar          AS current_city,
        ARRAY['a'::varchar]   AS tour,
        0                     AS total_cost,
        ARRAY['a'::varchar]   AS visited

    UNION ALL

    SELECT
        n.point2,
        t.tour    || n.point2,
        t.total_cost + n.cost,
        t.visited || n.point2
    FROM tours t
    JOIN nodes n ON n.point1 = t.current_city
    WHERE
        (n.point2 != ALL(t.visited))
        OR
        (n.point2 = 'a' AND array_length(t.visited, 1) = 4)
),

complete_tours AS (
    SELECT total_cost, tour
    FROM   tours
    WHERE  current_city = 'a'
      AND  array_length(tour, 1) = 5
),

min_cost AS (
    SELECT MIN(total_cost) AS min_cost FROM complete_tours
)

SELECT ct.total_cost, ct.tour
FROM   complete_tours ct
JOIN   min_cost m ON ct.total_cost = m.min_cost
ORDER  BY ct.total_cost, ct.tour::text;