/* Table Audit */

CREATE TABLE audit (
       numoperation SERIAL PRIMARY KEY,
       numcompte INTEGER REFERENCES comptes,
       date_operation DATE,
       operation VARCHAR(10),
       CHECK (operation IN ('RETRAIT','OUVERTURE','DEPOT','FERMETURE')),
       montant numeric(10,2)
);

/* Trigger */

DROP TRIGGER IF EXISTS trig3 ON audit;

CREATE TRIGGER trig3
  AFTER INSERT OR UPDATE OR DELETE 
  ON comptes
  FOR EACH ROW
    EXECUTE PROCEDURE trig3();

CREATE OR REPLACE FUNCTION trig3() RETURNS TRIGGER AS $$
  DECLARE
  
  BEGIN
    IF(TG_OP = 'INSERT') THEN
      RAISE NOTICE 'INSERTION : OUVERTURE';
      INSERT INTO audit (numcompte,date_operation,operation,montant) VALUES (NEW.numcompte,CURRENT_DATE,'OUVERTURE',NEW.solde);
      RETURN NEW;
    ELSIF (TG_OP = 'UPDATE') THEN
      IF(OLD.solde < NEW.solde) THEN
        RAISE NOTICE 'MISE A JOUR : DEPOT';
	INSERT INTO audit (numcompte,date_operation,operation,montant) VALUES (NEW.numcompte,CURRENT_DATE,'DEPOT',NEW.solde);
      ELSE
        RAISE NOTICE 'MISE A JOUR : RETRAIT';
	INSERT INTO audit (numcompte,date_operation,operation,montant) VALUES (NEW.numcompte,CURRENT_DATE,'RETRAIT',NEW.solde);
      END IF;
      RETURN NEW;
    ELSE
      RAISE NOTICE 'SUPPRESSION : FERMETURE';
      --DELETE FROM comptes WHERE numcompte = NEW.numcompte;
      --INSERT INTO audit (numcompte,date_operation,operation,montant) VALUES (NEW.numcompte,CURRENT_DATE,'FERMETURE',NEW.solde);
      RETURN NEW;
    END IF;
END;

$$ LANGUAGE 'plpgsql';

/* Commande */

INSERT INTO comptes VALUES ('2413269','Luigi','100','10');
UPDATE comptes SET solde = 110 WHERE nomclient = 'Luigi';
UPDATE comptes SET solde = 0 WHERE nomclient = 'Luigi';
DELETE FROM comptes WHERE nomclient = 'Luigi'; 
