CREATE SEQUENCE seq_person_discounts START WITH 1;

ALTER TABLE person_discounts ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');

SELECT setval('seq_person_discounts', (SELECT COUNT(*) FROM person_discounts) + 1);

SELECT count(*)=1 AS check1,
      max("start_value") = 1 AS check2,
      max("last_value") > 5 AS check3
FROM pg_sequences
WHERE sequencename = 'seq_person_discounts';