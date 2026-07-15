insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

WITH
balance_rows AS 
    (SELECT ROW_NUMBER() OVER (ORDER BY b.user_id, b.type, b.currency_id, b.updated, b.money) AS balance_row_id,
            b.user_id,
            b.money,
            b.type,
            b.currency_id,
            b.updated
     FROM balance b
     WHERE EXISTS (SELECT * FROM currency c WHERE b.currency_id = c.id)
     ),
past_rate AS 
    (SELECT br.balance_row_id,
            c.name AS currency_name,
            c.rate_to_usd,
            ROW_NUMBER() OVER (PARTITION BY br.balance_row_id ORDER BY c.updated DESC) AS rn
     FROM balance_rows br
     LEFT JOIN currency c ON br.currency_id = c.id AND c.updated <= br.updated
     ),
future_rate AS
    (SELECT br.balance_row_id,
            c.name AS currency_name,
            c.rate_to_usd,
            ROW_NUMBER() OVER (PARTITION BY br.balance_row_id ORDER BY c.updated ASC) AS rn
     FROM balance_rows br
     LEFT JOIN currency c ON br.currency_id = c.id AND c.updated > br.updated
     ),
selected_rate AS
    (SELECT br.balance_row_id,
            COALESCE(pr.currency_name, fr.currency_name) AS currency_name,
            COALESCE(pr.rate_to_usd, fr.rate_to_usd) AS rate_to_usd
     FROM balance_rows br
     LEFT JOIN past_rate pr ON pr.balance_row_id = br.balance_row_id AND pr.rn = 1
     LEFT JOIN future_rate fr ON fr.balance_row_id = br.balance_row_id AND fr.rn = 1
     )
SELECT COALESCE(u.name, 'not defined') AS name,
       COALESCE(u.lastname, 'not defined') AS lastname,
       sr.currency_name,
       br.money * sr.rate_to_usd AS currency_in_usd
FROM balance_rows br
LEFT JOIN selected_rate sr ON sr.balance_row_id = br.balance_row_id
LEFT JOIN "user" u ON u.id = br.user_id
ORDER BY name DESC,
         lastname ASC,
         currency_name ASC;