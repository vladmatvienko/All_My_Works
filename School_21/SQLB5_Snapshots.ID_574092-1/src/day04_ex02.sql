CREATE VIEW v_generated_dates AS
SELECT gs::date AS generated_date
FROM generate_series('2022-01-01', '2022-01-31', interval '1 day') AS gs
ORDER BY 1;

SELECT count(*) = 31 AS CHECK,
      min(generated_date) AS check1,
      max(generated_date) AS check2
FROM v_generated_dates;
