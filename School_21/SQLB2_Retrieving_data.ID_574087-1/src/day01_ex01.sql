SELECT test.object_name
FROM
  (SELECT pizza_name AS object_name,
          'menu' AS label
  FROM menu
  UNION ALL SELECT name,
                   'person' AS label
  FROM person
  ORDER BY label DESC, object_name)
  AS test;