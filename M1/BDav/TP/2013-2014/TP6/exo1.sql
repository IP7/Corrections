/* Requête */

CREATE TABLE comptes ( 
       numcompte integer PRIMARY KEY,
       nomclient varchar(20),
       solde numeric(10,2),
       decouvert_autorise numeric(10,2)
);

/* Insertion */

INSERT INTO comptes VALUES ('12345678','MarioBros','1000.00','200.00');
INSERT INTO comptes VALUES ('12345679','Barbie','200.00','0.00');
