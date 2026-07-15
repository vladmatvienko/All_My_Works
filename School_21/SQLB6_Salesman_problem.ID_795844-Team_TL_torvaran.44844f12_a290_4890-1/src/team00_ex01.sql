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
    AND    array_length(tour, 1) = 5
),
min_max_costs AS (
    SELECT MIN(total_cost) AS min_cost, MAX(total_cost) AS max_cost
    FROM   complete_tours
)
SELECT ct.total_cost, ct.tour
FROM   complete_tours ct
JOIN   min_max_costs m ON ct.total_cost = m.min_cost OR ct.total_cost = m.max_cost
ORDER  BY ct.total_cost, ct.tour::text;