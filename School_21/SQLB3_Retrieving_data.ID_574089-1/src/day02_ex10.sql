SELECT p.name, p2.name, p.address AS common_address
FROM person p
INNER JOIN person p2 ON p.id > p2.id
AND p.address = p2.address
ORDER BY 1, 2, 3;