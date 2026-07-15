SELECT pizza_name, name AS pizzeria_name, price
FROM menu
FULL JOIN pizzeria p ON menu.pizzeria_id = p.id
WHERE pizza_name IN ('mushroom pizza', 'pepperoni pizza')
ORDER BY 1, 2;