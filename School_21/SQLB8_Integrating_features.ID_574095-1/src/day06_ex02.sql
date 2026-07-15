SELECT 
    p.name,
    m.pizza_name,
    m.price,
    m.price * (1 - pd.discount / 100) AS discount_price,
    pz.name AS pizzeria_name
FROM person p
JOIN person_order po ON p.id = po.person_id
JOIN menu m ON po.menu_id = m.id
JOIN pizzeria pz ON m.pizzeria_id = pz.id
JOIN person_discounts pd ON p.id = pd.person_id AND pz.id = pd.pizzeria_id
ORDER BY p.name, m.pizza_name;