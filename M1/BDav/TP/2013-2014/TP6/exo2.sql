/* Question 2.1 */

CREATE OR REPLACE TABLE comptes(
  numcompte integer PRIMARY KEY,
  nomclient varchar(20),
  solde numeric(10,2),
  decouvert_autorise numeric(10,2),
  CHECK (solde >= -decouvert_autorise)
);

/* Question 2.2 */

DROP TRIGGER IF EXISTS trig1 ON comptes;

CREATE TRIGGER trig1
  AFTER UPDATE OR INSERT
  ON comptes
  FOR EACH ROW
    EXECUTE PROCEDURE trig1();

CREATE OR REPLACE FUNCTION trig1() RETURNS TRIGGER AS $$
  DECLARE
  
  BEGIN
    IF(NEW.solde < 0) THEN
      RAISE NOTICE 'Solde negatif: %  ,pour le compte: %' , NEW.solde , NEW.numcompte;
    END IF;
    RETURN NULL;
END;

$$ LANGUAGE 'plpgsql';

/* Question 2.3 */

DROP TRIGGER IF EXISTS trig2 ON comptes;

CREATE TRIGGER trig2
  BEFORE DELETE
  ON comptes
  FOR EACH ROW
    EXECUTE PROCEDURE trig2();

CREATE OR REPLACE FUNCTION trig2() RETURNS TRIGGER AS $$
  DECLARE
    tmpnum INTEGER;
  BEGIN
    IF(OLD.solde = 0) THEN
      tmpnum = OLD.numcompte;
      RAISE NOTICE 'Suppresion du compte: %' , tmpnum;
	  RETURN OLD;
    ELSE
      RAISE NOTICE 'Vous ne pouvez pas faire cet action';
	  RETURN NULL;
    END IF;
END;

$$ LANGUAGE 'plpgsql';

/* Requête */ 

INSERT INTO comptes VALUES ('12345','TEST','0','100');
DELETE FROM comptes WHERE numcompte = 12345;