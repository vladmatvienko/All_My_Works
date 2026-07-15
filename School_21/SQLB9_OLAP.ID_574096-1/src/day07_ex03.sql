SELECT COALESCE(ord.name, vis.name) AS name,
       COALESCE(ord.count, 0) + COALESCE(vis.count, 0) AS total_count
FROM (
    SELECT pz.name, COUNT(po.id) AS count
    FROM pizzeria pz
    JOIN menu m ON pz.id = m.pizzeria_id
    JOIN person_order po ON m.id = po.menu_id
    GROUP BY pz.name
) ord
FULL JOIN (
    SELECT pz.name, COUNT(pv.id) AS count
    FROM pizzeria pz
    JOIN person_visits pv ON pz.id = pv.pizzeria_id
    GROUP BY pz.name
) vis ON ord.name = vis.name
ORDER BY total_count DESC, name ASC;